<?php
/*
    PrizeListClass
   	

	https://app.equipe.com/organizers/515/meetings.json

	
	{
		"_group" : "Tdb",
		"_action" : "PrizePayout",
        "_event_id" : "636",
        "_event_name" : "Hjätat 2022-03-02",
        "_user_name" : "Test"
		"_user_id" : "69",
        "_operator_id" : "1",
        "_eco_record" : "1744,1912,1916,2160",
        "_eco_not_paid" : "1333"
	}	

    ALTER TABLE `btrans` ADD `event_id` INT NOT NULL DEFAULT '0' AFTER `company_id`; 

*/
require_once 'Group/Tdb/TdbBase.inc';

class PrizePayoutClass extends TdbBaseClass {

    private $userId;
	private $operatorId;
    private $eventId; 
    private $storeId;
    private $ecoRecord;
    private $premiePaid;
    public function _($data) {

        // echo json_encode($data);
        // die('');

		if ($this->parameterCheck($data) == false) {
			return array("code"=>"0","denide_code"=>"param-fail");
		}
        $this->mailList = array();
        $counter = $this->payout();
        if (sizeof($this->mailList) > 0) {
            $this->emailNotification();
        }

        $reply = new stdClass();
        $reply->code = '1';
        $reply->counter = $counter;
        $reply->premie_not_paid = $this->premieNotPaid;
        $reply->premie_paid = $this->premiePaid;
        $reply->mail_list = $this->mailList;
        return $reply;
	}

	private function parameterCheck($data) {
		
		if (isset($data->_user_id)) {
			$this->userId = trim($data->_user_id);
		}
		else {
			return false;
		}
        if (isset($data->_operator_id)) {
			$this->operatorId = trim($data->_operator_id);
		}
		else {
			return false;
		}
        if (isset($data->_event_id)) {
			$this->eventId = trim($data->_event_id);
		}
		else {
			return false;
		}
        if (isset($data->_event_name)) {
			$this->eventName = trim($data->_event_name);
		}
		else {
			return false;
		}
        if (isset($data->_user_name)) {
			$this->companyName = trim($data->_user_name);
		}
		else {
			return false;
		}
        if (isset($data->_store_id)) {
			$this->storeId = trim($data->_store_id);
		}
		else {
			return false;
		}
        if (isset($data->_eco_record)) {
			$this->ecoRecord = $data->_eco_record;
		}
        else {
			return false;
		}
        return true;
	}

    private function payout() {
        
        $this->premiePaid = 0;
        $this->premieNotPaid = 0;

        $sql = "SELECT ";
        $sql .= "e.tdb_eco_id, e.tdb_people_id, e.rnr, e.realrnr, e.competition_no, e.total ";
        $sql .= "FROM tdb_eco e ";
        $sql .= "WHERE e.tdb_eco_id IN ($this->ecoRecord) AND action='priz' ";
        $sql .= "ORDER BY e.rnr, e.tdb_people_id, e.competition_no";
        $ecoList = $this->_GetList($sql);
       
        for ($i=0; $i<sizeof($ecoList); $i++) {
            $sql = "SELECT item_code FROM tdb_people ";
            $sql .= "WHERE rnr = " . $ecoList[$i]['rnr'] . " AND action = 'sign' AND event_id = $this->eventId ";
            $sql .= "ORDER BY tdb_people_id DESC LIMIT 1";
            $tdbPeople = $this->_Get($sql);
            if ($tdbPeople['code'] == '1') {
                $itemCode = $tdbPeople['item_code'];
            }
            else {
                //$this->_ecoSetAction($ecoList[$i]['tdb_eco_id'], 'prix');
                //$this->premieNotPaid++;
                continue;
            }
            
            $sql = "SELECT ei.people_id, ei.people_name, ei.credit_id, ei.email ";
            $sql .= "FROM invoice_event_item i, event_item_v4 ei ";
            $sql .= "WHERE i.invoice_event_item_code = '$itemCode' ";
            $sql .= "AND i.event_item_id = ei.event_item_id";
            //echo $sql; die('');
            $item = $this->_Get($sql);
            
            if ($item['code'] == '1') {
                $peopleId = $item['people_id'];
                $peopleName = $item['people_name'];
                $creditId = $item['credit_id'];
                $email = $item['email'];
                $amount = (float) $ecoList[$i]['total'] * -1;
    
                $this->booking = new stdClass();
                $this->_bookingPrize($peopleId);
                $this->booking->_trans = [];
                $this->_transPrize($peopleId, $amount);
                // print_r($this->booking);   
                if ($this->_booking($this->booking) > 0) {
                    $this->_ecoSetAction($ecoList[$i]['tdb_eco_id'], 'pric');
                    $this->premiePaid++;
                }
                else {
                    $this->_ecoSetAction($ecoList[$i]['tdb_eco_id'], 'prix');
                    $this->premieNotPaid++;
                }
                $this->emailListAdd($peopleId);
            }
            else {
                $this->_ecoSetAction($ecoList[$i]['tdb_eco_id'], 'prix');
                $this->premieNotPaid++;
                continue;
            }    
        }
        return sizeof($ecoList);
    }
   
