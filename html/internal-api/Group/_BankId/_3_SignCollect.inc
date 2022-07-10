<?php
/*
     $reply->code = '1';CollectClass
    
   
    External need SSL:  

	{
		"_group" : "BankId",
		"_action" : "SignCollect",
        "_order_ref" : "test"
	}	

    ## Return OK
    {
        "code": "1",
        "name": "BO GRUSELL",
        "givenName": "BO",
        "surname": "GRUSELL",
        "ipAddress": "213.89.237.62",
        "signature": "",
        "ocspResponse": ""
    }
    ## Pending
    {
        "code": "2",
        "denied_code": "pending"
    }
    ## Fail
    {
        "code": "0",
        "denied_code": "bankid-problem"
    }

    {"code":"2","denied_code":"Pending"}
    {"code":"0","denied_code":"userCancel"}
    {"status":0,"denied_code":"No such order"} after cancel
    {"code":"0","denied_code":"expiredTransaction"}

*/

class SignCollectClass {

    private $orderRef;
	private $reply;
    
    public function _($data) {
        $this->reply = new stdClass();
        if ($this->parameterCheck($data) == false) {
            return array("code"=>"0", "denied_code"=>"parameter-fail");
        }
        if ($this->signControll() == false) {
            return array("code"=>"0", "denied_code"=>$this->reply->denied_code);
        }
       //echo '55';
        return $this->reply;
    }

    
	private function parameterCheck($data) {
        if (isset($data->_order_ref )) {
			$this->orderRef = trim($data->_order_ref );
		}
		else {
			return false;
		}
		return true;
	}

    private function signControll() {
        $isReady = false;
        $isOk = false;
        sleep(5);
        while ($isReady == false) {
            $result = $this->_signCollect();
            if(!$result) {
                $this->reply->code = "0";
                $this->reply->denied_code = "bankid_problem";
                $isReady = true;
            }
            else if (isset($result->errorCode)){ 
                $this->reply->code = 0;
                if (isset($result->details)) {
                    $this->reply->denied_code = $result->details;
                }
                else {
                    $this->reply->denied_code = "bankid_problem";
                }
                $isReady = true;
            } 
            else {
                switch ($result->status) {
                    case 'pending':
                        $this->reply->code = "2";
                        $this->reply->denied_code = 'Pending';
                        $isReady = false;
                        break;
                    case 'failed':
                        $this->reply->code = "0";
                        $this->reply->denied_code = $result->hintCode;
                        $isReady = true;
                        break;
                    case 'complete':
                        $this->reply->code = "1";
                        $this->reply->name = $result->completionData->user->name;
                        $this->reply->givenName = $result->completionData->user->givenName;
                        $this->reply->surname = $result->completionData->user->surname;
                        $this->reply->ipAddress = $result->completionData->device->ipAddress;
                        $this->reply->signature = $result->completionData->signature;
                        $this->reply->ocspResponse = $result->completionData->ocspResponse;
                        $isOk = true;
                        $isReady = true;
                        break;
                    default:
                        $this->reply->code = "0";
                        $this->reply->denied_code = "bankid_problem";
                        $isOk = false;   
                }   
            }
        }
        if ($isOk) {
            return true;
        } 
        else {
            return false;
        } 
    }

    private function _signCollect() {
      
        $json = '{"orderRef":"' . $this->orderRef . '"}';
        $curlCheck = curl_init();
        curl_setopt( $curlCheck, CURLOPT_URL, 'https://appapi2.bankid.com/rp/v5/collect');
        curl_setopt($curlCheck, CURLOPT_CUSTOMREQUEST, "POST");
        curl_setopt($curlCheck, CURLOPT_POSTFIELDS, $json);
        curl_setopt($curlCheck, CURLOPT_RETURNTRANSFER, 1);
        curl_setopt($curlCheck, CURLOPT_HTTPHEADER, array(
            'Content-Type: application/json',
            'Content-Length: ' . strlen($json))
        );
        curl_setopt($curlCheck, CURLOPT_CAINFO, 'cert/bankid.ca.pem');
        curl_setopt($curlCheck, CURLOPT_SSLKEY, 'cert/turtlepay2.key');
        curl_setopt($curlCheck, CURLOPT_SSLCERT, 'cert/turtlepay2.pem');
        curl_setopt($curlCheck, CURLOPT_SSLCERTPASSWD, 'Fk&1618BKl@tp');
        curl_setopt($curlCheck, CURLOPT_SSL_VERIFYHOST, 0);
        curl_setopt($curlCheck, CURLOPT_SSL_VERIFYPEER, 0);

        $result = curl_exec($curlCheck);
        if ($this->_JsonValidate($result)) {
            return json_decode($result);
        }
        else {
            $reply = new stdClass();
            $reply->code = '0';
            return json_decode($reply); 
        }
    }

    //JSON Validator function
    private function _JsonValidate($data=NULL) {
        if (!empty($data)) {
            json_decode($data);
            return (json_last_error() === JSON_ERROR_NONE);
        }
        return false;
    }
}