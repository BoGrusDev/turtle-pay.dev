<?php
/*
 
html.inc

Create the HTML.

Gravel Machine
also know as Gruvmaskinen

*/ 

function htmlSectionHeader($title, $classes, $isMobile = 'no') {
    $html = '';
    if ($isMobile == 'yes') {
        $html .= '<section class="hero ' . $classes . '">';
        $html .= '<div class="hero-body" style ="padding-bottom: 0; padding-top: 0;margin-bottom: 0;margin-top: 0;">';
        $html .= '<div class="container">';
        $html .= '<h1 style="padding-top: 10px;">' . $title . '</h1>';
        $html .= '</div>';
        $html .= '</div>';
        $html .= '</section>';
    }
    else {
        $html .= '<section class="hero ' . $classes . '">';
        $html .= '<div class="hero-body" style ="padding-bottom: 0; padding-top: 0;margin-bottom: 0;margin-top: 0;">';
        $html .= '<div class="container">';
        $html .= '<h1 style="padding-top: 10px;">' . $title . '</h1>';
        $html .= '</div>';
        $html .= '</div>';
        $html .= '</section>';
    }
    return $html;    
}

function htmlSection($classes, $isMobile = 'no') {
    $html = '';
    if ($isMobile == 'yes') {
        $html .= '<section class="section' . $classes . '" style="padding-bottom:0px">';
        $html .= '<div class="container">';
    }
    else {
        $html .= '<section class="section ' . $classes . '">';
        $html .= '<div class="container">';
    }
    return $html;    
}

function htmlSectionEnd() {
    $html = '';
    $html = '</div>';
    $html .= '</section>';

    return $html;
}
 

function htmlButtons($param) {
    $html = '';
    $html .= '<div class="columns" style="margin-top:4px; margin-bottom: 6px; ">';
    $html .= '<div class="column"  style="padding-bottom:3px; padding-top:6px">';
    $html .= '<div class="buttons is-right">';
    for ($i = 0; $i < sizeof($param); $i++) {
        if (isset($param[$i]->icon)) {
            $html .= '<a id="' . $param[$i]->eventId . '" class="button ' . $param[$i]->classes . '"><span class="icon is-medium"><i class="fas fa-times"></i></span></a>';
        }
        else {
            $html .= '<a id="' . $param[$i]->eventId . '" class="button ' . $param[$i]->classes . '">' . $param[$i]->text . '</a>';
        }
    }
    $html .= '</div>';
    $html .= '</div>';
    $html .= '</div>';
    return $html;
}

function htmlCheckbox($label, $eventId) {
    $html = '';
    $html .= '<div class="columns" style="margin-top:0; margin-bottom: 6px;">'; 
    $html .= '<div class="column" style="text-align:right; padding-bottom:0; padding-top: 0; margin:0">';
    $html .= '<label class="checkbox modal-label"> <input class="is-primary is-small modal-checkbox" id="' . $eventId . '" type="checkbox">&nbsp;&nbsp;' . $label . '</label>';
    $html .= '</div>';
    $html .= '</div>';
    return $html;
}

function htmlListArea($eventId) {
    $html = '';
    $html .= '<div class="columns no-padding" style="margin-top:0px;">';
    $html .= '<div id="' . $eventId . '" class="column" style="padding-top:0; padding-bottom:30px">';
    $html .= '</div>';
    $html .= '</div>';
    return $html;
}

function htmlPrintList($printId, $listId, $title) {
    $html = '';
    $html .= '<div class="container" id="' . $printId . '">';
    $html .= '<div class="columns" style="margin: 4px 0 6px 0; width:100%;">';
    $html .= '<div class="column no-margin no-padding left" >';
    $html .= '<div>';
    $html .= '<h1 id="' . $title . '" style="font-size:24px; font-weight:bold;"></h1>';
    $html .= '</div>';
    $html .= '</div>';
    $html .= '</div>';  
    $html .= '<div class="columns no-padding" style="margin-top:0px">';
    $html .= '<div id="' . $listId . '" class="column" style="padding-top:0; padding-bottom:30px">';
    $html .= '</div>';
    $html .= '</div>';
    $html .= '</div>';
    return $html;
}

