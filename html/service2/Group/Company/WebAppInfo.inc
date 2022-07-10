<?php
/*
    WebAppInfoClass

    Used in index.php to controll if the URL is a WebApp

	{
        "_group" : "Company",
        "_action" : "WebAppInfo",
        "_wa_url" : "test-bolaget"
    }
    {
        "company_id": "69",
        "wa_store_id": "67",
        "wa_sp_id": "34",
        "wa_logo": "69-turtle-pay.png",
        "code": "1"
    }
    {
        "code": "0"
    }

*/

class WebAppInfoClass extends AjaxClass {

    private $waUrl;
    private $webAppInfo;
    
    public function _($data) {
        if ($this->parameterCheck($data) == false) {
            return array("code"=>"3");
        }

        $param = new stdClass();
		$param->_group = 'Company';
        $param->_action= 'WebAppInfo';
        $param->_wa_url = $this->waUrl;
		return $this->_RestApiCall($param);
    }

	private function parameterCheck($data) {		
		if (isset($data->_wa_url)) {
			$this->waUrl = trim($data->_wa_url);
		}
        else {
		    return false;
        }
        return true;
	}

}