<?php
// 2021-07-01

echo '<div id="webform" class="column no-padding-top">';      
    //
    // -- Header-image-panel
    // --
    if ($Action->event['header_image_on'] == 'y') {
        echo '<div class="columns has-text-centered-of" id="header-image-panel" >';
            echo '<div class="column">';
                echo '<img id="header-image-src" src="' . SITE_URL . '/logo/' . $Action->event['header_image'] . '" alt="" />';
            echo '</div>';
        echo '</div>';
    }
    else {
        // --
        // -- Header-text-panel
        // --
        echo '<div class="columns">';
            echo '<div class="column">';
                echo '<h1 id="header-text-title" style="color:' . $Action->event['header_tcolor'] . '; background-color:' . $Action->event['header_bcolor'] . '">' . $Action->event['header_title'] . '</h1>';
            echo '</div>';
        echo '</div>';
    }

    // echo webformEventTitle($Action->event['event_name']);
    
    if (PREVIEW) {
        echo webformEventText('<i>FÖRHANDSGRANSKA</i><br>' . $Action->event['intro_text']);
    }
    else {
        echo webformEventText($Action->event['intro_text']);
    }
    // echo webformEventTextEdit();

    //echo '<div class="w100p">';
        echo webformRowInput($Action->event['personal_id_number_label'], 'personal_id_number', 'webform-personal-id-number only-numeric', '12', true, 'ååååmmddnnnn');
      
         // If invpice_event_id set email
         if ($Action->invoiceEventItemId > 0) {
            echo webformRowInputValue($Action->event['email_label'], 'email', 'webform-email no-special', '100', $Action->invoiceEvent['email'], true);
        }
        else {
             echo webformRowInput($Action->event['email_label'], 'email', 'webform-email no-special', '100', true);
        }
        if ($Action->event['mobile_on'] == 'y') {
            if ($Action->inheritOn == 'y') { // && $Action->event['inherit_mobile_on'] == 'y') {
                echo webformRowInputValue($Action->event['mobile_label'], 'mobile', 'webform-mobile no-special', '24', $Action->parentEventItem['mobile'], false);
            }
            else {
                echo webformRowInput($Action->event['mobile_label'], 'mobile', 'webform-mobile no-special', '24', false);
            }
        }

        // Inser company adress
        if ($Action->event['tdb_on'] == 'y' || $Action->event['company_address_on'] == 'y') {
            
            echo '<div class="column" style="max-width:456px; padding-bottom:6px!important">';
                echo '<div class="columns" style="margin-top:0px">';
                    echo '<div class="column" style="padding-left:0;">';
                        echo '<div class="field">';
                            echo '<label class="checkbox label">';
                                echo '<input type="checkbox" id="people_company_on">&nbsp;&nbsp;&nbsp;Företagsadress';
                            echo '</label>';
                        echo '</div>';
                    echo '</div>';
                echo '</div>';
            echo '</div>';
    
            echo webformRowInput('Företagsnamn', 'people_company', 'webform-email no-special', '80', false);
            echo webformRowInput('Adress', 'people_company_address', 'webform-email no-special', '60', false);
            echo '<div class="column people_company-panel-postaddress" style="max-width:456px;">';
                echo '<div class="columns" style="margin-top:0px">';
                    echo '<div class="column" style="margin-top:-14px;max-width:140px;padding-left:0;padding-right:36px">';
                        echo '<div class="field">';
                            echo '<label class="label">Postnr</label>';
                            echo '<div class="control">';
                                echo '<input class="input no-special" id="people_company_postcode" type="text" placeholder="" maxlength="5" autocomplete="off">';
                            echo '</div>';
                        echo '</div>';
                    echo '</div>'; 
                    echo '<div class="column" style="margin-top:-14px;padding-left:0; padding-right:0">';
                        echo '<div class="field">';
                            echo '<label class="label">Ort</label>';
                            echo '<div class="control">';
                                echo '<input class="input no-special" id="people_company_city" type="text" placeholder="" maxlength="60" autocomplete="off">';
                            echo '</div>';
                        echo '</div>';
                    echo '</div>';
                echo '</div>';
            echo '</div>';
        }

        // set ref from event
        if (strlen($Action->event['ref']) > 0) {
            echo webformRowInputValue($Action->event['ref_label'], 'receipt_number', 'webform-receipt-number no-special', '60', $Action->event['ref'], false, TRUE);
        }
        else {
              // Set ref, from invoice_event_item FIXED
              if (isset($Action->invoiceEvent['referens']) && strlen($Action->invoiceEvent['referens']) > 0) {
                echo webformRowInputValue($Action->event['ref_label'], 'receipt_number', 'webform-receipt-number no-special', '60', $Action->invoiceEvent['referens'], false, TRUE);
            }
            else {
                // Set blank
                 echo webformRowInput($Action->event['ref_label'], 'receipt_number', 'webform-receipt-number no-special', '60', true);
            }
        }
		
		 // 2021-02-02
        if ($Action->event['amount_on'] == 'y') {

            // Set amount, from invoice_event_item
            if ( isset($Action->invoiceEvent) && (float) $Action->invoiceEvent['amount'] > 0 ) {
                echo webformRowInputValue($Action->event['amount_label'], 'amount', 'webform-amount only-numeric', '10', $Action->invoiceEvent['amount'], true, TRUE);
            }

            // Set amount, from event
            else if ((float) $Action->event['amount'] > 0) {
                    echo webformRowInputValue($Action->event['amount_label'], 'amount', 'webform-amount only-numeric', '10', $Action->event['amount'], true, TRUE);
            }
            else {
                // Set blank
                echo webformRowInput($Action->event['amount_label'], 'amount', 'webform-amount only-numeric-point', '8', true);
            }

        }

		
		
        // Replace in prod
    if ($Action->event['participant_on'] == 'y') {

        if ($Action->inheritOn == 'y') {
            $tabsNumber = $Action->parentEventItem['participant_number'];
            $Action->event['participant_multi'] = 'n'; // Fix
        }
        else {
            $tabsNumber = 0;
        }
       
        echo webformParticipantTab( $Action->event['participant_title'], $Action->event['participant_apply_limit_on'], $Action->event['participant_apply_max'], $Action->inheritOn, $tabsNumber);
        // participant_multi
        echo '<div class="container" style="background-color:#e9e9e9; margin-bottom:24px;">';

            if ($Action->event['collect_spar_on'] == 'y') {
                echo '<div class="columns view-1" style="padding-top:8px">';
                    echo '<div class="column">';
                        echo '<div class="field">';
                            echo '<label class="label">Personnummer (12 tecken)</label>';
                            echo '<div class="control">';
                            echo '<input type="text" id="part-personal-id" maxlength="12" class="webform-input webform-color webform-personal-id-number only-numeric" placeholder="ååååmmddnnnn" style="padding-right:0;background-color: #ffffff" autocomplete="off">';
                            echo '</div>';
                        echo '</div>';
                    echo '</div>';

                    echo '<div class="column">';
                        echo '<div class="field">';
                            echo '<label class="label">&nbsp;&nbsp;</label>';
                            echo '<div class="control">';
                            echo '<button id="eGetFromSpar" class="button is-primary" style="margin-top: -4px">&nbsp;Hämta personuppgifter</button>';
                            echo '</div>';
                        echo '</div>';
                    echo '</div>';
                echo '</div>';
            }

            if ($Action->event['date_of_birth_on'] == 'y') {
                // echo webformInfoBoxText($Action->event['note_label'], 'note', 'height-36', '512');   
                echo htmlColumn();
                    // $text, $id, $value, $inputClass='', $maxlength='100', $placeholder = ''
                    echo htmlRowInput($Action->event['date_of_birth_label'], 'date_of_birth', '', 'webform-personal-id-number only-numeric', '8', "ååååmmdd");
                echo htmlDivEnd();
            }


            $paramForm = new stdClass();
            $paramForm->viewClass = 'view-1';
            $paramForm->noOfColumns = 2;
            $paramForm->column = array();
            $paramForm->column[0] = new stdClass();
            $paramForm->column[0]->label = $Action->event['participant_first_name_label'];
            $paramForm->column[0]->requiredOn = true;
            $paramForm->column[0]->id = 'first-name';
            $paramForm->column[0]->class = 'no-special';
            $paramForm->column[0]->maxlength = '50';
            $paramForm->column[0]->placeholder = 'Förnamn';
            $paramForm->column[1] = new stdClass();
            $paramForm->column[1]->label = $Action->event['participant_last_name_label'];
            $paramForm->column[1]->requiredOn = true;
            $paramForm->column[1]->id = 'last-name';
            $paramForm->column[1]->class = 'no-special';
            $paramForm->column[1]->maxlength = '50';
            $paramForm->column[1]->placeholder = 'Efternamn';
            echo webformRowMultiInput($paramForm);

            if ($Action->event['participant_address_on'] == 'y' || $Action->event['collect_spar_on'] == 'y') {
                if ($Action->event['participant_address_on'] == 'y') {
                    echo '<div class="columns view-1">';
                }
                else {
                    echo '<div class="columns view-1" style="display:none">';
                }
                    echo '<div class="column">';
                        echo '<div class="field">';
                            echo '<label class="label">Adress</label>';
                            echo '<div class="control">';
                                echo '<input class="input no-special" id="part-address" type="text" placeholder="" maxlength="100" autocomplete="off">';
                            echo '</div>';
                        echo '</div>';
                    echo '</div>';
                    
                    echo '<div class="column">';
                        echo '<div class="columns" style="margin-top:0px">';
                            echo '<div class="column">';
                                echo '<div class="field">';
                                    echo '<label class="label">Postnr</label>';
                                    echo '<div class="control">';
                                        echo '<input class="input no-special" id="part-postcode" type="text" placeholder="" maxlength="24" autocomplete="off">';
                                    echo '</div>';
                                echo '</div>';
                            echo '</div>'; 
                            echo '<div class="column"">';
                                echo '<div class="field">';
                                    echo '<label class="label">Ort</label>';
                                        echo '<div class="control">';
                                            echo '<input class="input no-special" id="part-city" type="text" placeholder="" maxlength="50" autocomplete="off">';
                                        echo '</div>';
                                    echo '</div>';
                                echo '</div>';
                            echo '</div>';
                        echo '</div>';
                    echo '</div>';

                if ($Action->event['participant_address_on'] == 'y') {

                    $paramForm = new stdClass();
                    $paramForm->viewClass = 'view-1';
                    $paramForm->noOfColumns = 2;
                    $paramForm->column = array();
                    $paramForm->column[0] = new stdClass();
                    $paramForm->column[0]->label = 'Mobilnummer';
                    $paramForm->column[0]->requiredOn = false;
                    $paramForm->column[0]->id = 'part-mobile';
                    $paramForm->column[0]->class = 'no-special';
                    $paramForm->column[0]->maxlength = '24';
                    $paramForm->column[0]->placeholder = '';
                    $paramForm->column[1] = new stdClass();
                    $paramForm->column[1]->label = 'E-postadress';
                    $paramForm->column[1]->requiredOn = false;
                    $paramForm->column[1]->id = 'part-email';
                    $paramForm->column[1]->class = 'no-special';
                    $paramForm->column[1]->maxlength = '100';
                    $paramForm->column[1]->placeholder = '';
                    echo webformRowMultiInput($paramForm);
                }

            }
            
            //echo '<pre>';
            //print_r($Action->selectionStatus); die('');
            // ---
            // --- Create each option
            // ---
            if (sizeof($Action->selection) > 0 ) {
                $newRow = true;
                for ($i = 0; $i < sizeof($Action->selection); $i++) { 
                    if ($Action->event['tdb_on'] == 'y' && $Action->event['event_create_type'] == 'i' && $Action->selectionStatus[$i]->on == 'n') {
                        // skip
                    }
                    else {
                        if ($newRow == true) {
                            echo htmlColumns('view-1');
                            $newRow = false;
                            $gridCol = 0;
                        }
                        $gridCol++;
                        echo htmlColumn();
                     
                        /*
                        if ( $Action->selection[$i]['external_id'] == 'discount') {
                            //print_r($Action->selection[$i]['option']);
                            $Action->selection[$i]['option'][0]['value'] = '-100';
                            $Action->selection[$i]['option'][0]['text'] = 'Rabatt (0kr)';
                            //print_r($Action->selection[$i]['option']);
                            //die('discount');
                        }
                        */
                        if ($i < sizeof($Action->selection)) {
                            
                            if ($Action->selection[$i]['parent_event_selection_setting_id'] > 0) {

                                echo webformOptionsCreate($Action->selection[$i]['text'], $Action->selection[$i]['required_on'], $i, $Action->selection[$i]['option'], $Action->eventId, 'Ej vald');
                            }  
                            else {
                                echo webformOptionsCreate($Action->selection[$i]['text'], $Action->selection[$i]['required_on'], $i, $Action->selection[$i]['option'], $Action->eventId);
                            }
                        }
                        echo htmlDivEnd();  
                        if ($gridCol == $Action->event['option_grid']) {
                            echo htmlDivEnd();
                            $newRow = true;
                        }
                    }
                }
                if ($newRow == false) {
                    for ($i = 0; $i <= $gridCol; $i++) {
                        echo htmlColumn();
                        echo htmlDivEnd();
                    }
                    echo htmlDivEnd();
                }
            
            if ($Action->event['note_on'] == 'y') {
                // echo webformInfoBoxText($Action->event['note_label'], 'note', 'height-36', '512');   
                echo htmlColumn();
                    echo htmlRowInput($Action->event['note_label'], 'note', '', 'note', '256');
                echo htmlDivEnd();
            }
            echo htmlDivEnd();    // --- Close the Participant box
            
            echo htmlColumns();
                echo htmlColumn();
                    echo htmlRowInput($Action->event['total_amount_label'], 'total_amount', '', 'amount', '10');
                echo htmlDivEnd();
            echo htmlDivEnd();
           
        }
    }    

    if ($Action->event['infobox_1_on'] == 'y') {
        //if ($Action->inheritOn == 'y' && $Action->event['inherit_infobox_1_on'] == 'y') {
            //echo webformInfoBoxText($Action->event['infobox_1_label'], 'infobox_1', '', '512', $Action->parentEventItem['infobox_1']);
        //}
        //else {
            echo webformInfoBoxText($Action->event['infobox_1_label'], 'infobox_1', 'no-special', '512');
        //}
    }

    if ($Action->event['infobox_2_on'] == 'y') {
        //if ($Action->inheritOn == 'y' && $Action->event['inherit_infobox_2_on'] == 'y') {
            //echo webformInfoBoxText($Action->event['infobox_2_label'], 'infobox_2', '', '512', $Action->parentEventItem['infobox_2']);
        //}
        //else {
            echo webformInfoBoxText($Action->event['infobox_2_label'], 'infobox_2', 'no-special', '512');
        //}
    }
                
    echo webformBankIdSection($Action->paymentText, $Action->isMobile, $Action->bankidText, $Action->confirmLabel, SITE_URL, LIB);

    echo webformFooter($Action->companyKnownAs . ' i samarbete med Turtle Pay AB.', 'www.turtle-pay.com, tel. 08-806220');

