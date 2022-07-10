<?php
if (isset($_GET['param'])) {
    $paramArray = explode("/", $_GET['param']);
    $page = $paramArray[0];
    if ($page == "mina-delajer") {
        $page = "details-user";
    }
    else if ($page == "transaktioner") {
        $page = "trans-user";
    }
    else if ($page == "fakturor") {
        $page = "invoices-user";
    }
    else if ($page == "hushallsbudget") {
        $page = "budget";
    }
    else if ($page == "people") {
        $page = "People";
    }
    else if ($page == "kyc") {
        $page = "kyc";
    }
    else {
        $page = "details-user";
        //--header("Location: " . SITE);
        //--die();
    }
} else {
    $page = 'details-user';
}

$userMessage = "Inloggad: $Operator->name";
?>

<section class="section" style="background-color: #ffffff">
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
                  <a id="navbar-user-details" class="navbar-item" style="background-color: transparent;" href="mina-detaljer">
                      <span class="icon" style="display:none;">
                          <i class="fas fa-home"></i>
                      </span>
                      <span> Mina detaljer</span>
                  </a>

                  <a id="navbar-user-trans" class="navbar-item" style="background-color: transparent;" href="transaktioner">
                      <span class="icon" style="display:none;">
                          <i class="fas fa-shield-alt"></i>
                      </span>
                      <span> Transaktioner</span>
                  </a>

                  <a id="navbar-user-invoices" class="navbar-item" style="background-color: transparent;" href="fakturor">
                      <span class="icon" style="display:none;">
                          <i class="fas fa-envelope"></i>
                      </span>
                       <span> Fakturor</span>
                   </a>

                  <a id="navbar-user-budget" class="navbar-item" style="background-color: transparent;" href="hushallsbudget">
                      <span class="icon" style="display:none;">
                         <i class="fas fa-question"></i>
                      </span>
                      <span> Hushållsbudget</span>
                  </a>

                  <a id="navbar-user-budget" class="navbar-item" style="background-color: transparent;" href="https://www.turtle-pay.com/villkor" target="_blank">
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
