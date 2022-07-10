<?php
    /*

    Mail test
*/
date_default_timezone_set("Europe/Stockholm");
require 'PHPMailerAutoload.php';
$mail = new PHPMailer;
$mail->isSMTP();
$mail->Port = 587; 

$mail->SMTPSecure = 'tls';
//$mail->Host = 'exchange.s.thehostingplatform.com';
$mail->Host = 'smtp.gmail.com';
$mail->SMTPAuth = true;
$mail->SMTPDebug = 2;
//$mail->Username = 'bogrus90@gmail.com';
//$mail->Password = "segdeg99";
$mail->Username = 'info.turtlepay@gmail.com';
$mail->Password = "SegTp_2019";

//$mail->Username = 'info@turtle-pay.com';
//$mail->Password = 'Mlif@2018';
$mail->CharSet = 'UTF-8';
$mail->From = 'info@turtle-pay.com';
$mail->FromName = 'TurtlePay';
$mail->addAddress('bo.grus@yahoo.com', "Bosse");
$mail->addAddress('bogrus90@hotmail.com', "Bosse");

$mail->addBCC('bo.grusell@turtle-pay.com');
//$mail->addReplyTo('info@turtle-pay.com');
$mail->isHTML(true);
//$mail->AddAttachment(FIRST_INVOICE_FOLDER . $invoiceObj->invoice_filename);
$mail->Subject = "Gmail Test Hot 2000";
//$mailInvoice->Body = $this->htmlInvoice . '<div style="width:100%; padding:20px 0 10px 0; text-align:center"><a href="' . DOCVIEW . 'o/' . $this->orderid . '.html"' . '" style="font-size:20px; font-weight:bold; color: green">Skriv ut</a>';
$mail->Body = "Gmail Info Mail Hot 2000";

if(!$mail->send()) {

    echo '{"code" : "0"}';
    echo $mail->ErrorInfo;
} else {
    echo '{"code" : "1"}';
   
}
