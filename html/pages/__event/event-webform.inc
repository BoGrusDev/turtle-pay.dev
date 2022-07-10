<?php 
/*
   @[class]event-webform.inc

   @[desc]
   * Hanling the list and report of Evnet items 
   @[end-desc]

   @[update]2021-07-01

   @[todo]
   @[end-todo]

*/
// Load Settings
$Setting = new stdClass();
$Setting->bankid_text = 'BankID på denna enhet';
$Setting->confirm_desc_label = 'Tryck bekräfta och öppna därefter BankID i din mobil eller på din dator.';
$Setting->confirm_label = 'Bekräfta';
$Setting->cancel_label = 'Avbryt';

$Setting->footer_text = 'Test Bolaget AB' . " i samarbete med Turtle Pay AB.";
$Setting->payment_text = '';
$Setting->continue_text = 'Fortsätt efter BankID signering';
$Setting->footer_line1 = '';
$Setting->footer_line2 = 'www.turtle-pay.com, tel. 08-806220';

echo '<section class="hero is-primary page-section section-webform-item hide-preview" style="display:none">';
    echo '<div class="hero-body" style ="padding-bottom: 0; padding-top: 0;margin-bottom: 0;margin-top: 0;">';
        echo '<div class="container">';
            echo '<h1 style="padding-top: 10px;">Webformulär</h1>';
        echo '</div>';
    echo '</div>';
echo '</section>';

