<?php
?>

<section class="hero is-primary page-section section-event">
    <div class="hero-body" style ="padding-bottom: 0; padding-top: 0;margin-bottom: 0;margin-top: 0;">
        <div class="container">
            <h1 style="padding-top: 10px;">
          Utskick
            </h1>
        </div>
    </div>
</section>


<section class="section page-section section-event">

    <div class="container">
        <div class="columns" style="margin-top:4px; margin-bottom: 6px; "> <!-- max-width: 950px; -->
            <div class="column"  style="padding-bottom:3px; padding-top:6px">
                <div class="buttons is-right">
                    <a id="eNewEvent" class="button is-link">Nytt utskick</a>
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
            Mottagare i utskick
            </h1>
        </div>
    </div>
</section>

<section class="section page-section section-event-items" style="display:none">
    <div class="container">
        <div class="columns" style="margin-top:4px; margin-bottom: 6px;">
            <div class="column"  style="padding-bottom:3px; padding-top:6px">
                <div class="buttons is-left">
                    <div>
                        <h1 id="title-invoice-event-name" style="font-size:24px; font-weight:bold; line-height:28px"></h1>
                        <p id="title-event-name" style="font-size:14px; font-weight:bold;"></p>
                    </div>
                </div>
            </div>
            <div class="column"  style="padding-bottom:3px; padding-top:6px">
                <div class="buttons is-right">
                    <a id="eImportModalOpen" class="button is-dark">Importera e-post</a>
                    <a id="eEventSettings" class="button is-Ligth">Meddelande</a>
                    <a id="eNewInvoice" class="button is-link">Lägg till mottagare</a>
                    <a id="eBackinvoiceEventList" class="button is-dark">Stäng</a>
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

<div id="event-new-modal"  class="modal ">
  <div class="modal-background"></div>
  <div class="modal-card" style="max-height:600px; height:600px">
   <!-- height:600px -->
    <header class="modal-card-head" style="padding-top: 12px; padding-bottom:0; background-color: #8dbf3b;">
        <p class="modal-card-title modal-ie-new" style="color:#ffffff">Skapa nytt utskick</p> 
    </header>

    <section class="modal-card-body" style="padding-top: 6px; padding-bottom:4px;">
       
        <div class="columns import-group">
            <div class="column modal-column" style="margin-top: 12px; padding-bottom:0">
            <label class="modal-label" style="font-size:14px; font-weight:bold;">Välj event för utskicket</label>
            </div>
        </div>

        <div class="columns import-group">
            <div class="column modal-column" style="padding-top: 6px; padding-bottom:0">
                <div class="select" style="width:100%" >
                    <select id="ddEventList" style="width:100%">
                       <option></option>
                    </select>
                </div>
            </div>
        </div>

        <div class="columns modal-columns" >
            <div class="column modal-column" style="padding-top: 14px;">
                <label class="modal-label" style="font-size:14px; font-weight:bold;">&nbsp;Namn på utskick</label>
                <input type="text" id="event-name" class="input is-primary" style="margin-top:5px; margin-bottom: 12px;">
            </div>
        </div>

    </section>  
   
    <footer class="modal-card-foot" style="padding-top: 10px; padding-bottom:10px;" >
        <div class="buttons is-right" style="width:100%">
            <span id="eCloseEventNewModal" style="width:84px" class="button" >Avbryt</span>
            <span id="eCreateEvent" style="width:84px" class="button is-primary" >Skapa</span>  
    </footer>
  </div>
</div>

