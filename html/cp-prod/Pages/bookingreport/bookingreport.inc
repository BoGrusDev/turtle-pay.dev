
<div id="bookingreport-section">
    <div class="d-flex justify-content-between flex-wrap flex-md-nowrap align-items-center pb-2 mb-3 border-bottom">
      <h1 class="h2">Booking Report</h1>

      <form class="form-inline">
          <div class="form-group mb-2">
                <label for="from_date">From date: </label>
                <input type="text" class="form-control" id="from_date" style="width:100px; padding: 2px 4px; margin-left: 8px" value="2018-09-19">
          </div>
          <div class="form-group mx-sm-3 mb-2">
              <label for="to_date" class="">To date: </label>
              <input type="text" class="form-control" id="to_date" style="width:100px; padding: 2px 4px; margin-left: 8px" value="2018-09-19">
          </div>
          <!-- <button type="submit" class="btn btn-primary mb-2">Confirm identity</button> -->
      </form>

      <div class="btn-toolbar mb-2 mb-md-0">
        <div class="btn-group mr-2">
            <button id="action-print" class="btn btn-sm btn-outline-secondary eBookingreport" action="print" style="display:none">Print</button>
            <button class="btn btn-sm btn-outline-secondary eBookingreport" action="GetBookingReport">Get Booking Report</button>
        </div>
      </div>
    </div>
    <div id="bookingreport-list" class="" style="height:600px; overflow-y: scroll;"></div>
</div>
