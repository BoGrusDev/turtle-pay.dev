<?php
/*
    ProcessClass
  {
    "_group": "WebAppTdb",
    "_action": "Process",
    "_approved_code": "6F2C1784-4CEA-309C-2E77-FCC507F607BD",
    "_web_app_tdb_log_id" : "2"
}
*/

require_once 'Group/WebAppTdb/WebAppTdbBase.inc';

class ProcessClass extends WebAppTdbBaseClass {

    private $approvedCode;
    private $orderRef;
    private $webAppLog; 
	private $reply;
    private $invoiceEventItemId;
    private $email;

    public function _($data) {
        $this->webAppTdbLoggAction = "Process";
        $this->reply = new stdClass();
		if ($this->parameterCheck($data) == false) {
			return array("code"=>"0", "denied_code"=>"parameter-fail");
		}

        // Get orderRef to collect th Signing
        if ($this->webAppLogGet() == false) {
			return array("code"=>"0", "denied_code"=>"not-in-progress");
		}

        //print_r($this->webAppLog); die('');

        if ($this->InvoiceReqestValid() == false) {
			return array("code"=>"0", "denied_code"=>"not-in-progress");
		}
        
        if ($this->signCollect() == false) {
            return $this->reply;
			// return array("code"=>"0", "denied_code"=>"not-in-progress");
		}
        
        
        if ( $this->invoiceRequestConfirmCall() == false) {
			return array("code"=>"0", "denied_code"=>"complete-rejected");
		}

        // print_r($this->invoiceRequestConfirm); die('');
    
        if ($this->invoiceComplete() == false) {
			return array("code"=>"0", "denied_code"=>"complete-rejected");
            return false;
		}
        
        $this->invoiceSignedSet();

        if ($this->invoiceEmail() == false) {
            $this->reply->mail_status = 'fail';
		}
        else {
            $this->reply->mail_status = 'ok';
        }

        $this->reply->code = '1';
        
        return $this->reply;

    }

    private function parameterCheck($data) {
        if (isset($data->_web_app_tdb_log_id)) {
			$this->webAppTdbLogId = trim($data->_web_app_tdb_log_id);
            $this->_WebWebAppTdbLog((object) ['part'=>'Enter']);
		}
		else {
            $this->paramError = '_web_app_tdb_log_id';
			return false;
		}
        if (isset($data->_approved_code)) {
			$this->approvedCode = trim($data->_approved_code);
		}
		else {
			return false;
		}
        
		return true;
	}

    private function webAppLogGet() {
		$sql = "SELECT * FROM wa_log_v4 ";
		$sql .= "WHERE approved_code = '$this->approvedCode'";
		$this->webAppLog = $this->_Get($sql);
		if ($this->webAppLog['code'] == "1") {
            $this->orderRef = $this->webAppLog['order_ref'];
            $this->invoiceEventItemId = $this->webAppLog['invoice_event_item_id'];
            $this->email = $this->webAppLog['email'];
            // $this->receiptNumber = $this->webAppLog['receipt_number'];
			return true;
		}
		else {
			return false;
		}
    }

    private function InvoiceReqestValid() {
        $sql = "SELECT invoice_request_id FROM invoice_request ";
		$sql .= "WHERE approved_code = '$this->approvedCode' AND invoice_request_status = 'a' ";
		$reply = $this->_Get($sql);
		if ($reply['code'] == "1") {
			return true;
		}
		else {
            $this->_WebWebAppTdbLog((object) ['part'=>"InvoiceReqestValid", "step"=>"Select Fail", 'denied_code'=>'not-in-progress',"step_ref"=>$this->approvedCode]);
			return false;
		}
    }

    private function signCollect() {
       
        // $bankIdText = str_replace('_ReceiptNumber_' ,$this->receiptNumber, $this->invoiceRequest->bankid_text);
        $param = new StdClass();
        $param->_group  = "BankId";
        $param->_action = "SignCollect";
        $param->_order_ref =  $this->orderRef;
       
        $reply = $this->_RestApiCall($param, INTERNAL_API);
        if ($reply->code == '1') {
            $this->_WebWebAppTdbLog((object) ['part'=>'SignCollect', 'step'=>"OK"]);
            $this->signature = $reply->signature;
            $this->ocspResponse = $reply->ocspResponse;
            return true;
        }
        else {
            $this->_WebWebAppTdbLog((object) ['part'=>'SignCollect', 'step'=>"Fail", 'step_ref'=>$reply->denied_code]);
            $this->reply->code = $reply->code;
            $this->reply->denied_code = $reply->denied_code;
            return false;
        }
        // return json_decode($this->_RestApiCall(json_encode($param)));
    }
    
    private function invoiceRequestConfirmCall() {
        $param = new stdClass();
        $param->_group = "InvoiceRequestConfirm";
        $param->_action = "Complete";
        $param->receipt_number = $this->webAppLog['receipt_number'];
        $param->cr_id = '1';
        $param->_approved_code = $this->webAppLog['approved_code'];
        $param->_order_ref =  $this->webAppLog['order_ref'];
        $param->signature = $this->signature;
        $param->ocspResponse = $this->ocspResponse;        
        $this->invoiceRequestConfirm = $this->_RestApiCall($param, CAPI_URL);
        if ($this->invoiceRequestConfirm->code == '1') {
            $this->_WebWebAppTdbLog((object) ['part'=>"InvoiceRequestConfirm", "step"=>"Call OK", "step_ref"=>$this->webAppLog['approved_code']]);
            return true;
        }
        else {
            $this->_WebWebAppTdbLog((object) ['part'=>"InvoiceRequestConfirm", "step"=>"Call Fail", "step_ref"=>$this->webAppLog['approved_code']]);
            return false;
        }
    }

