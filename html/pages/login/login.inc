
<section class="hero is-primary">
    <div class="hero-body">
        <div class="container">
            <h1>Logga in</h1>
            <h2>Här loggar du in på ditt privata konto eller företagskonto hos Turtle Pay</h2>
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

<div class="modal" id="budget-check-modal">
    <div class="modal-background"></div>
        <div class="modal-card pl0 pr0  modal-width">
            <header class="modal-card-head">
                <p class="modal-card-title has-text-centered">Hushållsbudget</p>
            </header>
            <section class="modal-card-body">
                <p class="has-text-centered">Gör din hushållsbudget!</p>
            </section>
            <footer class="modal-card-foot">
                <button id="eBudgetClose" class="button is-dark w120 image-center">Senare</button>
                <button id="eBudget" class="button is-dark w120 image-center">Nu</button>
            </footer>
        </div>
    </div>
</div>

<div class="modal" id="kyc-check-modal">
    <div class="modal-background"></div>
        <div class="modal-card pl0 pr0  modal-width">
            <header class="modal-card-head">
                <p class="modal-card-title has-text-centered">Kundkännedom</p>
            </header>
            <section class="modal-card-body">
                <p class="has-text-centered">Ange dina kunduppgifter!</p>
            </section>
            <footer class="modal-card-foot">
                <button id="eKycClose" class="button is-dark w120 image-center">Senare</button>
                <button id="eKyc" class="button is-dark w120 image-center">Nu</button>
            </footer>
        </div>
    </div>
</div>
