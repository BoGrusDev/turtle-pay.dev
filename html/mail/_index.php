<?php
    /*

    Mail test
*/

require 'PHPMailerAutoload.php';
$mail = new PHPMailer;
// -- $mail->isSMTP();
$mail->Host = 'postman.vmi.se';
// -- $mail->SMTPAuth = true;
$mail->Username = 'order@bappnet.se';
$mail->Password = 'se0Jo';
$mail->CharSet = 'UTF-8';
$mail->From = 'order@bappnet.se';
$mail->FromName = 'TurtlePay';
//$mail->addAddress('bo.grus@yahoo.com', "Bosse");
$mail->addAddress('bogrus90@hotmail.com', "Bosse");
//$mail->addAddress($invoiceObj->email, $invoiceObj->name);
//$mail->addAddress($data->email, $invoiceObj->name);
$mail->addBCC('bo.grus@yahoo.com');
//$mail->addReplyTo('info@turtle-pay.com');
//$mail->isHTML(true);
//$mail->AddAttachment(FIRST_INVOICE_FOLDER . $invoiceObj->invoice_filename);
$mail->Subject = "Test mail";
//$mailInvoice->Body = $this->htmlInvoice . '<div style="width:100%; padding:20px 0 10px 0; text-align:center"><a href="' . DOCVIEW . 'o/' . $this->orderid . '.html"' . '" style="font-size:20px; font-weight:bold; color: green">Skriv ut</a>';
$mail->Body = "Test Hot 99";

if(!$mail->send()) {

    echo '{"code" : "0"}';
} else {
    echo '{"code" : "1"}';
    echo $mail->ErrorInfo;
}
