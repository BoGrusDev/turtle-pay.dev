<div id="invoice-service-menu" class="invoice-service-section">
    <div id="dd-menu" class="dropdown is-active">
        <div class="dropdown-menu" id="dropdown-menu" role="menu">
            <div class="dropdown-content has-background-light">
                <a href="" class="dropdown-item menu-select" action="overview-invoicing" >
                    Overview
                </a>
               
                <hr class="dropdown-divider">
                
                <a class="dropdown-item menu-select" action="event-email-pre" >
                    Email to send Today
                </a>
                <a class="dropdown-item menu-select" action="event-reminder-pre" >
                    Reminder to send Today
                </a>
                <a class="dropdown-item menu-select" action="event-send-log" >
                    Send Log
                </a>
                <hr class="dropdown-divider">
                <a class="dropdown-item menu-select" action="event-send-email" >
                    Send Invoice & Reminders
                </a>
                <hr class="dropdown-divider">
                <a class="dropdown-item menu-select" action="event-company-notify-pre" >
                   Company notification preview
                </a>
                <a class="dropdown-item menu-select" action="event-company-notify-send" >
                   Company notification send
                </a>

            </div>
        </div>
    </div>
</div>

<div id="invoice-service-overview" class="invoice-service-section" style="display:none">
    <div class="d-flex justify-content-between flex-wrap flex-md-nowrap align-items-center pb-2 mb-3 border-bottom">
        <h1 class="title is-4 has-text-centered no-bottom" id="header-people-name">Overview (Fakturautskick) </h1>

        <div class="columns">

            <div class="column">
                <p>Invoice event: </p>
                <select id="eInvoiceEventSelection">
                </select>
            </div>

            <div class="column">
                <p>Status: </p>
                <select id="eInvoiceEventItemStatusSelection">
                    <option value="0">Alla</option>
                    <option value="p">Draft</option>
                    <option selected value="a">Send</option>
                    <option value="s">Sent</option>
                    <option value="r">Reminder</option>
                    <option value="c">Collected</option>
                    <option value="x">Bounced</option>
                    <option value="d">Denied</option>
                </select>
            </div>
           
            <div class="column">
                <div class="buttons is-right">
                    <button class="button is-primary" id="eGetOverview">Get invoices</button>
                </div>
            </div>
            
        </div>
    </div>
    <div id="invoice-service-overview-list" class="" style="height:600px"></div>
</div>

<div id="invoice-service-event-email-pre" class="invoice-service-section" style="display:none">
    <div class="d-flex justify-content-between flex-wrap flex-md-nowrap align-items-center pb-2 mb-3 border-bottom">
        <h1 class="title is-4 has-text-centered no-bottom" id="header-people-name">Email to send Today</h1>
    </div>

    <?php /*
    <div class="column">
        <div class="buttons is-right">
            <button class="button is-primary" id="eGetOverview">Get invoices</button>
        </div>
    </div>
    */ ?>
    <div id="invoice-service-event-email-pre-list" class="" style="height:600px"></div>
</div>

<div id="invoice-service-event-reminder-pre" class="invoice-service-section" style="display:none">
    <div class="d-flex justify-content-between flex-wrap flex-md-nowrap align-items-center pb-2 mb-3 border-bottom">
        <h1 class="title is-4 has-text-centered no-bottom" id="header-people-name">Reminder to send Today</h1>
    </div>

    <?php /*
    <div class="column">
        <div class="buttons is-right">
            <button class="button is-primary" id="eGetOverview">Get invoices</button>
        </div>
    </div>
    */ ?>
    <div id="invoice-service-event-reminder-pre-list" class="" style="height:600px"></div>
</div>

<div id="invoice-service-event-send-log" class="invoice-service-section" style="display:none">
    <div class="d-flex justify-content-between flex-wrap flex-md-nowrap align-items-center pb-2 mb-3 border-bottom">
        <h1 class="title is-4 has-text-centered no-bottom" id="header-people-name">Log</h1>
    </div>
    <div class="columns">
        <form class="form-inline">
            <div class="form" style="display:none">
                <label for="from_date">From date: </label>
                <input type="date" class="input" id="from-date-log" style=" width:160px;" value="2019-09-01">
                <label for="to_date" style="margin-left:14px">To date: </label>
                <input type="date" class="input" id="to-date-log" style="width:160px; margin-left: 8px" value="2018-09-27">

            </div>
        </form>
  
        <div class="column">
            <div class="buttons is-right">
                <button class="button is-primary" id="eGetEventSendLog">Get Logg</button>
            </div>
        </div>
    </div>

    <div id="invoice-service-event-send-log-list" class="" style="height:600px"></div>
</div>

<div id="invoice-service-event-send-email" class="invoice-service-section" style="display:none">
    <div class="d-flex justify-content-between flex-wrap flex-md-nowrap align-items-center pb-2 mb-3 border-bottom">
        <h1 class="title is-4 has-text-centered no-bottom" id="header-people-name">Send Invoice & Reminders</h1>
    </div>
    
    <div class="columns">   
        <div class="column">
            <div class="buttons">
                <button class="button is-primary" id="eSendEmail">Send Email</button>
                <button class="button is-info" id="eSendReminder">Send Reminder</button>
                <?php /* <button class="button is-dark" id="eUpdateNames">Updates Names</button> */ ?>

            </div>
        </div>
    </div>

    <div id="invoice-service-event-send-email-result" class="" style="height:600px"></div>
</div>

<div id="item-edit-modal" class="modal">
  <div class="modal-background"></div>
  <div class="modal-card">

    <header class="modal-card-head">
      <p class="modal-card-title">Set Denied</p>
    </header>

    <section class="modal-card-body">
        <label style="font-weight: bold">Email: </label>
        <input type="text" id="item-edit-modal-email" disabled class="input" style="border:0;">
        <br><br>
    </section>
    <footer class="modal-card-foot">
       <button class="button" id="eItemEditModalClose">Cancel</button>
       <button class="button is-primary" id="eItemEditModalUpdate">Set Denied</button>
    </footer>
  </div>
</div>

<div id="company-notify-pre" class="invoice-service-section" style="display:none">
    <div class="d-flex justify-content-between flex-wrap flex-md-nowrap align-items-center pb-2 mb-3 border-bottom">
        <h1 class="title is-4 no-bottom" id="header-people-name">Company notify preview</h1>
    </div>
    <div id="company-notify-pre-list"> </div>
</div>


<div id="company-notify-send" class="invoice-service-section" style="display:none">
    <div class="d-flex justify-content-between flex-wrap flex-md-nowrap align-items-center pb-2 mb-3 border-bottom">
        <h1 class="title is-4 no-bottom" id="header-people-name">Company notify sent</h1>
    </div>
    <!-- <button class="button is-primary large">Skicka</button> -->
    <div id="company-notify-send-list"> </div>
</div>