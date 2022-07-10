
<section class="section" style="background-color: #ffffff">
    <div class="container">
        <nav class="navbar" role="navigation" aria-label="main navigation">
             <div class="navbar-brand">
                <a class="navbar-item" style="padding-top:4px" href="">
                    <img src="images/turtle-pay.png" >
                </a>

                <a role="button" class="navbar-burger burger" aria-label="menu" aria-expanded="false" data-target="navbar">
                    <span aria-hidden="true"></span>
                    <span aria-hidden="true"></span>
                    <span aria-hidden="true"></span>
                    </a>
            </div>
          </div>
      </nav>
  </div>
</section>

<section class="hero" style="background-color:#4DB4D7; color: #ffffff">
    <div class="hero-body">
        <div class="container">
            <h1>Logga in</h1>
            <h2>Här loggar du in till Turtle Pay Events</h2>
        </div>
    </div>
</section>

<section class="section" style="padding-bottom: 12px; padding-top:12px">
    <div class="container">
        <div class="columns">
            <div class="column">

                <div class="columns" style="margin-bottom: 0">
                    <div class="column mobile-margin">
                        <div class="field">
                            <p>Personnummer</p>
                            <div class="control">
                                <input class="input personal-id-number personal-id-number" id="personal-id-number" type="text" placeholder="ååååmmddnnnn"  maxlength="12">
                            </div>
                        </div>
                    </div>
                </div>

                <div class="columns" style="margin-bottom: 0">
                    <div class="column mobile-margin">
                        <div class="field">
                            <label class="checkbox">
                                <input type="checkbox" id="BankIDCheckBox">
                                BankID på denna enhet
                            </label>
                        </div>
                    </div>
                </div>

                <div class="columns" style="margin-bottom: 0">
                    <div class="column mobile-margin">
                        <p>
                            Tryck Logga in och öppna därefter BankID i din mobil eller på din dator.
                        </p>
                    </div>
                </div>

                <div class="columns" style="margin-bottom: 0">
                    <div class="column mobile-margin">
                        <button class="button is-large bankid-button" id="eLogin">
                            <span class="icon is-medium">
                                <img src="images/icon_64x64.png" alt="" class="bankid-logo"/>
                            </span>
                            <span>Logga in</span>
                         </button>
                     </div>
                </div>
            </div>
        </div>
    </div>
</section>


<div class="modal" id="login-mobile-modal">
    <div class="modal-background"></div>
    <div class="modal-card pl0 pr0  modal-width" style="margin-top: -150px!important">
        <header class="modal-card-head">
            <p class="modal-card-title has-text-centered">Loggar in</p>
        </header>
        <section class="modal-card-body">
            <p id="login-mobile-modal-text" class="has-text-centered"></p>
        </section>

        <footer class="modal-card-foot">
            <button id="eMobileLogin" class="button is-primary w120 image-center" >Fortsätt</button>
        </footer>

    </div>
</div>

<div class="modal" id="login-wait-modal">
    <div class="modal-background"></div>
    <div class="modal-card pl0 pr0  modal-width" >
        <header class="modal-card-head">
            <p class="modal-card-title has-text-centered">Loggar in</p>
        </header>
        <section class="modal-card-body">
            <p  class="has-text-centered">Väntar på BankID</p>
        </section>
        <footer class="modal-card-foot">
            <button id="eLoginCancel" class="button is-dark w120 image-center">Avbryt</button>
        </footer>
    </div>
</div>
