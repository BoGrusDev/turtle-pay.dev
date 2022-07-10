<?php
/*
 
html.inc

Create the HTML.

Gravel Machine
also know as Gruvmaskinen

*/ 

function htmlSection($isMobile = 'no') {
    $html = '';
    if ($isMobile == 'yes') {
        $html .= '<section class="section" style="padding-bottom:0px">';
        $html .= '<div class="container">';
    }
    else {
        $html .= '<section class="section">';
        $html .= '<div class="container">';
    }

    return $html;    
}

function htmlNavbar($hasLogoImage, $logoUrl, $text, $bcolor, $tcolor) {
    
    $html = '';
    if ($hasLogoImage == 'y') {
        // --
        // -- Header-image
        // --
        $html .= '<div class="columns has-text-centered" id="header-image-panel" >';
        $html .= '<div class="column">';
        $html .= '<img id="header-image-src" src="" alt="" />';
        $html .= '</div>';
        $html .= '</div>';
    }
    else {
        // --
        // -- Header-text-panel
        // --
        $html .= '<div class="columns" id="header-text-panel">';
        $html .= '<div class="column">';
        $html .= '<h1 id="header-text-title"></h1>';
        $html .= '</div>';
        $html .= '</div>';
    }
    return $html;
}

function htmlColumns($viewClass='', $hidden = false) {
    $html = '';
    if ($hidden) {
        $html .='<div class="columns ' . $viewClass . '" style="display:none">';
    }
    else {
        $html .='<div class="columns ' . $viewClass . '">';
    }

    return $html;
}

function htmlColumn() {
    $html = '';
    $html .= '<div class="column">';

    return $html;
}

function htmlSubHeader ($text, $id = false) {
    $html = '';
    if ($id) {
        $html .= '<h2 id="' . $id . '" class="title is-6">' . $text . ' </h2>';
    } else {
        $html .= '<h2 class="title is-6">' . $text . ' </h2>';
    }
    return $html;
}

function htmlDivEnd() {
    $html = '';
    $html .=  '</div>';

    return $html;
}

function htmlRowText($text, $viewClass='') {
    $html = '';
    $html .='<div class="columns ' . $viewClass . '">';
        $html .='<div class="column">';
            $html .='<p class="p-default">';
                $html .= $text; 
            $html .='</p>';
        $html .='</div>';
    $html .='</div>';

    return $html;
}

function htmlRowInput($text, $id, $value, $inputClass='', $maxlength='100', $placeholder = '') {
    $html = '';
        $html .='<div class="field">';
            $html .='<label class="label">' . $text . '</label>';
            $html .='<div class="control">';
                $html .= '<input value="' . $value . '" class="input ' . $inputClass . '" id="' . $id . '" type="text" placeholder="' . $placeholder . '"  maxlength="' . $maxlength . '" autocomplete="off"/>';
        $html .='</div>';
    $html .='</div>';

    return $html;
}

function htmlRowTextarea($text, $id, $inputClass='', $rows='5', $placeholder = '') {
    $html = '';
    $html .='<div class="field">';
        $html .='<label class="label">' . $text . '</label>';
        //$html .='<div class="control">';
            $html .='<textarea id="' . $id . '"  placeholder="' . $placeholder . '" class="textarea ' . $inputClass . '" rows="' . $rows . '"></textarea>';
        //$html .='</div>';
    $html .='</div>';

    return $html;
}

function htmlSectionEnd() {
    $html = '';
    $html .='</section>';

    return $html;
}

function htmlFooter($line1, $line2) {
    $html = '';
    $html .='<footer class="footer" >';
        $html .='<div class="section">';
            $html .='<div class="container">';
                $html .='<div class="columns">';
                    $html .='<div class="column" style="padding: 14px 0 8px 0">';
                        $html .='<p class="p-small center">' . $line1 . '</p>';
                        $html .='<p class="p-small center">' . $line2 . '</p>';
                    $html .='</div>';
                $html .='</div>';
            $html .='</div>';
        $html .='</div>';
    $html .='</footer>';

    return $html;
}

