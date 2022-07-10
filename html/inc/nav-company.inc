<?php
if (isset($_GET['param'])) {
    $paramArray = explode("/", $_GET['param']);
    $page = $paramArray[0];
    if ($page == "foretagsdetaljer") {
        $page = "details-company";
    }
    else if ($page == "transaktioner") {
        $page = "trans-company";
    }
	 else if ($page == "bokforingsorder") {
        $page = "accounting-order";
    }
    else if ($page == "event") {
        $page = "event";
    }
    else if ($page == "webbformular") {
        $page = "webform";
    }
    else if ($page == "event") {
        if ($Operator->has_invoice_service == 'y') {
            $page = "event";
        }
        else {
            $page = "details-company";
        }    
    }

    else if ($page == "utskick") {
        if ($Operator->has_invoice_service == 'y') {
            $page = "invoice-event";
        }
        else {
            $page = "details-company";
        }    
    }
    else if ($page == "privilegier") {
        $page = 'priv';
    }
} else {
    $page = "details-company";
}

$userMessage = "Inloggad: $Operator->name på $Operator->company_name";

?>

<section class="section main-header" style="background-color: #ffffff">
  <div class="container">
		  <p class="has-text-right" style="padding-right:4px; margin-bottom:0; font-size:13px; color: #5a7d22;"><?php echo $userMessage; ?></p>
      <nav class="navbar" role="navigation" aria-label="main navigation" style="background-color: transparent; margin-top: -12px">
          <div class="navbar-brand">
              <a class="navbar-item" style="padding-top:4px" href="<?php echo SITE_URL; ?>">
                  <img src="images/turtle-pay.png" >
              </a>

              <a role="button" class="navbar-burger burger" aria-label="menu" aria-expanded="false" data-target="navbar">
                  <span aria-hidden="true"></span>
                  <span aria-hidden="true"></span>
                  <span aria-hidden="true"></span>
                </a>
          </div>

          <div id="navbar" class="navbar-menu">
              <div class="navbar-end">
                  <a id="navbar-company-details" class="navbar-item" style="background-color: transparent;" href="foretagsdetaljer">
                      <span class="icon" style="display:none;">
                          <i class="fas fa-home"></i>
                      </span>
                      <span> Företagsdetaljer</span>
                  </a>

                  <a id="navbar-company-trans" class="navbar-item" style="background-color: transparent;" href="transaktioner">
                      <span class="icon" style="display:none;">
                          <i class="fas fa-shield-alt"></i>
                      </span>
                      <span> Transaktioner</span>
                  </a>
					<?php
					if ($Operator->has_bo == 'y') {
					?>
					<a id="navbar-account-order" class="navbar-item" style="background-color: transparent;" href="bokforingsorder">
						<span class="icon" style="display:none;">
							<i class="fas fa-shield-alt"></i>
						</span>
						<span>Bokföringsorder</span>
					</a>
				

                  <?php 
					}
                    if ($Operator->has_invoice_service == 'y') {
                    ?>
                        <a id="navbar-event" class="navbar-item" style="background-color: transparent;" href="event">
                            <span class="icon" style="display:none;">
                                <i class="fas fa-shield-alt"></i>
                            </span>
                            <span>Event</span>
                        </a>

                    <?php
                    }
                    if ($Operator->has_invoice_service == 'y') {
                    ?>
                        <a id="navbar-invoice-event" class="navbar-item" style="background-color: transparent;" href="utskick">
                            <span class="icon" style="display:none;">
                                <i class="fas fa-shield-alt"></i>
                            </span>
                            <span>Utskick</span>
                        </a>
                    <?php    
                        }
                    ?>
                  <a id="navbar-user-budget" class="navbar-item" style="background-color: transparent;" href="https://www.turtle-pay.com/foretagsvillkor" target="_blank">
                      <span class="icon" style="display:none;">
                         <i class="fas fa-question"></i>
                      </span>
                      <span>Villkor</span>
                  </a>

                  <?php
                    if (sizeof($Operator->list) > 0) {
                  ?>

                        <div class="navbar-item has-dropdown is-hoverable" style="background-color: transparent;">
                            <a class="navbar-link" style="background-color: transparent;">
                                Konton
                            </a>
                            <div class="navbar-dropdown">
                                <a class="navbar-item" href="<?php echo SITE_URL; ?>konto?nr=0">
                                    Privat
                                </a>
                                <?php
                                    for ($i=0; $i < sizeof($Operator->list); $i++) {
                                        echo '<a class="navbar-item" href="' .  SITE_URL . 'konto?nr=' . $Operator->list[$i]->company_id . '">';
                                        echo $Operator->list[$i]->known_as;
                                        echo '</a>';
                                    }
                                ?>

                            </div>
                        </div>
                <?php } ?>

                  <div class="navbar-item" id="nav-login" >
                      <div class="buttons">
                          <button id="eLogout" class="button is-dark">Logga ut</button>
                      </div>
                  </div>


              </div>
          </div>
      </nav>
  </div>
</section>
