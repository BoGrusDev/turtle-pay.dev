
<script>

var Session = {};


$(document).on('click', '#eGetSpar', function(event) {

    var_personal_id_number = $('#eInvoiceEventSelection').val();
 
    var param = {};
    param._group = "Tool";
    param._action = 'Spar';
    param._personal_id_number = $('#spar-personal-id-number').val();

    $.ajax({ type: "POST", url: 'Service.php', data: param,
        success: function(result) {
            //alert(result);
           

            var data = jQuery.parseJSON(result);
            var html = '<pre><code>';
            html += JSON.stringify(data, null, 4) + '</pre></code>';
            $('#tool-spar-result').html(html);
            //alert(html);
            
            /*
            for (var i=0; i < data.length; i++ ) { 

            }
            */
            
        }

    });
});


/*
function redirectPeople(grid) {
    var sel = grid.getSelection();
	var sel_record = grid.get(sel[0]);
    var peopleId = sel_record.people_id;
    //alert(peopleId);
    var win = window.open("http://localhost/cp-prod/people-direct?" + peopleId, '_blank');
    //var win = window.open(Settings.FirstInvoicePath  + filename, '_blank');
    win.focus();
}
*/


$(document).on('click', '.menu-select', function(event) {
	event.preventDefault();
    var action = $(this).attr('action');
	if (action == 'tool-spar') {

        /*
        var todaysDate = new Date();
        $('#from-date').val(Helper.convertDate(todaysDate));
        $('#to-date').val(Helper.convertDate(todaysDate));
        */
        $('.tool-section').hide();
        $('#tool-spar').show();
	}
   
});


$(document).ready(function() {
    //invoiceServiceOverviewListCreateGrid ();
});

</script>
