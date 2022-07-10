 <?php
/*
	This class will handle all Booking 

	* PayIn() - Process from the Control Panel 
		- validatePayInParameters()
		- 1 - Ocrno (Credit)
		- prepareCreditIn()
		- bookingCreate()
		- transCreditInCreate()

			 
 		- 2 - Ocrno (People)
		 - 3 - Ocrno - Bond
		 

	## CreditNew
	All new credit

	## PeoplePayIn
	Pay into a cr

	## VendorPayOut

	## EventCrediting
 
*/

$includes = 'Db,Ocrno,Balances,Validate';

class Booking {

	public function __construct($package) {
        // 
        // Ladda package
        //
		foreach ($package as $key => $value) {
			$this->$key = $value;
		}
	}

    public function Run($data) {
		$actionMethod = 'action' . $data->_action;
		echo $this->$actionMethod($data);
    }

	private function actionTest($data) {
		echo 'inside';
    }

	private function actionPayIn($data) {
		/*
			All payin is done from CP or later automatic.
			A payin can com in for a:
				- Credit ocrno start with 1
				- People ocrno start width 2
				- Bond ocrno start width 3
		
			{
				"_key" : "test-key",
				"_group" : "Booking",
				"_action" : "PayIn",
				"booking_date" : "2020-10-15",
				"ocrno" : "123444109680",
				"amount" : "2000"
			}				
		*/

		$data->amount = (float) $data->amount;

		$reply = new stdClass();
		$resValidateParameters = $this->validatePayInParameters($data);
		if ($resValidateParameters->code == '0') {
			return json_encode($resValidateParameters);
		}

		$payInOcrCode = substr($data->ocrno , 0, 1);

		// --
		// OCR pay into Credit direct
		// --
		if ($payInOcrCode == "1") {
			// 
			// Check if ocrno exits in first and credit id
			//
			$sql = "SELECT people_id, credit_id FROM first_invoice WHERE ocrno = '$data->ocrno'";
			$replyFirstInvoice = $this->Db->_Get($sql);

			if ($replyFirstInvoice->code != '1') {
				$reply->code = '0';
				$reply->denied_code = 'ocrno_not_exist';
				return json_encode($reply);
			};
			
			$preparedData = $this->prepareCreditIn($replyFirstInvoice->credit_id, $data->amount, $data->booking_date, $replyFirstInvoice->people_id);
			$preparedData->ocrno = $data->ocrno;
			// -- Create the Booking (head)
			$booking = $this->bookingCreate($preparedData, 'Customer payment','cust-pmt');
			// -- Create transaction array
			$booking->_trans = array();
			// -- 
			// -- Create trans Book the Payin to (1380)
			// --
		
			$booking->_trans = $this->transCreditInCreate($booking->_trans, $preparedData->peopleId, $preparedData->creditId, $preparedData->amount, 'cust-pmt');

			if ($preparedData->creditStatus == 'c' || $preparedData->creditStatus == 'r')  {
				// (1) Transfer amount to 1680
				$booking->_trans = $this->transInternCreate($booking->_trans, $preparedData->peopleId, $preparedData->creditId, $preparedData->amount, 'intern'); 
			}
			else if ($preparedData->isOverDue == 'y')  {
				// (2) Transfer amount to 1680
				$booking->_trans = $this->transInternCreate($booking->_trans, $preparedData->peopleId, $preparedData->creditId, $preparedData->amount, 'intern'); 
			}
			else if ($preparedData->creditStatus == 'p') {
				// (3) Paid to P invoice
				if ($preparedData->isOverDueFirstInvoice == 'y') {
					// (3.1) Pay after due date, chaage status to a
					$this->creditStatusSet($preparedData->creditId, 'a');
				}
				else if ($preparedData->isOverPaid == 'y')  {
					// (3.2) Paid in time full, set Credit status "c";
					$booking->_trans = $this->transInternCreate($booking->_trans, $preparedData->peopleId, $preparedData->creditId, $preparedData->overPaidAmount, 'intern'); 
					$this->creditStatusSet($preparedData->creditId, 'c');
				}
				else if ($preparedData->isFullyPaid == 'y')  {
					// (3.3) Paid in time full, set Credit status "c";
					$this->creditStatusSet($preparedData->creditId, 'c');
				}
				else {
					// 3.4 Paid but not full credit
					$this->creditStatusSet($preparedData->creditId, 'a');
				}
			}
			else if ($preparedData->creditStatus == 'o' || $preparedData->creditStatus == 'a')  {
				// (4) This would include status "o" status "a"
			}
			else {
				die('Could not happend');
			}
			
		}
		else if ($payInOcrCode == "2") {
			$sql = "SELECT people_id FROM people WHERE ocrno = '" . $data->ocrno . "'";
			$replyPeople = $this->Db->_Get($sql);
			$replyPeople = $this->Db->_Get($sql);
			if ($replyPeople->code != '1') {
				$reply->code = '0';
				$reply->denied_code = 'ocrno_not_exist';
				return json_encode($reply);
			};
			$preparedData = $this->preparePeopleIn($replyPeople->people_id, $data->amount, $data->booking_date);
			$preparedData->ocrno = $data->ocrno;
			// -- Create the Booking (head)
			$booking = $this->bookingCreate($preparedData, 'Customer payment', 'cust-pmt');
			// -- Create transaction array
			$booking->_trans = array();
			// -- 
			// -- Create trans Book the Payin to (1680)
			// --
			$booking->_trans = $this->transPeopleInCreate($booking->_trans, $preparedData->peopleId, $preparedData->amount, 'cust-pmt');
		}	
		else if ($payInOcrCode == "3") {
			// 
			// Check if ocrno exits in first and credit id
			//
			$sql = "SELECT people_id, bond_id, bond_status FROM bond WHERE ocrno = '$data->ocrno'";
		
			$replyBond= $this->Db->_Get($sql);
			if ($replyBond->code != '1') {
				$reply->code = '0';
				$reply->denied_code = 'ocrno_not_exist';
				return json_encode($reply);
			};
			
			$preparedData = $this->prepareBondIn($replyBond->bond_id, $data->amount, $data->booking_date, $replyBond->people_id, $replyBond->bond_status);
			$preparedData->ocrno = $data->ocrno;
			// -- Create the Booking (head)
			$booking = $this->bookingCreate($preparedData, 'Bond payment','bond-pmt');
			// -- Create transaction array
			$booking->_trans = array();
			// -- 
			// -- Create trans Book the Payin to (1380)
			// --
			$booking->_trans = $this->transBondInCreate($booking->_trans, $preparedData->peopleId, $preparedData->bondId, $preparedData->amount, 'bond-pmt');
		}
		else if ($payInOcrCode == "4") {
			// 
			// Check if ocrno exits in first and credit id
			// - TransCreditIN - fixa
			//
			$sql = "SELECT company_id FROM company WHERE ocrno = '$data->ocrno'";
		
			$replyCompany = $this->Db->_Get($sql);
			if ($replyCompany->code != '1') {
				$reply->code = '0';
				$reply->denied_code = 'ocrno_not_exist';
				return json_encode($reply);
			};
			
			$preparedData = $this->prepareCompanyIn($replyCompany->company_id, $data->amount, $data->booking_date);
			$preparedData->ocrno = $data->ocrno;
			// -- Create the Booking (head)
			$booking = $this->bookingCreate($preparedData, 'Company pmt','comp-pmt');
			// -- Create transaction array
			$booking->_trans = array();
			// -- 
			// -- Create trans Book the Payin to (1380)
			// --
			$booking->_trans = $this->transCompanyInCreate($booking->_trans, $preparedData->companyId, $preparedData->amount, 'comp-pmt');
		
			//print_r($data);
			//print_r($replyCompany);
			//print_r($preparedData);
		}

		//print_r($booking); die('');

		$this->bookTransactions($booking);
		
		// Check and set overdue
		if ($payInOcrCode == "1") {
			$this->checkOverdueAfterBooking($preparedData->peopleId, $data->_booking_date);
		}
		
		$reply->code = '1';
		return json_encode($reply);

	}

