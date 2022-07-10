<?php
require_once '../.env/env.inc';
if (ERROR_REPORTING) {
    require_once '../.env/error-reporting.inc';
}

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    //session_start();
    require_once '../.env/' . ENV_TYPE . '/site.config.inc';
    $codes = ' 04115701,02046201';
    $codesUser['04115701'] = "195711040054";
    $codesUser['02046201'] = "196204021155";
    $codesUser['21046201'] = "196204021155";
    $code = $_POST['code'];
    if (strpos($codes , $code) > 0) {
     
      $param = new stdClass();
    	$param->_bankid_personal_id_number =  $codesUser[$code];
      $reply = bankIDAuth($param) ;
      if ($reply->code == '1') {
        $param = new stdClass();
        $param->_order_ref = $reply->order_ref;
        $reply = bankIDAuthCollect($param);
        if ($reply->code == '1') {
            $token = createToken();
            //setcookie("cp-prod", $token, time() + 21600 ); // 2 timmar
            if (ENV_TYPE == 'prod') {
                setcookie("cp-prod", $token, time() + (10 * 365 * 24 * 60 * 60), '/', '', false);
            }
            else  {
                setcookie("cp-prod", $token, time() + (10 * 365 * 24 * 60 * 60), '/', '', false);
            }
            //setcookie("cp-prod", $token, time() + (10 * 365 * 24 * 60 * 60), '/','www.turtle-pay.com', false);
            //$_SESSION["cp-prod"] = $token;


            header('Location: ' .  SITE_URL . 'cp-prod');

            /*
            if (ENV_TYPE == 'prod') {
                header('Location: https://www.turtle-pay.com/cp-prod');
            }
            else {
               header('Location: http://turtle-pay.prod/cp-prod');
            }
            */
            die();
        } else {
          print_r( $reply);
          die('PROBLEM SIGN IN!');
        }
      }
      else {
        print_r( $reply);
        die('PROBLEM CONNTACT BANKID IN!');
        
      }
    } else {
      die('WRONG CODE!');
    }
}