    private function invoiceSignedSet() {
        /*
            Set the people to sign, to block more than one siging
        */
        $sql = "SELECT tp.tdb_people_id FROM invoice_event_item ie, tdb_people tp ";
        $sql .= "WHERE ie.invoice_event_item_id = $this->invoiceEventItemId AND ";
        $sql .= "ie.invoice_event_item_code = tp.item_code";
		$reply = $this->_Get($sql);
		if ($reply['code'] == "1") {
            $tdbPeopleId = $reply['tdb_people_id'];
		}
		else {
			return false;
		}
        $param = new stdClass();
        $param->action = 'sign';
        $this->_Update('tdb_people', 'tdb_people_id', $tdbPeopleId, $param);
	}

    private function invoiceComplete() {
        /*
            Set a transaction complete, update, people, name, and invoice_id_id

            1. Get the people name, people_id from credit_id
            2. Update event_item
            3. Update people (if mobile no is applied) 
            4. Update inovoice_request_item, if from invoice request
        */
        
        $webAppLog = (object) $this->webAppLog;

        // --
        // -- 1. Get the people name, people_id from credit_id
        // --
        $sql = "SELECT p.people_id, CONCAT(p.last_name, ' ' ,p.first_name) AS people_name ";
        $sql .= "FROM people p, credit c ";
        $sql .= "WHERE c.credit_id = " . $this->invoiceRequestConfirm->credit_id . " AND c.people_id = p.people_id";
        $person = $this->_Get($sql);
        if ($person['code'] == '1') {
        }
        else {
            $this->_WebWebAppTdbLog((object) ['part'=>"invoiceComplete", "step"=>"Select people-credit", "step_ref"=>$this->invoiceRequestConfirm->credit_id]);
            return false;
        }


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
        $reply = $this->_Update('event_item_v4', 'event_item_id', $webAppLog->event_item_id, $param);
        if ($reply['code'] == '1') {
        }
        else {
            $this->_WebWebAppTdbLog((object) ['part'=>"invoiceComplete", "step"=>"Update event-item-v4", "step_ref"=>$this->invoiceRequestConfirm->credit_id]);
            return false;
        }


        // --
        // -- 3. Update people (if mobile no is applied) and the email
        // --
        $sql = "SELECT mobile, invoice_event_item_id, email, amount FROM event_item_v4 WHERE event_item_id = " . $webAppLog->event_item_id;
        $resEvent = $this->_Get($sql);
        $paramPeopleUpdate = new stdClass();
        if (strlen($resEvent['mobile']) > 7 ) {
        	$paramPeopleUpdate->mobile = $resEvent['mobile'];
        }
        $paramPeopleUpdate->email = $webAppLog->email;
        $res = $this->_Update('people', 'people_id', $person['people_id'], $paramPeopleUpdate);
        if ($res['code'] == '1') {
        }
        else {
            $this->_WebWebAppTdbLog((object) ['part'=>"invoiceComplete", "step"=>"Update people", "step_ref"=> $person['people_id']]);
            return false;
        }
     
        $paramUpdate = new stdClass();
        $paramUpdate->people_id = $person['people_id'];
        $paramUpdate->people_name = $person['people_name'];
        $paramUpdate->event_item_id =  $webAppLog->event_item_id;
        $paramUpdate->invoice_event_item_status = 'c';
        $paramUpdate->amount = $webAppLog->amount;
        $paramUpdate->email = $webAppLog->email;
        $dt = new DateTime();
        $paramUpdate->confirmed_datetime = $dt->format('Y-m-d H:i:s');
        $reply = $this->_Update('invoice_event_item', 'invoice_event_item_id',  $webAppLog->invoice_event_item_id, $paramUpdate);
        if ($reply['code'] == '1') {
        }
        else {
            $this->_WebWebAppTdbLog((object) ['part'=>"invoiceComplete", "step"=>"Update invoice_event_item", "step_ref"=> $webAppLog->invoice_event_item_id]);
            return false;
        }

        return true;
    }

    private function invoiceEmail() {
        //if (ENV_TYPE == 'prod') {
        $paramEmail = new StdClass();
        $paramEmail->_group = "Email";
        $paramEmail->_action = "FirstInvoice";
        $paramEmail->_invoice_filename = $this->invoiceRequestConfirm->invoice_filename;
        $paramEmail->email = $this->email;
        $reply = $this->_RestApiCall($paramEmail, CAPI_URL);
        if ($reply->code == '1') {
            $this->_WebWebAppTdbLog((object) ['part'=>"invoiceEmail", "step"=>"Send OK", "step_ref"=>$paramEmail->email]);
            return true;
        }
        else {
            $this->_WebWebAppTdbLog((object) ['part'=>"invoiceEmail", "step"=>"Send Fail", "step_ref"=>$this->invoiceRequestConfirm->invoice_filename]);
            return false;
        }  
    }

    /*
    private function _webappStatuSet($statusCode, $deniedCode = '') {
        $param = new stdClass();
        $param->webapp_log_status = $statusCode;
        $param->denied_code = $deniedCode;
        $this->_Update('webapp_log', 'webapp_log_id', $this->webappLogId, $param);
    }
    */
}