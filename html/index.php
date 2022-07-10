<?php
/*
	TurtlePay Kundportal

	Cockies
	turtlepaykp = token
	turtlepid = companyid
	turtlepayip = internal yes / no novile / no mobile

*/
//echo 'Inside';
//die('');

require_once '.env/env.inc';
require_once '.env/' . ENV_TYPE . '/site.config.inc';
if (ERROR_REPORTING) {
    require_once '.env/error-reporting.inc';
}

// 
// Special handlin for prod, for handling the SSL 
if (ENV_TYPE == 'prod') {
	// define ('SITE_URL', 'https://www.turtle-pay.com/');
	if  ($_SERVER["HTTP_HOST"] == 'turtle-pay.com') {
		header("Location: https://www.turtle-pay.com/", true, 301);
		exit;
	}

	if(!isset($_SERVER["HTTPS"]) || $_SERVER["HTTPS"] != "on") {
		header("Location: https://www.turtle-pay.com/" . $_SERVER["REQUEST_URI"], true, 301);
		exit;
	}

	if($_SERVER["HTTP_HOST"] == "176.57.88.50") {
		header("Location: https://www.turtle-pay.com/" . $_SERVER["REQUEST_URI"], true, 301);
		exit;
	}
}

require_once "inc/index-tools.inc";

parse_str($_SERVER['QUERY_STRING'], $Param);

/*
	Check if page exist in the portal
*/
if ( empty($Param)  || array_key_exists($Param['param'] ,$PageUrl)) {
	// OK, fortsätt
}
else {
	/* 
		Check if a web App
	*/
	$webAppInfo = IsWebApp($Param);
	if ($webAppInfo) {
		/*
			Enter Web App
		*/
		if (isset($Param['t']) || isset($Param['tp'])) {
			require_once 'webapp-tdb/index.inc';
		}
		else {
			$CompanyId = $webAppInfo->company_id;
			require_once 'wa-lib4/index.inc';
		}
		die('');
	}
	$Param = [];
}

require_once "inc/html.inc";
require_once "inc/Mobile_Detect.php";

$ChangeUser = 'no';
$ChangeUserId = '';

$Operator = IsLogedIn();

//echo '<pre>';
//print_r($Operator);

if ($Operator->code == '1') {
	$LogedIn = true;
	$UserId = $Operator->user_id;
	$Token = $Operator->token;
	if ($UserId > 0) { 
		$HasSie = $Operator->has_sie;
		$HasInvoiceService = $Operator->has_invoice_service;
		$HasBo = $Operator->has_bo;
	}
	/* 
		Change user account konto?nr=xx change company
	*/
	if (!empty($Param) && $Param['param'] == 'konto') {
		$ChangeUserId = $Param['nr'];
		if (is_numeric($ChangeUserId)) {
			$ChangeUser = 'yes';
		} 
	}
}
else {
	$LogedIn = false;
	$UserId = 0;
}

// echo $UserId; die('');

/*
	Check if Mobile
*/
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
  	<title>TurtlePay - Kundportal</title>
  	<link rel="icon" type="image/png" href="images/favicon.png">
	<link rel="stylesheet" type="text/css" href="css/kundportal.css">
	<?php /* <link rel="stylesheet" href="css/bulma-checkradio.min.css"> */ ?>
	<link rel="stylesheet" type="text/css" href="css/styles.css?<?php echo uniqid(); ?>">

  	<script src="js/jquery-3.2.1.min.js"></script>
	<script type="text/javascript" src="js/helper.js?<?php echo uniqid(); ?>"></script>

	<script src="js/bowser.min.js"></script>
	<script src="js/underscore-min.js"></script>
	<script type="text/javascript" src="js/spectrum.js"></script>
	<link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.8.1/css/all.css">


	<style>

  <?php
  if ($isMobile == "yes") { ?>

		#trans-user-list {padding-top: 0px}
		tr {
			border-bottom: 1px solid rgba(0, 0, 0, 0.1);
		}
		th {
		    font-size: 12px;
		    background-color: #cccccc;
		    padding: 4px!important;
		}
		td {
		    font-size: 13px;
		    padding: 3px;
		}
	<?php }
	else { ?>
		#trans-user-list {padding-top: 0px}
		tr {
			border-bottom: 1px solid rgba(0, 0, 0, 0.1);
		}
		th {
		    background-color: #cccccc;
		    padding: 4px!important;
		}
		td {
		    padding: 3px;
		}
		body, html {
			  height: 100%;
		}

	<?php } ?>

	.bg {
		background-image: url("css/turtle-pay-bg.jpg");
		background-position: center;
		background-repeat: no-repeat;
		background-size: cover;
	}
 	</style>
