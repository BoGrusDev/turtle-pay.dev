<?php

ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

// define ('ENV_TYPE','prod');
define ('ENV_TYPE','shop');
echo 'start';
$myMail = new TpMail();
$myMail->send();
echo 'sent';

Class TpMail {
    public function send() {
		
		require_once 'PHPMailerAutoload.php';
		
		$mail = new PHPMailer;
		$mail->isSMTP();
		
        $email = "bo.grusell@grusit.se";

		/*
			if (ENV_TYPE == 'prod') {
				$mail->Host = 'smtp.gmail.com';
				$mail->SMTPAuth = true;
				$mail->SMTPDebug = 2;
				$mail->Username = 'info.turtlepay@gmail.com';
				$mail->Password = 'SegTp_2019';
				$mail->CharSet = 'UTF-8';
				$mail->From = 'info@turtle-pay.com';
				
				// $mail->SMTPSecure = 'tcl';
				// $mail->Port = 465;
				//$email = $email;
				$mail->FromName = 'Test Turtle Pay';;
				$mail->addAddress($email);
				$mail->addBCC('bo.grus@yahoo.com');
				$mail->Subject = "Prod Mail";
				
			}
			else if (ENV_TYPE == 'tpe') {
				$mail->Host = 'smtp-mail.outlook.com';
				$mail->SMTPAuth = true;
				$mail->SMTPDebug = 2;
				$mail->Username = 'info@turtle-pay.com';
				$mail->Password = 'Xop03195';
				$mail->CharSet = 'UTF-8';
				$mail->From = 'info@turtle-pay.com';
				 $mail->SMTPSecure = "tls";
				 $mail->Port = 587;
				// $mail->SMTPSecure = 'tcl';
				//$mail->Port = 465;
				//$email = $email;
				$mail->FromName = 'Test Turtle Pay';;
				$mail->addAddress($email);
				$mail->addBCC('bo.grus@yahoo.com');
				$mail->Subject = "Prod Mail";
				
			}
			*/
			/*
			else if (ENV_TYPE == 'shop') 
				
				$mail->Host = 'mail.grus.zone';
				$mail->SMTPAuth = true;
				$mail->Username = 'infoturtle-pay.com.zone';
				$mail->Password = 'SegTp@2022';
				$mail->CharSet = 'UTF-8';
				$mail->From = 'info@turtle-pay.com';
				$mail->FromName = 'Turtle Pay';
				$mail->Port = 465;
				//$mail->SMTPDebug = 1; 
				$mail->SMTPSecure = 'ssl';
				$mail->addReplyTo('info@turtle-pay.com');
				$mail->addAddress('bo.grus@yahoo.com');
				$mail->Subject = "Test Mail shop";
			}
			// SegTp@2022
			*/
			//else {
				
		$mail->Host = 'mail.turtle-shop.se';
		$mail->SMTPAuth = true;
		$mail->Username = 'info@turtle-shop.se';
		$mail->Password = ''SegTp@2022';
		$mail->CharSet = 'UTF-8';
			$mail->From = 'info@turtle-pay.com';
		$mail->FromName = 'Demo - TurtleShop';
		$mail->Port = 465;
		//$mail->SMTPDebug = 1; 
		$mail->SMTPSecure = 'ssl';
			$mail->addReplyTo('info@turtle-pay.com');
		$mail->addAddress('bo.grus@yahoo.com');
		$mail->Subject = "Test Mail Shop";
		

		$mail->isHTML(true);
		
		//$mailInvoice->Body = $this->htmlInvoice . '<div style="width:100%; padding:20px 0 10px 0; text-align:center"><a href="' . DOCVIEW . 'o/' . $this->orderid . '.html"' . '" style="font-size:20px; font-weight:bold; color: green">Skriv ut</a>';
		$mail->Body = "Detta är test mail";

		if(!$mail->send()) {
            echo 'Error: ';
			echo $mail->ErrorInfo;
			return false;
		} else {
            echo 'OK';
			return true;
		}
	}
}