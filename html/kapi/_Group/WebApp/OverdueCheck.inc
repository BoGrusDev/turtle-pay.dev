<?php
/*
    OverdueCheckClass
    
   {
		"_group" : "WebApp",
		"_action" : "OverdueCheck",
		"_personal_id_number" : "195711040054"
	}	
*/

class OverdueCheckClass extends BaseClass {
    
    private $personalIdNumber;
	private $reply;

    public function _($data) {
        $this->reply = new stdClass();
		if ($this->parameterCheck($data) == false) {
			return array("code"=>"0");
		}
		$this->overdueCheck();

		return $this->reply;
	}

	private function parameterCheck($data) {
        if (isset($data->_personal_id_number)) {
			$this->personalIdNumber = trim($data->_personal_id_number);
		}
		else {
			return false;
		}
		return true;
	}

	public function overdueCheck() {
        // FIX and into blocked
		$sql = "SELECT people_status, overdue FROM people ";
		$sql .= "WHERE personal_id_number = '$this->personalIdNumber'";
		$reply = $this->_Get($sql);	
        if ($reply['code'] == '1') {
            if ($reply['overdue'] == '0') {
                $this->reply->code = '1';
            }
            else {
                $this->reply->code = '0';
            } 
        }
        else {
            // Person not exist in turtle pay, continue
            $this->reply->code = '1';
        }
	}
}