<?php
/*
    PrivUpdateClass
    
    Update privioliges for a person
    Only superuser has permission

	{
		"_group" : "Priv",
		"_action" : "Update,
		"_user_id" : "69",
       	"_token" : "780CCE158AA7C7D449E69AF19A7DD8CB"
        "_cp_id" : "207",
        "priv" : "sp"
	}	

*/

class UpdateClass extends AjaxClass {

    private $userId;
	private $operatorId;
    private $peopleId;
    private $cpId;
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

		if ($this->privInfo->priv == 'su') {
			$data->_operator_id = $this->privInfo->operatorId;
			$this->reply = $this->_RestApiCall($data);
        	return $this->reply;
        }
		else {
			return array("code"=>"0", "denied_code"=>"no-priv");
		}

    }

	private function parameterCheck($data) {
		/*
			Check and set all parameter.
			If not exist and mandaty return false
		*/
		
		// Check API paramer
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
		/*
		$reply= $this->superUserCheck($this->userId, $this->operatorId);
		if ($reply['code'] != '1') {
			return false;
		}
		*/
		return true;
	}

}