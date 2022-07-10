<?php
/*
    CreditLimitCheckClass
    
    Check compamyes credit limit
    used in crediting and in tdb prize payment
    
    Data_ 2022-03-18

	{
		"_group" : "Company",
		"_action" : "CreditLimitCheck",
        "_company_id" : "69",
		"_amount" : "87000"
	}	

*/

class CreditLimitCheckClass extends BaseClass {

    private $companyId;
    private $amount;
	private $reply;
    
    public function _($data) {
        if ($this->parameterCheck($data) == false) {
            return array("code"=>"0", "denied_code"=>"parameter-fail");
        }


        if ($this->companyExist() == false) {
            return array("code"=>"0", "denied_code"=>"company-not-exist");
        }
		

        if ($this->limitCheck() == false) {
            return array("code"=>"0", "denied_code"=>"no-credit-limit");
        }
        // Limted are acceåted
        $reply = new stdClass();
        $reply->code = '1';
        return $reply;
    }

	private function parameterCheck($data) {
        if (isset($data->_company_id)) {
			$this->companyId = trim($data->_company_id);
            if (!is_numeric($this->companyId)) {
                return false;
            }
		}
		else {
			return false;
		}
        if (isset($data->_amount)) {
			$this->amount = trim($data->_amount);
            if (!is_numeric($this->amount)) {
                return false;
            }
		}
		else {
			return false;
		}
		return true;
	}

    private function companyExist() {
        $sql = "SELECT company_id FROM company WHERE company_id = $this->companyId";
        $res = $this->_Get($sql);
        if ($res['code'] == '1') {
            return true;
        }
        else {
            return false;
        }
    }


    private function limitCheck() {

        // -- Get the companies credit limit, default value
        $sql = "SELECT company_credit_limit FROM setting WHERE setting_type = 's' ORDER BY setting_id DESC LIMIT 1";
        $resSetting = $this->_Get($sql);

        $sql = "SELECT company_credit_limit ";
        $sql .= "FROM setting ";
        $sql .= "WHERE setting_type = 'c' ";
        $sql .= "AND id = $this->companyId ";
        $sql .= "ORDER BY setting_id DESC ";
        $sql .= "LIMIT 1";
        $resSettingCompany = $this->_Get($sql);
       
        if ($resSettingCompany['company_credit_limit'] != null) {
            $creditLimit = $resSettingCompany['company_credit_limit'];
        }
        else {
            $creditLimit = $resSetting['company_credit_limit'];
        }

        // Extra check 
        if (!is_numeric($creditLimit)) {
            $creditLimit = $resSetting['company_credit_limit'];
        }
        // Extra check, more lika a block 
        if (!is_numeric($creditLimit)) {
            $creditLimit = "0";
        }

        $sql = "SELECT SUM(amount) AS sum ";
        $sql .= "FROM btrans ";
        $sql .= "WHERE account_no = '2981' AND prel = 'n' ";
        $sql .= "AND company_id = $this->companyId";
        $resBalance = $this->_Get($sql);
        if ($resBalance['sum'] == null) {
            $balance = "0";
        }
        else {
            $balance = $resBalance['sum'];
        }
        $balance = $balance + $this->amount;

        
        if ($creditLimit >= $balance) {
            return true;
        }
        else {
            return false;
        }
    }
}