<div id="invoice-event-settings-modal"  class="modal ">
  <div class="modal-background"></div>
  <div class="modal-card" style="max-height:580px; height:580px">
   <!-- height:600px -->
    <header class="modal-card-head" style="padding-top: 12px; padding-bottom:0; background-color: #8dbf3b;">
        <p class="modal-card-title modal-ie-new" style="color:#ffffff">Meddelande</p> 
    </header>

    <section class="modal-card-body invoice-event-setting-preview" style="display:none">
        <div class="columns modal-columns">
            <div class="column modal-column" id="invoice-event-setting-preview">
            Preview
            </div>
        </div>
    </section>

    <section class="modal-card-body invoice-event-setting-main">
        <div class="columns modal-columns">
            <div class="column modal-column">
                <label class="modal-label" style="font-size:14px; font-weight:bold;">&nbsp;Namn på utskick</label>
                <input type="text" id="setting-event-name" class="input is-primary modal-input">
            </div>
        </div>

        <div class="columns modal-columns">
            <div class="column modal-column">
                <label class="modal-label" style="font-size:14px; font-weight:bold;">&nbsp;Meddelande i e-post </label>
                <textarea id="settings-body"  placeholder="Skriv in ditt meddelande här ..." class="textarea is-primary is-small modal-textarea" rows="5"></textarea>
            </div>
        </div>

        <div class="columns modal-columns">
            <div class="column modal-column" style="padding-top: 8px; padding-bottom:0">
            <label class="modal-label" style="font-size:14px; font-weight:bold;">Välj formulärlänk</label>
            </div>
        </div>

        <div class="columns modal-columns">
            <div class="column modal-column" style="padding-top: 68x; padding-bottom:0">
                <div class="select" style="width:100%" >
                    <select id="ddFormLinkEventList" style="width:100%">
                       <option val="Hämta din faktura här!">Hämta din faktura här!</option>
                       <option val="Anmäl dig här!">Anmäl dig här!</option>
                       <option val="Gör din registrering här!">Gör din registrering här!</option>
                       <option val="Betala här!">Betala här! </option>
                       <option val="Beställ här!">Beställ här! </option>
                    </select>
                </div>
            </div>
        </div>

       
        <div class="columns modal-columns settings-reminder-container">
            <div class="column modal-column">
                <label class="checkbox modal-label" style="font-size:14px; font-weight:bold;"> <input class="is-primary is-small modal-checkbox" id="settings-reminder-text-on" type="checkbox">&nbsp;Meddelande i påminnelse</label>
                <textarea id="settings-reminder-body"  placeholder="Skriv in ditt meddelande här ..." class="textarea is-primary is-small modal-textarea" rows="5"></textarea>
            </div>
        </div>

       
    </section>  
  
    <footer class="modal-card-foot" style="padding-top: 10px; padding-bottom:10px;" >
        <div class="buttons is-right" style="width:100%">
       
            <span id="ePreviewInvoice" class="button is-dark" >Förhandsgranska</span>
            <span id="eCloseEventSettingsModal" style="width:84px" class="button" >Avbryt</span>
            <span id="eEventSettingsSave" style="width:84px" class="button is-primary" >Spara</span>  
    </footer>
  </div>
</div>

