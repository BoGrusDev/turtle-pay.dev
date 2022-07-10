<?php
Class Action extends DatabaseService{

		// localhost/TurtlePay/ControlPanel/Service/

		public function PaymentOrder($data) {
			/*
			SELECT t.company_id, c.company_name, c.bank_account, SUM(t.amount) AS to_pay FROM trans t, company c
			WHERE t.account_no = '2981' AND t.trans_date = '2018-09-26' AND t.company_id = c.company_id
			GROUP BY t.company_id;
			*/
		}
		// Moved
		public function InvoiceList($data) {
			$sql = "SELECT * FROM first_invoice ORDER BY ocrno";
			return json_encode($this->_GetList($sql));
		}
		// Moved
		public function InvoideSetPrinted($data) {
			return $this->_Update("first_invoice", "invoice_filename", $data->_invoice_filename, $data);
		}

		public function PeopleList() {
			/*
				{
					"_action" : "PeopleList"
				}
			*/
			$sql = "SELECT people_id, personal_id_number, CONCAT(last_name, ', ', first_name) AS people_name, address, postcode, city, is_customer, is_sp, is_principal, has_uc_check, people_status, email, mobile, created_date FROM people ORDER BY last_name, first_name";
			return json_encode($this->_GetList($sql));
		}

		public function PeopleGet($data) {
			$sql = "SELECT * FROM people WHERE people_id = $data->_people_id";
			return json_encode($this->_Get($sql));
		}

		public function PeopleGetInfo($data) {
			// Used for principal
			//{
			//	"_action" : "PeopleGetInfo",
			//	"_people_id" : "119"
			//}
			$sql = "SELECT personal_id_number, CONCAT(last_name, ', ', first_name) AS people_name, status_principal  FROM people WHERE people_id = $data->_people_id";
			return json_encode($this->_Get($sql));
		}

		public function PeopleRequestList($data) {
			$sql = "SELECT i.invoice_request_id, i.personal_id_number, i.request_time, i.amount, i.company_id, i.store_id,";
			$sql .= "i.sale_person_people_id, i.description, i.credit_id, i.denied_code, i.invoice_request_status, ";
			$sql .= "c.company_name, s.store_name, CONCAT(x.first_name, ' ' ,x.last_name) AS salesperson ";;
			$sql .= "FROM invoice_request i ";
			$sql .= "LEFT JOIN company c ON i.company_id = c.company_id ";
			$sql .= "LEFT JOIN store s ON i.store_id = s.store_id ";
			$sql .= "LEFT JOIN people x ON i.sale_person_people_id = x.people_id ";
			$sql .= "WHERE i.personal_id_number = '$data->_personal_id_number' ";
			$sql .= "ORDER BY i.invoice_request_id DESC ";
			return json_encode($this->_GetList($sql));
		}

		public function PeopleTotalDept($data) {
			$sql = "SELECT sum(amount) AS totaldept FROM trans WHERE people_id = 34 AND (account_no = '1380' OR account_no=1680)";
			$res =  json_encode($this->_Get($sql));
			return $res;
		}

		public function PeopleOverdueDept($data) {
			$sql = "SELECT sum(amount) AS overduedept FROM trans WHERE people_id = 34 AND account_no = '1380'";
			$res =  json_encode($this->_Get($sql));
			return $res;
		}

		public function PeopleTransList($data) {
			// Should be moved to Config and Settings
			$this->FirstInvoiceUrl = 'http://localhost/TurtlePay/f-invoice/';
			$sql = "SELECT t.trans_id, t.ver_id, t.trans_date, t.trans_text, t.invoice_filename,";
			$sql .= "s.store_name, co.company_name, t.account_no, t.amount ";
			$sql .= "FROM trans t ";
			$sql .= "LEFT JOIN ver v ON t.ver_id = v.ver_id ";
			$sql .= "LEFT JOIN company co ON t.company_id = co.company_id ";
			$sql .= "LEFT JOIN store s ON t.store_id = s.store_id ";
			$sql .= "WHERE t.people_id = $data->_people_id AND ";
			$sql .= "(t.account_no = '1380' OR t.account_no='1680' OR t.account_no='2380') ";
			$sql .= "ORDER BY t.trans_id";
			$list = $this->_GetList($sql);
			//echo $sql;
			$balance = 0;
			$balance_bonus = 0;
			$amount_1380 = 0;
			$amount_1680 = 0;
			$amount_2380 = 0;
			$result = array();
			foreach ($list as $item) {
				$listItem = array();
				$listItem['trans_id'] =  $item['trans_id'];
				//$listItem['ver_id'] =  $item['ver_id'];
				$listItem['trans_date'] =  $item['trans_date'];
				$listItem['trans_text'] =  $item['trans_text'];
				$listItem['company_name'] =  $item['company_name'];
				$listItem['store_name'] =  $item['store_name'];
				//$listItem['account_no'] =  $item['account_no'];
				if ($item['account_no'] == '1380') {
					$listItem['amount_1380'] =  number_format($item['amount'], 2);
					$balance = $balance + (float)$item['amount'];
					$amount_1380 = $amount_1380 + (float)$item['amount'];
					$listItem['extra'] = '<a style="font-size: 11px; color:blue" id="button-first-invoice" target="_blank" href="' . $this->FirstInvoiceUrl . $item['invoice_filename'] . '">Open Invoice</a>';
				}
				else if ($item['account_no'] == '1680') {
					$listItem['amount_1680'] =  number_format($item['amount'], 2);
					$balance = $balance +  (float)$item['amount'];
					$amount_1680 = $amount_1680 + (float)$item['amount'];
				}
				else if ($item['account_no'] == '2380') {
					$listItem['amount_2380'] =  number_format($item['amount'], 2);
					$balance_bonus = $balance_bonus +  (float)$item['amount'];
					$listItem['trans_text'] = 'Bonus in';
					$amount_2380 = $amount_2380 + (float)$item['amount'];
				}
				$listItem['balance'] = number_format($balance, 2);
				$listItem['balance_bonus'] = number_format($balance_bonus, 2);
				$result[] = $listItem;
			}
			/*
			$listItem = array();
			$listItem['trans_id'] = '999';
			$listItem['store_name'] = '<div style="font-weight:bold">TOTAL:</div>';
			$listItem['balance'] = '<div style="font-weight:bold">' . number_format($balance, 2) . '</div>';
			$listItem['amount_1380'] = '<div style="font-weight:bold">' . number_format($amount_1380, 2) . '</div>';
			$listItem['amount_1680'] = '<div style="font-weight:bold">' . number_format($amount_1680, 2) . '</div>';
			$listItem['amount_2380'] = '<div style="font-weight:bold">' . number_format($amount_2380, 2) . '</div>';
			*/
			//$result[] = $listItem;
			return json_encode($result);
		}

		public function RequestList() { // Should chnage name to PeopleRequestList
			$sql = "SELECT i.invoice_request_id, i.personal_id_number, i.request_time, i.amount, i.company_id, i.store_id, i.sale_person_people_id,";
			$sql .= "i.description, i.credit_id, i.denied_code, i.invoice_request_status, CONCAT(p.first_name, ' ' ,p.last_name) AS name,";
			$sql .= "c.company_name, s.store_name, CONCAT(x.first_name, ' ' ,x.last_name) AS salesperson ";
			$sql .= "FROM invoice_request i ";
			$sql .= "LEFT JOIN people p ON i.personal_id_number = p.personal_id_number ";
			$sql .= "LEFT JOIN company c ON i.company_id = c.company_id ";
			$sql .= "LEFT JOIN store s ON i.store_id = s.store_id ";
			$sql .= "LEFT JOIN people x ON i.sale_person_people_id = x.people_id ";
			$sql .= "ORDER BY i.invoice_request_id DESC ";
			return json_encode($this->_GetList($sql));
		}

		/*
		SELECT trans_id, trans_date, trans_text, account_no, amount, credit_id FROM trans
		WHERE people_id = 30 AND (account_no = '1380' OR account_no=1680)
		ORDER BY trans_date


		SELECT sum(amount) FROM trans WHERE people_id = 30 AND account_no = '1380'
		*/
		/*
		public function PeopleInsertGrid($data) {
			$sql = "INSERT INTO people(first_name, last_name, people_no, email, mobile) VALUES ('$data->first_name', '$data->last_name', '$data->people_no', '$data->email', '$data->mobile')";
			//echo $sql;
			// Set update date/time later
			$rcode = $this->_InsertSql($sql);
			if ($rcode < 1) {
				return false;
			}
			return $rcode;
		}

		public function PeopleUpdate($data) {
			return $this->_Update("people", "people_id", $data->_people_id, $data);
			//return json_encode($this->_Get($sql));
		}
		*/

		public function CompanyList() {
			$sql = "SELECT * FROM company ORDER BY company_name";
			return json_encode($this->_GetList($sql));
		}

		public function CompanyGet($data) {
			$sql = "SELECT * FROM company WHERE company_id = $data->_company_id";
			return json_encode($this->_Get($sql));
		}

		public function CompanyUpdate($data) {
			return $this->_Update("company", "company_id", $data->_company_id, $data);
		}

		public function CompanyInsert($data) {
			return $this->_Insert("company", $data);
		}

		public function StoreList($data) {
			$sql = "SELECT * FROM store WHERE company_id = $data->_company_id ORDER BY store_name";
			return json_encode($this->_GetList($sql));
		}

		public function StoreUpdate($data) {
			return $this->_Update("store", "store_id", $data->_store_id, $data);
		}

		public function StoreInsert($data) {
			return $this->_Insert("store", $data);
		}

		public function PrincipalList($data) {
			$sql = "SELECT c.cp_id, c.people_id, c.personal_id_number, c.cp_status, CONCAT(p.first_name, ' ', p.last_name) AS people_name ";
			$sql .= "FROM company_people c ";
			$sql .= "LEFT JOIN people p ON c.personal_id_number = p.personal_id_number ";
			$sql .= "WHERE c.company_id = $data->_company_id AND c.is_principal = 'y'";
			return json_encode($this->_GetList($sql));
		}

		public function SalespersonList($data) {
			$sql = "SELECT c.cp_id, c.people_id, c.personal_id_number, c.cp_status, CONCAT(p.first_name, ' ', p.last_name) AS people_name ";
			$sql .= "FROM company_people c ";
			$sql .= "LEFT JOIN people p ON c.personal_id_number = p.personal_id_number ";
			$sql .= "WHERE c.company_id = $data->_company_id AND c.is_sp = 'y'";
			return json_encode($this->_GetList($sql));
		}

		public function CompanyRequestList($data) {
			$sql = "SELECT i.invoice_request_id, i.personal_id_number, i.request_time, i.amount, i.company_id, i.store_id, i.sale_person_people_id,";
			$sql .= "i.description, i.credit_id, i.denied_code, i.invoice_request_status, CONCAT(p.first_name, ' ' ,p.last_name) AS name,";
			$sql .= "s.store_name, CONCAT(x.first_name, ' ' ,x.last_name) AS salesperson ";
			$sql .= "FROM invoice_request i ";
			$sql .= "LEFT JOIN people p ON i.personal_id_number = p.personal_id_number ";
			$sql .= "LEFT JOIN people x ON i.sale_person_people_id = x.people_id ";
			$sql .= "LEFT JOIN store s ON i.store_id = s.store_id ";
			$sql .= "WHERE i.company_id = $data->_company_id ";
			$sql .= "ORDER BY i.invoice_request_id DESC ";
			return json_encode($this->_GetList($sql));
		}

		public function SalespersonAdd($data) {
			/*
				{
					"_action" : "CompanyAddSalesperson",
					"_bankid" : "no",
					"_bankid_type" : "auth",
					"company_id" : "3",
					"personal_id_number" : "7512120012"
				}
			*/
			$sql = "INSERT INTO company_people (company_id, personal_id_number , is_sp,  cp_status) ";
			$sql .= "VALUES ($data->company_id,'$data->personal_id_number', 'y', 'a')";
			$this->_InsertSql($sql);
			$this->SetCompanyPeople($data->personal_id_number);
			return;
		}

		public function SalespersonUpdate($data) {
			return json_encode($this->_Update("company_people", "cp_id", $data->_cp_id, $data));
		}

		public function SalespersonRemove($data) {
			if ($data->people_id == '0') {
				$sql = "DELETE FROM company_people  WHERE cp_id = $data->_cp_id";
				return json_encode($this->_Query($sql));
			}
			else {
				$sql = "UPDATE company_people SET cp_status = 'r' WHERE cp_id = $data->_cp_id";
				return json_encode($this->_Query($sql));
			}
		}

		public function PrincipalAdd($data) {
			/*
				{
					"_action" : "CompanyAddPrincipal",
					"_bankid" : "no",
					"_bankid_type" : "auth",
					"company_id" : "3",
					"personal_id_number" : "6512120012"
				}
			*/
			$sql = "INSERT INTO company_people (company_id, personal_id_number , is_principal,  cp_status) ";
			$sql .= "VALUES ($data->company_id,'$data->personal_id_number', 'y', 'a')";
			$this->_InsertSql($sql);
			$this->SetCompanyPeople($data->personal_id_number);
			return;
		}

		private function setCompanyPeople($personal_id_number) {
			$res = $this->_Get("SELECT people_id FROM people WHERE personal_id_number = '$personal_id_number'");
			if ($res['code'] == '1') {
				$sql = "UPDATE company_people SET people_id = " . $res['people_id'] . " WHERE personal_id_number = '$personal_id_number'";
				$this->_Query($sql);
			}
		}

		public function PrincipalUpdate($data) {
			return json_encode($this->_Update("company_people", "cp_id", $data->_cp_id, $data));
		}

		public function PrincipalRemove($data) {
			if ($data->people_id == '0') {
				$sql = "DELETE FROM company_people  WHERE cp_id = $data->_cp_id";
				return json_encode($this->_Query($sql));
			}
			else {
				$sql = "UPDATE company_people SET cp_status = 'r' WHERE cp_id = $data->_cp_id";
				return json_encode($this->_Query($sql));
			}
		}

		public function CompanyTransList($data) {
			// Should be moved to Config and Settings
			$this->FirstInvoiceUrl = 'http://localhost/TurtlePay/f-invoice/';

			$sql = "SELECT t.trans_id, t.ver_id, t.trans_date, t.trans_text, t.invoice_filename,";
			$sql .= "s.store_name,  t.account_no, t.amount, t.trans_type ";
			$sql .= "FROM trans t ";
			$sql .= "LEFT JOIN ver v ON t.ver_id = v.ver_id ";
			$sql .= "LEFT JOIN store s ON t.store_id = s.store_id ";
			$sql .= "WHERE t.company_id = $data->_company_id AND ";
			$sql .= "(t.account_no = '2981' OR t.account_no='2999') ";
			$sql .= "ORDER BY t.trans_id ";

			$list = $this->_GetList($sql);
			//echo $sql;
			$balance = 0;
			$balance_bonus = 0;
			//$amount_2891 = 0;
			$balance_obs = 0;
			//$amount_2380 = 0;
			$result = array();
			foreach ($list as $item) {
				$listItem = array();
				$listItem['trans_id'] =  $item['trans_id'];
				//$listItem['ver_id'] =  $item['ver_id'];
				$listItem['trans_date'] =  $item['trans_date'];
				$listItem['trans_text'] =  $item['trans_text'];
				//$listItem['company_name'] =  $item['company_name'];
				$listItem['store_name'] =  $item['store_name'];
				//$listItem['account_no'] =  $item['account_no'];
				if ($item['account_no'] == '2981') {
					$listItem['amount_2891'] =  number_format($item['amount'], 2);
					$balance = $balance + (float)$item['amount'];
					if ($item['trans_type'] == "inv") {
						$listItem['extra'] = '<a style="font-size: 11px; color:blue" id="button-first-invoice" target="_blank" href="' . $this->FirstInvoiceUrl . $item['invoice_filename'] . '">Open Invoice</a>';
					}
				}
				else if ($item['account_no'] == '2999') {
					$listItem['amount_2999'] =  number_format($item['amount'], 2);
					$balance_obs = $balance_obs +  (float)$item['amount'];
					//$amount_1680 = $amount_1680 + (float)$item['amount'];
				}
				$listItem['balance'] = number_format($balance, 2);
				$listItem['balance_obs'] = number_format($balance_obs, 2);
				$result[] = $listItem;
			}
			/*
			$listItem = array();
			$listItem['trans_id'] = '999';
			$listItem['store_name'] = '<div style="font-weight:bold">TOTAL:</div>';
			$listItem['balance'] = '<div style="font-weight:bold">' . number_format($balance, 2) . '</div>';
			$listItem['amount_1380'] = '<div style="font-weight:bold">' . number_format($amount_1380, 2) . '</div>';
			$listItem['amount_1680'] = '<div style="font-weight:bold">' . number_format($amount_1680, 2) . '</div>';
			$listItem['amount_2380'] = '<div style="font-weight:bold">' . number_format($amount_2380, 2) . '</div>';
			*/
			//$result[] = $listItem;
			return json_encode($result);
		}

		public function CreditList($data){

			$sql = "SELECT c.credit_id, c.start_date, c.people_id, c.personal_id_number, c.company_id, c.amount, c.store_id, c.sale_person_people_id, ";
			$sql .= "c.receipt_number, c.started, c.completed, c.first_invoice_sent, c.first_invoice_email_sent, ";
			$sql .= "CONCAT(p.first_name, ' ' ,p.last_name) AS personname, co.company_name, s.store_name, f.invoice_filename ";
			$sql .= "FROM credit c ";
			$sql .= "LEFT JOIN people p ON c.personal_id_number = p.personal_id_number ";
			$sql .= "LEFT JOIN company co ON c.company_id = co.company_id  ";
			$sql .= "LEFT JOIN store s ON c.store_id = s.store_id ";
			$sql .= "LEFT JOIN first_invoice f ON c.credit_id = f.credit_id ";
			$sql .= "ORDER BY c.credit_id";
			return json_encode($this->_GetList($sql));
		}

		public function CreditGet($data){

			$sql = "SELECT c.credit_id, c.start_date, c.people_id, c.personal_id_number, c.company_id, c.amount, c.store_id, c.sale_person_people_id, ";
			$sql .= "c.receipt_number, c.started, c.first_invoice_ocrno, c.first_invoice_sent, c.first_invoice_email_sent, ";
			$sql .= "c.first_invoice_email_account, c.completed, ";
			$sql .= "CONCAT(p.first_name, ' ' ,p.last_name) AS personname, co.company_name, s.store_name, f.invoice_filename, CONCAT(x.first_name, ' ' ,x.last_name) AS salesperson ";
			$sql .= "FROM credit c ";
			$sql .= "LEFT JOIN people p ON c.personal_id_number = p.personal_id_number ";
			$sql .= "LEFT JOIN company co ON c.company_id = co.company_id  ";
			$sql .= "LEFT JOIN store s ON c.store_id = s.store_id ";
			$sql .= "LEFT JOIN first_invoice f ON c.credit_id = f.credit_id ";
			$sql .= "LEFT JOIN people x ON c.sale_person_people_id = x.people_id ";
			$sql .= "WHERE c.credit_id = " . $data->_credit_id;
			return json_encode($this->_Get($sql));
		}

		public function CreditUpdate($data) {
			return json_encode($this->_Update("credit", "credit_id", $data->_credit_id, $data));
		}

		/*
			Inser:

			INSERT INTO `ver` (`ver_id`, `trans_date`, `ver_text`) VALUES (NULL, '2018-09-27', 'Vendor payment');

			INSERT INTO `trans` (`trans_id`, `period_id`, `ver_id`, `trans_text`, `trans_date`, `trans_type`, `account_no`, `amount`, `people_id`, `company_id`, `store_id`, `cr_id`, `sales_person_people_id`, `credit_id`, `invoice_filename`, `ocr_number`, `reference`, `reference_date`, `due_date`, `interest`, `terms`) VALUES (NULL, '1', '26', 'Vendor payment', '2018-09-27', 'venpa', '1930', '-2597', NULL, '1', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

		*/

		public function BookOrderDaysReport($data) {
			/*
			 {
			 "_action" : "BookOrderDaysReport",
			 "_from_date" : "2018-09-19",
			 "_to_date" : "2018-09-19"
			}
			*/
			$sql = "SELECT t.account_no, a.account_name, SUM(t.amount) AS sum_account FROM trans t, account a ";
			$sql .= "WHERE t.account_no = a.account_no AND  ";
			$sql .= "t.trans_date >= '" . $data->_from_date . "' AND t.trans_date <= '" . $data->_to_date .  "'";
			$sql .= "GROUP BY t.account_no, a.account_name";

			return json_encode($this->_GetList($sql));
		}

		public function BookOrderList($data) {
			$sql = "SELECT v.ver_id, v.trans_date, v.ver_text, t.account_no, a.account_name, t.amount FROM ver v  ";
			$sql .= "LEFT JOIN trans t on v.ver_id = t.ver_id ";
			$sql .= "LEFT JOIN account a on t.account_no = a.account_no ";
			$sql .= "WHERE v.trans_date >= '" . $data->_from_date . "' AND v.trans_date <= '" . $data->_to_date . "' ";
			$sql .= "ORDER BY v.ver_id ";
			//echo $sql;
			return json_encode($this->_GetList($sql));
		}

		public function SettingGet() {
			$sql = "SELECT * FROM setting ORDER BY setting_id DESC LIMIT 1";
			return json_encode($this->_Get($sql));
		}

		public function SettingInsert($data) {
			return $this->_Insert("setting", $data);
		}

		/*
		SELECT v.ver_id, v.trans_date, v.ver_text, t.account_no, a.account_name, t.amount,
		t.people_id, t.company_id, t.store_id, t.cr_id, t.salese_person_people_id, t.credit_id,
		t.invoice_no, t.ocr_number, t.reference, t.reference_date, t.due_date, t.interest, t.terms,
		co.company_name, s.store_name
		FROM ver v, trans t
		LEFT JOIN account a on t.account_no = a.account_no
		LEFT JOIN company co ON t.company_id = co.company_id
		LEFT JOIN store s ON t.store_id = s.store_id
		WHERE t.people_id = 82 AND v.ver_id = t.ver_id
		ORDER BY v.ver_id;
		*/


		/*
		public function CashRegisterList($data) {
			$sql = "SELECT * FROM cash_register WHERE shop_id = $data->_store_id ORDER BY cash_register_no";
			return json_encode($this->_GetList($sql));
		}

		public function CashRegisterGet($data) {
			$sql = "SELECT * FROM cash_register WHERE cr_id = $data->_cr_id ORDER BY cash_register_no";
			return json_encode($this->_GetList($sql));
		}

		public function CustomerList() {
			$sql = "SELECT client_id, client_name, client_no FROM client ORDER BY client_name";
			return json_encode($this->_GetList($sql));
		}

		public function CustomerGet($data) {
			$sql = "SELECT * FROM client WHERE client_id = $data->_client_id";
			return json_encode($this->_Get($sql));
		}
		*/
		/*

		public function LoanList() {
			$sql = "SELECT l.loan_id, l.start_date, l.customer_id, l.customer_no, l.client_id, l.store_id, l.sp_id, l.receipt_number,l.amount, l.loan_status,";
			$sql .= "CONCAT(p.last_name, ', ', p.first_name) AS people_name ";
			$sql .= "FROM loan l, people p ";
			$sql .= "WHERE l.customer_id = p.people_id ";
			$sql .= "ORDER BY loan_id";
			return json_encode($this->_GetList($sql));
		}

		public function LoanListNew() {
			$sql = "SELECT * FROM loan WHERE loan_status='n' ORDER BY loan_id";
			return json_encode($this->_GetList($sql));
		}

		public function LoanGet($data) {
			$sql = "SELECT * FROM loan WHERE loan_id = $data->_loan_id";
			return json_encode($this->_Get($sql));
		}
		*/
		public function AccountList() {
			$sql = "SELECT * FROM account ORDER BY account_no";
			return json_encode($this->_GetList($sql));
		}

		public function LenderList() {
			$sql = "SELECT * FROM lender ORDER BY lender_name";
			return json_encode($this->_GetList($sql));
		}

		public function LenderUpdateGrid($data) {
			//echo $data['data'];
			//return true;
			//$dataList = json_decode($data['data']);
			foreach (json_decode($data->data) as $item) {
				$this->_UpdateGrid('lender', $item, 'lender_id', $item->recid, 'recid');
			}
		}

		public function RefinancDept($data) {

			$trans_text = "Refinance in";
			$ref_id = $data->lender_id;
			$ref_no = $data->loan_no;
			$ref_date = $data->due_date;
			$ver_id = $this->verCreate();
			if (!$ver_id) {
					return $this->errorMessage('FALSE', 'Verification create problen');
			}

			$sql = "INSERT INTO trans(ver_id, trans_text, account_no, amount, trans_date, ref_id, ref_no, ref_date) VALUES ($ver_id, '$trans_text', '$account_no', $amount, '$trans_date', $ref_id, '$ref_no', '$ref_date')";
			$rcode = $this->_InsertSql($sql);
			if ($rcode < 1) {
				//$this->_Rollback();
				return '-1';
			}

			return $rcode;


			if ($this->transCreate ($ver_id, $trans_text, '2460', -$data->amount, $data->trans_date, $ref_id, $ref_no, $ref_date) < 0) {
				return $this->errorMessage('-1', 'Transaction 2460 fail');
			}
			if ($this->transCreate ($ver_id, $trans_text, '1040', $data->amount, $data->trans_date, $ref_id, $ref_no,  $ref_date) < 0) {
				return $this->errorMessage('-1', 'Transaction 1040 fail');
			}
			// $this->_Commit();
			return  '{"code":"TRUE"}';
		}

		public function RefinanceRepayment($data) {
			print_r($data);
			// 1040 – Credit
			// 2460 – Debit - Refinance dept. (option)
			// 6500 – Debit - Refinance interest (option)
			// 6510 – Debit - Refinance cost (option)

		}

		public function InvoiceBuy($data) {
			// 1510 – Debit – Customer receivable
			// 2440 – Credit – Client payable
			// 3020 – Credit – Income (1% for fee for client / shop)

		}

		public function ClientRepay($data) {
			// 1510 – Credit Customer receivable
			// 1040 – Debit – Bank (option)
			// 3010 – Credit – Income fee
			// 3020 – Credit – Income default fee
			// 3100 – Credit - Interest income
			// 3310 – Credit – Interest default income
			// 1510 – Debit - Outstanding default (option)
			// 1510 – Credit - Outstanding default (option)

		}

		public function OutstandingPayment($data) {

		}

		private function verCreate(){
			$ver_text = '';
			$sql = "INSERT INTO ver() VALUES ()";
			//$this->_BeginTrans();
			$ver_id = $this->_InsertSql($sql);
			if ($ver_id < 1) {
				//$this->_Rollback();
				//echo $sql;
				return false;
			}
			return $ver_id;
		}

		private function transCreate ($ver_id, $trans_text, $account_no, $amount, $trans_date, $ref_id = 0, $ref_no = "", $ref_date = null  ) {
			$sql = "INSERT INTO trans(ver_id, trans_text, account_no, amount, trans_date, ref_id, ref_no, ref_date) VALUES ($ver_id, '$trans_text', '$account_no', $amount, '$trans_date', $ref_id, '$ref_no', '$ref_date')";
			$rcode = $this->_InsertSql($sql);
			if ($rcode < 1) {
				//$this->_Rollback();
				//echo $sqlTrans1;
				//echo $sql;
				return '-1';
			}
			//echo $rcode;
			//echo $sql;
			return $rcode;
		}

		private function errorMessage($error_code, $error_text) {
			$errorMessage = '{';
			$errorMessage .= '"code":"' . $error_code . '",';
			$errorMessage .= '"text":"' . $error_text . '"';
			$errorMessage .= '}';
			return $errorMessage;
		}

		public function FiDeposit($data)  {
			$ttype_no = 'FI-DEP';
			$ver_text = "Finanace deposit";
			$trans_date = $data->trans_date;
			$amount = $data->amount;
			$ref_id = $data->lender_id; // ref_id
			$ref_no = $data->loan_no; // ref_no
			$ref_date = $data->due_date; // ref_date
			$account_Bank = '1040';
			$account_FinanceLoan = '2460';


			$sqlTrans1 = "INSERT INTO trans(ver_id, trans_date, account_no, amount, ref_id, ref_no, ref_date) VALUES ($ver_id, '$trans_date', '$account_Bank', $amount, $ref_id, '$ref_no', '$ref_date')";
			$rcode = $this->_InsertSql($sqlTrans1);
			if ($rcode < 1) {
				$this->_Rollback();
				//echo $sqlTrans1;
				echo $sqlTrans1;
				return false;
			}
			$sqlTrans2 = "INSERT INTO trans(ver_id, trans_date, account_no, amount, ref_id, ref_no, ref_date) VALUES ($ver_id, '$trans_date', '$account_FinanceLoan', -$amount, $ref_id, '$ref_no', '$ref_date')";
			$rcode = $this->_InsertSql($sqlTrans2);
			if ($rcode < 1) {
				$this->_Rollback();
				//echo $sqlTrans2;
				echo 'sql2';
				return false;
			}
			$this->_Commit();
			echo 'OK';
			return true;
		}

		public function FiRepay($data)  {
			$ttype_no = 'FI-REP';
			$ver_text = "Repay finance";
			if (isset($data->trans_date)) {
				$trans_date = $data->trans_date;
			} else {
				//return '{"code":"false"}';
			}
			$amount = $data->amount;
			$ref_id = $data->lender_id;
			$ref_no = $data->loan_no;
			$interest = $data->interest;
			$amor = $data->amor;
			$account_Bank = '1040';
			$account_FinanceLoan = '2460';
			$account_FinanceInterest = '8030';


			$sqlVer = "INSERT INTO ver(ttype_no, ver_text) VALUES ('$ttype_no', '$ver_text')";
			$this->_BeginTrans();
			$ver_id = $this->_InsertSql($sqlVer);
			if ($ver_id < 1) {
				//$this->_Rollback();
				echo $sqlVer;
				return false;
			}
			// Bank
			$sqlTrans1 = "INSERT INTO trans(ver_id, trans_date, account_no, amount, ref_id, ref_no) VALUES ($ver_id, '$trans_date', '$account_Bank', -$amount, $ref_id, '$ref_no')";
			$rcode = $this->_InsertSql($sqlTrans1);
			if ($rcode < 1) {
				$this->_Rollback();
				echo $sqlTrans1;
				echo 'sql1';
				return false;
			}
			//Amor
			$sqlTrans2 = "INSERT INTO trans(ver_id, trans_date, account_no, amount, ref_id, ref_no) VALUES ($ver_id, '$trans_date', '$account_FinanceLoan', -$amor, $ref_id, '$ref_no')";
			$rcode = $this->_InsertSql($sqlTrans2);
			if ($rcode < 1) {
				$this->_Rollback();
				echo $sqlTrans2;
				echo 'sql2';
				return false;
			}
			//Interest
			$sqlTrans3 = "INSERT INTO trans(ver_id, trans_date, account_no, amount, ref_id, ref_no) VALUES ($ver_id, '$trans_date', '$account_FinanceInterest', -$interest, $ref_id, '$ref_no')";
			$rcode = $this->_InsertSql($sqlTrans3);
			if ($rcode < 1) {
				$this->_Rollback();
				echo $sqlTrans3;
				echo 'sql3';
				return false;
			}
			$this->_Commit();
			echo 'OK';
			return;
		}

		public function AccountLedger($data) {
			if (!isset($data->_account_no)) {
				return json_encode([
					'replycode' => '-10'
				]);
			}
			$sql = "SELECT t.trans_id, t.ver_id, t.trans_date, t.trans_text, t.account_no, t.ref_date, t.ref_id, t.ref_no, t.amount  FROM trans t WHERE t.account_no ='$data->_account_no' ORDER BY t.ver_id";
			return json_encode($this->_GetList($sql));
		}

		public function _AccountLedger($data) {
			if (!isset($data->_account_no)) {
				return json_encode([
					'replycode' => '-10'
				]);
			}
			$sql = "SELECT e.event_id, e.event_date, e.text, e.customer_id, t.amount FROM trans t, event e WHERE t.account_no = '$data->_account_no' AND e.event_id = t.event_id";
			return json_encode($this->_GetList($sql));
		}

		public function AccountLedgerSum($data) {
			if (!isset($data->_account_no)) {
				return json_encode([
					'replycode' => '-10'
				]);
			}
			$sql = "SELECT a.account_no, a.account_name, sum(t.amount) AS sum FROM account a, trans t, event e WHERE t.account_no = '$data->_account_no' AND e.event_id = t.event_id AND a.account_no = t.account_no";
			return json_encode($this->_Get($sql));
		}

		public function CustomerUpdate() {
			$id = $_POST["_ID"];
			return $this->_Update("customer", "customerid", $id);
		}

		public function EntryRefinancingNew($data){
			/*
				1930 Bank - Debet
				2350 Refinancing debt - Credit
				{
					"_action" : "EntryRefinancingNew",
					"trans_date" : "2018-04-18",
					"amount" : "2500000.00",
					"company_id" : "4"
				}
			*/
			$text = "Refinancing New";

			$dataVer = clone $data;
			$dataVer->ver_text = $text;
			$ver_id = $this->verInsert($dataVer);
			if (!$ver_id) return $this->errorMessage(FALSE, 'Verification create error');

			$dataTrans = clone $data;
			$dataTrans->ver_id = $ver_id;
			$dataTrans->trans_text = $text;
			$dataTrans->account_no = '1930';
			if ($this->_Insert('trans', $dataTrans) < 0) {
				//$this->_Rollback();
				return $this->errorMessage(FALSE, 'Transaction Debet (1930) error');
			}

			$dataTrans->account_no = '2350';
			$dataTrans->amount = -$dataTrans->amount;
			if ($this->_Insert('trans', $dataTrans) < 0) {
				//$this->_Rollback();
				return $this->errorMessage(FALSE, 'Transaction Credit (2350) error');
			}

			return  '{"code":"1"}';
		}

		public function EntryRefinancingRepay($data){
			/*
				2350 Refinancing debt - Debet
				1930 Bank - Credit
				{
					"_action" : "EntryRefinancingRepay",
					"trans_date" : "2018-04-22",
					"amount" : "400000.00",
					"company_id" : "4"
				}
			*/
			$text = "Refinancing Repay";

			$dataVer = clone $data;
			$dataVer->ver_text = $text;
			$ver_id = $this->verInsert($dataVer);
			if (!$ver_id) return $this->errorMessage(FALSE, 'Verification create error');

			$dataTrans = clone $data;
			$dataTrans->ver_id = $ver_id;
			$dataTrans->trans_text = $text;
			$dataTrans->account_no = '2350';
			if ($this->_Insert('trans', $dataTrans) < 0) {
				//$this->_Rollback();
				return $this->errorMessage(FALSE, 'Transaction Debet (2350) error');
			}

			$dataTrans->account_no = '1930';
			$dataTrans->amount = -$dataTrans->amount;
			if ($this->_Insert('trans', $dataTrans) < 0) {
				//$this->_Rollback();
				return $this->errorMessage(FALSE, 'Transaction Credit (1930) error');
			}

			return  '{"code":"1"}';
		}

		public function EntryRefinancingInterest($data){
			/*
				8400 Interest Cost - Debet
				1330 Customer Credits - Credit
				{
					"_action" : "EntryRefinancingInterest",
					"trans_date" : "2018-04-24",
					"amount" : "2765.00",
					"company_id" : "4"
				}
			*/
			$text = "Refinancing Interest";

			$dataVer = clone $data;
			$dataVer->ver_text = $text;
			$ver_id = $this->verInsert($dataVer);
			if (!$ver_id) return $this->errorMessage(FALSE, 'Verification create error');

			$dataTrans = clone $data;
			$dataTrans->ver_id = $ver_id;
			$dataTrans->trans_text = $text;
			$dataTrans->account_no = '2350';
			if ($this->_Insert('trans', $dataTrans) < 0) {
				//$this->_Rollback();
				return $this->errorMessage(FALSE, 'Transaction Debet (2350) error');
			}

			$dataTrans->account_no = '1930';
			$dataTrans->amount = -$dataTrans->amount;
			if ($this->_Insert('trans', $dataTrans) < 0) {
				//$this->_Rollback();
				return $this->errorMessage(FALSE, 'Transaction Credit (1930) error');
			}

			return  '{"code":"1"}';
		}

		public function EntryCustomerCreditNew($data) {

			$text = "Customer Credit New";

			$dataVer = clone $data;
			$dataVer->ver_text = $text;
			$ver_id = $this->verInsert($dataVer);
			if (!$ver_id) return $this->errorMessage(FALSE, 'Verification create error');

			$dataTrans = clone $data;
			$dataTrans->ver_id = $ver_id;
			$dataTrans->trans_text = $text;
			$dataTrans->account_no = '1380';
			if ($this->_Insert('trans', $dataTrans) < 0) {
				//$this->_Rollback();
				return $this->errorMessage(FALSE, 'Transaction Debet (1380) error');
			}

			$dataTrans->account_no = '1930';
			$dataTrans->amount = -$dataTrans->amount;
			if ($this->_Insert('trans', $dataTrans) < 0) {
				//$this->_Rollback();
				return $this->errorMessage(FALSE, 'Transaction Credit (1930) error');
			}

			return  '{"code":"1"}';
		}

		public function EntryCustomerInvoice($data) {
				// Book Avi Feee

		}

		public function EntryCustomerPayment($data) {
			/*
				Collect data:
					MinMum to Pay this Amount
					Avi Fee
					Calculate Interest on Planned Payment until today.
					Last Interest date
					(Overdue Interest)
					OverDueCredit
			*/
		}

		public function EntryVendorPayout($data) {
			/*
				Payback Vendor
				2981 Debet Vendor Payables
				1930 Credit Bank
			*/
		}

		public function JobVendorPayout($data){

		}

		public function JobCustomerInvoicing($data){

		}

		private function JobCustomemonthlyRecon($data){

		}

		private function JobCustomerCreditComplete($data){

		}

}
