<?php
?>

<section class="hero is-primary page-section section-event">
    <div class="hero-body" style ="padding-bottom: 0; padding-top: 0;margin-bottom: 0;margin-top: 0;">
        <div class="container">
            <h1 style="padding-top: 10px;">
          Fakturautskick V4
            </h1>
        </div>
    </div>
</section>


<section class="section page-section section-event">

    <div class="container">
        <div class="columns" style="margin-top:4px; margin-bottom: 6px; "> <!-- max-width: 950px; -->
            <div class="column"  style="padding-bottom:3px; padding-top:6px">
                <div class="buttons is-right">
                    <a id="eNewEvent" class="button is-link">Nytt fakturasutskick</a>
                </div>
            </div>
        </div>
        <div class="columns" style="margin-top:0; margin-bottom: 6px; "> 
            <div class="column" style="text-align:right; padding-bottom:0; padding-top: 0; margin:0">
                <label class="checkbox modal-label"> <input class="is-primary is-small modal-checkbox" id="eShowCompleted" type="checkbox">&nbsp;&nbsp;Visa avslutade</label>
            </div>    
        </div>
    </div>

    <div class="container">
        <div class="columns" style="margin-top:0px; padding:0 0 0 0;">
            <div id="invoice-event-list" class="column" style="padding-top:0; padding-bottom:30px">
            </div>
        </div>
    </div>
</section>

<section class="hero is-primary page-section section-event-items" style="display:none">
    <div class="hero-body" style ="padding-bottom: 0; margin-bottom: 0;margin-top: 0; background-color: #5a7d22">
        <div class="container">
            <h1 style="padding-top: 10px;">
            Fakturor i utskick
            </h1>
        </div>
    </div>
</section>

<section class="section page-section section-event-items" style="display:none">
    <div class="container">
        <div class="columns" style="margin-top:4px; margin-bottom: 6px;">
            <div class="column"  style="padding-bottom:3px; padding-top:6px">
                <div class="buttons is-left">
                    <h1 id="title-event-name" style="font-size:24px; font-weight:bold;"></h1>
                </div>
            </div>
            <div class="column"  style="padding-bottom:3px; padding-top:6px">
                <div class="buttons is-right">
                    <a id="eEventSettings" class="button is-light">Inställningar utskick</a>
                    <a id="eNewInvoice" class="button is-link">Lägg till faktura</a>
                    <a id="eBackinvoiceEventList" class="button is-dark"><span class="icon is-medium"><i class="fas fa-times"></i></span></a>
                </div>
            </div>
        </div>
    </div>
    
    <div class="container" id="print-trans">
        <div class="columns" style="margin-top:0px; padding:0 0 0 0;">
            <div id="event-items-list" class="column" style="padding-top:0; padding-bottom:30px">
            </div>
        </div>

    </div>

</section>

<?php
    // echo htmlInvoveMailingsNewBox();

    echo htmlSettingsBox();

    echo htmlInvoiceItemBox();

    // echo htmlInvoiceItemRemoveBox();



