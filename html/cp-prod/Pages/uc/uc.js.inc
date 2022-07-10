
<script>

var Session = {};
Session.currentPeopleId = 0;

$(document).on('click', '#eReportRaw', function(event) {
    event.preventDefault();
    w2ui['uc-simulate-list'].clear();
    Session.ucId = $('#eUcPeople').val();
    //alert(Session.currentPeopleId);
    var param = {};
    param._group = "Uc";
    param._action = 'GetReport';
    param._uc_id = Session.ucId;
    param._filter = "n";
    $.ajax({ type: "POST", url: 'Service.php', data: param,
        success: function(result) {
            //alert(result);
            var data = jQuery.parseJSON(result);
            w2ui['uc-simulate-list'].add(data);
        }
    });
});

$(document).on('click', '#eReportFilter', function(event) {
    event.preventDefault();
    w2ui['uc-simulate-list'].clear();
    Session.currentPeopleId = $('#eUcPeople').val();
    //alert(Session.currentPeopleId);
    var param = {};
    param._group = "Uc";
    param._action = 'GetReport';
    param._people_id =Session.currentPeopleId;
    param._filter = "y";
    $.ajax({ type: "POST", url: 'Service.php', data: param,
        success: function(result) {
            var data = jQuery.parseJSON(result);
            w2ui['uc-simulate-list'].add(data);
        }
    });
});

$(document).on('click', '#eCheck', function(event) {
    event.preventDefault();
    //w2ui['uc-simulate-list'].clear();
    //Session.currentPeopleId = $('#eUcPeople').val();
    //alert(Session.currentPeopleId);
    var param = {};
    param._group = "Uc";
    param._action = 'Check';
    param._uc_id =Session.ucId;
    //param._filter = "y";
    $.ajax({ type: "POST", url: 'Service.php', data: param,
        success: function(result) {
           
            var data = jQuery.parseJSON(result);
            var html = '<pre><code>';
            html += JSON.stringify(data, null, 4) + '</pre></code>';
           
            $('#uc-simulate-result').html(html);
            
        }
    });
});


function ucListCreateGrid () {
	dgUcList = {
		name: 'uc-simulate-list',
		show: {
			toolbar: false,
			footer: false,
			//toolbarAdd: true,
			toolbarDelete: false,
			toolbarSave: false,
			//toolbarEdit: true
		},

        /*
		onDblClick: function(event) {
			event.onComplete = function () {
                //redirectPeople(this);
                var sel = this.getSelection();
			 	var sel_record = this.get(sel[0]);
                 Session.event_item_id = sel_record.invoice_event_item_id;
                $('#item-edit-modal-email').val(sel_record.email);
                $('#item-edit-modal-auto-reminder').val(sel_record.auto_reminder);
                $('#item-edit-modal').addClass('is-active');
			}
		},
        */
		recid   : 'uc_item_id',
		columns: [
			{ field : "uc_item", caption: "",  size: "80px", sortable: true },
            { field : "text", caption: "Text",  size: "250px", sortable: true },
            { field : "value", caption: "Value",  size: "250px", sortable: true }
			
		],
		records: []
	};
	//dg.records = jQuery.parseJSON(result);
	$('#uc-simulate-list').w2grid(dgUcList);
	//Session.Invoice.gridCreated = true;
}

$(document).ready(function() {
    ucListCreateGrid();
});

</script>
