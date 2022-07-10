<?php
/*
   @[class]even-report.js.inc

   @[desc]
   * Script for the event-report.inc 
   @[end-desc]

   @[update]2020-09-13

   @[todo]
   @[end-todo]

*/
// Declared in event-main.js
/* 
	require_once 'base-lib/ModelBaseClass.js.inc';
	class ModelBase extends ModelBaseClass {}
	const Model = new ModelBase();
	Current.serviceApi = 'service2/';
*/
?>

<script>




Current.panelLoad = false;
Current.panelReportId = '0';
Current.reportName = '';
Current.canceledOn = false;
Current.performOnGoing = false;

$(document).on('click', '#ePanel', function(event) {
	event.preventDefault();
	panelLoad();
	//$('#box-panel').addClass('is-active');
});

$(document).on('click', '#ePanelClose', function(event) {
	event.preventDefault();
	$('#box-panel').removeClass('is-active');
});

$(document).on('click', '#ePanelRemove', function(event) {
	event.preventDefault();
	$('#box-panel').removeClass('is-active');
	$('#box-panel-remove-report').addClass('is-active');
	
});

$(document).on('click', '#ePanelProcess', function(event) {
	event.preventDefault();
	if (Current.tdbOn == 'y') {
		panelProcess('part_name,p_0_note', 'a');
	}
	else {
		panelProcess('part_name', 'a');
	}
});

$(document).on('click', '#eTdbOpenClosePanel', function(event) {
	event.preventDefault();
	$('#box-tdb-close').addClass('is-active');
});

$(document).on('click', '#eBoxTdbCloseCompetion', function(event) {
	event.preventDefault();
	Current.tdbClosed = 'y';
	document.getElementById('eTdbOpenClosePanel').disabled = true;
	$('#eTdbUpdate').hide();
	$('#eTdbOpenClosePanel').hide();
	$('#eTdbPremier').show();
	//$('#title-event-last-invoicing').html('Tävling stängd: <i>' + '2022-03-14' + '</i>');
	$('#title-event-last-invoicing').html('Tävling stängd <i>' + '' + '</i>');
	$('#eBoxParticipantDetailsPerform').show();
	$('#box-tdb-close').removeClass('is-active');
	let param = {};
	param._group = "Tdb";
   	param._action = "EventClose";
   	param._token = Token;
   	param._user_id = UserId;
	param._event_id = Current.eventId;
	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {}
	});
});

$(document).on('click', '#eBoxTdbCloseCancel', function(event) {
	event.preventDefault();
	$('#eTdbOpenClosePanel').prop('checked', false);
	$('#box-tdb-close').removeClass('is-active');
});

$(document).on('click', '#eTdbPremier', function(event) {
	event.preventDefault();
	$('.event-part-item-list').hide();
	$('#section-header').html('Premier');
	$('.event-part-item-prize').show();
	let param = {};
	param._group = "Tdb";
   	param._action = "PrizeList";
   	param._token = Token;
   	param._user_id = UserId;
	param._event_id = Current.eventId;
	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			Current.prizeList = result;
			// Check if exist
			var html = '<table id = "PrizeListTable" class="table" style="width:100%; margin-bottom:20px"';
			html += '<tr>';
			html += '<th style="background-color:#ffffff">Ryttare</th>';
			html += '<th style="background-color:#ffffff">Häst</th>';
			html += '<th style="background-color:#ffffff">Klass</th>';
			html += '<th style="background-color:#ffffff">Belopp</th>';
			html += '<tr>';
		
			for (var i=0; i<Current.prizeList.length; i++) {
				html += '<tr>';
					html += '<td>' + Current.prizeList[i].name + '</td>';
					html += '<td>' + Current.prizeList[i].horse_name + '</td>';
					html += '<td>' + Current.prizeList[i].competition_no + '</td>';
					Current.prizeList[i].total = Current.prizeList[i].total * -1;
					html += '<td>' + Current.prizeList[i].total + '</td>';

					html += '<td pstatus="' + Current.prizeList[i].action + '" index="' + i + '">';
					html += '<p class="control" style="margin-bottom:0">';
						html += '<span class="select is-small">';
						if (Current.prizeList[i].action == 'pric') {
							html += '<select disabled style="background-color: #ffffff" class="prize-options">';
							html += '<option value="pric">Betald</option>';
							html += '</select>';
						}
						else {
							html += '<select class="prize-options">';
								if (Current.prizeList[i].action == 'priz') {
									html += '<option value="priz" selected>Betalas</option>'; // Put live
									html += '<option value="prix">Betalas ej</option>'; // Pu live
									//html += '<option value="priz" >Betalas</option>'; // value="' + i + '
									//html += '<option value="prix" selected>Betalas ej</option>';
								}
								else if (Current.prizeList[i].action == 'prip') {
									html += '<option value="prip" selected>Pågående</option>';
								}
								else {
									html += '<option value="priz">Betalas</option>'; // value="' + i + '
									html += '<option value="prix" selected>Betalas ej</option>';
								}
								//html += '<option >Betald</option>';
							html += '</select>';
						}
						html += '</span>';
					html += '</p>';
					html += '</td>';

					html += '<td style="text-align:right;width:66px"><button index="' + i + '" class="ePrizeDetailsOpen button is-dark is-small">Detaljer</button></td>';
				html += '</tr>';
			}
				
			$('#event-prize-list').html(html);
			
		}
	});
});

$(document).on('change', '.prize-options', function(event) {
	event.preventDefault();
	let value = $(this).val();
	$(this).parent().parent().parent().attr('pstatus', value);
	// Update 
	let index = $(this).parent().parent().parent().attr('index');
	// Update inddd
	let param = {};
	param._tdb_eco_id = Current.prizeList[index].tdb_eco_id;
	param._tdb_action = value;
	param._group = 'Tdb';
   	param._action = 'PrizeStatusUpdate';
	param._token = Token;
	param._user_id = UserId;
	console.log(param);
	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			console.log(result);
		}
	});
});

$(document).on('click', '.ePrizeDetailsOpen', function(event) {
	event.preventDefault();
	let index = $(this).attr('index');
	let html = '';
	html += '<b><span style="font-size: 14px">Premiemottagare</span></b><br>' + Current.prizeList[index].name;
	html += '<br><b><span style="font-size: 14px">Ryttare</span></b><br>' + Current.prizeList[index].rider;
	html += '<br><b><span style="font-size: 14px">Häst</span></b><br>' + Current.prizeList[index].horse_name;
	html += '<br><b><span style="font-size: 14px">Klass</span></b><br>' + Current.prizeList[index].competition_no;
	html += '<br><b><span style="font-size: 14px">Beskrivning</span></b><br>' + Current.prizeList[index].description;
	html += '<br><b><span style="font-size: 14px">Belopp</span></b><br>' + (Current.prizeList[index].total * -1);
	html += '<br><b><span style="font-size: 14px">Status</span></b><br>Betald';
	$('#prize-details-text').html(html);
	$('#box-prize-details').addClass('is-active');
});

$(document).on('click', '#eBoxPrizeDetailsCancel', function(event) {
	event.preventDefault();
	$('#box-prize-details').removeClass('is-active');
});

$(document).on('click', '#ePrizeClose', function(event) {
	event.preventDefault();
	$('#event-prize-list').html('');
	$('.event-part-item-prize').hide();
	$('#section-header').html('Deltagarlista');
	$('.event-part-item-list').show();
});