<div id="invoice-item-modal"  class="modal ">
  <div class="modal-background"></div>
  <div class="modal-card" style="max-height:580px; height:580px">
    <header class="modal-card-head" style="padding-top: 12px; padding-bottom:0; background-color: #5a7d22;">
        <p class="modal-card-title" id="title-invoice-item-modal" style="color:#ffffff">Mottagare i utskick</p> 
    </header>

    <section id = "GetTab" class="modal-card-body" style="padding-top: 6px; padding-bottom:0; display:none">
        <div id="customer-list" class="columns get-tab" style="padding-top: 8px">
        </div>
    </section>

    <section id = "ItemTab" class="modal-card-body" style="padding-top: 6px; padding-bottom:0;">
        <div class="columns modal-columns item-tab">
            <div class="column modal-column">
                <label class="modal-label">&nbsp;Namn på mottagare</label>
                <p class="control has-icons-right" style="margin-bottom:0">
                    <input type="text" id="invoice-people-name" class="input is-primary" style="padding-right:3px; width:530px;" autocomplete="off">   
                    <span class="icon is-small is-right" style="width: auto; pointer-events: auto;"> 
                        <button id="eInvoiceGetTab" class="button is-dark">&nbsp;Hämta </button>
                    </span>
                </p>
            </div>
        </div>

        <div class="columns modal-columns item-tab">
            <div class="column modal-column">
                <label class="modal-label" >&nbsp;E-post </label>
                <input type="text" id="invoice-email" class="input is-primary" autocomplete="off">
            </div>
        </div>

        <div class="columns modal-columns item-tab">
            <div class="column modal-column">
                <label class="modal-label" >&nbsp;Referens </label>
                <input type="text" id="invoice-referens" class="input is-primary" autocomplete="off">
            </div>
        </div>
     
        <div class="columns modal-columns item-tab">
            <div class="column modal-column">
                <label class="modal-label" id="invoice-amount-label">&nbsp;Belopp</label>
            </div>
            <div class="column modal-column col-planed-date" style="padding-left: 6px">
                <label class="modal-label">Skickas datum </label>
            </div>
            <div class="column modal-column col-sent-date">
                <label class="modal-label" id="invoice-label-sent-datetime">&nbsp;Skickad</label>
            </div>
            <div class="column modal-column col-reminder-last-datetime">
                <label class="modal-label">&nbsp;Påmind</label>
            </div>
            <div class="column modal-column col-empty"></div>
            <div class="column modal-column col-empty2"></div>

            <div class="column modal-column col-confirmed">
                <label class="modal-label" id="invoice-label-confirmed-datetime">&nbsp;Hämtad datum</label>
            </div>
        </div>

        <div class="columns modal-columns item-tab" >
            <div class="column modal-column">
                <input type="text" id="invoice-amount" class="input is-primary modal-input" style="max-width: 160px; width: 100%" autocomplete="off">
            </div>
            <div class="column modal-column col-planed-date">
                <input type="date" id="invoice-planed-date" class="input is-primary" style="max-width: 170px; width: 100%" autocomplete="off">
            </div>
            <div class="column modal-column col-sent-date">
                <input type="text" id="invoice-sent-datetime" class="input is-primary" style="max-width: 120px; width: 100%">
            </div>
            <div class="column modal-column col-reminder-last-datetime">
                <input type="text" id="invoice-reminder-last-datetime" class="input is-primary margin-top:2px; " style="max-width: 120px; width: 100%">
            </div>
            <div class="column modal-column col-empty"></div>
            <div class="column modal-column col-empty2" ></div>
            <div class="column modal-column col-confirmed">
                <input type="text" id="invoice-confirmed-datetime" class="input is-primary modal-input" style="max-width: 120px; width: 100%">
            </div>
        </div>
        
        <div class="columns modal-columns-line col-remider item-tab">
            <div class="column modal-column-line"></div>
        </div>

        <div class="columns modal-columns col-remider item-tab">
            <div class="column modal-column">
                <label class="checkbox modal-label" > <input class="is-primary is-small modal-checkbox" id="invoice-auto-reminder" type="checkbox">&nbsp;Påminnelse</label>
            </div>
            <div class="column modal-column reminder-container">
                <label class="checkbox modal-label"> &nbsp;Dagar</label>
            </div>
            <div class="column modal-column reminder-container">
                <label class="checkbox modal-label">&nbsp;Gånger kvar</label>
            </div>
            <div class="column modal-column reminder-container">
                <label class="modal-label" id="invoice-label-reminder-next-date">&nbsp;Nästkommande</label>
            </div>
        </div>
       
        <div class="columns modal-columns reminder-container item-tab">
            <div class="column modal-column">
            </div>
            <div class="column modal-column">
                <?php 
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
                    ?>
                    <div class="select"><select id="invoice-reminder-days"><?php echo $optionDays;?></select></div>
            </div>
            <div class="column modal-column">
                <?php 
                    $optionTimes = '<option value="0"> 0</option>';
                    $optionTimes .= '<option value="1"> 1</option>';
                    $optionTimes .= '<option value="2"> 2</option>';
                    $optionTimes .= '<option value="3" selected> 3</option>';
                    $optionTimes .= '<option value="4"> 4</option>';
                    $optionTimes .= '<option value="5"> 5</option>';
                    ?>
                    <div class="select"><select id="invoice-reminder-times"><?php echo $optionTimes;?></select></div>
            </div>
            <div class="column modal-column">
                <input type="text" id="invoice-reminder-next-date" class="input is-primary modal-input" style="max-width: 120px; width: 100%">
            </div>
        </div>

        <div class="columns modal-columns check-reminder-all item-tab" >
            <div class="column modal-column">
                <label class="checkbox modal-label" ><input id="invoice-reminder-all" type="checkbox">&nbsp;&nbsp;Sätt samma påminnelsefrekvens för alla med status: <span id="label-reminder-all-status"></span></label>
            </div>
        </div>

        <div class="columns modal-columns check-send-all item-tab" >
            <div class="column modal-column">
                <label class="checkbox modal-label" ><input id="invoice-send-all" type="checkbox">&nbsp;&nbsp;Sätt samma utskicksdatum för alla med status: <span id="label-send-all-status"></span></label>
            </div>
        </div>

    </section>  
   
    <footer class="modal-card-foot" style="padding-top: 10px; padding-bottom:10px;">
        <?php /* <div class="buttons is-left"><p id="invoice-status-modal" style="padding:12px 0 0 0; margin: 0; color:#5a7d22; font-size: 22px; font-style: italic;">Status</p></div> */ ?>
       
        <div class="buttons is-right" style="width:100%">
			 <span id="ePreviewInvoiceItemModal" code="" class="item-tab button is-link" style="width:84px;">Granska</span>
            <span id="eCloseInvoiceItemModal" class="item-tab button" style="width:84px;">Avbryt</span>
            <span id="eSaveInvoiceItemAsDraftModal" class="item-tab button is-dark" style="width:118px;">Spara utkast</span>  
            
            <span id="eAddInvoiceItemModal" class="item-tab button is-link" style="width:84px;">Skicka</span>  
            <span id="eUpdateInvoiceItemModal" class=" item-tab button is-link" style="width:84px;">Skicka</span>  
            <span id="eSaveInvoiceItemModal" class=" item-tab button is-link" style="width:84px;">Spara</span>  
            <span id="eInvoiceItemTab" class="get-tab button" style="width:84px; display:none">Tillbaka</span>  
        </div>
    </footer>
  </div>
