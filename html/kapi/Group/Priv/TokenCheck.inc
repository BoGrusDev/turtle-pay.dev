<?php
/*
    TokenCheckClass
    
    2022-01-31

    Check if token is valid and the return code = 1, 
        - operatorId 
        - list of company that operator has priv to
        - priv to slected userId (company)'
        - userId : same if operator has priv to t else returb as 0
        priv if its OK, 
    else return code = 0
   
    
    Called from Kundportal och service2, before all access to custpmer portal.

    This is the main security check, so all paramers are checked.

    execpt the public part.

    {
        "_group": "Priv",
        "_action": "TokenCheck",
        "_token": "E6170BB7CA5BA3D060BBDB6517C6E9DA",
        "_user_id" : "69"
    }
    Reply
    {
        "operator_id": "1",
        "priv": "pr",
        "code": "1"
    }
  
*/


class TokenCheckClass extends BaseClass {

    private $userId;
    private $token;
    private $cperatorId;
    private $priv;
    
    public function _($data) {
        
        $this->reply = new stdClass();
        if ($this->parameterCheck($data) == false) {
            return array("code"=>"0");
        }
        if ($this->tokenValidate() == false) {
            return array("code"=>"0");
        }
        
        // UserId 0 is private person
        if ($this->userId > 0) {
            if ($this->commanyPrivGet() == false) {
                return array("code"=>"0");
            }
        }
        $reply = new stdClass();
        $reply->code = '1';
        $reply->operator_id = $this->operatorId;
        if ($this->userId > 0) {
            $reply->priv = $this->priv;
        }
        return $reply;
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

    private function tokenValidate() {
    
        $sql = "SELECT t.people_id ";
        $sql .="FROM token t ";
        $sql .="WHERE t.token = '$this->token' AND ";
        $sql .="t.status = 'w' ";
        $this->res = $this->_get($sql);
        if ($this->res['code'] == "1") {
            $this->operatorId = $this->res['people_id'];
            return true;
        }
        else {
            return false;
        }        
    }

    private function commanyPrivGet() {
        /*
            Check if the operator has priv to the company (userId)
         */
        $sql = "SELECT priv ";
        $sql .= "FROM company_people ";
        $sql .= "WHERE people_id = " . $this->operatorId . " AND ";
        $sql .= " company_id = $this->userId";
        $res = $this->_Get($sql);
        if ($res['code'] == "1") {
            if ($res['priv'] == 'pe') {
                return false;
            }
            else {
                $this->priv = $res['priv'];
                return true;
            }
        }
        else {
            return false;
        }        
    }
}