/*
function htmlBoxEventNew($title) {

    $html = '';
    $html .= '<div id="box-event-new"  class="modal">';
    $html .= '<div class="modal-background"></div>';
    $html .= '<div class="modal-card" style="max-height:360px; height:360px">';
    $html .= '<header class="modal-card-head" style="padding-top: 12px; padding-bottom:0; background-color: #8dbf3b;">';
    $html .= '<p class="modal-card-title modal-ie-new" style="color:#ffffff">' . $title . '</p>'; 
    $html .= '</header>';
    $html .= '<section class="modal-card-body">';

    $html .= htmlBoxRow();
    $html .= htmlBoxInput('Namn på Event', 'new-event-name', true);
    $html .= htmlDivEnd();
       
    $html .= htmlBoxRow();
    $html .= '<div class="column modal-column" style="padding-top: 8px; padding-bottom:4px">';
        $html .= '<label class="modal-label" style="font-size:14px; font-weight:bold;">Välj formulär</label>';
        $html .= '<div class="select" style="width:100%">';
            $html .= '<select id="ddWebFormList" style="width:100%">';
                $html .= '<option></option>';
            $html .= '</select>';
        $html .= '</div>';
    $html .= '</div>';
    $html .= htmlDivEnd();

    $html .= htmlBoxRow();
    $html .= htmlBoxInput('Event länk', 'new-event-url', true);
    $html .= htmlColumnBlack();
    $html .= htmlDivEnd();

    $html .= htmlBoxError('box-event-new');
    $html .=  htmlSectionEnd();
             
    $html .= '<footer class="modal-card-foot" style="padding-top: 10px; padding-bottom:10px;">';
    $html .= '<div class="buttons is-right" style="width:100%">';
    $html .= '<span id="eBoxEventNewClose" style="width:84px" class="button" >Avbryt</span>';
    $html .= '<span id="eBoxEventNewCreate" style="width:84px" class="button is-primary" >Skapa</span>';  
    $html .= '</footer>';
    $html .= '</div>';
    $html .= '</div>';

    return $html;
} 
*/
/*
function htmlBoxEventSettings($title) {
    $html = '';
    $html .= '<div id="box-event-settings"  class="modal">';
    $html .= '<div class="modal-background"></div>';
    $html .= '<div class="modal-card" style="max-height:360px; height:360px">';
    $html .= '<header class="modal-card-head" style="padding-top: 12px; padding-bottom:0; background-color: #8dbf3b;">';
    $html .= '<p class="modal-card-title modal-ie-new" style="color:#ffffff">' . $title . '</p>'; 
    $html .= '</header>';
    $html .= '<section class="modal-card-body">';

    // -- Name
    $html .= '<form id="box-event-settings-form">';
    $html .= htmlBoxRow();
    $html .= htmlBoxInput('Namn på Event', 'event_name');
    $html .= htmlDivEnd();
    // $html .= htmlBoxTextarea('Beskrivning', 'description');
    // $html .= htmlBoxRow();
    // $html .= htmlBoxInput('Referens', 'referens');
    // $html .= htmlDivEnd();
    $html .= htmlBoxRow();
    //$html .= htmlBoxInput('Belopp', 'amount');
    $html .= htmlBoxInput('Event länk', 'event_url');
    $html .= htmlColumnBlack();
    $html .= htmlDivEnd();

    $param = array();
    $param[0] = new stdClass();
    $param[0]->value = 'p';
    $param[0]->text = 'Utkast';
    $param[1] = new stdClass();
    $param[1]->value = 'a';
    $param[1]->text = 'Aktiv';
    $param[2] = new stdClass();
    $param[2]->value = 'c';
    $param[2]->text = 'Avslutad';
    $html .= htmlBoxDropdown('event_status', 'Status', $param, '3');
    $html .= '</form>';
    $html .= '</section>';  
    $html .= '<footer class="modal-card-foot" style="padding-top: 10px; padding-bottom:10px;">';
    $html .= '<div class="buttons is-right" style="width:100%">';
    $html .= '<span id="eBoxEventSettingsClose" style="width:84px" class="button" >Avbryt</span>';
    $html .= '<span id="eBoxEventSettingsSave" style="width:84px" class="button is-primary" >Spara</span>';
    $html .= '</footer>';
    $html .= htmlDivEnd();
    $html .= htmlDivEnd();

    return $html;
} 
*/

function htmlBoxWebform($title) {
    $html = '';
    $html .= '<div id="box-webform"  class="modal">';
    $html .= '<div class="modal-background"></div>';
    $html .= '<div class="modal-card" style="max-height:660px; height:660px; width:780px;">';
    $html .= '<header class="modal-card-head" style="padding-top: 12px; padding-bottom:0; background-color: #efefef;">';
    $html .= '<p class="modal-card-title modal-ie-new" style="color:#444444">' . $title . '</p>'; 
    $html .= '</header>';
    $html .= '<section class="modal-card-body">';
    
    $html .= '<div id="box-tab-form" class="columns modal-columns box-tab-form">';
    //$html .= '<form id="box-tab-webform-form"></form>';
    $html .= htmlDivEnd();
    
    $html .= '<div id="box-tab-preview"  class="modal-columns box-tab-preview" style="display:none">';
    $html .= 'Preview';
    $html .= htmlDivEnd();

    $html .= '</section>';  
    $html .= '<footer class="modal-card-foot" style="padding-top: 10px; padding-bottom:10px;">';
    $html .= '<div class="buttons is-right" style="width:100%">';
    $html .= '<span id="eBoxWebformForm" style="width:84px;display:none;" class="button box-tab-preview">Tillbaka</span>';
    $html .= '<span id="eBoxWebformPreview" style="width:130px; " class="button is-link box-tab-form">Förhansgranska</span>';
    $html .= '<span id="eBoxWebformClose" style="width:84px" class="button box-tab-form" >Avbryt</span>';
    $html .= '<span id="eBoxWebformSave" style="width:84px" class="button is-primary box-tab-form" >Spara</span>';
    $html .= '</footer>';
    $html .= htmlDivEnd();
    $html .= htmlDivEnd();

    return $html;
} 

