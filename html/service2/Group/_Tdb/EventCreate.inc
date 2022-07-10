<?php
/*
    EventCreateClass
    
    2022-02-16

    Used by:
        -event-main.js

	{
		"_group" : "Tdb",
		"_action" : "EventCreate",
		"_user_id" : "69",
        "_token" : "E6170BB7CA5BA3D060BBDB6517C6E9DA",
        "_event_name" : "Test",
        "_competion_id" : "41991"
	}	

*/

class EventCreateClass extends AjaxClass {

    private $token;
    private $userId;
    private $operatorId;
    private $eventName;
    private $competionId;
    
    public function _($data) {
        if ($this->parameterCheck($data) == false) {
            return array("code"=>"0");
        }
        if ($this->TokenCheck($data) == false) {
            return array("code"=>"0");
        }
        $param = new stdClass();
		$param->_group = 'Tdb';
        $param->_action= 'EventCreate';
        $param->_operator_id = $this->operatorId;
        $param->_user_id = $this->userId;
        $param->event_name = $this->eventName;
        $param->_meeting_no = $this->competionId;
        // return $param;
		return $this->_RestApiCall($param);
    }

	private function parameterCheck($data) {
		
        if (isset($data->_token)) {
			$this->token = trim($data->_token);
		}
		else {
			return false;
		}
		if (isset($data->_user_id)) {
			$this->userId = trim($data->_user_id);
		}
		else {
			return false;
		}
        if (isset($data->event_name)) {
			$this->eventName = trim($data->event_name);
		}
		else {
			return false;
		}
        if (isset($data->_competion_id)) {
			$this->competionId = trim($data->_competion_id);
		}
		else {
			return false;
		}
		return true;

	}

    private function tokenCheck() {
        $res = $this->_TokenCheckCall($this->token, $this->userId);
        if ($res->code == '1') {
            $this->operatorId = $res->operator_id;
            if ( $this->userId > 0) {
                $this->priv = $res->priv;
            }
            return true;
        }
        else {
            return false;
        }
    }
}