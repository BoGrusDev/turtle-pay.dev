<section class="hero is-primary">
    <div class="hero-body" style ="padding-bottom: 0; padding-top: 0;margin-bottom: 0;margin-top: 0;">
        <div class="container">
            <h1 style="padding-top: 10px;">
           Bokföringsorder
            </h1>
        </div>
    </div>
</section>

<section class="section">

    <div class="container">
        <div class="columns" style="margin: 4px 0 6px 0; width:100%; padding-right:0;">
            <div class="column" style="padding-bottom:0">
                <p style="font-weight:bold; margin-bottom: 4px">Från datum</p>
                <input type="date" class="form-control" id="from_date" style="width:250px;font-size:16px">
                <?php // <input type="text" class="form-control" id="from_date" placeholder="åååå-mm-dd" maxlength="10" style="width:110px;font-size:16px"> ?>
            </div>
            <div class="column"  style="padding-bottom:0">
                <p style="font-weight:bold; margin-bottom: 4px">Till datum</p>
                <input type="date" class="form-control" id="to_date" style="width:250px;font-size:16px">
                <?php // <input type="text" class="form-control" id="to_date" placeholder="åååå-mm-dd" maxlength="10" style="width:110px;font-size:16px"> ?>
            </div>
            <div class="column"  style="padding-bottom:0;padding-right:0;">
                <div class="buttons is-right">

                   
                    <a id="eBoOrder" class="button is-primary">Hämta</a>
                    <a id="eBoOrderPdf" class="button is-dark">PDF</a>
                    <a id="ePrintBoOrder" class="button is-dark">Skriv ut</a>    
                    <?php if ($HasSie == 'y') { ?>
                        <a id="eSieFileInit" class="button is-light" style="border-color:#bbbbbb;">SIE-fil</a>
                     <?php } ?>
                   
                
                
                </div>
            </div>

        </div>
    </div>


    <div class="container" id="print-boorder" style="display:none">
        <div class="columns" style="margin: 4px 0 6px 0; width:100%; padding-right:0;">
            <div class="column" style="text-align:left; padding-bottom:0; margin:0">
                <div>
                    <h1 style="font-size:24px; font-weight:bold;">Bokföringsorder</h1>
                </div>
            </div>
            <?php /*
            <div class="column" style="text-align:right; padding-bottom:0; padding-right:0; margin:0">
                <span class="bold">Er fordran (+) / skuld (-)</span>
            </div>
            */ ?>
        </div>

        <div class="columns" style="margin-top:0px; padding:0 0 0 0;">
            <div id="boorder-list" class="column" style="padding-top:0; padding-bottom:30px">
            </div>
        </div>

    </div>

</section>

<div class="modal" id="sie-file-modal">
    <div class="modal-background"></div>
        <div class="modal-card pl0 pr0  modal-width">
            <header class="modal-card-head">
                <p class="modal-card-title has-text-centered">Exportera till SIE-fil</p>
                <!--<button class="eSieExportClose button" style="border-radius: 25px"aria-label="close">X</button> -->
            </header>
            <section class="modal-card-body" style="min-height: 140px;">
                <div class="columns modal-columns sie-file-modal-date">
                    <div class="column modal-column" style="padding-top: 12px!important;">
                        <p style="font-weight:bold; margin-bottom: 4px">Till datum</p>
                        <input type="date" class="form-control" id="sie-date" style="width:250px;font-size:16px">
                    </div>
                </div>
                <div class="columns modal-columns">
                    <div class="column modal-column" style="padding-top: 12px!important;">
                        <p id="sie-file-modal-result-text" style="margin-top: 6px"></p>
                    </div>
                </div>

            </section>
            <footer class="modal-card-foot">
                <div class="buttons is-right" style="width:100%">
                    <button id="eSieExportClose" class="button is-dark w120 sie-file-modal-normal" style="margin-right:8px">Avbryt</button>
                    
                    <button id="eSieExport" class="button is-primary w120 sie-file-modal-normal">Exportera</button>
                    <a id="sie-file-modal-file" href="" 
                        download=""
                        class="sie-file-modal-result" style="display:none"> 
                        <button id="eDownload" class="button is-primary" type="button">Ladda ner SIE-fil</button>
                    </a> 
                    <!--
                    <button id="eSieExportDone" class="button is-dark w120 eSieExportClose" style="display:none; margin-left:8px">Klart</button>
                    -->
                </div>
            </footer>
        </div>
    </div>
</div>
