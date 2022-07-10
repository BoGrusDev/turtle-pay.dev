<?php
/*
   InvoicingClass
    
   	Invoice a event

    Used by:
        - event-main.js
{
        "_group": "Tdb",
        "_action": "PeopleFileCreate",
        "_token": "57559D3E4F1DE94A4735967B9F515958",
        "_user_id": "69",
        "_event_id": "648",
        "_people_id": "1"
    }

*/

class PeopleFileCreateClass extends AjaxClass {

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
        $param->_action= 'PeopleFileCreate';
        $param->_operator_id = $this->operatorId;
        $param->_user_id = $this->userId;
        $param->_event_id = $this->eventId;
        //return json_decode('{"code":"1","counter":336,"file_name":"69-648-2022-03-10-1203.json"}');
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