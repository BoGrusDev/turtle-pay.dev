<?php
/*
    service.php
*/
date_default_timezone_set("Europe/Stockholm");
$json = file_get_contents('php://input');
$data =  json_decode($json);    
echo $data->_code;
//require_once 'Service/class/' . $data->_group . '.class';
//$api = new $class(DB_SECURITY_HOST, DB_SECURITY_NAME, DB_SECURITY_USER, DB_SECURITY_PASS, $text);
$reply = new StdClass();
$reply->code = '0';
$reply->token = 'GUI 1234567890';
echo json_encode($reply);

