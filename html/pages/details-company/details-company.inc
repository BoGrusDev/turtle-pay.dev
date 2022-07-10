<?php
    require_once "company-model.js.inc";
    require_once "company-view.js.inc";
    require_once "company-controller.js.inc";
    require_once 'base-lib/ViewBaseClass.js.inc';
    require_once "priv.js.inc";
?>

<section class="hero is-primary">    <div class="hero-body" style ="padding-bottom: 0; padding-top: 0;margin-bottom: 0;margin-top: 0;">
        <div class="container">
            <h1 style="padding-top: 10px;">
                Företagsdetaljer
            </h1>
        </div>
    </div>
</section>

<section class="section" id="page-section" style="display:none">
    <div class="container">

        <div class="columns" style="margin-top:4px; margin-bottom:6px">
            <div class="column mobile-margin">
                <form id="people-form">
                    <?php 
                    // ----- 
                    // Adress part
                    // 
                    ?>
                    <div class="columns details-row">
                        <div class="column details-label w-col1"><span>Företag:</span></div>
                        <div class="column details-column"><span id="dCompanyName"></span></div>
                    </div>
                    <div class="columns details-row">
                        <div class="column details-label w-col1"><span>Känt som:</span></div>
                        <div class="column details-column"><span id="dKnownAs"></span></div>
                    </div>

                    <div class="columns details-row">
                        <div class="column details-label w-col1"><span>Adress:</span></div>
                        <div class="column details-column"><span id="dAddress"></span></div>
                    </div>
                    <?php /*
                    <div class="columns details-row">
                        <div class="column details-label w280px"><span>&nbsp;</span></div>
                        <div class="column details-column"><span id="dAddress2"></span></div>
                    </div>
                    */ ?>
                    <div class="columns details-row">
                        <div class="column details-label w-col1"><span>Postadress</span></div>
                        <div class="column details-column"><span id="dPostAddress"></span></div>
                    </div>
                        
                    <div class="columns details-row">
                        <div class="column details-label w-col1"><span>Org.nr:</span></div>
                        <div class="column details-column"><span id="dCompanyIdNumber"></span></div>
                    </div>

                    <div class="columns details-row">
                        <div class="column details-label w-col1"><span>Bankgiro:</span></div>
                        <div class="column details-column"><span id="dBankAccount"></span></div>
                    </div>
                    <div class="columns details-row">
                        <div class="column details-label w-col1"><span>OCR-nummer:</span></div>
                        <div class="column details-column"><span id="dOcrno"></span></div>
                    </div>

                    <div class="columns details-row">
                        <div class="column details-label w-col1"><span>Telefon (+46):</span></div>
                        <div class="column details-column">
                            <span class="edit-off" id="dPhone" ></span>
                            <input class="input edit-on" id="editPhone" style="max-width:180px; padding: 0 4px; height:26px; display:none"/>
                        </div>
                    </div>

                    <div class="columns details-row">
                        <div class="column details-label w-col1"><span>Fakturaavisering:</span></div>
                        <div class="column details-column">
                            <label class="checkbox"><input id="eNotiInvoiceOn" type="checkbox" ></label> 
                        </div>
                    </div>

                    <div class="columns details-row noti-invoice-container" style="display:none">
                        <div class="column details-label w-col1"><span>Epostadress:</span></div>
                        <div class="column details-column">
                            <span class="edit-off" id="dNotiInvoiceEmail"></span>
                            <input class="input edit-on" id="editNotiInvoiceEmail" style="max-width:340px; padding: 0 4px; height:26px; display:none"/>
                        </div>
                    </div>
                  
                    <?php 
                    // ----- 
                    // VAT part
                    // 
                    ?>

                    <div class="columns details-row has-vat-view" style="display:none;">
                        <div class="column details-label w-col1"><span style="color: #5a7d22; font-weight:bold">Momsredovisning:</span></div>
                        <div class="column details-column">
                            <label class="checkbox"><input id="eHasVatAccounting" type="checkbox" ></label> 
                        </div>
                    </div>
                    
                    <div class="columns details-row vat-view" style="display:none">
                        <div class="column details-label w-col1"><span style="color: #5a7d22">Momskonton</span></div>
                    </div>
        
		            <div class="columns details-row vat-view" style="display:none">
			            <div class="column details-label w-col1">
                                <span class="edit-off" id="dVatAccountNameCode1"></span>
                                <input class="input edit-on" id="editdVatAccountNameCode1" maxlength="24" style="max-width:240px; padding: 0 4px; height:26px;  display:none" />
                        </div>
                        <div class="column details-column">
                            <span class="edit-off" id="dVatAccountNoCode1"></span>
                            <input class="input edit-on" id="editdVatAccountNoCode1" style="max-width:80px; padding: 0 4px; height:26px; display:none"/>
                        </div>
                    </div>
    
                    <div class="columns details-row vat-view" style="display:none">
			            <div class="column details-label w-col1">
                            <span class="edit-off" id="dVatAccountNameCode2"></span>
                            <input class="input edit-on" id="editdVatAccountNameCode2" maxlength="24" style="max-width:240px; padding: 0 4px; height:26px;  display:none" />
                        </div>
                        <div class="column details-column">
                            <span class="edit-off" id="dVatAccountNoCode2"></span>
                            <input class="input edit-on" id="editdVatAccountNoCode2" style="max-width:80px; padding: 0 4px; height:26px; display:none"/>
                        </div>
                    </div>

                    <div class="columns details-row vat-view" style="display:none">
			            <div class="column details-label w-col1">
                                <span class="edit-off" id="dVatAccountNameCode3"></span>
                                <input class="input edit-on" id="editdVatAccountNameCode3" maxlength="24" style="max-width:240px; padding: 0 4px; height:26px;  display:none" />
                        </div>
                        <div class="column details-column">
                            <span class="edit-off" id="dVatAccountNoCode3"></span>
                            <input class="input edit-on" id="editdVatAccountNoCode3" style="max-width:80px; padding: 0 4px; height:26px; display:none"/>
                        </div>
                    </div>

                    <div class="columns details-row" style="display:none">
                        <div class="column details-label w-col1"><span>Moms på faktura:</span></div>
                        <div class="column details-column">
                            <label class="checkbox"><input id="eHasVatInvoice" type="checkbox" ></label> 
                        </div>
                    </div>

                    <div class="columns details-row has-tdb-view" style="display:none">
                        <div class="column details-label w-col1"><span style="color: #5a7d22; font-weight:bold">TDB inställningar</span></div>
                        <div class="column details-column">
                        </div>
                    </div>


                    <?php /*
                    <div class="columns details-row noti-invoice-container" style="display:none">
                        <div class="column details-label w-col1"><span>Epostadress:</span></div>
                        <div class="column details-column">
                            <span class="edit-off" id="dNotiInvoiceEmail"></span>
                            <input class="input edit-on" id="editNotiInvoiceEmail" style="max-width:340px; padding: 0 4px; height:26px; display:none"/>
                        </div>
                    </div>
                    */ ?>


                    <div class="columns details-row has-tdb-view" style="display:none">
                        <div class="column details-label w-col1"><span>Organizer ID:</span></div>
                        <div class="column details-column">
                            <span class="edit-off" id="dTdbOrgno"></span>
                            <input class="input edit-on" id="editTdbOrgno" style="max-width:100px; padding: 0 4px; height:26px; display:none"/>
                        </div>
                    </div>
                    
                    <div class="columns details-row has-tdb-view" style="display:none">
                        <div class="column details-label w-col1"><span>API-nyckel:</span></div>
                        <div class="column details-column">
                        <span class="edit-off" id="dTdbApikey"></span>
                            <input class="input edit-on" id="editTdbApikey" style="max-width:280px; padding: 0 4px; height:26px; display:none"/>
                        </div>
                    </div>
                    
              </form>
            </div>

            <div class="column mobile-margin">
                <?php 
                    // ----- 
                    // Booking report
                    // 
                ?>
                <div class="columns details-row">
                    <div class="column details-label w-col1"><span style="color: #5a7d22; font-weight:bold">Bokföringsorder:</span></div>
                    <div class="column details-column">
                        <label class="checkbox"><input id="eHasBo" type="checkbox" ></label> 
                    </div>
                </div>              

                <div class="columns details-row bo-notify-on-checkbox" style="display:none">
                    <div class="column details-label w-col1"><span>Bokföringsorderavisering:</span></div>
                    <div class="column details-column">
                        <label class="checkbox"><input id="eBoNotifyOn" type="checkbox" ></label> 
                    </div>
                </div>

                <div class="columns details-row bo-notify-on-container" style="display:none">
                    <div class="column details-label w-col1"><span>Epostadress:</span></div>
                    <div class="column details-column">
                        <span class="edit-off" id="dEmailReport"></span>
                        <input class="input edit-on" id="editEmailReport" style="max-width:340px; padding: 0 4px; height:26px; display:none"/>
                    </div>
                </div>
                
                <div class="columns details-row bo-view" style="display:none">
                    <div class="column details-label w-col1"><span>Verifikationstext:</span></div>
                    <div class="column details-column">
                        <span class="edit-off" id="dBoText" ></span>
                        <input class="input edit-on" id="editBoText" maxlength="40" style="max-width:240px; padding: 0 4px; height:26px; display:none"/>
                    </div>
                </div>

                <div class="columns details-row bo-view" style="display:none">
                    <div class="column details-label w-col1"><span style="color: #5a7d22">Kontonamn</span></div>
                    <div class="column details-column"><span style="color: #5a7d22">Konto</span></div>
                </div>
              
                <div class="columns details-row bo-view" style="display:none">
                    <div class="column details-label w-col1">
                        <span class="edit-off" id="dBoSettlAccountName"></span>
                        <input class="input edit-on" id="editBoSettlAccountName" placeholder="Turtle Pay avräkning" maxlength="24" style="max-width:240px; padding: 0 4px; height:26px;  display:none" />
                    </div>
                    <div class="column details-column">
                        <span class="edit-off" id="dBoSettlAccount" ></span>
                        <input class="input edit-on is-numeric" id="editBoSettlAccount"  maxlength="6" style="max-width:80px; padding: 0 4px; height:26px; display:none"/>
                    </div>
                </div>
                
                <div class="columns details-row bo-view" style="display:none">
                    <div class="column details-label w-col1">
                        <span class="edit-off" id="dBoBankAccountName"></span>
                        <input class="input edit-on" id="editBoBankAccountName" placeholder="Bank" maxlength="24" style="max-width:240px; padding: 0 4px; height:26px; display:none"/>
                    </div>
                    <div class="column details-column">
                        <span class="edit-off" id="dBoBankAccount"></span>
                        <input class="input edit-on is-numeric" id="editBoBankAccount" maxlength="6" style="max-width:80px; padding: 0 4px; height:26px; display:none"/>
                    </div>
                </div>

                <div class="columns details-row bo-view" style="display:none">
                    <div class="column details-label w-col1">
                        <span class="edit-off" id="dBoTransfeeAccountName"></span>
                        <input class="input edit-on" id="editBoTransfeeAccountName" placeholder="Transaktionsavgift" maxlength="24" style="max-width:240px; padding: 0 4px; height:26px; display:none"/>
                    </div>
                    <div class="column details-column">
                        <span class="edit-off" id="dBoTransfeeAccount" ></span>
                        <input class="input edit-on" id="editBoTransfeeAccount"  maxlength="6" style="max-width:80px; padding: 0 4px; height:26px; display:none"/>
                    </div>
                </div>

                <div class="columns details-row bo-view" style="display:none">
                    <div class="column details-label w-col1">
                        <span class="edit-off" id="dBoInterestAccountName"></span>
                        <input class="input edit-on" id="editBoInterestAccountName" placeholder="Ränta" maxlength="24" style="max-width:240px; padding: 0 4px; height:26px; display:none"/>
                    </div>
                    <div class="column details-column">
                        <span class="edit-off" id="dBoInterestAccount" ></span>
                        <input class="input edit-on is-numeric" id="editBoInterestAccount" maxlength="6" style="max-width:80px; padding: 0 4px; height:26px; display:none"/>
                    </div>
                </div>

                <!--
                <div class="columns details-row bo-view" style="display:none">
                    <div class="column details-label w-col1">
                        <span class="edit-off" id="dBoAppAccountName"></span>
                        <input class="input edit-on" id="editBoAppAccountName" placeholder="App-konto" maxlength="24" style="max-width:240px; padding: 0 4px; height:26px; display:none"/>
                    </div>
                    <div class="column details-column">
                        <span class="edit-off" id="dBoAppAccount"></span>
                        <input class="input edit-on is-numeric" id="editBoAppAccount" maxlength="6" style="max-width:80px; padding: 0 4px; height:26px; display:none"/>
                    </div>
                </div>
                -->

                <div class="columns details-row bo-view" style="display:none; margin-bottom:0">
                    <div class="column details-label w-col1"><span style="color: #5a7d22">Intäktskonton</span></div>
                    <div class="column details-column edit-on" style="display:none"><span><button id="eAccountNew" class="button is-primary is-small">Lägg till</button></span></div>
                    <div class="column details-label edit-off vat-view"><span style="color: #5a7d22;margin-left:60px; display:none">Moms</span></div>
                </div>
                
                <div id="AccountList" class="bo-view" style="display:none"></div>

                <?php 
                    // ----- 
                    // SIE export
                    // 
                ?>

                <div class="columns details-row has-sie-view" style="margin-top:6px">
                    <div class="column details-label w-col1"><span style="color: #5a7d22; font-weight:bold">SIE export</span></div>
                    <div class="column details-column">
                        <!-- 
                            <label style="display:block" class="checkbox"><input id="eHasSie" type="checkbox" disabled></label> 
                        -->
                    </div>
                </div>

                <div class="columns details-row sie-view" style="display:none">
                    <div class="column details-label w-col1">
                        <span>Räkenskapsår:</span>
                    </div>
                    <div class="column details-column">
                        <span class="edit-off" id="dFyYearNo"></span>
                        <div class="select edit-on" style="margin-top: 6px; margin-bottom:4px; display:none">
                            <select id="editFyYearNo" >
                                <option value="1">Januari - December</option>
                                <option value="2">Februari - Januari</option>
                                <option value="3">Mars - Februari</option>
                                <option value="4">April - Mars</option>
                                <option value="5">Maj - April</option>
                                <option value="6">Juni - Maj</option>
                                <option value="7">Juli - Juni</option>
                                <option value="8">Augusti - Juli</option>
                                <option value="9">September - Augusti</option>
                                <option value="10">Oktoberr - September</option>
                                <option value="11">November - Oktober</option>
                                <option value="12">December - November</option>
                            </select>
                        </div>
                    </div>
                </div>

                <div class="columns details-row sie-view" style="display:none">
                    <div class="column details-label w-col1">
                        <span>Export typ:</span>
                    </div>
                    <div class="column details-column">
                        <span class="edit-off" id="dSieType"></span>
                        <div class="select edit-on" style="margin-top: 6px; margin-bottom:4px; display:none">
                            <select id="editSieType" >
                                <option value="d">Detaljerad (per transaktion)</option>
                                <option value="a">Aggregerad (per dag)</option>
                            </select>
                        </div>
                    </div>
                </div>

                <div class="columns details-row sie-view" style="display:none">
                    <div class="column details-label w-col1">
                        <span>Typ av kontoplan:</span>
                    </div>
                    <div class="column details-column">
                        <span class="edit-off" id="dSieKpType"></span>
                        <div class="select edit-on" style="margin-top: 6px; margin-bottom:4px; display:none">
                            <select id="editSieKpType" >
                                <option value="BAS95">BAS 95</option>
                                <option value="BAS96">BAS 96</option>
                                <option value="EUBAS97">EUBAS 97</option>
                                <option value="NE2007">NE 2007</option>
                            </select>
                        </div>
                    </div>
                </div>

                <div class="columns details-row sie-view" style="display:none">
                    <div class="column details-label w-col1">
                        <span>Serie:</span>
                    </div>
                    <div class="column details-column">
                        <span class="edit-off" id="dSieSerie" ></span>
                        <input class="input edit-on" id="editSieSerie" maxlength="1" style="max-width:80px; padding: 0 4px; height:26px; display:none"/>
                    </div>
                </div>

                <div class="columns details-row sie-view-ver-no" style="display:none">
                    <div class="column details-label w-col1">
                        <span>Första verfikationsnnr:</span>
                    </div>
                    <div class="column details-column">
                        <span class="edit-off" id="dSieVerno" ></span>
                        <input class="input edit-on" id="editSieVerno"  maxlength="8" style="max-width:80px; padding: 0 4px; height:26px; display:none "/>
                    </div>
                </div>

                <div class="columns details-row sie-view-start-date" style="display:none">
                    <div class="column details-label w-col1">
                        <span>Första SIE datum:</span>
                    </div>
                    <div class="column details-column">
                        <span class="edit-off" id="dSieStartDate" ></span>
                        <input type="date" class="input edit-on" id="editSieStartDate"  style="width:150px;font-size:16px; padding: 0 4px; height:26px; display:none "/>
                    </div>
                </div>

                <div class="columns details-row sie-view-last-ver-no" style="display:none">
                    <div class="column details-label w-col1">
                        <span>Senaste verfikationsnr:</span>
                    </div>
                    <div class="column details-column">
                        <span class="edit-off" id="dSieLastVerNo" ></span>
                    </div>
                </div>

                <div class="columns details-row sie-view-last-booking-date" style="display:none">
                    <div class="column details-label w-col1">
                        <span>Senaste datum:</span>
                    </div>
                    <div class="column details-column">
                        <span class="edit-off" id="dSieLastBookingDate" ></span>
                    </div>
                </div>
                
            </div>
       
        </div>
        
        <div class="columns">
            <div class="column has-text-centered" style="margin-top:40px; border-top: 1px solid #cccccc">
                <button id="ePrivOpen" class="button edit-off" style="display:none;width:120px;background-color: #2565AE; color: #eeeeee;">Behörighet</button>
                <button id="eEditOn" class="button is-primary edit-off" style="width:120px;">Ändra</button>
                <button id="eEditCancel" class="button is-gray edit-on" style="display:none;width:120px;">Avbryt</button>
                <button id="eEditUpdate" class="button is-dark edit-on" style="display:none;width:120px;">Spara</button>
            </div>
        </div>

    </div>
