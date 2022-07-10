<?php
/*
    InfoGetClass
    
   	Get the company info

    Used by:
        - evevt.main.js

	{
		"_group" : "Company",
		"_action" : "Info",
		"_user_id" : "69",
        "_token" : "E6170BB7CA5BA3D060BBDB6517C6E9DA"
	}	

*/

class InfoGetClass extends AjaxClass {

    private $token;
    private $userId;
    private $operatorId;
    private $priv;
    

    public function _($data) {
        if ($this->parameterCheck($data) == false) {
            return array("code"=>"2");
        }
        if ($this->TokenCheck($data) == false) {
            return array("code"=>"0");
        }
		
        $param = new stdClass();
		$param->_group = 'Company';
        $param->_action= 'InfoGet';
        $param->_operator_id = $this->operatorId;
        $param->_user_id = $this->userId;
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