<?php
/*
    index.php
    
    This is the entry point for the API.

*/

ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

date_default_timezone_set("Europe/Stockholm");


$method = $_SERVER['REQUEST_METHOD'];
if ($method != 'POST') {
    die('NOT ALLOWED'); 
}

$json = file_get_contents('php://input');
$data = json_decode($json);

if ($data == false) {
    die('NOT ALLOWED'); 
}

if (isset($data->_key) && isset($data->_group) && isset($data->_action)) {
    // All ready to go
}
else {
    die('NOT ALLOWED'); 
}

$group = $data->_group;

// Include class from the parameter group
require_once 'class/' . $group . 'Class.inc';
if (isset($includes)) {
    $includes = explode(',', $includes);
    $package = [];
    for ($i=0; $i<sizeof($includes); $i++) {
        require_once 'inc/' . $includes[$i] . '.inc';

        if ($includes[$i] == 'Db') {
            require_once "Db.config.inc";
            $package[$includes[$i]] = new $includes[$i](DB_HOST, DB_NAME, DB_USER, DB_PASS);
        }
        else {
            $package[$includes[$i]] = new $includes[$i]();
        }
    }
    $api = new $group($package);
}
else {
    $api = new $group();
}
echo $api->Run($data);

