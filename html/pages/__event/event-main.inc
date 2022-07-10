<?php 
/*
   @[class]even-main.inc

   @[desc]
   * Hanling the main event function
   @[end-desc]

   @[update]2020-09-13

   @[todo]
   @[end-todo]

*/
// --
// -- Creae the header of page 
// --

echo '<section class="hero is-primary page-section section-event-list" style="display:none">';
    echo '<div class="hero-body" style>';
        echo '<div class="container">';
            echo '<h1 style="padding-top: 10px;">Event</h1>';
        echo '</div>';
    echo '</div>';
echo '</section>';

echo '<section class="section page-section section-event-list" style="display:none">';
    echo '<div class="container">';

        $param = array();
        $param[0] = new stdClass();
        $param[0]->text = 'Skapa nytt Event';
        $param[0]->eventId = 'eNewEvent';
        $param[0]->classes = 'is-link';
        echo htmlButtons($param);

        echo '<div class="columns" style="margin-top:0; margin-bottom: 6px;">'; 
            echo '<div class="column" style="text-align:right; padding-bottom:0; padding-top: 0; margin:0">';
                echo '<label class="checkbox modal-label"> <input class="is-primary is-small modal-checkbox" id="eEventListFiler" type="checkbox">&nbsp;&nbsp;<span id="filter-list-event">' . 'Visa avslutade' . '</label>';
            echo '</div>';
        echo  '</div>';

        echo '<div class="columns no-padding" style="margin-top:0px;">';
        echo '<div id="event-list" class="column" style="padding-top:0; padding-bottom:30px">';
        echo '</div>';
        echo  '</div>';
    echo '</div>';
echo '</section>';

echo htmlBoxEventNew('Nytt Event');
echo htmlBoxInherit();
echo webformYesNoCloseEvent();
echo htmlBoxClearEvent();


function htmlBoxEventNew($title) {

    $html = '';
    $html .= '<div id="box-event-new"  class="modal">';
        $html .= '<div class="modal-background"></div>';
        $html .= '<div class="modal-card" style="max-height:420px; height:420px">';
            $html .= '<header class="modal-card-head" style="padding-top: 12px; padding-bottom:0; background-color: #8dbf3b;">';
                $html .= '<p class="modal-card-title modal-ie-new" style="color:#ffffff">' . $title . '</p>'; 
            $html .= '</header>';
            $html .= '<section class="modal-card-body">';
                $html .= htmlBoxRow();
                $html .= htmlBoxInput('Namn på Event', 'new-event-name', true);
                $html .= htmlDivEnd();

                $html .= htmlBoxRow();
                    $html .= '<div class="column modal-column" id="tdb-competions-list"></div>';
                $html .= htmlDivEnd();

                $html .= htmlBoxRow();
                    $html .= '<div class="column modal-column" id="event-template-list"></div>';
                $html .= htmlDivEnd();
                $html .= htmlBoxError('box-event-new'); // box-event-new-error-container

            $html .= '</section>';
             
            $html .= '<footer class="modal-card-foot" style="padding-top: 10px; padding-bottom:10px;">';
                $html .= '<div class="buttons is-right" style="width:100%">';
                    $html .= '<span id="eBoxEventNewClose" style="width:84px" class="button" >Avbryt</span>';
                    $html .= '<span id="eBoxEventNewCreate" style="width:84px" class="button is-primary" >Skapa</span>';  
                $html .= '</div>';
            $html .= '</footer>';
        $html .= '</div>';
    $html .= '</div>';

    return $html;
} 

function htmlBoxInherit() {

    $html = '';
    $html .= '<div id="box-inherit"  class="modal">';
        $html .= '<div class="modal-background"></div>';
        $html .= '<div class="modal-card" style="max-height:290px; height:290px">';
            $html .= '<header class="modal-card-head" style="padding-top: 12px; padding-bottom:0; background-color: #8dbf3b;">';
                $html .= '<p class="modal-card-title modal-ie-new" style="color:#ffffff">' . 'Nytt webformulär' . '</p>'; 
            $html .= '</header>';
            $html .= '<section class="modal-card-body">';
                $html .= htmlBoxRow();
                $html .= htmlBoxInput('Ny referens', 'new-ref', true);
                $html .= htmlDivEnd();

                $html .= htmlBoxRow();
                    $html .= '<div class="column modal-column" style="padding-top: 10px!important">';
                        $html .= '<input type="radio" id="webform-continue" name="inherit_type" value="continue">';
                        $html .= '<label for="webform-continue" style="padding: 4px 2px 4px; 6px"> Importera data</label>';
                    $html .= '</div>';
                $html .= htmlDivEnd();

                $html .= htmlBoxRow();
                    $html .= '<div class="column modal-column">';
                        $html .= '<input type="radio" id="webform-new" name="inherit_type" value="new">';
                        $html .= '<label for="webform-continue" style="padding: 4px 2px 4px; 6px"> Gruppera</label>';
                    $html .= '</div>';
               $html .= htmlDivEnd();

               $html .= htmlBoxError('box-inherit'); // Set to box id
                
            $html .= '</section>';
             
            $html .= '<footer class="modal-card-foot" style="padding-top: 10px; padding-bottom:10px;">';
                $html .= '<div class="buttons is-right" style="width:100%">';
                    $html .= '<span id="eBoxInheritClose" style="width:84px" class="button" >Avbryt</span>';
                    $html .= '<span id="eBoxInheritCreate" style="width:84px" class="button is-primary" >Skapa</span>';  
                $html .= '</div>';
            $html .= '</footer>';
        $html .= '</div>';
    $html .= '</div>';

    return $html;
} 

