<?php
date_default_timezone_set("Europe/Stockholm");

$reply = new StdClass();
$reply->code = '0';
$reply->message ="TurtlePay är i service läge.\r Försök igen om en halvtimme!";
echo json_encode($reply);
