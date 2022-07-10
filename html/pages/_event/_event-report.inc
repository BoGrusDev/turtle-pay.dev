<?php 
/*
   @[class]even-report.inc

   @[desc]
   * Hanling the list and report of Evnet items 
   @[end-desc]

   @[update]2020-09-13

   @[todo]
   @[end-todo]

*/
?>

<section class="hero is-primary page-section section-event-item" style="display:none">
    <div class="hero-body" style ="padding-bottom: 0; padding-top: 0;margin-bottom: 0;margin-top: 0;">
        <div class="container">
            <h1 style="padding-top: 10px;">Deltagarlista</h1>
        </div>
    </div>
</section>

<section class="section page-section section-event-item" style="display:none">
    <div class="container">
        <div class="columns" style="margin-top:4px; margin-bottom: 6px; ">
            <div class="column" style="padding-bottom:3px; padding-top:6px">
                <div class="buttons is-left">
                    <div>
                        <h1 id="title-report-name" style="font-size:24px; font-weight:bold; line-height:28px">Deltagarlista</h1>
                        <p id="title-event-name" style="font-size:14px; font-weight:bold; margin-bottom:0"></p>
                         <p id="title-event-counter" style="font-size:14px; font-weight:bold; margin-bottom:0"></p>
                        <p id="title-event-last-invoicing" style="font-size:14px; font-weight:bold; margin-bottom:0"></p>
                    </div>
                </div>
            </div>
            <div class="column" style="padding-bottom:3px; padding-top:6px">
                <div class="buttons is-right">
                    <a id="eTdbPremier"  style="width:100px; background-color: #2565AE  ; color: #eeeeee" class="button">Premier</a>
					<a id="eTdbUpdate" style="width:100px; background-color: #cc3333; color: #eeeeee" class="button">Fakturera</a>
                    <a id="ePanel" class="button is-primary">Visa</a>
                    <a id="ePrintList" class="button is-dark">Skriv ut</a>
                    <a id="eExportCsv" class="button is-dark">Excel</a>
                    <a id="eBackEventList" class="button is-dark">Stäng</a>
                </div>
            </div>
        </div>
    
        <div class="columns" style="margin-top:0; margin-bottom: 6px; "> 
            <div class="column" style="text-align:right; padding-bottom:0; padding-top: 0; margin:0">
                <label class="checkbox modal-label"> <input class="is-primary is-small modal-checkbox" id="ePanelCanceled" type="checkbox">&nbsp;&nbsp;Visa avbokade</label>
            </div>
        </div>

    </div> <!-- container -->

    <?php echo htmlPrintList('print-list', 'event-item-list', 'event-title'); ?>
</section>

<?php 
echo boxPanel();
echo boxPanelSaveAs();
echo boxPanelRemove();
echo boxParticipantDetails();
echo boxInvoice();

