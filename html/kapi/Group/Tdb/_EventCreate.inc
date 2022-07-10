<?php
/*
    EventCreateClass
    
   	Get the compentions for a organization and return all 
	that today day no expieer

	https://app.equipe.com/organizers/515/meetings.json

	prodOn means get from API else get from local file

	{
		"_group" : "Tdb",
		"_action" : "EventCreate",
		"_user_id" : "69",
        "_operator_id" : "1",
        "_meeting_no" : "0099",
        "_event_name" : "NYTT TDB Event Test"
	}	

	// Event
	Här hämtar du din faktura för [tävlingsnamn].

	VARMT VÄLKOMNA!

	Fyll i uppgifterna nedan och bekräfta med ditt BankID.

	// Mail
	Här kommer din faktura inför [tävlingsnamn] under länken nedan.
 
	Varmt välkomna!
	Spekeröds ridklubb


*/
require_once 'Group/Tdb/TdbBase.inc';

class EventCreateClass extends TdbBaseClass {

    private $userId;
	private $operatorId;
	private $eventName;
    private $tdbApikey;
	private $tdbOrgno;
    private $meetingNo;
    private $templateId;
    private $eventId;
	private $companyName;
	
    public function _($data) {
		if ($this->parameterCheck($data) == false) {
			return array("code"=>"0", "denide_code"=>"param-fail");
		}      
        // Controll of exist 
        if ($this->competionsLoad() == false) {
            return array("code"=>"0", "denide_code"=>"competion-load-fail");
        }
        if ($this->eventCreate() == false) {
			return array("code"=>"0",  "denide_code"=>"selection-create-fail");
		}
        if ($this->selectionsCreate() == false) {
			return array("code"=>"3");
		}
        if ($this->invoiceEventCreate() == false) {
			return array("code"=>"4");
		}
        $reply = new stdClass();
        $reply->code = '1';
        $reply->event_id = $this->eventId;
        $reply->invoice_event_id = $this->invoiceEventId;
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
        if (isset($data->_meeting_no)) {
			$this->meetingNo = trim($data->_meeting_no);
		}
		else {
			return false;
		}
        if (isset($data->event_name)) {
			$this->eventName = trim($data->event_name);
		}
		else {
			return false;
		}
		
		$reply= $this->TdbSettingGet($this->userId);
		if ($reply['code'] != '1') {
			return false;
		}
		$this->tdbApikey = $reply['tdb_apikey'];
		$this->tdbOrgno = $reply['tdb_orgno'];
        $this->templateId = 437; // Mall for TDB
		
		return true;
	}

    private function competionsLoad() {
		/*
			https://app.equipe.com/meetings/37076/competitions.json
			https://app.equipe.com/meetings/37076/competions.json
		*/
		$prodOn = true;
      
		if ($prodOn) {
			$list = $this->_RestApiTdb('meetings/' . $this->meetingNo . '/competitions.json', $this->tdbApikey);
			//$this->apiResult = $this->_RestApiTdb('organizers/' . $this->tdbOrgno . '/meetings.json', $this->tdbApikey);
		}
		else {
			$list = json_decode(file_get_contents("Group/Tdb/meeting-41991.json")); 
		}
        if ($list) {
            $this->competions = array();
            /*
                Load all the infor for each competion and the cost
            */
            for ($i=0; $i<sizeof($list); $i++) {
                $record = new stdClass();
				$record->comp_no = $this->_nullFix($list[$i]->kq);
                $record->klass = $this->_nullFix($list[$i]->klass);
                $record->datum = $this->_nullFix($list[$i]->datum);
                $record->anm = $this->_nullFix($list[$i]->anm);
                $record->sta = $this->_nullFix($list[$i]->sta);
                $record->anb = $this->_nullFix($list[$i]->anb);
                $record->stb = $this->_nullFix($list[$i]->stb);
                $record->eanma = $this->_nullFix($list[$i]->eanma);
                $record->eanmb = $this->_nullFix($list[$i]->eanmb);
                $record->clabb = $this->_nullFix($list[$i]->clabb);
                array_push($this->competions, $record);
            }
            return true;
        }
        else {
            return false;
        }
	}

