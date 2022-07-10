<div id="peoplelist-section">
    <div class="columns">
        <div class="column">
            <div class="buttons is-right">
                <a class="button is-primary eCompany" disabled action="new-company">New person</a>
            </div>
        </div>
    </div>
    <div id="people-list" style="height:600px" ></div>
</div>

<div id="people-section" style="display:none;">

    <h1 class="title is-4 has-text-centered no-bottom" id="header-people-name"></h1>

    <div id="people-tab" class="tabs is-boxed is-size-6 is-primary">
        <ul>
            <li id="tab-people-details" onclick="tabDetails()" class="tabs-people is-active"><a><span>Details</span></a></li>
            <li onclick="tabCredits()" class="tabs-people"><a><span>Credits</span></a></li>
            <li onclick="tabBond()" class="tabs-people"><a><span>Bond</span></a></li>
            <li id="tab-people-trans" onclick="tabTrans()" class="tabs-people"><a><span>Transactions</span></a></li>
            <li id="tab-people-invoices" onclick="tabInvoices()" class="tabs-people"><a><span>Invoices</span></a></li>
            <li id="tab-people-tp"  onclick="tabTp()" class="tabs-people" style="display:none"><a><span>Turtle App</span></a></li>
            <!-- <li id="tab-company-payments" onclick="tabTp()" class="tabs-company"><a><span>Payments</span></a></li>
            <li id="tab-company-reporting" onclick="tabTp()" class="tabs-company"><a><span>Reporting</span></a></li> -->
        </ul>
    </div>

    <div id="tab-details" class="people-tabs">
        <div class="columns">
            <div class="column">
                <div class="buttons  is-right">
                    <a id="eSparGet" class="button">Get SPAR</a>
                    <a id="eUcOpen" class="button is-danger">Get UC</a>
                    <a id="eUcDetails" class="button">UC detail</a>
                    <a id="ePeopleEdit" class="button is-dark ePeople" action="edit-people">Edit Information</a>
                   
                    <a id="ePeopleCancel" class="button is-light ePeople" action="cancel-people" style="display:none">Cancel </a>
                    <a id="ePeopleSave" class="button is-primary" style="display:none">Save Person</a>
                    <a id="eSettingsEdit" class="button is-dark ePeople" action="edit-settings">Edit settings</a>
                    <a id="eSettingsCancel" class="button is-light ePeople" action="cancel-settings" style="display:none">Cancel </a>
                    <a id="eSettingsSave" class="button is-primary ePeople" action="save-settings" style="display:none">Save Settings</a>

                </div>
            </div>
        </div>
        <div class="columns">
            <div class="column" style="padding-top: 0">
                <h2 class="title is-6 has-text-centered no-bottom has-background-primary has-text-white">Information</h2>
                <form id="people-form">
                    <?php
                        echo FormItemCreate('Name',null,'people-name', 'w-large');
                        echo FormItemCreate('Personal ID','personal_id_number','personal_id_number', 'w-medium');
                        echo FormItemCreate('Address','address','address', 'w-large');
                        echo FormItemCreate('Postcode','postcode','postcode', 'w-small');
                        echo FormItemCreate('City','city','city', 'w-large');
                        echo FormItemCreate('E-mail','email',null, 'w-large', "", false);
                        echo FormItemCreate('Mobile','mobile',null, 'w-large', "", false);
                        echo FormItemCreate('Gender','gender','gender', 'w-74', "", false);
                        echo FormItemCreate('Ocrno.','ocrno',null, 'w-large', "", false);
                        echo FormItemCreate('Overdues','overdue',null, 'w-74', "", false);
                        echo FormItemCreate('Clearingno.','clearing_no',null, 'w-small', "", false);
                        echo FormItemCreate('Bank account','bank_account',null, 'w-small', "", false);
                        echo FormItemCreate('ID','people_id',null, 'w-74', "", false);
                        // -- New 
                        echo FormItemCreate('UC taken','has_uc_check',null, 'w-74', "", false);
                        echo FormItemCreate('UC date','uc_date',null, 'w-74', "", false);
                        echo FormItemCreate('UC credit status','credit_status',null, 'w-74', "", false);
                        echo FormItemCreate('UC credit limit','credit_limit',null, 'w-74', "", false);
                        echo FormItemCreate('UC income','income',null, 'w-74', "", false);
                        
                        echo FormItemCreate('Lats updated','created_date',null, 'w-medium');
                    ?>
                
                    <div class="field is-horizontal">
                        <div class="field-label is-small">
                            <label class="label is-small has-text-black-ter">Status:</label>
                        </div>
                        <div class="field-body">
                            <div class="field">
                                <div class="control">
                                    <div class="select is-primary is-small">
                                        <select id="edit-people_status" name="people_status" class="is-primary is-small">
                                            <option value="p">Normal</option>
                                            <option value="b">Blocked</option>
                                        </select>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </div>


              </form>
            </div>

            <div class="column" style="padding-top: 0">
                <h2 class="title is-6 has-text-centered no-bottom has-background-primary has-text-white">Settings</h2>
                <div class="columns">
                    <div class="column">
                        <form id="settings-form" class="needs-validation" novalidate>
                            <?php
                                 echo FormItemCreate('Monthly invoice due days','monthly_invoice_due_days', null, 'w-74','label-settings');
                                 echo FormItemCreate('Monthly invoice due day','monthly_invoice_due_day', null, 'w-74','label-settings');
                                 echo FormItemCreate('Monthly settlement day','monthly_settlement_day', null, 'w-74','label-settings');
                                 echo FormItemCreate('Monthly invoice fee (kr)','monthly_invoice_fee', null, 'w-74','label-settings');
                                 echo FormItemCreate('Customer overdue interest margin (%)','due_interest_margin', null, 'w-74','label-settings');
                                 echo FormItemCreate('Reminder fee (kr)','reminder_fee', null, 'w-74','label-settings');
                                 echo FormItemCreate('Collection fee (kr)','collection_fee', null, 'w-74','label-settings');
                                 echo FormItemCreate('Customer credit limit (kr)','customer_credit_limit"', null, 'w-74','label-settings');
                                /*
                                echo FormItemCreate('Monthly invoice due days','monthly_invoice_due_days', null, 'w-74','label-settings');
                                echo FormItemCreate('Monthly invoice due day','monthly_invoice_due_day', null, 'w-74','label-settings');
                                echo FormItemCreate('Monthly settlement day','monthly_settlement_day', null, 'w-74','label-settings');
                                echo FormItemCreate('Monthly invoice fee (kr)','monthly_invoice_fee', null, 'w-74','label-settings');
                                echo FormItemCreate('Customer credit limit (kr)','customer_credit_limit"', null, 'w-74','label-settings');
                                // echo FormItemCreate('Customer UC limit (kr)','customer_uc_limit"', null, 'w-74','label-settings');
                                echo FormItemCreate('Customer overdue interest margin (%)','due_interest_margin', null, 'w-74','label-settings');
                                echo FormItemCreate('Reminder fee (kr)','reminder_fee', null, 'w-74','label-settings');
                                echo FormItemCreate('Collection fee (kr)','collection_fee', null, 'w-74','label-settings');
                                */

                          ?>
                        </form>
                    </div>

                     <div class="column">
                         <form id="settings-global-form" class="needs-validation" novalidate>
                            <?php
                                  echo FormItemCreate('','monthly_invoice_due_days', null, 'w-74','no-label');
                                  echo FormItemCreate('','monthly_invoice_due_day', null, 'w-74','no-label');
                                  echo FormItemCreate('','monthly_settlement_day', null, 'w-74','no-label');
                                  echo FormItemCreate('','monthly_invoice_fee', null, 'w-74','no-label');
                                  echo FormItemCreate('','due_interest_margin', null, 'w-74','no-label');
                                  echo FormItemCreate('reminder_fee', '', null, 'w-74','no-label');
                                  echo FormItemCreate('','collection_fee', null, 'w-74','no-label');
                                  
                                /*
                                echo FormItemCreate('','monthly_invoice_due_days', null, 'w-74','no-label');
                                echo FormItemCreate('','monthly_invoice_due_day', null, 'w-74','no-label');
                                echo FormItemCreate('','monthly_settlement_day', null, 'w-74','no-label');
                                echo FormItemCreate('','monthly_invoice_fee', null, 'w-74','no-label');
                                echo FormItemCreate('','customer_credit_limit"', null, 'w-74','no-label');
                                //echo FormItemCreate('','customer_uc_limit"', null, 'w-74','no-label');
                                echo FormItemCreate('','due_interest_margin', null, 'w-74','no-label');
                                echo FormItemCreate('reminder_fee', '', null, 'w-74','no-label');
                                echo FormItemCreate('','collection_fee', null, 'w-74','no-label');
                                */
                          ?>

                          </form>
                      </div>
                  </div>
            </div>

            <div class="column" style="padding-top: 0">
                <h2 class="title is-6 has-text-centered no-bottom has-background-primary has-text-white">Customer Assessment</h2>


                <div class="columns">
                    <div class="column">
                        <div id="uc-list" style="height:500px;"></div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>

    <div id="tab-credits" class="people-tabs" style="display:none">
        <div class="columns">
            <div class="column is-7">
                <div id="credits-list"  class="column" style="height:600px"></div>
            </div>
            <div class="column is-5">
                <div id="credit-detail-list"  style="height:600px"></div>
            </div>

        </div>
    </div>


    <div id="tab-bond" class="people-tabs" style="display:none">
        <div class="columns">
            <div class="column">
                <div id="bond-list"  class="column" style="height:600px"></div>
            </div>
            <div class="column">
                <div id="bond-detail-list"  class="column" style="height:600px"></div>
            </div>
        </div>
    </div>



    <div id="tab-invoices" class="people-tabs" style="display:none">
        <div class="columns">
            <div class="column">
                <div id="invoice-list"  class="column" style="height:600px"></div>

            </div>
        </div>
    </div>

    <div id="tab-trans" class="people-tabs" style="height:600px; display:none">
    <div class="columns">
            <div class="column">
                <div class="buttons  is-right">
                    <div class="select is-primary">
                        <select id="eSelectPeopleAction" class="is-primary">
                            <option value="0">-- Action --</option>
                            <option value="write-off">Write-off</option>
                            <option value="payout">Payout</option>
                        </select>
                    </div>
                </div>
            </div>   
        </div>   
           
        <div id="trans-list" style="height:600px"></div>
        
    </div>

    <div id="tab-tp" class="people-tabs" style="display:none">
        <div class="columns">
            <div class="column">
                <div class="buttons  is-right">
                    <a id="ePeopleEdit" class="button is-dark" disabled>Edit</a>
                </div>
            </div>
        </div>
        <div class="columns">
            <div class="column" style="padding-top: 0">
                <h2 class="title is-6 has-text-centered no-bottom has-background-primary has-text-white">Information</h2>
                <div id="people-info-company-connections"></div>
            </div>

            <div class="column" style="padding-top: 0">
                <h2 class="title is-6 has-text-centered no-bottom has-background-primary has-text-white">Bonus</h2>
            </div>

            <div class="column" style="padding-top: 0">
                <h2 class="title is-6 has-text-centered no-bottom has-background-primary has-text-white">Extra</h2>
            </div>
        </div>
    </div>

