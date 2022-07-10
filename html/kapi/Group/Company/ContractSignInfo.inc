<?php
/*
    ContractSignInfo
    
    2022-04-36

    - Called from Service 
   
    {
        "_group": "Priv",
        "_action": "CompanyContractSignInfo",
        "_operator_id": "1",
        "_user_id" : "69"
    }

}

*/


class ContractSignInfoClass extends BaseClass {

    private $userId;
    private $operatorId;
    private $reply;

   
    public function _($data) {     
        
        if ($this->parameterCheck($data) == false) {
            return array("code"=>"0");
        }
        if ($this->personIsSuperUserCheck() == false) {
            return array("code"=>"0", "denied_code"=>"not-superuser");
        }
      
        $reply = new stdClass();
        $reply->code = '1';
        $reply->people_name = $this->peopleName;
        $reply->personal_id_number = $this->personalIdNumber;
        $reply->company_name = $this->companyName;
        return $reply;
    }

	private function parameterCheck($data) {
		/*
			Check and set all parameter.
			If not exist and mandatory return false
		*/
        if (isset($data->_operator_id)) {
			$this->operatorId = trim($data->_operator_id);
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

    private function personIsSuperUserCheck() {
		$sql = "SELECT c.company_name, p.personal_id_number, CONCAT(p.first_name, ' ', p.last_name) AS people_name ";
        $sql .= "FROM company_people cp, company c, people p ";
		$sql .= "WHERE cp.people_id = $this->operatorId AND ";
        $sql .= "cp.company_id = $this->userId AND ";
        $sql .= "cp.priv IN ('su') AND "; 
        $sql .= "cp.company_id = c.company_id AND ";
        $sql .= "c.company_id = $this->userId AND ";
        $sql .= "p.people_id = $this->operatorId ";
        $res = $this->_Get($sql);
        if ($res['code'] == '1') {
            $this->peopleName = $res['people_name'];
            $this->personalIdNumber = $res['personal_id_number'];
            $this->companyName = $res['company_name'];
            return true;
        }
        else {
            return false;
        }
    }

}