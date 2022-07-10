<?php
/*
   EventCloseClass
    
   

	{
		"_group" : "Tdb",
		"_action" : "EventClose",
		"_user_id" : "69",
        "_token" : "FAD8533D01875141E502FF5EBD99CD8C",
        "_event_id" : "659"
	}	

*/

class EventCloseClass extends AjaxClass {

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
        $param->_action= 'EventClose';
        $param->_operator_id = $this->operatorId;
        $param->_user_id = $this->userId;
        $param->_event_id = $this->eventId;

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