</div>

<div class="modal" id="remove-item-modal">
    <div class="modal-background"></div>
    <div class="modal-card pl0 pr0  modal-width">
        <header class="modal-card-head">
            <p class="modal-card-title has-text-centered">Ta bort</p>
        </header>
        <section class="modal-card-body">

            <p id="remove-item-modal-text" class="has-text-centered"><br>Är du säker på att du vill ta bort mottagare?<br><br></p>
        </section>
        <footer class="modal-card-foot">
            <button id="eCloseRemoveItemModal" class="button w120 image-center">Avbryt</button>
            <button id="eRemoveItemModal" class="button is-primary w120 image-center">Ja</button>
        </footer>
    </div>
</div>

<div class="modal" id="update-bulk-item-modal">
    <div class="modal-background"></div>
    <div class="modal-card" style="max-height:320px; height:320px; max-width: 380px">
        <header class="modal-card-head" style="padding-top: 12px; padding-bottom:0; background-color: #8dbf3b;">
            <p class="modal-card-title modal-ie-new" style="color:#ffffff">Ändra i utskick</p> 
        </header>
        <section class="modal-card-body">
            <p id="update-bulk-item-text" class="has-text-centered" style="font-size:18px; padding-top: 18px"></p>
        </section>
        <footer class="modal-card-foot">
            <button id="eCloseUpdateBulkItemModal" class="button w120 image-center">Ändra inte</button>
            <button id="eUpdatingBulk" class="button is-primary image-center">Ändra all pågående</button>
        </footer>
    </div>
</div>

