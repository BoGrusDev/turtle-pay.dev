<?php

/*

ALTER TABLE `company` ADD `priv_on` CHAR(1) NOT NULL DEFAULT 'n' AFTER `tdb_orgno`; 

*/

class PrivBaseClass extends BaseClass {

    public function superUserCheck($userId, $operatorId) {
        //$sql = "SELECT tdb_apikey, tdb_orgno FROM company WHERE company_id=$companyId AND tdb_on = 'y'";
        //$reply = $this->_Get($sql);
        //return $reply;
        return array("code"=>"1");
    }
}