	private function actionCreditOverPayed($data) {
		// called for settlement
		/*
		{
			"_key" : "test-key",
			"_group" : "Booking",
			"_action" : "CreditOverPayed",
			"booking_date" : "2020-12-03",
			"people_id" : "1164",
			"credit_id" : "12344412845",
			"amount" : "62"
		}	
		*/
		
		// print_r($data); 

		// remove - first char 
		$reply = new stdClass();
		$preparedData = new stdClass();
		$preparedData->peopleId = $data->people_id;
		$preparedData->creditId = $data->credit_id;
		$preparedData->bookingDate = $data->booking_date;
		$preparedData->amount = $data->amount;

		$booking = $this->bookingCreate($preparedData, 'Settlement','m-settl');	
		$booking->_trans = array();

		$booking->_trans = $this->transInternCreate($booking->_trans, $preparedData->peopleId, $preparedData->creditId, $preparedData->amount, 'intern'); 

		// $this->creditStatusSet($preparedData->creditId, 'c');
		
		// print_r($preparedData);
		// print_r($booking);

		//die('');
		
		$this->bookTransactions($booking);
		$reply->code = '1';
		return json_encode($reply);



	}

	private function actionCreditingInterest($data) {
		/*
			Crediting of Interest from to CP
			
			{
				"_key" : "test-key",
				"_group" : "Booking",
				"_action" : "CreditingInterest",
				"booking_date" : "2020-10-15",
				"credit_id" : "12344413165",
				"people_id" : "1",
				"amount" : "6"
			}			
			
			after: prepareCredit
				[creditId] => 12344413165
				[peopleId] => 1
				[amount] => 6
				[bookingDate] => 2020-10-15
				[creditBalance] => 777.00
				[peopleBalance] => 7067.00
				[overDueBalance] => 0.00
				[isOverDue] => n
				[creditStatus] => o
				[creditOcrno] => 123444131650
		*/

		$reply = new stdClass();
		
		$preparedData = $this->prepareCreditIn($data->credit_id, $data->amount, $data->booking_date, $data->people_id);
		// -- Create the Booking (head)

		// print_r($preparedData); 

		$booking = $this->bookingCreate($preparedData, 'Crediting','crediting');
		// -- Create transaction array
		$booking->_trans = array();
		
		$booking->_trans = $this->transCreditingInterest($booking->_trans, $preparedData->peopleId, $preparedData->creditId, $preparedData->amount, 'crediting') ;
		
		if ($preparedData->creditStatus == 'c' || $preparedData->creditStatus == 'r')  {
			// (1) Transfer amount to 1680
			$booking->_trans = $this->transInternCreate($booking->_trans, $preparedData->peopleId, $preparedData->creditId, $preparedData->amount, 'intern'); 
		}
		else if ($preparedData->isOverDue == 'y')  {
			// (2) Transfer amount to 1680
			$booking->_trans = $this->transInternCreate($booking->_trans, $preparedData->peopleId, $preparedData->creditId, $preparedData->amount, 'intern'); 
		}
		
		//print_r($booking); 
		//die('');

		$this->bookTransactions($booking);
		$reply->code = '1';
		return json_encode($reply);

	}

