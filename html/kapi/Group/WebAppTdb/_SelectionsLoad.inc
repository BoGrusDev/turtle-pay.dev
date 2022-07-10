<?php
/*
    SelectionsLoadLoadClass 
   	{
		"_group" : "WebAppTdb",
		"_action" : "SelectionsLoad",
		"_item_code" : "74F4C04749F5AFAF148E7D3394A0DAC2",
		"_user_id" : "134"
	}

*/

class SelectionsLoadClass extends BaseClass {

	private $itemCode;
	private $reply;

    public function _($data) {

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
		
		// print_r($this->reply); die('');

        if ($this->reply['code'] == '1' ) {
            //$sql = "SELECT * FROM tdb_eco WHERE tdb_people_id = " . $this->reply['tdb_people_id'] . ' ORDER BY realrnr DESC, horse_num ';
			
			$sql = "SELECT * FROM tdb_eco WHERE tdb_people_id = " . $this->reply['tdb_people_id'];
			//$sql .= " AND fee_type IN ('entry', 'meeting') ";
			$sql .= " AND action = 'inv'";
			$sql .= "ORDER BY realrnr DESC, horse_num ";
			$res = $this->_GetList($sql);
			//print_r($res); die('');
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
							$record->horse_num = $res[$i]['horse_num'];
						
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
					$precord->tdb_eco_id = $res[$i]['tdb_eco_id']; // Added
					array_push($spec[$realrnrIndex]->part, $precord);
				}
            }  

			if (sizeof($notComplet) > 0) {
				/*
					No realrnd
				*/
				for ($i=0; $i<sizeof($notComplet); $i++) {
					$found = false;
					$index = $notComplet[$i];
					if ($res[$index]['horse_num'] AND sizeof($spec) > 0) {
						/*
							No realrnd but hourse_num 
						*/
						if (sizeof($spec) > 0 ) {
							for ($j=0; $j<sizeof($spec); $j++) {
								//print_r($res[$index]);
								//print_r($spec[$j]); die('');
								if ($res[$index]['horse_num'] == $spec[$j]->horse_num) {
									$precord = new stdClass();
									$precord->horse = $res[$index]['horse_name'];;
									$precord->event_option_setting_id = $res[$index]['event_option_setting_id'];
									$precord->text = $res[$index]['text'];
									$precord->description = $res[$index]['description'];
									$precord->total = $res[$index]['total'];
									$precord->tdb_eco_id = $res[$index]['tdb_eco_id']; // Added
									array_push($spec[$j]->part, $precord);
									$found = true;
									break;
								}
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
						$precord->tdb_eco_id = $res[$index]['tdb_eco_id']; // Added
						array_push($spec[$realrnrIndex]->part, $precord);		
					}
				}
			}
            $this->reply['people']['spec'] = $spec;
        }
	}

	/*
	private function participantConnect($eventItemId) {
		// Get all current participant id
		$sql = "SELECT event_participant_id FROM event_participant WHERE event_item_id = $eventItemId";
		$resPart = $this->_GetList($sql);
		print_r($resPart);
		// Loop  true  participant in new this order 
		for ($i=0; $i<sizeof($resPart); $i++) {
			// Get first tdb_eco_id
			$sql = "SELECT tdb_eco_id FROM event_option ";
			$sql .= "WHERE event_participant_id = " . $resPart[$i]['event_participant_id'];
			$sql .= " ORDER BY event_option_id"; // LIMIT 1";
			$resOption = $this->_Get($sql);
			print_r($resOption);
			//die('');
			if ($resOption['code'] == '1') {
				$sql = "SELECT event_id, rnr, realrnr, horse_num FROM tdb_eco WHERE tdb_eco_id = " . $resOption['tdb_eco_id'];
				$resTdbEco = $this->_Get($sql);
				print_r($resTdbEco);
				
				// find match before
				$sql = "SELECT tdb_eco_id FROM tdb_eco ";
				$sql .="WHERE event_id = " . $resTdbEco['event_id'];  
				$sql .=" AND rnr = " . $resTdbEco['rnr'];
				$sql .=" AND realrnr = " . $resTdbEco['realrnr'];
				$sql .=" AND horse_num = " . $resTdbEco['horse_num'];
				$sql .= "  ORDER BY tdb_eco_id LIMIT 1";
				
				$resPrev = $this->_Get($sql);
				print_r($resPrev);
				// 
				//die('');

				$sql = "SELECT event_participant_id FROM event_option WHERE tdb_eco_id = " . $resPrev['tdb_eco_id'];
				$resParticipant = $this->_Get($sql);
				// Update the base_participant to group it
				$param = new stdClass();
				$param->base_participant_id = $resParticipant['event_participant_id'];
				// Updatera bas id 
				$res = $this->_Update('event_participant', 'event_participant_id', $resPart[$i]['event_participant_id'], $param);
				print_r($res);
				print_r($param);
			}
		}
	}
	*/
}