echo '</div>';  


echo '<div class="modal" id="login-mobile-modal">';
    echo '<div class="modal-background"></div>';
        echo '<div class="modal-card pl0 pr0  modal-width" style="margin-top: -150px!important">';
            echo '<header class="modal-card-head">';
                echo '<p class="modal-card-title has-text-centered">Signering</p>';
            echo '</header>';
            echo '<section class="modal-card-body">';
                echo '<p id="login-mobile-modal-text" class="has-text-centered"></p>';
            echo '</section>';
        echo '<footer class="modal-card-foot">';
            echo '<button id="eMobileLogin" class="button is-dark w120 image-center" >Fortsätt</button>';
        echo '</footer>';
    echo '</div>';
echo '</div>';


function webformEventTitle($title) {

    $html = '';
    $html .= '<div class="columns">';
        $html .= '<div class="column">';
            $html .= '<h1 id="webform-webform-name" class="webform-text-color">' . $title . '</h1>';
        $html .= '</div>';
    $html .= '</div>';
    
    return $html;
}

function webformEventText($text) {

    $html = '';
    $html .= '<div class="columns">';
        $html .= '<div class="column">';
            $html .= '<p id="webform-intro-text" class="webform-text-color">' . nl2br($text) . '</p>';
        $html .= '</div>';
    $html .= '</div>';

    return $html;
}