<div id="import-modal"  class="modal ">
  <div class="modal-background"></div>
  <div class="modal-card" style="max-height:600px; height:600px">
   <!-- height:600px -->
    <header class="modal-card-head" style="padding-top: 12px; padding-bottom:0; background-color: #8dbf3b;">
        <p class="modal-card-title modal-ie-new" style="color:#ffffff">Importera e-postadresser</p> 
    </header>

    <section class="modal-card-body" style="padding-top: 6px; padding-bottom:4px;">
         
        <div class="columns modal-columns import-main" style="margin-top:12px!important">
            <div class="column modal-column" style="text-align:center">
                <button id="eImportPartCutIn" class="button is-dark" style="width:420px">Klipp in enbart e-postadresser</button>
            </div>
        </div>

        <div class="columns modal-columns import-main" style="margin-top:12px!important">
            <div class="column modal-column" style="text-align:center">
                <button id="eImportPartRecent"   class="button is-dark" style="width:420px">Importera från tidigare utskick</button>
            </div>
        </div>

        <div class="columns modal-columns cut-in-step-1">
            <div class="column modal-column">
                <label class="modal-label" style="font-size:14px; font-weight:bold;">&nbsp;Klipp in enbart e-postadresser - Steg 1 av 3</label>
                <textarea id="import-area"  placeholder="" class="textarea is-primary is-small modal-textarea" rows="15"></textarea>
            </div>
        </div>
        <div class="columns modal-columns cut-in-step-1">
            <div class="column modal-column">
                <div class="control" style="padding-top: 6px" style="display:block">
                    <label class="radio modal-label" >
                        <input type="radio" checked name="delimiter" value="excel">
                        Rad-avgränsad
                    </label>
                    <label class="radio modal-label" >
                        <input type="radio" name="delimiter" value="comma">
                        Komma-avgränsad
                    </label>
                    <label class="radio modal-label">
                        <input type="radio" name="delimiter" value="semi">
                        Semikolon-avgränsad
                    </label>
                </div>
            </div>
        </div>

        <div class="columns modal-columns cut-in-step-2">
            <div class="column modal-column">
                <label class="modal-label" style="font-size:14px; font-weight:bold;">&nbsp;Godkännda e-postadresser - Steg 2 av 3</label>
                <textarea id="import-preview-list"  placeholder="" class="textarea is-primary is-small modal-textarea" rows="10"></textarea>
            </div>
        </div>

        <div class="columns modal-columns cut-in-step-2">
            <div class="column modal-column">
                <label class="modal-label" style="font-size:14px; font-weight:bold;">&nbsp;Ej godkännda e-postadresser / eller data</label>
                <textarea id="import-preview-error-list"  placeholder="" class="textarea is-primary is-small modal-textarea" rows="5"></textarea>
            </div>
        </div>

        <div class="columns import-group import-part-recent" style="margin-top:12px!important">
            <div class="column modal-column">
            <label class="modal-label" style="font-size:14px; font-weight:bold;">Välj nedan från tidigare utskick att importera från</label>
            </div>
        </div>

        <div class="columns import-group import-part-recent" style="margin-top:6px!important">
            <div class="column modal-column">
                <div class="select" style="width:100%" >
                    <select id="ddImportInvoiceEventList" style="width:100%">
                       <option></option>
                    </select>
                </div>
            </div>
        </div>
       
        <div class="columns modal-columns import-part-recent">
            <div class="column modal-column">
                <label class="modal-label" style="font-size:14px; font-weight:bold;">
                    <input class="is-primary is-small" id="import-referense" type="checkbox">&nbsp;Importera referens
                </label>
            </div>
        </div>
        
    </section>  
   
    <footer class="modal-card-foot" style="padding-top: 10px; padding-bottom:10px;" >
        <div class="buttons is-right" style="width:100%">
            <span id="eCloseImportModal" style="width:84px" class="button" >Avbryt</span>
            <span id="eImportPreviewModal" style="width:200px" class="button is-primary" >Förhandsgranska import</span>  
            <span id="eImportModal" style="width:84px" class="button is-primary" >Importera</span>  
            <span id="eImportRecentModal" style="width:84px" class="button is-primary import-part-recent" >Importera</span>  

    </footer>
  </div>
