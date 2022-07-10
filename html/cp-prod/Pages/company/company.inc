<div id="companylist-section">
    <div class="columns">
        <div class="column">
            <div class="buttons is-right">
                <a class="button is-primary eCompany" action="new-company">New company</a>
            </div>
        </div>
    </div>

    <div id="company-list" style="height:600px" ></div>
</div>

<div id="company-section" style="display:none;">

    <h1 class="title is-4 has-text-centered no-bottom" id="header-company-name"></h1>

    <div id="company-tab" class="tabs is-boxed is-size-6 is-primary">
        <ul>
            <li id="tab-company-details" onclick="tabDetails()" class="tabs-company is-active"><a><span>Details</span></a></li>
            <li onclick="tabCredits()"><a><span>Credits</span></a></li>
            <li id="tab-company-trans" onclick="tabTrans()" class="tabs-company"><a><span>Transactions</span></a></li>
            <li id="tab-company-tp" onclick="tabTp()" class="tabs-company"><a><span>Turtle App</span></a></li>
            <li id="tab-company-payments" onclick="tabTp()" class="tabs-company"><a><span>Payments</span></a></li>
            <li id="tab-company-reporting" onclick="tabTp()" class="tabs-company"><a><span>Reporting</span></a></li>
        </ul>
    </div>

