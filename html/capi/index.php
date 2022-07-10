<?php
/*
	index.php - Base for the c-api
*/

date_default_timezone_set("Europe/Stockholm");
require_once '../.env/env.inc';
require_once '../.env/' . ENV_TYPE . '/site.config.inc';
if (ERROR_REPORTING) {
    require_once '../.env/error-reporting.inc';
}

// --
// Define allowed API Groups
//
$groups = [
	'BankID',
	'Company',
	'Email',
	'InvoiceRequest',
	'InvoiceRequestConfirm',
	'MyPage',
	'Check',
	'Refund',
	'Report',
	'Security',
	'Trans',
	'WebApp',
	'WebAppV2',
	'WebAppV4',
	'WebAppOffer'
];

require_once "ActionOpen.class";

// Used for mark reports and PDF with demo stamp.
define ('DEMO_MODE' , true); // Obsolet

$method = $_SERVER['REQUEST_METHOD'];
if ($method == 'POST') {
	$json = file_get_contents('php://input');
    $data =  json_decode($json);
	/*
	if (!isset($data->_token) && $data->_group != "Security" ) {
		echo '{"code":"0", "denied_code":"no_token"}';
	}
	*/
	$class = $data->_group . 'Class';
	if ($data->_group == "Server") {
		server($data->_action);
		die('');
	}
	if (in_array($data->_group, $groups)) {
    	require_once 'class/' . $data->_group . '.class';
    	$api = new $class(BAPI_URL);

    	echo $api->Run($data);
	} else {
		die('NOT ALLOWED GROUP');
	}
}
else {
    die('NOT ALLOWED METHOD');
}

function server ($action) {
    if ($action == "Status") {
        $reply = new StdClass();
        $reply->code = '1';
        $reply->message ="Aktiv";
        echo json_encode($reply);
    } else {
        die('NOT ALLOWED');
    }
}
