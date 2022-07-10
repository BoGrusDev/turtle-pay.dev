<?php

echo eventSectionHeader('Event', 'is-primary page-section section-event-list', $isMobile);
echo '<section class="section page-section section-event-list" style="display:none">';
    echo '<div class="container">';
        echo '<div class="columns no-padding" style="margin-top:0px;">';
            echo '<div id="event-list" class="column" style="padding-top:0; padding-bottom:30px"></div>';
        echo '</div>';
    echo '</div>';
echo '</section>';

echo eventSectionHeader('Eventrapporter', 'is-primary page-section section-report-list', $isMobile);
echo '<section class="section page-section section-report-list" style="display:none">';
    echo '<div class="container">';
        echo '<div class="columns" style="margin-top:4px; margin-bottom: 6px;">';
            echo '<div class="column" style="padding-bottom:3px; padding-top:6px">';
                echo '<div class="buttons is-right">';
                    echo '<a id="eBackEventList" class="button is-dark">Stäng</a>';
                echo '</div>';
            echo '</div>';
        echo '</div>';
        echo '<div class="columns no-padding" style="margin-top:-32px;">';
            echo '<div id="report-list" class="column" style="padding-top:0; padding-bottom:30px"></div>';
        echo '</div>';
    echo '</div>';
echo '</section>';

echo eventSectionHeader('Deltagarlista', 'is-primary page-section section-participant-list', $isMobile);

echo '<section class="section page-section section-participant-list" style="display:none">';
    echo '<div class="container">';
        echo '<div class="columns" style="margin-top:4px; margin-bottom: 6px;">';
            echo '<div class="column" style="padding-bottom:3px; padding-top:6px">';
                echo '<h1 id="title-report-name" style="font-size:24px; font-weight:bold; line-height:28px">Deltagarlista</h1>';
                echo '<p id="title-event-name" style="font-size:14px; font-weight:bold; margin-bottom:0"></p>';
                echo '<p id="title-event-counter" style="font-size:14px; font-weight:bold;"></p>';
            echo '</div>';

            echo '<div class="column" style="padding-bottom:3px; padding-top:6px">';
                echo '<div class="buttons is-right">';
                    if ($isMobile == 'no') {
                        echo '<a id="ePrintList" class="button is-dark">Skriv ut</a>';
                        echo '<a id="eExportCsv" class="button is-dark">Excel</a>';
                    }
                    echo '<a id="eBackReportList" class="button is-dark">Stäng</a>';
                echo '</div>';
            echo '</div>';
        echo '</div>';
    
        //echo '<div class="columns" style="margin-top:0; margin-bottom: 6px; ">';
            //echo '<div class="column" style="text-align:right; padding-bottom:0; padding-top: 0; margin:0">';
            //echo '<label class="checkbox modal-label"> <input class="is-primary is-small modal-checkbox" id="ePanelCanceled" type="checkbox">&nbsp;&nbsp;Visa avbokade</label>';
            //echo '</div>';
        // echo '</div>';
        
    echo '</div>';  // container -

   echo htmlPrintList('print-list', 'participant-list', 'report-title');
echo '</section>';

function eventSectionHeader($title, $classes) {
    $html = '';
    $html .= '<section class="hero ' . $classes . '" style="display:none;background-color:#4DB4D7; color: #ffffff">';
        $html .= '<div class="hero-body" style ="padding-bottom: 0; padding-top: 0;margin-bottom: 0;margin-top: 0;">';
            $html .= '<div class="container">';
                $html .= '<h1 style="padding-top: 10px;">' . $title . '</h1>';
            $html .= '</div>';
        $html .= '</div>';
    $html .= '</section>';
    
    return $html;    
}
function htmlPrintList($printId, $listId, $title) {
    $html = '';
    $html .= '<div class="container" id="' . $printId . '">';
    $html .= '<div class="columns" style="margin: 4px 0 6px 0; width:100%;">';
    $html .= '<div class="column no-margin no-padding left">';
    $html .= '<div>';
    $html .= '<h1 id="' . $title . '" style="font-size:24px; font-weight:bold;"></h1>';
    $html .= '</div>';
    $html .= '</div>';
    $html .= '</div>';  
    $html .= '<div class="columns no-padding" style="margin-top:0px">';
    $html .= '<div id="' . $listId . '" class="column" style="padding-top:0; padding-bottom:30px;overflow:auto">';
    $html .= '</div>';
    $html .= '</div>';
    $html .= '</div>';
    return $html;
}

/*

// --
// -- EventItem list
// --
echo eventSectionHeader('Eventlista', 'is-primary page-section section-event-item', $isMobile);

echo eventSection('page-section section-event-item',  $isMobile);
    $param = array();
    $param[0] = new stdClass();
    $param[0]->text = 'Skriv ut';
    $param[0]->eventId = 'ePrintList';
    $param[0]->classes = 'is-dark';
    $param[1] = new stdClass();
    $param[1]->text = 'Excel';
    $param[1]->eventId = 'eExportCsv';
    $param[1]->classes = 'is-dark';
    $param[2] = new stdClass();
    $param[2]->icon = 'fa-times';
    $param[2]->eventId = 'eBackEventList';
    $param[2]->classes = 'is-dark';    
    echo htmlButtons($param);
    echo htmlPrintList('print-list', 'event-item-list', 'event-title');
echo eventSectionEnd();

// -- 
// -- Help function for Event
// --

function eventSectionHeader($title, $classes) {
    $html = '';
    $html .= '<section class="hero ' . $classes . '" style="display:none;background-color:#4DB4D7; color: #ffffff"">';
        $html .= '<div class="hero-body" style ="padding-bottom: 0; padding-top: 0;margin-bottom: 0;margin-top: 0;">';
            $html .= '<div class="container">';
                $html .= '<h1 style="padding-top: 10px;">' . $title . '</h1>';
            $html .= '</div>';
        $html .= '</div>';
    $html .= '</section>';
    
    return $html;    
}

function eventSection($classes, $isMobile = 'no') {
    $html = '';
    $html .= '<section class="section ' . $classes . '" style="display:none">';
    $html .= '<div class="container">';
    return $html;    
}

function eventSectionEnd() {
    $html = '';
    $html = '</div>';
    $html .= '</section>';

    return $html;
}
 
function htmlButtons($param) {
    $html = '';
    $html .= '<div class="columns" style="margin-top:4px; margin-bottom: 6px; ">';
    $html .= '<div class="column"  style="padding-bottom:3px; padding-top:6px">';
    $html .= '<div class="buttons is-right">';
    for ($i = 0; $i < sizeof($param); $i++) {
        if (isset($param[$i]->icon)) {
            $html .= '<a id="' . $param[$i]->eventId . '" class="button ' . $param[$i]->classes . '"><span class="icon is-medium"><i class="fas fa-times"></i></span></a>';
        }
        else {
            $html .= '<a id="' . $param[$i]->eventId . '" class="button ' . $param[$i]->classes . '">' . $param[$i]->text . '</a>';
        }
    }
    $html .= '</div>';
    $html .= '</div>';
    $html .= '</div>';
    return $html;
}

function htmlListArea($eventId) {
    $html = '';
    $html .= '<div class="columns no-padding" style="margin-top:0px;">';
    $html .= '<div id="' . $eventId . '" class="column" style="padding-top:0; padding-bottom:30px">';
    $html .= '</div>';
    $html .= '</div>';
    return $html;
}


*/
?>