echo '<section class="section page-section section-webform-item" style="display:none">';
   echo '<div class="container">';

        $param = array();
        $param[0] = new stdClass();
        $param[0]->text = 'Förhandsgranska';
        $param[0]->eventId = 'ePreview';
        $param[0]->classes = 'is-link is-small';
     
        $param[1] = new stdClass();
	    $param[1]->text = 'Stäng';
        $param[1]->eventId = 'eBackWebform';
        $param[1]->classes = 'is-dark is-small';    
    
        // --
        // Webform Image
        //
        echo '<div class="columns no-margin-top">';
            echo '<div id="webform" class="column no-padding-top" >';  
                echo '<div class="box" style="width: 812px">';
                    echo '<div class="columns " id="header-image-panel" style="margin-top: 0">';
                        echo '<div class="column is-horizontal-center-x" style="padding-top: 4px!important; padding-bottom:24px!important; display:grid">';
                            echo '<img id="header-image-src" src="" alt="" />';
                        echo '</div>';
                    echo '</div>';

                    echo '<div class="columns has-text-centered-2" id="header-text-panel" style="margin-top: 0">';
                        echo '<div class="column" style="padding-top: 0!important">';
                            echo '<h1 id="header-text-title"></h1>';
                        echo '</div>';
                    echo '</div>';

                    echo webformEventText();

                    /*
                    echo '<div class="columns">';
                        echo'<div class="column">';
                            echo  '<p id="intro_text_edit" class="webform-intro-text webform-text-color"></p>';
                            echo '<textarea id="intro_text" style="width: 88%; color:#eeeeee; background-color:#666666;display:none" class="webform-intro-text-edit" rows="12"></textarea>';
                        echo '</div>';
                    echo '</div>';

                    echo '<div class="columns tool-panel">';
                        echo '<div class="column">';
                            echo '<a class="button eEditIntroText" ><span class="icon is-small"><i class="far fa-edit"></i></span>&nbsp;&nbsp;Event beskrivning</a>';
                            echo  '&nbsp;&nbsp;';
                            echo '<a action="cancel" style="background-color: #efefef; border-color: #cccccc; font-size:13px; padding: 16px; display:none" class="button eEditPanelIntroText"><span class="icon is-small"><i class="fas fa-times"></i></span></a>';
                            echo '&nbsp;&nbsp;';
                            echo '<a action="ok" style="padding: 16px; display:none" class="button is-primary eEditPanelIntroText"><span class="icon is-small"><i class="fas fa-check"></i></span></a>';
                        echo '</div>';
                    echo '</div>';
                    */
                    
                    echo webformRowInput('Köparens personnummer (12 teckem)', 'personal_id_number', 'webform-personal-id-number only-numeric', '12',  array(TRUE, FALSE, FALSE), 'ååååmmddnnnn');
                    echo webformRowInput('Fakturamottagarens e-postadress', 'email', 'webform-email', '100', array(TRUE, FALSE, FALSE));
                    echo webformRowInput('Mobilnummer', 'mobile', 'webform-mobile', '24', array(TRUE, FALSE, FALSE));
                    echo webformRowInput('Referens', 'ref', 'webform-receipt-number', '60', array(TRUE, TRUE,  FALSE));


                    echo webformRowInputAmount('Belopp kr', 'amount', 'webform-amount', '10',  array(TRUE, TRUE, FALSE));
                
                    echo '<div class="columns participant-form" style="display:none; margin-top:6px">'; // participant-panel columns
                        echo '<div class="column" style="max-width: 812px;">';  // participant-panel main column
                        echo htmlParticipantTab('Deltagare', 'y');
                        
                        echo '<div class="columns collect_spar-panel" >';
                            echo '<div class="column" style="padding-bottom: 2px;">';
                                echo '<input disabled="disabled" value="Personnummer (12 tecken)" class="webform-label webform-text-color " id="address-label" type="text" maxlength="100" autocomplete="off" style="color: rgb(34, 34, 34);">';
                            echo '</div>';
                        echo '</div>';

                        echo '<div class="columns collect_spar-panel" >';
                            echo '<div class="column" style="padding-bottom: 2px; max-width: 296px">';
                                echo '<p class="control has-icons-right" style="margin-bottom:0">';
                                    echo '<input disabled="disabled" type="text" id="participant_personal_id" class="webform-input webform-color webform-personal-id-number only-numeric" placeholder = "ååååmmddnnnn" style="padding-right:0;background-color: #ffffff" autocomplete="off">';
                                    echo '<span class="icon is-small" style="width: auto; pointer-events: auto;">';
                                        echo '<button id="eGetFromSpar" class="button is-primary" style="margin-left: 20px">&nbsp;Hämta personuppgifter</button>';
                                    echo '</span>';
                                echo '</p>';
                            echo '</div>';
                        echo '</div>';

                        echo '<div class="columns date_of_birth-panel">';
                             echo '<div class="column" style="padding-bottom:  6px!important; width:100%">';
                                echo webformRowInput('Födelsedatum', 'date_of_birth', 'webform-personal-id-number only-numeric', '8',array(TRUE, FALSE, FALSE), 'ååååmmdd');
                            echo '</div>';  
                        echo '</div>';

                        echo '<div class="columns">';
                            echo '<div class="column" style="padding-bottom:  6px!important;">';
                                echo webformRowInput('Förnamn', 'participant_first_name', 'webform-name', '50',  array(TRUE, FALSE, FALSE));
                            echo '</div>';
                            echo '<div class="column" style="padding-bottom: 6px!important;">';
                                echo webformRowInput('Efternamn', 'participant_last_name', 'webform-name', '50',  array(TRUE, FALSE, FALSE));
                            echo '</div>';
                        echo '</div>';

                        echo '<div class="columns participant_address-panel" style="margin-top: -18px">';
                            echo '<div class="column">';
                                echo '<input disabled="disabled" value="Adress" class="webform-label webform-text-color" id="adress-label" type="text" maxlength="100" autocomplete="off" style="color: rgb(34, 34, 34);">';
                            echo '</div>';
                            echo '<div class="column">';
                                echo '<input disabled="disabled" value="Postnr" class="webform-label webform-text-color" id="postcode-label" type="text" maxlength="90" autocomplete="off" style="color: rgb(34, 34, 34);width:100px;display: inline-block">';
                                echo '<input disabled="disabled" value="Ort" class="webform-label webform-text-color" id="city-label" type="text" maxlength="100" autocomplete="off" style="color: rgb(34, 34, 34);width:100px;display: inline-block; margin-left:8px">';   
                            echo '</div>';
                        echo '</div>';

                        echo '<div class="columns participant_address-panel">';
                            echo '<div class="column">';
                                echo '<input disabled="disabled" class="webform-input webform-input-color webform-address" id="address" type="text" placeholder="" maxlength="50" autocomplete="off" style="background-color: rgb(255, 255, 255); color: rgb(34, 34, 34);">';
                            echo '</div>';
                            echo '<div class="column">';
                                echo '<input disabled="disabled" class="webform-input webform-input-color webform-postcode" id="postcode" type="text" placeholder="" maxlength="6" autocomplete="off" style="background-color: rgb(255, 255, 255); color: rgb(34, 34, 34);width:100px;display: inline-block">';
                                echo '<input disabled="disabled" class="webform-input webform-input-color webform-city" id="city" type="text" placeholder="" maxlength="40" autocomplete="off" style="background-color: rgb(255, 255, 255); color: rgb(34, 34, 34);display: inline-block;margin-left:8px">';   
                            echo '</div>';
                        echo '</div>';

                        echo '<div class="columns participant_address-panel">';
                            echo '<div class="column" style="padding-bottom: 6px!important;">';
                               echo webformRowInput('Mobil', 'part-mobile', 'webform-mobile', '50',  array(FALSE, FALSE, FALSE));
                            echo '</div>';
                            echo '<div class="column" style="padding-bottom: 6px!important;">';
                                echo webformRowInput('E-post', 'part-email', 'webform-email', '50',  array(FALSE, FALSE, FALSE));
                            echo '</div>';
                        echo '</div>';

                        echo webformSpecToolbar(); // Show in 2 diffrent context, level

                        echo '<div class="columns"  style="padding-top: 12px;">';
                            echo '<div class="column" id="webform-selections"></div>';
                        echo '</div>';
                    
                        // echo webformRowInput('Fritext', 'note', 'webform-note', '256',array(TRUE, FALSE, FALSE, TRUE));
                        echo '<div class="columns note-panel"><div class="column"><input disabled="disabled" value="Fritext" class="webform-label webform-text-color" id="note-label" type="text" maxlength="27" autocomplete="off" style="color: rgb(34, 34, 34);"><a itemid="note" action="cancel" style="display:none" class="button webform-edit-panel-cancel eEditPanel edit-panel-note"><span class="icon is-small"><i class="fas fa-times"></i></span></a><a itemid="note" action="ok" style="display:none" class="button webform-edit-panel-ok is-primary eEditPanel edit-panel-note"><span class="icon is-small"><i class="fas fa-check"></i></span></a></div></div>';
                        echo '<div class="columns note-panel"><div class="column"><input disabled="disabled" class="webform-input webform-input-color webform-note" id="note" type="text" placeholder="" maxlength="27" autocomplete="off" style="background-color: rgb(255, 255, 255); color: rgb(34, 34, 34);"><a itemid="note" action="cancel" style="background-color: #efefef; border-color: #cccccc; font-size:13px; padding: 16px; display:none" class="button eEditValue edit-value-note"><span class="icon is-small"><i class="fas fa-times"></i></span></a><a itemid="note" action="ok" style="padding: 16px; display:none" class="button is-primary eEditValue edit-value-note"><span class="icon is-small"><i class="fas fa-check"></i></span></a></div></div>';
                        echo '<div class="columns note-panel tool-panel"><div class="column"><a class="button eToolLabel" itemid="note"><span class="icon is-small"><i class="far fa-edit"></i></span>&nbsp;&nbsp;Rubrik</a>&nbsp;&nbsp;<a class="button is-dark eToolRemove" itemid="note"><span class="icon is-small"><i class="fas fa-times"></i></span></a></div></div>';

					   
					   
					   
					   
                        //echo webformRowInput('Totalt', 'total_amount', 'amount', '100', array(TRUE, FALSE, FALSE));

                        echo '<div class="columns total_amount-panel">';
                            echo '<div class="column">';
                                echo '<input disabled="disabled" value="Totalt" class="webform-label webform-text-color" id="total_amount-label" type="text" maxlength="100" autocomplete="off" style="color: rgb(34, 34, 34);">';
                                echo '<a itemid="total_amount" action="cancel" style="display:none" class="button webform-edit-panel-cancel eEditPanel edit-panel-total_amount">';
                                    echo '<span class="icon is-small"><i class="fas fa-times"></i></span>';
                                    echo '</a>';
                                echo '<a itemid="total_amount" action="ok" style="display:none" class="button webform-edit-panel-ok is-primary eEditPanel edit-panel-total_amount">';
                                    echo '<span class="icon is-small"><i class="fas fa-check"></i></span>';
                                echo '</a>';
                            echo '</div>';

                            echo accountingPanel1('accounting', 'accounting-panel');
                        echo '</div>';

                        echo '<div class="columns total_amount-panel">';
                            echo '<div class="column">';
                                echo '<input disabled="disabled" class="webform-input webform-input-color amount" id="total_amount" type="text" placeholder="" maxlength="100" autocomplete="off" style="background-color: rgb(255, 255, 255); color: rgb(34, 34, 34);">';
                                echo '<a itemid="total_amount" action="cancel" style="background-color: #efefef; border-color: #cccccc; font-size:13px; padding: 16px; display:none" class="button eEditValue edit-value-total_amount">';
                                    echo '<span class="icon is-small"><i class="fas fa-times"></i></span></a><a itemid="total_amount" action="ok" style="padding: 16px; display:none" class="button is-primary eEditValue edit-value-total_amount"><span class="icon is-small"><i class="fas fa-check"></i></span>';
                                echo '</a>';
                            echo '</div>';
                            echo accountingPanel2('accounting', 'accounting-panel', 'ddAccountList');
                        echo '</div>';

                        echo '<div class="columns total_amount-panel tool-panel">';
                            echo '<div class="column">';
                                echo '<a class="button eToolLabel" itemid="total_amount">';
                                    echo '<span class="icon is-small"><i class="far fa-edit"></i></span>&nbsp;&nbsp;Rubrik';
                                echo '</a>';  
                            echo '</div>';
                            echo accountingPanel3('accounting', 'accounting-panel');
                        echo '</div>';

                    echo '</div>'; // participant-panel main column
                echo '</div>'; // articipant-panel columns
                

                // echo accountingPanel();

                echo webformInfoBoxText('Infobox 1', 'infobox_1', '', '512',array(TRUE, FALSE, FALSE));
                echo webformInfoBoxText('Infobox 2', 'infobox_2', '', '512',array(TRUE, FALSE, FALSE));

                echo webformBankIdSection($Setting->payment_text, 'no', $Setting->bankid_text, $Setting->confirm_label);

                echo webformFooter($Setting->footer_line1, $Setting->footer_line2);

            echo '</div>'; 
        echo '</div>';  

        echo '<div id="webform-preview-panel" class="column" style="display:none">';
            echo '<div class="box" style="width: 40px; max-width:40px;">';
                echo '<div class="columns">';
                    echo '<div class="column">';
                        echo '<button id="eBackEdit" class="button is-danger is-small" style="display:none; ">Avsluta förhandsgranskning</button>';
                    echo '</div>'; 
                echo '</div>';
            echo '</div>';
        echo '</div>';

        echo '<div id="webform-panel" class="column">';
            echo '<div class="box" style="width: 340px;">';
                echo htmlButtons($param);
                echo webformPanel();
            echo '</div>';

            echo '<form style="display:none">';
                echo '<input type="file" id="upload-file" name="image" class="image" required >';
                echo '<input type="submit" name="submit" class="submit button is-small is-primary" value="">';
            echo '</form>';

            echo '<form style="display:none">';
                echo '<input type="file" id="upload-attach" name="attach" class="attach" required >';
                //echo '<input type="submit" name="submit" class="submit button is-small is-primary" value="">';
        echo '</form>';
        echo '</div>';
    echo '</div>';;