// --
// -- Input row for input boxes
//

function webformRowInput($label, $id, $inputClass, $maxlength='100', $requiredOn, $placeholder = '') {

    if ($requiredOn) {
        $requiredMark = '<span class="requied-color"> * </span>';
    }
    else {
        $requiredMark = '';
    }

    $html = '';
    $html .= '<div class="columns ' . $id . '-panel">';
        $html .= '<div class="column">';
            $html .= '<label class="webform-label webform-text-color">' . $label . $requiredMark . '</label/>';
        $html .= '</div>';
    $html .= '</div>';

    $html .= '<div class="columns ' . $id . '-panel">';
        $html .= '<div class="column">';
            $html .= '<input class="webform-input webform-input-color ' . $inputClass . '" id="' . $id . '" type="text" placeholder="' . $placeholder . '"  maxlength="' . $maxlength . '" autocomplete="off"/>';
        $html .='</div>';
    $html .='</div>';

    return $html;
}

function webformRowInputValue($label, $id, $inputClass, $maxlength='100', $value, $requiredOn, $disabled = FALSE) {

    if ($requiredOn) {
        $requiredMark = '<span class="requied-color"> * </span>';
    }
    else {
        $requiredMark = '';
    }

    $html = '';
    $html .= '<div class="columns ' . $id . '-panel">';
        $html .= '<div class="column">';
            $html .= '<label class="webform-label webform-text-color">' . $label . $requiredMark . '</label/>';
        $html .= '</div>';
    $html .= '</div>';

    if ($disabled) {
        $dis = 'disabled';
    }
    else {
        $dis = '';
    }
    $html .= '<div class="columns ' . $id . '-panel">';
        $html .= '<div class="column">';
            $html .= '<input ' . $dis . ' class="webform-input webform-input-color ' . $inputClass . '" id="' . $id . '" type="text" value="' . $value . '"  maxlength="' . $maxlength . '" autocomplete="off"/>';
        $html .='</div>';
    $html .='</div>';

    return $html;
}


