<?php
/*
    CheckClass
    
    Kollar priv off operator.
    if none or pe return ccode 0
    else return code 1 and the oriv
    Only Superuser has permission

	{
		"_group" : "Priv",
		"_action" : "Check,
		"_user_id" : "69",
       	"_token" : "6B94C2B1E12EBD0637170A6E453B1B50"
	}	

*/

class CheckClass extends AjaxClass {

    private $userId;
	private $operatorId;
	private $privInfo;

    public function _($data) {
        // Check if all demand paramer exist
        if ($this->parameterCheck($data) == false) {
            return array("code"=>"0", "denied_code"=>"param-fail");
        }

		$this->privInfo = $this->_TokenCheck($this->token, $this->userId);

		if ($this->privInfo->code == '0') {
            return array("code"=>"0", "denied_code"=>"no-priv");
        }

		if ($this->privInfo->priv == 'pe') {
            return array("code"=>"0", "denied_code"=>"no-priv");	
        }
        
        $reply = new stdClass();
        $reply->code = '1';
        $reply->priv = $this->privInfo->priv;
        return $reply;
    }

	private function parameterCheck($data) {
		if (isset($data->_user_id)) {
			$this->userId = trim($data->_user_id);
		}
		else {
			return false;
		}
        if (isset($data->_token)) {
			$this->token = trim($data->_token);
		}
		else {
			return false;
		}        
		return true;
	}

}