echo  '</section>';

echo webformYesNoRemoveSelection();
echo webformYesNoRemoveNote();
echo attachRemoveModal();
echo webformSelections();

function htmlParticipantTab($label, $multi) {
    $html = '';
    $html .='<div class="columns">';
        $html .='<div class="column">';
            $html .='<div class="tabs is-small">';
                $html .='<ul>';   // id="eParticipantTab"
                    $html .='<li class="is-active participant-tab" index="0" style="font-size:13px;"><a>' . $label . '</a></li>';
                    if ($multi == 'y') {
                        $html .='<li id="eAddTab"><a style="font-size:13px; font-weight:bold">+ Lägg till ' . $label . '</a></li>'; 
                        $html .='<li id="eRemoveTab"><a style="font-size:13px; font-weight:bold">- Ta bort ' . $label . '</a></li>'; 
                    }
                $html .='</ul>';  
            $html .='</div>';
        $html .='</div>';
    $html .='</div> ';
    return $html;
}

function webformSpecToolbar() {
    $html = '';
    $html .= '<div class="columns">';
        $html .= '<div class="column tool-panel" style="padding-top:6px;">';  
            $html .= '<a class="button eToolLabel" id="eBoxSelectionNew"><span class="icon is-small"><i class="fas fa-plus"></i></span>&nbsp;&nbsp;Lägg till Urval</a>';
            $html .= '&nbsp;&nbsp;';
            $html .= '<a class="button eToolLabel" id="eBoxActiveNote"><span class="icon is-small"><i class="fas fa-plus"></i></span>&nbsp;&nbsp;Lägg Fritext</a>';
        $html .= '</div>';
    $html .= '</div>';

    return $html;
}

