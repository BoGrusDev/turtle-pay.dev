<?php
/*
    CreditingClass
   	

	https://app.equipe.com/organizers/515/meetings.json

    ALTER TABLE event_option ADD tdb_eco_id INT NOT NULL DEFAULT '0' AFTER event_option_status; 
	
    ALTER TABLE TP_prod_grusit.event_option ADD INDEX (tdb_eco_id); 

    {
		"_group" : "Tdb",
		"_action" : "Crediting",
        "_event_id" : "663",
        "_event_name" : "Folksam Ponnyallsvenskan omg 2",
		"_user_id" : "138",
        "_operator_id" : "1"
	}	

	{
		"_group" : "Tdb",
		"_action" : "Crediting",
        "_event_id" : "671",
        "_event_name" : "Vårhoppet 2022",
		"_user_id" : "139",
        "_operator_id" : "1"
	}	
    
    {
		"_group" : "Tdb",
		"_action" : "Crediting",
        "_event_id" : "660",
        "_event_name" : "Majhoppet 30 april - 1 maj",
		"_user_id" : "140",
        "_operator_id" : "1"
	}	

    {
		"_group" : "Tdb",
		"_action" : "Crediting",
        "_event_id" : "674",
        "_event_name" : "Dressyr Ponny 2022-05-08",
		"_user_id" : "127",
        "_operator_id" : "1"
	}	

    {
		"_group" : "Tdb",
		"_action" : "Crediting",
        "_event_id" : "673",
        "_event_name" : "Dressyr Häst 2022-05-07",
		"_user_id" : "127",
        "_operator_id" : "1"
	}	

     {
		"_group" : "Tdb",
		"_action" : "Crediting",
        "_event_id" : "675",
        "_event_name" : "Vårdressyr häst 8 maj",
		"_user_id" : "140",
        "_operator_id" : "1"
	}	

    {
		"_group" : "Tdb",
		"_action" : "Crediting",
        "_event_id" : "682",
        "_event_name" : Norrvidinge Pony Show 21-22 maj 22",
		"_user_id" : "120",
        "_operator_id" : "1"
	}	

    // Huvudsta

    {
		"_group" : "Tdb",
		"_action" : "Crediting",
        "_event_id" : "680",
        "_event_name" : "Ponny och Hästhoppning 21 maj",
		"_user_id" : "127",
        "_operator_id" : "1"
	}	

    {
		"_group" : "Tdb",
		"_action" : "Crediting",
        "_event_id" : "696",
        "_event_name" : "Fälttävlan 2022",
		"_user_id" : "140",
        "_operator_id" : "1"
	}	



    {
    "crediting": 3,
    "mailed": 2,
    "removed": 19,
    "maillist": [
        2314,
        4557
    ],
    "code": "1"
}

*/
require_once 'Group/Tdb/TdbBase.inc';

class CreditingClass extends TdbBaseClass {

    private $userId;
	private $operatorId;
    private $eventId; 
    private $booking;
    private $mailList;
    private $reply;
    
    public function _($data) {

		if ($this->parameterCheck($data) == false) {
			return array("code"=>"0","denide_code"=>"param-fail");
		}

        if ($this->companyInfo() == false) {
			return array("code"=>"0","denide_code"=>"company-info-missing");
		}

        /*
            // Test för email notification
            $this->mailList = array();
            $this->emailListAdd('1');
            $this->emailNotification();
            die('');
        */

        // Intit value for reply
        $this->reply = new stdClass();
        $this->reply->crediting = 0;
        $this->reply->mailed = 0;
        $this->reply->removed = 0;
        $this->mailList = array();
     
        $this->creditingSign();

        $this->creditingNotCollected();

        $this->invoiceEventEmpty();
              

        $this->emailNotification();
        
        $this->reply->maillist = $this->mailList;
        $this->reply->mailed = sizeof($this->mailList);
        $this->reply->code = '1';
        return $this->reply;
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
        return true;
	}