function webformOptionsCreate($text,  $requiredOn, $index, $option, $eventId, $initLabel = '--- Välj ---' ) {

    if ($requiredOn == 'y') {
        $requiredMark = '<span class="requied-color"> * </span>';
    }
    else {
        $requiredMark = '';
    }

    $html = '';
    $html .= '';
    $html .= '<label class="label">' . $text .  $requiredMark . '</label>';
    $html .= '<div class="select" style="width:100%">';
    $html .= '<select class="select-option" id="option-' . $index .  '" style="width:100%">';
    $html .= '<option selected value="8E1C7E8F67D0">' . $initLabel . '</option>';
        for ($j = 0; $j < sizeof($option); $j++) { 
            if ($eventId == '5' && $option[$j]['webform_option_id'] == '25') {
                // Skip
            }
            else {
                //echo '<pre>';
                //print_r($option[$j]);
                //die('');
               
                if ($option[$j]['max_on'] == 'y') {
                    if ($option[$j]['counter'] >= $option[$j]['max_number'] ) {
                        $html .= '<option disabled value="' . $option[$j]['value'] . '">' . $option[$j]['text']  . '</option>';
                    }
                    else {
                        $html .= '<option value="' . $option[$j]['value'] . '">' . $option[$j]['text']  . '</option>';
                    }
                }
                else {
                    $html .= '<option value="' . $option[$j]['value'] . '">' . $option[$j]['text']  . '</option>';
                }
                
            }
        }
        $html .=  '</select>';
    $html .=  '</div>';

    return $html;
}