function webformInfoBoxText($label, $id, $inputClass, $maxlength='100', $toolOption, $placeholder = '') {

    $html = '';
    $html .= '<div class="columns ' . $id . '-panel">';
        $html .= '<div class="column">';
            $html .= '<input disabled="disabled" value= "' . $label . '" class="webform-label webform-text-color" id="' . $id . '-label" type="text"  maxlength="100" autocomplete="off"/>';
            $html .= '<a itemid="' . $id .  '" action="cancel" style="display:none" class="button webform-edit-panel-cancel eEditPanel edit-panel-' . $id .'">';
                $html .= '<span class="icon is-small"><i class="fas fa-times"></i></span>';
            $html .= '</a>';
            $html .= '<a itemid="' . $id .  '" action="ok" style="display:none" class="button webform-edit-panel-ok is-primary eEditPanel edit-panel-' . $id .'">';
                $html .= '<span class="icon is-small"><i class="fas fa-check"></i></span>';
            $html .= '</a>';
        $html .= '</div>';
    $html .= '</div>';

    $html .= '<div class="columns ' . $id . '-panel">';
        $html .= '<div class="column">';
           
            $html .= '<textarea id="' . $id . '" style="width: 88%;" class="textarea" rows="2" disabled="disabled" maxlength="' . $maxlength . '"></textarea>';
            //$html .= '<a itemid="' . $id .  '" action="cancel" style="background-color: #efefef; border-color: #cccccc; font-size:13px; padding: 16px; display:none" class="button eEditValue edit-value-' . $id .'"><span class="icon is-small"><i class="fas fa-times"></i></span></a>';
            //$html .= '<a itemid="' . $id .  '" action="ok" style="padding: 16px; display:none" class="button is-primary eEditValue edit-value-' . $id .'"><span class="icon is-small"><i class="fas fa-check"></i></span></a>';
        $html .='</div>';
    $html .='</div>';

    $html .= '<div class="columns ' . $id . '-panel tool-panel">';
        $html .= '<div class="column">';

            // -- Edit label
            if ($toolOption[0]) {
                $html .= '<a class="button eToolLabel" itemid="' . $id .  '"><span class="icon is-small"><i class="far fa-edit"></i></span>&nbsp;&nbsp;Rubrik</a>';
                $html .= '&nbsp;&nbsp;';
            }
            // -- Edit value
            if ($toolOption[1]) {
                $html .= '<a class="button eToolValue" itemid="' . $id . '"><span class="icon is-small"><i class="far fa-edit"></i></span>&nbsp;&nbsp;Värde</a>';
                $html .= '&nbsp;&nbsp;';
            }

            // -- Help 
            if ($toolOption[2]) {
                $html .= '&nbsp;&nbsp;';
                $html .= '<a class="button"><span class="icon is-small"><i class="fas fa-info"></i></span></a>';
            }

        $html .='</div>';
    $html .='</div>';

    return $html;

}

function webformPanel() {
    // Use 
    // -- webFormPanelInput
    // - webFormPanelYesNo
    // - webFormPanelDate
    $html = '<table class="">';
  
    $html .= '<tr><td colspan="2" class="webform-panel-header">Inställningar</td></tr>';
   
    $html .= '<tr>';
   
    $html .= webformPanelInput('Eventnamn', 'event_name', 80);
    $html .= webformPanelYesNo('Publik', 'private_on');
    $html .= webformPanelInput('Formulärlänk', 'event-url', 80, 'event_url-panel');
    //$html .= webformPanelYesNo('Tidsbegränsat', 'limited_time_on');
    //$html .= webformPanelDate('Startdatum', 'start_date', 'limited_time-panel');
    //$html .= webformPanelDate('Slutdatum', 'end_date', 'limited_time-panel');
    $html .= webformPanelYesNo('Webformulär', 'webform_on');
    $html .= webformPanelYesNo('Moms på faktura', 'has_vat', 'has_vat-panel');

    $html .= '<tr><td colspan="2" class="webform-panel-header">Fält</td></tr>';

    $html .= webformPanelYesNo('Standardbelopp', 'amount_on');
    $html .= webformPanelYesNo('Mobilnummer', 'mobile_on');
    $html .= webformPanelYesNo('Infobox 1:', 'infobox_1_on');
    $html .= webformPanelYesNo('infobox 2:', 'infobox_2_on');
    $html .= webformPanelYesNo('Företagsadress:', 'company_address_on');

    $html .= '<tr><td colspan="2" class="webform-panel-header">Deltagare</td></tr>';
    $html .= webformPanelYesNo('Deltagare', 'participant_on');
    $html .= webformPanelInput('Rubrik deltagare', 'participant_title', 12, 'participant-panel');
    
    $html .= webformPanelYesNo('Begränsat antal deltagare', 'participant_limit_on', 'participant-panel participant_max-panel');
    $html .= webformPanelInput('Max antal deltagare', 'participant_max', 6, 'participant-panel participant_max-panel participant_max-panel-value');
    $html .= webformPanelYesNo('Begränsat antal per anmälan', 'participant_apply_limit_on', 'participant-panel participant_apply-max-panel');
    $html .= webformPanelInput('Max antal per anmälan', 'participant_apply_max', '2', 'participant-panel participant-apply_max-panel participant-apply_max-panel-value');
    
    //$html .= webformPanelYesNo('Personnr', 'participant_personal_id_on', 'participant-panel');
    $html .= webformPanelYesNo('Kontaktuppgifter', 'participant_address_on', 'participant-panel');
    $html .= webformPanelYesNo('Hämta från SPAR', 'collect_spar_on', 'participant-panel spar-panel');
    $html .= webformPanelYesNo('Födelsedatum', 'date_of_birth_on', 'participant-panel date-of-birth'); 
    // $html .= webformPanelYesNo('Fritextfält', 'note_on', 'participant-panel');
   
    $html .= '<tr><td colspan="2" class="webform-panel-header">Design</td></tr>';
    $html .= webformPanelYesNo('Logotyp som bild', 'header_image_on');
    $html .= webformPanelInput('Logotype text', 'header_title', 60, 'header_title-panel');

    $html .= '<tr class="logo-list-panel">';
        $html .= '<th>' . 'Arkiv logotyp' . '</th>';
        $html .= '<td>';
            $html .= '<div class="select">';
            $html .= '<select id="logo-list"></select>';
            $html .= '</div>';
        $html .= '</td>';
    $html .= '</tr>';
      
    $html .= '<tr>';
        $html .= '<td colspan="2">';
            $html .=  '<button id="eSelectFile" class="button is-small is-dark">Ladda upp logotyp</button>';
        $html .= '</td>';
    $html .= '</tr>';
    

    $html .= '<tr><td colspan="2" class="webform-panel-header">Bilagor</td></tr>';
    $html .= webformPanelYesNo('Bifoga', 'has_attach');
   
    $html .= '<tr class="attach-list-panel">';
        $html .= '<th>' . 'Bilagor' . '</th>';
        $html .= '<td>';
            $html .= '<div class="select">';
                $html .= '<select id="attach-list"></select>';
            $html .= '</div>';
            $html .= '<button index="0" id="eEventAttachRemove" class="button is-dark is-small is-pulled-right"><i class="fas fa-times"></i></button>';
            // $html .= '<div style="clear: both;"></div>';
        $html .= '</td>';
    $html .= '</tr>';
      
    $html .= '<tr class="attach-list-panel">';
        $html .= '<td colspan="2">';
            $html .=  '<button id="eSelectAttach" class="button is-small is-link">Ladda upp bilaga</button>';
        $html .= '</td>';
    $html .= '</tr>';
 
    $html .= '</table>';

    //$html .= '</div>';

    return $html;
}


