<?php
/*
    Turtle Pay 
*/

require_once '../.env/env.inc';
require_once '../.env/' . ENV_TYPE . '/db.config.inc';
require_once '../.env/' . ENV_TYPE . '/site.config.inc';
if (ERROR_REPORTING) {
    require_once '../.env/error-reporting.inc';
}

require_once "Inc/tools.inc";

$peopleDirect = 0;
$peopleIdDirect = 0;

if (isset($_GET['param'])) {
	$paramArray = explode("/", $_GET['param']);
	$page = $paramArray[0];

	if ($page == "people-direct") {
		$page = "people";
		$peopleDirect = 1;
		$qstr = $_SERVER['QUERY_STRING'];
		$arr = explode("&", $qstr);
		$peopleIdDirect = $arr[1];
	}
	
	if ($page == "logout") {
		setcookie("cp-prod", '', time() -3600, '/', '', false);
		header('Location: ' . SITE_URL . 'cp-prod');
		die('');
	}
	
}
else {
    $page = 'home';
}

$valid = false;
if(isset($_COOKIE["cp-prod"])) {
	$cToken = $_COOKIE["cp-prod"];
	$valid = true;
}

if ($valid == true) {

?>

<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <meta name="description" content="">
    <meta name="author" content="">
    <link rel="icon" href="../../../../favicon.ico">

    <title>TurtlePay - Control Panel</title>

    <link rel="stylesheet" href="css/turtlepay-cp.css">
	<script defer src="https://use.fontawesome.com/releases/v5.3.1/js/all.js"></script>
	<link rel="stylesheet" type="text/css" href="css/w2ui-1.5.rc1.css" />
	<link rel="stylesheet" href="css/styles.css?<php echo uniqid(); ?>">
	<script src="js/jquery-3.2.1.min.js"></script>
	<script type="text/javascript" src="js/w2ui-1.5.rc1.min.js"></script>

	<script type="text/javascript" src="js/Helper.js?<php echo uniqid(); ?>"></script>

	<style>
		.amount {width: 120px}
		.PreRow {color: #A62A2A!important}
		.PayRow {color: green!important}
		.column-tight {padding-top: 2px; padding-bottom: : 2px;}
	</style>

	<script>
		var Settings = {};
		Settings.FirstInvoicePath = '<?php echo INVOICE_FOLDER; ?>';
		Settings.SiteUrl = '<?php echo SITE_URL; ?>';

		var PeopleDirect = '<?php echo $peopleDirect; ?>';
		var PeopleIdDirect = '<?php echo $peopleIdDirect; ?>';


	</script>

  </head>

  <body>
	   	<?php require_once "Inc/nav.inc"; ?>

		<section class="section">
			<?php require_once "Pages/" . $page . "/" . $page . ".inc"; ?>

	    	<?php require_once "Pages/" . $page . "/" . $page . ".js.inc"; ?>
		<section>

		<script type="text/javascript" src="js/bulma.js"></script>
  </body>
</html>

<?php

} else  {

	if ($page == "zxcvb55") {
		require_once "Security/login.php";
	}
	else {
	//require_once "Security/login.php";
		die ("NOT ALLOWED");
	}
}

?>
