<?php
/*
    CollectClass
    
    Get personal informationn from SPAR
    
    External need SSL:  spar-cert.pem

	{
		"_group" : "BankId",
		"_action" : "SignInit",
        "_personal_id_number" : "195711040054",
		"_bankid_text" : "Testa av ny signering"
	}	

*/

class SignInitClass {

    private $personalIdNumber;
    private $bankIdText;
	private $reply;
    
    public function _($data) {
	
        if ($this->parameterCheck($data) == false) {
            return array("code"=>"0", "denied_code"=>"parameter-fail");
        }
		$this->reply = new stdClass();

        if ($this->signInit() == false) {
            return $this->reply;
        }
        
        return $this->reply;
    }

	private function parameterCheck($data) {
        if (isset($data->_personal_id_number)) {
			$this->personalIdNumber = trim($data->_personal_id_number);
		}
		else {
			return false;
		}
        if (isset($data->_bankid_text)) {
			$this->bankidText = trim($data->_bankid_text);
		}
		else {
			return false;
		}
		return true;
	}

    private function signInit() {
        $json = '{"personalNumber":"' . $this->personalIdNumber . '", "endUserIp":"176.57.88.50", "userVisibleData" : "' . base64_encode($this->bankidText) . '"}';
        $curl = curl_init();
        curl_setopt( $curl, CURLOPT_URL, 'https://appapi2.bankid.com/rp/v5/sign');
        curl_setopt($curl, CURLOPT_CUSTOMREQUEST, "POST");
        curl_setopt($curl, CURLOPT_POSTFIELDS, $json);
        curl_setopt($curl, CURLOPT_RETURNTRANSFER, 1);
        curl_setopt($curl, CURLOPT_HTTPHEADER, array(
            'Content-Type: application/json',
            'Content-Length: ' . strlen($json))
        );
        curl_setopt($curl, CURLOPT_CAINFO, 'cert/bankid.ca.pem');
        curl_setopt($curl, CURLOPT_SSLKEY, 'cert/turtlepay2.key');
        curl_setopt($curl, CURLOPT_SSLCERT, 'cert/turtlepay2.pem');
        curl_setopt($curl, CURLOPT_SSLCERTPASSWD, 'Fk&1618BKl@tp');
        curl_setopt($curl, CURLOPT_SSL_VERIFYHOST, 0);
        curl_setopt($curl, CURLOPT_SSL_VERIFYPEER, 0);
        $result = curl_exec($curl);
        curl_close($curl);

        if($result == false) {
            $this->reply->code = "0";
            $this->reply->denied_code = "bankid_problem";
            return false;
        }
    
        $authObject = json_decode($result);
        if (isset($authObject->orderRef)) {
            $this->reply->code = "1";
            $this->reply->order_ref = $authObject->orderRef;
            $this->reply->denied_code = "";
            $this->reply->auto_start_token = $authObject->autoStartToken; // Till lögg för Web App
            return true;
        }
        else {
            $this->reply->code = "0";
            if (isset($authObject->errorCode)) {
                $this->reply->denied_code = $authObject->errorCode;
            }
            else {
                $this->reply->denied_code = "bankid-problem";
            }
            return false;
        }
    }

}