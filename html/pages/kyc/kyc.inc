<section class="hero is-primary">
    <div class="hero-body" style ="padding-bottom: 0; padding-top: 0;margin-bottom: 0;margin-top: 0;">
        <div class="container">
            <h1 style="padding-top: 10px;">
                Kundkännedom
            </h1>
        </div>
    </div>
</section>

<section class="section">
    <div class="container" style="margin-top:4px; padding-bottom: 40px">

        <div class="columns  kyc-columns">
            <div class="column kyc-column-header mobile-margin">
                <p style="font-weight:normal">
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

            <?php // echo checkBoxItem('Medborgare i Sverige','medborgare_sverige'); ?>

            <?php echo textBoxItem('Medborgarskap.', 'medborgare', "medborgare-block"); ?>

            <?php echo checkBoxItem('Medborgare i andra länder än Sverige?','medborgare_annat_land'); ?>

            <?php echo textBoxItem('Redogör för vilka länder du är medborgare i förutom Sverige.', 'medborgare_andra_lander', 'medborgare_andra_lander-block'); ?>

            <div class="columns kyc-columns">
                <div class="column kyc-column-header mobile-margin">
                    <span>Skattehemvist</span>
                </div>
            </div>

            <?php echo checkBoxItem('Skattehemvist i annat land än Sverige','skatt_annat_land'); ?>

            <?php echo textBoxItem('Redogör för vilka länder detta är.', 'skatt_andra_lander', 'skatt_andra_lander-block'); ?>

            <div class="columns kyc-columns">
                <div class="column kyc-column-header mobile-margin">
                    <span>Sysselsättning</span>
                </div>
            </div>

            <div class="columns columns kyc-columns">
                <div class="column mobile-margin kyc-column">
                    <div class="select">
                        <select id="sysselsattning" class="selectbox">
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
                        <select id="pengarna_kommer_fran" class="selectbox" >
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

            <?php echo textBoxItem('Ange vad', 'pengarna_annat', 'pengarna_annat-block'); ?>

            <?php echo checkBoxItem('Jag kommer att betala krediten med utländska medel.','utlandska_medel', 'utlandska_medel-block'); ?>

            <div class="columns columns kyc-columns utlandska_medel-select" style="display:none">
                <div class="column mobile-margin kyc-column">
                    <div class="field-label is-normal" style="text-align:left;padding-bottom:4px">
                        <label for="pengarna_kommer_fran" style="text-align:left;">
                            Vad är ursprunget till dessa utländska medel?
                        </label>
                    </div>

                    <div class="select selectbox" >
                        <select id="utlandska_kommer_fran" class="selectbox">
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

            <?php echo textBoxItem('Ange vad', 'utlandska_medel_annat', 'utlandska_medel_annat-block'); ?>


            <div class="columns kyc-columns">
                <div class="column kyc-column-header mobile-margin">
                    <span>PEP – Person i politiskt utsatt ställning</span>
                </div>
            </div>
            <?php echo checkBoxItem('Jag, en familjemedlem eller nära medarbetare innehar en politiskt utsatt ställning.','pep'); ?>

            <div class="columns kyc-columns">
                <div class="column mobile-margin" style="padding-top:20px">
                    <button id="eSaveKyc" class="button is-dark edit-on" >Spara</button>
                </div>
            </div>

        </form>
    <!--        </div>
    </div> -->
    </div>
</section>

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
                        $html .= '<input class="input w-large" type="text" id="' . $id . '" style="border-color:#dbdbdb; width:100%; max-width:500px"/>';
                    $html .= '</p>';
                $html .= '</div>';
            $html .= '</div>';
        $html .= '</div>';
    $html .= '</div>';
    return $html;
}
