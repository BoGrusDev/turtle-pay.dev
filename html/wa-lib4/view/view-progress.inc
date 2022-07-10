<?php
echo htmlColumns('margin-bottom');
    echo htmlColumn();   
        echo '<div class="p-default" id="status-text" style="padding-top:10px;">';
        if ($Action->isMobile == "yes") {
            echo $Message['progress-mobile'];
        }
        else {
            echo $Message['progress-computer'];
        }
        echo '</div>';

        
            //echo '<div class="has-text-centered" id="MobilePanel" style="display:none">';
            //echo '<button id="eMobileContinue" class="button is-primary  image-center" >' . $Setting->continue_text . '</button>';
            //echo '</div>';
    echo htmlDivEnd();
echo htmlDivEnd();
?>