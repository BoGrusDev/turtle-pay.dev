
<?php
/*
    ListClass
    
   	Get the compentions for a organization and return all 
	that today day no expieer

	https://app.equipe.com/organizers/515/meetings.json

	prodOn means get from API else get from local file

	{
		"_group" : "Priv",
		"_action" : "List",
		"_user_id" : "69",
        "_operator_id" : "1"
	}	

*/
require_once 'Group/Priv/PrivBase.inc';

class ListClass extends PrivBaseClass {

    private $userId;
    private $operatorId;
    private $peopleList;

    public function _($data) {
        // Check if all demand paramer exist
        if ($this->parameterCheck($data) == false) {
            return array("code"=>"0");
        }

        $this->peopleListCreate();
        return $this->peopleList;
    }

	private function parameterCheck($data) {
		/*
			Check and set all parameter.
			If not exist and mandaty return false
		*/
		
		// Check API paramer
		if (isset($data->_user_id)) {
			$this->userId = trim($data->_user_id);
		}
		else {
			return false;
		}

        if (isset($data->_operator_id)) {
			$this->operatorId = trim($data->_operator_id);
		}
		else {
			return false;
		}

		$reply= $this->superUserCheck($this->userId, $this->operatorId);
		if ($reply['code'] != '1') {
			return false;
		}
		
		return true;

	}

	private function peopleListCreate() {
		$sql = "SELECT cp.cp_id, cp.people_id, cp.personal_id_number, cp.priv, CONCAT(p.first_name, ' ', p.last_name) AS people_name ";
		$sql .= "FROM company_people cp, company c, people p ";
		$sql .= "WHERE cp.company_id = $this->userId AND ";
		$sql .= "cp.priv IN ('ac','pr','sp') AND ";
		$sql .= "cp.people_id = p.people_id AND ";
		$sql .= "cp.company_id = c.company_id";
		$this->peopleList = $this->_GetList($sql);
	}

}