function boxPanel() {

    $html = '';
    $html .= '<div id="box-panel"  class="modal">';
        $html .= '<div class="modal-background"></div>';
        $html .= '<div class="modal-card" style="width: 720px; max-height:600px; height:600px">';
            $html .= '<header class="modal-card-head" style="padding-top: 12px; padding-bottom:0; background-color: #8dbf3b;">';
                $html .= '<p class="modal-card-title modal-ie-new" style="color:#ffffff">' . 'Visa' . '</p>'; 
            $html .= '</header>';
            $html .= '<form id="panel-form" style="overflow-y: scroll;">';

                $html .= '<section id="panel-report" class="modal-card-body">';  
                      $html .= '<div class="columns modal-columns">';
                        $html .= '<div class="column"style="padding-top:0; padding-bottom:0">';
                            $html .= '<h3 style="font-weight:bold">Rapporter</h3>';              
                        $html .= '</div>'; 
                    $html .= '</div>';
                    
                    $html .= '<div class="columns modal-columns">';
                        $html .= '<div id="panel-report-list" class="column modal-column" style="margin-top:6px"">';
                            // Drop down loaded dynamic
                        $html .= '</div>';
                    $html .= '</div>';
                   
                    $html .= '<hr style="background-color: #666666; height: 0.5px; margin: 12px 0 6px 0">';  
                    
                $html .= '</section>';

                $html .= '<section id="panel-part" class="modal-card-body">';  

                    $html .= '<div class="columns modal-columns panel-part">';
                        $html .= '<div class="column" style="padding-top:0; padding-bottom:0">';
                            $html .= '<div id="participant-box-title2" style="font-weight:bold">Deltagaruppgifter</div>';              
                        $html .= '</div>'; 
                    $html .= '</div>';
                    
                $html .= '</section>';

                $html .= '<section id="panel-selection" class="modal-card-body">';
                    
                    $html .= htmlBoxRow();
                        $html .= '<div class="column"style="padding-top:0; padding-bottom:0">';
                            $html .= '<h3 style="font-weight:bold">Urval</h3>';              
                        $html .= '</div>'; 
                    $html .= '</div>';
                
                $html .= '</section>';
                

                $html .= '<section id = "panel-webform-data" class="modal-card-body">';

                    $html .= '<div class="columns modal-columns">';
                        $html .= '<div class="column" style="padding-top:0; padding-bottom:0">';
                            $html .= '<label class="checkbox bold">';
                                $html .= '<input label="Summa" class="is-primary" id="_part_sum" type="checkbox">&nbsp;&nbsp;Summera alla urval';
                            $html .= '</label>';
                        $html .= '</div>';
                    $html .= '</div>';

                    $html .= '<hr style="background-color: #666666; height: 0.5px; margin: 14px 0 2px 0">';   
                    
                    $html .= htmlBoxRow();
                        $html .= '<div class="column"style="padding-top:0; padding-bottom:0">';
                            $html .= '<h3 style="font-weight:bold">Webformulär</h3>';              
                        $html .= '</div>'; 
                    $html .= '</div>';
                    
                $html .= '</section>';

            $html .= '</form>';

            $html .= '<footer class="modal-card-foot" style="padding-top: 10px; padding-bottom:10px;">';
           
				$html .= '<div id="save-message" class="is-left" style="width:240px; display:none">';
                    $html .= '<span style="font-style:italic; color: #5a7d22">Rapporten har sparats</span>';
                $html .= '</div>';
		   
		   
                $html .= '<div class="buttons is-right" style="width:100%">';
                    $html .= '<span id="ePanelRemove" style="width:92px" class="button is-white">Ta bort</span>';
                    $html .= '<span id="ePanelSaveAs" style="width:92px" class="button is-dark">Spara som</span>';
                    $html .= '<span id="ePanelSave" style="width:84px" class="button is-dark">Spara</span>';
                    // $html .= '<span id="ePanelDetails" style="width:84px" class="button is-primary">Detaljer</span>';
                    $html .= '<span id="ePanelProcess" style="width:84px" class="button is-primary" >OK</span>';  
                $html .= '</div>';
            $html .= '</footer>';
        $html .= '</div>';
    $html .= '</div>';

    return $html;
} 

function boxPanelSaveAs() {
    
    $html = '';
    $html .='<div class="modal" id="box-panel-save-report">';
    $html .='<div class="modal-background"></div>';
    $html .='<div class="modal-card pl0 pr0  modal-width">';
    $html .='<header class="modal-card-head">';
    $html .='<p class="modal-card-title has-text-centered">Spara rapport</p>';
    $html .='</header>';
    $html .='<section class="modal-card-body">';
     
        $html .= '<div class="columns modal-columns" id="panel-save-as">';
            $html .= '<div class="column modal-column" style="padding-top: 14px;">';
                $html .= '<label class="modal-label" style="font-size:14px; font-weight:bold;">&nbsp;Namn på rapport</label>';
                $html .= '<input type="text" id="panel-report-name" class="input is-primary" style="margin-top:5px; margin-bottom: 12px;">';
            $html .= '</div>';
        $html .= '</div>';
        
    $html .='</section>';
    $html .='<footer class="modal-card-foot">';
    $html .='<button id="eBoxPanelSaveReportCancel" class="button is-dark w120 image-center">Avbryt</button>';
    $html .='<button id="eBoxPanelSaveReportSave" class="button is-primary w120 image-center">Spar</button>';
    $html .='</footer>';
    $html .='</div>';
    $html .='</div>';

    return $html;  
}

