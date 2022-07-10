<?php
/*
    ContractSignInitClass

	{
		"_group" : "Company",
		"_action" : "Contract",
        "_user_id" : "69",
		"_token" : "AD1E5395150A9010C9558A2E90F85EFD", 
		"_order_ref": "2f7c201e-07d2-47d4-af12-26cd43b5cd0a"
	}	
    */

class ContractClass extends AjaxClass {



    public function _($data) {

        $this->reply = new stdClass();
        if ($this->parameterCheck($data) == false) {
            return array("code"=>"0", "denied_code"=>"param-fail");
        }

        if ($this->tokenCheck() == false) {
            return array("code"=>"0");
        }

        $this-> contract();    
        
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
        if (isset($data->_order_ref)) {
            $this->orderRef = $data->_order_ref;
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

    private function contract() {
        $param = new stdClass();
        $param->_group = 'Company';
        $param->_action ='Contract';
        $param->_operator_id = $this->operatorId;
        $param->_user_id = $this->userId;
        $param->_order_ref = $this->orderRef;
        // echo json_encode($param); die('');
        $this->reply = $this->_RestApiCall($param);
    }

}
