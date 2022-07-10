<?php

 // $OfferText = 'Inbetalning av lånebeloppet sker på inbetalningsavi/skuldebrev som skickas till din e-postadress efter att du har bekräftat lånevillkoren med BankID nedan.';
$OfferText = 'Inbetalningsavi/skuldebrev skickas till din e-postadress efter att du har bekräftat villkoren med BankID nedan.';


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
   

        // ---
        // --- Create each option
        // ---
        if (sizeof($Action->selection) > 0 ) {
            $newRow = true;
            for ($i = 0; $i < sizeof($Action->selection); $i++) { 
                if ($newRow == true) {
                    echo htmlColumns('view-1');
                    $newRow = false;
                    $gridCol = 0;
                }
                $gridCol++;
                echo htmlColumn();
                
                if ($i < sizeof($Action->selection)) {
                    echo webformOptionsCreate($Action->selection[$i]['text'], $i, $Action->selection[$i]['option'], $Action->eventId);
                }
                echo htmlDivEnd();  
                if ($gridCol == $Action->event['option_grid']) {
                    echo htmlDivEnd();
                    $newRow = true;
                }
            }
            if ($newRow == false) {
                for ($i = 0; $i <= $gridCol; $i++) {
                    echo htmlColumn();
                    echo htmlDivEnd();
                }
                echo htmlDivEnd();
            }
        }

        echo webformRowInput($Action->event['personal_id_number_label'], 'personal_id_number', 'webform-personal-id-number', '12', 'ååååmmddnnnn');
      
         // If invpice_event_id set email
         if ($Action->invoiceEventItemId > 0) {
            echo webformRowInputValue($Action->event['email_label'], 'email', 'webform-email', '100', $Action->invoiceEvent['email']);
        }
        else {
             echo webformRowInput($Action->event['email_label'], 'email', 'webform-email', '100');
        }
        if ($Action->event['mobile_on'] == 'y') {
            echo webformRowInput($Action->event['mobile_label'], 'mobile', 'webform-mobile is only-numeric', '24');
        }

    /*
    if ($Action->event['infobox_1_on'] == 'y') {
        echo webformInfoBoxText($Action->event['infobox_1_label'], 'infobox_1', '', '512');
    }

    if ($Action->event['infobox_2_on'] == 'y') {
        echo webformInfoBoxText($Action->event['infobox_2_label'], 'infobox_2', '', '512');
    }
    */

    echo '<div class="columns view-1" style="padding-top:8px">';
        echo '<div class="column is-one-quarter">';
            echo '<div class="field">';
                echo '<label class="label">' . $Action->event['infotext_small_1_label'] . '</label>';
                echo '<div class="control">';
                    echo '<input type="text" id="infotext-small-1" maxlength="5" class="webform-input webform-color only-numeric" style="width:100px; padding-right:0;background-color: #ffffff" autocomplete="off">';
                echo '</div>';
            echo '</div>';
        echo '</div>';

        echo '<div class="column">';
            echo '<div class="field">';
                echo '<label class="label">' . $Action->event['infotext_1_label'] . '</label>';
                echo '<div class="control">';
                    echo '<input type="text" id="infotext-1" maxlength="12" class="webform-input webform-color only-numeric" style="width: 400px; padding-right:0;background-color: #ffffff" autocomplete="off">';
                echo '</div>';
            echo '</div>';
        echo '</div>';
    echo '</div>';


    echo webformBankIdSection($OfferText, $Action->isMobile, $Action->bankidText, $Action->confirmLabel, SITE_URL, LIB);

    echo webformFooter($Action->companyKnownAs . ' i samarbete med Turtle Pay AB.', 'www.turtle-pay.com, tel. 08-806220');

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
function webformRowInput($label, $id, $inputClass, $maxlength='100', $placeholder = '') {

    $html = '';
    $html .= '<div class="columns ' . $id . '-panel">';
        $html .= '<div class="column">';
            $html .= '<label class="webform-label webform-text-color">' . $label . '</label/>';
        $html .= '</div>';
    $html .= '</div>';

    $html .= '<div class="columns ' . $id . '-panel">';
        $html .= '<div class="column">';
            $html .= '<input class="webform-input webform-input-color ' . $inputClass . '" id="' . $id . '" type="text" placeholder="' . $placeholder . '"  maxlength="' . $maxlength . '" autocomplete="off"/>';
        $html .='</div>';
    $html .='</div>';

    return $html;
}

function webformRowInputValue($label, $id, $inputClass, $maxlength='100', $value, $disabled = FALSE) {

    $html = '';
    $html .= '<div class="columns ' . $id . '-panel">';
        $html .= '<div class="column">';
            $html .= '<label class="webform-label webform-text-color">' . $label . '</label/>';
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

function webformOptionsCreate($text, $index, $option, $eventId, $initLabel = '--- Välj ---' ) {
    $html = '';
    $html .= '';
    $html .= '<label class="label">' . $text . '</label>';
    $html .= '<div class="select" style="width:100%">';
    $html .= '<select class="select-option" id="option-' . $index .  '" style="width:100%">';
    $html .= '<option selected value="8E1C7E8F67D0">' . $initLabel . '</option>';
        for ($j = 0; $j < sizeof($option); $j++) { 
            if ($eventId == '5' && $option[$j]['webform_option_id'] == '25') {
                // Skip
            }
            else {
                $html .= '<option value="' . $option[$j]['value'] . '">' . $option[$j]['text']  . '</option>';
            }
        }
        $html .=  '</select>';
    $html .=  '</div>';

    return $html;
}

function webformInfoBoxText($label, $id, $inputClass, $maxlength='100') {

    $html = '';
    $html .= '<div class="columns ' . $id . '-panel">';
        $html .= '<div class="column">';
            $html .= '<label class="webform-label webform-text-color">' . $label . '</label/>';
        $html .= '</div>';
    $html .= '</div>';
  
    $html .= '<div class="columns ' . $id . '-panel">';
        $html .= '<div class="column">';
            $html .= '<textarea id="' . $id . '" style="width: 88%;" class="textarea" rows="1" maxlength="' . $maxlength . '"></textarea>';
            //$html .= '<input class="webform-input webform-input-color ' . $inputClass . '" id="' . $id . '" type="text" maxlength="' . $maxlength . '" autocomplete="off"/>';
        $html .='</div>';
    $html .='</div>';

    return $html;

}

function webformRowMultiInput($form) {

    $html = '';
    $html .='<div class="columns ' . $form->viewClass . '">';
    for ($i=0; $i<$form->noOfColumns; $i++) {
        $html .='<div class="column">';
            $html .='<div class="field">';
                $html .='<label class="label">' . $form->column[$i]->label . '</label>';
                $html .='<div class="control">';
                    $html .='<input class="input ' . $form->column[$i]->class . '" id="' . $form->column[$i]->id . '" type="text" placeholder="' . $form->column[$i]->placeholder . '"  maxlength="' . $form->column[$i]->maxlength . '" autocomplete="off"/>';
                $html .='</div>';
            $html .='</div>';
        $html .='</div>';
    }
    $html .='</div>'; 

    return $html;
}

function webformParticipantTab($label, $multi) {
    $html = '';
    $html .='<div class="columns view-1" style="margin-top:0px">';
        $html .='<div class="column">';
            $html .='<div class="tabs is-small">';
                $html .='<ul>';
                    $html .='<li class="is-active participant-tab" index="0" style="font-size:13px"><a>' . $label . '</a></li>';
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
    $line1 = 'Turtle Pay AB';
    $line2 = 'www.turtle-pay.com, tel. 08-806220';
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