$(document).on('click', '#ePrizePayout', function(event) {
	event.preventDefault();
	var counter = 0;
	var totalToPay = 0;
	Current.ecoToPay = '';
	// Current.ecoNotPay = '';
	$(".prize-options").each(function(index){
		let action = $("option:selected", this).val();
		//console.log('index: ' + index + ' ' + action);
		if (action == 'priz') {
			counter++;			
			Current.ecoToPay += Current.prizeList[index].tdb_eco_id + ','; 
			totalToPay += Current.prizeList[index].total; 
		} 
		/*
		if (action == 'prix') {
			counter++;			
			Current.ecoNotPay += Current.prizeList[index].tdb_eco_id + ','; 
		} 
		*/
	});
	
	if (Current.ecoToPay.length > 0) {
		Current.ecoToPay = Current.ecoToPay.substring(0, Current.ecoToPay.length - 1);
	}
    let html = '<table style="width:94%">';
	html += '<tr style="border-width:0"><td>Antal premieutbetalningar:</th><td>' + counter + '</td></tr>';
	html += '<tr style="border-width:0"><td>Totalt att utbetala (kr): </th><td>' + totalToPay + ' </td></tr>';
	html += '</table>';
	$('#prize-payout-text').html(html);
	if (counter == 0) {
		$('#ePayoutConfirm').hide();
		return;
	}
	else {
		$('#ePayoutConfirm').show();
	}

	$('#box-prize-payout').addClass('is-active');
	$('#ePayoutConfirm').hide();
	// $('#ePayoutConfirm').hide();
	// Check overdue
	let param = {};
	param._group = 'Company';
    param._action = 'CreditLimitCheck';
    param._amount  = totalToPay;
	param._token = Token;
   	param._user_id = UserId;
	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			let data = result;
			if (data.code == '1') {
				$('#ePayoutConfirm').show();
				$('#premmie-warning-text').html('Observera att en premieutbetalning ej går att ångra!');
			}
			else {
				let html = '<b>Premieutbetalning medges ej!</b><br>För mera information kontakta Turtle Pay AB på telefon 08-806220 eller via e-post info@turtle-pay.com.'
				$('#premmie-warning-text').html(html);
			}
		}
	});
});

$(document).on('click', '#ePayoutConfirm', function(event) {
	event.preventDefault();
	let param = {};
	param._group = 'Tdb';
	param._action = 'PrizePayout';
	param._event_id = Current.eventId;
	param._event_name = Current.eventName;
	param._token = Token;
	param._user_id = UserId;
	param._user_name = Current.companyInfo.company_name;
	param._store_id = Current.companyInfo.store_id;
	param._eco_record = Current.ecoToPay;
	// console.log(JSON.stringify(param));

	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			let data = result;
			if (data.code == '1') {
				
				let html = '<table style="width:94%">';
				html += '<tr style="border-width:0"><td>' +  data.premie_paid + 'st. premier har utbetalats:<td></tr>';
				//html += '<tr style="border-width:0"><td>' +  data.premie_not_paid + 'st. premier har inte utbetalas:<td></tr>';
				html += '</table>';
				$('#prize-payout-text').html(html);
				$('#premmie-warning-text').html('');
				$('#ePayoutConfirm').hide();
				/*
				html += data.premie_paid + 'st. premier har utbetalats<br>';
				alert(html);
				if (premie_not_paid > 0) {
					html += data.premie_not_paid + 'st. premier har inte utbetalas<br>';
				}
				$('#premmie-warning-text').html(html);
				*/
			}
			else {
				let html = '<b>Premieutbetalning kan ej göras!</b><br>För mera information kontakta Turtle Pay AB på telefon 08-806220 eller via e-post info@turtle-pay.com.'
				$('#premmie-warning-text').html(html);
			}
		}
	});
});

$(document).on('click', '#ePayoutCancel', function(event) {
	event.preventDefault();
	$('#box-prize-payout').removeClass('is-active');
	$('#eTdbPremier').trigger("click");
});

$(document).on('change', '#ePanelCanceled', function(event) {
	event.preventDefault();

	if(this.checked) {
		Current.canceledOn = true;
		Current.reportNameLast =  Current.reportName;
		Current.reportName = 'Avbokade';
	}
	else {
		Current.reportName =  Current.reportNameLast;
		Current.canceledOn = false;
	}   
	if (Current.tdbOn == 'y') {
		panelProcess('part_name,p_0_note', 'a');
	}
	else {
		panelProcess('part_name', 'a');
	}
});

$(document).on('click', '#ePanelRun', function(event) {
	event.preventDefault();
	panelReportLoad('1', false);
});

$(document).on('click', '#ePanelSave', function(event) {
	event.preventDefault();
	if (Current.panelReportId == '0') {
		$('#box-panel').removeClass('is-active');
		$('#panel-report-name').val('');
		$('#box-panel-save-report').addClass('is-active');
	}
	else {
		panelReportSave(Current.panelReportId, '', false);
	}
});

$(document).on('click', '#ePanelSaveAs', function(event) {
	event.preventDefault();
	$('#box-panel').removeClass('is-active');
	$('#panel-report-name').val('');
	$('#box-panel-save-report').addClass('is-active');
});

$(document).on('click', '#eBoxPanelRemoveReportOk', function(event) {
	event.preventDefault();
	var param = {};
   	param._group = "Event";
   	param._action = "EventItemPanelReportUpdate";
   	param._token = Token;
   	param._user_id = UserId;
	param._panel_report_id = Current.panelReportId;
	param.cancel_on = 'y';
   	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			// data = JSON.parse(result);	
			$("#ddPanelReportList option[value='" + Current.panelReportId + "']").remove();
			$('#box-panel-remove-report').removeClass('is-active');
			$('#box-panel').addClass('is-active');
			$('#ddPanelReportList').val('0').change();
			Current.panelReportId = 0;
			var cookieName = 'tpreport-' + UserId + '-' + Current.eventId;
			var cookieDate = new Date;
			cookieDate.setFullYear(cookieDate.getFullYear() +10);
			document.cookie = cookieName + '=' + Current.panelReportId + '; expires=' + cookieDate.toGMTString() + ';sameSite=lax;path=/';
	   	}
   	});	
});

$(document).on('click', '#eBoxPanelRemoveReportCancel', function(event) {
	event.preventDefault();
	$('#box-panel-remove-report').removeClass('is-active');
	$('#box-panel').addClass('is-active');
});

$(document).on('click', '#eBoxPanelSaveReportCancel', function(event) {
	event.preventDefault();
	$('#box-panel-save-report').removeClass('is-active');
	$('#box-panel').addClass('is-active');
});

$(document).on('click', '#eBoxPanelSaveReportSave', function(event) {
	event.preventDefault();
	var reportName = $('#panel-report-name').val();
	if (reportName.length < 2) {
		alert('Namn måste anges på rapport');
		return;
	}
	else {
		$('#box-panel-save-report').removeClass('is-active');
		$('#box-panel').addClass('is-active');
		panelReportSave('0', reportName, true);
	}
});

$(document).on('click', '.ePanelSort', function(event) {
	event.preventDefault();
	var sort = $(this).attr('col');
	var sort_order = $(this).attr('order');
	// switch order
	if (sort_order == 'a') {
		sort_order = 'd'
	}
	else {
		sort_order = 'a';
	}
	panelProcess(sort, sort_order);
});

