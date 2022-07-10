<?php
/*
    ContractSignInitClass

	{
		"_group" : "Company",
		"_action" : "ContractCheck",
        "_user_id" : "69",
		"_token" : "AD1E5395150A9010C9558A2E90F85EFD""
	}	
    */

class ContractCheckClass extends AjaxClass {


    public function _($data) {

        $this->reply = new stdClass();
        if ($this->parameterCheck($data) == false) {
            return array("code"=>"0", "denied_code"=>"param-fail");
        }

        if ($this->tokenCheck() == false) {
            return array("code"=>"0");
        }

        $this-> contractCheck();    
        
        return $this->reply;
    }

    private function parameterCheck($data) {
        if (isset($data->_token)) {
            $this->token = $data->_token;
        }
        else {
            return false;
        }
        if (isset($data->_user_id)) {
            $this->userId = $data->_user_id;
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
            return true;
        }
        else {
            return false;
        }
    }

    private function contractCheck() {
        $param = new stdClass();
        $param->_group = 'Company';
        $param->_action ='ContractCheck';
        $param->_operator_id = $this->operatorId;
        $param->_user_id = $this->userId;
        $this->reply = $this->_RestApiCall($param);
    }

}
