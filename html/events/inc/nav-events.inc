<?php
if (isset($_GET['param'])) {
    $paramArray = explode("/", $_GET['param']);
    $page = $paramArray[0];
    if ($page == "events") {
        $page = "events";
    }
    else {
        $page = "events";
    }
}
?>

<section class="section main-header" style="background-color: #ffffff">
  <div class="container">
      <nav class="navbar" role="navigation" aria-label="main navigation" style="background-color: #ffffff">
          <div class="navbar-brand">
              <a class="navbar-item" style="padding-top:4px" href="<?php echo SITE_URL; ?>events">
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
               
                <?php
                    if (sizeof($UserList) > 0) {
                ?>
                    <div class="navbar-item has-dropdown is-hoverable">
                        <a class="navbar-link">
                            Konton
                        </a>
                        <div class="navbar-dropdown">
                            <?php
                                for ($i=0; $i < sizeof($UserList); $i++) {
                                    echo '<a class="navbar-item" href="' . SITE_URL . 'events?konto=' . $UserList[$i]->company_id . '">';
                                    echo $UserList[$i]->known_as;
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