$(document).on('click', '#ePrintList', function(event) {
	event.preventDefault();
	var mywindow = window.open('', 'PRINT', 'height=600,width=800');
	mywindow.document.write('<html><head></head><body>');
	mywindow.document.write($('#print-list').html());
	mywindow.document.write('</body></html>');
	mywindow.document.close(); // necessary for IE >= 10
	mywindow.focus(); // necessary for IE >= 10
	mywindow.print();
	mywindow.close();
});

$(document).on('click', '#eTdbUpdate', function(event) {
	event.preventDefault();
	if (Current.tdbOn == 'y') {
		$('#box-invoice-result').html('Här skapas faktureraunderlagen för Eventet');	
		$('#eBoxInvoiceConfirm').show();
		$('#box-invoice').addClass('is-active');
		$('#eBoxInvoiceClose').html('Avbryt');
	}
	else {
		$('#message-text-modal').html('Fakturering ej aktiverad!');
		$('#message-modal').addClass('is-active');
	}
});

$(document).on('click', '#eBoxInvoiceConfirm', function(event) {
	// UPDATED 2022-02
	event.preventDefault();
	$('#eBoxInvoiceConfirm').hide();
	$('#eBoxInvoiceClose').hide();
	$('#box-invoice-result').html('Bearbetning pågår, detta kan ta flera minuter<br><br>v.g. vänta ..... ');	

	let param = {};
	param._group = "Tdb";
	param._action = "PeopleFileCreate";
	param._token = Token;
	param._user_id = UserId;
	param._event_id = Current.eventId;
	$.ajax({ type: "POST", url: 'service2/', data: param,  
		success: function(result) {
			//alert(result);
			let data = result; 
			//let data = jQuery.parseJSON(result);
			if (data.code == '1') {
				if (data.counter > 0) {
					invoicing(data.file_name);
				}
				else {
					$('#eBoxInvoiceClose').show();
					$('#message-text-modal').html('Inget finns att hämta för tillfället!');
					$('#message-modal').addClass('is-active');
					
				}
			}
			else {
				$('#eBoxInvoiceClose').show();
				$('#message-text-modal').html('Inget finns att hämta för tillfället!');
				$('#message-modal').addClass('is-active');
			}
		},
		error: function(XMLHttpRequest, textStatus, errorThrown) {
    	 	//alert("Error: " + errorThrown);
			$('#eBoxInvoiceClose').show();
			$('#message-text-modal').html('Något fel har inträffat. <br><br>Kontakta Turtle Pay');
			$('#message-modal').addClass('is-active');
		}
	});
});

function invoicing(fileName) {

	let param = {};
	param._group = "Tdb";
	param._action = "Invoicing";
	param._token = Token;
	param._user_id = UserId;
	param._event_id = Current.eventId;
	param._file_name = fileName;
	Model.service(param, Current.serviceApi)
	.then(response => response.json())
	.then(function(data) {   
		if (data.code == '1') { 
			$('#eBoxInvoiceClose').html('Stäng');
			$('#eBoxInvoiceClose').show();
			if (data.invoiced > 0) {
				$('#box-invoice-result').html(data.invoiced + ' skapade fakturor.<br><br>Stäng och gå vidare till Utskick');	
				$('#title-event-last-invoicing').html('Senast fakturerad: <i>' + data.tdb_last + '</i>');		
			}
			else {
				$('#box-invoice-result').html('Inga nya fakturor för tillfället');		
				$('#title-event-last-invoicing').html('Senast fakturerad: <i>' + data.tdb_last + '</i>');
			}
		}
		else {
			$('#box-invoice-result').html('Något fel har uppstått.<br>Kontakata Turtle Pay');	
		}
	})
}
	// Error handling

$(document).on('click', '#eBoxInvoiceClose', function(event) {
	event.preventDefault();
	$('#box-invoice').removeClass('is-active');
});