function webformInfoBoxText($label, $id, $inputClass, $maxlength='100', $value='') {

    $html = '';
    $html .= '<div class="columns ' . $id . '-panel">';
        $html .= '<div class="column">';
            $html .= '<label class="webform-label webform-text-color">' . $label . '</label/>';
        $html .= '</div>';
    $html .= '</div>';
  
    $html .= '<div class="columns ' . $id . '-panel">';
        $html .= '<div class="column">';
            $html .= '<textarea id="' . $id . '" style="width: 88%;" class="textarea ' .  $inputClass . '" rows="1" maxlength="' . $maxlength . '">' . $value . '</textarea>';
            //$html .= '<input class="webform-input webform-input-color ' . $inputClass . '" id="' . $id . '" type="text" maxlength="' . $maxlength . '" autocomplete="off"/>';
        $html .='</div>';
    $html .='</div>';

    return $html;

}

function webformRowMultiInput($form) {

    $requiredMarkOn = '<span class="requied-color"> * </span>';

    $html = '';
    $html .='<div class="columns ' . $form->viewClass . '">';
    for ($i=0; $i<$form->noOfColumns; $i++) {
        $html .='<div class="column">';
            $html .='<div class="field">';
                if ($form->column[$i]->requiredOn) {
                    $html .='<label class="label">' . $form->column[$i]->label . $requiredMarkOn . '</label>';
                }
                else {
                    $html .='<label class="label">' . $form->column[$i]->label . '</label>';
                }
                $html .='<div class="control">';
                    $html .='<input class="input ' . $form->column[$i]->class . '" id="' . $form->column[$i]->id . '" type="text" placeholder="' . $form->column[$i]->placeholder . '"  maxlength="' . $form->column[$i]->maxlength . '" autocomplete="off"/>';
                $html .='</div>';
            $html .='</div>';
        $html .='</div>';
    }
    $html .='</div>'; 

    return $html;
}