</div>

<?php
    // NEW 2020-02-06
?>


<div id="spar-modal" class="modal ">
  <div class="modal-background"></div>
  <div class="modal-card">

    <header class="modal-card-head">
      <p id = "titleRebookModal" class="modal-card-title">Get Spar</p>
    </header>

    <section class="modal-card-body">
        <div class="columns">
            <div class="column column-tight">
                <div class="field">
                    <label class="label is-small">Personal id number</label>
                    <div class="control">
                        <input id="spar-personal-id-number" disabled class="input amount" type="text" >
                    </div>
                </div>
            </div>

            <div class="column column-tight">
                <div class="field">
                    <label class="label is-small">Firstname</label>
                    <div class="control">
                        <input id="spar-people-first-name-current" disabled class="input people-name" type="text" >
                    </div>
                </div>
            </div>
            <div class="column column-tight">
                <div class="field">
                    <label class="label is-small">Lastname</label>
                    <div class="control">
                        <input id="spar-people-last-name-current" disabled class="input people-name" type="text" >
                    </div>
                </div>
            </div>
        </div>

        <div class="columns">
            <div class="column column-tight">
                <div class="field">
                    <label class="label is-small">Namn i SPAR</label>
                    <div class="control">
                    </div>
                </div>
            </div>

            <div class="column column-tight">
                <div class="field">
                    <label class="label is-small">Firstname</label>
                    <div class="control">
                        <input id="spar-people-first-name" disabled class="input people-name" type="text" >
                    </div>
                </div>
            </div>
            <div class="column column-tight">
                <div class="field">
                    <label class="label is-small">Lastname</label>
                    <div class="control">
                        <input id="spar-people-last-name" disabled class="input people-name" type="text" >
                    </div>
                </div>
            </div>
        </div>


        <div class="columns">        
            <div class="column column-tight">
                <div class="field">
                    <label class="label is-small">Ny address</label>
                    <div class="control">
                        <input id="spar-address" disabled class="input address" type="text" >
                    </div>
                </div>
            </div>
            <div class="column column-tight">
                <div class="field">
                    <label class="label is-small">Postcode</label>
                    <div class="control">
                        <input id="spar-postcode" disabled class="input postcode" type="text" >
                    </div>
                </div>
            </div>
            <div class="column column-tight">
                <div class="field">
                    <label class="label is-small">City</label>
                    <div class="control">
                        <input id="spar-city" disabled class="input city" type="text" >
                    </div>
                </div>
            </div>
            <div class="column column-tight">
                <div class="field">
                    <label class="label is-small">Gender</label>
                    <div class="control">
                        <input id="spar-gender" disabled class="input postcode" type="text" >
                    </div>
                </div>
            </div>
        </div>
    </section>

    <footer class="modal-card-foot">
       <button class="button is-default" id="eCloseSpar">Cancel</button>
       <button class="button is-primary" id = "eDoSpar" action="">Get from SPAR</button>
       <button class="button is-primary" id = "eSaveSpar" action="">Save new address</button>
    </footer>
  </div>