function panelLoad() {
	/*
		@[function]
		@[desc]
		* Get the data for the panel creation
		* Create the Panel and Open it
		* If the panel has been created for the Event, open panel with last values
		@[end-desc]
		@[update]2020-09-02
		@[param]
		- No paramter 
		@[end-param] 
		@[todo9
		- Fixa so it handling both JSON and ]
	*/
	// Check Current.panelIsLoaded
	if (Current.panelLoad) {
		$('#box-panel').addClass('is-active');
		return;
	}
	var cookieName = 'tpreport-' + UserId + '-' + Current.eventId;
	var valueCookie = getCookie(cookieName);

	if(typeof valueCookie === 'undefined') { 
		Current.panelReportId = '0';
	}
	else {
		Current.panelReportId = valueCookie;
	}

	$('#eTdbUpdate').hide();
	$('#eTdbPremier').hide();
	$('#eTdbOpenClosePanel').hide();
	
	// Current.panelReportId = '16';

	Current.panelLoad = true;
	var param = {};
	param._group = "Event";
	param._action = "EventItemPanel";
	param._token = Token;
	param._user_id = UserId;
	param._event_id = Current.eventId;
	$.ajax({ type: "POST", url: 'service2/', data :param,
		success: function(result) {
			var data = JSON.parse(result);
			var panel = {};
            Current.participantTitle = data.labels.participant_title;
			panel.partOn = false;
			panel.partIndex = 0; 
			panel.partAddressOn = false;
			panel.boxNumber = 0;
			panel.partDateOfBirthOn = false;
			panel.partCollectSparOn = false;
			panel.noteIndex = -1;
			panel.notes = Array();
			// Check if the participant_address in on for each 
			$('.panel-address-on').hide();
			$('#panel-part').hide();
			for (var i=0; i<data.fields.length; i++) {
				// if (data.fields[i].participant_address_on == 'y' && panel.partOn == false) {
				if (data.fields[i].participant_address_on == 'y') {
					panel.partIndex = i;
					panel.partOn = true;
					panel.partAddressOn = true;
					
				}
				if (data.fields[i].date_of_birth_on == 'y') {
					panel.partOn = true;
					panel.partDateOfBirthOn = true;
				}
				
				if (data.fields[i].collect_spar_on  == 'y') {
					panel.partOn = true;
					panel.partCollectSparOn = true;
				}	
				if (data.fields[i].note_on  == 'y') {
					//panel.partOn = true;
					panel.noteOn = true;
					panel.noteIndex++;
					panel.notes[panel.noteIndex] = {};
					panel.notes[panel.noteIndex].tag = 'p_' + i + '_note';
					panel.notes[panel.noteIndex].label = data.fields[i].note_label;
				}
			}
			
			if (panel.partOn) {
				panelHtml = '';
				if (panel.partAddressOn || panel.partCollectSparOn) {
					$('#participant-box-title2').text(Current.participantTitle + 'uppgifter');
					panelHtml += '<div class="columns modal-columns panel-address-on">';
						panelHtml += '<div class="column panel-checkbox-d_address" style="padding-top:0; padding-bottom:0">';
							panelHtml += '<label class="checkbox ">';
								panelHtml += '<input label="Adress" class="is-primary" id="d_address" type="checkbox">&nbsp;&nbsp;Adress';
							panelHtml += '</label>';
						panelHtml += '</div>';
						panelHtml += '<div class="column panel-checkbox-d_postcode" style="padding-top:0; padding-bottom:0">';
							panelHtml += '<label class="checkbox ">';
								panelHtml += '<input label="Postnr" class="is-primary" id="d_postcode" type="checkbox">&nbsp;&nbsp;Postnr';
							panelHtml += '</label>';
						panelHtml += '</div>';
						panelHtml += '<div class="column panel-checkbox-d_city" style="padding-top:0; padding-bottom:0">';
							panelHtml += '<label class="checkbox ">';
								panelHtml += '<input label="Ort" class="is-primary" id="d_city" type="checkbox">&nbsp;&nbsp;Ort';
							panelHtml += '</label>';
						panelHtml += '</div>';
						if (panel.partAddressOn) {
							panelHtml += '<div class="column panel-checkbox-d_email" style="padding-top:0; padding-bottom:0">';
								panelHtml += ' <label class="checkbox ">';
									panelHtml += '<input label="E-Mail" class="is-primary" id="d_email" type="checkbox">&nbsp;&nbsp;E-Mail';
								panelHtml += '</label>';
							panelHtml += '</div>';
							panelHtml += '</div>';  // End first row
						panelHtml += '<div class="columns modal-columns">';
							panelHtml += '<div class="column panel-checkbox-d_mobile" style="padding-top:0; padding-bottom:0">';
								panelHtml += '<label class="checkbox ">';
									panelHtml += '<input label="Mobil" class="is-primary" id="d_mobile" type="checkbox">&nbsp;&nbsp;Mobil';
								panelHtml += '</label>';
							panelHtml += '</div>';
						panel.boxNumber++; 
					}
					else { // Empy column when just has Spar
						panelHtml += '<div class="column panel-checkbox-d_email" style="padding-top:0; padding-bottom:0">';
						panelHtml += '</div>';
						panelHtml += '</div>'; // End firs row
					}
				}

				if (panel.partDateOfBirthOn) {
					if (panel.boxNumber == 0) {
						panelHtml += '<div class="columns modal-columns">';	
					}
					panelHtml += '<div class="column panel-checkbox-d_date_of_birth" style="padding-top:0; padding-bottom:0">';
					panelHtml += '<label class="checkbox ">';
					panelHtml += '<input label="Födelsedatum" class="is-primary" id="d_date_of_birth" type="checkbox">&nbsp;&nbsp;Födelsedatum';
					panelHtml += '</label>';
					panelHtml += '</div>';
					panel.boxNumber++; 
				}
				
				if (panel.partCollectSparOn) {
					if (panel.boxNumber == 0) {
						panelHtml += '<div class="columns modal-columns">';
					}
					panelHtml += '<div class="column" style="padding-top:0; padding-bottom:0">';
					panelHtml += '<label class="checkbox ">';
					panelHtml += '<input label="Personnr" class="is-primary" id="d_personno" type="checkbox">&nbsp;&nbsp;Personnr';
					panelHtml += '</label>';
					panelHtml += '</div>';
					panel.boxNumber++; 
				}
				
				if (panel.boxNumber > 0 && panel.boxNumber < 4) {
					for (var i=0; i<4-panel.boxNumber; i++){
						panelHtml += '<div class="column" style="padding-top:0; padding-bottom:0">';
						panelHtml += '</div>';
					}
					panelHtml += '</div>';
				}
				
				panelHtml += '<hr style="background-color: #666666; height: 0.5px; margin: 8px 0 6px 0">';
				
				$('#panel-part').append(panelHtml);
				$('#panel-part').show();
			}

			var html = '';
			for (var i=0; i<data.olabels.length; i++) {	
				
				if (data.olabels[i].show == 'y') {
					html += '<div class="columns modal-columns" style="margin-bottom: 0;">';
						html += '<div class="column" style="padding-top:0; padding-bottom:0">';
							html += '<label class="checkbox">';
								html += '<input label="' + data.olabels[i].text + '" class="is-primary" id="s_' + i + '" type="checkbox">&nbsp;&nbsp;' + data.olabels[i].text + '';
							html += '</label>';
						html += '</div>';
						html += '<div class="column" style="padding-top:0; padding-bottom:0">';
							html += '<label class="checkbox italic">';
								html += '<input label="Belopp" class="is-primary" id="v_' + i + '" type="checkbox">&nbsp;&nbsp;Belopp';
							html += '</label>';
						html += '</div>';
					html += '</div>';
				}
				/*
				
					html += '<div class="columns modal-columns" style="margin-bottom: 0;">';
						html += '<div class="column" style="padding-top:0; padding-bottom:0">';
							html += '<label class="checkbox">';
								html += '<input label="' + data.olabels[i].text + '" class="is-primary" id="s_' + i + '" type="checkbox">&nbsp;&nbsp;' + data.olabels[i].text + '';
							html += '</label>';
						html += '</div>';
						html += '<div class="column" style="padding-top:0; padding-bottom:0">';
							html += '<label class="checkbox italic">';
								html += '<input label="Belopp" class="is-primary" id="v_' + i + '" type="checkbox">&nbsp;&nbsp;Belopp';
							html += '</label>';
						html += '</div>';
					html += '</div>';
				*/
            }
                
            if (panel.noteOn) {
                var boxNumber = -1;
                var boxFirst = true;
                for (var i=0; i<panel.notes.length; i++) {
                    boxNumber++;
                    if (boxNumber == 2) {
                        boxNumber =0;
                    }
                    if (boxNumber == 0) {
                        if (boxFirst == false) {
                            html += '</div>';
                        }
                        boxFirst = false;
                        html += '<div class="columns modal-columns">';
                    }
                    html += '<div class="column" style="padding-top:0; padding-bottom:0">';
                        html += '<label class="checkbox ">';
                            html += '<input label="' + panel.notes[i].label + '" class="is-primary" id="' + panel.notes[i].tag + '" type="checkbox">&nbsp;&nbsp;' +panel.notes[i].label;
                        html += '</label>';
                    html += '</div>';
                }
                if (boxNumber == 0) {
                    html += '<div class="column" style="padding-top:0; padding-bottom:0"></div>';
                    html += '</div>';
                }
                else {
                    html += '</div>';
                }
            }
                
			$('#panel-selection').append(html);

			var html ='';
			for (var i=0; i<data.fields.length; i++) {
				html += '<div class="columns modal-columns">';
					html += '<div class="column" style="padding-top:0; padding-bottom:0">';
						html += '<h3 style="font-style:italic">' + data.fields[i].ref + '</h3>';
					html += '</div>';
				html += '</div>';

				html += '<div class="columns modal-columns">';
					html += '<div class="column" style="padding-top:0; padding-bottom:0">';
						html += '<label class="checkbox ">';
							html += '<input label="Fakturamottagare" class="is-primary" id="p_' + i + '_people_name" type="checkbox">&nbsp;&nbsp;Fakturamottagare';
						html += '</label>';
					html += '</div>';
                    // data.fields[i].email_label
					html += '<div class="column" style="padding-top:0; padding-bottom:0">';
						html += '<label class="checkbox">';
							html += '<input label="Fakturamottagare e-post" class="is-primary" id="p_' + i + '_email" type="checkbox">&nbsp;&nbsp;Fakturamottagare e-post';
						html += '</label>';
					html += '</div>';
                    if (data.fields[i].mobile_on == 'y') {
                        html += '<div class="column" style="padding-top:0; padding-bottom:0">';
                            html += '<label class="checkbox">';
                                html += '<input label="Fakturamottagare mobil" class="is-primary" id="p_' + i + '_mobile" type="checkbox">&nbsp;&nbsp;Fakturamottagare mobil';
                            html += '</label>';
                        html += '</div>';
                    }
                    else {
                        html += '<div class="column" style="padding-top:0; padding-bottom:0"></div>';
                    }


				html += '</div>';

				html += '<div class="columns modal-columns">';

				html += '<div class="column column" style="padding-top:0; padding-bottom:0">';
						html += '<label class="checkbox ">';
							html += '<input label="' + 'Trans.datum' + '" class="is-primary" id="p_' + i + '_trans_date" type="checkbox">&nbsp;&nbsp;' + 'Trans.datum';
						html += '</label>';
					html += '</div>';

					html += '<div class="column column is-two-thirds" style="padding-top:0; padding-bottom:0">';
						html += '<label class="checkbox ">';
							html += '<input label="' + data.fields[i].ref_label + '" class="is-primary" id="p_' + i + '_referens" type="checkbox">&nbsp;&nbsp;' + data.fields[i].ref_label;
						html += '</label>';
					html += '</div>';
				html += '</div>';
				
				if (data.fields[i].infobox_1_on == 'y' ) {
					html += '<div class="columns modal-columns">';
						html += '<div class="column" style="padding-top:0; padding-bottom:0">';
							html += '<label class="checkbox ">';
								html += '<input label="' + data.fields[i].infobox_1_label + '" class="is-primary" id="p_' + i + '_infobox_1" type="checkbox">&nbsp;&nbsp;' + data.fields[i].infobox_1_label;
							html += '</label>';
						html += '</div>';
					html += '</div>';
				}

				if (data.fields[i].infobox_2_on == 'y' ) {
					html += '<div class="columns modal-columns">';				
						html += '<div class="column" style="padding-top:0; padding-bottom:0">';
							html += '<label class="checkbox ">';
								html += '<input label="' + data.fields[i].infobox_2_label + '" class="is-primary" id="p_' + i + '_infobox_2" type="checkbox">&nbsp;&nbsp;' + data.fields[i].infobox_2_label + '';
							html += '</label>';
						html += '</div>';
					html += '</div>';
				}  
			}

			$('#panel-webform-data').append(html);
			panelLoadPart2();
			//$('#box-panel').addClass('is-active');
		}
	});
}