function htmlFooterMobile($line1, $line2) {
    $html = '';
    $html .='<footer class="footer-mobile" >';
        $html .='<div class="section">';
            $html .='<div class="container">';
                $html .='<div class="columns">';
                    $html .='<div class="column" style="padding: 0 0 8px 0">';
                        $html .='<p class="p-small center">' . $line1 . '</p>';
                        $html .='<p class="p-small center">' . $line2 . '</p>';
                    $html .='</div>';
                $html .='</div>';
            $html .='</div>';
        $html .='</div>';
    $html .='</footer>';

    return $html;
}

function htmlBankidSection($paymentText, $isMobile, $bankIdText, $buttonLabel, $host, $lib, $viewClass ) {
    $html = '';

    $html .='<div class="columns ' . $viewClass . '">';
        $html .='<div class="column">';
            $html .='<p class="p-default">';
                $html .= $paymentText; 
            $html .='</p>';
        $html .='</div>';
    $html .='</div>';

    $html .= '<div class="columns view-1">';
    $html .= '<div class="column" style="padding-top: 8px">';
    $html .= '<div class="field">';   
    $html .= '<label class="checkbox">';
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

    $html .='<button class="button is-large" id="eConfirm" style="width:100%">';
    $html .='<span class="icon is-medium">';
    //$html .='<img src="' .  $host . $lib . '/images/icon_64x64.png" alt="" class="bankid-logo" height="40" width="40"/>';
    $html .='<img src="' .  $host . $lib . '/images/icon_64x64.png" alt="" />';
    $html .='</span>';
    $html .='<span>' . $buttonLabel . '</span>';
    $html .='</button>';
    
    return $html;
}

function htmlBankidCancelButton($butonLabel) {
    $html = '';
    $html .='<button class="button is-large is-loading is-dark w100p" id="eCancelBankID" style="display:none;">' . $buttonLabel . '</button>';
    
    return $html;
}

function htmlRowMultiInput($form) {

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

function htmlOptionsCreate($text, $index, $option, $eventId, $initLabel = '--- Välj ---' ) {
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

function htmlBankId($isMobile, $bankIdText) {
    $html = '';
    $html .= '<div class="columns view-1">';
        $html .= '<div class="column" style="padding-top: 8px">';
            $html .= '<div class="field">';   
                $html .= '<label class="checkbox">';
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

    return $html;
}

function htmlMessageBoxCreate() {

    $html = '';
    $html .='<div class="modal" id="message-box">';
    $html .='<div class="modal-background"></div>';
    $html .='<div class="modal-card pl0 pr0">';
    $html .='<header class="modal-card-head">';
    $html .='<p class="modal-card-title has-text-centered">Meddelande</p>';
    $html .=' </header>';
    $html .='<section class="modal-card-body">';
    $html .='<p id="message-box-text" class="has-text-centered"></p>';
    $html .='</section>';
    $html .='<footer class="modal-card-foot">';
    $html .='<div class="has-text-centered w100p">';
    $html .='<button id="eMessageBoxClose" class="button is-dark w120">OK</button>';
    $html .='</div>';
    $html .='</footer>';
    $html .='</div>';
    $html .='</div>';

    return $html;
}

function htmlUcBoxCreate() {

    $html = '';
    $html .='<div class="modal" id="uc-box">';
    $html .='<div class="modal-background"></div>';
    $html .='<div class="modal-card pl0 pr0">';
    $html .='<header class="modal-card-head">';
    $html .='<p class="modal-card-title has-text-centered">Meddelande</p>';
    $html .='</header>';
    $html .='<section class="modal-card-body">';
    $html .='<p class="has-text-centered">';
    $html .='En kreditupplysning kommer att inhämtas.<br><br><i>Godkänn genom att välja fortsätt?</i>';
    $html .='</p>';
    $html .='</section>';
    $html .='<footer class="modal-card-foot">';
    $html .='<div class="has-text-centered w100p">';
    $html .='<button id="eUcBoxCancel" class="button is-light w120" style="border: 1px solid #ccc">Avbryt</button>';
    $html .='<button id="eUcBoxContinue" class="button is-dark w120">Fortsätt</button>';
    $html .='</div>';
    $html .=' </footer>';
    $html .='</div>';
    $html .='</div>';

    return $html;
}
