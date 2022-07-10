<?php
/*
    SelectionsLoadLoadClass 
   	{
		"_group" : "WebAppTdb",
		"_action" : "ParticipantConnect",
		"_event_item_id" : "12466",
		"_user_id" : "134"
	}
*/

class ParticipantConnectClass extends BaseClass {

	private $eventItemId;
	
    public function _($data) {

		// Check if all demand paramer exist
		if ($this->parameterCheck($data) == false) {
			return array("code"=>"0");
		}
	
		if ($this->participantConnect() == false) {
            return array("code"=>"0","denied-code"=>"no-match");
        }
        $reply = new stdClass();
        $reply->code = "1";
		return $reply;
	}

	private function parameterCheck($data) {
        if (isset($data->_event_item_id)) {
			$this->eventItemId = trim($data->_event_item_id);
		}
		else {
			return false;
        }
		return true;
	}

	private function participantConnect() {
		$return = false;
		// Get all current participant id
		$sql = "SELECT event_participant_id FROM event_participant WHERE event_item_id = $this->eventItemId";
		$resPart = $this->_GetList($sql);
		// Loop  true  participant in new this order 
		for ($i=0; $i<sizeof($resPart); $i++) {
			// Get first tdb_eco_id
			$sql = "SELECT tdb_eco_id FROM event_option ";
			$sql .= "WHERE event_participant_id = " . $resPart[$i]['event_participant_id'];
			$sql .= " LIMIT 1";
			$resOption = $this->_Get($sql);
			// echo $resOption['tdb_eco_id']; die('');
			if ($resOption['code'] == '1') {
				$sql = "SELECT event_id, rnr, realrnr, horse_num, tdb_people_id FROM tdb_eco WHERE tdb_eco_id = " . $resOption['tdb_eco_id'];
				$resTdbEco = $this->_Get($sql);
				// find match before
				$sql = "SELECT e.tdb_eco_id, e.action, p.action FROM tdb_eco e, tdb_people p ";
				$sql .="WHERE e.event_id = " . $resTdbEco['event_id'];  
				$sql .=" AND e.rnr = " . $resTdbEco['rnr'];
				if ($resTdbEco['realrnr']) {
					$sql .=" AND e.realrnr = " . $resTdbEco['realrnr'];
				}
				if ($resTdbEco['horse_num']) {
					$sql .=" AND e.horse_num = " . $resTdbEco['horse_num'];
				}
				$sql .= " AND e.tdb_eco_id <> " . $resOption['tdb_eco_id'];
				$sql .= " AND e.action IN ('inv','crec')";
				$sql .= " AND p.tdb_people_id <> "  . $resTdbEco['tdb_people_id'];
				$sql .= " AND e.tdb_people_id = p.tdb_people_id ";
				$sql .= " ORDER BY e.tdb_eco_id LIMIT 1";
				/*
					SELECT e.tdb_eco_id, e.action, p.tdb_people_id, p.action FROM tdb_eco e, tdb_people p 
					WHERE e.event_id = 664 AND e.rnr = 35 AND e.realrnr = 35 AND e.horse_num = 15 
					AND e.tdb_people_id = p.tdb_people_id
					AND e.action IN ('inv', 'crex')  
					AND p.tdb_people_id <> 29
					ORDER BY e.tdb_eco_id;
					echo $sql; die('');
				*/
				$resPrev = $this->_Get($sql);
                if ($resPrev['code'] == '1') {
				    // $sql = "SELECT event_participant_id FROM event_option WHERE tdb_eco_id = " . $resPrev['tdb_eco_id'];
					$sql = "SELECT p.event_participant_id FROM event_option o, event_participant p, event_item_v4 i ";
					$sql .= "WHERE o.tdb_eco_id = " . $resPrev['tdb_eco_id'] . " AND i.event_item_status = 'c' ";
					$sql .= "AND p.event_participant_id = o.event_participant_id AND p.event_item_id = i.event_item_id ";
					$sql .= "ORDER BY i.event_item_id LIMIT 1 ";
				    $resParticipant = $this->_Get($sql);
				    // Update the base_participant to group it
					if ($resParticipant['code'] == '1') {
						$param = new stdClass();
						$param->base_participant_id = $resParticipant['event_participant_id'];
	
						$res = $this->_Update('event_participant', 'event_participant_id', $resPart[$i]['event_participant_id'], $param);
						if ($res['code'] == '1') {
							$return = true;
						}
					}
                }
			}
		}
        return $return;
	}
}