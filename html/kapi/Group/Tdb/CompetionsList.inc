<?php
/*
    TdbCompetionsListClass
    
   	Get the compentions for a organization and return all 
	that today day no expieer

	https://app.equipe.com/organizers/515/meetings.json

	prodOn means get from API else get from local file

	{
		"_group" : "Tdb",
		"_action" : "CompetionsList",
		"_tdb_orgno" : "515",
		"_user_id" : "69",
        "_operator_id" : "1"
	}	

*/
require_once 'Group/Tdb/TdbBase.inc';

class CompetionsListClass extends TdbBaseClass {

    private $userId;
	private $operatorId;
    private $tdbApikey;
	private $tdbOrgno;
	private $competionList;

    public function _($data) {

		// Check if all demand paramer exist
		if ($this->parameterCheck($data) == false) {
			return array("code"=>"0");
		}

		// echo 'organizers/' . $this->tdbOrgno . '/meetings.json', $this->tdbApikey; die('');

		// $this->today = date('Y-m-d');
		$this->today = '2021-10-01';

		$this->apiResult = $this->_RestApiTdb('organizers/' . $this->tdbOrgno . '/meetings.json', $this->tdbApikey);

		if (is_array($this->apiResult) == false) {
			return array("code"=>"0");
		}

		$this->competionsListCreate();

		return $this->competionList;
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
		$reply= $this->TdbSettingGet($this->userId);
		if ($reply['code'] != '1') {
			return false;
		}
		$this->tdbApikey = $reply['tdb_apikey'];
		$this->tdbOrgno = $reply['tdb_orgno'];
		return true;
	}

	private function competionsListCreate() {
		$this->competionList = array();
        for ($i=0; $i<sizeof($this->apiResult); $i++) {
            if (date($this->apiResult[$i]->starts_on) > $this->today) {
                $record = new stdClass();
                $record->id = $this->apiResult[$i]->id;
                $record->name = $this->apiResult[$i]->name;
                $record->start_on = $this->apiResult[$i]->starts_on;
                $record->ends_on = $this->apiResult[$i]->ends_on;
                array_push($this->competionList, $record);
            }
        }
	}
}