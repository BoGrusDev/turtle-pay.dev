<?php
?>
<div id="payment-section">
    <div id="dd-menu" class="dropdown is-active">
        <div class="dropdown-trigger">
            <button class="button" id="dd-trigger" aria-haspopup="true" aria-controls="dropdown-menu">
                <span>Select report</span>
                <span class="icon is-small">
                    <i class="fas fa-angle-down" aria-hidden="true"></i>
                </span>
            </button>
        </div>
        <div class="dropdown-menu" id="dropdown-menu" role="menu">
            <div class="dropdown-content">
                <a href="" class="dropdown-item menu-select" action="outgoing">
                    Payment outgoing
                </a>
                <a class="dropdown-item menu-select" action="incomming">
                    Payment incomming
                </a>
                <a class="dropdown-item menu-select" action="incomming-file">
                    Payment incomming (file)
                </a>
            </div>
        </div>
    </div>
</div>

<div id="payment-outgoing-section" style="display:none">
    <div class="column no-margin no-padding">
        <div class="column no-margin no-padding" style="padding-bottom:6px">
            <a class="button is-primary ePayment" action="list">Get payment</a>
        </div>
    </div>
    <form class="form-inline">
        <div class="form-group mb-2">
              <label for="from_date">From date: </label>
              <input type="text" class="input" id="payment-date" style="width:96px; padding: 2px 4px; margin-left: 8px" value="2018-11-27">
        </div>
    </form>
    <div id="payment-list" style="height:600px" ></div>

</div>


<div id="payment-incomming-section" style="display:none">


    <form>
        <div style="margin-bottom:6px">
              <p>From date: </p>
              <input type="text" class="input" id="incomming-date" style="width:110px;" >
        </div>
        <div style="margin-bottom:6px">
              <p>OCR no:</p>
              <input type="text" class="input" id="incomming-ocrno" style="width:200px;" >
        </div>
        <div style="margin-bottom:20px"
              <p>Amount:</p>
              <input type="text" class="input" id="incomming-amount" style="width:120px;" >
        </div>
        <div style="margin-top:6px">
            <a class="button is-primary" id="do-incomming-payment">Book payment</a>
        </div>
    </form>

</div>

<div id="payment-incomming-file-section" style="display:none">
    <div class="column no-margin no-padding">
        <div class="column no-margin no-padding" style="padding-bottom:6px">
            <a class="button is-primary eUpploadTrigger _eLoadPaymentFile" action="list">Load payment file</a>
           
        </div>
       
    </div>
    <form class="form-inline">
            <input type="file" id="upload-file" name="file_name" style="visibility:hidden;" class="button-one file" required >
    </form>
    <div id="payment-file-list" style="height:600px"></div>

</div>
