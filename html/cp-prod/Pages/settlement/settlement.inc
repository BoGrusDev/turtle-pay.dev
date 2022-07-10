<div id="settlement-section" class="settlement-section">
    <div id="dd-menu" class="dropdown is-active">
        <div class="dropdown-menu" id="dropdown-menu" role="menu">
            <div class="dropdown-content has-background-light">
                <a href="" class="dropdown-item menu-select" action="report-settlement-summary" >
                    Summary
                </a>
                <a href="" class="dropdown-item menu-select" action="" >
                    Latest
                </a>
                <a class="dropdown-item menu-select" action="report-settlement-people">
                    Report settlement people
                </a>

                <hr class="dropdown-divider">
                
                <a href="" class="dropdown-item menu-select" action="settlement-admin">
                    Settlement adminitration
                </a>
                <?php /*
                <a class="dropdown-item menu-select" action="incoming-payment">
                    Pre-settlement people
                </a>
                <hr class="dropdown-divider">
                <a class="dropdown-item menu-select" action="create-monthly-billing">
                    Create monthly invoices people
                </a>
                <a class="dropdown-item menu-select" action="accounts-balance">
                    Settlement company
                </a>
                <a class="dropdown-item menu-select" action="trans" style="color:gray">
                    Report settlement company
                </a>
                */
                ?>
            </div>
        </div>
    </div>
</div>

<div id="report-settlement-people-section" class="settlement-section" style="display:none">
    <div class="d-flex justify-content-between flex-wrap flex-md-nowrap align-items-center pb-2 mb-3 border-bottom">
        <h1 class="title is-4 has-text-centered no-bottom" id="header-people-name">People Settlement</h1>

        <div class="columns">

            <div class="column">
                <span>Period: </span>
                <input type="text" class="input" id="report_settlement-people-period" style="width:100px; padding: 2px 4px; margin-left: 8px" value="201905">
            </div>

            <div class="column">
                <div class="buttons is-right">
                    <button class="button is-primary" id="ePeopleSettlementReport">Get report</button>
                </div>
            </div>
        </div>
    </div>
    <div id="settlement-people-list" class="" style="height:600px"></div>
</div>

<?php /*
<div id="create-monthly-billing-section" class="settlement-section" style="display:none">
    <div class="d-flex justify-content-between flex-wrap flex-md-nowrap align-items-center pb-2 mb-3 border-bottom">
        <h1 class="title is-4 has-text-centered no-bottom" id="header-people-name">People Settlement</h1>

        <div class="columns">

            <div class="column">
                <span>Period: </span>
                <input type="text" class="input" id="report_settlement-people-period" style="width:100px; padding: 2px 4px; margin-left: 8px" value="201905">
                <button class="button is-primary" id="eCreateMonthlyBilling">Create the invoices</button>
            </div>
        </div>
    </div>
    <div id="create-monthly-billing-list"></div>
</div>
*/
?>


<div id="report-settlement-summary-section" class="settlement-section" style="display:none">
    <div class="d-flex justify-content-between flex-wrap flex-md-nowrap align-items-center pb-2 mb-3 border-bottom">
        <h1 class="title is-4 has-text-centered no-bottom" id="header-people-name">Summary</h1>
    </div>
    <div id="settlement-summary-list" class="" style="height:600px"></div>
</div>


<div id="settlement-admin-section" class="settlement-section" style="display:none">
    <div id="payment-list" style="height:600px">
        <h1 class="title is-size-4">Settlement</h1>
        
        <div class="columns">
            <div class="column">
                <span>Period: </span>
                <div class="select is-primary">
                    <select id="eSettlementPeriod" class="is-primary">
                    </select>
                </div>
            </div>
        </div>
        <table class="table is-striped" style="width:720px" id="settlement-table">
            <tbody>
                <tr>
                    <th style="width: 300px; text-align: left">Part</th>
                    <th style="width: 80px; text-align: left"></th>
                    <th style="width: 60px; text-align: right"></th>
                    <th style="width: 120px;"></th>
                </tr>
                <tr>
                    <td>People settlement</td>
                    <td>Completed:</td>
                    <td style="width: 60px; text-align: center" id="counts-people-settlement"></td>
                    <td><a class="button is-small is-primary" id="eDoPeopleSettlement">Run</a></td>
                </tr>
                <tr>
                    <td>People pre-settlement</td>
                    <td>Planned:</td>
                    <td style="width: 60px; text-align: center" id="counts-pre-settlement"></td>
                    <td><a class="button is-small is-primary" id="eDoPreSettlement">Run</a></td>
                </tr>
                <tr>
                    <td>Create invoices</td>
                    <td>Created:</td>
                    <td style="width: 60px; text-align: center" id="counts-created-invoices"></td>
                    <td><a class="button is-small is-primary" id="eDoCreateInvoices">Run</a></td>
                </tr>
                <tr>
                    <td>Mailing invoices</td>
                    <td>Created:</td>
                    <td id="counts-email-sent"></td>
                    <td><a class="button is-small is-primary" id="eDoMailing">Run</a></td>
                </tr>
                <tr>
                    <td>Company settlment</td>
                    <td>Skapade:</td>
                    <td id="counts-company-settlement"></td>
                    <td><a class="button is-small is-primary" id="eDoCompanySettlment">Run</a></td>
                </tr>

            </tbody>
        </table>
        </div>