	private function actionCreditingCredit($data) {
		/*
			Crediting of Interest from to CP
			
		*/

		$reply = new stdClass();
		
		$preparedData = $this->prepareCreditIn($data->credit_id, $data->amount, $data->booking_date, $data->people_id);
		// -- Create the Booking (head)

		$preparedData->companyId = $data->company_id;
		// print_r($preparedData); 

		$booking = $this->bookingCreate($preparedData, 'Crediting','crediting');
		// -- Create transaction array
		$booking->_trans = array();
		
		$booking->_trans = $this->transCreditingCredit($booking->_trans, $preparedData->peopleId, $preparedData->creditId, $data->company_id, $preparedData->amount, 'crediting') ;
		
		if ($preparedData->creditStatus == 'c' || $preparedData->creditStatus == 'r')  {
			// (1) Transfer amount to 1680
			$booking->_trans = $this->transInternCreate($booking->_trans, $preparedData->peopleId, $preparedData->creditId, $preparedData->amount, 'intern'); 
		}
		else if ($preparedData->isOverDue == 'y')  {
			// (2) Transfer amount to 1680
			$booking->_trans = $this->transInternCreate($booking->_trans, $preparedData->peopleId, $preparedData->creditId, $preparedData->amount, 'intern'); 
		}
		
		// print_r($booking); 
		// die('');

		$this->bookTransactions($booking);
		$reply->code = '1';
		return json_encode($reply);

	}