function webformPanelDate($label, $id, $panelClass = '' ,$placeholder = '') {
    $html = '';
    if (strlen($panelClass) > 0 ) {
        $html .= '<tr class="' . $panelClass . '">';
    }
    else {
        $html .= '<tr>';
    }
        $html .= '<th>' . $label . '</th>';
        $html .= '<td>';
        $html .= '<input type="date" class="form-control" id="' . $id . '">';
        $html .= '</td>';
    $html .= '</tr>';

    return $html;
}

function webformPanelInput($label, $id, $maxlength, $panelClass = '' ,$placeholder = '') {

    $html = '';
    if (strlen($panelClass) > 0 ) {
        $html .= '<tr class="' . $panelClass . '">';
    }
    else {
        $html .= '<tr>';
    }
        $html .= '<th>' . $label . '</th>';
        $html .= '<td>';
            $html .= '<input class="" id="' . $id . '" type="text" placeholder="' . $placeholder . '"  maxlength="' . $maxlength . '" autocomplete="off"/>';
        $html .= '</td>';
    $html .= '</tr>';

    return $html;
}

function webformPanelYesNo($label, $id, $panelClass = '') {
    $html = '';
    if (strlen($panelClass) > 0 ) {
        $html .= '<tr class="' . $panelClass . '">';
    }
    else {
        $html .= '<tr>';
    }
        $html .= '<th>' . $label . '</th>';
        $html .= '<td>';
            //$html .= '<div class="select">';
                $html .= '<select class="ePanelYes" id="' . $id . '">';
                    $html .= '<option value="n">Av</option>';
                    $html .= '<option value="y">På</option>';
                $html .= '</select>';
            //$html .= '</div>';
        $html .= '</td>';
    $html .= '</tr>';

    return $html;
}

function webformYesNoRemoveSelection() {
    $html = '';
    $html .='<div class="modal" id="yesno-remove-selection-modal">';
    $html .='<div class="modal-background"></div>';
    $html .='<div class="modal-card pl0 pr0  modal-width">';
    $html .='<header class="modal-card-head">';
    $html .='<p class="modal-card-title has-text-centered">Kontrollfråga</p>';
    $html .='</header>';
    $html .='<section class="modal-card-body">';
    $html .='<p class="remove-selection-warning has-text-centered" style="margin-bottom:2px; font-weight:bold">VARNING!</p>';
    $html .='<p class="remove-selection-warning has-text-centered" style="font-size: 12px; font-style:italic; margin-bottom:8px">Vidarekopplingar kommer att gå förlorade</p>';
    $html .='<p class="has-text-centered" style="margin-bottom:24px" id="yesno-text-modal">Är du säker på att du vill ta bort urval?</p>';
    $html .='</section>';
    $html .='<footer class="modal-card-foot">';
    $html .='<button id="eYesNoRemoveSelectionNo" class="button is-dark w120 image-center">Avbryt</button>';
    $html .='<button id="eYesNoRemoveSelectionYes" class="button is-primary w120 image-center">Ja</button>';
    $html .='</footer>';
    $html .='</div>';
    $html .='</div>';
    return $html;
}

function attachRemoveModal() {
    $html = '';
    $html .='<div class="modal" id="attach-remove-modal">';
    $html .='<div class="modal-background"></div>';
    $html .='<div class="modal-card pl0 pr0  modal-width">';
    $html .='<header class="modal-card-head">';
    $html .='<p class="modal-card-title has-text-centered">Ta bort bilaga</p>';
    $html .='</header>';
    $html .='<section class="modal-card-body">';
    $html .='<p class="has-text-centered" style="margin-bottom:24px" id="attach_remove-yesno-text-modal">Är du säker på att du vill ta bort bilaga?</p>';
    $html .='</section>';
    $html .='<footer class="modal-card-foot">';
    $html .='<button id="eAttachRemoveNo" class="button is-dark w120 image-center">Avbryt</button>';
    $html .='<button id="eAttachRemoveYes" class="button is-primary w120 image-center">Ja</button>';
    $html .='</footer>';
    $html .='</div>';
    $html .='</div>';
    return $html;
}

function webformYesNoRemoveNote() {
    $html = '';
    $html .='<div class="modal" id="yesno-remove-note-box">';
    $html .='<div class="modal-background"></div>';
    $html .='<div class="modal-card pl0 pr0  modal-width">';
    $html .='<header class="modal-card-head">';
    $html .='<p class="modal-card-title has-text-centered">Kontrollfråga</p>';
    $html .='</header>';
    $html .='<section class="modal-card-body">';
    //$html .='<p class="remove-selection-warning has-text-centered" style="margin-bottom:2px; font-weight:bold">VARNING!</p>';
    // $html .='<p class="remove-selection-warning has-text-centered" style="font-size: 12px; font-style:italic; margin-bottom:8px">Vidarekopplingar kommer att gå förlorade</p>';
    $html .='<p class="has-text-centered" style="margin-bottom:24px" id="yesno-text-modal">Är du säker på att du vill ta bort urval?</p>';
    $html .='</section>';
    $html .='<footer class="modal-card-foot">';
    $html .='<button id="eYesNoRemoveNoteNo" class="button is-dark w120 image-center">Avbryt</button>';
    $html .='<button id="eYesNoRemoveNoteYes" class="button is-primary w120 image-center">Ja</button>';
    $html .='</footer>';
    $html .='</div>';
    $html .='</div>';
    return $html;
}

