<?php
/** 
    SendClass
   
    Used by:
        Email.class
        Event.class

    {
    "_group": "Email",
    "_action": "Send",
    "_email": "bo.grus@yahoo.com",
    "_subject": "Test - VMI 3",
    "_body": "Test API",
    "_reciever": "bo.grusell@turtle-pay.com",
    "_from_email": "bosse@turtle-pay.se",
    "_from_name": "Storbolaget",
    "_bcc": "bo.grusell@turtle-pay.com",
    "_reply_to": "bo.grusell@grusit.se",
    "_attach": [
        "../finvoice/12344422395-44924581-F871-F668-A598-346A2BF2F26C.pdf",
        "../finvoice/12344422394-BD290642-6A4F-9D9E-864C-1E0F8B799E7C.pdf"
    ]
}



	{
		"_group" : "Email",
		"_action" : "Send",
        "_email" : "bo.grus@yahoo.com",
         "_subject" : "Test ny email"
        "_body" : "Test av body"
    }

        "_reciever" : "",
        "_from_email" : "".
        "_from_name" : "",
        "_bcc" : "bo.grusell@turtle-pay.com",
        "_reply_to" : "bo.grusell@grusit.se",
        "_attach" : [
            {
                
            }
        ]
        }
    
	}	

*/
ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

class SendClass {

    private $email;
    private $reciever;
    private $from; // from_email
    private $from_name;
    private $reply_to;
    private $bcc;
    private $subject;
    private $body;
    
    private $defaultFrom;
    private $defaultFromName;
    private $defaultReplyTo;
    private $defaultBcc;
    public function _($data) {
        
        $this->defaultFromEmail = 'info@turtle-pay.com';
        $this->defaultFromName = 'Turtle Pay';
        $this->defaultReplyTo = 'info@turtle-pay.com';
        $this->defaultBcc = 'bo.grusell@turtle-pay.com';
        
        if ($this->parameterCheck($data) == false) {
            return array("code"=>"2");
        }
       
        $reply = new stdClass();
        if ($this->emailSend()) {
            $reply->code = '1';
        }
        else {
            $reply->code = '0';
        }

        return $reply;

        //return $this->peopleInfoFromSpar;
    }

	private function parameterCheck($data) {
		
		if (isset($data->_email)) {
			$this->email = trim($data->_email);
		}
		else {
			return false;
		}

        if (isset($data->_reciever)) {
			$this->reciever = trim($data->_reciever);
		}
		else {
			$this->reciever = '';
		}

        if (isset($data->_from_email)) {
			$this->from = trim($data->_from_email);
		}
		else {
			$this->fromEmail  = $this->defaultFromEmail;
		}

        if (isset($data->_from_name)) {
			$this->fromName = trim($data->_from_name);
		}
		else {
			$this->fromName  = $this->defaultFromName;
		}

        if (isset($data->_reply_to)) {
			$this->replyTo = trim($data->_reply_to);
		}
		else {
			$this->replyTo  = $this->defaultReplyTo;
		}

        if (isset($data->_bcc)) {
			$this->bcc = trim($data->_bcc);
		}
		else {
			$this->bcc  = $this->defaultBcc;
		}

        if (isset($data->_subject)) {
			$this->subject = trim($data->_subject);
		}
		else {
			return false;
		}

        if (isset($data->_body)) {
			$this->body = trim($data->_body);
		}
		else {
			return false;
		}
        if (isset($data->_attach)) {
			$this->attach = $data->_attach;
		}
		else {
			$this->attach = false;
		}
		return true;
	}


    private function emailSend() {

       //  print_r($this->attach); die('');


        require 'PHPMailerAutoload.php';
		$mail = new PHPMailer;
		$mail->isSMTP();
        $mail->isHTML(true);
        $mail->SMTPDebug = 2;

        
        $mail->Host = 'smtp.net.vmi.se';
        //$mail->Host = 'smtp.gmail.com';
        $mail->SMTPAuth = true;
        $mail->Username = 'turtlepaycom';
        $mail->Password = 'Kajk48Vaa'; // SegTp@2022';
        $mail->CharSet = 'UTF-8';
        $mail->Port = 465; // 465
        $mail->SMTPSecure = 'ssl';
        
        /*
         // infi@turtle-pay.se
         $mail->Host = 'smtp-relay.gmail.com';
         //$mail->Host = 'smtp.gmail.com';
         $mail->SMTPAuth = true;
         $mail->Username = 'info@turtle-pay.se';
         $mail->Password = 'gwqnwycxjmjmncry'; // SegTp@2022';
         $mail->CharSet = 'UTF-8';
         $mail->Port = 465;
         $mail->SMTPSecure = 'ssl';
        */

        /*
        // turtle-shop.se
            $mail->Host = 'mail.turtle-shop.se';
            $mail->SMTPAuth = true;
            $mail->Username = 'info@turtle-shop.se';
            $mail->Password = 'SegTp@2022';
            $mail->CharSet = 'UTF-8';
            $mail->Port = 465;
            $mail->SMTPSecure = 'ssl';
        */

        //echo $this->fromEmail; die('');

		$mail->From = $this->fromEmail;
		$mail->FromName = $this->fromName;
		$mail->addAddress($this->email);
		$mail->addReplyTo($this->replyTo);
		$mail->addBCC($this->bcc);
		$mail->Subject = $this->subject;
        $mail->Body = $this->body;

        if ($this->attach) {
            for ($i=0; $i<sizeof($this->attach); $i++) {
                $mail->AddAttachment($this->attach[$i]);
            }
        }
       // print_r($this->replyTo); die('');

		if($mail->send()) {
			return true;
		} else {
            // echo $mail->ErrorInfo;
			return false;
		}

   }
   /*
   private function emailLogWrite() {

    $param = new stdClass();
    //@sqlINSERT INTO `
    $param->email_log = '';
    $param->email_log_id = '';
    $param->email_type = '';
    $param->company_id = '';
    $param->people_id = '';
    $param->send_date = '';
    $param->send_status = '';
    // $param->resent= 0;
    $param->_group= '';
    $param->_action= '';
    $param->from_email= '';
    $param->from_name= '';
    $param->email= '';
    $param->reciever= '';
    $param->reply_to= '';
    $param->bcc = '';
    $param->subject = '';
    $param->body = '';
    }
    */
}

/*

email-log



*/