function webformYesNoCloseEvent() {
    $html = '';
    $html .='<div class="modal" id="yesno-close-event-box">';
    $html .='<div class="modal-background"></div>';
    $html .='<div class="modal-card pl0 pr0  modal-width">';
    $html .='<header class="modal-card-head">';
    $html .='<p class="modal-card-title has-text-centered">Kontrollfråga</p>';
    $html .='</header>';
    $html .='<section class="modal-card-body">';
    //$html .='<p class="remove-selection-warning has-text-centered" style="margin-bottom:2px; font-weight:bold">VARNING!</p>';
    // $html .='<p class="remove-selection-warning has-text-centered" style="font-size: 12px; font-style:italic; margin-bottom:8px">Vidarekopplingar kommer att gå förlorade</p>';
    $html .='<p class="has-text-centered" style="margin-bottom:24px" id="yesno-text-modal">Är du säker på att du vill avsluta Eventet?</p>';
    $html .='<p class="has-text-centered" style="margin-bottom:24px; font-style:italic" id="yesno-text-modal">Importerade och grupperade Event kommer även att avslutas</p>';
    $html .='</section>';
    $html .='<footer class="modal-card-foot">';
    $html .='<button id="eYesNoCloseEventNo" class="button is-dark w120 image-center">Avbryt</button>';
    $html .='<button id="eYesNoCloseEventYes" class="button is-primary w120 image-center">Ja</button>';
    $html .='</footer>';
    $html .='</div>';
    $html .='</div>';
    return $html;
}

function htmlBoxClearEvent() {

    $html = '';
    $html .= '<div id="box-event-clear"  class="modal">';
        $html .= '<div class="modal-background"></div>';
        $html .= '<div class="modal-card" style="max-height:330px; height:300px">';
            $html .= '<header class="modal-card-head" style="padding-top: 12px; padding-bottom:0; background-color: #8dbf3b;">';
                $html .= '<p class="modal-card-title modal-ie-new" style="color:#ffffff">' . 'Radera Event' . '</p>'; 
            $html .= '</header>';
            $html .= '<section class="modal-card-body">';
                $html .= '<div class="column modal-column" style="padding-top: 10px!important">';
                    //$html .= '<p style="font-size: 20px; margin:12px 8px 8px 8px">Radera Event<p>'; 
                    $html .= '<p id="event-clear-type-event" style="font-size: 20px; margin:2px 8px 8px 8px"><p>'; 

                    $html .= '<p style="margin:16px 8px 8px 8px">”Radera alla personuppgifter och deltagarlistor permanent.”<p>'; 
                    //$html .= '<p style="margin:0px 8px 8px 8px">kommer att raderas permanent.</p>';

                    $html .= '<div class="columns" style="margin:20px 8px 8px 8px; font-weight:bold"> ';
                        $html .= '<label class="checkbox modal-label">';
                        $html .= '<input class="is-primary is-small modal-checkbox" id="eEventClearConfirm" type="checkbox">&nbsp;&nbsp;Godkänn radering!</label>';
                    $html .= '</div>';
                $html .= '</div>';
              
               // $html .= htmlBoxError('box-event-clear'); // Set to box id
                
            $html .= '</section>';
             
            $html .= '<footer class="modal-card-foot" style="padding-top: 10px; padding-bottom:10px;">';
                $html .= '<div class="buttons is-right" style="width:100%">';
                    $html .= '<span id="eBoxEventClearClose" style="width:84px" class="button" >Avbryt</span>';
                    $html .= '<span id="eBoxEventClearStart" style="width:84px" class="button is-primary" >Radera</span>';  
                $html .= '</div>';
            $html .= '</footer>';
        $html .= '</div>';
    $html .= '</div>';

    return $html;
} 