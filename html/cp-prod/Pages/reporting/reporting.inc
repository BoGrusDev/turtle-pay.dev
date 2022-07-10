<div id="report-section" class="report-section">
    <div id="dd-menu" class="dropdown is-active">
        <!--
        <div class="dropdown-trigger">
            <button class="button" id="dd-trigger" aria-haspopup="true" aria-controls="dropdown-menu">
                <span>Select report</span>
                <span class="icon is-small">
                    <i class="fas fa-angle-down" aria-hidden="true"></i>
                </span>
            </button>
        </div>
        -->
        <div class="dropdown-menu" id="dropdown-menu" role="menu">
            <div class="dropdown-content has-background-light">
                <a href="" class="dropdown-item menu-select" action="company">
                    Company report
                </a>
                <a class="dropdown-item menu-select" action="booking">
                    Booking report
                </a>
                <!--
                <a class="dropdown-item menu-select" action="outgoing-payment">
                    Outgoing payment report
                </a>
                -->
                <a class="dropdown-item menu-select" action="incoming-payment">
                    Incoming payment report
                </a>
                <hr class="dropdown-divider">
                <a class="dropdown-item menu-select" action="accounts-balance">
                   Account balance & Income statement
                </a>
                <a class="dropdown-item menu-select" action="spec">
                    Specification
                </a>
                <a class="dropdown-item menu-select" action="trans">
                    Transactions
                </a>
                
                <hr class="dropdown-divider">
                <a class="dropdown-item menu-select" action="pep-list">
                    PEP list
                </a>

                <hr class="dropdown-divider">
                <a class="dropdown-item menu-select" action="fi-report">
                    Financial reporting
                </a>

                <hr class="dropdown-divider">
                <a class="dropdown-item menu-select" action="tax-reporting-list">
                    Tax Reporting List
                </a>
                <a class="dropdown-item menu-select" action="tax-reporting-create">
                    Create Tax Reporting
                </a>
                <a class="dropdown-item menu-select" action="tax-reporting-mail">
                    Mail Tax Reporting
                </a>
            </div>
        </div>
    </div>
</div>

<div id="CompanyReportList-section" class="report-section" style="display:none">
    <div class="column no-margin no-padding">
        <div class="column no-margin no-padding" style="padding-bottom:6px">
            <a class="button is-primary eReporting" action="company-list">Get Company report</a>
        </div>
    </div>
    <form class="form-inline">
        <div class="form">
              <label for="from_date">From date: </label>
              <input type="text" class="input" id="from-date" style="width:110px; padding: 2px 4px; margin-left: 8px" value="2018-11-27">
              <label for="to_date">To date: </label>
              <input type="text" class="input" id="to-date" style="width:110px; padding: 2px 4px; margin-left: 8px" value="2018-11-27">
        </div>
    </form>
    <div id="company-report-list" style="height:600px" ></div>
</div>

<div id="BookingReportList-section" class="report-section" style="display:none">
    <div class="column no-margin no-padding">
        <div class="column no-margin no-padding" style="padding-bottom:6px">
            <a class="button is-primary eReporting" action="booking-list">Get Booking Report</a>
			<a class="button is-light eReporting" action="sie-export" style="border-color: #cccccc">Export SIE</a>
            <a class="button is-primary eReporting" action="booking-print">Print</a>
        </div>
    </div>
    <form class="form-inline">
        <div class="form">
              <label for="from_date">From date: </label>
              <input type="text" class="input" id="from-date-booking" style="width:110px; padding: 2px 4px; margin-left: 8px" value="2018-11-27">
              <label for="to_date">To date: </label>
              <input type="text" class="input" id="to-date-booking" style="width:110px; padding: 2px 4px; margin-left: 8px" value="2018-11-27">

        </div>
    </form>
    <div id="booking-report-list" style="height:600px" ></div>
</div>

<div id="IncomingPaymentReportList-section" class="report-section" style="display:none">
    <div class="columns">
        <div class="column">
            <div class="buttons is-right">
                <a class="button is-primary eCompany" disabled action="new-company">Filter</a>
            </div>
        </div>
    </div>
    <div id="IncommingPayment-list" style="height:600px" ></div>
</div>

<div id="AccountsBalanceList-section" class="report-section" style="display:none">

    <div class="columns">
        <div class="column">
            <h1 class="title is-4">Account balance & Income statement</h1>
            <form class="form-inline">
                <div class="form">
                    <label>To date: </label>
                    <input type="text" class="input" id="to-date-accounts-balance" style="width:110px; padding: 2px 4px; margin-left: 8px" value="2018-11-27">
                    <span class="" style="float: right">
                        <a  class="button is-dark eReporting" action="accounts-balance-print">Print</a>
                        <a  class="button is-primary eReporting" action="accounts-balance-list">Get list</a>
                    </span>
                </div>  
            </form>       
        </div>
    </div>

    <div id="accounts-balance-report-list" style="" ></div>
	<div id="accounts-result-list" style="" ></div>
</div>

