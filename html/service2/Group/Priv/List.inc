
<?php
/*
    ListClass
    
   	Get the compentions for a organization and return all 
	that today day no expieer

	https://app.equipe.com/organizers/515/meetings.json

	prodOn means get from API else get from local file

	{
		"_group" : "Priv",
		"_action" : "List",
		"_user_id" : "69",
		"_token" : "780CCE158AA7C7D449E69AF19A7DD8CB"
	}	

*/

class ListClass extends AjaxClass {

    private $userId;
    private $operatorId;
    private $peopleList;

    public function _($data) {

        if ($this->parameterCheck($data) == false) {
            return array("code"=>"0", "denied_code"=>"param-fail");
        }
		
		$this->privInfo = $this->_TokenCheck($this->token, $this->userId);

		if ($this->privInfo->code == '0') {
            return array("code"=>"0", "denied_code"=>"no-priv");
        }

		if ($this->privInfo->priv == 'su') {
			$data->_operator_id = $this->privInfo->operatorId;
			$this->peopleList = $this->_RestApiCall($data);
        	return $this->peopleList;
        }
		else {
			return array("code"=>"0", "denied_code"=>"no-priv");
		}
    }

	private function parameterCheck($data) {
		
		// Check API paramer
		if (isset($data->_user_id)) {
			$this->userId = trim($data->_user_id);
		}
		else {
			return false;
		}

        if (isset($data->_token)) {
			$this->token = trim($data->_token);
		}
		else {
			return false;
		}
		

		/*
		$reply= $this->superUserCheck($this->userId, $this->operatorId);
		if ($reply['code'] != '1') {
			return false;
		}
		*/

		return true;

	}
}