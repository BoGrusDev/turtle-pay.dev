<script>

var Action = {};
var Session = {};
Session.Payment = {};
Session.PaymentFileData;

Action.paymentListCreate = function() {

    var paymentDate = $('#payment-date').val();
    var param = {};
	param._group = "Payment";
	param._action = 'PaymentList';
    param._booking_date = paymentDate;

	$.ajax({ type: "POST", url: 'Service.php', data: param,
		success: function(result) {
			var data = jQuery.parseJSON(result);
			var html = "";
			html += '<h1 class="title is-size-4">Payment List</h1>';
			html += '<b>From date:  </b>' + param._booking_date + '<br>';
			//html += '<b>To date:    </b>' + param._to_date + '<br><br><br>';
			html += '<table class="table is-striped" style="width:720px">';
			html += '<tr>';
			html += '<th style="width: 160px; text-align: left">Company</th>';
			html += '<th style="width: 120px; text-align: left">Bankgiro</th>';
            html += '<th style="width: 120px; text-align: right">Balance</th>';
            html += '<th style="width: 120px; text-align: right">Date</th>';
			html += '<th style="width: 120px; text-align: right">To Pay</th>';
            html += '<th style="width: 120px;"></th>';
            html += '<th style="width: 120px; text-align: left">Confirm</th>';
			html += '</tr>';
			for(var i=0; i < data.length; i++) {
                if (data[i].to_pay != '0.00') {
                    var amount = -data[i].to_pay;
    				html += '<tr>';
    				html += '<td>' + data[i].company_name + '</td>';
    				html += '<td>' + data[i].bank_account + '</td>';
    				html += '<td style="text-align: right">' + data[i].to_pay + '</td>';
                    //html += '<td style="padding-left:10px"><input type="checkbox" ';
                    //html += 'company_id="' + data[i].company_name + '" bg="' + data[i].bank_account + '" class="payment"></td>';
                    html += '<td style="padding-left:10px"><input type="text" class="input" style="width:110px;" id="date-' + i + '" value="' + param._booking_date + '"></td>';
                    html += '<td style="padding-left:10px;"><input style="width:100px" type="text" class="input" id="to-pay-' + i +'" value="' + amount  + '"></td>';

                    html += '<td><a class="button is-small is-primary" index="'+ i + '"';
                    html += ' company-id="' + data[i].company_id + '" bg="' + data[i].bank_account + '"';
                    html += ' id="do-payment">Pay</a></td>';

                    html += '<td><input type="checkbox" id="check-'+ i + '"></td>';
                  

    				html += '</tr>';
                }
			}
			html += '</table>';
			$('#payment-list').html(html);
			//Helper.show('#action-print');
        }
	});
}

$(document).on('click', '#do-payment', function(event) {

    var index = $(this).attr('index');
    if($('#check-' + index). is(":checked")){
    }
    else {
        alert('Confirm the Payment to continue!!!');
        return false;
    }
   
    var bookingDate = $('#date-' + index).val();
    var toPay = $('#to-pay-' + index).val();
    var param = {};
	param._group = "Payment";
	param._action = 'VendorPayment';
    //param._booking_type = "vendor-pmt";
    param.booking_date = bookingDate;
    param.amount = toPay;
    param.bank_account = $(this).attr('bg');
    param.company_id = $(this).attr('company-id');
    $.ajax({ type: "POST", url: 'Service.php', data: param,
		success: function(result) {
            alert('Payment Completed');
            Action.paymentListCreate();
        }
    });
});

$(document).on('click', '#do-incomming-payment', function(event) {

    var bookingDate = $('#incomming-date').val();
    var ocrno = $('#incomming-ocrno').val();
    var amount = $('#incomming-amount').val();
    //alert(bookingDate);
    //alert(ocrno);
    //alert(amount);

    var param = {};
	param._group = "Payment";
	param._action = 'IncommingPayment';
    //param._booking_type = "vendor-pmt";
    param.booking_date = bookingDate;
    param.amount = amount;
    param.ocrno = ocrno;
    param.company_id = $(this).attr('company-id');
    $.ajax({ type: "POST", url: 'Service.php', data: param,
		success: function(result) {
            //alert(result);
			var data = jQuery.parseJSON(result);
            if (data.code == "1") {
                $('#incomming-ocrno').val('');
                $('#incomming-amount').val('');
            } else {
                alert(result);
            }
        }
    });
});

$(document).on('click', '.ePayment', function(event) {
	event.preventDefault();
	var action = $(this).attr('action');
	if (action == 'list') {
		Action.paymentListCreate();
	}
});

Action.paymentInputFileListCreate = function(filename) {
  
    var param = {};
	param._group = "Payment";
	param._action = 'IncommingFileLoad';
    param._file = filename;
	$.ajax({ type: "POST", url: 'Service.php', data: param,
		success: function(result) {
            var data = jQuery.parseJSON(result);
            if (data.code == '1') {
                var html = "";
                html += '<h1 class="title is-size-4">Incoming payment</h1>';
                html += '<table class="table is-striped" style="width:720px">';
                html += '<tr>';
                html += '<th style="width: 160px; text-align: left">Date</th>';
                html += '<th style="width: 120px; text-align: left">OCR no</th>';
                html += '<th style="width: 120px; text-align: right">Amount</th>';
                html += '<th style="width: 120px; text-align: left">Confirm</th>';
                html += '</tr>';
                for(var i=0; i < data.list.length; i++) {
                    html += '<tr>';
                        html += '<td>' + data.list[i].date + '</td>';
                        html += '<td>' + data.list[i].ocrno + '</td>';
                        html += '<td style="text-align: right">' + data.list[i].amount + '</td>';
                        html += '<td><a class="button is-small is-primary do-payment-file" style="width:120px" index="' + i + '"> Book </a></td>';
                    html += '</tr>'
                }
                html += '</table>';
                Session.PaymentFileData = data.list;
                $('#payment-file-list').html(html);
            }
            else if (data.code == '2') {
                var message = 'FILE ALREADY LOADED \n\n';
                message += 'Serial no: ' + data.serial_no + '\nPayment date: ' + data.payment_date + '\nUploaded: ' + data.created;
                alert(message); 
            }
            else {
                alert('Wrong format');
            }
        }
    });
}

