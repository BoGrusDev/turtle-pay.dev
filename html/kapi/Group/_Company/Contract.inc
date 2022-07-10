<?php
/*

    BondPdf

    20200-01-09

	sudo chmod -R 777 /var/www/html/f-invoice

	{
		"_group" : "Company",
		"_action" : "Contract",
        "_user_id" : "69",
		"_operator_id" : "1", 
		"_order_ref": "2f7c201e-07d2-47d4-af12-26cd43b5cd0a"
	}	

*/

use setasign\Fpdi;
require('fpdf181/fpdf.php');
require_once('ftpi/autoload.php');


class ContractClass extends BaseClass {

	private $userId;
	private $folder;
	private $peopleId;
	private $orderRef;
	private $reply;

	public function _($data) {
		if ($this->parameterCheck($data) == false) {
			return array("code"=>"0", "denied_code"=>"parameter-fail");
		}

		$this->reply = new stdClass();
		$this->folder = 'avtal/';
		$this->pre = 'n'; // When create a new preview and store it in foretagsvillkor
		
		if ($this->pre == 'y') {
			$this->companyNameHeader = '';
			$this->companyName = '';
			$this->companyIdNumber = '';
			$this->superUserName = '';
		}
		else {
			if ($this->companyInfo() == false) {
				return array("code"=>"0", "denied_code"=>"company-not-exist");
			}
		}

        if ($this->signCollect() == false) {
            return $this->reply;
			return array("code"=>"0", "denied_code"=>"not-in-progress");
		}

		if ($this->contractCreate() == false) {
			return array("code"=>"0", "denied_code"=>"cant-create-contract");
		}

		if ($this->companySignSave() == false) {
			return array("code"=>"0", "denied_code"=>"cant-create-contract");
		}

		if ($this->contractEmail() == false) {
			$this->reply->mail_status = 'fail';
		} 
		else {
			$this->reply->mail_status = 'ok';
		}

		$this->reply->code = '1';
		return $this->reply;
	}

	private function parameterCheck($data) {
		if (isset($data->_user_id)) {
			$this->userId = trim($data->_user_id);
			if (!is_numeric($this->userId)) {
				return false;
			}
		}
		else {
			return false;
		}
		if (isset($data->_operator_id)) {
			$this->operatorId = trim($data->_operator_id);
			if (!is_numeric($this->operatorId)) {
				return false;
			}
		}
		else {
			return false;
		}
		if (isset($data->_order_ref)) {
			$this->orderRef = trim($data->_order_ref);
		}
		else {
			return false;
		}
		
		return true;
	}

	private function companyInfo() {
        $sql = "SELECT company_name, company_id_number FROM company WHERE company_id = $this->userId";
        $res = $this->_Get($sql);
        if ($res['code'] == '1') {
			$this->companyNameHeader = $res['company_name'] . ', org. nr ';
			$this->companyName = $res['company_name'];
			$this->companyIdNumber = $res['company_id_number'];
			$sql = "SELECT personal_id_number, CONCAT(first_name, ' ', last_name) AS people_name, email FROM people WHERE people_id = $this->operatorId";
			$res = $this->_Get($sql);
			if ($res['code'] == '1') {
				$this->superUserName = $res['people_name'];
				$this->email = $res['email'];
				$this->personalIdNumber = $res['personal_id_number'];
				return true;
			}
			else {
				return false;
			}
        }
        else {
            return false;
        }
    }

	private function signCollect() {
       
        $param = new StdClass();
        $param->_group  = "BankId";
        $param->_action = "SignCollect";
        $param->_order_ref =  $this->orderRef;
       
        $reply = $this->_RestApiCall($param, INTERNAL_API);
        if ($reply->code == '1') {
            $this->signature = $reply->signature;
            $this->ocspResponse = $reply->ocspResponse;
            return true;
        }
        else {
            $this->reply->code = $reply->code;
            $this->reply->denied_code = $reply->denied_code;
            return false;
        }
    }

