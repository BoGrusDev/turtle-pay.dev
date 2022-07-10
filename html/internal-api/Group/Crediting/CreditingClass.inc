<?php

class CreditingBaseClass extends InternalBaseClass {


	protected function bookingCrediting() {
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

			$replyBooking = $this->_bookNew($booking);
	
	}


	/*
		public function TdbSettingGet($userId) {
			$sql = "SELECT tdb_apikey, tdb_orgno FROM company WHERE company_id=$userId AND tdb_on = 'y'";
			$reply = $this->_Get($sql);
			return $reply;
		}
	*/

	/*
		public function _RestApiTdb($param, $apiKey) {	
			$apiKeyName = 'X-API-KEY';
			$tdbUrl = 'https://app.equipe.com/';
			$curl = curl_init($tdbUrl . $param);
			curl_setopt($curl, CURLOPT_RETURNTRANSFER, 1);
			curl_setopt($curl,CURLOPT_SSL_VERIFYPEER, false);
			curl_setopt($curl, CURLOPT_HTTPHEADER, array(
				"$apiKeyName : $apiKey"
			));
			$result = curl_exec($curl);
			if (curl_errno($curl)) {
				$error_msg = curl_error($curl);
				print_r($error_msg);
				die('stop');
			}
			
			curl_close($curl);
			return json_decode($result);
		}
	*/


}