    private function eventCreate() {
		
		/*
            Create the url 
		*/
		$url =  strtolower($this->eventName);
		$url = $this->_nullFix($url);
		$url = str_replace("å","a",$url);
		$url = str_replace("Å","a",$url);
		$url = str_replace("ä","a",$url);
		$url = str_replace("Ä","a",$url);
		$url = str_replace("ö","o",$url);
		$url = str_replace("Ö","o",$url);
		$url = str_replace(' ', '-', $url); 
		$url = preg_replace('/[^A-Za-z0-9\-]/', '', $url); 
		$url = str_replace('----', '-', $url); 
		$url = str_replace('---', '-', $url); 
		$url = str_replace('--', '-', $url); 
		
		
        /*
            Get company info
        */
		$sql = "SELECT known_as, wa_logo, wa_url FROM company WHERE company_id = $this->userId";
		$companyInfo = $this->_GET($sql);
		$this->companyName = $companyInfo['known_as'];
        /*
            Load TDB template event
        */
		$sql = "SELECT * FROM event_v4 WHERE event_id= $this->templateId";
		$template = $this->_GET($sql);

		// --
		// -- Remove fileds
		unset($template['event_id']);
		unset($template['code']);
		unset($template['start_date']);
		unset($template['end_date']);

		unset($template['parent_on']);
		unset($template['child_on']); 
		unset($template['base_event_id']);
		unset($template['inherit_event_id']);
		unset($template['inherit_mobile_on']);
		unset($template['inherit_infobox_1_on']);
		unset($template['inherit_infobox_2_on']);
		unset($template['inherit_part_on']); 

        unset($template['last_tdb_invoicing_id']);
        unset($template['tdb_invocing_event_id']);
      
		$template['event_name'] = $this->eventName;
		$template['event_url'] = $url;
		$template['wa_url'] = $companyInfo['wa_url'];
		$template['create_date'] = Date('Y-m-d');
		$template['note_on'] = 'y';
		$template['note_label'] = 'Häst';	
		$template['event_status'] = 'p';
		$template['header_title'] = $companyInfo['known_as'];
		$template['header_image_on'] = 'n';
		$template['company_id'] = $this->userId;
        $template['company_address_on'] = 'y';

		/*
		$introText = $template['intro_text'];
		$introText = str_replace("'", "", $introText);
		$introText = str_replace('"', '', $introText);
		$template['intro_text'] = $introText;
		*/

		$template['intro_text'] = 'Här hämtar du din faktura för ' . $this->eventName . '.' . PHP_EOL . PHP_EOL;
		$template['intro_text'] .= 'VARMT VÄLKOMNA!' . PHP_EOL . PHP_EOL;
		$template['intro_text'] .= 'Fyll i uppgifterna nedan och bekräfta med ditt BankID.';
		
		$template['ref'] = $this->eventName;
		$reply = $this->_Insert("event_v4", $template);

		$param = new stdClass();	
		$param->base_event_id = $reply['id'];
		$param->tdb_on = 'y';
		$param->tdb_meeting_no = $this->meetingNo;
		$res = $this->_Update('event_v4', 'event_id',$reply['id'], $param);
		
        $this->eventId = $reply['id']; 

        return true;

    }

