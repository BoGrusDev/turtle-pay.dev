<div id="settings-section">
    <div class="d-flex justify-content-between flex-wrap flex-md-nowrap align-items-center pb-2 mb-2 border-bottom" >
        <h1 class="title is-4 has-text-centered" style="margin-bottom: 0.7rem;">Settings</h1>

        <div class="columns">
            <div class="column">
                <div class="buttons  is-right">
                    <a id="eSettingsEdit" class="button is-dark eSettings" action="edit">Edit settings</a>
                    <a id="eSettingsSave" class="button is-primary eSettings" action="save" style="display:none">Save Settings</a>
                    <a id="eSettingsCancel" class="button is-light eSettings" action="cancel" style="display:none">Cancel </a>
                </div>
            </div>
        </div>

    </div>
    <form id="settings-form" class="needs-validation" novalidate>
    <div class="columns">

        <div class="column">
            <h2 class="title is-6 has-text-centered no-bottom has-background-primary has-text-white">Global</h2>
            <?php
                echo FormItemCreate('Startdate:',null, 'start-date', 'w-dt','label-settings');
                echo FormItemCreate('Base interest (%):','base_interest',null, 'w-74','label-settings');

                echo FormItemCreate('Refinance interest margin 3m (%):','refinance_interest_margin_3m',null, 'w-74','label-settings');
                echo FormItemCreate('Refinance interest margin 6m (%):','refinance_interest_margin_6m',null, 'w-74','label-settings');
                echo FormItemCreate('Refinance interest margin 12m (%):','refinance_interest_margin_12m',null, 'w-74','label-settings');
                echo FormItemCreate('Refinance interest margin 18m (%):','refinance_interest_margin_18m',null, 'w-74','label-settings');
                echo FormItemCreate('Refinance interest margin 24m (%):','refinance_interest_margin_24m',null, 'w-74','label-settings');
                echo FormItemCreate('Refinance interest margin 36m (%):','refinance_interest_margin_36m',null, 'w-74','label-settings');
                echo FormItemCreate('Refinance interest margin 48m (%):','refinance_interest_margin_48m',null, 'w-74','label-settings');
            ?>
        </div>
        <div class="column">
            <h2 class="title is-6 has-text-centered no-bottom has-background-primary has-text-white">Company</h2>
            <?php
                echo FormItemCreate('Company credit limit (kr):','company_credit_limit',null, 'w-74','label-settings');
                echo FormItemCreate('Company UC limit (kr):','company_uc_limit',null, 'w-74','label-settings');
                echo FormItemCreate('Company UC limit (kr):','company_customer_limit',null, 'w-74','label-settings');
                
                echo FormItemCreate('Company UC limit (kr):','company_customer_limit',null, 'w-74','label-settings');

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
          ?>
      </div>
      <div class="column">
          <h2 class="title is-6 has-text-centered no-bottom has-background-primary has-text-white">People</h2>
           <?php
               echo FormItemCreate('Monthly invoice due days','monthly_invoice_due_days', null, 'w-74','label-settings');
               echo FormItemCreate('Monthly invoice due day','monthly_invoice_due_day', null, 'w-74','label-settings');
               echo FormItemCreate('Monthly settlement day','monthly_settlement_day', null, 'w-74','label-settings');
               echo FormItemCreate('Monthly invoice fee (kr)','monthly_invoice_fee', null, 'w-74','label-settings');

               echo FormItemCreate('Customer overdue interest margin (%)','due_interest_margin', null, 'w-74','label-settings');
               echo FormItemCreate('Reminder fee (kr)','reminder_fee', null, 'w-74','label-settings');
               echo FormItemCreate('Collection fee (kr)','collection_fee', null, 'w-74','label-settings');
               echo FormItemCreate('Installment limit (kr)','installment_limit', null, 'w-74','label-settings');

               echo FormItemCreate('UC level-0 (kr)','uc_level_0', null, 'w-74','label-settings');
               echo FormItemCreate('UC level-0 credit (kr)','uc_level_0_credit', null, 'w-74','label-settings');
               echo FormItemCreate('UC level-1 (kr)','uc_level_1', null, 'w-74','label-settings');
               echo FormItemCreate('UC level-1 credit (kr)','uc_level_1_credit', null, 'w-74','label-settings');
               echo FormItemCreate('UC level-2 (kr)','uc_level_2', null, 'w-74','label-settings');
               echo FormItemCreate('UC level-2 credit (kr)','uc_level_2_credit', null, 'w-74','label-settings');
               echo FormItemCreate('UC level-3 (kr)','uc_level_3', null, 'w-74','label-settings');
               echo FormItemCreate('UC level-3 credit (kr)','uc_level_3_credit', null, 'w-74','label-settings');
               echo FormItemCreate('UC level-4 (kr)','uc_level_4', null, 'w-74','label-settings');
               echo FormItemCreate('UC level-4 credit (kr)','uc_level_4_credit', null, 'w-74','label-settings');
               echo FormItemCreate('UC level-5 (kr)','uc_level_5', null, 'w-74','label-settings');
               echo FormItemCreate('UC level-5 credit (kr)','uc_level_5_credit', null, 'w-74','label-settings');
               echo FormItemCreate('UC level-6 (kr)','uc_level_6', null, 'w-74','label-settings');
               echo FormItemCreate('UC level-6 credit (kr)','uc_level_6_credit', null, 'w-74','label-settings');
               echo FormItemCreate('UC level-7 (kr)','uc_level_7', null, 'w-74','label-settings');
               echo FormItemCreate('UC level-7 credit (kr)','uc_level_7_credit', null, 'w-74','label-settings');
               echo FormItemCreate('UC max credit (kr)','uc_max_credit', null, 'w-74','label-settings');
              
           ?>
      </div>

    </div>
     <input type="hidden" name="setting_type" value="s">
      </form>
</div>

<?php /*
    ALTER TABLE `setting` ADD `installment_limit` INT NULL DEFAULT NULL AFTER `collection_fee`; 

*/ ?>