	private function actionCreditingPeople($data) {
		/*

			Crediting of people from to CP (account 1680)
			billing-fee (3543)
			reminder-fee (3544)
			collection-fee (3542)
			ointrest (8301) (people line 483)
			
			The call from people.class, need be update one day,
			the $data->trans array should ne removed and simplified

		*/

		$reply = new stdClass();
		
		$preparedData = $this->preparePeopleIn($data->people_id, $data->amount, $data->booking_date);
		// -- Create the Booking (head)
		$booking = $this->bookingCreate($preparedData, 'Crediting', 'crediting');
		// -- Create transaction array
		$booking->_trans = array();
		// -- 
		// -- Create trans Book the Payin to (1680)
		// --
		switch ($data->type) {
			case 'billing-fee' :
				$accountNo = '3543';
				break;
			case 'reminder-fee' :
				$accountNo = '3544';
				break;
			case 'collection-fee' :
				$accountNo = '3542';
				break;
			case 'o-interest' :
				$accountNo = '8301';
				break;
			default :
				$reply->code = '0';
				$reply->denied_code = 'wrong_type';
				return json_encode($reply);
				die('');
		}
			
		$booking->_trans = $this->transCreditingPeopleCreate($booking->_trans, $preparedData->peopleId, $preparedData->amount, $accountNo, 'crediting');


		// print_r($booking); 
		// die('');

		$this->bookTransactions($booking);
		$reply->code = '1';
		return json_encode($reply);

	}

	private function validatePayInParameters($data) {

		$reply = new stdClass();
		if (!isset($data->ocrno)) {
			$reply->code = '0';
			$reply->denied_code = 'param_ocrno_not_set';
			return $reply;
		}
		else if (!isset($data->booking_date)) {
			$reply->code = '0';
			$reply->denied_code = 'booking_date_not_set';
			return $reply;
		}
		else if (!is_numeric($data->amount)) {
			$reply->code = '0';
			$reply->denied_code = 'amount_not_valid';
			return $reply;
		}
		else if ($this->Validate->dateFormat($data->booking_date) == false) {
			$reply->code = '0';
			$reply->denied_code = 'booking_date_not_valid';
			return $reply;
		}
		else if (is_numeric($data->amount) == false) {
			$reply->code = '0';
			$reply->denied_code = 'amount_not_valid';
			return $reply;
		}

		// Check the forst ocr

		// All parameters är OK 
		else {
			$reply->code = '1';
		
			return $reply;
		}
	}