function panelLoadPart2() {
	var param = {};
  	param._group = "Event";
   	param._action = "EventItemPanelReportList";
   	param._token = Token;
   	param._user_id = UserId;
   	param._event_id = Current.eventId;
   	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			
			Current.panelReports = JSON.parse(result);
		
			var html = '';
			html += '<div class="select" style="width:100%">';
			html += '<select id="ddPanelReportList" style="width:100%">';
			html += '<option value="0">-- Välj --</option>';
			if (Current.panelReports.length > 0) {
				for (var i=0; i<Current.panelReports.length; i++) {
					html += '<option value="' + Current.panelReports[i].panel_report_id + '">' +Current.panelReports[i].report_name + '</option>';
				}
			}
			html += '</select>';
			html += '</div>';
			$('#panel-report-list').html(html); 
			
			if ( Current.panelReportId != '0') {
				$("#ddPanelReportList").val(Current.panelReportId).change();
				panelReportLoad (Current.panelReportId, true);
			}

			else if (Current.panelReports.length > 0 && Current.panelReports.length == 1) {
				$("#ddPanelReportList").val(Current.panelReports[0].panel_report_id).change();
				panelReportLoad (Current.panelReports[0].panel_report_id, true);
			}
			else {
				var param2 = {};
				param2._group = "Event";
				param2._action = "EventItemList2";
				param2._token = Token;
				param2._user_id = UserId;
				param2._event_id = Current.eventId;
				if (Current.tdbOn == 'y') {
					param2._fields = 'part_name,p_0_note';
					param2._header = Current.participantTitle + ',Häst';
				}
				else {
					param2._fields = 'part_name';
					param2._header = Current.participantTitle;
				}
				param2._sort = 'part_name';
				param2._sort_order = 'a';
			 // 'Deltagare'; // Sätt dynamisk
				param2._part_sum = 'n';
				// avräkning
				param._abandoned = 'y';
				panelReport(param2);
			}
	   	}
   	});
}

function panelProcess(sort, sort_order) {
	var labels = '';
	var fields = '';
	
	var totalOn = false;

	$('#panel-form input:checked').each(function(index, value){
		//$(this).val(data[$(this).attr('name')]);
		if ($(this).attr('id') == '_part_sum') {
			totalOn = true;
		}
		labels += $(this).attr('label') + ',';
		fields += $(this).attr('id') + ',';
	});
	// FIXAS

	//if (Current.tdbOn == 'y') {
		//$('#p_0_note').prop('checked', true);
		// fields =  'part_name,p_0_note,' + fields; 	
		// labels = Current.participantTitle + ',Häst,' + labels;	
	// }
	// else {
		fields =  'part_name,' + fields; 
		labels = Current.participantTitle + ',' + labels;
	// }
	fields = fields.substring(0, fields.length - 1);
	labels = labels.substring(0, labels.length - 1);
	
	var param = {};
	param._group = "Event";
	param._action = "EventItemList2";
	param._token = Token;
	param._user_id = UserId;
	param._event_id = Current.eventId;
	param._fields = fields; // 's_0,s_1,__total,p_0_people_name,p_0_mobile,p_0_email';
	param._sort = sort;
	param._sort_order = sort_order;
	param._header = labels; // Anmälningsavgift,Letionsavgift,Summa,Betalare,Mobil,E-post';
	if (totalOn) {
		param._part_sum = 'y';
	}
	else {
		param._part_sum = 'n';
	}

	// Current.canceledOn = true;
	// avräkning
	// param._abandoned = 'y';


	panelReport(param);
	$('#box-panel').removeClass('is-active');
}

function panelReport(param) {
	
	if (Current.canceledOn) {
		param._participant_status = 'r';
	}
	else {
		param._participant_status = 'c';
	}

	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			var header = param._header.split(',');
			var fields = param._fields.split(',');
			data = JSON.parse(result);
			if (data.code == "2") {
				if ($('#ePanelCanceled').prop('checked')) {
					// Current.canceledOn = false;
					$('#ePanelCanceled').prop('checked', false);
					$('#message-text-modal').html('Inga avbokade finns!');
					$('#message-modal').addClass('is-active');
					return;
				} 
			}
			else {
				if (Current.reportName.length == 0) {
					$('#title-report-name').html('Deltagarlista');
				}
				else {
					$('#title-report-name').html(Current.reportName);
				}
				$('#title-event-name').html('Event: <i>' + Current.eventName + '</i>'); 
				$('#title-event-counter').html('Antal: <i>' + Current.counter + '</i>'); 
			
			//if (data.code == '1') {
				var html = '<table id = "EventListTable" class="table" style="width:100%; margin-bottom:20px"';
				html += '<tr>';
				//$.each(data.header, function(index, value) {
				$.each(header, function(index, value) {
					var sortOrder = 'o';
					if (param._sort == fields[index]) {	
						sortOrder = param._sort_order;
					} 
					html += '<th class="ePanelSort" col="' + fields[index] + '" order="' + sortOrder + '" style="cursor:pointer">' + value + '</th>';
				});
				html += '<th></th>'; // Open button
				html += '</tr>';
				for (var i=0; i<data.report.length; i++) {
					html += '<tr>';
					$.each(data.report[i], function(index, value) {
						if (index == '_base_participant_id') {
							// skip
						}
						else {
							html += '<td>' + value + '</td>';
						}
					});
					
					html += '<td style="text-align:right;width:66px"><button e-item="' + data.report[i]._base_participant_id + '" class="eParticipantDetails button is-dark is-small">Öppna</button></td>';
					
					html += '</tr>';
				}
				$('#event-item-list').html(html);
			}
			if (Current.tdbOn == 'y') {	
				var param2 = {};
				param2._group = "Event";
				param2._action = "EventGetTdbLast";
				param2._token = Token;
				param2._user_id = UserId;
				param2._event_id = Current.eventId;
				
				$.ajax({ type: "POST", url: 'service2/', data: param2,
					success: function(result) {
						data = JSON.parse(result);
						Current.tdbClosed =  data.tdb_closed;
						
						$('#panel-selection').hide();
						$('.part-sum').hide();
						if (Current.tdbClosed == 'n') { // } && UserId == 69) { // SPÄRR
							$('#eTdbUpdate').show();
							$('#eTdbOpenClosePanel').show();
							$('#eBoxParticipantDetailsPerform').hide();
							$('#title-event-last-invoicing').html('Senast fakturerad: <i>' + data.tdb_last + '</i>');
							$('#title-event-last-invoicing').show()
						}
						else {
							$('#eTdbPremier').show();
							$('#eBoxParticipantDetailsPerform').show();
							//$('#title-event-last-invoicing').html('Tävling stängd: <i>' + '2022-03-14' + '</i>');
							$('#title-event-last-invoicing').html('Tävling stängd <i>' + '' + '</i>');
							$('#title-event-last-invoicing').show()
						}	
						$('#eTdbClosePanel').show();
					}
				});
			}
			else {
				$('#title-event-last-invoicing').hide();
				Current.tdbClosed = 'n';
				$('#panel-selection').show();
				$('.part-sum').show();
				$('#eTdbClosePanel').hide();
			}
			
		}		
	});	
}

