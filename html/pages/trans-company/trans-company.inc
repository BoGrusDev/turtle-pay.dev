<section class="hero is-primary">
    <div class="hero-body" style ="padding-bottom: 0; padding-top: 0;margin-bottom: 0;margin-top: 0;">
        <div class="container">
            <h1 style="padding-top: 10px;">
           Transaktioner
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
                    <a id="eGetTrans" class="button is-primary eCompany" action="edit-settings">Hämta</a>
                    <a id="ePrintTrans" class="button is-dark eCompany" action="edit-settings">Skriv ut</a>
                    <a id="eExportCsv" class="button is-dark">Excel</a>
                </div>
            </div>

        </div>
    </div>

    <div class="container" id="print-trans">
        <div class="columns" style="margin: 4px 0 6px 0; width:100%; padding-right:0;">
            <div class="column" style="text-align:left; padding-bottom:0; margin:0">
                <div>
                    <h1 style="font-size:24px; font-weight:bold;">Transaktioner</h1>
                </div>
            </div>
            <div class="column" style="text-align:right; padding-bottom:0; padding-right:0; margin:0">
                <span class="bold">Er fordran (+) / skuld (-)</span>
            </div>
        </div>

        <div class="columns" style="margin-top:0px; padding:0 0 0 0;">
            <div id="trans-company-list" class="column" style="padding-top:0; padding-bottom:30px">
            </div>
        </div>

    </div>
</section>
