<section class="hero is-primary">
    <div class="hero-body" style ="padding-bottom: 0; padding-top: 0;margin-bottom: 0;margin-top: 0;">
        <div class="container">
            <h1 style="padding-top: 10px;">
                Mina detaljer
            </h1>
        </div>
    </div>
</section>

<section class="section">
    <div class="container">

        <div class="columns" style="margin-top:4px; margin-bottom:6px">
            <div class="column mobile-margin">
                <form id="people-form">
                    <div class="columns details-row">
                        <div class="column details-label w100px"><span>Namn:</span></div>
                        <div class="column details-column"><span id="dName"></span></div>
                    </div>
                    <div class="columns details-row">
                        <div class="column details-label w100px"><span>Personnr:</span></div>
                        <div class="column details-column"><span id="dPersonalId"></span></div>
                    </div>

                    <div class="columns">
                        <div class="column details-label w100px"><span>Adress:</span></div>
                        <div class="column details-column"><span id="dAddress"></span></div>
                    </div>
                    <div class="columns details-row">
                        <div class="column details-label w100px"><span></span></div>
                        <div class="column details-column"><span id="dPostAddress"></span></div>
                    </div>

                    <div class="columns details-row">
                        <div class="column details-label w100px"><span>E-post:</span></div>
                        <div class="column details-column">
                            <span class="edit-off" id="dEmail"></span>
                            <input class="input edit-on" id="editEmail" style="max-width:340px; padding: 0 4px; display:none"/>
                        </div>
                    </div>

                    <div class="columns details-row">
                        <div class="column details-label w100px"><span>Mobil (+46):</span></div>
                        <div class="column details-column">
                            <span class="edit-off" id="dMobile" ></span>
                            <input class="input edit-on" id="editMobile" style="max-width:180px; padding: 0 4px; display:none"/>
                        </div>
                    </div>

                    <div class="columns details-row">
                        <div class="column details-label w100px"><span>Kundnr.:</span></div>
                        <div class="column details-column"><span id="dOcrno"></span></div>
                    </div>

                    <?php /*
                        ALTER TABLE `people` ADD `clearing_no` VARCHAR(10) NULL DEFAULT NULL AFTER `ocrno`;

                    */ ?>
                    <!-- Clearingnr. -->

                    <div class="columns details-row">
                        <div class="column details-label w100px"><span style="color: #5a7d22">Bankuppgifter</span></div>
                    </div>
                    
                    <div class="columns details-row">
                        <div class="column details-label w100px"><span>Clearingnr.</span></div>
                        <div class="column details-label"><span>Kontonummer</span></div>
                    </div>

                    <div class="columns details-row edit-off">
                        <div class="column details-label w100px"><span id="dClearingNo"></span></div>
                        <div class="column details-label"><span id="dBankAccount"></span></div>
                    </div>

                    <div class="columns details-row">
                        <div class="column details-label w100px">
                            <input class="input edit-on" maxlength="7" id="editClearingNo" style="max-width: 80px; padding: 0 4px; display:none"/>
                        </div>
                        <div class="column details-label">
                            <input class="input edit-on" maxlength="20" id="editBankAccount" style="max-width:180px; padding: 0 4px; display:none"/>
                        </div>
                    </div>
                    
                    <div class="columns">
                        <div class="column" style="padding-top:20px">
                            <button id="eEditModeOn" class="button is-primary edit-off" >Ändra</button>
                            <button id="eEditModeCancel" class="button is-gray edit-on" style="display:none">Avbryt</button>
                            <button id="eEditUpdate" class="button is-dark edit-on" style="display:none">Spara</button>
                        </div>
                    </div>

              </form>
            </div>
        </div>

        <div class="columns" style="margin-top:0; margin-bottom:0">
            <div class="column mobile-margin" style="padding-bottom:0; padding-top:0;">
                <p style="margin-bottom:0; margin-top:0">
                    Lagen kräver att vi ständigt arbetar för att motverka penningtvätt och finansiering av
                    terrorism och att vi har god kännedom om Dig som kund.
                    Därför ställer vi några frågor vars svar vi hanterar i enlighet med gällande regelverk.
                </p>
            </div>
        </div>

        <div class="columns" style="margin-top:0">
            <div class="column mobile-margin">
                <!-- <a class="button is-primary" href="kyc">Kundkännedom</a> -->
                <button class="button is-primary" id="kyc">Kundkännedom</button> 
            </div>
        </div>
    </div>
    <?php
        require_once 'base-lib/KycModal.inc';
    ?>
</section>

<?php
    require_once 'base-lib/ViewBaseClass.js.inc';
    require_once 'base-lib/Kyc.js.inc';
?>