    private function companyInfo() {

        $sql = "SELECT company_name, known_as, email, wa_store_id ";
		$sql .= "FROM company ";
		$sql .= "WHERE company_id = " .  $this->userId;
		$res = $this->_Get($sql);
        if ($res['code'] == '1') {
            $this->companyName = $res['known_as'];
            $this->companyEmail = $res['email'];
            $this->storeId =  $res['wa_store_id'];
            return true;
        }
        else {
            return false;
        }
    }

    private function creditingSign() {
            
        $sql = "SELECT ";
        $sql .= "e.event_id, e.tdb_eco_id, e.tdb_people_id, p.rnr, e.realrnr, e.competition_no, e.total, e.event_option_setting_id, ";
        $sql .= "p.item_code, p.action ";
        $sql .= "FROM tdb_eco e, tdb_people p ";
        $sql .= "WHERE e.tdb_people_id = p.tdb_people_id AND ";
        $sql .= "e.action = 'cre' AND p.action = 'sign' AND ";
        $sql .= "e.event_id = $this->eventId ";
        $sql .= "ORDER BY e.rnr, e.tdb_people_id, e.competition_no";
        // echo $sql; die('');
        $list = $this->_GetList($sql);

       //  print_r($list); die('');

        if (sizeof($list) > 0) {
            for ($i=0; $i<sizeof($list); $i++) {
                // Get info 
                $sql = "SELECT e.people_id, e.credit_id, e.event_item_id ";
                $sql .= "FROM invoice_event_item i, event_item_v4 e ";
                $sql .= "WHERE invoice_event_item_code = '" . $list[$i]['item_code'] . "' AND ";
                $sql .= "i.event_item_id = e.event_item_id";
                $resEventItem = $this->_Get($sql);

                //print_r($list);
                //print_r($resEventItem);
                //die('');

                if ($resEventItem['code'] == '1') {
                    $peopleId = $resEventItem['people_id'];
                    $creditId = $resEventItem['credit_id'];
                }
                else {
                    // Should not happend
                    continue;
                }
                $amount = (float) $list[$i]['total']; //  * -1;
                // $amount = 700;
                $this->booking = new stdClass();
                $this->bookingPcreding($peopleId, $creditId);
                $this->booking->_trans = [];
                $this->transCredit($peopleId, $amount, $creditId);
                if ($this->peopleOverDueCheck($peopleId) < 0 || $this->creditCloseCheck($creditId)) {
                    $this->transInternal($peopleId, $amount, $creditId);
                }
                else {
                    $creditBalance = $this->creditBalanceGet($creditId);
                    if ($creditBalance - $amount < 0) {
                        $this->transInternal($peopleId, ($creditBalance - $amount) * -1 , $creditId);
                    }
                }
            
                // if ($creditBalance) 
                // print_r($this->booking);
                if ($this->booking($this->booking) > 0) {
                    if ($this->creditBalanceGet($creditId) == 0) {
                        $this->creditClose($creditId);
                    }
                    
                    $this->tdbEcoStatusSet($list[$i]['tdb_eco_id'], 'crec');
                    $this->optionCredit($list[$i]['tdb_eco_id']);
                    $this->reply->crediting++; 
                    $this->emailListAdd($peopleId);
                }    
                else {
                    // echo 'Fail';
                }
            }
        }
    }

    private function creditingNotCollected() {
        /*
            Get item frpm not collected 
        */
        $sql = "SELECT ";
        $sql .= "e.event_id, e.tdb_eco_id, e.tdb_people_id, p.rnr, e.realrnr, e.competition_no, e.total, e.event_option_setting_id, ";
        $sql .= "p.item_code, p.action ";
        $sql .= "FROM tdb_eco e, tdb_people p ";
        $sql .= "WHERE e.tdb_people_id = p.tdb_people_id AND ";
        $sql .= "e.action = 'cre' AND p.action = 'inv' AND ";
        $sql .= "e.event_id = $this->eventId ";
        $sql .= "ORDER BY e.rnr, e.tdb_people_id, e.competition_no";
        $list = $this->_GetList($sql);
        if (sizeof($list) > 0) {
            for ($i=0; $i<sizeof($list); $i++) {        
                $this->tdbEcoStatusSet($list[$i]['tdb_eco_id'], 'crex');
                $this->reply->removed++;
            }
        }
    }

