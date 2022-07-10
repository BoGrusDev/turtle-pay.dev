<?php
/*
    WebAppInfo

    Check if URL is a valid WebApp - URL connectd to a company, if so
    Return company_id, wa_store_id, wa_sp_id, wa_logo

    Called from index-tools.inc 

    {
        "_group" : "Company",
        "_action" : "WebAppInfo",
        "_wa_url" : "test-bolaget"
    }
*/

class WebAppInfoClass extends BaseClass {

    private $waUrl;
    private $webAppInfo;
   
    public function _($data) {
        // Check if all demand paramer exist
        if ($this->parameterCheck($data) == false) {
            return array("code"=>"0");
        }
        $this->webAppInfoGet();
        return $this->webAppInfo;
    }

	private function parameterCheck($data) {
		/*
			Check and set all parameter.
			If not exist and mandaty return false
		*/
		
		// Check API paramer
		if (isset($data->_wa_url)) {
			$this->waUrl = trim($data->_wa_url);
		}
		else {
			return false;
		}

		return true;

	}

    private function webAppInfoGet() {
        $sql = "SELECT company_id, wa_store_id, wa_sp_id, wa_logo FROM company ";
        $sql .= "WHERE wa_url = '$this->waUrl' AND company_status = 'a'";
        $this->webAppInfo = $this->_Get($sql);
        return;
    }
}
