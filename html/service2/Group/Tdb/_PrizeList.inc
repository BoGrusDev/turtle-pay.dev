<?php
/*
    PrizeListClass
    
   	List all comming competions for a user

    Used by:
        - evevt.main.js

*/

class PrizeListClass extends AjaxClass {

    private $token;
    private $userId;
    private $operatorId;
    private $priv;
    

    public function _($data) {
        if ($this->parameterCheck($data) == false) {
            return array("code"=>"0", "denide_code"=>"param-fail");
        }
        if ($this->TokenCheck($data) == false) {
            return array("code"=>"0", "denide_code"=>"token-fail");
        }
        $param = new stdClass();
		$param->_group = 'Tdb';
        $param->_action= 'PrizeList';
        $param->_event_id = $this->eventId;
        $param->_operator_id = $this->operatorId;
        $param->_user_id = $this->userId;

        //echo json_encode($param); die('');

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