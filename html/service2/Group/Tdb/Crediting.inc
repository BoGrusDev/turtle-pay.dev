<?php
/*
   InvoicingClass
    
   	Invoice a event

    Used by:
        - event-main.js

	{
		"_group" : "Company",
		"_action" : "Crediting",
		"_user_id" : "127",
        "_token" : "E6170BB7CA5BA3D060BBDB6517C6E9DA",
        "_event_id" : "683",
        "_event_name" : "Ponny och Hästhoppning 22 maj"
	}	

    Call to kai
     {
		"_group" : "Tdb",
		"_action" : "Crediting",
        "_event_id" : "683",
        "_event_name" : "Ponny och Hästhoppning 22 maj",
		"_user_id" : "127",
        "_operator_id" : "1"
	}	


*/

class CreditingClass extends AjaxClass {

    private $token;
    private $userId;
    private $operatorId;
    private $eventId;
    private $priv;
    
    public function _($data) {
        if ($this->parameterCheck($data) == false) {
            return array("code"=>"0");
        }
        if ($this->TokenCheck($data) == false) {
            return array("code"=>"0");
        }
        $param = new stdClass();
		$param->_group = 'Tdb';
        $param->_action= 'Crediting';
        $param->_operator_id = $this->operatorId;
        $param->_user_id = $this->userId;
        $param->_event_id = $this->eventId;
        $param->_event_name = $this->eventName;

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
        if (isset($data->_event_id)) {
			$this->eventId = trim($data->_event_id);
		}
		else {
			return false;
		}
        if (isset($data->_event_name)) {
			$this->eventName = trim($data->_event_name);
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