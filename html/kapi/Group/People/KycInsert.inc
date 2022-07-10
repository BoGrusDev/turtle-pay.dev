<?php
/*
   InfoGet

    Check if URL is a valid WebApp - URL connectd to a company, if so
    Return company_id, wa_store_id, wa_sp_id, wa_logo

    Called from index-tools.inc 

    {
        "_group" : "People",
        "_action" : "KycInsert",
        "people_id" : "1",
        "personal_id_number" : "195711040054", 
        "medborgare_sverige": "y",
        "medborgare_annat_land": "n",
        "medborgare_andra_lander": "",
        "skatt_annat_land": "n",
        "skatt_andra_lander": "",
        "sysselsattning": "2",
        "arbetsgivare": "Tele Bolaget",
        "pengarna_kommer_fran": "1",
        "pengarna_annat": "",
        "utlandska_medel": "n",
        "utlandska_kommer_fran": "",
        "pep" : "n"
    }

    ALTER TABLE `people` 
        ADD `kyc_id` INT NOT NULL DEFAULT '0' AFTER `kyc_need`, 
        ADD `kyc_date` DATE NULL DEFAULT NULL AFTER `kyc_id`; 

*/

class KycInsertClass extends BaseClass {

    private $peopleId;
    private $reply;
   
    public function _($data) {
        $this->reply = new stdClass();

        if ($this->parameterCheck($data) == false) {
            return array("code"=>"0");
        }
        $this->actionKycInsert($data);
        return $this->reply;
       
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

    private function actionKycInsert($data) {
        $data->kyc_date = date('Y-m-d');
		$this->reply = $this->_Insert("kyc", $data);
        
        if ($this->reply['code'] == '1') {
            $param = new stdClass();
            $param->kyc_need = 'n';
            $param->kyc_id = $this->reply['id'];
            $param->kyc_date = date('Y-m-d');
            //print_r($param);
            //echo $this->peopleId;
            $res = $this->_Update('people', 'people_id', $this->peopleId, $param);
            //print_r($res);
        }
	}
}