<div id="tab-details" class="company-tabs ">
    <div class="columns">
        <div class="column">
            <div class="buttons  is-right">
                <a id="eCompanyEdit" class="button is-dark eCompany" action="edit-company">Edit Information</a>
                <a id="eCompanyCancel" class="button is-light eCompany" action="cancel-company" style="display:none">Cancel </a>
                <a id="eCompanySave" class="button is-primary" style="display:none">Save Company</a>

                <a id="eSettingsEdit" class="button is-dark eCompany" action="edit-settings">Edit settings</a>
                <a id="eSettingsCancel" class="button is-light eCompany" action="cancel-settings" style="display:none">Cancel </a>
                <a id="eSettingsSave" class="button is-primary eCompany" action="save-settings" style="display:none">Save Settings</a>

            </div>
        </div>
    </div>

    <div class="columns">
        <div class="column" style="padding-top: 0">
            <h2 class="title is-6 has-text-centered no-bottom has-background-primary has-text-white">Information</h2>
            <form id="company-form">
                <?php
                    echo FormItemCreate('Known as','known_as',null , 'w-large');
                    echo FormItemCreate('Company','company_name',null, 'w-large');
                    //echo FormItemCreate('Company id','company_id',null, 'w-medium');
                    echo FormItemCreate('Company regno.','company_id_number',null, 'w-medium');
                    echo FormItemCreate('Address','address',null, 'w-large');
                    echo FormItemCreate('','address_2',null, 'w-large','', false);
                    echo FormItemCreate('Postcode','postcode',null, 'w-small');
                    echo FormItemCreate('City','city',null, 'w-large');
                    echo FormItemCreate('E-mail','email',null, 'w-large');
                    echo FormItemCreate('E-report','email_report',null, 'w-large');
                    echo FormItemCreate('Invoice notify','noti_invoice_email',null, 'w-large');
                    echo FormItemCreate('Phone','phone',null, 'w-medium');
                    echo FormItemCreate('Bank account','bank_account',null, 'w-medium');
                    echo FormItemCreate('Huvudmän','real_principal',null, 'w-large', '', false);
                    echo FormItemCreate('Huvudmän pnr','real_principal_orgno',null, 'w-medium', '', false);
                    echo FormItemCreate('Website','website',null, 'w-medium','', false);
                    echo FormItemCreate('Web-faktura URL','wa_url',null, 'w-large');
                    ?>
                    <div class="field is-horizontal">
                        <div class="field-label is-small">
                            <label class="label is-small has-text-black-ter">Invoice service:</label>
                        </div>
                        <div class="field-body">
                            <div class="field">
                                <div class="control">
                                    <div class="select is-primary is-small">
                                        <select name="has_invoice_service" class="is-primary is-small">
                                            <option value="n">No</option>
                                            <option value="y">Yes</option>
                                        </select>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </div>

                    <div class="field is-horizontal">
                        <div class="field-label is-small">
                            <label class="label is-small has-text-black-ter">Webapp store:</label>
                        </div>
                        <div class="field-body">
                            <div class="field">
                                <div class="control">
                                    <div class="select is-primary w-large is-small">
                                        <select name="wa_store_id" id="wa_store_list" class="is-primary" style="width: 100%">
                                           
                                        </select>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </div>

                    <div class="field is-horizontal">
                        <div class="field-label is-small">
                            <label class="label is-small has-text-black-ter">Webapp saleperson:</label>
                        </div>
                        <div class="field-body">
                            <div class="field">
                                <div class="control">
                                    <div class="select is-primary w-large is-small">
                                        <select name="wa_sp_id" id="wa_sp_list" class="is-primary" style="width: 100%">
                                        </select>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </div>

                    <div class="field is-horizontal">
                        <div class="field-label is-small">
                            <label class="label is-small has-text-black-ter">Vendor:</label>
                        </div>
                        <div class="field-body">
                            <div class="field">
                                <div class="control">
                                    <div class="control">
                                        <div class="select is-primary is-small">
                                            <select name="is_vendor" class="is-primary is-small">
                                                <option value="n">No</option>
                                                <option value="y">Yes</option>
                                            </select>
                                        </div>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </div>

                    <div class="field is-horizontal">
                        <div class="field-label is-small">
                            <label class="label is-small has-text-black-ter">Lender:</label>
                        </div>
                        <div class="field-body">
                            <div class="field">
                                <div class="control">
                                    <div class="control">
                                        <div class="select is-primary is-small">
                                            <select name="is_lender" class="is-primary is-small">
                                                <option value="n">No</option>
                                                <option value="y">Yes</option>
                                            </select>
                                        </div>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </div>

                    <div class="field is-horizontal">
                        <div class="field-label is-small">
                            <label class="label is-small has-text-black-ter">Status:</label>
                        </div>
                        <div class="field-body">
                            <div class="field">
                                <div class="control">
                                    <div class="control">
                                        <div class="select is-primary is-small">
                                            <select name="company_status" class="is-primary is-small">
                                                <option value="p">Progress</option>
                                                <option value="a">Active</option>
                                                <option value="b">Blocked</option>
                                            </select>
                                        </div>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </div>

                    <div class="field is-horizontal">
                        <div class="field-label is-small">
                            <label class="label is-small has-text-black-ter">Privilege:</label>
                        </div>
                        <div class="field-body">
                            <div class="field">
                                <div class="control">
                                    <div class="select is-primary is-small">
                                        <select name="priv_on" class="is-primary is-small">
                                            <option value="n">No</option>
                                            <option value="y">Yes</option>
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
                        echo FormItemCreate('Company credit limit (kr):','company_credit_limit',null, 'w-74','label-settings');
                        echo FormItemCreate('Company UC limit (kr):','company_uc_limit',null, 'w-74','label-settings');
                        echo FormItemCreate('Customer UC limit (kr):','company_customer_limit',null, 'w-74','label-settings');

                        echo FormItemCreate('Company interest margin (%):','company_interest_margin', null, 'w-74','label-settings');
                        echo FormItemCreate('Company overdue interest margin (%):','company_overdue_interest_margin',null, 'w-74','label-settings');
                        echo FormItemCreate('Credit interest grace days:','credit_interest_grace_days',null, 'w-74','label-settings');
                       
                        echo FormItemCreate('Vendor fee (%)','vendor_fee', null, 'w-74','label-settings');
                        echo FormItemCreate('Sales person rebate (%)','sales_person_rebate', null, 'w-74','label-settings');
                        echo FormItemCreate('First invoice minimum (kr)','first_invoice_minimum', null, 'w-74','label-settings');
                        echo FormItemCreate('First invoice start fee (kr)','first_invoice_start_fee', null, 'w-74','label-settings');
                        echo FormItemCreate('First Invoice due days','first_Invoice_due_days', null, 'w-74','label-settings');
                        echo FormItemCreate('First invoice due days plus','first_invoice_due_days_plus', null, 'w-74','label-settings');

                        echo FormItemCreate('First invoice fee','first_invoice_fee', null, 'w-74','label-settings');
                        echo FormItemCreate('Administration fee (kr)','administration_fee', null, 'w-74','label-settings');
                        echo FormItemCreate('Repayment terms (month):','repayment_term',null, 'w-74','label-settings');
                        echo FormItemCreate('Repayment model:','repayment_model',null, 'w-74','label-settings');
                        echo FormItemCreate('Repayment overdue model','repayment_overdue_term', null, 'w-74','label-settings');
                        echo FormItemCreate('Repayment overdue terms','repayment_overdue_model', null, 'w-74','label-settings');
                        echo FormItemCreate('Customer interest margin (%)','customer_interest_margin', null, 'w-74','label-settings');
                        echo FormItemCreate('Effective interest rate (YTM):','effective_rate',null, 'w-74','label-settings');
						echo FormItemCreate('Effective total cost:','effective_total',null, 'w-74','label-settings');
                  ?>
                  </form>
              </div>
             <div class="column">
                 <form id="settings-global-form" class="needs-validation" novalidate>
                    <?php
                        echo FormItemCreate('','company_credit_limit',null, 'w-74','no-label');
                        echo FormItemCreate('','company_uc_limit',null, 'w-74','no-label');
                        echo FormItemCreate('','company_customer_limit',null, 'w-74','no-label');
                        echo FormItemCreate('','company_interest_margin', null, 'w-74','no-label');
                        echo FormItemCreate('','company_overdue_interest_margin',null, 'w-74','no-label');
                        echo FormItemCreate('','credit_interest_grace_days',null, 'w-74','no-label');
                        
                        echo FormItemCreate('','vendor_fee', null, 'w-74', 'no-label');
                        echo FormItemCreate('','sales_person_rebate', null, 'w-74','no-label');
                        echo FormItemCreate('','first_invoice_minimum', null, 'w-74','no-label');
                        echo FormItemCreate('','first_invoice_start_fee', null, 'w-74','no-label');
                        echo FormItemCreate('','first_Invoice_due_days', null, 'w-74','no-label');
                        echo FormItemCreate('','first_invoice_due_days_plus', null, 'w-74','no-label');

                        echo FormItemCreate('','first_invoice_fee', null, 'w-74','no-label');
                        echo FormItemCreate('','administration_fee', null, 'w-74','no-label');
                        echo FormItemCreate('','repayment_term',null, 'w-74','no-label');
                        echo FormItemCreate('','repayment_model',null, 'w-74','no-label');
                        echo FormItemCreate('','repayment_overdue_term', null, 'w-74','no-label');
                        echo FormItemCreate('','repayment_overdue_model', null, 'w-74','no-label');
                        echo FormItemCreate('','customer_interest_margin', null, 'w-74','no-label');
                        echo FormItemCreate('','effective_rate',null, 'w-74','no-label');
                  ?>
                  </form>
              </div>
          </div>
        </div>

        <div class="column" style="padding-top: 0">
            <h2 class="title is-6 has-text-centered no-bottom has-background-primary has-text-white">Information</h2>
                <div id="company-sign-info"></div>
        </div>
    </div>