	private function prepareCreditIn($creditId, $amount, $bookingDate, $peopleId) {

		/*
			## Reply
			- creditId
			- peopleId
			- amount
			- bookingDate
			- creditBalance (positiv = dept)
			- peopleBalance (positiv = dept)
			- overdueBalance (positiv = dept)
			- isOverdue (y, n)
			- creditStatus  (p, a, c, o, r)
			- creditOcrno  (credit Ocrno)
			- isOverdueFirstInvoice (y/n)
			- (options if creditStatus = "p")
				- overdueFirstInvoice (y/n)
				- isFullPaid (y/n)
				- isOverPaid (y)
		print_r($		- overPaidAmount (amount)
		*/

		$reply = new stdClass();
		$reply->creditId = $creditId;
		$reply->peopleId = $peopleId;
		$reply->amount = $amount;
		$reply->bookingDate = $bookingDate;
		$reply->creditBalance = $this->Balances->credit($creditId, $bookingDate,  $this->Db);
		$reply->peopleBalance = $this->Balances->people($peopleId, $bookingDate,  $this->Db);
		$reply->overDueBalance = $this->Balances->peopleOverDue($peopleId, $bookingDate,  $this->Db);
		if ($reply->overDueBalance > 0) {
			$reply->isOverDue = 'y';
		} 
		else {
			$reply->isOverDue = 'n';
		}
		// 
		// --  Check credit status
		//
		$sql = "SELECT credit_status, first_invoice_ocrno  FROM credit WHERE credit_id = " . $creditId;
		$replyCredit = $this->Db->_Get($sql);
		$reply->creditStatus = $replyCredit->credit_status;
		$reply->creditOcrno = $replyCredit->first_invoice_ocrno;


		$reply->isOverPaid = 'n';
			
		// 
		// -- Check due date
		// 
		if ($reply->creditStatus == 'p') {
			$sql = "SELECT duedate FROM first_invoice WHERE ocrno = '$reply->creditOcrno'";
			$replyFirstInvoice = $this->Db->_Get($sql);
			if ($replyFirstInvoice->duedate < $bookingDate) {
				$reply->isOverDueFirstInvoice =  'y';
			}
			else {
				$reply->isOverDueFirstInvoice =  'n';
				if ($reply->amount < $reply->creditBalance) {
					// Delbetalning
					$reply->isFullyPaid = 'n';
				}
				else if ($reply->amount > $reply->creditBalance) {
					$reply->isOverPaid = 'y';
					$reply->overPaidAmount = $reply->amount - $reply->creditBalance;
					$reply->isFullyPaid = 'y';
				}
				else {
					$reply->isOverPaid = 'n';
					$reply->isFullyPaid = 'y';
				}

			}
		}
		
		// 
		// --  Check if people have ovderdue on 1680
		//
		
		//$reply->code = '1';
		//$reply->type = 'credit';
		
		return $reply; 
	} 

	private function checkOverdueAfterBooking($peopleId, $bookingDate) {
		//
		// Check if still overdue after pay
		// 2021-04-14
		// 
		$overDueBalance = $this->Balances->peopleOverDue($peopleId, $bookingDate,  $this->Db);
		if ((float) $replyPeopleOverDue->overdue > 0) {
			$param = new stdClass();
			$param->overdue = '0';
			$this->Db->_Update('people', 'people_id', $peopleId, $param);
		}
	}


	private function preparePeopleIn($peopleId, $amount, $bookingDate) {
		$reply = new stdClass();
		$reply->peopleId = $peopleId;
		$reply->amount = $amount;
		$reply->bookingDate = $bookingDate;
		$reply->overDueBalance = $this->Balances->peopleOverDue($peopleId, $bookingDate,  $this->Db);
		if ($reply->overDueBalance - $amount <= 0 ) {
			$sql = "SELECT overdue FROM people WHERE people_id = $peopleId";
			$replyPeopleOverDue = $this->Db->_Get($sql);
			if ((float) $replyPeopleOverDue->overdue > 0) {
				$param = new stdClass();
				$param->overdue = '0';
				$this->Db->_Update('people', 'people_id', $peopleId, $param);
			}
		}
		return $reply;
	}

	private function prepareBondIn($bondId, $amount, $bookingDate, $peopleId, $bondStatus) {
		$reply = new stdClass();
		$reply->bondId = $bondId; // Use the same ffeld in the table booking
		$reply->peopleId = $peopleId;
		$reply->amount = $amount;
		$reply->bookingDate = $bookingDate;
		if ($bondStatus  == 'p') {
			$param = new stdClass();	
			$param->bond_status = 'o';
			$this->Db->_Update('bond', 'bond_id', $bondId, $param);
		}
		return $reply;
	}	

