<?php

ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

define ('INTERNAL_API', 'https://turtle-pay.grusit/internal-api/');
define('FIRST_INVOICE_FOLDER',  '../finvoice/');

$param = new stdClass();

$param->_group = 'Email';
$param->_action =  'Send';

$param->_email = 'bo.grus@yahoo.com';
$param->_subject =  'Test - Bilaga';
$param->_body = "Test API";

$param->_reciever = "bo.grus@icloud.com";
$param->_from_email = "bosse@turtle-pay.se";
$param->_from_name = "Storbolaget";
$param->_bcc = "bo.grusell@turtle-pay.com";
$param->_reply_to = "bo.grusell@grusit.se";

$param->_attach = array();
array_push($param->_attach, FIRST_INVOICE_FOLDER . '12344422395-44924581-F871-F668-A598-346A2BF2F26C.pdf');
array_push($param->_attach, FIRST_INVOICE_FOLDER . '12344422394-BD290642-6A4F-9D9E-864C-1E0F8B799E7C.pdf');

echo json_encode($param); die('');

require_once '../interface/EmailSend.inc'; 

$replyEmail = interfaceEmailSend($param);

print_r($replyEmail);

function _interfaceEmailSend($param) {
    $param->_group = 'Email';
    $param->_action = 'Send';
   	$json = json_encode($param);
    $curl = curl_init(INTERNAL_API);
    curl_setopt($curl, CURLOPT_CUSTOMREQUEST, "POST");
    curl_setopt($curl, CURLOPT_POSTFIELDS, $json);
    curl_setopt($curl, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($curl, CURLOPT_HTTPHEADER, array(
        'Content-Type: application/json',
        'Content-Length: ' . strlen($json))
    );
    //if (ENV_TYPE != 'prod') {	
        curl_setopt($curl, CURLOPT_SSL_VERIFYHOST, 0);
        curl_setopt($curl, CURLOPT_SSL_VERIFYPEER, 0);
    //}
    $result = curl_exec($curl);
		/*
			if (curl_errno($curl)) {
				$error_msg = curl_error($curl);
				print_r($error_msg);
			}
			die('stop');
		*/
    curl_close($curl);
    return json_decode($result);
		
}
