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
                    Create Tax Report Fil (XML)
                </a>
                <a class="dropdown-item menu-select" action="booking">
                    Create TaxStament on people
                </a>
                <!--
                <a class="dropdown-item menu-select" action="outgoing-payment">
                    Outgoing payment report
                </a>
                -->
                <a class="dropdown-item menu-select" action="incoming-payment">
                    Email Tax Statment to people
                </a>
                <hr class="dropdown-divider">
                <a class="dropdown-item menu-select" action="fi-report">
                Financial reporting
                </a>
               
                <!--
                    <a class="dropdown-item menu-select" action="">
                        Ledger
                    </a>
                -->
            </div>
        </div>
    </div>
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

<?php 
/*
<div id="BookingReportList-section" class="report-section" style="display:none">
    <div class="column no-margin no-padding">
        <div class="column no-margin no-padding" style="padding-bottom:6px">
            <a class="button is-primary eReporting" action="booking-list">Get Booking Report</a>
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
            <h1 class="title is-4">Account balance</h1>
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

    <div id="accounts-balance-report-list" style="height:600px" ></div>
</div>

    <!--
    <div class="column no-margin no-padding">
        <div class="column no-margin no-padding" style="padding-bottom:6px">
            <a class="button is-primary eReporting" action="accounts-balance-list">Get Accounts balance</a>
            <a class="button is-primary eReporting" action="accounts-balance-print">Print</a>
        </div>
    </div>
    <form class="form-inline">
        <div class="form">
              <label for="to_date">To date: </label>
              <input type="text" class="input" id="to-date-accounts-balance" style="width:110px; padding: 2px 4px; margin-left: 8px" value="2018-11-27">

        </div>
    </form>
    <div id="accounts-balance-report-list" style="height:600px" ></div>
</div>
-->
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
*/