function panelReportLoad (reportId, runReport) {
   
	Current.panelReportId = reportId;
	//document.cookie = "tpreport=" + Current.panelReportId + ';sameSite=lax;path=/';
	var cookieName = 'tpreport-' + UserId + '-' + Current.eventId;
	var cookieDate = new Date;
	cookieDate.setFullYear(cookieDate.getFullYear() +10);
	document.cookie = cookieName + '=' + Current.panelReportId + '; expires=' + cookieDate.toGMTString() + ';sameSite=lax;path=/';

	var param = {};
	param._group = "Event";
	param._action = "EventItemPanelReportLoad";
	param._token = Token;
	param._user_id = UserId;
	param._panel_report_id = reportId;
	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			data = JSON.parse(result);
			var fields = data.fields.split(',');
			Current.reportName = data.report_name;
			$('#panel-form input:checked').each(function(index, value){
				$(this).prop( "checked", false);
			});

			for (var i=0; i<fields.length; i++) {
				$( '#' +  fields[i]).prop( "checked", true );
			} 

			if (runReport) {
				var param2 = {};
				param2._group = "Event";
				param2._action = "EventItemList2";
				param2._token = Token;
				param2._user_id = UserId;
				param2._event_id = Current.eventId;
				param2._fields = data.fields;
				param2._sort = data.fields_sort;
				param2._sort_order = data.sort_order;

				// Get labels
				var labels = '';
				$('#panel-form input:checked').each(function(index, value){
					//$(this).val(data[$(this).attr('name')]);
					labels += $(this).attr('label') + ',';
				});
				labels = 'Deltagare,' + labels;
				labels = labels.substring(0, labels.length - 1);

				param2._header = labels;
    			//"cancel_on": "n",
				if (data.part_sum_on == 'y') {
					param2._part_sum = 'y';
				}
				else {
					param2._part_sum = 'n';
				}
				// $('#box-panel').removeClass('is-active');

				// avräkning
				param._abandoned = 'y';

				panelReport(param2);
			}
		}
	});
}

function panelReportLoadList(selectedReportId) {
	var param = {};
  	param._group = "Event";
   	param._action = "EventItemPanelReportList";
   	param._token = Token;
   	param._user_id = UserId;
   	param._event_id = Current.eventId;
   	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			
			Current.panelReports = JSON.parse(result);
			if (Current.panelReports.length > 0) {
				var html = '';
				html += '<div class="select" style="width:100%">';
				html += '<select id="ddPanelReportList" style="width:100%">';
				html += '<option value="0">-- Välj --</optioon>';
				for (var i=0; i<Current.panelReports.length; i++) {
					html += '<option value="' + Current.panelReports[i].panel_report_id + '">' +Current.panelReports[i].report_name + '</option>';
				}
                html += '</select>';
                html += '</div>';
				$('#panel-report-list').html(html); 
				$("#ddPanelReportList").val(selectedReportId).change();
				$('#panel-form input:checked').each(function(index, value){
					$(this).prop( "checked", false);
				});
				// Current.panelReportId = 0;
			}
		}
   });
}

$(document).on('change', '#ddPanelReportList', function(event) {
	event.preventDefault();
	var reportId = $(this).val();
	if (reportId == '0') {
		$('#panel-form input:checked').each(function(index, value){
				$(this).prop( "checked", false);
		});
		Current.panelReportId = 0; 
	}
	else {
		panelReportLoad(reportId, false);
	}
});	

function panelReportSave (reportId, reportName, reload) {
   
	Current.reportListReload = reload;

   	var param = {};
   	param._group = "Event";
   	param._action = "EventItemPanelReportUpdate";
   	param._token = Token;
   	param._user_id = UserId;
   	if (reportId == '0') {
		param._panel_report_id = '0';
		param.report_name = reportName;
   	}
   	else {
   		param._panel_report_id = reportId;// Current.PanelReportId;
   	}
   	param.event_id = Current.eventId;
   	param.part_sum_on = 'n';
	   if (Current.tdbOn == 'y') {
		param.fields =  'part_name,p_0_note,'; 		
	}
	else {
		param.fields =  'part_name,'; 
	}
	param.headers = "Deltagare,";
   	$('#panel-form input:checked').each(function(index, value){
		if ($(this).attr('id') == '_part_sum') {
			param.part_sum_on = 'n';
		}
		param.headers += $(this).attr('label') + ',';
		param.fields += $(this).attr('id') + ',';
	});
   	param.fields = param.fields.substring(0, param.fields.length - 1);
	param.headers = param.headers.substring(0, param.headers.length - 1);

   	param.fields_sort = 'part_name';
   	param.sort_order = 'a';

   	// param.cancel_on
    
   	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			data = JSON.parse(result);
			if (data.hasOwnProperty("id") ) {
				Current.panelReportId = data.id;
			}
			if (Current.reportListReload) {
				panelReportLoadList(data.id);
			}
			$('#save-message').show();
			setTimeout(showSaveMessage, 8000);
	   	}
   	});
}

function showSaveMessage() {
	$('#save-message').hide();
}

$(document).on('click', '.eParticipantDetails', function(event) {
	event.preventDefault();
	Current.participantId = $(this).attr('e-item');
	companyCheckLimit();
});

function companyCheckLimit() {
	var param = {};
	param._group = "Event";
	param._action = "CheckLimit";
	param._token = Token;
	param._user_id = UserId;
	$.ajax({ type: "POST", url: 'service2/', data: param, 
		success: function(result) {
			let data = jQuery.parseJSON(result);
			participantDetails(data.code);
		}
	});
}

