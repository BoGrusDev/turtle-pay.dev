<?php
/*
    TokenCheckClass
    
    Check if token is valid and return priv and some other info
    
    Called from all calls from service2, to validate the call
    Called from: Kundportal Pages(event/event-main.js
    
  
	{
		"_group" : "Priv",
		"_action" : "TokenCheck,
		"_user_id" : "69",
        "_token" : "6817A0722A87AD4695F09EA0C9A782C2"
	}	
    for result se KAPI.

*/
require_once 'Group/Priv/PrivBase.inc';

class PrivTokenCheckClass extends PrivBaseClass {

    private $userId;
    private $token;
    private $cperatorId;
    private $reply;

    public function _($data) {
        // Check if all demand paramer exist
        if ($this->parameterCheck($data) == false) {
            return array("code"=>"0");
        }

        if ($this->tokenCheck() == false) {
            return array("code"=>"0");
        }
     
        return $this->reply;
    }

	private function parameterCheck($data) {
		/*
			Check and set all parameter.
			If not exist and mandaty return false
		*/
		
		// Check API paramer
		if (isset($data->_company_id)) {
			$this->companyId = trim($data->_company_id);
		}
		else {
			return false;
		}

        if (isset($data->_people_id)) {
			$this->peopleId = trim($data->_people_id);
		}
		else {
			return false;
		}        
        if (isset($data->_cp_id)) {
			$this->cpId = trim($data->_cp_id);
		}
		else {
			return false;
		}

        if (isset($data->priv)) {
			$this->priv = trim($data->priv);
		}
		else {
			return false;
		}
      
		$reply= $this->superUserCheck($this->companyId, $this->peopleId);
		if ($reply['code'] != '1') {
			return false;
		}
		return true;
	}

    private function tokenCheckCall() {
        /* 
            Called to validate token and get the operatorId (people_id)
        
            */

        $param = new stdClass();
        $param->_group = "Priv";
        $param->_action = "TokenCheck";
        $param->_token = $this->token;
        $param->_user_id = $this->userId;
        $this->reply = $this->_RestApiCall($param);
    }

    /*
        private function tokenCheck() {
        $reply = new stdClass();
        $sql = "SELECT people_id, last_access FROM token WHERE token = '$this->token' AND status = 'w'";
        $result = $this->_get($sql);
        if ($result['code'] == "1") {
            // Check the date if it is expiere
            $this->operatorId = $result['people_id'];
        }
        else {
            return false;
        }
    */
}