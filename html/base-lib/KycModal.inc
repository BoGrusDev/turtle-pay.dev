<div id="kyc-box"  class="modal ">
  <div class="modal-background"></div>
  <div class="modal-card" style="max-height:700px; height:700px">
    <!-- height:600px -->
        <header class="modal-card-head" style="padding-top: 12px; padding-bottom:0; background-color: #8dbf3b;">
            <p class="modal-card-title modal-ie-new" style="color:#ffffff; margin-bottom: 12px;">Kundkännedom</p> 
        </header>
        <section class="modal-card-body" style="padding-top: 6px; padding-bottom:4px;">
            <div class="container" style="margin-top:4px; padding-bottom: 0">

                <div class="columns  kyc-columns">
                    <div class="column kyc-column-header mobile-margin">
                        <p style="font-weight:normal; font-style:italic; font-size:13px">
                            Lagen kräver att vi ständigt arbetar för att motverka penningtvätt och finansiering av terrorism
                            och att vi har god kännedom om Dig som kund. Därför ställer vi några frågor vars svar vi hanterar
                            i enlighet med gällande regelverk.
                        </p>
                    </div>
                </div>
               

                <form id="kyc-form">

                    <div class="columns  kyc-columns">
                        <div class="column kyc-column-header mobile-margin">
                            <span>Medborgarskap</span>
                        </div>
                    </div>

                    <?php echo checkBoxItem(' Medborgare i Sverige','eMedborgareSverige'); ?>

                    <?php // echo textBoxItem('Medborgarskap.', 'medborgare', "medborgare-block"); ?>

                    <?php echo checkBoxItem(' Medborgare i andra länder än Sverige?','eMedborgareAndraLander'); ?>

                    <?php echo textBoxItem(' Redogör för vilka länder du är medborgare i förutom Sverige.', 'medborgare_andra_lander', 'medborgare_andra_lander-block'); ?>

                    <div class="columns kyc-columns">
                        <div class="column kyc-column-header mobile-margin">
                            <span>Skattehemvist</span>
                        </div>
                    </div>

                    <?php echo checkBoxItem(' Skattehemvist i Sverige','eSkattSverige'); ?>
                 
                    <?php echo checkBoxItem(' Skattehemvist i annat land än Sverige','eSkattAnnatLand'); ?>

                    <?php echo textBoxItem('Redogör för vilka länder detta är.', 'skatt_andra_lander', 'skatt_andra_lander-block'); ?>

                    <div class="columns kyc-columns">
                        <div class="column kyc-column-header mobile-margin">
                            <span>Sysselsättning</span>
                        </div>
                    </div>

                    <div class="columns columns kyc-columns">
                        <div class="column mobile-margin kyc-column">
                            <div class="select">
                                <select id="eSysselsattning" class="selectbox">
                                    <option value="0">--- Välj ---</option>
                                    <option value="1">Anställd</option>
                                    <option value="2">Egen företagare</option>
                                    <option value="3">Pensionär</option>
                                    <option value="4">Studerande</option>
                                    <option value="5">Arbetssökande</option>
                                </select>
                            </div>
                        </div>
                    </div>

                    <?php echo textBoxItem('Arbetsgivarens namn', 'arbetsgivare', 'arbetsgivare-block'); ?>

                    <div class="columns kyc-columns">
                        <div class="column kyc-column-header mobile-margin">
                            <span>Transaktioner</span>
                        </div>
                    </div>

                    <div class="columns columns kyc-columns">
                        <div class="column mobile-margin kyc-column">

                            <div class="field-label is-normal" style="text-align:left;padding-bottom:4px">
                                <label for="pengarna_kommer_fran" style="text-align:left;">
                                    Varifrån kommer pengarna du betalar din kredit med?
                                </label>
                            </div>

                            <div class="select">
                                <select id="ePengarnaKommerFran" class="selectbox" style="font-size:14px;padding:2px 9px">
                                    <option value="0">--- Välj ---</option>
                                    <option value="1">Lön/pension</option>
                                    <option value="2">Vinster från näringsverksamhet</option>
                                    <option value="3">Arv/gåva</option>
                                    <option value="4">Sparande</option>
                                    <option value="5">Intäkter från placeringsverksamhet</option>
                                    <option value="6">Lån</option>
                                    <option value="9">Annat</option>
                                </select>
                            </div>
                        </div>
                    </div>

                    <?php echo textBoxItem('Ange varifrån', 'pengarna_annat', 'pengarna_annat-block'); ?>

                    <div class="columns columns kyc-columns utlandska_medel-block" style="display:none">
                        <div class="column mobile-margin kyc-column"></div>
                    </div>

                    <?php echo checkBoxItem(' Jag kommer att betala krediten med utländska medel.','eUtlandskaMedel', 'utlandska_medel-block'); ?>

                    <div class="columns columns kyc-columns utlandska_medel-block" style="display:none">
                        <div class="column mobile-margin kyc-column">
                            <div class="field-label is-normal" style="text-align:left;padding-bottom:4px">
                                <label for="pengarna_kommer_fran" style="text-align:left;">
                                    Vad är ursprunget till dessa utländska medel?
                                </label>
                            </div>

                            <div class="select selectbox" >
                                <select id="eUtlandskaKommerFran" class="selectbox" style="font-size:14px; padding:2px 9px">
                                    <option value="0">--- Välj ---</option>
                                    <option value="1">Lön/pension</option>
                                    <option value="2">Vinster från näringsverksamhet</option>
                                    <option value="3">Arv/gåva</option>
                                    <option value="4">Sparande</option>
                                    <option value="5">Intäkter från placeringsverksamhet</option>
                                    <option value="6">Lån</option>
                                    <option value="9">Annat</option>
                                </select>
                            </div>
                        </div>
                    </div>

                    <?php echo textBoxItem('Ange varifrån', 'utlandska_medel_annat', 'utlandska_medel_annat-block'); ?>

                    <div class="columns kyc-columns">
                        <div class="column kyc-column-header mobile-margin">
                            <span>PEP – Person i politiskt utsatt ställning</span>
                        </div>
                    </div>
                    
                    <?php echo checkBoxItem(' Jag, en familjemedlem eller nära medarbetare innehar en politiskt utsatt ställning.','ePep'); ?>
                    
                </form>
              
            <!--        </div>
            </div> -->
            </div>
        </section>

        <footer class="modal-card-foot" style="padding-top: 10px; padding-bottom:10px;" >
        
            <div style="width:100%">
                <div class="is-left" id="kyc-message-block" style="display:none">
                    <span id="kyc-message" style="color: #5a7d22;">Sysselsättning måste anges</span>
                </div>
                <div class="buttons is-right" style="width:100%">
                    <span id="eKycCancel" style="width:84px" class="button" >Avbryt</span>
                    <span id="eKycSave" style="width:84px" class="button is-primary" >Spara</span>  
                    <span id="eKycComplete" style="display:none" class="button is-primary" >Complete</span> 
                </div>
            </div>
        </footer>
    </div>