	private function contractCreate() {

		$font = 'Helvetica';
		$extra = 0;
		
		$mall = "avtal/Turtle-Pay-AB-Avtal-om-samarbete.pdf";
		$this->filename = 'Turtle-Pay-Avtal-Samarbete-' . date('Y-m-d') . '-' . $this->userId . '.pdf';
		// require('fpdf181/fpdf.php');
		// require_once('ftpi/autoload.php');
		$pdf = new Fpdi\Fpdi();

		$pageCount = $pdf->setSourceFile($mall);
		for ($pageNo = 1; $pageNo <= $pageCount; $pageNo++) {
			$templateId = $pdf->importPage($pageNo);
			$size = $pdf->getTemplateSize($templateId);
			// $pdf->AddPage('P', array($size['width'], 310));
			$pdf->AddPage('P', array($size['width'], $size['height']));
			$pdf->useTemplate($templateId);
			$pdf->SetFont($font);
			$pdf->SetXY(12, 6); // 18
			$pdf->Image('avtal/logo.jpg', null,null,33,16); 
			if ($pageNo == 1) {
				$pdf->SetFontSize(10);
				$pdf->SetXY(36, 61);
				$pdf->Write(14, utf8_decode($this->companyNameHeader . $this->companyIdNumber . ' ("Organisationen")'));
			}
			else if ($pageNo == 7) {
				$pdf->SetFontSize(10);
				$pdf->SetXY(110, 222);
				$pdf->Write(14, utf8_decode($this->companyName));
				
				$pdf->SetFontSize(10);
				$pdf->SetXY(110, 260);
				$pdf->Write(14, utf8_decode($this->superUserName));

				$pdf->SetXY(139, 248);
				$pdf->Write(14, utf8_decode(date('Y-m-d')));

				if ($this->pre == 'n') {
					$pdf->SetXY(20, 236); // 18
					$pdf->Image('avtal/stellan-sign5.png', null,null,0,0); // 38 / 20
				}
			}

		}
		/*

			Organisationen, org.nr.] (”Organisationen”)

			$pdf->SetFont($font,'I');
			$pdf->SetFontSize(9);
			$pdf->SetXY(12, 22);
			$pdf->Write(14, utf8_decode('P.O. Box 24078'));
			$pdf->SetXY(12, 27);
			$pdf->Write(14, utf8_decode('SE-104 50 Stockholm'));
        */
				/*
			$nextRow = $nextRow + 4;
			$pdf->SetXY( 18, $nextRow);
		 	$pdf->Write(10, utf8_decode('Turtle Pay AB'));

			$nextRow = $nextRow + 8;
			$pdf->SetXY(18, $nextRow); // 18
			$pdf->Image('stellan-sign5.png', null,null,0,0); // 38 / 20

			$nextRow = $nextRow + 18;
			$pdf->SetXY( 18, $nextRow);
			$pdf->Write(10, utf8_decode('Stellan Forsberg, verkställande direktör'));
		*/
		
		try {
			
			$pdf->Output($this->folder . $this->filename, 'F');
			return true;
		}
		catch(Exception $e) {
			return false;
			//echo 'Message: ' .$e->getMessage();
		}
	}

	private function companySignSave() {
		$param = new stdClass();
		$param->company_id = $this->userId;
		$param->people_id = $this->operatorId;
		$param->personal_id_number = $this->personalIdNumber;
		$param->company_contract_id = '3';
		$param->signature = $this->signature;
		$param->ocspResponse = $this->ocspResponse;
		$res = $this->_Insert('company_sign', $param);
		if ($res['code'] == "1" ) {
			return true;
		}
		else {
			return false;
		}
	}

	private function contractEmail() {
		
		$toSubject = "Avtal om samarbete och personuppgiftsbiträde";
		$html = '';
		$html .= '<div style="width:780px; margin: 10px 4px 0; font-family: Helvetica,Arial,sans-serif, Verdana; padding:6px">';
			$html .= '<p>Hej ' . $this->superUserName . ',</p>';
			$html .= '<p>' . 'Här kommer ditt exemplar av undertecknat avtal om samarbete och personuppgiftsbiträde för ' . $this->companyName . '.</p>';
			$html .= '<p>Med vänlig hälsning' . '</p>';
			$html .= '<p>Turtle Pay AB' . '</br>'; 
			$html .= 'P.O. Box 24078' . '</br>';
			$html .= 'SE-104 50 Stockholm' . '</br>';
			$html .= 'Tel. 08-80 62 20' . '</br>';
			$html .= 'www.turtle-pay.com'  . '</p>';
		
		$html .= '</div>';

		// echo $html;
		// die('');
		// return;
		
		require_once 'PHPMailerAutoload.php';
		
		$mail = new PHPMailer;
		$mail->isSMTP();
		
		if (ENV_TYPE == 'prod') {
			$mail->Host = 'smtp.gmail.com';
			$mail->SMTPAuth = true;
			$mail->Username = 'info.turtlepay@gmail.com';
			$mail->Password = 'SegTp_2019';
			$mail->CharSet = 'UTF-8';
			$mail->From = 'info@turtle-pay.com';
			$mail->addAddress($this->email, $this->superUserName);
			// $mail->addBCC('bo.grus@yahoo.com');
			$mail->addBCC('stellan.forsberg@turtle-pay.com');
			$mail->addReplyTo('info@turtle-pay.com');
			$mail->FromName = 'Turtle Pay';
			$mail->addAddress($this->email);
			$mail->addBCC('bo.grusell@turtle-pay.com');
			$mail->addReplyTo($this->emailemail_report);
		}
		else {
			$mail->Host = 'mail.grus.zone';
			$mail->SMTPAuth = true;
			$mail->Username = 'demo@grus.zone';
			$mail->Password = 'Test@2021';
			$mail->CharSet = 'UTF-8';
			$mail->From = 'demo@grus.zone';
			$mail->FromName = 'Demo - TurtlePay';
			$mail->Port = 465;
			//$mail->SMTPDebug = 1; 
			$mail->SMTPSecure = 'ssl';
			$mail->addReplyTo('demo@grus.zone');
			$mail->addAddress('bo.grus@yahoo.com');
		}
		$mail->isHTML(true);
		$mail->Subject = $toSubject;
		$mail->Body = $html;
		// echo CONTRACT_FOLDER . $this->filename;
		// return false;
		$mail->AddAttachment(CONTRACT_FOLDER . $this->filename);
		if(!$mail->send()) {
			//echo $mail->ErrorInfo;
			return false;
		} else {
			return true;
		}
	}

}

?>