	private function prepareCompanyIn($companyId, $amount, $bookingDate) {
		$reply = new stdClass();
		$reply->companyId = $companyId;
		$reply->amount = $amount;
		$reply->bookingDate = $bookingDate;

		return $reply;
	}	

	private function bookingCreate($data, $bookingText, $bookingType) {
		/*
			Create the Booking (verfication)
		*/
		$booking = new StdClass();
		$booking->booking_date = $data->bookingDate;
		$booking->booking_text = $bookingText;
		$booking->booking_type = $bookingType;
		if (isset($data->peopleId)) {
			$booking->people_id = $data->peopleId;
		}
		if (isset($data->ocrno)) {
			$booking->ocrno = $data->ocrno;
		}
		if (isset($data->creditId)) {
			$booking->credit_id = $data->creditId;
		}
		if (isset($data->companyId)) {
			$booking->company_id = $data->companyId;
		}
		$booking->_trans = array();
		return $booking;
	}

	private function transCreditInCreate($trans, $peopleId, $creditId, $amount, $transType) {
		/*
			Use for create all trans,
			take a trans array and append transaction to it.
		*/

		$desc = (object) [ 
			"type" => $transType, 
			"debetAccount" => 1930, 
			"creditAccount" => 1380, 
			"debetAmount" => $amount,
			"creditAmount" => -$amount,
			"peopleId" => $peopleId,
			"creditId" => $creditId
		]; 
		$trans = $this->createTrans($trans, $desc);
		return $trans; 
	}
	
	private function transInternCreate($trans, $peopleId, $creditId, $amount, $transType) {
		/*
			Use for create all trans,
			take a trans array and append transaction to it.
		*/
		
		$desc = (object) [ 
			"type" => $transType, 
			"debetAccount" => 1380, 
			"creditAccount" => 1680, 
			"debetAmount" => $amount,
			"creditAmount" => -$amount,
			"peopleId" => $peopleId,
			"creditId" => $creditId
		]; 

		$trans = $this->createTrans($trans, $desc);
		return $trans; 
	}

	private function transPeopleInCreate($trans, $peopleId, $amount, $transType) {
		/*
			Use for create all trans,
			take a trans array and append transaction to it.
		*/
		
		$desc = (object) [ 
			"type" => $transType, 
			"debetAccount" => 1930, 
			"creditAccount" => 1680, 
			"debetAmount" => $amount,
			"creditAmount" => -$amount,
			"peopleId" => $peopleId
		]; 

		$trans = $this->createTrans($trans, $desc);
		return $trans; 
	}

	private function transBondInCreate($trans, $peopleId, $bondId, $amount, $transType) {
		/*
			Use for create all trans,
			take a trans array and append transaction to it.
		*/

		$desc = (object) [ 
			"type" => $transType, 
			"debetAccount" => 1930, 
			"creditAccount" => 2350, 
			"debetAmount" => $amount,
			"creditAmount" => -$amount,
			"peopleId" => $peopleId,
			"creditId" => $bondId
		]; 
		// Use creditId psoition in Booking
		$trans = $this->createTrans($trans, $desc);
		return $trans; 
	}

	private function transCompanyInCreate($trans, $companyId, $amount, $transType) {
		/*
			Use for create all trans,
			take a trans array and append transaction to it.
		*/

		$desc = (object) [ 
			"type" => $transType, 
			"debetAccount" => 1930, 
			"creditAccount" => 2981, 
			"debetAmount" => $amount,
			"creditAmount" => -$amount,
			"companyId" => $companyId
		]; 
		// Use creditId psoition in Booking
		$trans = $this->createTrans($trans, $desc);
		return $trans; 
	}

