<?php
/*
    TdbCompetionClass
   	Get a list of all clsses for a special competion

    https://app.equipe.com/meetings/37076/competitions.json
    https://app.equipe.com/meetings/37076/competions.json

    prodOn means get from API else get from local file

    {
        "_group" : "Tdb",
        "_action" : "CompetionDetails",
        "_competion_id" : "37076",
       	"_user_id" : "69",
        "_operator_id" : "1"
    }

*/

require_once 'Group/Tdb/TdbBase.inc';

class TdbCompetionDetailsClass extends TdbBaseClass {

    private $userId;
    private $operatorId;
    private $tdbApikey;
	private $tdbOrgno;
	private $competionDetails;

    public function _($data) {
		if ($this->parameterCheck($data) == false) {
			return array("code"=>"0");
		}
		$this->apiResult = $this->_RestApiTdb('meetings/' . $this->tdbOrgno . '/competitions.json', $this->tdbApikey);
		if (is_array($this->apiResult) == false) {
			return array("code"=>"0");
		}

		$this->competionDetailsCreate();

		return $this->competionDetails;
	}

	private function parameterCheck($data) {
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

	private function competioncCreate() {
        
		
        $reply = array();
        for ($i=0; $i<sizeof($list); $i++) {
            $record = new stdClass();
            $record->comp_no = $list[$i]->kq;
            $record->klass = $list[$i]->klass;
            $record->datum = $list[$i]->datum;
            $record->anm = $list[$i]->anm;
			$record->sta = $list[$i]->sta;
			$record->anb = $list[$i]->anb;
			$record->stb = $list[$i]->stb;
			$record->eanma = $list[$i]->eanma;
			$record->eanmb = $list[$i]->eanmb;
			$record->clabb = $list[$i]->clabb;
            array_push($reply, $record);
        }

        return json_encode($reply);

	}
}