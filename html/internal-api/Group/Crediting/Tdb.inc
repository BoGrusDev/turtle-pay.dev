<?php
/*
	{
		"_group" : "Crediting",
		"_action" : "Tdb",
		"tdb_eco_ids" : [1]


	}

*/


class TdbClass extends CreditingBaseClass { 


    private $tdbEcoIds;
    
    
    public function _($data) {
        // Check if all demand paramer exist
        if ($this->parameterCheck($data) == false) {
            return array("code"=>"0");
        }

        //$this->peopleInfoFromSparGet();

        //return $this->peopleInfoFromSpar;
    }

	private function parameterCheck($data) {
		/*
			Check and set all parameter.
			If not exist and mandaty return false
		*/
		// Check API paramer
		if (isset($data->_personal_id_number)) {
			$this->personalIdNumber = trim($data->_personal_id_number);
		}
		else {
			return false;
		}
		return true;
	}

	
	private function participantAbondoned($data) {
		// -- Check who have done the paynets
		/*

			Parameters:
			$abValues - Change values // Vurrent values
			$abCvalues - Change values 
		*/

		// print_r($data); die('');

		$abIds = explode(',', $data->_ab_ids);
		$abCvalues = explode(',', $data->_ab_cvalues);
		
		$total = 0;
		for ($i=0; $i<sizeof($abCvalues); $i++) {
			$total = $total + $abCvalues[$i]; 
		}

		$creditCheck = json_decode($this->_CompanyCreditLimitCheck($data->_company_id, $total));

		if ($creditCheck->code == '1') {
			// OK 
		}
		else {
			return false;
		}

		// Get store id
		$sql = "SELECT wa_store_id FROM company WHERE company_id = $data->_company_id";
		$resStore = $this->_Get($sql);

		// $booking[] = new stdClass();
		$mailList = [];
		$index = -1;
		if (sizeof($abIds) > 0) {
			for ($i=0; $i<sizeof($abIds); $i++) {
				$sql = "SELECT i.people_id, i.people_name, e.base_event_id, i.event_item_id, i.credit_id ";
				$sql .= "FROM event_option o, event_item_v4 i, event_participant p, event_v4 e ";
				$sql .= "WHERE ";
				$sql .= "o.event_option_id = " . $abIds[$i] . " AND e.event_id = i.event_id AND ";
				$sql .= "o.event_participant_id = p.event_participant_id AND i.event_item_id = p.event_item_id";				
			
				$resPeople = $this->_Get($sql);

				$creditIsClosed = false;
				$allTo1380 = false;

				// Check  the Credit is closed
				$sql = "SELECT credit_status FROM credit WHERE credit_id = " . $resPeople['credit_id'];
				$resCredit = $this->_Get($sql);
				if ($resCredit['credit_status'] == 'c') {
					$creditIsClosed = true;
				}
				else { 
					// Check balance on credit
					$sql= "SELECT SUM(amount) AS balance FROM btrans ";
					$sql .= " WHERE account_no = '1380' AND prel IN ('n') AND credit_id = " .  $resPeople['credit_id'];
					$resBalance1380 = $this->_Get($sql);
					
					if ((float) $resBalance1380['balance'] >= (float) $abCvalues[$i]) {
						$allTo1380 = true;
					}
					else {
						$to1380 = (float) $abCvalues[$i] - (float) $resBalance1380['balance'];
						// $to1680 =  (float) $abCvalues[$i] - $to1380;

						//echo $resBalance1380['balance'] . ' : ' . $abCvalues[$i] . ' : ' . $to1380 . ' : ' . $to1680;
						//die('');
					}
				}

				$booking = new stdClass();

				$booking->people_id = $resPeople['people_id'];
				$booking->booking_date = date("Y-m-d"); // today
				$booking->booking_text = 'Credit';
				$booking->booking_type = 'pcreding';
				$booking->company_id = $data->_company_id;
				$booking->receipt_number = $resPeople['base_event_id'];
				$booking->sales_person_people_id = $data->_people_id;
				$booking->store_id = $resStore['wa_store_id'];
				$booking->_amount = $abCvalues[$i];
				$booking->credit_id = $resPeople['credit_id'];
				$booking->cr_id = '1';
		
				$booking->_trans = [];

				if ($creditIsClosed) {
					$booking->_trans[] = new stdClass();
					$booking->_trans[0]->trans_type  = 'pcredit';
					$booking->_trans[0]->account_no = '1380'; 
					$booking->_trans[0]->amount = -$booking->_amount;
					$booking->_trans[0]->people_id = $booking->people_id;
					$booking->_trans[0]->company_id = $booking->company_id;
					$booking->_trans[0]->credit_id = $resPeople['credit_id'];

					$booking->_trans[] = new stdClass();
					$booking->_trans[1]->trans_type  = 'pcredit';
					$booking->_trans[1]->account_no = '2981'; 
					$booking->_trans[1]->amount = $booking->_amount;
					$booking->_trans[1]->people_id = $booking->people_id;
					$booking->_trans[1]->company_id = $booking->company_id;
					$booking->_trans[1]->credit_id = $resPeople['credit_id'];

					$booking->_trans[] = new stdClass();
					$booking->_trans[2]->trans_type  = 'intern';
					$booking->_trans[2]->account_no = '1380'; 
					$booking->_trans[2]->amount = $booking->_amount; // new
					$booking->_trans[2]->people_id = $booking->people_id;
					// -- $booking->_trans[2]->company_id = $booking->company_id;
					$booking->_trans[2]->credit_id = $resPeople['credit_id'];

					$booking->_trans[3] = new stdClass();
					$booking->_trans[3]->trans_type  = 'intern';
					$booking->_trans[3]->account_no = '1680'; 
					$booking->_trans[3]->amount = -$booking->_amount; // new
					$booking->_trans[3]->people_id = $booking->people_id;
				
					$booking->_trans[3]->credit_id = $resPeople['credit_id'];

					// print_r($booking);
				}
				else 
				if ($allTo1380) {
					$booking->_trans[] = new stdClass();
					$booking->_trans[0]->trans_type  = 'pcredit';
					$booking->_trans[0]->account_no = '1380'; 
					$booking->_trans[0]->amount = -$booking->_amount;
					$booking->_trans[0]->people_id = $booking->people_id;
					$booking->_trans[0]->company_id = $booking->company_id;
					$booking->_trans[0]->credit_id = $resPeople['credit_id'];

					$booking->_trans[] = new stdClass();
					$booking->_trans[1]->trans_type  = 'pcredit';
					$booking->_trans[1]->account_no = '2981'; 
					$booking->_trans[1]->amount = $booking->_amount;
					$booking->_trans[1]->people_id = $booking->people_id;
					$booking->_trans[1]->company_id = $booking->company_id;
					$booking->_trans[1]->credit_id = $resPeople['credit_id'];
				}
				
				else {
					$booking->_trans[] = new stdClass();
					$booking->_trans[0]->trans_type  = 'pcredit';
					$booking->_trans[0]->account_no = '1380'; 
					$booking->_trans[0]->amount = -$booking->_amount;
					$booking->_trans[0]->people_id = $booking->people_id;
					$booking->_trans[0]->company_id = $booking->company_id;
					$booking->_trans[0]->credit_id = $resPeople['credit_id'];

					$booking->_trans[] = new stdClass();
					$booking->_trans[1]->trans_type  = 'pcredit';
					$booking->_trans[1]->account_no = '2981'; 
					$booking->_trans[1]->amount = $booking->_amount;
					$booking->_trans[1]->people_id = $booking->people_id;
					$booking->_trans[1]->company_id = $booking->company_id;
					$booking->_trans[1]->credit_id = $resPeople['credit_id'];

					$booking->_trans[] = new stdClass();
					$booking->_trans[2]->trans_type  = 'intern';
					$booking->_trans[2]->account_no = '1380'; 
					$booking->_trans[2]->amount = $to1380; // new
					$booking->_trans[2]->people_id = $booking->people_id;
					// -- $booking->_trans[2]->company_id = $booking->company_id;
					$booking->_trans[2]->credit_id = $resPeople['credit_id'];

					$booking->_trans[3] = new stdClass();
					$booking->_trans[3]->trans_type  = 'intern';
					$booking->_trans[3]->account_no = '1680'; 
					$booking->_trans[3]->amount = -$to1380; // new
					$booking->_trans[3]->people_id = $booking->people_id;
					$booking->_trans[3]->credit_id = $resPeople['credit_id'];

					// print_r($booking);
				}

				// print_r($booking); 
				$replyBooking = $this->_bookNew($booking);
				


				$mailExist = false;
				if (sizeof($mailList) > 0) {
					for ($j=0; $j<sizeof($mailList); $j++) {
						if ($mailList[$j] == $resPeople['people_id']) {
							$mailExist = true;
						}
					}
				}

				/*
				$mailExist = false;
				if (sizeof($mailList) > 0) {
					for ($j=0; $i<sizeof($mailList); $j++) {
						if ($mailList[$j] == $resPeople['people_id']) {
							$mailExist = true;
						}
					}
				}
				*/
				if ($mailExist == false) {
					array_push($mailList,$resPeople['people_id']);
				}

				//$param = new stdClass();
				//$param->_people_id = $resPeople['people_id'];
				//$param->_company_id = $data->_company_id;
				// Mail avisering
				// $this->actionMailNotification($param);
			}
		}
		
		// print_r($mailList);
		/*
		if (sizeof($mailList) > 0) {
			for ($j=0; $j<sizeof($mailList); $j++) {
				$param = new stdClass();
				$param->_people_id = $mailList[$j];
				$param->_company_id = $data->_company_id;
				$this->actionMailNotification($param);
				//print_r($param);
				//die('');
			}
		}
		*/

		if (sizeof($mailList) > 0) {
			for ($j=0; $j<sizeof($mailList); $j++) {
				$param = new stdClass();
				$param->_people_id = $mailList[$j];
				$param->_company_id = $data->_company_id;
				$this->actionMailNotification($param);
				//print_r($param);
				//die('');
			}
		}


		return true;
	}