	private function transCreditingInterest($trans, $peopleId, $creditId, $amount, $transType) {
		/*
			Use for create all trans,
			take a trans array and append transaction to it.
		*/

		$desc = (object) [ 
			"type" => $transType, 
			"debetAccount" => 8300, 
			"creditAccount" => 1380, 
			"debetAmount" => $amount,
			"creditAmount" => -$amount,
			"peopleId" => $peopleId,
			"creditId" => $creditId
		]; 
		$trans = $this->createTrans($trans, $desc);
		return $trans; 
	}

	private function transCreditingCredit($trans, $peopleId, $creditId, $companyId, $amount, $transType) {
		/*
			Use for create all trans,
			take a trans array and append transaction to it.
		*/

		$desc = (object) [ 
			"type" => $transType, 
			"debetAccount" => 2981, 
			"creditAccount" => 1380, 
			"debetAmount" => $amount,
			"creditAmount" => -$amount,
			"peopleId" => $peopleId,
			"companyId" => $companyId,
			"creditId" => $creditId
		]; 
		$trans = $this->createTrans($trans, $desc);
		return $trans; 
	}

	private function transCreditingPeopleCreate($trans, $peopleId, $amount, $accountNo, $transType) {
		/*
			Use for create all Credit,
		*/
		
		$desc = (object) [ 
			"type" => $transType, 
			"debetAccount" => $accountNo, 
			"creditAccount" => 1680, 
			"debetAmount" => $amount,
			"creditAmount" => -$amount,
			"peopleId" => $peopleId
		]; 

		$trans = $this->createTrans($trans, $desc);
		return $trans; 
	}

	private function createTrans($trans, $desc) {

		$item = new stdClass();
		$item->account_no = $desc->debetAccount; // Bank account
		$item->amount = $desc->debetAmount;
		// $item->people_id = $desc->peopleId;
		$item->trans_type = $desc->type;
		if(isset($desc->creditId)) {
			$item->credit_id = $desc->creditId;
		}
		if(isset($desc->peopleId)) {
			$item->people_id = $desc->peopleId;
		}
		if(isset($desc->companyId)) {
			$item->company_id = $desc->companyId;
		}
		array_push($trans, $item);
		
		$item = new stdClass();
		$item->account_no = $desc->creditAccount; 
		$item->amount = $desc->creditAmount;
		//$item->people_id = $desc->peopleId;
		$item->trans_type = $desc->type;
		if(isset($desc->creditId)) {
			$item->credit_id = $desc->creditId;
		}
		if(isset($desc->peopleId)) {
			$item->people_id = $desc->peopleId;
		}
		if(isset($desc->companyId)) {
			$item->company_id = $desc->companyId;
		}
		array_push($trans, $item);
			
		return $trans;
	}
	
	private function bookTransactions($data) {

		
			// Check balans zero
			$balance = 0;
			for ($i=0; $i<sizeof($data->_trans); $i++) {
				$balance =  $balance + $data->_trans[$i]->amount;
			}
			$balance = round($balance, 2);
	
			//$this->_BeginTrans();
			$reply = $this->Db->_Insert('booking', $data );
	
			if ($reply['code'] =! "0") {
				$bookingId = $reply['id'];
				for ($i=0; $i<sizeof($data->_trans); $i++) {
					$data->_trans[$i]->booking_id = $bookingId;
					$this->Db->_Insert('btrans', $data->_trans[$i]);
				}
				if ($balance != 0) {
					$trans = new stdClass();
					$trans->trans_type = "equaliz";
					$trans->account_no = '8193';
					$trans->amount = $balance;
					$this->Db->_Insert('btrans', $trans);
				}
			} else {
				// Error with save Booking
				//$this->_Rollback();
				$reply['code'] = "0";
			}
	
			return $reply['id'];
	}
		
	private function creditStatusSet($creditId, $creditStatus) {
		$param = new stdClass();
		$param->credit_status = $creditStatus;
		// print_r($param);
		$this->Db->_Update('credit', 'credit_id', $creditId, $param);
	}

}
