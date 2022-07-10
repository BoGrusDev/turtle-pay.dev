<?php
/*
    Service.php

    ## FIX
        - Block direkt call from a POST
*/

date_default_timezone_set("Europe/Stockholm");
require_once '../.env/env.inc';
require_once '../.env/' . ENV_TYPE . '/db.config.inc';
require_once '../.env/' . ENV_TYPE . '/site.config.inc';
if (ERROR_REPORTING) {
    require_once '../.env/error-reporting.inc';
}

define('TRUE', "1");
define('FALSE', "-1");
$text = new StdClass();
$method = $_SERVER['REQUEST_METHOD'];

if ($method == 'POST') {
    require_once "Config/Setting.inc";
    $json = file_get_contents('php://input');
    $data =  json_decode($json);
    $class = $data->_group . 'Class';
    require_once 'Service/class/' . $data->_group . '.class';
    $api = new $class(DB_HOST, DB_NAME, DB_USER, DB_PASS, $text);
    echo $api->Run($data);
} else {
    die('NOT ALLOWED ');
}
