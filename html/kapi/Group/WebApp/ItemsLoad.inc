<?php
/*
    ItemsLoadClass
    
   {
		"_group" : "WebApp",
		"_action" : "ItemsLoad",
		"_item_code" : "882E3A6B7B0DD6A1CF2A60F5F68C025D"
	}	
*/

class ItemsLoadClass extends BaseClass {

    private $userId;
	private $invoiceEventItemCode;
	private $selectionOn;
	private $reply;

    public function _($data) {

		// Check if all demand paramer exist
		if ($this->parameterCheck($data) == false) {
			return array("code"=>"0");
		}
		
		if ($this->invoiceEventLoad($data) == false) {
			return array("code"=>"0");
		}
		
		$this->settings = $this->_Settings($this->reply['company_id']);

		if ($this->selectionOn == 'y') {
			$this->eventSelectionLoad();
		}

		$this->settingsSet();

		return $this->reply;

	}

	private function parameterCheck($data) {
        if (isset($data->_item_code)) {
			$this->itemCode = trim($data->_item_code);
		}
		else {
			return false;
		}
		if (isset($data->_selection_on)) {
			$this->selectionOn = trim($data->_selection_on);
		}
		else {
			$this->selectionOn = 'n';
		}
		return true;
	}

	public function invoiceEventLoad(){
	
		$sql = "SELECT e.*, c.known_as, c.company_name, ";
		$sql .= "ie.event_id, i.invoice_event_item_id, i.invoice_event_id, i.email, i.invoice_event_item_status, ie.invoice_event_status ";
		$sql .= "FROM event_v4 e, invoice_event_item i, invoice_event ie, company c ";
		$sql .= "WHERE e.event_id = ie.event_id AND invoice_event_item_code = '$this->itemCode' AND ";
		$sql .= "ie.invoice_event_id = i.invoice_event_id AND e.company_id = c.company_id ";
		$sql .= "AND i.invoice_event_item_status IN ('s','r')";
		$this->reply = $this->_Get($sql);			
		if ($this->reply['code'] == '1') {
			return true;
		}
		else {
			return false;
		}
	}

	public function eventSelectionLoad() {
		$sql = "SELECT * FROM event_v4 WHERE event_id = " . $this->reply['event_id'];
		$this->eventWebform = $this->_Get($sql);
        
		if ($this->reply['participant_on'] == 'y') {
			$sql = "SELECT * FROM event_selection_setting WHERE event_id = " . $this->reply['event_id'] . " ORDER BY sortorder";
			$this->reply['selection'] = $this->_GetList($sql);
			for ($i = 0; $i < sizeof($this->reply['selection']); $i++) {
				$sql = "SELECT * FROM event_option_setting WHERE event_selection_setting_id = " . $this->reply['selection'][$i]['event_selection_setting_id']  .   " ORDER BY sortorder";
				$this->reply['selection'][$i]['option'] = $this->_GetList($sql);
			}
		} 
	}

	private function settingsSet() {
		$settings = new stdClass();
		$settings->first_Invoice_due_days = $this->settings->first_Invoice_due_days;
		$settings->first_invoice_start_fee = $this->settings->first_invoice_start_fee; 
		$settings->first_invoice_start_fee = round($this->settings->first_invoice_start_fee, 0);
		$settings->credit_interest_grace_days = $this->settings->credit_interest_grace_days; 
		$settings->first_invoice_fee = round($this->settings->first_invoice_fee, 0);
		$settings->repayment_term = $this->settings->repayment_term;
		$settings->customerInterest = $this->settings->customerInterest;
		$settings->monthly_invoice_fee = round($this->settings->monthly_invoice_fee, 0);
		$settings->administration_fee = $this->settings->administration_fee;
		$settings->effective_rate = $this->settings->effective_rate; 
		$this->reply['settings'] = $settings;  
	}

}