<?php
/*
*/

class KycInsertClass extends AjaxClass {

    private $token;
    private $userId;
    private $operatorId;
    private $priv;
    

    public function _($data) {
        if ($this->parameterCheck($data) == false) {
            return array("code"=>"0", "denide_code"=>"param-fail");
        }
        
        /*
        $param = new stdClass();
		$param->_group = 'Tdb';
        $param->_action= 'PrizeList';
        $param->_event_id = $this->eventId;
        $param->_operator_id = $this->operatorId;
        $param->_user_id = $this->userId;
        */
        //echo json_encode($param); die('');

		return $this->_RestApiCall($data);
    }

    private function parameterCheck($data) {		
        if (isset($data->people_id)) {
			$this->peopleId = trim($data->people_id);
		}
		else {
			return false;
		}
		return true;
	}

}