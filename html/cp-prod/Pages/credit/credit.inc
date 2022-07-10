<div id="creditlist-section">
    <div class="columns">
        <div class="column">
            <label class="checkbox">
                <input type="checkbox" id="eCurrent">
                Current
            </label>
        </div>
        <div class="column">
            <div class="buttons is-right">
                <div style="width:140px">Total: <span id="credit-sum"></span></div>
                <div class="select">
                    <select id="eSelectStatus">
                        <option value="">-- Select --</option>
                        <option value="0">All (active)</option>
                        <option value="p">Pending</option>
                        <option value="a">Activated</option>
                        <option value="o">Ongoing</option>
                        <option value="r">Refund (total)</option>
                        <option value="c">Completed</option>
                    </select>
                </div>
            </div>
        </div>
    </div>

    <div class="columns">
        <div class="column is-two-thirds">
            <div id="credit-list" class="" style="height:600px"></div>
        </div>
        <div class="column">
            <div id="trans-list" class="" style="height:600px"></div>
        </div>
    </div>

</div>

<div id="credit-section" style="display:none">
    <div class="d-flex justify-content-between flex-wrap flex-md-nowrap align-items-center pb-2 mb-2 border-bottom">
        <h1 id="header-name" class="header">Credit</h1>
        <div class="btn-toolbar mb-2 mb-md-0">
            <div class="btn-group mr-2">
                <a id="button-first-invoice" target="_blank" class="btn btn-sm btn-outline-secondary">First Invoice</a>
                <button class="btn btn-sm btn-outline-secondary eCredit" action="update">Spara</button>
                <button class="btn btn-sm btn-outline-secondary eCredit" action="back">Back</button>
            </div>
      </div>
    </div>
    <div class="row">
        <div class="col-6">
            <div class="row">
                <div class="col-12">
                    <form id="credit-form" class="needs-validation" novalidate>
                    <table class="table table-sm">
                        <tr>
                            <th>Credit-ID:</th>
                            <td>
                                <input class="tp-input w-100" disabled type="text" name="credit_id">
                            </td>
                        </tr>
                        <tr>
                            <th>Date:</th>
                            <td>
                                <input class="tp-input w-100" disabled type="text" name="start_date">
                            <td>
                        </tr>
                        <tr>
                            <th>Personal ID:</th>
                            <td>
                                <input class="tp-input w-100" disabled type="text" name="personal_id_number">
                            </td>
                        </tr>
                        <tr>
                            <th>Name:</th>
                            <td>
                                <input class="tp-input w-100" disabled type="text" name="personname">
                            </td>
                        </tr>

                        <tr>
                            <th>Amount:</th>
                            <td>
                                <input class="tp-input w-100" disabled type="text" name="amount">
                            </td>
                        </tr>
                        <tr>
                            <th>Company:</th>
                            <td>
                                <input class="tp-input w-100" disabled type="text" name="company_name">
                            <td>
                        </tr>
                        <tr>
                            <th>Store:</th>
                            <td>
                                <input class="tp-input w-100" disabled type="text" name="store_name">
                            <td>
                        </tr>
                        <tr>
                            <th>Salesperson:</th>
                            <td>
                                <input class="tp-input w-100" disabled type="text" name="salesperson">
                            <td>
                        </tr>
                        <tr>
                            <th>Receipt number:</th>
                            <td>
                                <input class="tp-input w-100" disabled type="text" name="receipt_number">
                            <td>
                        </tr>
                        <tr>
                            <th>OCR-no:</th>
                            <td>
                                <input class="tp-input w-100" disabled  type="text" name="first_invoice_ocrno">
                            </td>
                        </tr>
                        <tr>
                            <th>Invoice posted:</th>
                            <td>
                                <div class="form-check-inline">
                                    <input id="input-first_invoice_sent" type="checkbox" class="form-check-input" >
                                </div>
                            </td>
                        </tr>
                        <tr>
                            <th>Invoice emailed:</th>
                            <td>
                                <div class="form-check-inline">
                                    <input id="input-first_invoice_email_sent" type="checkbox" class="form-check-input" >
                                </div>
                            </td>
                        </tr>
                        <tr>
                            <th>Emailed to:</th>
                            <td>
                                <input id="input-first_invoice_email_account" class="tp-input w-100" type="text" name="first_invoice_email_account">
                            </td>
                        </tr>
                        <tr>
                            <th>Credit activated:</th>
                            <td>
                                <div class="form-check-inline">
                                    <input id="input-started" type="checkbox" class="form-check-input" name="started">
                                </div>
                            </td>
                        </tr>
                        <tr>
                            <th>Credit completed:</th>
                            <td>
                                <div class="form-check-inline">
                                    <input id="input-completed" type="checkbox" class="form-check-input" >
                                </div>
                            </td>
                        </tr>

                    </table>
                </form>
                </div>
            </div>
            <div class="row" style="display: none">
                <div class="col-12">
                    <hr>
                    <h3>Förfrågningar</h3>
                    <div id="people-request-list" style="height:300px"></div>
                </div>
            </div>
        </div>
        <div class="col-6" style="backgroud-color=#dddddd; display:none">
            <div class="col-12">
                <h3>Transaction</h3>
                <div id="trans-list" class="" style="height:600px"></div>
            </div>
        </div>
    </div>
</div>