function webformSelections() {
    $html = '';

    $html .= '<div id="box-selection"  class="modal">';
        $html .= '<div class="modal-background"></div>';
        $html .= '<div class="modal-card" style="max-height:500px; height:500px">';
            $html .= '<header class="modal-card-head" style="padding-top: 12px; padding-bottom:0; background-color: #8dbf3b;">';
                $html .= '<p class="modal-card-title" style="color:#ffffff">Urval - Inställning</p>'; 
            $html .= '</header>';

            $html .= '<section class="modal-card-body">';

                $html .= '<form id="box-selection-form">';
                    $html .= '<div class="columns" style="padding-top:12px">';
                        $html .= '<div class="column modal-column">';
                            $html .= '<label class="modal-label">&nbsp;Urvalsrubrik <span style="font-weight: normal">(max 27 tecken)</span></label>';
                            $html .= '<input type="text" maxlength="27" id="selection_header" class="input is-primary modal-input no-comma">';
                        $html .= '</div>';
                    $html .= '</div>';
                
                    $html .= '<div class="columns" style="padding-top:4px">';
                        $html .= '<div class="column  modal-column">';
                            $html .= '<label class="checkbox modal-label">';
                                $html .= '&nbsp;&nbsp;Obligatoriskt val&nbsp;&nbsp;&nbsp;';
                                $html .= '<input type="checkbox" id="selection_required">';
                            $html .= '</label>'>
                        $html .= '</div>'; 
                    $html .= '</div>'; 

                    $html .= '<div class="columns" style="height:42px">'; 
                        $html .= '<div class="column" style="padding-top:2px;">';
                            $html .= '<div class="buttons is-right" style="width:100%;">';
                                $html .= '<span id="eBoxSelectionAdd" style="width:84px; margin-bottom:0; margin-right:14px;" class="button is-primary" >Lägg till</span>';
                            $html .= '</div>';
                        $html .= '</div>'; 
                    $html .= '</div>';

                    $html .= '<div class="columns" style="margin-top: -24px">';
                        $html .= '<div class="column" style="padding-top:0">';
                            $html .= '<div id="box-selection-list"></div>';
                        $html .= '</div>'; 
                    $html .= '</div>';

                      

                $html .= '</form>';

            $html .= '</section>';  

            $html .= '<footer class="modal-card-foot" style="padding-top: 10px; padding-bottom:10px;">';
                $html .= '<div class="buttons is-right" style="width:100%">';
                    $html .= '<span id="eBoxSelectionClose" style="width:84px" class="button" >Avbryt</span>';
                    $html .= '<span id="eBoxSelectionSave" style="width:84px" class="button is-primary" >Spara</span>';
                $html .= '</div>';
            $html .= '</footer>';
        $html .= '</div>';
    $html .= '</div>';

    return $html;
} 

