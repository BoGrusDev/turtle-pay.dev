
<?php
/*
    PrivAddClass
    
    Adde priviliges for a person
    Only superuser has permission
    In the PrivList, does not show pe or su
    If they are set as new, they will insead be updated.

    External: AAPI

	{
		"_group" : "Priv",
		"_action" : "Add",
		"_user_id" : "69",
        "_operator_id" : "1",
        "_personal_id_number" : "199507134709",
        "priv" : "pe"
	}	

*/
require_once 'Group/Priv/PrivBase.inc';

class AddClass extends PrivBaseClass {

    private $userId;
    private $operatorId;
    private $peopleId;
    private $personalIdNumber;
	private $priv;
    private $cpId;


    public function _($data) {
        // -- Check if all demand paramer exist
        if ($this->parameterCheck($data) == false) {
            return array("code"=>"0");
        }
        // -- Check if person exist in Turtle Pay
        if ($this->peopleInTurtlePayGet() == false) {
            // -- Get people from SPAR and insert it to Trtle Pay
             if ($this->peopleGetfromSpar() == false) {
                // -- Person not exist in SPAr or Sekretes marked
                return array("code"=>"0", "denied_code"=>"people_not_exist");
            }
        }      
        if ($this->peopleInserPriv() == false) {
            return array("code"=>"0", "denied_code"=>"add-fail");
        }
        $reply = new stdClass();
        $reply->cp_id = $this->cpId;
        $reply->code = '1';
        return $reply; 
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
        if (isset($data->_personal_id_number)) {
			$this->personalIdNumber = trim($data->_personal_id_number);
		}
		else {
			return false;
		}

        if (isset($data->priv)) {
			$this->priv = trim($data->priv);
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

    
    private function peopleInTurtlePayGet() {
        /*
            Get the person for Turtle Pay database
        */
        // Check if person exist
		$sql = "SELECT people_id, CONCAT(first_name, ' ', last_name) AS people_name FROM people WHERE personal_id_number = '$this->personalIdNumber'";
		$res = $this->_Get($sql);
        if ($res['code'] == '1') {
            $this->peopleId = $res['people_id'];
            return true;
        }
        else {
            return false;
        }
    }

	private function peopleGetfromSpar() {
        /*
            Get people form SPAR
            If exist insert to Turle Pay database and 
            set $this->peopleId and return true else false
        */
        $param = new stdClass();
        $param->_group = "Spar";
        $param->_action = "Collect";
        $param->_personal_id_number = $this->personalIdNumber;

        $result = $this->_RestApiCall($param, INTERNAL_API);
        if($result->code == "0") {
            return false;
		} else {
            // -- Insert into Rurtle Pay
            $result->people->people_status = 'p';
            $reply = $this->_Insert('people', $result->people);
            if ($reply['code'] == "1") {
                $this->peopleId = $reply['id'];
                return true;
            } else {
                return false;
            }
        }
	}

    private function peopleInserPriv() {

        // Check if exist and are removed
        $sql = "SELECT cp_id FROM company_people WHERE company_id = $this->userId AND people_id = $this->peopleId";
        $res = $this->_Get($sql);
        if ($res['code'] == '1') {
            $this->cpId = $res['cp_id'];
            // Gas connection before
            $sql = "UPDATE company_people SET priv = '$this->priv' WHERE cp_id = $this->cpId";
		    $resUpdate  =  $this->_Query($sql);
		    return true;
        }
        else {
            $param = new stdClass();
            $param->company_id = $this->userId;
            $param->people_id  = $this->peopleId;
            $param->personal_id_number = $this->personalIdNumber;
            $param->priv = $this->priv;
            $reply = $this->_Insert('company_people', $param);
            if ($reply['code'] == "1") {
                $this->cpId = $reply['id']; 
                return true;
            }
            else {
                return false;
            }
        }
    }
    
}