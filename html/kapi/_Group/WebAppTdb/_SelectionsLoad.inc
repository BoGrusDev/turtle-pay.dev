<?php
/*
    SelectionsLoadLoadClass 
   	{
		"_group" : "WebAppTdb",
		"_action" : "SelectionsLoad",
		"_item_code" : "882E3A6B7B0DD6A1CF2A60F5F68C025D",
		"_user_id" : "69"
	}	
*/

class SelectionsLoadClass extends BaseClass {

	private $itemCode;
	private $reply;

    public function _($data) {

		// Check if all demand paramer exist
		if ($this->parameterCheck($data) == false) {
			return array("code"=>"0");
		}
	
        $this->selectionsLoad();

		return $this->reply;

	}

	private function parameterCheck($data) {
        if (isset($data->_item_code)) {
			$this->itemCode = trim($data->_item_code);
		}
		else {
			return false;
		}
		return true;
	}

	private function selectionsLoad() {
		$sql = "SELECT * FROM tdb_people WHERE item_code = '$this->itemCode'";
		$this->reply = $this->_Get($sql);
		
        if ($this->reply['code'] == '1' ) {
            $sql = "SELECT * FROM tdb_eco WHERE tdb_people_id = " . $this->reply['tdb_people_id'] . ' ORDER BY realrnr DESC, horse_num ';
		    $res = $this->_GetList($sql);
			// print_r($res); die('');
            $spec = array();
			$notComplet = array();
            $realrnrNumCurrent = 0;
			$horseNumCurrent = 0;
            $realrnrIndex = -1;
            for ($i=0; $i<sizeof($res); $i++) {
                //if (!$realrnrNumCurrent || $res[$i]['realrnr'] != $realrnrNumCurrent) {
				if ($res[$i]['realrnr'] == null) {
					array_push($notComplet, $i);
				}
				else { 
					if ($res[$i]['realrnr'] != $realrnrNumCurrent || $res[$i]['horse_num'] != $horseNumCurrent){
						$realrnrIndex++;
						$realrnrNumCurrent = $res[$i]['realrnr'];
						$horseNumCurrent = $res[$i]['horse_num'];
						$record = new stdClass();
						if ($res[$i]['name'] == null) {
							$record->name = $this->reply['name'];
							$record->first_name = '';
							$record->last_name = $this->reply['name'];
							$record->horse_name =  $res[$i]['horse_name'];;
							$record->horse_no = $res[$i]['horse_num'];
						}
						else {
							$record->name = $res[$i]['name'];
							$record->first_name = $res[$i]['first_name'];
							$record->last_name = $res[$i]['last_name'];
							$record->horse_name = $res[$i]['horse_name'];
							$record->horse_num = $res[$i]['horse_num'];
						}
						array_push($spec, $record);
						$spec[$realrnrIndex]->part = array();           
					}
					$precord = new stdClass();
					$precord->horse = $res[$i]['horse_name'];
					$precord->event_option_setting_id = $res[$i]['event_option_setting_id'];
					$precord->text = $res[$i]['text'];
					$precord->description = $res[$i]['description'];
					$precord->total = $res[$i]['total'];
					array_push($spec[$realrnrIndex]->part, $precord);
				}
            }  

			if (sizeof($notComplet)) {
				/*
					No realrnd
				*/
				for ($i=0; $i<sizeof($notComplet); $i++) {
					$found = false;
					$index = $notComplet[$i];
					if ($res[$index]['horse_num']) {
						/*
							No realrnd but hourse_num 
						*/
						for ($j=0; $j<sizeof($res); $j++) {
							if ($res[$index]['horse_num'] == $spec[$j]->horse_num) {
								$precord = new stdClass();
								$precord->horse = $res[$index]['horse_name'];;
								$precord->event_option_setting_id = $res[$index]['event_option_setting_id'];
								$precord->text = $res[$index]['text'];
								$precord->description = $res[$index]['description'];
								$precord->total = $res[$index]['total'];
								array_push($spec[$j]->part, $precord);
								$found = true;
								break;
							}
						}
					}
					if ($found == false) {
						/*
							No realrnd No hourse_num 
						*/					
						$record = new stdClass();
						if ($res[$index]['name'] == null) {
							$record->name = $this->reply['name'];
							$record->first_name = '';
							$record->last_name = $this->reply['name'];
							$record->horse_name =  '';
							//$record->horse_no = $res[$i]['horse_num'];
						}
						else {
							$record->name = $res[$index]['name'];
							$record->first_name = $res[$index]['first_name'];
							$record->last_name = $res[$index]['last_name'];
							$record->horse_name =  '';
							//$record->horse_num = $res[$i]['horse_num'];
						}  
						array_push($spec, $record);
						$realrnrIndex++;
						$spec[$realrnrIndex]->part = array();
						$precord = new stdClass();
						$precord->horse = ''; // $res[$index]['horse_name'];;
						$precord->event_option_setting_id = $res[$index]['event_option_setting_id'];
						$precord->text = $res[$index]['text'];
						$precord->description = $res[$index]['description'];
						$precord->total = $res[$index]['total'];
						array_push($spec[$realrnrIndex]->part, $precord);		
					}
				}
			}
            $this->reply['people']['spec'] = $spec;
        }
	}