    private function invoiceEventEmpty() {
        $sql = "SELECT p.tdb_people_id, p.item_code ";
        $sql .= "FROM tdb_eco e, tdb_people p ";
        $sql .= "WHERE 	e.action = 'crex' AND ";
        $sql .= "e.tdb_people_id = p.tdb_people_id AND ";
        $sql .= "e.event_id = $this->eventId AND p.event_id = $this->eventId AND p.action = 'inv' ";
        $sql .= "GROUP BY p.tdb_people_id ";
        $list = $this->_GetList($sql);
        if (sizeof($list) > 0) {
            for ($i=0; $i<sizeof($list); $i++) {        
                $sql = "SELECT COUNT(*) as counter FROM tdb_eco WHERE tdb_people_id = " . $list[$i]['tdb_people_id'];
                $sql .= " AND action = 'inv'";
                $res = $this->_Get($sql);
                if ($res['code'] == '1') {
                    if ((int) $res['counter'] == 0) {
                        // Update InvoiceEventItem
                        $param = new stdClass();
                        $param->invoice_event_item_status = 'm';
                        $resUpdate = $this->_Update('invoice_event_item', 'invoice_event_item_code', $list[$i]['item_code'], $param);
                        
                        // Update tdb_people
                        $param2 = new stdClass();
                        $param2->action = 'crex';
                        $resUpdate2 = $this->_Update('tdb_people', 'tdb_people_id', $list[$i]['tdb_people_id'], $param2);
                    }
                }
            }
        }

        // print_r($listCounter);
               
    }

    private function bookingPcreding($peopleId, $creditId) {
        $this->booking->people_id = $peopleId;
        $this->booking->booking_date = date("Y-m-d");
        $this->booking->booking_text = 'Credit';
        $this->booking->booking_type = 'pcrediting';
        $this->booking->company_id = $this->userId;
        $this->booking->receipt_number = 'Kreditering - ' . $this->eventName;
        $this->booking->sales_person_people_id = $this->operatorId;
        $this->booking->store_id = $this->storeId;
        $this->booking->cr_id = '1';
        $this->credit_id = $creditId;
    }

    private function transCredit($peopleId, $amount, $creditId) {
        $this->booking->_trans[] = new stdClass();
        $index = sizeof($this->booking->_trans) - 1;
        $this->booking->_trans[$index]->trans_type = 'pcredit'; // 'pcredit';
        $this->booking->_trans[$index]->account_no = '1380'; 
        $this->booking->_trans[$index]->amount = -$amount;
        $this->booking->_trans[$index]->people_id = $peopleId;
        $this->booking->_trans[$index]->company_id = $this->userId;
        $this->booking->_trans[$index]->credit_id = $creditId;
        
        $this->booking->_trans[] = new stdClass();
        $index++;
        $this->booking->_trans[$index]->trans_type =  'pcredit';  // 'pcredit';
        $this->booking->_trans[$index]->account_no = '2981'; 
        $this->booking->_trans[$index]->amount = $amount;
        $this->booking->_trans[$index]->people_id = $peopleId;
        $this->booking->_trans[$index]->company_id = $this->userId;
        $this->booking->_trans[$index]->credit_id = $creditId;
    }

    private function transInternal($peopleId, $amount, $creditId) {
        $this->booking->_trans[] = new stdClass();
        $index = sizeof($this->booking->_trans) - 1;
        $this->booking->_trans[$index]->trans_type = 'intern'; // 'pcredit';
        $this->booking->_trans[$index]->account_no = '1680'; 
        $this->booking->_trans[$index]->amount = -$amount;
        $this->booking->_trans[$index]->people_id = $peopleId;
        $this->booking->_trans[$index]->credit_id = $creditId;
        
        $this->booking->_trans[] = new stdClass();
        $index++;
        $this->booking->_trans[$index]->trans_type =  'intern';  // 'pcredit';
        $this->booking->_trans[$index]->account_no = '1380'; 
        $this->booking->_trans[$index]->amount = $amount;
        $this->booking->_trans[$index]->people_id = $peopleId;
        $this->booking->_trans[$index]->credit_id = $creditId;
    }

