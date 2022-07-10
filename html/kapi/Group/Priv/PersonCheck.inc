<?php
/*
    PersonCheckClass
    
    2022-01-31

    Check if token is valid and the return code = 1, 
        - operatorId 
        - list of company that operator has priv to
        - priv to slected userId (company)'
        - userId : same if operator has priv to t else returb as 0
        priv if its OK, 
    else return code = 0
   
    
    Called from Kundportal och index.php, is called in the preprocess, not from the JavaScript

    This is the security check every time a papage is vccalled in the kundportal.

    {
        "_group": "Priv",
        "_action": "PersonCheck",
        "_token": "E6170BB7CA5BA3D060BBDB6517C6E9DA",
        "_user_id" : "69"
    }

    Reply:
    {
    "operatorId": "1",
    "name": "Bo Erik Grusell",
    "company_name": "Test Bolaget",
    "has_invoice_service": "y",
    "has_bo": "y",
    "known_as": "Test Bolaget",
    "has_sie": "y",
    "tdb_on": "y",
    "priv_on": "n",
    "priv": "pr",
    "list": [
        {
            "company_id": "92",
            "known_as": "Brolöten Dressyrcentrum"
        },
        {
            "company_id": "13",
            "known_as": "Djurgårdens ridskola"
        },
        {
            "company_id": "69",
            "known_as": "Test Bolaget"
        }
    ],
    "code": "1",
    "user_id": "69",
    "token": "E6170BB7CA5BA3D060BBDB6517C6E9DA"
}

*/


class PersonCheckClass extends BaseClass {

    private $userId;
    private $token;
    private $cperatorId;
    private $reply;
   
    public function _($data) {     
        $this->reply = new stdClass();
        if ($this->parameterCheck($data) == false) {
            return array("code"=>"0");
        }
        if ($this->tokenValidate() == false) {
            return array("code"=>"0");
        }
      
        if ($this->userId > 0) {
            $this->userSelectedInfo();
        }
        
        $this->privList();
        $this->reply->code = '1';
        $this->reply->user_id = $this->userId;
        $this->reply->token = $this->token;
        return $this->reply;
    }

	private function parameterCheck($data) {
		/*
			Check and set all parameter.
			If not exist and mandatory return false
		*/
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
    
        $sql = "SELECT t.people_id,  p.first_name, p.last_name ";
        $sql .="FROM token t, people p ";
        $sql .="WHERE t.token = '$this->token' AND ";
        $sql .="t.status = 'w' AND ";
        $sql .="t.people_id = p.people_id";
        $result = $this->_get($sql);
        if ($result['code'] == "1") {
            $this->reply->operatorId = $result['people_id'];
            $this->reply->name = $result['first_name'] . ' ' . $result['last_name'];
            return true;
        }
        else {
            return false;
        }        
    }

    private function userSelectedInfo() {
        $sql = "SELECT c.company_id, c.known_as, c.wa_url, c.has_invoice_service, c.has_bo, c.has_sie, cp.priv, ";
        $sql .= "tdb_on, priv_on ";
        $sql .= "FROM company_people cp, company c ";
        $sql .= "WHERE cp.people_id = " . $this->reply->operatorId . " AND ";
        $sql .= "cp.company_id = $this->userId AND ";
        $sql .= "cp.priv IN ('su','ac','pr') AND "; 
        $sql .= "cp.company_id = c.company_id ";
        $result = $this->_Get($sql);
        if ($result['code'] == '1') {
            $this->reply->company_name = $result['known_as'];
            $this->reply->has_invoice_service = $result['has_invoice_service'];
            $this->reply->has_bo = $result['has_bo'];
            //$this->reply->allowedUser = true;
            $this->reply->known_as = $result['known_as'];
            $this->reply->has_sie = $result['has_sie'];
            $this->reply->tdb_on = $result['tdb_on'];
            $this->reply->priv_on = $result['priv_on'];
            $this->reply->priv = $result['priv'];
        }
        else {
            // Operator has no privlgige for this User (company)
            // set userId = 0 thas is operators provate acccount part
            $this->userId = 0;
        }
        return;
    }

    private function privList() {
		$sql = "SELECT c.company_id, c.known_as ";
        $sql .= "FROM company_people cp, company c ";
		$sql .= "WHERE cp.people_id = " . $this->reply->operatorId . " AND ";
        $sql .= "cp.priv IN ('su','ac','pr') AND "; 
        $sql .= "cp.company_id = c.company_id ";
		$sql .= "ORDER BY c.known_as ";
		$this->reply->list = $this->_GetList($sql);
        return;
    }

}