function participantDetails(creditOn) {

	$('#eBoxParticipantDetailsPerform').attr('participant-id',  Current.ParticipantId);

	var param = {};
	param._group = "Event";
	param._action = "ParticipantDetails";
	param._token = Token;
	param._user_id = UserId;
	param._tdb_on = Current.tdbOn;
	param._participant_id = Current.participantId;
	$.ajax({ type: "POST", url: 'service2/', data: param, 
		success: function(result) {
			Current.participantDetails = jQuery.parseJSON(result);
			//$('#box-participant-cancel-people-name').html(Current.participantDetails.first_name + ' ' + Current.participantDetails.last_name);
			// 2021-10-07
			var header = Current.participantDetails.first_name + ' ' + Current.participantDetails.last_name;
			if (Current.tdbOn == 'y') {
				header += ' - ' + Current.participantDetails.note;;
			}
			$('#box-participant-cancel-people-name').html(header);
			
			var total = 0;
			var html2 = '';
			
			for (var i=0; i<Current.participantDetails.option.length; i++) {
			
				html2 += '<div class="columns">'
					html2 += '<div class="column is-5" style="padding-bottom:0; padding-top: 0; margin:0">';
						html2 += '<label class="checkbox modal-checkbox" style="font-size:14px!important">';
							html2 += Current.participantDetails.option[i].option_text;
						html2 += '</label>';
					html2 += '</div>';

					html2 += '<div class="column is-2" style="padding-bottom:0; padding-top: 0; margin:0">';
						if (Current.participantDetails.option[i].event_option_status == 'r') {
							var checked = 'checked';
						}
						else {
							var checked = '';
						}
						if (Current.tdbOn == 'y' && Current.tdbClosed == 'n') {
							html2 += '&nbsp;&nbsp;&nbsp;<input disabled ' + checked + ' class="is-primary is-small modal-checkbox abandoned-cancel" style="color: #000000" index="' + i + '" type="checkbox">';
						} 
						else {
							html2 += '&nbsp;&nbsp;&nbsp;<input ' + checked + ' class="is-primary is-small modal-checkbox abandoned-cancel" style="color: #000000" index="' + i + '" type="checkbox">';
						}
					html2 += '</div>';
					
					if (creditOn == '1') {
						if (Number(Current.participantDetails.option[i].value) < 1) {
							var disabled = 'disabled';
						}
						else {
							var disabled = '';
						}
						
						if (Current.tdbOn == 'y' && Current.tdbClosed == 'n') {
							disabled = 'disabled';
						} 
						html2 += '<div class="column is-3" style="padding-bottom:0; padding-top: 0; margin:0">';
							html2 += '<label class="checkbox modal-checkbox" style="font-size:14px!important">';
								html2 += '&nbsp;&nbsp;&nbsp;<input ' + disabled + ' class="is-primary is-small eAbandonedCredit" style="color: #000000" index="' + i + '" type="checkbox">&nbsp;&nbsp;';
								html2 += '<input type="text" style="width: 80px;font-size:14px!important; display:none" class="modal-input only-numeric eAbandonedCreditAmount" id="abid-' + i + '" index="' + i + '" value="' + Current.participantDetails.option[i].value + '"/>';
							html2 += '</label>';
						html2 += '</div>';
						html2 += '<div class="column is-2" style="padding-bottom:0; padding-top: 0; margin:0">';
							html2 += '<label id="abvid-' + i + '" class="checkbox" style="font-size:14px!important; color: "#888888">&nbsp;&nbsp;&nbsp;&nbsp;';
								html2 += Current.participantDetails.option[i].value;
							html2 += '</label>';
						html2 += '</div>';
					
						total = total + Number(Current.participantDetails.option[i].value);
					}
				html2 += '</div>';
			}
			
			html2 += '<div class="columns" id="ab-warning-container" style="display:none">';
				html2 += '<div class="column" style=" padding-top: 16px; margin:0">';
					html2 += '<div id="ab-error" style="font-size: 14px; font-weight: bold; font-style:italic; color: #5a7d22; text-align:center; padding-bottom:6px;"></div>';
					if (creditOn == '1') {  
						html2 += '<div style="font-size: 14px; font-style:italic; color: #5a7d22; text-align:center">Observera att en kreditering ej går att ångra!</div>';
					}
				html2 += '</div>';
			html2 += '</div>';
			
			var html = '';

			html += '<div class="columns" style="border-bottom: 1px #cccccc solid">';
				html += '<div class="column is-5" style="padding-bottom:0; padding-top: 0; margin:0">';
					html += '<label class="modal-label">Urval</label>';
				html += '</div>';
				html += '<div class="column is-2" style="padding-bottom:0; padding-top: 0; margin:0">';
					html += '<label class="modal-label">Avboka</label>';
				html += '</div>';
				if (creditOn == '1') {
					html += '<div class="column is-3" style="padding-bottom:0; padding-top: 0; margin:0">';
					html += '<label class="modal-label">Kreditera</label>';
					html += '</div>';
					html += '<div class="column is-2" style="padding-bottom:0; padding-top: 0; margin:0">';
						html += '<label class="modal-label">Belopp</label>';
					html += '</div>';
				}
			html += '</div>';

			html += html2;
			
			$('#box-participant-details-selections').html(html);
			$('#box-participant-details').addClass('is-active');
		}
	});
	//$('#box-panel').addClass('is-active');
}

$(document).on('change', '.eAbandonedCredit', function(event) {
	event.preventDefault();
	var index = $(this).attr('index');
	var id = 'abid-' + index;
	if ($(this).prop('checked')) {
		$('#' + id).val(Current.participantDetails.option[index].value);
		$('#' + id).show();
		$('#ab-warning-container').show();
	}
	else {
		$('#' + id).val('');
		$('#' + id).hide();
		$('#abvid-' + index).html('&nbsp;&nbsp;&nbsp;&nbsp;' + Current.participantDetails.option[index].value);
		$('#ab-error').hide();

		var isOn = false;
		$('.eAbandonedCredit').each(function() {
			if (this.checked ) {		
				isOn = true;
			}
		});
		if (isOn ==false) {
			$('#ab-warning-container').hide();
		} 
	}
	
});

$(document).on('focusout', '.eAbandonedCreditAmount', function(event) {
	event.preventDefault();
	
	var index = $(this).attr('index');
	var valueText = $(this).val();
	if (valueText.length < 1) {
		$('#ab-error').html('Ej giltigt värde:!');
		$('#ab-error').show();
		//$(this).val('');
		return;
	}
	
	var value = Number(valueText);
	var orgValue = Current.participantDetails.option[index].value;
	if (value > orgValue) {
		$('#ab-error').html('För stort värde!');
		$('#ab-error').show();
		//$(this).val('');
		return;
	}

	if (value <= 0 ) {
		$('#ab-error').html(value + ' kan ej krediteras!');
		$('#ab-error').show();
		//$(this).val('');
		return;
	}
	$('#ab-error').hide();

	var newValue = orgValue - value;
	Current.participantDetails.option[index].newValue = newValue;
	$('#abvid-' + index).html('&nbsp;&nbsp;&nbsp;&nbsp;' + newValue);
	$('#abvi-' + index).hide();
	
});