</div>

<div id="uc-modal" class="modal ">
  <div class="modal-background"></div>
  <div class="modal-card">

    <header class="modal-card-head">
      <p id = "titleRebookModal" class="modal-card-title">Get UC</p>
    </header>

    <section class="modal-card-body">
        <div class="columns">
            <div class="column column-tight">
                <div class="field">
                    <label class="label is-small">Personal id number</label>
                    <div class="control">
                        <input id="uc-personal-id-number" disabled class="input amount" type="text" >
                    </div>
                </div>
            </div>

            <div class="column column-tight">
                <div class="field">
                    <label class="label is-small">Name</label>
                    <div class="control">
                        <input id="uc-people-name" disabled class="input people-name" type="text" >
                    </div>
                </div>
            </div>
        </div>

    </section>

    <footer class="modal-card-foot">
       <button class="button is-default" id="eCloseUc">Cancel</button>
       <button class="button is-danger" id = "eDoTheRealUc" action="">Get a UC from Upplysnings Centralen</button>
       
    </footer>
  </div>
</div>


<div id="rebook-pre-modal" class="modal ">
    <div class="modal-background"></div>
        <div class="modal-card">
            <header class="modal-card-head">
                <p class="modal-card-title">Update Pre Booking</p>
            </header>

            <section class="modal-card-body">

                <div class="columns">
                    <div class="column column-tight">
                        <div class="field">
                            <label class="label is-small">Transaction-type</label>
                            <div class="control">
                                <p id="pre-trans-type"></p>
                            </div>
                        </div>
                    </div>
                </div>
                   
                <div class="columns">
                    <div class="column column-tight">
                        <div class="field">
                            <label class="label is-small">Amount</label>
                            <div class="control">
                                <input id="pre-amount" class="input amount" type="text" maxlength="8" >
                            </div>
                        </div>
                    </div>
                </div>
            </section>

            <footer class="modal-card-foot">
                 <button class="button is-default" id="eCloseRebookPre">Cancel</button>
                <button class="button is-primary" id = "eDoRebookPre" action="">Update Pre Booking</button>
            </footer>
        </div>
    </div>