<script>

	const Site = '<?php echo SITE_URL; ?>';
	var UserId = '<?php echo $UserId; ?>';
	var ChangeUser = '<?php echo $ChangeUser; ?>';
	var ChangeUserId = '<?php echo $ChangeUserId; ?>';
	var Users;
	var MessageError = "Ett okänd fel har inträffat, försök igen<br>eller kontakta Turtle Pay AB på telefon 08-806220<br>eller e-post info@turtle-pay.com."
	var LoginTime = 20;

	/*
	function CheckUser(token) {
		var param = {};
		param._group = "People";
		param._action = "CheckPr";
		param._token = token;
		$.ajax({ type: "POST", url: 'service2/', data: param,
			success: function(result) {
				console.log(result);
				var Users = jQuery.parseJSON(result);
			}
		});
	}
	*/
	var isMobile = '<?php echo $isMobile; ?>';
	<?php if ($LogedIn) {?>

		var Token = "<?php echo $Token; ?>";

	<?php } else { ?>
		var Token = false;
	<?php } ?>

	var Browser = bowser.name;   // Safari // FireFox // Chrome
	if (ChangeUser == 'yes') {
		document.cookie = "turtlepayid=" + ChangeUserId + ';sameSite=lax;path=/';
		window.location.href = Site;
	}
  </script>


</head>
  <body>
	  <?php
	  	
  		if ($LogedIn) {
			if ($UserId == '0') {
				require_once "inc/nav-user.inc";
			}
			else {
				require_once "inc/nav-company.inc";
			}
		}
		else {
			require_once "inc/nav.inc";
		}
	 ?>
	  <?php require_once "pages/" . $page . "/" . $page . ".inc"; ?>
	  <?php require_once "pages/" . $page . "/" . $page . ".js.inc"; ?>

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

    <script type="text/javascript" src="js/bulma.js"></script>

	<script>

        function closeMessageModal() {
            $('#message-modal').removeClass('is-active');
        }

        document.addEventListener('DOMContentLoaded', function() {
            Helper.onClick('eMessageModalClose', closeMessageModal);
			 if (Token) {
				Helper.onClick('eLogout', logout);
				<?php if (ENV_TYPE == 'prod') { ?>
        			var date = new Date();
        			date.setTime(date.getTime()+(LoginTime*180*1000)); // Original
        			var expires = "; expires="+date.toGMTString();
        			document.cookie = "turtlepaykp=" + Token + expires + ';sameSite=lax;path=/';
    			<?php } else { ?>
				// Utveckling
        			document.cookie = "turtlepaykp=" + Token + ';expires=Fri, 31 Dec 9999 23:59:59 GMT;sameSite=lax;path=/';
    			<?php } ?>
			}
		});
		
		window.addEventListener( "pageshow", function ( event ) {
			var historyTraversal = event.persisted || 
			( typeof window.performance != "undefined" && 
				window.performance.navigation.type === 2 );
			if ( historyTraversal ) {
				window.location.reload();
			}
		});
		
		function logout() {
			//alert('logout');
			document.cookie = 'turtlepaykp=; expires=Thu, 01 Jan 1970 00:00:00 UTC;path=/';
			document.cookie = 'turtlepayid=; expires=Thu, 01 Jan 1970 00:00:00 UTC;path=/';
			document.cookie = 'turtlepayip=; expires=Thu, 01 Jan 1970 00:00:00 UTC;path=/';
			window.location.href = Site;
		}

    </script>
  </body>
</html>
