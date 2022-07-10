<?php
/*
    PrizeStatusUpdateClass
    
*/

class  PrizeStatusUpdateClass extends AjaxClass {

    private $token;
    private $userId;
    private $operatorId;
    private $priv;
    private $tdbEcoId; 
    private $tdAction;
    

    public function _($data) {
        if ($this->parameterCheck($data) == false) {
            return array("code"=>"0", "denide_code"=>"param-fail");
        }
        if ($this->TokenCheck($data) == false) {
            return array("code"=>"0", "denide_code"=>"token-fail");
        }
        $param = new stdClass();
		$param->_group = 'Tdb';
        $param->_action= 'PrizeStatusUpdate';
        $param->_tdb_eco_id = $this->tdbEcoId;
        $param->_tdb_action = $this->tdbAction;
        $param->_operator_id = $this->operatorId;
        $param->_user_id = $this->userId;
        //return $param;
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
        if (isset($data->_tdb_eco_id)) {
			$this->tdbEcoId = trim($data->_tdb_eco_id);
		}
		else {
			return false;
		}
        if (isset($data->_tdb_action)) {
			$this->tdbAction = trim($data->_tdb_action);
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