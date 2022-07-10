<div id="invoicelist-section">
    <div class="d-flex justify-content-between flex-wrap flex-md-nowrap align-items-center pb-2 mb-3 border-bottom">
        <h1 class="h2">Invoices</h1>
        <div class="btn-toolbar mb-2 mb-md-0">
            <div class="btn-group mr-2">
                <!--<button class="btn btn-sm btn-outline-secondary eClient" action="new"><span data-feather="plus"></span> New </button> -->
            </div>
        </div>
    </div>

    <div id="invoice-list" class="" style="height:600px"></div>
</div>


<div id="invoice-modal" class="modal ">
    <div class="modal-background"></div>
    <div class="modal-card">
        <header class="modal-card-head">
            <p class="modal-card-title">Faktura</p>
        </header>
        <section class="modal-card-body">
            <table class="table is-small">
                <tr><th>Date:</th><td id="invoiceModal-date"></td></tr>
                <tr><th>Duedate:</th><td id="invoiceModal-duedate"></td></tr>
                <tr><th>Name:</th><td id="invoiceModal-name"></td></tr>
                <tr><th>Company:</th><td id="invoiceModal-company_name"></td></tr>
                <tr><th>Store:</th><td id="invoiceModal-store_name"></td></tr>
                <tr><th>Total:</th><td id="invoiceModal-total"></td></tr>
            </table>
        </section>
        <footer class="modal-card-foot">
            <div class="buttons  is-right">
                <button class="button eInvoice" action="close">Cancel</button>
                <button id="eInvoicePost" class="button is-dark eInvoice" action="post">Mark as Posted</button>
                <button id="eInvoiceView" class="button is-primary eInvoice" action="view">View / Print</button>
            </div>
        </footer>
    </div>
</div>

<!--
<div class="modal fade" id="invoiceModal" tabindex="-1" role="dialog" aria-labelledby="invoiceModal" aria-hidden="true">
    <div class="modal-dialog">
        <div class="modal-content">
            <div class="modal-header">
                <h4 class="modal-title" id="InvoiceModalLabel">Invoice</h4>
                <button type="button" class="close" data-dismiss="modal" aria-label="Close">
                    <span aria-hidden="true">×</span>
                </button>
            </div>
            <div class="modal-body">
                <form id="invoice-form">

                    <table class="table table">
                        <tr><th>Date:</th><td id="invoiceModal-date"></td></tr>
                        <tr><th>Duedate:</th><td id="invoiceModal-duedate"></td></tr>
                        <tr><th>Name:</th><td id="invoiceModal-name"></td></tr>
                        <tr><th>Company:</th><td id="invoiceModal-company_name"></td></tr>
                        <tr><th>Store:</th><td id="invoiceModal-store_name"></td></tr>
                        <tr><th>Total:</th><td id="invoiceModal-total"></td></tr>
                    </table>


                </form>
            </div>
            <div class="modal-footer">
                <button type="button" class="btn btn-default" data-dismiss="modal">Cancel</button>
                <button id="eInvoiceView" type="button" class="btn btn-dark eInvoice" filename= "" action="view">View / Print</button>
                <button id="eInvoicePost" type="button" class="btn btn-primary eInvoice" filename= "" action="post">Mark as Posted</button>
            </div>
        </div>
    </div>
</div>
-->