</div>

<div id="payout-modal" class="modal ">
    <div class="modal-background"></div>
        <div class="modal-card">
            <header class="modal-card-head">
                <p class="modal-card-title">Payout</p>
            </header>

            <section class="modal-card-body">
                <div class="columns">
                    <div class="column">
                        <label class="label is-small">Date</label>
                        <div class="control">
                            <input type="date" class="form-control" id="payout-date" style="width:250px;font-size:16px">
                        </div>
                    </div>

                    <div class="column">
                        <label class="label is-small">Amount</label>
                        <div class="control">
                            <input id="payout-amount" class="input amount is-numeric-comma" type="text" maxlength="8" >
                        </div>
                    </div>
                </div>
            </section>

            <footer class="modal-card-foot">
                 <button class="button is-default" id="eClosePayout">Cancel</button>
                <button class="button is-primary" id = "eDoPayout" action="">Payout</button>
            </footer>
        </div>
    </div>
</div>

<div id="crediting-cancel-modal" class="modal ">
    <div class="modal-background"></div>
        <div class="modal-card">
            <header class="modal-card-head">
                <p class="modal-card-title">Cancel Crediting</p>
            </header>
            <section class="modal-card-body">
            </section>
            <footer class="modal-card-foot">
                 <button class="button is-default" id="eCloseCreditingCancel">Cancel</button>
                <button class="button is-primary" id = "eDoCreditingCancel" action="">Cancel Crediting</button>
            </footer>
        </div>
    </div>