</div>

<div class="modal" id="yesno-modal">
    <div class="modal-background"></div>
    <div class="modal-card">
        <header class="modal-card-head">
            <p class="modal-card-title has-text-centered">Kontrollfråga</p>
        </header>
        <section class="modal-card-body">
            <p id="yesno-text-modal" class="has-text-centered"></p>
        </section>
        <footer class="modal-card-foot" >
            <button id="eYesNoModalNo" class="button is-dark w120 image-center">Avbryt</button>
            <button id="eYesNoModalYes" class="button is-primary w120 image-center">Ja</button>
        </footer>
    </div>
</div>

<div class="modal" id="test-email-modal">
    <div class="modal-background"></div>
    <div class="modal-card pl0 pr0 modal-width">
        <header class="modal-card-head">
            <p class="modal-card-title has-text-centered">Förhandsgranska</p>
        </header>
        <section class="modal-card-body" style="padding-top:18px!important; padding-bottom:26px!important;">
            <div class="columns modal-columns">
                <div class="column modal-column">
                    <label class="modal-label" style="font-size:14px; font-weight:bold;">&nbsp;E-postadress dit förhandsgranskning skickas:</label>
                    <input type="text" id="test-email" class="input modal-input is-primary">
                </div>
            </div>
        </section>
        <footer class="modal-card-foot" >
            <button id="eTestEmailCancel" class="button is-dark w120 image-center">Avbryt</button>
            <button id="eTestEmailSend" class="button is-primary w120 image-center">Skicka</button>
        </footer>
    </div>
</div>


<?php 

echo htmlBoxClearInvoiceEvent();

function htmlBoxClearInvoiceEvent() {

    $html = '';
    $html .= '<div id="box-invoice-event-clear"  class="modal">';
        $html .= '<div class="modal-background"></div>';
        $html .= '<div class="modal-card" style="max-height:330px; height:300px">';
            $html .= '<header class="modal-card-head" style="padding-top: 12px; padding-bottom:0; background-color: #8dbf3b;">';
                $html .= '<p class="modal-card-title modal-ie-new" style="color:#ffffff">' . 'Radera Utskick' . '</p>'; 
            $html .= '</header>';
            $html .= '<section class="modal-card-body">';
                $html .= '<div class="column modal-column" style="padding-top: 10px!important">';
                    //$html .= '<p style="font-size: 20px; margin:12px 8px 8px 8px">Radera Event<p>'; 
                    $html .= '<p id="invoice-event-clear-type-event" style="font-size: 20px; margin:2px 8px 8px 8px"><p>'; 

                    $html .= '<p style="margin:16px 8px 8px 8px">”Radera alla personuppgifter och utskick permanent.”<p>'; 
                    //$html .= '<p style="margin:0px 8px 8px 8px">kommer att raderas permanent.</p>';

                    $html .= '<div class="columns" style="margin:20px 8px 8px 8px; font-weight:bold"> ';
                        $html .= '<label class="checkbox modal-label">';
                        $html .= '<input class="is-primary is-small modal-checkbox" id="eEventClearConfirm" type="checkbox">&nbsp;&nbsp;Godkänn radering!</label>';
                    $html .= '</div>';
                $html .= '</div>';
            
            // $html .= htmlBoxError('box-event-clear'); // Set to box id
                
            $html .= '</section>';
            
            $html .= '<footer class="modal-card-foot" style="padding-top: 10px; padding-bottom:10px;">';
                $html .= '<div class="buttons is-right" style="width:100%">';
                    $html .= '<span id="eBoxInvoiceEventClearClose" style="width:84px" class="button" >Avbryt</span>';
                    $html .= '<span id="eBoxInvoiceEventClearStart" style="width:84px" class="button is-primary" >Radera</span>';  
                $html .= '</div>';
            $html .= '</footer>';
        $html .= '</div>';
    $html .= '</div>';
    return $html;
} 
?>