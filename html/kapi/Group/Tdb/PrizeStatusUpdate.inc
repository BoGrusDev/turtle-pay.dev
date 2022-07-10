
<?php
/*
    PrizeStatusUpdate
	
	{
		"_group" : "Tdb",
		"_action" : "PrizeStatusUpdate",
        "_tdb_eco_id":3255,
        "_tdb_action":"priz"
		"_user_id" : "139",
        "_operator_id" : "1"
	}	

*/
require_once 'Group/Tdb/TdbBase.inc';

class  PrizeStatusUpdateClass extends TdbBaseClass {

    private $userId;
	private $operatorId;
    private $tdbEcoId; 
    private $tdAction;
   
    public function _($data) {

		if ($this->parameterCheck($data) == false) {
			return array("code"=>"0","denide_code"=>"param-fail");
		}

        if ($this->update() == false) {
            return array("code"=>"0", "denide_code"=>"update-fail");
        }
        
        $reply = new stdClass(); 
        $reply->code = '1';
        return $reply;
	}

	private function parameterCheck($data) {
		
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

    private function update() {
        $param = new stdClass();
        $param->action = $this->tdbAction;
        $this->_Update('tdb_eco', 'tdb_eco_id', $this->tdbEcoId, $param);        
        if ($ret['code'] = '1') {
            return true;
        }
        else {
            return false;
        }
    }

}