// Replace in prod
function webformParticipantTab($label, $limitOn, $maxNo, $inheritOn, $tabsNo) {
    $html = '';
    $html .='<div class="columns view-1" style="margin-top:0px">';
        $html .='<div class="column">';
            $html .='<div class="tabs is-small">';
                $html .='<ul>';
                    $html .='<li class="is-active eParticipantTab" index="0" style="font-size:13px"><a>' . $label . '</a></li>';
                    // This is used when inherit
                    if ($inheritOn == 'y' ) {
                        for ($i=1; $i<$tabsNo; $i++) { 
                            $html .='<li class="eParticipantTab" index="' . $i . '" style="font-size:13px"><a>' . $label . '</a></li>';
                        }
                    }
                    else {
                        if ($limitOn == 'n') {
                        // if ($tabsNo == '1') {
                                $html .='<li id="eAddTab"><a style="font-size:13px; font-weight:bold">+ Lägg till ' . $label . '</a></li>'; 
                                $html .='<li id="eRemoveTab"><a style="font-size:13px; font-weight:bold">- Ta bort ' . $label . '</a></li>'; 
                            //}
                        }
                        else {
                            if ($maxNo > 1) {
                                $html .='<li id="eAddTab"><a style="font-size:13px; font-weight:bold">+ Lägg till ' . $label . '</a></li>'; 
                                $html .='<li id="eRemoveTab"><a style="font-size:13px; font-weight:bold">- Ta bort ' . $label . '</a></li>'; 
                            }
                        }
                    }
                $html .='</ul>';  
            $html .='</div>';
        $html .='</div>';
    $html .='</div> ';

    // echo $limitOn . ' : ' . $maxNo; die(' - STOP');

    return $html;
}

function webformBankIdSection($paymentText, $isMobile, $bankIdText, $buttonLabel, $host, $lib) {
    $html = '';

    $html .='<div class="columns" style="margin-top: 12px">';
        $html .='<div class="column">';
            $html .='<p style="font-size:14px" id="webform-payment-text">';
                $html .= $paymentText;
            $html .='</p>';
        $html .='</div>';
    $html .='</div>';

    $html .= '<div class="columns">';
    $html .= '<div class="column" style="padding-top: 8px">';
    $html .= '<div class="field">';   
    $html .= '<label class="checkbox" style="font-size:14px">';
    if ($isMobile == "yes") {
        $html .= '<input type="checkbox" id="BankIDCheckBox" checked >';
    }
    else {
        $html .= '<input type="checkbox" id="BankIDCheckBox" >';
    }
    $html .= ' ' . $bankIdText; 
    $html .= '</label>';
    $html .= '</div>';
    $html .= '</div>';
    $html .= '</div>';

    $html .= '<div class="columns">';
        $html .= '<div class="column">';
            if (PREVIEW) {
                $html .='<button class="button is-large" style="width:100%">';
            }
            else {
                $html .='<button class="button is-large" id="eConfirm" style="width:100%">';
            }
                $html .='<span class="icon is-medium">';
                    // - $html .='<img src="' .  $host . $lib . '/images/icon_64x64.png" alt="" class="bankid-logo" height="40" width="40"/>';
                    // - $html .='<img src="images/icon_64x64.png" alt="" />';
                    $html .='<img src="' .  $host . $lib . '/images/icon_64x64.png" alt="" />';
                $html .='</span>';
                $html .='<span>' . $buttonLabel . '</span>';
            $html .='</button>';
        $html .= '</div>';
    $html .= '</div>';

    return $html;
}

function webformFooter($line1, $line2) {
    $html = '';
    //$html .='<footer class="footer" >';
        //$html .='<div class="section">';
            //$html .='<div class="container">';
                $html .='<div class="columns">';
                    $html .='<div class="column" style="margin: 14px 0 8px 0">';
                        $html .='<p id="webform-footer-line1" class="has-text-centered" style="font-size: 13px;font-style: italic; margin-bottom:2px">' . $line1 . '</p>';
                        $html .='<p class="has-text-centered" style="font-size: 13px;font-style: italic">' . $line2 . '</p>';
                    $html .='</div>';
                $html .='</div>';
            //$html .='</div>';
        //$html .='</div>';
    //$html .='</footer>';

    return $html;
}

?>