$(document).on('click', '.do-payment-file', function(event) {

    var index = $(this).attr('index');
    $(this).removeClass('is-primary');
    $(this).prop('disabled', true);
    $(this).text(' Done ');
    var bookingDate = Session.PaymentFileData[index].date;
    var ocrno = Session.PaymentFileData[index].ocrno;
    var amount = Session.PaymentFileData[index].amount;
    //alert(bookingDate);
    //alert(ocrno);
    //alert(amount);

    // return;

    var param = {};
    param._group = "Payment";
    param._action = 'IncommingPayment';

    param.booking_date = bookingDate;
    param.amount = amount;
    param.ocrno = ocrno;
    $.ajax({ type: "POST", url: 'Service.php', data: param,
        success: function(result) {
            //alert(result);
            var data = jQuery.parseJSON(result);
            if (data.code == "1") {
                // OK
            } else {
                alert(result);
            }
        }
    });
});

$(document).on("click", ".eUpploadTrigger", function(event) {
	event.preventDefault();
	$('#upload-file').trigger("click");
});

$("#upload-file").change(function (e) {

    const fi = document.getElementById('upload-file'); 

    if (fi.files.length > 0) { 
        for (var i = 0; i <= fi.files.length - 1; i++) { 
            const fsize = fi.files.item(i).size; 
            const file = Math.round((fsize / 1024)); 
            if (file > 20000) { // 300
                alert('Filen är för stor, max storlek är 20000kb!');
        
                return;
            } 
            else {
                if (this.files && this.files[0]) {
                    var reader = new FileReader();
                    // -- reader.onload = function (e) {
                        // -- $('#header-image-src').attr('src', e.target.result);
                    // -- }
                    reader.readAsDataURL(this.files[0]);
                    var file_data = $('.file').prop('files')[0];

                    if (file_data != undefined) {
                        var form_data = new FormData();                  
                        form_data.append('file', file_data);
                        $.ajax({
                            type: 'POST',
                            //url: 'service2/upload.php?id=' + UserId,
                            url: 'Service/upload-file.php',
                            contentType: false,
                            processData: false,
                            data: form_data,
                            success:function(result) {
                                var data = jQuery.parseJSON(result); 
                                if (data.code == '1') {
                                    Action.paymentInputFileListCreate(data.filename);
                                }
                                else {
                                    alert('Someting go wrong when upload file"')
                                }
                                /*
                                console.log(result);
                                
                                var data = jQuery.parseJSON(result); 
                                if (data.code =='1')  {
                                    // Process File
                                    var param = {};

                                    param._group = 'RecountServicePublic';
                                    param._action = 'SieFileProcess';
                                    param._file = data.filename;
                                    param._recount_company_id = COMPANY_ID;
                                    param._site_code = 'F2CEC5891A2E21AA35AD10BAC40C9010';
                                
                                    $.ajax({type: "POST", url: Control.serviceUrl, data: JSON.stringify(param),
                                        success: function(result) {
                                            //alert(result);
                                            //data = jQuery.parseJSON(result);
                                            RecountProcess.load();
                                        }
                                    });

                                    // OK
                                    // Reload page
                                    // Image.load();
                                
                                }
                                else if (data.code == '0') {
                                    alert('Filen kan inte laddas upp!');
                                    
                                    return;
                                } 
                                // $('.image').val('');
                                */
                            }
                        });
                    }
                }
            }
        }
    }
});

$(document).on('click', '#SelectFile', function(event) {
    event.preventDefault();
    $('#upload-file').trigger('click');
});

/*
$(document).on('click', '.eLoadPaymentFile', function(event) {
    event.preventDefault();
    Action.paymentInpitFileListCreate();
});
*/

$(document).on('click', '.menu-select', function(event) {
    event.preventDefault();
    var action = $(this).attr('action');
    if (action == 'outgoing') {
        var todaysDate = new Date();
        $('#payment-date').val(Helper.convertDate(todaysDate));
        $('#payment-section').hide();
        $('#payment-outgoing-section').show();
    }
    else
    if (action == 'incomming') {
        var todaysDate = new Date();
        $('#incomming-date').val(Helper.convertDate(todaysDate));
        $('#payment-section').hide();
        $('#payment-incomming-section').show();
    }
    else 
    if (action == 'incomming-file') {
        //var todaysDate = new Date();
        //var fileName = 'payment-' +Helper.convertDate(todaysDate) + '.csv'; 
        //$('#payment-file').val(fileName);
        $('#payment-section').hide();
        $('#payment-incomming-file-section').show();
    }
});

$(document).ready(function() {

	//Action.paymentListCreate();

});

</script>
