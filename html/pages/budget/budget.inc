<section class="hero is-primary">
    <div class="hero-body" style ="padding-bottom: 0; padding-top: 0;margin-bottom: 0;margin-top: 0;">
        <div class="container">
            <h1 style="padding-top: 10px;">
                Hushållsbudget
            </h1>
        </div>
    </div>
</section>

<section class="section">
    <div class="container">
        <div class="columns" style="margin-top:4px; padding-bottom: 40px">
            <div class="column mobile-margin">
                <form id="budget-form">

                    <div class="columns details-row">
                        <div class="column details-label h-budget"><span>Arbetsinkomst</span></div>
                    </div>
                    <div class="columns details-row">
                        <div class="column details-column">
                            <table class="table" style="width:100%;">
                                <?php
                                echo budgetItem('Arbetsinkomst efter skatt per månad','ipm_arbete');
                                echo budgetItem('Pension','ipm_pension');
                                echo budgetItem('Förmåner, ersättningar & bidrag','ipm_form');
                                echo budgetSum('Summa','ipm_sum');
                                ?>
                            </table>
                        </div>
                    </div>

                    <div class="columns details-row">
                        <div class="column details-label h-budget"><span>Bostadskostnader per månad</span></div>
                    </div>
                    <div class="columns details-row">
                        <div class="column details-column">
                            <table class="table" style="width:100%;">
                                <?php
                                echo budgetItem('Avgift/hyra','bpm_hyra');
                                echo budgetItem('Kostnadsräntor','bpm_ranta');
                                echo budgetItem('Amorteringar','bpm_amor');
                                echo budgetItem('El/värme','bpm_el');
                                echo budgetItem('Vatten','bpm_vatten');
                                echo budgetItem('Sophämtning','bpm_sop');
                                echo budgetItem('Reparationer','bpm_rep');
                                echo budgetSum('Summa','bpm_sum');
                                ?>
                            </table>
                        </div>
                    </div>

                    <div class="columns details-row">
                        <div class="column details-label h-budget"><span>Övriga lånekostnader per månad</span></div>
                    </div>
                    <div class="columns details-row">
                        <div class="column details-column">
                            <table class="table" style="width:100%;">
                                <?php
                                echo budgetItem('Kostnadsräntor','lpm_ranta');
                                echo budgetItem('Amorteringar','lpm_amor');
                                echo budgetSum('Summa','lpm_sum');
                                ?>
                            </table>
                        </div>
                    </div>
                    <div class="columns details-row">
                        <div class="column details-label h-budget"><span>Fordon</span></div>
                    </div>
                    <div class="columns details-row">
                        <div class="column details-column">
                            <table class="table" style="width:100%;">
                                <?php
                                echo budgetItem('Kostnadsräntor','fpm_ranta');
                                echo budgetItem('Skatt','fpm_skatt');
                                echo budgetItem('Besiktning','fpm_besikt');
                                echo budgetItem('Försäkring','fpm_fors');
                                echo budgetItem('Reparationer/Service','fpm_rep');
                                echo budgetItem('Bränsle','fpm_bransle');
                                echo budgetItem('Parkering','fpm_parking');
                                echo budgetSum('Summa','fpm_sum');
                                ?>
                            </table>
                        </div>
                    </div>

                    <div class="columns details-row">
                        <div class="column details-label h-budget"><span>Hushållskostnader per månad</span></div>
                    </div>
                    <div class="columns details-row">
                        <div class="column details-column">
                            <table class="table" style="width:100%;">
                                <?php
                                echo budgetItem('Livsmedel','hpm_livs');
                                echo budgetItem('Kläder','hpm_klader');
                                echo budgetItem('Sport/Fritid','hpm_sport');
                                echo budgetItem('Mobiltelefon','hpm_mobil');
                                echo budgetItem('Förbrukningsvaror','hpm_forbruk');
                                echo budgetItem('Hemutrustning','hpm_hemutr');
                                echo budgetSum('Summa','hpm_sum');
                                ?>
                            </table>
                        </div>
                    </div>

                    <div class="columns details-row">
                        <div class="column details-label h-budget"><span>Övriga månadskostnader</span></div>
                    </div>
                    <div class="columns details-row">
                        <div class="column details-column">
                            <table class="table" style="width:100%;">
                                <?php
                                echo budgetItem('Restaurang','omk_rest');
                                echo budgetItem('Kollektivresor','omk_kollek');
                                echo budgetItem('Läkare, tandläkare, medicin', "omk_lakare");
                                echo budgetSum('Summa','omk_sum');
                                ?>
                            </table>
                        </div>
                    </div>

                    <div class="columns details-row" style="margin-top: 20px">
                        <div class="column details-column">
                            <table class="table" style="width:100%;">
                                <?php
                                echo budgetSum('Summa att leva på','sum_att_leva');
                                ?>
                            </table>
                        </div>
                    </div>

                    <!-- summa_att_leva -->

                    <div class="columns">
                        <div class="column" style="padding-top:20px">
                            <!-- <button id="eEditModeOn" class="button is-primary edit-off" >Ändra</button> -->
                            <button id="eEditModeCancel" class="button is-gray edit-on" style="display:none">Avbryt</button>
                            <button id="eEditUpdate" class="button is-dark edit-on" style="display:none">Spara</button>
                        </div>
                    </div>

                </form>
            </div>
        </div>
    </div>
</section>

<?php


function budgetItem($label, $id) {

    $html = '<tr>';
    $html .= '<td>' . $label . '</td>';
    $html .= '<td class="right">';
    $html .= '<span class="edit-off s-budget" id="show_' . $id  . '"></span>';
    $html .= '<input class="edit-on w-budget" id="' . $id . '" style="display:none"/>';
    $html .= '</td>';
    $html .= '</tr>';
    return $html;
}

function budgetSum($label, $id) {

    $html = '<tr>';
    $html .= '<td class="bold">' . $label . '</td>';
    $html .= '<td class="right">';
    $html .= '<span class="bold s-budget" id="show_' . $id  . '"></span>';
    //$html .= '<input class="edit-on w-budget" id="' . $id . '" style="display:none"/>';
    $html .= '</td>';
    $html .= '</tr>';
    return $html;
}

/*
function budgetItem2($label, $id) {

    $html = '<div class="columns details-row">';
    $html .= '<div class="column details-label l-budget is-two-thirds" ><span>' . $label . '</span></div>';
    $html .= '<div class="column details-column right">';
    $html .= '<span class="edit-off s-budget" id="show_' . $id  . '"></span>';
    $html .= '<input class="edit-on w-budget" id="' . $id . '" style="display:none"/>';
    $html .= '</div>';
    $html .= '</div>';
    return $html;
}
*/
