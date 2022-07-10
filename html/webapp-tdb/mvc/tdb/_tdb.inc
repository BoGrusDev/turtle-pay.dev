<?php
/*
    TDB - Form
*/

if ($Current->isMobile == 'yes') {
    echo '<section class="section" style="padding-bottom:0px">';
    echo '<div class="container">';
}
else {
    echo '<section class="section">';
    echo '<div class="container">';
}

    echo '<div id="webform" class="column no-padding-top">';      
        //
        // -- Header-image-panel
        // --
        if ($Current->items->header_image_on == 'y') {
            echo '<div class="columns has-text-centered-of" id="header-image-panel" >';
                echo '<div class="column">';
                    echo '<img id="header-image-src" src="' . WEBAPP_URL . '/logo/' . $Current->items->header_image . '" alt="" />';
                echo '</div>';
            echo '</div>';
        }
        else {
            // --
            // -- Header-text-panel
            // --
            echo '<div class="columns">';
                echo '<div class="column">';
                    echo '<h1 id="header-text-title" style="color:' . $Current->items->header_tcolor . '; background-color:' . $Current->items->header_bcolor . '">' . $Current->items->header_title . '</h1>';
                echo '</div>';
            echo '</div>';
        }

        echo '<div class="columns">';
            echo '<div class="column">';
                echo '<p id="webform-intro-text" class="webform-text-color">' . nl2br($Current->items->intro_text) . '</p>';
            echo '</div>';
        echo '</div>';

        echo webformRowInput($Current->items->personal_id_number_label, 'personal_id_number', 'webform-personal-id-number only-numeric', '12', true, 'ååååmmddnnnn');
        echo webformRowInputValue($Current->items->email_label, 'email', 'webform-email', '100', $Current->items->email, true);
            
        if ($Current->items->mobile_on == 'y') {
            echo webformRowInput($Current->items->mobile_label, 'mobile', 'webform-mobile is-numeric', '24', false);
        }
        /* 
            Company address
        */    
        echo '<div class="column" style="max-width:456px; padding-bottom:6px!important">';
            echo '<div class="columns" style="margin-top:0px">';
                echo '<div class="column" style="padding-left:0;">';
                    echo '<div class="field">';
                        echo '<label class="checkbox label">';
                            echo '<input type="checkbox" id="ePeopleCompanyOn">&nbsp;&nbsp;&nbsp;Företagsadress';
                        echo '</label>';
                    echo '</div>';
                echo '</div>';
            echo '</div>';
        echo '</div>';
        echo '<div id="company-adress-panel" style="display:none">'; // style="display:none"
            echo webformRowInput('Företagsnamn', 'people_company', 'webform-email no-special', '80', false);
            echo webformRowInput('Adress', 'people_company_address', 'webform-email no-special', '60', false);
            echo '<div class="column people_company-panel-postaddress" style="max-width:456px;">';
                echo '<div class="columns" style="margin-top:0px">';
                    echo '<div class="column" style="margin-top:-14px;max-width:140px;padding-left:0;padding-right:36px">';
                        echo '<div class="field">';
                            echo '<label class="label">Postnr</label>';
                            echo '<div class="control">';
                                echo '<input class="input is-numeric" id="people_company_postcode" type="text" placeholder="" maxlength="5" autocomplete="off">';
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
        echo '</div>';
        
        echo webformRowInputValue($Current->items->ref_label, 'receipt_number', 'webform-receipt-number', '60', $Current->items->ref, false, TRUE);
        

        echo '<div class="columns view-1">';
            echo '<div class="column" id="specification"></div>';
        echo '</div>';
		     
        if ($Current->items->infobox_1_on == 'y') {
            echo webformInfoBoxText($Current->items->infobox_1_label, 'infobox_1', 'no-special', '512');
        }
    
        if ($Current->items->infobox_2_on == 'y') {
            echo webformInfoBoxText($Current->items->infobox_2_label, 'infobox_2', 'no-special', '512');
        }

        echo webformBankIdSection($Current->items->settings, $Current->items->known_as, $Current->isMobile, WEBAPP_URL, LIB);

        echo webformFooter($Current->items->known_as . ' i samarbete med Turtle Pay AB.', 'www.turtle-pay.com, tel. 08-806220');

    echo '</div>';  