</section>

<div id="contract-box"  class="modal ">
  <div class="modal-background"></div>
  <div class="modal-card" style="max-height:290px; height:290px">
    <!-- height:600px -->
        <header class="modal-card-head" style="padding-top: 12px; padding-bottom:0; background-color: #8dbf3b;">
            <p class="modal-card-title modal-ie-new" style="color:#ffffff; margin-bottom: 12px;">Signering av avtal</p> 
        </header>
        <section class="modal-card-body" style="padding-top: 6px; padding-bottom:4px;">
            <div class="container" style="margin-top:4px; padding-bottom: 0">
                <div class="columns">
                    <div class="column mobile-margin">
                        <p style="font-size:16px; margin-top: 4px; margin-bottom:8px">
                            Vi har uppdaterat vårt samarbets- och personuppgiftsavtal, se villkor 
                            <a style="font-weight:bold" id="eContractPreViewPdf">här.</a>
                        </p>
                        <p style="font-size:16px; margin-top: 4px; margin-bottom:8px">
                            Avtalet signeras med BankID!
                        </p>
                        <p id ="contract-box-message" style="font-size:16px;font-style:italic; margin-top: 1px; color:#53731f">
                        &nbsp;<br>&nbsp;
                        </p>
                    </div>
                </div>

                <div class="columns">
                    <div class="column" style="padding-top: 10px">
                        <div class="field">
                            <label class="checkbox" style="font-size:14px">
                                <?php if ($isMobile == "yes") { ?>
                                    <input type="checkbox" id="eBankIdInternal" checked>
                                <?php } else { ?>
                                    <input type="checkbox" id="eBankIdInternal">
                                <?php } ?>
                                Jag har BankID på denna enhet
                            </label>
                        </div>
                    </div>
                </div>
            </div>
        </section>

        <footer class="modal-card-foot" style="padding-top: 10px; padding-bottom:10px;" >
            <div style="width:100%">
                <div class="buttons is-right" style="width:100%">
                    <span id="eContractCancel" style="width:84px" class="button" >Avbryt</span>
                    <span id="eContractComplete" style="width:84px" class="button is-primary" >Signera</span> 
                </div>
            </div>
        </footer>
    </div>
