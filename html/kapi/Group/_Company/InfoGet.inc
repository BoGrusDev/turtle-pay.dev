<?php
/*
   InfoGet

    Check if URL is a valid WebApp - URL connectd to a company, if so
    Return company_id, wa_store_id, wa_sp_id, wa_logo

    Called from index-tools.inc 

    {
        "_group" : "Company",
        "_action" : "InfoGet",
        "_operator_id" : "1",
        "_user_id" : "69"
    }
*/

class InfoGetClass extends BaseClass {

    private $userId;
    private $operatorId;
    private $info;
   
    public function _($data) {
        // Check if all demand paramer exist
        if ($this->parameterCheck($data) == false) {
            return array("code"=>"0");
        }
        $this->infoGet();
        return $this->info;
    }

	private function parameterCheck($data) {
		
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

    private function infoGet() {
        $sql = "SELECT company_name, known_as, tdb_on, wa_store_id AS store_id, company_status FROM company ";
        $sql .= "WHERE company_id = '$this->userId' ";
        $this->info = $this->_Get($sql);
        return;
    }
}