    private function selectionsCreate() {
		
		$fees = array("anm", "sta", "anb", "stb", "eanma", "eanmb");
        for ($i=0; $i<sizeof($this->competions); $i++) {
			foreach ($fees as $fee) {
				if (is_numeric($this->competions[$i]->$fee)) {
					$value = $this->competions[$i]->$fee;
				}
				else {
					$value = '0';
				}
				if ($value > 0) {
					$this->competions[$i]->klass = str_replace('  ', ' ', $this->competions[$i]->klass);
					$this->competions[$i]->klass = str_replace('   ', ' ', $this->competions[$i]->klass);
					$this->competions[$i]->klass = str_replace('    ', ' ', $this->competions[$i]->klass);
					$this->competions[$i]->clabb = trim($this->competions[$i]->clabb);
					switch ($fee) {
						case 'anm':
							$textSelection = $this->competions[$i]->clabb . ' - ' . trim($this->competions[$i]->klass);
							//$externalId = trim($this->competions[$i]->clabb) . '-anm';
                            $externalType = 'anm';
							$textOption = 'Anmäld ' . $this->competions[$i]->clabb . ' - ' . trim($this->competions[$i]->klass);
							$this->_selectionWrite($value, $textSelection, $textOption, $this->competions[$i]->comp_no, $externalType, $this->eventId);
							break;
						case 'anb':	
							$textSelection = $this->competions[$i]->clabb . 'B - ' . trim($this->competions[$i]->klass);
							//$externalId = trim($this->competions[$i]->clabb) . '-anm';
                            $externalType = 'anb';
							$textOption = 'Anmäld ' . $this->competions[$i]->clabb . 'B - ' . trim($this->competions[$i]->klass);
							$this->_selectionWrite($value, $textSelection, $textOption, $this->competions[$i]->comp_no, $externalType, $this->eventId);
							break;
						case 'eanma':
							$textSelection = $this->competions[$i]->clabb . ' - ' . trim($this->competions[$i]->klass) . ' (Efteranmälan)';
							//$externalId = trim($this->competions[$i]->clabb) . '-eanma';
                            $externalType = 'eanma';
							$textOption = 'Efteranmälan ' . $this->competions[$i]->clabb . ' - ' . trim($this->competions[$i]->klass);
							$this->_selectionWrite($value, $textSelection, $textOption, $this->competions[$i]->comp_no, $externalType, $this->eventId);
							break;
						case 'eanmb':	
							$textSelection = $this->competions[$i]->clabb . 'B- ' . trim($this->competions[$i]->klass) . ' (Efteranmälan)';
							//$externalId = trim($this->competions[$i]->clabb) . 'eanma';
                            $externalType = 'eanmb';
							$textOption = 'Efteranmälan ' . $this->competions[$i]->clabb . 'B - ' . trim($this->competions[$i]->klass);
							$this->_selectionWrite($value, $textSelection, $textOption, $this->competions[$i]->comp_no, $externalType, $this->eventId);
							break;

                        case 'sta':
                            $textSelection = $this->competions[$i]->clabb . ' - ' . trim($this->competions[$i]->klass) . ' (Startavgift)';
                            $externalType = 'sta';
                            $textOption = 'Startavgift ' . $this->competions[$i]->clabb . ' - ' . trim($this->competions[$i]->klass);
                            $this->_selectionWrite($value, $textSelection, $textOption, $this->competions[$i]->comp_no, $externalType, $this->eventId);
                            break;
                        case 'stb':	
                            $textSelection = $this->competions[$i]->clabb . 'B- ' . trim($this->competions[$i]->klass) . ' (Startavgift)';
                            $externalType = 'stb';
                            $textOption = 'Startavgift ' . $this->competions[$i]->clabb . 'B - ' . trim($this->competions[$i]->klass);
                            $this->_selectionWrite($value, $textSelection, $textOption, $this->competions[$i]->comp_no, $externalType, $this->eventId);
                            break;

						default:
							# code...Efteranmälan
							break;
					}
				}	
			}	
		}
		$textSelection = 'Rabatt';
		$externalType = 'discount';
		$textOption = 'Rabatt';
		$this->_selectionWrite('0', $textSelection, $textOption, '0', $externalType, $this->eventId);

        return true;

		//$reply = $this->inheritOptionUpdate($eventId, $data->_company_id, $data->_people_id);
		//return json_encode($reply);
	}

	private function _selectionWrite($value, $textSelection, $textOption, $externalId, $externalType, $eventId ) {
	
		$paramSelection = new stdClass();
		$paramSelection->event_id = $eventId;
		$paramSelection->text = $textSelection; 
		//$paramSelection->sortorder =  $;
		$paramSelection->required_on = 'n';
		$paramSelection->external_id = $externalId;  // competion_no
        $paramSelection->external_type = $externalType; // 
		$resSelection = $this->_Insert('event_selection_setting', $paramSelection);
	
		$currentSelectionId = $resSelection['id'];
		$param = new stdClass();
		$param->group_selection_setting_id = $currentSelectionId;
		$this->_Update('event_selection_setting', 'event_selection_setting_id', $currentSelectionId, $param);

		$paramOption = new stdClass();
		$paramOption->event_selection_setting_id = $resSelection['id'];
		$paramOption->text = $textOption;
		$paramOption->value = $value;
		$paramOption->sortorder = 100;
		$paramOption->max_on = 'n';
		$paramOption->max_number = 0;
	
		$resOption = $this->_Insert('event_option_setting', $paramOption);
		
	}
    
    private function invoiceEventCreate() {
        /*
			Create InvoiceEventId connected to the Event.
		*/
		
        $param = new stdClass();
        $param->company_id = $this->userId;    
		$param->invoice_event_name = $this->eventName;
		$param->event_id = $this->eventId;
		$param->invoice_event_type = 't'; // TDB
		$param->create_date = date("Y-m-d");
		$param->body = 'Här kommer din faktura inför ' . $this->eventName . ' under länken nedan.' . PHP_EOL . PHP_EOL;
		$param->body .= 'Varmt välkomna!' . PHP_EOL;
		$param->body .= $this->companyName . PHP_EOL;
		$param->webform_link = 'Hämta din faktura här!';

		$res = $this->_Insert("invoice_event", $param);
        if ($res['code'] == '1') {
           $this->invoiceEventId = $res['id'];
           $param = new stdClass();	
           $param->invoice_event_id = $this->invoiceEventId;
           $res = $this->_Update('event_v4', 'event_id',$this->eventId, $param);
            return true;
        }
        else {
            return false;
        }	
    }

	private function _nullFix($string) {
		if (is_null($string)) {
			return '';
		} 
		else {
			return  trim($string);
		}
	}

}