echo '<div class="modal" id="bankid-box">';
    echo '<div class="modal-background"></div>';
        echo '<div class="modal-card pl0 pr0  modal-width" style="margin-top: -150px!important">';
            echo '<header class="modal-card-head">';
                echo '<p class="modal-card-title has-text-centered">Signering</p>';
            echo '</header>';
            echo '<section class="modal-card-body">';
                echo '<p class="has-text-centered">Väntar på BankID signering</p>';
            echo '</section>';
        echo '<footer class="modal-card-foot">';
            echo '<button id="eBankIdBoxContinue" class="button is-dark w120 image-center" >Fortsätt</button>';
        echo '</footer>';
    echo '</div>';
echo '</div>';

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

function webformBankIdSection($settings, $companyName, $isMobile, $host, $lib) {

    $paymentText = 'Betalning sker mot ' . $settings->first_Invoice_due_days . ' dagars faktura ';
    $paymentText .= '<i>(';
    if ($settings->first_invoice_start_fee > 0) {
        $paymentText .= 'Uppläggningsavg. ' . $settings->first_invoice_start_fee . 'kr, ';
    }
    $paymentText .= '0' . '% ränta  under ' . $settings->credit_interest_grace_days . ' dagar och ' . $settings->first_invoice_fee . ' kr i aviavg.)</i> ';
    $paymentText .= 'som skickas till din e-postadress efter att du har bekräftat med BankID nedan.';
    $paymentText .= ' Fakturan kan även delbetalas i upp till ' . $settings->repayment_term . ' månader ';
    $paymentText .= '<i>(' . $settings->customerInterest . '% ränta och ' . $settings->monthly_invoice_fee  . ' kr i aviavg.';
    if ($settings->administration_fee > 0) {
        $paymentText .= ' Adm. avg. ' . $settings->administration_fee . 'kr/mån';
    }
    $paymentText .= ', effektiv ränta ' . $settings->effective_rate . '% på 10 000 kr)</i>. ';
    $paymentText .= ' Se villkor under <a href="https://www.turtle-pay.com/villkor" target="_blank">www.turtle-pay.com/villkor</a>';
    $paymentText .= ' och integritetspolicy <a href="https://www.turtle-pay.com/integritetspolicy" target="_blank">www.turtle-pay.com/integritetspolicy</a>.';

    // GDPR
    $paymentText .=  ' Du samtycker samtidigt att Turtle Pay behandlar dina personuppgifter åt ';
    $paymentText .= $companyName; 
    $paymentText .=  ', enligt deras integritetspolicy.';


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
        $html .= '<input type="checkbox" id="eBankIdInternal" checked>';
    }
    else {
        $html .= '<input type="checkbox" id="eBankIdInternal">';
    }
    $html .= ' ' . '<b>Jag har BankID på denna enhet</b>'; 
    $html .= '</label>';
    $html .= '</div>';
    $html .= '</div>';
    $html .= '</div>';
    $html .= '<div class="columns">';
        $html .= '<div class="column">';
            $html .='<button class="button is-large" id="eConfirm" style="width:100%">';
                $html .='<span class="icon is-medium">';
                    $html .='<img src="' .  $host . $lib . '/images/icon_64x64.png" alt="" />';
                $html .='</span>';
                $html .='<span>';
                    $html .='Bekräfta';
                $html . '</span>';
            $html .='</button>';
        $html .= '</div>';
    $html .= '</div>';
    return $html;
}

function webformFooter($line1, $line2) {
    $html = '';
    $html .='<div class="columns">';
        $html .='<div class="column" style="margin: 14px 0 8px 0">';
            $html .='<p id="webform-footer-line1" class="has-text-centered" style="font-size: 13px;font-style: italic; margin-bottom:2px">' . $line1 . '</p>';
            $html .='<p class="has-text-centered" style="font-size: 13px;font-style: italic">' . $line2 . '</p>';
        $html .='</div>';
    $html .='</div>';
    return $html;
}
   
?>