</div>

<div id="rebook-modal" class="modal ">
  <div class="modal-background"></div>
  <div class="modal-card">

    <header class="modal-card-head">
      <p id = "titleRebookModal" class="modal-card-title">Rebooking</p>
    </header>

    <section class="modal-card-body">
        <div class="columns">
            <div class="column is-one-third">
                <div class="select">
                    <select id="selRebooking" disabled>
                        <option value="blank">(select)</option>
                        <option value="billing-fee">Billing fee</option>
                        <option value="reminder-fee">Reminder fee</option>
                        <option value="collection-fee">Collection fee</option>
                        <option value="payment">Payment</option>
                        <option value="duedate">Duedate</option>
                    </select>
                </div>
            </div>
            <div class="column">
                <div class="rebook-body" id="rebook-body-fee">
                    <h3 id="rebook-title" class="title is-4"</h3>
                    <div class="columns">
                        <div class="column column-tight">
                            <div class="field">
                               <label class="label is-small">Current date</label>
                               <div class="control">
                                   <input id="current_date" disabled class="input amount" type="text" maxlength="12" >
                               </div>
                           </div>
                       </div>
                        <div class="column column-tight">
                            <div class="field">
                               <label class="label is-small">Current fee</label>
                               <div class="control">
                                   <input id="current_fee" disabled class="input amount" type="text" maxlength="8" >
                               </div>
                           </div>
                       </div>
                   </div>
                   <div class="columns">
                       <div class="column column-tight">
                           <div class="field">
                              <label class="label is-small">New date</label>
                              <div class="control">
                                  <input id="new_date"  class="input amount" type="text" maxlength="12" >
                              </div>
                          </div>
                      </div>
                       <div class="column column-tight">
                           <div class="field">
                              <label class="label is-small">New billing fee</label>
                              <div class="control">
                                  <input id="new_fee" class="input amount" type="text" >
                              </div>
                          </div>
                      </div>
                  </div>

            </div>
        </div>
    </section>

    <footer class="modal-card-foot">
       <button class="button is-default" id="eCloseRebook">Cancel</button>
       <button class="button is-primary" id = "eDoRebook" action="">Book</button>
    </footer>
  </div>
</div>

