<?php
/*
    PrizeListClass
    
   	List all comming competions for a user

    Used by:
        - evevt.main.js

        {
            "_group" : "Tdb",
            "_action" : "PrizePayout",
            "_event_id" : "648",
            "_event_name" : "Hjätat 2022-03-02",
            "_user_id" : "69",
            "_store_id" : "67",
            "_eco_record" : "1744,1912,1916,2160",
            "_token" : "67A84156ECD95A27C352777016B1BD76"
        }		


*/

class PrizePayoutClass extends AjaxClass {

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
        $param->_action= 'PrizePayout';
        $param->_event_id = $this->eventId;
        $param->_event_name = $this->eventName;
        $param->_store_id = $this->storeId;
        $param->_operator_id = $this->operatorId;
        $param->_user_id = $this->userId;
        $param->_eco_record = $this->ecoRecord;

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
        if (isset($data->_store_id)) {
			$this->storeId = trim($data->_store_id);
		}
		else {
			return false;
		}
        if (isset($data->_eco_record)) {
			$this->ecoRecord = trim($data->_eco_record);
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