function boxParticipantDetails() {

	$html = '';
	$html .= '<div id="box-participant-details" class="modal">';
		$html .= '<div class="modal-background"></div>';
		$html .= '<div class="modal-card" style="max-height:420px; height:420px">';
			$html .= '<header class="modal-card-head" style="padding-top: 12px; padding-bottom:0; background-color: #8dbf3b;">';
				$html .= '<p class="modal-card-title modal-ie-new" style="color:#ffffff">' . 'Detaljer' . '</p>'; 
			$html .= '</header>';
			$html .= '<section class="modal-card-body">';
				$html .= htmlBoxRow();
				$html .= '<h3 style="padding: 0 0px 6px 8px; font-size:1.2rem" id="box-participant-cancel-people-name">Larsson Peter</h3>';
				$html .= htmlDivEnd();

				$html .= '<div id="box-participant-details-selections"></div>';
            
               
			$html .= '</section>';
			
            $html .= '<footer class="modal-card-foot" style="padding-top: 10px; padding-bottom:10px;">';
               
				$html .= '<div class="buttons is-right" style="width:100%">';
					$html .= '<span id="eBoxParticipantDetailsClose" style="width:84px" class="button" >Avbryt</span>';
					$html .= '<span id="eBoxParticipantDetailsPerform" style="width:84px" class="button is-primary" >Utför</span>';  
				$html .= '</div>';
			$html .= '</footer>';
		$html .= '</div>';
	$html .= '</div>';

	return $html;
} 


function boxPanelRemove() {
    
    $html = '';
    $html .='<div class="modal" id="box-panel-remove-report">';
    $html .='<div class="modal-background"></div>';
    $html .='<div class="modal-card pl0 pr0  modal-width">';
    $html .='<header class="modal-card-head">';
    $html .='<p class="modal-card-title has-text-centered">Ta bort rapport</p>';
    $html .='</header>';
    $html .='<section class="modal-card-body">';
     
        $html .= '<div class="columns modal-columns" id="panel-save-as">';
            $html .= '<div class="column modal-column" style="padding-top: 12px!important;">';
                $html .= '<p class="modal-label" style="font-size:14px; text-align: center; font-weight:bold;">Är det säker?</p>';
            $html .= '</div>';
        $html .= '</div>';
        
    $html .='</section>';
    $html .='<footer class="modal-card-foot">';
    $html .='<button id="eBoxPanelRemoveReportCancel" class="button is-dark w120 image-center">Avbryt</button>';
    $html .='<button id="eBoxPanelRemoveReportOk" class="button is-primary w120 image-center">Ja</button>';
    $html .='</footer>';
    $html .='</div>';
    $html .='</div>';

    return $html;  
}

function boxInvoice() {
    
    $html = '';
    $html .='<div class="modal" id="box-invoice">';
    $html .='<div class="modal-background"></div>';
    $html .='<div class="modal-card pl0 pr0  modal-width">';
    $html .='<header class="modal-card-head">';
    $html .='<p class="modal-card-title has-text-centered">Fakturera</p>';
    $html .='</header>';
    $html .='<section class="modal-card-body">';
     
        $html .= '<div class="columns modal-columns" >';
            $html .= '<div class="column modal-column"  style="padding-top: 14px; min-height:80px;">';
                $html .= '<p id="box-invoice-result" style="margin-top: 18px; font-size: 16px; text-align:center">';
            $html .= '</div>';
        $html .= '</div>';
        
    $html .='</section>';
    $html .='<footer class="modal-card-foot">';
    $html .='<button id="eBoxInvoiceClose" class="button is-dark w120 image-center">Stängt</button>';
    $html .='<button id="eBoxInvoiceConfirm" class="button is-primary w120 image-center">Skapa</button>';
    $html .='</footer>';
    $html .='</div>';
    $html .='</div>';

    return $html;  
}