</div>

<div id="tab-credits" class="company-tabs" style="display:none">
    <div id="credits-list"  class="column" style="height:600px"></div>
    <div id="credit-details"  class="column" style="height:600px">
        <h2>Credit</h2>
    </div>
</div>


<div id="tab-trans" class="company-tabs" style="display:none;" >
    <div>
        <div id="trans-list" style="height:600px"></div>
    </div>
</div>


</div>

<div id="people-modal" class="modal ">
  <div class="modal-background"></div>
  <div class="modal-card">

    <header class="modal-card-head">
      <p id="people-modal-title" class="modal-card-title"></p>
    </header>

    <section class="modal-card-body">
        <label>Personal Id Number: </label>
        <input type="text" id="people-modal-pesonal-id-number" class="input" style="width:160px">

        <div class="control" style="padding-top: 6px">
            <label class="radio">
                <input type="radio" checked name="priv" value="pe">
                Pending
            </label>
            <label class="radio">
                <input type="radio" name="priv" value="sp">
                Sales person
            </label>
            <label class="radio" >
                <input type="radio" name="priv" value="pr">
                Principal
            </label>
            <label class="radio" >
                <input type="radio" name="priv" value="su">
                Super user
            </label>
        </div>



    </section>
    <footer class="modal-card-foot">
       <button class="button is-small eCompany" action="people-modal-close">Cancel</button>
       <button id="people-modal-insert-button" class="button is-primary is-small eCompany" action="people-insert" style="display:none">Add people</button>
       <button id="people-modal-update-button" class="button is-primary is-small eCompany" action="people-update" style="display:none">Change privilege</button>
    </footer>
  </div>
</div>


<div id="tab-tp" class="company-tabs" >
    <div class="columns">
        <div class="column" style="padding-top: 0">
            <h2 class="title is-6 has-text-centered no-bottom has-background-primary has-text-white">Stores</h2>
            <div id="company-store-list" style="height:300px; width: 350px;"></div>
            <div class="column">
                <a class="button is-small is-outlined is-primary eCompany" action="add-store">Add store</a>
            </div>
        </div>

        <div class="column" style="padding-top: 0">
            <h2 class="title is-6 has-text-centered no-bottom has-background-primary has-text-white">People</h2>
             <div id="company-people-list" style="height:300px; width: 350px"></div>
             <div class="column">
                 <a class="button is-small is-outlined is-primary eCompany" action="add-people">Add people</a>
             </div>
        </div>

        <div class="column">
        </div>
    </div>
</div>

<div id="add-store-modal" class="modal ">
  <div class="modal-background"></div>
  <div class="modal-card">

    <header class="modal-card-head">
      <p class="modal-card-title">Add Store</p>
    </header>

    <section class="modal-card-body">
        <label>Store name: </label>
        <input type="text" id="store-add-name" class="input" >
        <br>
        <label>Location: </label>
        <input type="text" id="store-add-location" class="input" >
    </section>
    <footer class="modal-card-foot">
       <button class="button  is-small eCompany" action="store-modal-close">Cancel</button>
       <button class="button  is-primary is-small eCompany" action="store-insert">Add store</button>
    </footer>
  </div>
</div>

<div id="store-edit-modal" class="modal ">
  <div class="modal-background"></div>
  <div class="modal-card">

    <header class="modal-card-head">
      <p class="modal-card-title">Update Store</p>
    </header>

    <section class="modal-card-body">
        <label>Store name: </label>
        <input type="text" id="store-edit-name" class="input" >
        <br>
        <label>Location: </label>
        <input type="text" id="store-edit-location" class="input" >
    </section>
    <footer class="modal-card-foot">
       <button class="button  is-small eCompany" action="store-edit-modal-close">Cancel</button>
       <button class="button  is-primary is-small eCompany" action="store-update">Update store</button>
    </footer>
  </div>
</div>