<div id="credit-amor-modal" class="modal ">
    <div class="modal-background"></div>
        <div class="modal-card">
            <header class="modal-card-head">
                <p class="modal-card-title">Credit Amortization</p>
            </header>
            <section class="modal-card-body">
                <div class="columns">
                    <div class="column column-tight">
                        <div class="field">
                            <label class="label is-small">Credit ID</label>
                            <div class="control">
                                <input id="amor-credit-id" disabled class="input amount" type="text" maxlength="20" >
                            </div>
                        </div>
                    </div>
                    <div class="column column-tight">
                        <div class="field">
                            <label class="label is-small">Amount</label>
                            <div class="control">
                                <input id="amor-credit-amount" class="input amount" type="text" maxlength="20" >
                            </div>
                        </div>
                    </div>
                    <div class="column column-tight">
                        <div class="field">
                            <label class="label is-small">Date</label>
                            <div class="control">
                                <input id="credit-amor-date"  class="input amount" type="text" maxlength="12" >
                            </div>
                        </div>
                    </div>
                </div>
            </section>
            <footer class="modal-card-foot">
                 <button class="button is-default" id="eCloseCreditAmor">Cancel</button>
                <button class="button is-primary" id = "eDoCreditAmor" action="">Credit Amortization</button>
            </footer>
        </div>
    </div>
</div>

<div id="credit-interest-modal" class="modal ">
    <div class="modal-background"></div>
        <div class="modal-card">
            <header class="modal-card-head">
                <p class="modal-card-title">Crediting Interest</p>
            </header>
            <section class="modal-card-body">
                <div class="columns">
                    <div class="column column-tight">
                        <div class="field">
                            <label class="label is-small">Credit ID</label>
                            <div class="control">
                                <input id="interest-credit-id" disabled class="input amount" type="text" maxlength="20" >
                            </div>
                        </div>
                    </div>
                    <div class="column column-tight">
                        <div class="field">
                            <label class="label is-small">Amount</label>
                            <div class="control">
                                <input id="interest-credit-amount" class="input amount" type="text" maxlength="20" >
                            </div>
                        </div>
                    </div>
                    <div class="column column-tight">
                        <div class="field">
                            <label class="label is-small">Date</label>
                            <div class="control">
                                <input id="interest-credit-date"  class="input amount" type="text" maxlength="12" >
                            </div>
                        </div>
                    </div>
                </div>
            </section>
            <footer class="modal-card-foot">
                 <button class="button is-default" id="eCloseCreditInterest">Cancel</button>
                <button class="button is-primary" id = "eDoCreditInterest" action="">Credit Interest</button>
            </footer>
        </div>
    </div>
</div>

<div id="credit-ointerest-modal" class="modal ">
    <div class="modal-background"></div>
        <div class="modal-card">
            <header class="modal-card-head">
                <p class="modal-card-title">Crediting O-interest</p>
            </header>
            <section class="modal-card-body">
                <div class="columns">
                    <div class="column column-tight">
                        <div class="field">
                            <label class="label is-small">Amount</label>
                            <div class="control">
                                <input id="ointerest-credit-amount" class="input amount" type="text" maxlength="20" >
                            </div>
                        </div>
                    </div>
                    <div class="column column-tight">
                        <div class="field">
                            <label class="label is-small">Date</label>
                            <div class="control">
                                <input id="ointerest-credit-date"  class="input amount" type="text" maxlength="12" >
                            </div>
                        </div>
                    </div>
                </div>
            </section>
            <footer class="modal-card-foot">
                 <button class="button is-default" id="eCloseCreditOinterest">Cancel</button>
                <button class="button is-primary" id = "eDoCreditOinterest" action="">Credit O-interest</button>
            </footer>
        </div>
    </div>
</div>