<div id="Spec-section" style="display:none">
    <div class="columns">
        <div class="column">
            <h1 class="title is-4">Specification</h1>
            <form class="form-inline">
                <div class="form">
                    <label>To date: </label>
                    <input type="text" class="input" id="to-date-spec" style="width:110px; padding: 2px 4px; margin-left: 8px" value="2018-11-27">
                    <label>Object: </label>
                    <div class="select is-primary is-small">
                        <select id="spec-object" class="is-primary" style="font-size:14px;">
                            <option selected value="customer">Customer dept (1380 and 1680)</option>
                            <option value="vendors">Vendors dept</option>
                            <option value="sp">Sales person rebate</option>
                        </select>
                    </div>
                               
                    <span class="" style="float: right">
                        <a id="eSpecItemPrint" class="button is-dark" action="">Print</a>
                        <a id="eExportSpec" class="button is-dark" action="">Excel</a>
                        <a id="eSpecLoadList" class="button is-primary" action="">Get list</a>
                    </span>
                </div>
            </form>       
        </div>
    </div>
  
    <div class="columns">
        <div class="column">
            <div id="spec-list"></div>
        </div>
       
    </div>

</div>

<div id="trans-section" style="display:none">
    <div class="columns">
        <div class="column">
            <h1 class="title is-4">Transactions</h1>
            <form class="form-inline">
                <div class="form">
                    <label>From date: </label>
                    <input type="text" class="input" id="from-date-trans" style="width:110px; padding: 2px 4px; margin-left: 8px" value="2018-11-27">
                    <label>To date: </label>
                    <input type="text" class="input" id="to-date-trans" style="width:110px; padding: 2px 4px; margin-left: 8px" value="2018-11-27">
                    <span class="" style="float: right">
                        <a id="eTransItemPrint" class="button is-dark" action="">Print</a>
                        <a id="eTransLoadList" class="button is-primary" action="">Get list</a>
                    </span>
                </div>
                <!--
                    <div class="buttons is-right">
                        <a class="button is-primary eTrans" disabled action="">Get list</a>
                    </div>
                -->
            </form>       
        </div>
    </div>
  
    <div class="columns">
        <div class="column">
            <div id="trans-list" style="height:600px" ></div>
        </div>
        <div class="column">
            <div id="trans-item"></div>
        </div>
    </div>

</div>

<div id="pep-section" class="report-section" style="display:none">
    <div class="columns">
        <div class="column">
            <h1 class="title is-4">PEP list</h1>
        </div>
    </div>
    
    <div id="pep-report-list" ></div>
</div>

<div id="FiReport-section" class="report-section" style="display:none">
    <div class="column no-margin no-padding">
        <div class="column no-margin no-padding" style="padding-bottom:6px">
            <a class="button is-primary" id = "eFinansiellReportCreate" >Get finansiell report</a>
        </div>
    </div>
    <form class="form-inline">
        <div class="form">
              <label for="fi-date-from">From date: </label>
              <input type="text" class="input" id="fi-date-from" style="width:110px; padding: 2px 4px; margin-left: 8px" value="2018-11-27">
              <label for="fi-date-to">To date: </label>
              <input type="text" class="input" id="fi-date-to" style="width:110px; padding: 2px 4px; margin-left: 8px" value="2018-11-27">
        </div>
    </form>
    <div id="finansiell-report-list" style="height:600px;margin-top:30px; margin-left:12px"" ></div>
</div>

<div id="tax-reporting-section" class="report-section" style="display:none">

    <div class="column no-margin no-padding">
        <div class="column no-margin no-padding" style="padding-bottom:6px">
            <a class="button is-primary ePayment" id="eGetTaxReporting">Get Tax Reporting</a>
            <a class="button is-dark" style="display:none" id="eTaxCreatePdf">Create PDF:s</a>
        </div>
    </div>
    <form class="form-inline">
        <div class="form-group mb-2">
              <label for="tax-reporting-income-year">Income year: </label>
              <input type="text" class="input" id="tax-reporting-income-year" max-length="4" style="width:60px; padding: 2px 4px; margin-left: 8px" value="">
        </div>
    </form>
    <div id="tax-reporting-list" style="height:600px" ></div>
    <a id="taxControllerLink" href="" target="_blank" class="button is-dark" style="display:none; margin-top:12px">Ladda ner Tax Controll Report</a>

</div>

<div id="tax-reporting-create-section" class="report-section" style="display:none">

    <div class="column no-margin no-padding">
        <div class="column no-margin no-padding" style="padding-bottom:6px">
            <a class="button is-primary ePayment" id="eCreateTaxReporting">Create Tax Reporting</a>
        </div>
    </div>
    <form class="form-inline">
        <div class="form-group mb-2">
              <label for="tax-reporting-create-income-year">Income year: </label>
              <input type="text" class="input" id="tax-reporting-create-income-year" max-length="4" style="width:60px; padding: 2px 4px; margin-left: 8px" value="">
        </div>
    </form>
    <div style="padding-top: 20px">
        <h2 class="title is-4" id="create-tax-reporting-reply"></h2>
        <h2 class="title is-4" id="create-tax-reporting-filename"></h2>
    </div>
</div>

<div id="tax-reporting-mail-section" class="report-section" style="display:none">

    <div class="column no-margin no-padding">
        <div class="column no-margin no-padding" style="padding-bottom:6px">
            <a class="button is-primary ePayment" id="eSendTaxReportingMail">Send Tax reporting </a>
        </div>
    </div>
    <form class="form-inline">
        <div class="form-group mb-2">
              <label for="tax-reporting-mail-income-year">Income year: </label>
              <input type="text" class="input" id="tax-reporting-mail-income-year" max-length="4" style="width:60px; padding: 2px 4px; margin-left: 8px" value="">
        </div>
    </form>
    <div id="tax-reporting-mail-list" style="height:600px" ></div>
</div>