// --
// -- Helper for HTML
// --
function htmlInvoveMailingsNewBox() {
    $html = '';

    $html .= '<div id="event-new-modal"  class="modal ">';
    $html .= '<div class="modal-background"></div>';
    $html .= '<div class="modal-card" style="max-height:600px; height:600px">';
   // <!-- height:600px -->
   $html .= '<header class="modal-card-head" style="padding-top: 12px; padding-bottom:0; background-color: #8dbf3b;">';
   $html .= '<p class="modal-card-title modal-ie-new" style="color:#ffffff">Skapa nytt Fakturautskick</p>';
   $html .= '</header>';

   $html .= '<section class="modal-card-body" style="padding-top: 6px; padding-bottom:4px;">';
   $html .= '<div class="columns modal-columns">';
   $html .= '<div class="column modal-column" style="padding-top: 14px;">';
   $html .= '<label class="modal-label" style="font-size:14px; font-weight:bold;">&nbsp;Namn på Fakturautskick</label>';
   $html .= '<input type="text" id="event-name" class="input is-primary" style="margin-top:5px; margin-bottom: 12px;">';
   $html .= ' </div>';
   $html .= '</div>';
        
   $html .= '<div class="columns columns-modal">';
   $html .= '<div class="column modal-column" style="padding-top: 4px; padding-bottom:6px">';
   $html .= '<label class="checkbox modal-label" style="font-size:14px; font-weight:bold;">'; 
   $html .= '<input id="event-import" type="checkbox">&nbsp;&nbsp;Importera från tidigare Fakturautskick</label>';
   $html .= '</div>';
   $html .= '</div>';

   $html .= '<div class="columns import-group" style="display:none">';
   $html .= '<div class="column modal-column" style="padding-top: 8px; padding-bottom:0">';
   $html .= '<label class="modal-label" style="font-size:14px; font-weight:bold;">Välj nedan från tidigare Fakturautskick ann importera från</label>';
   $html .= '</div>';
   $html .= '</div>';

   $html .= '<div class="columns import-group" style="display:none">';
   $html .= ' <div class="column modal-column" style="padding-top: 6px; padding-bottom:0">';
   $html .= ' <div class="select" style="width:100%">';
   $html .= ' <select id="ddEventList" style="width:100%">';
   $html .= ' <option></option>';
   $html .= '</select>';
   $html .= '</div>';
   $html .= '</div>';
   $html .= '</div>';

   $html .= '<div class="columns modal-columns import-group" style="display:none">';
   $html .= '<div class="column modal-column">';
   $html .= '<label class="modal-label" style="font-size:14px; font-weight:bold;">';
   $html .= '<input checked class="is-primary is-small" id="event-referense-import" type="checkbox">&nbsp;Importera referens</label>';
   $html .= '</div>';
   $html .= ' </div>';

   $html .= '<div class="columns modal-columns import-group" style="display:none">';
   $html .= '<div class="column modal-column">';
   $html .= '<label class="modal-label" style="font-size:14px; font-weight:bold;">';
   $html .= '<input checked class="is-primary is-small" id="event-spec-import" type="checkbox">&nbsp;&nbsp;Importera specifikation</label>';
   $html .= '<textarea id="event-spec" class="textarea is-primary is-small modal-textarea" rows="2" style="display:none"></textarea>';
   $html .= '</div>';
   $html .= '</div>';

   $html .= '<div class="columns modal-columns import-group" style="display:none">';
   $html .= '<div class="column modal-column">';
   $html .= '<label class="checkbox modal-label" style="font-size:16px;">';
   $html .= '<input checked class="is-primary is-small" id="event-amount-import" type="checkbox">&nbsp;&nbsp;Importera belopp</label>';
   $html .= '</div>';
   $html .= '<div class="column modal-column">';
   $html .= '<label id="event-amount-label" style="font-size:14px; font-weight:bold;">Nytt belopp ?</label>';
   $html .= '</div>';
   $html .= '<div class="column modal-column">';  
   $html .= '<input type="text" id="event-amount" class="input is-primary modal-input" style="max-width: 140px; width: 100%;display:none" autocomplete="off" style="display:none">';
   $html .= '</div>';
            
   $html .= '</div>';

   $html .= '<div class="columns modal-columns import-group" style="display:none">';
   $html .= '<div class="column modal-column">';
   $html .= '<label class="checkbox modal-label" style="font-size:16px;">';
   $html .= '<input class="is-primary is-small" id="event-send-date-pre" type="checkbox">&nbsp;&nbsp;Planerad utskicksdag</label>';
   $html .= '</div>';
   $html .= '<div class="column modal-column" > </div>';
   $html .= '<div class="column modal-column">';  
   $html .= '<input style="width: 180px;font-size:16px;display:none" id="event-send-date" class="input is-success" type="date">';
   $html .= '</div>';
   $html .= '</div>';

   $html .= '<div class="columns modal-columns import-group" style="display:none">';
   $html .= '<div class="column modal-column">';
   $html .= '<label class="modal-label" style="font-size:14px; font-weight:bold;">';
   $html .= '<input checked class="is-primary is-small" id="event-allow-edit-import" type="checkbox">&nbsp;&nbsp;Tillåt mottagare ändra uppgifter</label>';
   $html .= '</div>';
   $html .= '</div>';

   $html .= '<div class="columns modal-columns import-group" style="display:none">';
   $html .= '<div class="column modal-column">';
   $html .= '<label class="checkbox modal-label" style="font-size:14px; font-weight:bold;">'; 
   $html .= '<input class="is-primary is-small modal-checkbox" id="event-auto-reminder" type="checkbox">&nbsp;Påminnelsefrekvens</label>';
   $html .= '</div>';
   $html .= '<div class="event-reminder-container column modal-column" style="font-size:14px; font-weight:bold;padding-left:4; padding-right:0;display:none">';
   $html .= 'Dagar:&nbsp;&nbsp;';
   
        $optionDays = '<option value="2"> 2</option>';
        $optionDays .= '<option value="3"> 3</option>';
        $optionDays .= '<option value="4"> 4</option>';
        $optionDays .= '<option value="5"> 5</option>';
        $optionDays .= '<option value="6"> 6</option>';
        $optionDays .= '<option value="7" selected> 7</option>';
        $optionDays .= '<option value="8"> 8</option>';
        $optionDays .= '<option value="9"> 9</option>';
        $optionDays .= '<option value="10"> 10</option>';
        $optionDays .= '<option value="11"> 11</option>';
        $optionDays .= '<option value="12"> 12</option>';
        $optionDays .= '<option value="13"> 13</option>';
        $optionDays .= '<option value="14"> 14</option>';
        $optionDays .= '<option value="15"> 15</option>';
        $optionDays .= '<option value="16"> 16</option>';
        $optionDays .= '<option value="17"> 17</option>';
        $optionDays .= '<option value="18"> 18</option>';
        $optionDays .= '<option value="19"> 19</option>';
        $optionDays .= '<option value="20"> 20</option>';
        $optionDays .= '<option value="21"> 21</option>';
        $optionDays .= '<option value="22"> 22</option>';
        $optionDays .= '<option value="23"> 23</option>';
        $optionDays .= '<option value="24"> 24</option>';
        $optionDays .= '<option value="25"> 25</option>';
        $optionDays .= '<option value="26"> 26</option>';
        $optionDays .= '<option value="27"> 27</option>';
        $optionDays .= '<option value="28"> 28</option>';
        $optionDays .= '<option value="29"> 29</option>';
        $optionDays .= '<option value="30"> 30</option>';
                    
   $html .= '<div class="select"><select id="event-reminder-days">';
   $html .= $optionDays . '</select></div>';
   $html .= '</div>';

   $html .= '<div class="event-reminder-container column modal-column" style="font-size:14px; font-weight:bold;padding-left:14px; padding-right:0;display:none">';
   $html .= '&nbsp;Gånger:&nbsp;&nbsp;';
                
    $optionTimes = '<option value="1"> 1</option>';
    $optionTimes .= '<option value="2"> 2</option>';
    $optionTimes .= '<option value="3" selected> 3</option>';
    $optionTimes .= '<option value="4"> 4</option>';
    $optionTimes .= '<option value="5"> 5</option>';
    
    $html .= '<div class="select"><select id="event-reminder-times"><?php echo $optionTimes;?></select></div>';
    $html .= '</div>';
    $html .= '</div>';

    $html .= '</section>  ';

    $html .= '<footer class="modal-card-foot" style="padding-top: 10px; padding-bottom:10px;">';
    $html .= '<div class="buttons is-right" style="width:100%">';
    $html .= '<span id="eCloseEventNewModal" style="width:84px" class="button" >Avbryt</span>';
    $html .= '<span id="eCreateEvent" style="width:84px" class="button is-primary" >Skapa</span>';
    $html .= '</footer>';
    $html .= '</div>';
    $html .= '</div>';

    return $html;
}