function webformBankidSection($paymentText, $isMobile, $bankIdText, $buttonLabel ) {
    $html = '';

    $html .='<div class="columns" style="margin-top: 12px">';
        $html .='<div class="column">';
            $html .='<p style="font-size:14px" id="webform-payment-text">';
                
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
            $html .='<button class="button is-large" id="eConfirm" style="width:100%">';
                $html .='<span class="icon is-medium">';
                //$html .='<img src="' .  $host . $lib . '/images/icon_64x64.png" alt="" class="bankid-logo" height="40" width="40"/>';
                    $html .='<img src="images/icon_64x64.png" alt="" />';
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


function webformRowInput($label, $id, $inputClass, $maxlength='100', $toolOption, $placeholder = '') {
    // --
    // Tool options
    // 0 - rubrik
    // 1 - värde
    // 2 - info
    // 3 - remove

    $html = '';
    $html .= '<div class="columns ' . $id . '-panel">';
        $html .= '<div class="column">';
            $html .= '<input disabled="disabled" value= "' . $label . '" class="webform-label webform-text-color" id="' . $id . '-label" type="text"  maxlength="100" autocomplete="off"/>';
            $html .= '<a itemid="' . $id .  '" action="cancel" style="display:none" class="button webform-edit-panel-cancel eEditPanel edit-panel-' . $id .'">';
                $html .= '<span class="icon is-small"><i class="fas fa-times"></i></span>';
            $html .= '</a>';
            $html .= '<a itemid="' . $id .  '" action="ok" style="display:none" class="button webform-edit-panel-ok is-primary eEditPanel edit-panel-' . $id .'">';
                $html .= '<span class="icon is-small"><i class="fas fa-check"></i></span>';
            $html .= '</a>';
        $html .= '</div>';
    $html .= '</div>';

    $html .= '<div class="columns ' . $id . '-panel">';
        $html .= '<div class="column">';
            $html .= '<input disabled="disabled" class="webform-input webform-input-color ' . $inputClass . '" id="' . $id . '" type="text" placeholder="' . $placeholder . '"  maxlength="' . $maxlength . '" autocomplete="off"/>';
            $html .= '<a itemid="' . $id .  '" action="cancel" style="background-color: #efefef; border-color: #cccccc; font-size:13px; padding: 16px; display:none" class="button eEditValue edit-value-' . $id .'"><span class="icon is-small"><i class="fas fa-times"></i></span></a>';
            $html .= '<a itemid="' . $id .  '" action="ok" style="padding: 16px; display:none" class="button is-primary eEditValue edit-value-' . $id .'"><span class="icon is-small"><i class="fas fa-check"></i></span></a>';
        $html .='</div>';
    $html .='</div>';

    $html .= '<div class="columns ' . $id . '-panel tool-panel">';
        $html .= '<div class="column">';

            // -- Edit label
            if ($toolOption[0]) {
                $html .= '<a class="button eToolLabel" itemid="' . $id .  '"><span class="icon is-small"><i class="far fa-edit"></i></span>&nbsp;&nbsp;Rubrik</a>';
                $html .= '&nbsp;&nbsp;';
            }
            // -- Edit value
            if ($toolOption[1]) {
                $html .= '<a class="button eToolValue" itemid="' . $id . '"><span class="icon is-small"><i class="far fa-edit"></i></span>&nbsp;&nbsp;Värde</a>';
                $html .= '&nbsp;&nbsp;';
            }

            // -- Help 
            if ($toolOption[2]) {
                $html .= '&nbsp;&nbsp;';
                $html .= '<a class="button"><span class="icon is-small"><i class="fas fa-info"></i></span></a>';
            }
            if (isset($toolOption[3])) {
                if ($toolOption[3]) {
                    // $html .= '&nbsp;&nbsp;';
                    $html .= '<a class="button is-dark eToolRemove" itemid="' . $id . '"><span class="icon is-small"><i class="fas fa-times"></i></span></a>';
                }
            }

        $html .='</div>';
    $html .='</div>';


    return $html;
}

function webformEventText() {

    $html = '';
    $html .= '<div class="columns">';
        $html .= '<div class="column">';
            $html .= '<p id="intro_text_edit" class="webform-intro-text webform-text-color"></p>';
            $html .= '<textarea id="intro_text" style="width: 88%; color:#eeeeee; background-color:#666666;display:none" class="webform-intro-text-edit" rows="12"></textarea>';
        $html .= '</div>';
    $html .= '</div>';

    //$html .= '<div class="control tool-panel" style="padding-top:6px;">';  
    $html .= '<div class="columns tool-panel">';
        $html .= '<div class="column">';
            $html .= '<a class="button eEditIntroText" ><span class="icon is-small"><i class="far fa-edit"></i></span>&nbsp;&nbsp;Event beskrivning</a>';
            // -- $html .= '&nbsp;&nbsp;';
            // -- $html .= '<a class="button"><span class="icon is-small"><i class="fas fa-info"></i></span></a>';
            $html .= '&nbsp;&nbsp;';
            $html .= '<a action="cancel" style="background-color: #efefef; border-color: #cccccc; font-size:13px; padding: 16px; display:none" class="button eEditPanelIntroText"><span class="icon is-small"><i class="fas fa-times"></i></span></a>';
            $html .= '&nbsp;&nbsp;';
            $html .= '<a action="ok" style="padding: 16px; display:none" class="button is-primary eEditPanelIntroText"><span class="icon is-small"><i class="fas fa-check"></i></span></a>';
        $html .= '</div>';
    $html .= '</div>';

    return $html;
}


function webformRowInputAmount($label, $id, $inputClass, $maxlength='100', $toolOption, $placeholder = '') {
    // --
    // Tool options
    // 0 - rubrik
    // 1 - värde
    // 2 - info
    // 3 - remove

    $html = '';
    $html .= '<div class="columns" style="margin-top:0;">';
        $html .= '<div class="column standard-amount-panel">';
            $html .= '<input disabled="disabled" value= "' . $label . '" class="webform-label webform-text-color" id="' . $id . '-label" type="text"  maxlength="100" autocomplete="off"/>';
            $html .= '<a itemid="' . $id .  '" action="cancel" style="display:none" class="button webform-edit-panel-cancel eEditPanel edit-panel-' . $id .'">';
                $html .= '<span class="icon is-small"><i class="fas fa-times"></i></span>';
            $html .= '</a>';
            $html .= '<a itemid="' . $id .  '" action="ok" style="display:none" class="button webform-edit-panel-ok is-primary eEditPanel edit-panel-' . $id .'">';
                $html .= '<span class="icon is-small"><i class="fas fa-check"></i></span>';
            $html .= '</a>';
        $html .= '</div>';
        $html .= accountingPanel1('accounting-standard', 'accounting-standard-panel');
    $html .= '</div>';

    $html .= '<div class="columns" style="margin-top:0;">';
        $html .= '<div class="column standard-amount-panel">';
            $html .= '<input disabled="disabled" class="webform-input webform-input-color ' . $inputClass . '" id="' . $id . '" type="text" placeholder="' . $placeholder . '"  maxlength="' . $maxlength . '" autocomplete="off"/>';
            $html .= '<a itemid="' . $id .  '" action="cancel" style="background-color: #efefef; border-color: #cccccc; font-size:13px; padding: 16px; display:none" class="button eEditValue edit-value-' . $id .'"><span class="icon is-small"><i class="fas fa-times"></i></span></a>';
            $html .= '<a itemid="' . $id .  '" action="ok" style="padding: 16px; display:none" class="button is-primary eEditValue edit-value-' . $id .'"><span class="icon is-small"><i class="fas fa-check"></i></span></a>';
        $html .='</div>';
        $html .= accountingPanel2('accounting-standard', 'accounting-standard-panel', 'ddAccountStandardList');
    $html .='</div>';

    $html .= '<div class="columns tool-panel" style="margin-top:0;">';
        $html .= '<div class="column standard-amount-panel">';

            // -- Edit label
            if ($toolOption[0]) {
                $html .= '<a class="button eToolLabel" itemid="' . $id .  '"><span class="icon is-small"><i class="far fa-edit"></i></span>&nbsp;&nbsp;Rubrik</a>';
                $html .= '&nbsp;&nbsp;';
            }
            // -- Edit value
            if ($toolOption[1]) {
                $html .= '<a class="button eToolValue" itemid="' . $id . '"><span class="icon is-small"><i class="far fa-edit"></i></span>&nbsp;&nbsp;Värde</a>';
                $html .= '&nbsp;&nbsp;';
            }

            // -- Help 
            if ($toolOption[2]) {
                $html .= '&nbsp;&nbsp;';
                $html .= '<a class="button"><span class="icon is-small"><i class="fas fa-info"></i></span></a>';
            }
            if (isset($toolOption[3])) {
                if ($toolOption[3]) {
                    // $html .= '&nbsp;&nbsp;';
                    $html .= '<a class="button is-dark eToolRemove" itemid="' . $id . '"><span class="icon is-small"><i class="fas fa-times"></i></span></a>';
                }
            }

        $html .='</div>';
        $html .= accountingPanel3('accounting-standard', 'accounting-standard-panel');
    $html .='</div>';


    return $html;
}


function accountingPanel1($id, $panel) {

    $html = '';
    //$html .= ' <div class="columns accounting-panel">';
    $html .= '<div class="column ' . $panel . '">';
    $html .= '<input disabled="disabled" value="Kontering" class="webform-label webform-text-color"  type="text"  style="color: rgb(34, 34, 34);">';
    $html .= '<a itemid="' . $id . '" action="cancel" style="display:none" class="button webform-edit-panel-cancel eEditPanel edit-panel-accounting">';
    $html .= '<span class="icon is-small">';
    $html .= '<i class="fas fa-times"></i>';
    $html .= '</span>';
    $html .= '</a>';
    $html .= '<a itemid="' . $id . '" action="ok" style="display:none" class="button webform-edit-panel-ok is-primary eEditPanel edit-panel-accouting">';
    $html .= '<span class="icon is-small">';
    $html .= '<i class="fas fa-check"></i>';
    $html .= '</span>';
    $html .= '</a>';
    $html .= '</div>';
    // $html .= '</div>';
    return $html;
}

function accountingPanel2($id, $panel, $ddList) {
    $html = '';
    // $html .='<div class="columns accounting-panel">';
    $html .= '<div class="column ' . $panel . '">';
    $html .= '<div class="select">';
    $html .= '<select id="' . $ddList . '" disabled="disabled">';
                // echo '<option value="2">3100 Terminsavgift</option><option value="3">3200 Medlemsavgift</option><option value="4">3300 Lägeravgift</option>';
    $html .= '</select>';
    $html .= '</div>';
        
    $html .= '<a itemid="' . $id . '" action="cancel" style="background-color: #efefef; border-color: #cccccc; font-size:13px; padding: 16px; display:none" class="button eEditValue edit-value-' . $id . '">';
    $html .= '<span class="icon is-small">';
    $html .= '<i class="fas fa-times"></i>';
    $html .= '</span>';
    $html .= '</a>';
    $html .= '<a itemid="' . $id . '" action="ok" style="padding: 16px; display:none" class="button is-primary eEditValue edit-value-' . $id . '">';
    $html .= '<span class="icon is-small">';
    $html .= '<i class="fas fa-check"></i>';
    $html .= '</span>';
    $html .= '</a>';
    $html .= '</div>';
    //$html .= '</div>';
    return $html;
}

function accountingPanel3($id, $panel) {
    $html = '';
    // $html .= '<div class="columns accounting-panel tool-panel">';
    $html .= '<div class="column ' . $panel . '">';
    
    $html .= '<a class="button eToolValue" itemid="' . $id . '">';
    $html .= '<span class="icon is-small">';
    $html .= '<i class="far fa-edit"></i>';
    $html .= '</span>';
    $html .= '&nbsp;&nbsp;Konto</a>&nbsp;&nbsp;';
    $html .= '</div>';
    
    // $html .= '</div>';

    return $html;
}

function accountingPanel() {

    $html = '';
    $html .= ' <div class="columns accounting-panel">';
    $html .= '<div class="column">';
    $html .= '<input disabled="disabled" value="Kontering" class="webform-label webform-text-color"  type="text"  style="color: rgb(34, 34, 34);">';
    $html .= '<a itemid="accounting" action="cancel" style="display:none" class="button webform-edit-panel-cancel eEditPanel edit-panel-accounting">';
    $html .= '<span class="icon is-small">';
    $html .= '<i class="fas fa-times"></i>';
    $html .= '</span>';
    $html .= '</a>';
    $html .= '<a itemid="accounting" action="ok" style="display:none" class="button webform-edit-panel-ok is-primary eEditPanel edit-panel-accouting">';
    $html .= '<span class="icon is-small">';
    $html .= '<i class="fas fa-check"></i>';
    $html .= '</span>';
    $html .= '</a>';
    $html .= '</div>';
    $html .= '</div>';

    $html .='<div class="columns accounting-panel">';
    $html .= '<div class="column">';
    $html .= '<div class="select">';
    $html .= '<select id="ddAccountList" disabled="disabled">';
                // echo '<option value="2">3100 Terminsavgift</option><option value="3">3200 Medlemsavgift</option><option value="4">3300 Lägeravgift</option>';
    $html .= '</select>';
    $html .= '</div>';
        
    $html .= '<a itemid="accounting" action="cancel" style="background-color: #efefef; border-color: #cccccc; font-size:13px; padding: 16px; display:none" class="button eEditValue edit-value-accounting">';
    $html .= '<span class="icon is-small">';
    $html .= '<i class="fas fa-times"></i>';
    $html .= '</span>';
    $html .= '</a>';
    $html .= '<a itemid="accounting" action="ok" style="padding: 16px; display:none" class="button is-primary eEditValue edit-value-accounting">';
    $html .= '<span class="icon is-small">';
    $html .= '<i class="fas fa-check"></i>';
    $html .= '</span>';
    $html .= '</a>';
    $html .= '</div>';
    $html .= '</div>';

    $html .= '<div class="columns accounting-panel tool-panel">';
    $html .= '<div class="column">';
    
    $html .= '<a class="button eToolValue" itemid="accounting">';
    $html .= '<span class="icon is-small">';
    $html .= '<i class="far fa-edit"></i>';
    $html .= '</span>';
    $html .= '&nbsp;&nbsp;Konto</a>&nbsp;&nbsp;';
    $html .= '</div>';
    
    $html .= '</div>';

    return $html;

}