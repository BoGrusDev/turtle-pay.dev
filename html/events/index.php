<?php
/*
	TurtlePay Lista
	
	Cookie: 
	- turtlepayevents : contain the tokenid
    - turtlepayekontoid : cuurent company id
	- turtlepayeip : internt bankid yes else no
	- turtlepayetoid : hold mobile token with login 

	ALTER TABLE `panel_report` ADD `is_open` CHAR(1) NOT NULL DEFAULT 'n' AFTER `cancel_on`;
*/


date_default_timezone_set("Europe/Stockholm");
require_once '../.env/env.inc';
require_once '../.env/' . ENV_TYPE . '/site.config.inc';
if (ERROR_REPORTING) {
    require_once '../.env/error-reporting.inc';
}


// -- Check for SSL
if (ENV_TYPE == 'prod') {
	//define ('SITE_URL', 'https://www.turtle-pay.com/events');
	if(!isset($_SERVER["HTTPS"]) || $_SERVER["HTTPS"] != "on") {
		header("Location: https://www.turtle-pay.com/" . $_SERVER["REQUEST_URI"], true, 301);
		exit;
	}
	if($_SERVER["HTTP_HOST"] == "176.57.88.50") {
		header("Location: https://www.turtle-pay.com" . $_SERVER["REQUEST_URI"], true, 301);
		exit;
	}
}

// --
// -- Check if logged in and handle the loggin 
// --

parse_str($_SERVER['QUERY_STRING'], $Param);

$Reload = 'no';
$UserId = '0';
$UserName = '';
$LogedIn = false;
$ChangeUser = 'no';
$ChangeUserId = '';
if(isset($_COOKIE['turtlepayevents'])) {
	$Token = $_COOKIE['turtlepayevents'];
	require_once "inc/tools.inc";

	// $UserList = UserApiCall($Token);
	// echo SITE_URL . 'events/service/json.php'; die('');
	//$UserList = UserApiCall($Token, SITE_URL . 'events/service/json.php');
	$UserList = UserApiCall($Token, EVENTS_URL);
	$UserList = $UserList->list;
	
	//print_r($UserList);
	//echo SITE_URL . 'events/service/json.php');
	//die('');
	
	

	for ($i = 0; $i < sizeof($UserList); $i++) {
		if ($UserList[$i]->company_id == $UserId ) {
			
		}
	}

	if (isset($Param['konto'])) {
		$newUserId = $Param['konto'];
		$UserId = 0;
		$Reload = 'yes';
		for ($i=0; $i<sizeof($UserList); $i++) {
			if ($newUserId == $UserList[$i]->company_id) {
				$UserId = $newUserId;
			}
		}
	}
	else {
		 
		if (isset($_COOKIE['turtlepayekontoid'])) {
			$UserId = $_COOKIE['turtlepayekontoid'];
			for ($i=0; $i<sizeof($UserList); $i++) {
				if ($UserId == $UserList[$i]->company_id) {
					$UserName = $UserList[$i]->known_as;
				}
			}
		}
		else {
			$UserId = $UserList[0]->company_id;
			$Reload = 'yes';
		}
	}
	//echo 'UserId: ' . $UserId . ' ' . $UserName; die('');
	$LogedIn = true;
}

require_once "inc/Mobile_Detect.php";
$detect = new Mobile_Detect;

// Any mobile device (phones or tablets).
if ( $detect->isMobile() ) {
	$isMobile = 'yes';
}
else {
	$isMobile = 'no';
}




?>

<!DOCTYPE html>
<html lang="en">

<head>
  	<meta charset="UTF-8">
  	<meta name="viewport" content="width=device-width, initial-scale=1.0">
  	<meta http-equiv="X-UA-Compatible" content="ie=edge">
  	<title>TurtlePay - Events</title>
  	<link rel="icon" type="image/png" href="images/favicon.png">
	<link rel="stylesheet" type="text/css" href="css/kundportal.css">  
	<?php /* <link rel="stylesheet" href="css/bulma-checkradio.min.css"> */ ?>
	<link rel="stylesheet" type="text/css" href="css/styles.css?<?php echo uniqid(); ?>">

  	<script src="js/jquery-3.2.1.min.js"></script>
	<script type="text/javascript" src="View/HelperView.js?<?php echo uniqid(); ?>"></script> 
	<script type="text/javascript" src="js/Helper.js?<?php echo uniqid(); ?>"></script> 
	
	<script src="js/bowser.min.js"></script>
	<script src="js/underscore-min.js"></script>
	
	<link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.8.1/css/all.css">
	 
	<script>
		var Site = '<?php echo SITE_URL; ?>';
		var UserId = '<?php echo $UserId; ?>';
		var UserName = '<?php echo $UserName; ?>';
		var Reload = '<?php echo $Reload; ?>';
		var Users;
		var MessageError = "Ett okänd fel har inträffat, försök igen<br>eller kontakta Turtle Pay AB på telefon 08-806220<br>eller e-post info@turtle-pay.com."
		var LoginTime = 20;

		
		var isMobile = '<?php echo $isMobile; ?>';
		<?php if ($LogedIn) {?>
			var Token = "<?php echo $Token; ?>";
		<?php } else { ?>
			var Token = false;
		<?php } ?>

		var Browser = bowser.name;   // Safari // FireFox // Chrome

		if (Reload == 'yes') {
			if (UserId == '0') {
				// skip
			}
			else {
				document.cookie = "turtlepayekontoid=" + UserId + ';sameSite=lax;path=/';
			}
			
			window.location.href = Site + 'events';
		}
		const _ = new HelperView();
  </script>

<body>
	<?php
		if ($LogedIn)  { 
			require_once "inc/nav-events.inc";
			require_once "pages/events/events.inc"; 
			require_once "pages/events/events.js.inc"; 
		}
		else {
			
			require_once 'pages/login/login.js.inc';
			require_once 'pages/login/login.inc';
		}
		 
	?>

	<div class="modal" id="message-modal">
        <div class="modal-background"></div>
		<div class="modal-card pl0 pr0  modal-width">
			<header class="modal-card-head">
				<p class="modal-card-title has-text-centered">Meddelande</p>
			</header>
			<section class="modal-card-body">
				<p id="message-text-modal" class="has-text-centered"></p>
			</section>
			<footer class="modal-card-foot" >
				<button id="eMessageModalClose" class="button is-dark w120 image-center">OK</button>
			</footer>
		</div>
	</div>


<script>


	$(document).on('click', '#eMessageModalClose', function(event) {
		event.preventDefault();
		$('#message-modal').removeClass('is-active');
	});

	document.addEventListener('DOMContentLoaded', function() {
	//Helper.onClick('eMessageModalClose', closeMessageModal);

	 if (Token) {
		var date = new Date();
		date.setTime(date.getTime()+(LoginTime*180*1000)); // 60
		var expires = "; expires="+date.toGMTString();
		document.cookie = "turtlepayevents=" + Token + expires + ';sameSite=lax;path=/';
	
		Controller.init(); 
	}

});

$(document).on('click', '#eLogout', function(event) {
    event.preventDefault();
   
	document.cookie = 'turtlepayevents=; expires=Thu, 01 Jan 1970 00:00:00 UTC;path=/';
	document.cookie = 'turtlepayekontoid=; expires=Thu, 01 Jan 1970 00:00:00 UTC;path=/';
	document.cookie = 'turtlepayeip=; expires=Thu, 01 Jan 1970 00:00:00 UTC;path=/';
	window.location.href = Site + 'events';
});

</script>
<script src="js/bulma.js"></script>


</body>
</html>
	