function  htmlSettingsBox() {
    $html = '';

    $html .= '<div id="invoice-event-settings-modal"  class="modal ">'; // div 1
        $html .= '<div class="modal-background"></div>'; // div 2
        $html .= '<div class="modal-card" style="max-height:660px; height:660px">'; 
            // height:600px -->
            $html .= '<header class="modal-card-head" style="padding-top: 12px; padding-bottom:0; background-color: #8dbf3b;">';
                $html .= '<p class="modal-card-title modal-ie-new" style="color:#ffffff">Inställningar Fakturautskick</p> ';
            $html .= '</header>';

            $html .= '<section class="modal-card-body">';
                $html .= '<div class="columns modal-columns">';
                    $html .= '<div class="column modal-column">';
                        $html .= '<label class="modal-label" style="font-size:14px; font-weight:bold;">&nbsp;Namn på Fakturautskick <span class="required">*<span></label>';
                        $html .= '<input type="text" id="setting-event-name" class="input is-primary modal-input">';
                    $html .= '</div>';
                $html .= '</div>';

                $html .= '<div class="columns modal-columns">';
                    $html .= '<div class="column modal-column">';
                        $html .= '<label class="modal-label" style="font-size:14px; font-weight:bold;">&nbsp;Meddelande i e-post <span class="required">*<span></label>';
                        $html .= '<textarea id="settings-body"  placeholder="Skriv in ditt meddelande här ..." class="textarea is-primary is-small modal-textarea" rows="6"></textarea>';
                    $html .= '</div>';
                $html .= '</div>';
                
                $html .= '<div class="columns modal-columns" style="padding-bottom:12px">';
                    $html .= '<div class="column modal-column">';
                        $html .= '<label class="modal-label" style="font-size:14px; font-weight:bold;">&nbsp;Utskicksdag <span class="required">*<span></label>';
                    $html .= '</div>';
                    $html .= '<div class="column modal-column">';  
                        $html .= '<input style="width: 180px;" id="settings-send-date" class="input is-success modal-input" type="date">';
                    $html .= '</div>';
                    $html .= '<div class="column modal-column"></div>';
                $html .= '</div>';
                
                $html .= '<div class="columns modal-columns">';
                    $html .= '<div class="column modal-column">';
                        $html .= '<label class="checkbox modal-label" style="font-size:14px; font-weight:bold;"> <input class="is-primary is-small modal-checkbox" id="settings-auto-reminder" type="checkbox">&nbsp;Påminnelsefrekvens</label>';
                    $html .= '</div>';

                    $html .= '<div class="settings-reminder-container column modal-column" style="font-size:14px; font-weight:bold;padding-left:4; padding-right:0">';
                        $html .= 'Dagar:&nbsp;&nbsp;';
            
                            $optionDays = '<option value="2"> 2</option>';
                            $optionDays .= '<option value="3"> 3</option>';
                            $optionDays .= '<option value="4"> 4</option>';
                            $optionDays .= '<option value="5"> 5</option>';
                            $optionDays .= '<option value="6"> 6</option>';
                            $optionDays .= '<option value="7" selected> 7</option>';
                            $optionDays .= '<option value="8"> 8</option>';
                            $optionDays .= '<option value="9"> 9</option>';
                            $optionDays .= '<option value="10"> 10</option>';
                            $optionDays .= '<option value="11"> 11</option>';
                            $optionDays .= '<option value="12"> 12</option>';
                            $optionDays .= '<option value="13"> 13</option>';
                            $optionDays .= '<option value="14"> 14</option>';
                            $optionDays .= '<option value="15"> 15</option>';
                            $optionDays .= '<option value="16"> 16</option>';
                            $optionDays .= '<option value="17"> 17</option>';
                            $optionDays .= '<option value="18"> 18</option>';
                            $optionDays .= '<option value="19"> 19</option>';
                            $optionDays .= '<option value="20"> 20</option>';
                            $optionDays .= '<option value="21"> 21</option>';
                            $optionDays .= '<option value="22"> 22</option>';
                            $optionDays .= '<option value="23"> 23</option>';
                            $optionDays .= '<option value="24"> 24</option>';
                            $optionDays .= '<option value="25"> 25</option>';
                            $optionDays .= '<option value="26"> 26</option>';
                            $optionDays .= '<option value="27"> 27</option>';
                            $optionDays .= '<option value="28"> 28</option>';
                            $optionDays .= '<option value="29"> 29</option>';
                            $optionDays .= '<option value="30"> 30</option>';

                            $html .= '<div class="select">';
                                $html .= '<select id="settings-reminder-days">';
                                    $html .= $optionDays;
                                $html .= '</select>';
                            $html .= '</div>';
                    $html .= '</div>';

                    $html .= '<div class="settings-reminder-container column modal-column" style="font-size:14px; font-weight:bold;padding-left:14px; padding-right:0">';
                        $html .= '&nbsp;Gånger:&nbsp;&nbsp;';
                        $optionTimes = '<option value="1"> 1</option>';
                        $optionTimes .= '<option value="2"> 2</option>';
                        $optionTimes .= '<option value="3" selected> 3</option>';
                        $optionTimes .= '<option value="4"> 4</option>';
                        $optionTimes .= '<option value="5"> 5</option>';
        
                        $html .= '<div class="select">';
                            $html .= '<select id="settings-reminder-times">';
                                $html .= $optionTimes;
                            $html .= '</select>';
                        $html .= '</div>';
                    $html .= '</div>';
                $html .= '</div>';
      
                $html .= '<div class="columns modal-columns settings-reminder-container">';
                    $html .= '<div class="column modal-column">';
                            $html .= '<label class="checkbox modal-label" style="font-size:14px; font-weight:bold;"> <input class="is-primary is-small modal-checkbox" id="settings-reminder-text-on" type="checkbox">&nbsp;Meddelande i påminnelse</label>';
                            $html .= '<textarea id="settings-reminder-body"  placeholder="Skriv in ditt meddelande här ..." class="textarea is-primary is-small modal-textarea" rows="5"></textarea>';
                    $html .= '</div>';
                $html .= '</div>';
                
                $html .= '<div class="columns modal-columns-label">';
                    $html .= '<div class="column modal-column">';
                        $html .= '<label class="modal-label" style="font-size:14px; font-weight:bold;">&nbsp;Status</label>';
                    $html .= '</div>';
                    $html .= '<div class="column modal-column"></div>';
                    $html .= '<div class="column modal-column"></div>';
                $html .= '</div>';
                
                $html .= '<div class="columns modal-columns">';
                    $html .= '<div class="column modal-column">';
                        $html .= '<div class="select modal-select">';
                            $html .= '<select id="settings-ddStatus" class="w-max">';
                                $html .= '<option value="p"> Utkast </option>';
                                $html .= '<option value="a"> Aktiv </option>';
                                $html .= '<option value="c"> Avslutad </option>';
                            $html .= '</select>';
                        $html .= '</div>';
                    $html .= '</div>';
                    $html .= '<div class="column modal-column"></div>';
                    $html .= '<div class="column modal-column"></div>';
                $html .= '</div>';  
                

            $html .= '</section>';
            
            $html .= '<footer class="modal-card-foot" style="padding-top: 10px; padding-bottom:10px;">';
                $html .= '<div class="buttons is-right" style="width:100%">';
                    $html .= '<span id="eCloseEventSettingsModal" style="width:84px" class="button" >Avbryt</span>';
                    $html .= '<span id="eEventSettingsSave" style="width:84px" class="button is-primary" >Spara</span>';
                $html .= '</div>';
            $html .= '</footer>';
  
        $html .= '</div>'; // div 2
    $html .= '</div>'; // div 1

    return $html;
}