<div id="credit-full-modal" class="modal ">
    <div class="modal-background"></div>
        <div class="modal-card">
            <header class="modal-card-head">
                <p class="modal-card-title">Crediting</p>
            </header>
            <section class="modal-card-body">
                <div class="columns">
                    <div class="column column-tight">
                        <div class="field">
                            <label class="label is-small">Credit ID</label>
                            <div class="control">
                                <input id="full-credit-id" disabled class="input amount" type="text" maxlength="20" >
                            </div>
                        </div>
                    </div>
                    <div class="column column-tight">
                        <div class="field">
                            <label class="label is-small">Amount</label>
                            <div class="control">
                                <input id="full-credit-amount" class="input amount" type="text" maxlength="20" >
                            </div>
                        </div>
                    </div>
                    <div class="column column-tight">
                        <div class="field">
                            <label class="label is-small">Date</label>
                            <div class="control">
                                <input id="full-credit-date"  class="input amount" type="text" maxlength="12" >
                            </div>
                        </div>
                    </div>
                </div>
				
				<?php // 20211101 */ ?>
                <div class="columns">
                    <div class="column column-tight">
                        <div class="field">
                            <label class="label is-small">Referens</label>
                            <div class="control">
                                <input id="full-receipt_number" style="width:260px" class="input" type="text" maxlength="30" >
                            </div>
                        </div>
                    </div>
                </div>
				
            </section>
            <footer class="modal-card-foot">
                 <button class="button is-default" id="eCloseCreditFull">Cancel</button>
                <button class="button is-primary" id = "eDoCreditFull" action="">Credit</button>
            </footer>
        </div>
    </div>
</div>

<div id="change-credit-status-modal" class="modal ">
    <div class="modal-background"></div>
        <div class="modal-card">
            <header class="modal-card-head">
                <p class="modal-card-title">Change Credit</p>
            </header>
            <section class="modal-card-body">
                <div class="columns">
                    <div class="column column-tight">
                        <div class="field">
                            <label class="label is-small">Credit ID</label>
                            <div class="control">
                                <input id="change-credit-status-id" disabled class="input amount" type="text" maxlength="20" >
                            </div>
                        </div>
                    </div>
                    <div class="column column-tight" style="display:none">
                        <div class="field">
                            <label class="label is-small">Status</label>
                            <div class="control">
                            
                                <div class="select is-primary is-small">
                                    <select id="change-credit-status" class="is-primary is-small">
                                        <option value="c">Closed</option>
                                        <option value="r">Return</option>
                                        <option value="p">Pending</option>
                                        <option value="a">Activated</option>
                                        <option value="o">Ongoing</option>
                                    </select>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>

                <div class="columns">
                    <div class="column column-tight">
                        <div class="field">
                            <label class="label is-small">Payment terms</label>
                            <div class="control">
                                <input id="change-monthly-no" class="input amount is-numeric" type="text" maxlength="3" style="width:60">
                            </div>
                        </div>
                    </div>
                    <div class="column column-tight">
                        <div class="field">
                            <label class="label is-small">Interest margin (%)</label>
                            <div class="control">
                                <input id="change-interest-margin" class="input amount is-numeric-comma" type="text" maxlength="5" style="width:60">
                            </div>
                        </div>
                    </div>
                </div>


            </section>
            <footer class="modal-card-foot">
                 <button class="button is-default" id="eCloseChangeCreditStatus">Cancel</button>
                <button class="button is-primary" id = "eDoChangeCreditStatus" action="">Change credit status</button>
            </footer>
        </div>
    </div>
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


<div id="uc-details-modal" class="modal ">
    <div class="modal-background"></div>
    <div class="modal-card" style="max-height:580px; height:580px; width:960px">
        <?php /*
        <header class="modal-card-head">
            <p class="modal-card-title">UC</p>
        </header>
        */ ?>
        <section class="modal-card-body" id="uc-details-body">
            
        </section>
        <footer class="modal-card-foot">
            <div class="buttons  is-right">
                <button id="eUclose" class="button" action="close">Close</button>
                <button id="eUcPrint" class="button is-primary" action="view">Print</button>
            </div>
        </footer>
    </div>
</div>


<div id="write-off-modal" class="modal ">
    <div class="modal-background"></div>
        <div class="modal-card">
            <header class="modal-card-head">
                <p class="modal-card-title">Write-off</p>
            </header>
            <section class="modal-card-body">
                <div class="columns">
                    <div id="write-off-body" class="column column-tight">  
                    </div>
                </div>
            </section>
            <footer class="modal-card-foot">
                 <button class="button is-default" id="eCloseWriteOff">Cancel</button>
                <button class="button is-primary" id = "eDoWriteOff" action="">Write off the depts</button>
            </footer>
        </div>
    </div>
</div>