</div>

<?php

function checkBoxItem($label, $id) {
    $html = '<div class="columns kyc-columns">';
    $html .= '<div class="column mobile-margin kyc-column">';
    $html .= '<div class="field">';
    $html .= '<input class="is-checkradio is-success checkbox" id="' . $id . '" type="checkbox" name="' . $id . '" ">';
        // checked="checked
    $html .= '<label for="' . $id . '">' . $label . '</label>';
    $html .= '</div>';
    $html .= '</div>';
    $html .= '</div>';
    return $html;
}

function textBoxItem($label, $id, $block = '') {
    $html = '<div class="columns kyc-columns ' . $block . '" style="display:none">';
        $html .= '<div class="column mobile-margin kyc-column">';
            $html .= '<div class="field-label is-normal" style="text-align:left; padding-bottom:4px">';
                $html .= '<label for="' . $id . '" style="text-align:left;">' . $label . '</label>';
            $html .= '</div>';
            $html .= '<div class="field-body">';
                $html .= '<div class="field">';
                    $html .= '<p class="control">';
                        $html .= '<input class="input w-large" type="text" id="' . $id . '" style="border-color:#dbdbdb; width:100%; max-width:500px; padding:2px 9px"/>';
                    $html .= '</p>';
                $html .= '</div>';
            $html .= '</div>';
        $html .= '</div>';
    $html .= '</div>';
    return $html;
}