	/*
    private function selectionsLoad() {
		$sql = "SELECT * FROM tdb_people WHERE item_code = '$this->itemCode'";
		$this->reply = $this->_Get($sql);
		
        if ($this->reply['code'] == '1' ) {
            $sql = "SELECT * FROM tdb_eco WHERE tdb_people_id = " . $this->reply['tdb_people_id'] . ' ORDER BY realrnr DESC, horse_num ';
		    $res = $this->_GetList($sql);

            $spec = array();
            $realrnrNumCurrent = 0;
			$horseNumCurrent = 0;
            $realrnrIndex = -1;
            for ($i=0; $i<sizeof($res); $i++) {
                //if (!$realrnrNumCurrent || $res[$i]['realrnr'] != $realrnrNumCurrent) {
				if ($res[$i]['realrnr'] != $realrnrNumCurrent || $res[$i]['horse_num'] != $horseNumCurrent){
                    $realrnrIndex++;
					$horseNumCurrent = $res[$i]['horse_num'];
                    $record = new stdClass();
					/ *
					if ($res[$i]['realrnr'] == null) {
						for ($k=0; $k<sizeof($spec); $k++) {
							if ($spec[$k]->horse_num == $horseNumCurrent) {
								$precord = new stdClass();
								$precord->horse = $spec[$k]->horse_name;;
								$precord->event_option_setting_id = $res[$i]['event_option_setting_id'];
								$precord->text = $res[$i]['text'];
								$precord->description = $res[$i]['description'];
								$precord->total = $res[$i]['total'];
								array_push($spec[$k]->part, $precord);
							}
						}
					}
					* /
				}
				
				/ *	
				if ($res[$i]['realrnr'] == null) {
					$record->name = $this->reply['name'];
					$record->first_name = '';
					$record->last_name = '';
					$record->horse_name = '';
				}
					else {
				* /
				$realrnrNumCurrent = $res[$i]['realrnr'];
				$record->name = $res[$i]['name'];
				$record->first_name = $res[$i]['first_name'];
				$record->last_name = $res[$i]['last_name'];
				$record->horse_name = $res[$i]['horse_name'];
				$record->horse_num = $res[$i]['horse_num'];
				$record->realrnr = $res[$i]['realrnr'];
					
				array_push($spec, $record);
				$spec[$realrnrIndex]->part = array();           
				$precord = new stdClass();
				$precord->horse = $res[$i]['horse_name'];
				$precord->event_option_setting_id = $res[$i]['event_option_setting_id'];
				$precord->text = $res[$i]['text'];
				$precord->description = $res[$i]['description'];
				$precord->total = $res[$i]['total'];
				array_push($spec[$realrnrIndex]->part, $precord);
				//print_r($spec);
				//die('');
			}
        }
		$this->reply['people']['spec'] = $spec;
	}
	*/
	/*
		private function selectionsLoad() {
			// Group by horses
			$sql = "SELECT * FROM tdb_people WHERE item_code = '$this->itemCode'";
			$this->reply = $this->_Get($sql);
			
			if ($this->reply['code'] == '1' ) {
				$sql = "SELECT * FROM tdb_eco WHERE tdb_people_id = " . $this->reply['tdb_people_id'] . ' ORDER BY horse_num, rnr';
				$res = $this->_GetList($sql);
				$spec = array();
				$horseNumCurrent = false;
				$horseIndex = -1;
				for ($i=0; $i<sizeof($res); $i++) {
					if (!$horseNumCurrent || $res[$i]['horse_num'] != $horseNumCurrent) {
						$horseIndex++;
						$horseNumCurrent = $res[$i]['horse_num'];
						$record = new stdClass();
						$record->horse_name = $res[$i]['horse_name'];
						array_push($spec, $record);
						$spec[$horseIndex]->part = array();           
					}
					$precord = new stdClass();
					$precord->name = $res[$i]['name'];
					$precord->description = $res[$i]['description'];
					$precord->total = $res[$i]['total'];
					array_push($spec[$horseIndex]->part, $precord);
				}  
				$this->reply['people']['spec'] = $spec;
			}
			
		}
	*/
}