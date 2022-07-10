<?php
/*
    ProcessClass
    {
        "_group": "WebAppTdb",
        "_action": "Process",
        "_order_ref": "b9d15baa-3b9d-4149-81fa-470a0db01f58"
    }
*/


class ProcessClass extends BaseClass {

    private $orderRef;
    private $webAppLog; 
	private $reply;

    public function _($data) {

		if ($this->parameterCheck($data) == false) {
			return array("code"=>"0", "denied_code"=>"parameter-fail");
		}

        if ($this->webAppLogGet() == false) {
			return array("code"=>"0", "denied_code"=>"not-in-progress");
		}

        //print_r($this->webAppLog);
        //die('');

        /*
        if ($this->signCollect() == false) {
			return array("code"=>"0", "denied_code"=>"not-in-progress");
		}
        */
        $this->bankidSign = new stdClass();
        $this->bankidSign->signature = 'signatur';
        $this->bankidSign->ocspResponse = 'ocsp-response';
        $this->invoiceRequestConfirm();

        if ( $this->invoiceComplete() == false) {
			return array("code"=>"0", "denied_code"=>"complete-rejected");
		}
       
        $this->invoiceEmail();

        $reply = new stdClass();
        $reply->code = '1';
        
        return $reply;

    }

    private function parameterCheck($data) {
        if (isset($data->_order_ref)) {
			$this->orderRef = trim($data->_order_ref);
		}
		else {
			return false;
		}
        
		return true;
	}

    private function webAppLogGet() {
		$sql = "SELECT * FROM webapp_log ";
		//$sql .= "WHERE approved_code = '$approvedCode'";
		$sql .= "WHERE order_ref = '$this->orderRef'";
		$this->webAppLog = $this->_Get($sql);
		if ($this->webAppLog ['code'] == "1") {
			return true;
		}
		else {
			return false;
		}
    }

    private function signCollect() {

    }

    private function invoiceRequestConfirm() {
        $param = new stdClass();
        $param->_group = "InvoiceRequestConfirm";
        $param->_action = "Complete";
        $param->receipt_number = $this->webAppLog['receipt_number'];
        $param->cr_id = '1';
        $param->_approved_code = $this->webAppLog['approved_code'];
        $param->_order_ref =  $this->orderRef;
        $param->signature = $this->bankidSign->signature;
        $param->ocspResponse = $this->bankidSign->ocspResponse;        
        $this->invoiceRequestConfirm = $this->_RestApiCall($param, CAPI_URL);
        if ($this->invoiceRequestConfirm->code == '1') {
            return true;
        }
        else {
            return false;
        }
    }

    private function invoiceComplete() {
		/*
		    Set a transaction complete, update, people, name, and invoice_id_id

		    1. Get the people name, people_id from credit_id
		    2. Update event_item
		    3. Update people (if mobile no is applied) 
		    4. Update inovoice_request_item, if from invoice request
		*/
		
		// --
		// -- 1. Get the people name, people_id from credit_id
		// --
		$sql = "SELECT p.people_id, CONCAT(p.last_name, ' ' ,p.first_name) AS people_name ";
		$sql .= "FROM people p, credit c ";
		$sql .= "WHERE c.credit_id = " . $this->invoiceRequestConfirm->credit_id . " AND c.people_id = p.people_id";
		$person = $this->_Get($sql);
		
		// --
		// -- 2. Update event_item
		// --
		$param = new stdClass();
		$param->people_id = $person['people_id'];
		$peopleName = $person['people_name'];
		$peopleName = str_replace ("'", "\'", $peopleName); // Fix for special char
		$param->people_name = $peopleName;
		$param->credit_id = $this->invoiceRequestConfirm->credit_id;
		$param->event_item_status = 'c';
		$reply = $this->_Update('event_item_v4', 'event_item_id', $this->invoiceRequestConfirm->event_item_id, $param);
		
		// --
		// -- 3. Update people (if mobile no is applied) and the email
		// --
		$sql = "SELECT mobile, invoice_event_item_id, email, amount FROM event_item_v4 WHERE event_item_id = $this->invoiceRequestConfirm->event_item_id ";
		$resEvent = $this->_Get($sql);
		$paramUpdate = new stdClass();
            //if (strlen($resEvent['mobile']) > 7 ) {
            //	$paramUpdate->mobile = $resEvent['mobile'];
            //}
		$paramUpdate->email = $this->invoiceRequestConfirm->credit_id;
		$res = $this->_Update('people', 'people_id', $result['people_id'], $paramUpdate);
	
		if ($this->invoiceRequestConfirm->event_item_id] > '0') {
			$paramUpdate = new stdClass();
			$paramUpdate->people_id = $person['people_id'];
			$paramUpdate->people_name = $person['people_name'];
			$paramUpdate->event_item_id = $this->invoiceRequestConfirm->event_item_id;
			$paramUpdate->invoice_event_item_status = 'c';
			$paramUpdate->amount = $this->invoiceRequestConfirm->amount;
			$paramUpdate->email = $this->invoiceRequestConfirm->credit_id;
			$dt = new DateTime();
			$paramUpdate->confirmed_datetime = $dt->format('Y-m-d H:i:s');
			$reply = $this->_Update('invoice_event_item', 'invoice_event_item_id', $this->invoiceRequestConfirm->invoice_event_item_id, $paramUpdate);
		}
	}

    private function invoiceEmail() {
        if (ENV_TYPE == 'prod') {
            $paramEmail = new StdClass();
            $paramEmail->_group = "Email";
            $paramEmail->_action = "FirstInvoice";
            $paramEmail->_invoice_filename = $this->invoiceRequestConfirm->email;
            $paramEmail->email = $this->invoiceRequestConfirm->email;
            $res = $this->_RestApiCall($paramEmail, CAPI_URL);
            return true;
        }
        else {
            true;
        }
    }

    private function _webappStatuSet($statusCode, $deniedCode = '') {
        $param = new stdClass();
        $param->webapp_log_status = $statusCode;
        $param->denied_code = $deniedCode;
        $this->_Update('webapp_log', 'webapp_log_id', $this->webappLogId, $param);
    }

}