    private function booking($data) {

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

    private function creditBalanceGet($creditId) {
        $sql= "SELECT SUM(amount) AS balance FROM btrans ";
        $sql .= " WHERE account_no = '1380' AND prel IN ('n') AND credit_id = " .  $creditId;
        // echo $sql; die('');
        $res = $this->_Get($sql);
        if ($res['code'] == '1') {
            return (float) $res['balance'];  
        }
        else {
            return 0;
        }
    }
    
    private function creditCloseCheck($creditId) {
        $sql = "SELECT credit_status FROM credit WHERE credit_id = " .  $creditId;
        $res = $this->_Get($sql);
        // echo $sql; die('');
        if ($res['credit_status'] == 'c') {
           return true;
        }
        else {
            return false;
        }
    }

    private function creditClose($creditId) {
        $param = new stdClass();
		$param->credit_status = 'c';
		$this->_Update('credit', 'credit_id', $creditId, $param);
    }

    private function peopleOverDueCheck($peopleId) {
        $sql = "SELECT SUM(t.amount) AS balance ";
        $sql .= "FROM btrans t, booking b WHERE t.account_no = '1680' AND ";
        $sql .= "t.prel = 'n' AND ";
        $sql .= "t.people_id = $peopleId AND t.booking_id = b.booking_id";
       
        $res = $this->_Get($sql);
        if (is_null($res['balance'])) {
                return 0;
        }
        else {
            //return 0;
            return $res['balance'];
        }
    }

    private function tdbEcoStatusSet($tdbEcoId, $status) {
        $param = new stdClass();
        $param->action = $status; // Credit complete for eco 
        $this->_Update('tdb_eco', 'tdb_eco_id', $tdbEcoId, $param);
    }

    private function optionCredit($tdbEcoId) {
        $sql = "UPDATE event_option SET value = 0, event_option_status = 'r' ";
        $sql .="WHERE tdb_eco_id = $tdbEcoId AND event_option_status = 'c'"; 
        $res = $this->_Query($sql);
    }

    private function tdbEcoOptionMatch($eventItemId, $tdbEcoId) {
        $sql = "SELECT event_participant_id, first_name, last_name, note FROM event_participant ";
        $sql .= "WHERE event_item_id = $eventItemId AND event_participant_status = 'c'";
        $partList = $this->_GetList($sql);
        print_r($partList);
        $sql = "SELECT * FROM tdb_eco ";
        $sql .= "WHERE tdb_eco_id = $tdbEcoId" ;
        $item = $this->_Get($sql);
        print_r($item);
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
		
        if (sizeof($this->mailList) < 1) {
            // If list empty
            return false;
        }
       
        for ($i= 0; $i<sizeof($this->mailList); $i++) {
		    $peopleId = $this->mailList[$i];
		
		    $sql = "SELECT CONCAT(first_name, ' ', last_name) AS people_name, email ";
		    $sql .= "FROM people ";
		    $sql .= "WHERE people_id = " .  $peopleId ;
		    $people = $this->_Get($sql);
		
		    $subject = 'Kreditering från ' . $this->companyName;


            $body = 'Hej ' . $people['people_name'] . ',';
            $body .= '<br><br>';
            $body .= 'Vi har krediterat dig idag. ';

            $body .= 'Om du fått ett tillgodohavande efter krediteringen och önskar få det utbetalat till dig behöver du logga in på ';
            $body .= '<a href="https://www.turtle-pay.com/logga-in">www.turtle-pay.com/logga-in</a>'; 
            $body .= ' med ditt BankID och ange dina bankuppgifter.';
            $body .= '<br><br>'; 
            $body .= 'När du är inloggad ser du även alla transaktioner och ditt saldo.';
            $body .= '<br><br>';
            $body .= 'Mejla därefter till info@turtle-pay.com och meddela att du vill få tillgodohavandet utbetalat, så ordnar Turtle Pay en banköverföring till dig.';
            $body .= '<br><br>';
            $body .= 'Har du fakturor kvar att betala kan du även dra av det krediterade beloppet mot fakturabeloppet och bara betala mellanskillnaden.';
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
          
           
            if (ENV_TYPE == 'prod') {
                
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