<?php
date_default_timezone_set("Europe/Stockholm");
require_once '../.env/env.inc';
require_once '../.env/' . ENV_TYPE . '/site.config.inc';
if (ERROR_REPORTING) {
    require_once '../.env/error-reporting.inc';
}
parse_str($_SERVER['QUERY_STRING'], $Param);
if (isset($Param['id'])) {
    $id = $Param['id'] .  '-';
}
else {
    $id = '';
}
//allowed file types

//echo getcwd(); die('');

$arr_file_types = ['image/png', 'image/gif', 'image/jpg', 'image/jpeg'];
 
if (!(in_array($_FILES['file']['type'], $arr_file_types))) {
    $reply = new stdClass();
    $reply->code = '0';
    $reply->denied_code = 'wrong-format-on-file';
    echo json_encode($reply);
}

// Create Filenamne
$url =  strtolower($_FILES['file']['name']);
$url = trim($url);
$url = str_replace("å","a",$url);
$url = str_replace("Å","a",$url);
$url = str_replace("ä","a",$url);
$url = str_replace("Ä","a",$url);
$url = str_replace("ö","o",$url);
$url = str_replace("Ö","o",$url);
$url = str_replace(' ', '-', $url); 
//$url = preg_replace('/[^A-Za-z0-9\-]/', '', $url); 
$url = preg_replace('/[^A-Za-z0-9\-.]/', '', $url);
$url = str_replace('----', '-', $url); 
$url = str_replace('---', '-', $url); 
$url = str_replace('--', '-', $url); 

$logoName = $url;
$logoName = $id . trim($logoName);


// $folder = '/Users/bogrusell/WebSites/turtle-pay.dev/logo/';
$folder = '/var/www/html/logo/';
//$folder = LOGO_FOLDER;
//move_uploaded_file($_FILES['file']['tmp_name'], $folder . $id . $_FILES['file']['name']);
move_uploaded_file($_FILES['file']['tmp_name'], $folder . $logoName);
 
 
$reply = new stdClass();
$reply->code = '1';
$reply->logo_name = $logoName; //  $id . $_FILES['file']['name'];
echo json_encode($reply);
?>