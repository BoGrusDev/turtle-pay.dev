<?php
/*
    UpdateClass
    
    Update privioliges for a person
    Only superuser has permission

	{
		"_group" : "Priv",
		"_action" : "Update,
		"_user_id" : "69",
        "_operator_id" : "1",
        "_cp_id" : "207",
        "priv" : "sp"
	}	

*/
require_once 'Group/Priv/PrivBase.inc';

class UpdateClass extends PrivBaseClass {

    private $userId;
	private $operatorId;
    private $cpId;
	private $priv;

    public function _($data) {
        // Check if all demand paramer exist
        if ($this->parameterCheck($data) == false) {
            return array("code"=>"0");
        }

        $reply = $this->peopleUpdate();
        return $reply;
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

        if (isset($data->_operator_id)) {
			$this->operatorId = trim($data->_operator_id);
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
      
		$reply= $this->superUserCheck($this->userId, $this->operatorId);
		if ($reply['code'] != '1') {
			return false;
		}
		return true;
	}

	private function peopleUpdate() {
        $sql = "UPDATE company_people SET priv = '$this->priv' WHERE cp_id = $this->cpId";
		$reply =  $this->_Query($sql);
		return $reply;
	}

}