function bankIDAuth($data) {

  $reply = new StdClass();
  if (!isset($data->_bankid_personal_id_number)) {
    $reply->code = "0";
    $reply->denied_code = "bankid_personal_id_number_is_missing";
    return $reply;
    die('');
  }

  $json = '{"personalNumber":"' . $data->_bankid_personal_id_number . '", "endUserIp":"176.57.88.50"}';
  $curl = curl_init();
  curl_setopt( $curl, CURLOPT_URL, 'https://appapi2.bankid.com/rp/v5/auth');
  curl_setopt($curl, CURLOPT_CUSTOMREQUEST, "POST");
  curl_setopt($curl, CURLOPT_POSTFIELDS, $json);
  curl_setopt($curl, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($curl, CURLOPT_HTTPHEADER, array(
    'Content-Type: application/json',
    'Content-Length: ' . strlen($json))
  );

  curl_setopt($curl, CURLOPT_CAINFO, 'Security/bankid.ca.pem');
  curl_setopt($curl, CURLOPT_SSLKEY, 'Security/turtlepay2.key');
  curl_setopt($curl, CURLOPT_SSLCERT, 'Security/turtlepay2.pem');
  curl_setopt($curl, CURLOPT_SSLCERTPASSWD, 'Fk&1618BKl@tp');
  curl_setopt($curl, CURLOPT_SSL_VERIFYHOST, 0);
  curl_setopt($curl, CURLOPT_SSL_VERIFYPEER, 0);
  $result = curl_exec($curl);
  curl_close($curl);

  if(!$result) {
    $reply->code = "0";
        $reply->denied_code = "bankid_problem";
  }
  else {
    $authObject = json_decode($result);
    if (isset($authObject->orderRef)) {
      $reply->code = "1";
      $reply->order_ref = $authObject->orderRef;
      $reply->auto_start_token = $authObject->autoStartToken;
      $reply->denied_code = "";
    }
    else if (isset($authObject->errorCode)) {
      $reply->code = "0";
      $reply->denied_code = $authObject->errorCode;
    }
    else {
      $reply->code = "0";
      $reply->denied_code = "bankid_problem";
    }
  }

  return $reply;
}

function bankIDAuthCollect($data) {

  $reply = new StdClass();
  if (!isset($data->_order_ref)) {
    $reply->code = "0";
    $reply->denied_code = "order_ref_is_missing";
    return $reply;
    die('');
  }
  $json = '{"orderRef":"' . $data->_order_ref . '"}';
  $curlCheck = curl_init();
  curl_setopt( $curlCheck, CURLOPT_URL, 'https://appapi2.bankid.com/rp/v5/collect');
  curl_setopt($curlCheck, CURLOPT_CUSTOMREQUEST, "POST");
  curl_setopt($curlCheck, CURLOPT_POSTFIELDS, $json);
  curl_setopt($curlCheck, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($curlCheck, CURLOPT_HTTPHEADER, array(
    'Content-Type: application/json',
    'Content-Length: ' . strlen($json))
  );
  curl_setopt($curlCheck, CURLOPT_CAINFO, 'Security/bankid.ca.pem');
  curl_setopt($curlCheck, CURLOPT_SSLKEY, 'Security/turtlepay2.key');
  curl_setopt($curlCheck, CURLOPT_SSLCERT, 'Security/turtlepay2.pem');
  curl_setopt($curlCheck, CURLOPT_SSLCERTPASSWD, 'Fk&1618BKl@tp');

  curl_setopt($curlCheck, CURLOPT_SSL_VERIFYHOST, 0);
  curl_setopt($curlCheck, CURLOPT_SSL_VERIFYPEER, 0);

  sleep(5);

  $status = false; // Set true when a complete, fail or inknown error occur
  while ($status== false) {

    $result = curl_exec($curlCheck);
    if(!$result) {
      $reply->code = "0";
          $reply->denied_code = "bankid_problem";
      return $reply;
      die('');
       }
    else {
      $collectObject = json_decode($result);
      if (isset($collectObject->errorCode)) {
        $reply->code = '0';
        $reply->denied_code = $collectObject->details;
        $status = true;
      } else {
        switch ($collectObject->status) {
          case 'pending':
            sleep(3);
            break;
          case 'failed':
            $reply->code = '0';
            $reply->denied_code = $collectObject->hintCode;
             $status = true;
            break;
          case 'complete':
            $reply->code = '1';
            $reply->name = $collectObject->completionData->user->name;
            $reply->givenName = $collectObject->completionData->user->givenName;
            $reply->surname = $collectObject->completionData->user->surname;
            $reply->ipAddress = $collectObject->completionData->device->ipAddress;
            $status = true;
            break;
          default:
            $reply->code = '0';
            $reply->denied_code = "bankid_problem";
            $status = true;
            print_r($collectObject);
        }
      }
    }
  }
  return $reply;
}

function createToken(){
  // Return 2F8672B9-1BB8-2FFA-C56D-C5F8E8946FEF
  if (function_exists('com_create_guid')){
    return com_create_guid();
  }	else{
    mt_srand((double)microtime()*10000);//optional for php 4.2.0 and up.
    $charid = strtoupper(md5(uniqid(rand(), true)));
    return $charid;
  }
}
?>

<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <meta name="description" content="">
    <meta name="author" content="">
    <link rel="icon" href="favicon.ico">

    <title>TurtlePay - Login</title>

    <!-- Bootstrap core CSS -->
    <link href="Security/css/bootstrap.min.css" rel="stylesheet">

    <!-- Custom styles for this template -->
    <link href="Security/css/login.css" rel="stylesheet">
  </head>

  <body class="text-center">
    <form class="form-signin" method="POST">
    <h1>TurtlePay</h1>
      <h2 class="h3 mb-3 font-weight-normal">Control Panel</h1>
      <label for="code" class="sr-only">Code</label>
      <input type="text"  id="code" name="code" class="form-control"  required autofocus>

      <button class="btn btn-lg btn-primary btn-block" type="submit">Sign in</button>

    </form>
  </body>
</html>
