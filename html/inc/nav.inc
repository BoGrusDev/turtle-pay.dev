<?php

if (isset($_GET['param'])) {
	$paramArray = explode("/", $_GET['param']);
	$page = $paramArray[0];
    if ($page == "om-oss") {
      $page = "about-us";
    }
    else if ($page == "turtlepay-integritetspolicy") {
      $page = "integr";
    }
    else if ($page == "vanliga-fragor-och-svar") {
      $page = "faq";
    }
	else if ($page == "kontakt") {
      $page = "contact-us";
  }
    else if ($page == "logga-in") {
      $page = "login";
  }
   else {
        $page = 'home';
   }
} else {
    $page = 'home';
}
?>

<section class="section" style="background-color: #ffffff">
  <div class="container">
      <nav class="navbar" role="navigation" aria-label="main navigation">
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
                  <a id="navbar-about-us" class="navbar-item" href="om-oss">
                      <span class="icon" style="display:none;">
                          <i class="fas fa-home"></i>
                      </span>
                      <span> Om</span>
                  </a>

                  <a id="navbar-integr" class="navbar-item" href="turtlepay-integritetspolicy">
                      <span class="icon" style="display:none;">
                          <i class="fas fa-shield-alt"></i>
                      </span>
                      <span> Integritetspolicy</span>
                  </a>

                  <a id="navbar-contact-us" class="navbar-item" href="kontakt">
                      <span class="icon" style="display:none;">
                          <i class="fas fa-envelope"></i>
                      </span>
                       <span> Kontakt</span>
                   </a>

                  <a id="navbar-faq" class="navbar-item" href="vanliga-fragor-och-svar">
                      <span class="icon" style="display:none;">
                         <i class="fas fa-question"></i>
                      </span>
                      <span> Vanliga frågor & svar</span>
                  </a>

				  <?php if ($page == "login") {
					  // do nothing
				  }
				  else { ?>
                  
	                  <div class="navbar-item" id="nav-login" >
	                      <div class="buttons">
	                          <a class="button is-primary" href="logga-in">
	                              <strong>Logga in</strong>
	                          </a>
	                      </div>
	                  </div>
                      
				  <?php } ?>

              </div>
          </div>
      </nav>
  </div>
</section>
