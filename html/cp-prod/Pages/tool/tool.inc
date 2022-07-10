<div id="tool-menu" class="invoice-service-section">
    <div id="dd-menu" class="dropdown is-active">
        <div class="dropdown-menu" id="dropdown-menu" role="menu">
            <div class="dropdown-content has-background-light">
                <a href="" class="dropdown-item menu-select" action="tool-spar" >
                   SPAR
                </a>
               
               
                <?php /*
                 <hr class="dropdown-divider">
                <a class="dropdown-item menu-select" action="report-settlement-people" >
                    Daily invoicing
                </a>
                <a class="dropdown-item menu-select" action="report-settlement-people" >
                    Daily reminders
                </a>
                */ ?>
            </div>
        </div>
    </div>
</div>

<div id="tool-spar" class="tool-section" style="display:none">
    <div class="d-flex justify-content-between flex-wrap flex-md-nowrap align-items-center pb-2 mb-3 border-bottom">
        <h1 class="title is-4 has-text-centered no-bottom" id="header-people-name">SPAR -Sökning</h1>

        <div class="columns">

            <div class="column">
                <label style="font-weight: bold">Personal id number: </label>
                <input type="text" id="spar-personal-id-number" class="input is-large" style="width: 200px; height: 32px!important">
            </div>
           
            <div class="column">
                <div class="buttons is-right">
                    <button class="button is-primary" id="eGetSpar">Get SPAR</button>
                </div>
            </div>
        </div>

    <div id="tool-spar-result" class="" ></div>
</div>