function htmlInvoiceItemBox() {
    $html = '';
    $html .= '<div id="invoice-item-modal"  class="modal">';
    $html .= '<div class="modal-background"></div>';
        $html .= '<div class="modal-card" style="max-height:630px; height:630px">';
            $html .= '<header class="modal-card-head" style="padding-top: 12px; padding-bottom:0; background-color: #5a7d22;">';
                $html .= '<p class="modal-card-title" id="title-invoice-item-modal" style="color:#ffffff">Faktura i utskick</p>';
            $html .= '</header>';

            $html .= '<section class="modal-card-body" style="padding-top: 6px; padding-bottom:0;">';
                $html .= '<div id="customer-list" class="columns get-tab" style="display:none; padding-top: 8px">';
            $html .= '</div>';

            $html .= '<div class="columns modal-columns item-tab">';
                $html .= '<div class="column modal-column">';
                    $html .= '<label class="modal-label">&nbsp;Namn på mottagare</label>';
                    $html .= '<p class="control has-icons-right" style="margin-bottom:0">';
                        $html .= '<input type="text" id="invoice-people-name" class="input is-primary" style="padding-right:3px; width:530px;" autocomplete="off">';
                        $html .= '<span class="icon is-small is-right" style="width: auto; pointer-events: auto;">';
                            $html .= '<button id="eInvoiceGetTab" class="button is-dark">&nbsp;Hämta </button>';
                        $html .= '</span>';
                    $html .= '</p>';
                $html .= '</div>';
            $html .= '</div>';

            $html .= '<div class="columns modal-columns item-tab">';
                $html .= '<div class="column modal-column">';
                    $html .= '<label class="modal-label" >&nbsp;E-post <span class="required">*<span></label>';
                    $html .= '<input type="text" id="invoice-email" class="input is-primary" autocomplete="off">';
                $html .= '</div>';
            $html .= '</div>';

            $html .= '<div class="columns modal-columns item-tab">';
                $html .= '<div class="column modal-column">';
                    $html .= '<label class="modal-label" >&nbsp;Referens <span class="required">*<span></label>';
                    $html .= '<input type="text" id="invoice-referens" class="input is-primary" autocomplete="off">';
                $html .= '</div>';
            $html .= '</div>';

        //$html .= '<div class="columns modal-columns item-tab">';
        //$html .= '<div class="column modal-column">';
        //$html .= '<label class="modal-label" >&nbsp;Specifikation </label>';
        //$html .= '<textarea id="invoice-spec" class="textarea is-primary is-small modal-textarea" rows="3" ></textarea>';
        //$html .= '</div>';
        //$html .= '</div>';
        
    $html .= '<div class="columns modal-columns item-tab">';
    $html .= '<div class="column modal-column">';
    $html .= '<label class="modal-label" >&nbsp;Belopp</label>';
    $html .= '</div>';
    $html .= '<div class="column modal-column col-planed-date" style="padding-left: 6px">';
    $html .= '<label class="modal-label">Skickas datum <span class="required">*<span></label>';
    $html .= '</div>';
    $html .= '<div class="column modal-column col-sent-date">';
    $html .= '<label class="modal-label" id="invoice-label-sent-datetime">&nbsp;Skickad</label>';
    $html .= '</div>';
    $html .= '<div class="column modal-column col-reminder-last-datetime">';
    $html .= '<label class="modal-label">&nbsp;Påmind</label>';
    $html .= '</div>';
    $html .= '<div class="column modal-column col-empty"></div>';
    $html .= '<div class="column modal-column col-empty2"></div>';

    $html .= '<div class="column modal-column col-confirmed">';
    $html .= '<label class="modal-label" id="invoice-label-confirmed-datetime">&nbsp;Hämtad datum</label>';
    $html .= '</div>';
    $html .= '</div>';

    $html .= '<div class="columns modal-columns item-tab">';
    $html .= '<div class="column modal-column">';
    $html .= '<input type="text" id="invoice-amount" class="input is-primary modal-input" style="max-width: 160px; width: 100%" autocomplete="off">';
    $html .= '</div>';
    $html .= '<div class="column modal-column col-planed-date">';
    $html .= '<input type="date" id="invoice-planed-date" class="input is-primary" style="max-width: 170px; width: 100%" autocomplete="off">';
    $html .= '</div>';
    $html .= '<div class="column modal-column col-sent-date">';
    $html .= '<input type="text" id="invoice-sent-datetime" class="input is-primary" style="max-width: 120px; width: 100%">';
    $html .= '</div>';
    $html .= '<div class="column modal-column col-reminder-last-datetime">';
    $html .= '<input type="text" id="invoice-reminder-last-datetime" class="input is-primary margin-top:2px; " style="max-width: 120px; width: 100%">';
    $html .= '</div>';
    $html .= '<div class="column modal-column col-empty"></div>';
    $html .= '<div class="column modal-column col-empty2" ></div>';
    $html .= '<div class="column modal-column col-confirmed">';
    $html .= '<input type="text" id="invoice-confirmed-datetime" class="input is-primary modal-input" style="max-width: 120px; width: 100%">';
    $html .= '</div>';
    $html .= '</div>';
        
    $html .= '<div class="columns modal-columns-line col-remider item-tab">';
    $html .= '<div class="column modal-column-line"></div>';
    $html .= '</div>';

    $html .= '<div class="columns modal-columns col-remider item-tab">';
    $html .= '<div class="column modal-column">';
    $html .= '<label class="checkbox modal-label" > <input class="is-primary is-small modal-checkbox" id="invoice-auto-reminder" type="checkbox">&nbsp;Påminnelse</label>';
    $html .= '</div>';
    $html .= '<div class="column modal-column reminder-container">';
    $html .= '<label class="checkbox modal-label"> &nbsp;Dagar</label>';
    $html .= '</div>';
    $html .= '<div class="column modal-column reminder-container">';
    $html .= '<label class="checkbox modal-label">&nbsp;Gånger kvar</label>';
    $html .= '</div>';
    $html .= '<div class="column modal-column reminder-container">';
    $html .= '<label class="modal-label" id="invoice-label-reminder-next-date">&nbsp;Nästkommande</label>';
    $html .= '</div>';
    $html .= '</div>';
       
    $html .= '<div class="columns modal-columns reminder-container item-tab">';
    $html .= '<div class="column modal-column">';
    $html .= '</div>';
    $html .= '<div class="column modal-column">';
              
        $optionDays = '<option value="2"> 2</option>';
        $optionDays .= '<option value="3"> 3</option>';
        $optionDays .= '<option value="4"> 4</option>';
        $optionDays .= '<option value="5"> 5</option>';
        $optionDays .= '<option value="6"> 6</option>';
        $optionDays .= '<option value="7" selected> 7</option>';
        $optionDays .= '<option value="8"> 8</option>';
        $optionDays .= '<option value="9"> 9</option>';
        $optionDays .= '<option value="10"> 10</option>';
        $optionDays .= '<option value="11"> 11</option>';
        $optionDays .= '<option value="12"> 12</option>';
        $optionDays .= '<option value="13"> 13</option>';
        $optionDays .= '<option value="14"> 14</option>';
        $optionDays .= '<option value="15"> 15</option>';
        $optionDays .= '<option value="16"> 16</option>';
        $optionDays .= '<option value="17"> 17</option>';
        $optionDays .= '<option value="18"> 18</option>';
        $optionDays .= '<option value="19"> 19</option>';
        $optionDays .= '<option value="20"> 20</option>';
        $optionDays .= '<option value="21"> 21</option>';
        $optionDays .= '<option value="22"> 22</option>';
        $optionDays .= '<option value="23"> 23</option>';
        $optionDays .= '<option value="24"> 24</option>';
        $optionDays .= '<option value="25"> 25</option>';
        $optionDays .= '<option value="26"> 26</option>';
        $optionDays .= '<option value="27"> 27</option>';
        $optionDays .= '<option value="28"> 28</option>';
        $optionDays .= '<option value="29"> 29</option>';
        $optionDays .= '<option value="30"> 30</option>';
                
    $html .= '<div class="select"><select id="invoice-reminder-days"><?php echo $optionDays;?></select></div>';
    $html .= '</div>';
    $html .= '<div class="column modal-column">';
            
        $optionTimes = '<option value="0"> 0</option>';
        $optionTimes .= '<option value="1"> 1</option>';
        $optionTimes .= '<option value="2"> 2</option>';
        $optionTimes .= '<option value="3" selected> 3</option>';
        $optionTimes .= '<option value="4"> 4</option>';
        $optionTimes .= '<option value="5"> 5</option>';
        
    $html .= '<div class="select"><select id="invoice-reminder-times"><?php echo $optionTimes;?></select></div>';
    $html .= '</div>';
    $html .= '<div class="column modal-column">';
    $html .= '<input type="text" id="invoice-reminder-next-date" class="input is-primary modal-input" style="max-width: 120px; width: 100%">';
    $html .= '</div>';
    $html .= '</div>';

    $html .= '<div class="columns modal-columns check-start modal-column item-tab">';
    $html .= '<div class="column modal-column">';
    $html .= '<label class="checkbox modal-label"><input id="invoice-allowed-edit" type="checkbox">&nbsp;&nbsp;Tillåt mottagare ändra uppgifter</label>';
    $html .= '</div>';
    $html .= '</div>';

    $html .= '<div class="columns modal-columns check-start item-tab">';
    $html .= '<div class="column modal-column">';
    $html .= '<label class="checkbox modal-label" ><input id="invoice-draft" type="checkbox">&nbsp;&nbsp;Spara som utkast</label>';
    $html .= '</div>';
    $html .= '</div>';

    $html .= '<div class="columns modal-columns col-close-item item-tab">';
    $html .= '<div class="column modal-column">';
    $html .= '<label class="checkbox modal-label" ><input id="invoice-item-close" type="checkbox">&nbsp;&nbsp;Stäng</label>';
    $html .= '</div>';
    $html .= '</div>';

    $html .= '</section>';  
   
    $html .= '<footer class="modal-card-foot" style="padding-top: 10px; padding-bottom:10px;">';
    $html .= '<div class="buttons is-right" style="width:100%">';
    $html .= '<span id="eCloseInvoiceItemModal" class="item-tab button" style="width:84px;">Avbryt</span>';
    $html .= '<span id="eSaveInvoiceItemModal" class="item-tab button is-link" style="width:84px;">Spara</span>';  
    $html .= '<span id="eUpdateInvoiceItemModal" class=" item-tab button is-link" style="width:84px;">Spara</span>';  
    $html .= '<span id="eInvoiceItemTab" class="get-tab button" style="width:84px; display:none">Tillbaka</span>';
    $html .= '</div>';
    $html .= '</footer>';

    $html .= '</div>';
    $html .= '</div>';

    return $html;
}

function htmlInvoiceItemRemoveBox() {
    $html = '';
    $html .= '<div class="modal" id="remove-item-modal">';
    $html .= '<div class="modal-background"></div>';
    $html .= '<div class="modal-card pl0 pr0  modal-width">';
    $html .= '<header class="modal-card-head">';
    $html .= '<p class="modal-card-title has-text-centered">Ta bort</p>';
    $html .= '</header>';
    $html .= '<section class="modal-card-body">';
    $html .= '<p id="remove-item-modal-text" class="has-text-centered"></p>';
    $html .= '</section>';
    $html .= '<footer class="modal-card-foot">';
    $html .= '<button id="eCloseRemoveItemModal" class="button w120 image-center">Nej</button>';
    $html .= '<button id="eRemoveItemModal" class="button is-primary w120 image-center">Ja</button>';
    $html .= '</footer>';
    $html .= '</div>';
    $html .= '</div>';

    return $html;
}

    ?>