</div>

<div class="modal" id="bankid-box">
    <div class="modal-background"></div>
        <div class="modal-card pl0 pr0  modal-width" style="margin-top: -150px!important">
            <header class="modal-card-head">
                <p class="modal-card-title has-text-centered">Signering</p>
            </header>
            <section class="modal-card-body">
                <p class="has-text-centered">Väntar på BankID signering</p>
            </section>
        <footer class="modal-card-foot">
            <button id="eBankIdBoxContinue" class="button is-dark w120 image-center" >Fortsätt</button>
        </footer>
    </div>
</div>

<div class="modal" id="priv-box">
    <div class="modal-background"></div>
    <div class="modal-card" style="max-height:700px; height:700px">
        <header class="modal-card-head">
            <p class="modal-card-title has-text-centered">Behörighet</p>
        </header>
        <section class="modal-card-body">
            <div class="container priv-list-container">
                <div class="columns" style="margin-top:4px; margin-bottom:6px">
                    <div class="column mobile-margin">
                        <div id="priv-list"></div>
                    </div>
                </div>
            </div>
            <div class="container priv-update-container" style="display:none">
                <label class="modal-label" style="display:block">Personnr: </label>
                <p id="priv-personal-id-number-text"></p>
                <input type="text" id="priv-personal-id-number" class="input modal-input is-primary is-numeric" maxlen="12" style="width:160px">

                <label id="priv-name-label" class="modal-label" style="display:block">Namn </label>
                <p id="priv-name-text"></p>
           
                <div class="control" style="padding-top: 6px" style="display:block">
                    <?php /*
                    <label class="radio modal-label" >
                        <input type="radio" name="priv" value="ac">
                        Ekonomi
                    </label>
                    */ ?>
                    <label class="radio modal-label" style="font-size:16px!important;display:inline-flex">
                        <input type="radio" name="priv" value="pr">
                        &nbsp;Administratör
                    </label>
                    <label class="radio modal-label" style="font-size:16px!important;display:inline-flex">
                        <input type="radio" name="priv" value="sp">
                        &nbsp;Funktionär
                    </label>
                    <label id="priv-radio-pe" class="radio modal-label" style="font-size:16px!important;display:inline-flex">
                        <input type="radio" name="priv" value="pe">
                        &nbsp;Ta bort
                    </label>
                </div>

                <div id="warning-container">
                    <div id="priv-warning-text"></div>
                </div>
            </div>                    
        </section>
        <footer class="modal-card-foot">
            <div class="buttons is-right w100p"">
                <button id="ePrivCancel" class="button" style="display:none">Avbryt</button>
                <button id="ePrivInsert" class="button is-primary" style="display:none">Lägg till</button>
                <button id="ePrivUpdate" class="button is-primary"  style="display:none">Spara ändring</button>
                <button id="ePrivClose" class="button is-dark">Stäng</button>
                <button id="ePrivAdd" class="button is-primary" >Lägg till användare</button>
            </div>
        </footer>
    </div>
</div>