    private function _ecoSetAction($ecoId, $action) {
        $param = new stdClass();
        $param->action = $action;
        $this->_Update('tdb_eco', 'tdb_eco_id', $ecoId, $param);
    }

    private function _bookingPrize($peopleId) {
        $this->booking->people_id = $peopleId;
        $this->booking->booking_date = date("Y-m-d");
        $this->booking->booking_text = 'Premium';
        $this->booking->booking_type = 'prize';
        $this->booking->company_id = $this->userId;
        $this->booking->receipt_number = 'Premie - ' . $this->eventName;
        $this->booking->sales_person_people_id = $this->operatorId;
        $this->booking->store_id = $this->storeId;
        $this->booking->cr_id = '1';
    }

    private function _transPrize($peopleId, $amount) {
        $this->booking->_trans[] = new stdClass();
        $index = sizeof($this->booking->_trans) - 1;
        $this->booking->_trans[$index]->trans_type = 'prize'; // 'pcredit';
        $this->booking->_trans[$index]->account_no = '1680'; 
        $this->booking->_trans[$index]->amount = -$amount;
        $this->booking->_trans[$index]->people_id = $peopleId;
        $this->booking->_trans[$index]->company_id = $this->userId;
        $this->booking->_trans[$index]->event_id = $this->eventId;
        $this->booking->_trans[] = new stdClass();
        $index++;
        $this->booking->_trans[$index]->trans_type =  'prize';  // 'pcredit';
        $this->booking->_trans[$index]->account_no = '2981'; 
        $this->booking->_trans[$index]->amount = $amount;
        $this->booking->_trans[$index]->people_id = $peopleId;
        $this->booking->_trans[$index]->company_id = $this->userId;
        $this->booking->_trans[$index]->event_id = $this->eventId;
        
    }

	private function _booking($data) {

		$balance = 0;
		for ($i=0; $i<sizeof($data->_trans); $i++) {
			$balance =  $balance + $data->_trans[$i]->amount;
		}
		$balance = round($balance, 2);
		$reply = $this->_Insert('booking', $data );

		if ($reply['code'] =! "0") {
			$bookingId = $reply['id'];
			for ($i=0; $i<sizeof($data->_trans); $i++) {
				$data->_trans[$i]->booking_id = $bookingId;
				$this->_Insert('btrans', $data->_trans[$i]);
			}
			if ($balance != 0) {
				$trans = new stdClass();
				$trans->trans_type = "equaliz";
				$trans->account_no = '8193';
				$trans->amount = $balance;
				$this->_Insert('btrans', $trans);
			}
		} else {
			// Error with save Booking
			$reply['code'] = 0;
		}

		return (int) $reply['id'];
	}