function checkTheAb() {

	var reply = true;
	var totalNow =0;
	var totalCredit = 0;
	$('.eAbandonedCredit').each(function() {
		var index = $(this).attr('index');
		totalNow += Number(Current.participantDetails.option[index].value);
		if (this.checked ) {
			var id='#abid-' + index;
			var valueText = $(id).val();
			if (valueText.length < 1) {
				$('#ab-error').html('Ej giltigt värde:!');
				$('#ab-error').show();
				$(this).val('');
				reply = false;
			}
			var value = Number(valueText);
			totalCredit += value;
			
			var orgValue = Current.participantDetails.option[index].value;
			if (value > orgValue) {
				$('#ab-error').html('För stort värde!');
				$('#ab-error').show();
				reply = false;
			}
			if (value <= 0 ) {
				$('#ab-error').html(value + ' kan ej krediteras!');
				$('#ab-error').show();
				reply = false;
			}
			var newValue = orgValue - value;
			Current.participantDetails.option[index].newValue = newValue;
		}
	});
	if (reply) {
		$('#ab-error').hide();
	}

	// alert(totalCredit + " : " + totalNow);
	var diff = totalNow - totalCredit;
	if (diff < 0) {
		$('#ab-error').html('Max totalbelopp som kan krediteras är ' + totalNow);
		$('#ab-error').show();
		reply = false;
	}

	return reply;
}

$(document).on('click', '#eBoxParticipantDetailsPerform', function(event) {
	event.preventDefault();
	
	if (Current.performOnGoing) {
		return;
	}
	else {
		Current.performOnGoing = true;
	}
	
	if (checkTheAb() == false) {
		Current.performOnGoing = false;
		return;
	}

	var participantId = Current.participantId; //  = $(this).attr('participant-id');

	var onCancel = 'n';
	var listCancelIds = '';
	var onUncancel = 'n';
	var listUncancelIds = '';
	$('.abandoned-cancel').each(function() {
		var index = $(this).attr('index');
		if (this.checked && Current.participantDetails.option[index].event_option_status == 'c') {
			onCancel = 'y'; 
			listCancelIds += Current.participantDetails.option[index].event_option_id + ',';
		}
		else if (!this.checked && Current.participantDetails.option[index].event_option_status == 'r') {
			onUncancel = 'y'; 
			listUncancelIds += Current.participantDetails.option[index].event_option_id + ',';
		}	
	});

	if (onCancel == 'y') {
		listCancelIds = listCancelIds.substring(0, listCancelIds.length - 1);
	}

	if (onUncancel == 'y') {
		listUncancelIds = listUncancelIds.substring(0, listUncancelIds.length - 1);
	}

	var onAb = 'n';
	var paramAbIds = ''; 
	var paramAbValues = '';
	var paramAbCvalues = '';

	$('.eAbandonedCredit').each(function() {
		if (this.checked ) {
			onAb = 'y';
			var index = $(this).attr('index');
			paramAbIds += Current.participantDetails.option[index].event_option_id + ',';
			paramAbValues += Current.participantDetails.option[index].newValue + ',';

			var cValue = Current.participantDetails.option[index].value - Current.participantDetails.option[index].newValue;
			paramAbCvalues += cValue + ',';
		}
	});
	var paramAbNvalues = '';
	if (onAb == 'y') {
		paramAbIds = paramAbIds.substring(0, paramAbIds.length - 1);
		paramAbValues = paramAbValues.substring(0, paramAbValues.length - 1);
		paramAbCvalues = paramAbCvalues.substring(0, paramAbCvalues.length - 1);
	}
	
	var param = {};
	param._group = "Event";
	param._action = "ParticipantDetailsPerform";
	param._token = Token;
	param._user_id = UserId;
	param._on_cancel = onCancel;
	param._list_cancel_ids = listCancelIds;
	param._on_uncancel = onUncancel;
	param._list_uncancel_ids = listUncancelIds;
	param._participant_id = participantId;
	param._on_ab = onAb;
	param._ab_ids = paramAbIds;
	param._ab_values = paramAbValues;
	param._ab_cvalues = paramAbCvalues;
	// param._ab_nvalues = paramAbNvalues;


	$.ajax({ type: "POST", url: 'service2/', data: param, 
		success: function(result) {
			let data = jQuery.parseJSON(result);
			$('#box-participant-details').removeClass('is-active');
			Current.performOnGoing = false;
			if (data.code == '3') {
				$('#message-text-modal').html('Kreditering medges ej!');
				$('#message-modal').addClass('is-active');
			}
			if (Current.tdbOn == 'y') {
				panelProcess('part_name,p_0_note', 'a');
			}
			else {
				panelProcess('part_name', 'a');
			}
		}
	});
});

$(document).on('click', '#eBoxParticipantDetailsClose', function(event) {
	event.preventDefault();
	$('#box-participant-details').removeClass('is-active');
});

$(document).on('keypress', '.only-numeric', function (e) {
	var keyCode = e.which ? e.which : e.keyCode     
	if (!(keyCode >= 48 && keyCode <= 57)) {
		return false;
	}
});

$(document).on('keypress', '.only-numeric-neg', function (e) {
	var keyCode = e.which ? e.which : e.keyCode     
	if (keyCode == 45) {
		// return true; - tecken
	} 
	else if (!(keyCode >= 48 && keyCode <= 57)) {
		return false;
	}
});


function getCookie(name) {
  const value = `; ${document.cookie}`;
  const parts = value.split(`; ${name}=`);
  if (parts.length === 2) return parts.pop().split(';').shift();
}


function download_csv(csv, filename) {
    var csvFile;
    var downloadLink;

    // CSV FILE
	//csvFile = new Blob([csv], {type: "text/plain;charset=utf-8"});
	csvFile = new Blob(["\uFEFF"+csv], {type: 'text/csv; charset=utf-8'});
	//var blob = new Blob(["Hello, world!"], {type: "text/plain;charset=utf-8"});
    // Download link
    downloadLink = document.createElement("a");

    // File name
    downloadLink.download = filename;

    // We have to create a link to the file
    downloadLink.href = window.URL.createObjectURL(csvFile);

    // Make sure that the link is not displayed
    downloadLink.style.display = "none";

    // Add the link to your DOM
    document.body.appendChild(downloadLink);

    // Lanzamos
    downloadLink.click();
}

function exportPrizeTableToCsv(filename) {
	var csv = [];
	
	// -- var d = new Date();
	// -- var dateNow = getTimeStamp();
	// -- csv.push(Current.eventName + ';;'+ dateNow + '\n'); 
	csv.push("Premielista" + '\n'); 
	csv.push("Ryttare;Häst;Klass;Belopp;Status"); 
	var rows = document.querySelectorAll('#PrizeListTable tr');
    for (var i = 0; i < rows.length; i++) {
		// var row = [], cols = rows[i].querySelectorAll("td, th");
		var row = [], cols = rows[i].querySelectorAll("td");
        for (var j = 0; j < cols.length - 1; j++) {
			var value = cols[j].innerText;
			value =  value.replace(";", ":"); // Fix
			if (j == 3) {
				value =  value.replace(",", "");
				value =  value.replace(".", ",");
			}
			else if (j == 4) {
				value = cols[j].getAttribute('pstatus');
				if (value == 'pric') {
					value = 'Betald';
				}
				else if (value == 'prix') {
					value = 'Betalas ej';
				}
				else if (value == 'priz') {
					value = 'Betalas';
				}
				else {
					value = '';
				}
			}
            row.push(value);
		}
		csv.push(row.join(";"));		
	}

    download_csv(csv.join("\n"), filename);
}

$(document).on('click', '#eExportPrizeCsv', function(event) {
	event.preventDefault();
	// alert('excel');
	exportPrizeTableToCsv("Premielista.csv");
});

</script>