function htmlBoxRow() {
    $html = '';
    $html .= '<div class="columns modal-columns">';
    return $html;
}

function htmlColumnBlack() {
    $html = '';
    $html .= '<div class="column modal-column"></div>';

    return $html;
}

function htmlBoxInput($label, $inputName, $inputId = false) {
    $html = '';
    
    $html .= '<div class="column modal-column">';
    $html .= '<label class="modal-label">&nbsp;' . $label . '</label>';
    if ($inputId) {
        $html .= '<input type="text" id="' . $inputName  . '" class="input is-primary modal-input">';
    } 
    else {
        $html .= '<input type="text" name="' . $inputName  . '" class="input is-primary modal-input">';
    }
    $html .= '</div>';
    return $html;
}

function htmlBoxLabel($label) {
    $html = '';
    $html .= '<div class="column modal-column">';
    $html .= '<label class="modal-label">&nbsp;' . $label . '</label>';
    $html .= '</div>';
    return $html;
}

function htmlBoxTextarea($label, $nameId) {
    $html = '';
    
    $html .= '<div class="columns modal-columns">';
    $html .= '<div class="column modal-column">';
    $html .= '<label class="modal-label">&nbsp;' . $label . '</label>';
    $html .= '<textarea name="' . $nameId  . '" class="textarea is-primary is-small modal-textarea" rows="2"></textarea>';
    $html .= '</div>';
    $html .= '</div>';

    // $html .= '<div class="column modal-column">';
    // $html .= '<label class="modal-label" style="font-size:14px; font-weight:bold;">&nbsp;' . $label . '</label>';
    // $html .= '<input type="text" id="' . $inputId  . '" class="input is-primary modal-input">';
    // $html .= '</div>';
    return $html;
}

function htmlBoxDropdown($id, $label, $param, $grid) {

    $html = '';
    $html .= '<div class="columns modal-columns">';
    $html .= '<div class="column modal-column">';
    $html .= '<label class="modal-label">&nbsp;' . $label . '</label>';
    $html .= ' <div class="select modal-select">';
    $html .= '<select name="' . $id . '" class="w-max">';
    for ($i = 0; $i < sizeof($param); $i++) {
        $html .= '<option value="' . $param[$i]->value  . '">' . $param[$i]->text . '</option>';
    }
    $html .= '</select>';
    $html .= '</div>';
    $html .= '</div>';
    if ($grid > '1') {
        for ($i = 2; $i <= $grid; $i++) {
            $html .= '<div class="column modal-column"></div>';
        }
    }
    $html .= '</div>';
    return $html;
}

function htmlBoxError($id) {
    $html = '';
    $html .= '<div id="' .  $id . '-error-container" class="columns modal-columns" style="padding-top: 12px;">';
    $html .= '<div class="column modal-column">';
    $html .= '<p id="' . $id .  '-error" class="modal-error">';
    $html .= '</p>';
    $html .= '</div>';
    $html .= '</div>';
    return $html;
}

// -- Not used
function htmlNavbar($hasLogoImage, $logoUrl, $text, $bcolor, $tcolor) {
    $html = '';
    $html .='<nav class="navbar" role="navigation" aria-label="main navigation" >';
        if ($hasLogoImage == 'y') {
            $html .= '<div class="has-text-centered" style="width:100%">';
                $html .= '<img src="' . $logoUrl . '" alt="" />';
            $html .= '</div>';
        }
        else {
            $html .= '<h1 style="background-color:' . $bcolor . ';color:' . $tcolor . '">' . $text . '</h1>';
        }
    $html .= '</nav>';
    
    return $html;
}

// -- Not used
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

// -- Not used
function htmlColumn() {
    $html = '';
    $html .= '<div class="column">';

    return $html;
}

// -- Not used
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

// -- Not used
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

// -- Not used
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

// -- Not used
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

// -- Not used
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

// -- Not used
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

// -- Not used
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

// -- Not used
function htmlBankidCancelButton($butonLabel) {
    $html = '';
    $html .='<button class="button is-large is-loading is-dark w100p" id="eCancelBankID" style="display:none;">' . $buttonLabel . '</button>';
    
    return $html;
}

// -- Not used
function _htmlParticipantTab($label, $multi) {
    $html = '';
    $html .='<div class="columns view-1">';
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

// -- Not used
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

// -- Not used
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

// -- Not used
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

// -- Not used
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

// -- Not used
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