    private function emailListAdd($peopleId) {
        $mailExist = false;
        if (sizeof($this->mailList) > 0) {
            for ($i=0; $i<sizeof($this->mailList); $i++) {
                if ($this->mailList[$i] == $peopleId) {
                    $mailExist = true;
                }
            }
        }
        if ($mailExist == false) {
            array_push($this->mailList, $peopleId);
        }
    }

    private function emailNotification() {
		
        for ($i= 0; $i<sizeof($this->mailList); $i++) {
		    $peopleId = $this->mailList[$i];
		
		    $sql = "SELECT CONCAT(first_name, ' ', last_name) AS people_name, email ";
		    $sql .= "FROM people ";
		    $sql .= "WHERE people_id = " .  $peopleId ;
		    $people = $this->_Get($sql);
		
		    $subject = 'Premie från ' . $this->eventName;

            $body = 'Hej ' . $people['people_name'] . ',';
            $body .= '<br><br>';

            $body .= 'Grattis till premien för er prestation i ' . $this->eventName . '!';
            $body .= '<br><br>'; 

            $body .= 'För att betala ut premien behöver du logga in på www.turtle-pay.com/logga-in med ditt BankID och ange dina bankuppgifter.';
            $body .= '<br><br>'; 

            $body .= 'När du är inloggad ser du även alla transaktioner och ditt saldo.';
            $body .= '<br><br>'; 

            $body .= 'Mejla därefter till info@turtle-pay.com och meddela att du vill få premien utbetalat, så ordnar Turtle Pay en banköverföring till dig.';
            $body .= '<br><br>'; 

            $body .= 'Har du fakturor kvar att betala kan du även dra av premiebeloppet mot fakturabeloppet och bara betala mellanskillnaden.';
            $body .= '<br><br>'; 

            $body .= 'Med vänlig hälsning,';
            $body .= '<br><br>';
            
            $body .= $this->companyName;

            $htmlBody = '';
            $htmlBody .= '<div style="width:780px; margin: 10px auto 0; font-family: Helvetica,Arial,sans-serif, Verdana; padding:6px">';
            $htmlBody .= '<p>' . $body . '</p>';          
            $htmlBody .= '</div>';

    		require_once 'PHPMailerAutoload.php';
            $mail = new PHPMailer;
            $mail->isSMTP();
            
            /*
            if (ENV_TYPE == 'prod') {
                
                $mail->Host = 'smtp.gmail.com';
                $mail->SMTPAuth = true;
                $mail->Username = 'info.turtlepay@gmail.com';
                $mail->Password = 'SegTp_2019';
                $mail->CharSet = 'UTF-8';
                $mail->From = 'info@turtle-pay.com';
            
                $mail->FromName = $this->companyName;
                $mail->addAddress($people['email']);
                $mail->addBCC('bo.grusell@turtle-pay.com');
                $mail->addReplyTo($this->companyEmail);
                
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
            */

            $mail->Host = 'mail.turtle-shop.se';
            $mail->SMTPAuth = true;
            $mail->Username = 'info@turtle-shop.se';
            $mail->Password = 'SegTp@2022';
            $mail->CharSet = 'UTF-8';
            $mail->From = 'info@turtle-pay.com';
            $mail->FromName = 'Turtle Pay';
            $mail->Port = 465;
            $mail->SMTPSecure = 'ssl';
            $mail->From = 'info@turtle-pay.com';
            $mail->FromName = $from;
            $mail->FromName = $this->companyName;
            
            $mail->addAddress($people['email']);
            $mail->addBCC('info@turtle-shop.se');
            $mail->addReplyTo($this->companyEmail);


		    $mail->isHTML(true);
		    $mail->Subject = $subject;
            $mail->Body = $htmlBody;

            if(!$mail->send()) {
                //echo $mail->ErrorInfo;
                // return false;
            } else {
			    // return true;
		    }
        }
	}

}