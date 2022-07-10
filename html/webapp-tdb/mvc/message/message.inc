<?php

if ($Current->isMobile == 'yes') {
    echo '<section class="section" style="padding-bottom:0px">';
    echo '<div class="container">';
}
else {
    echo '<section class="section">';
    echo '<div class="container">';
}
?>
<div class="columns has-text-centered-of" id="header-image-panel" >
    <div class="column">
        <img src="/webapp-tdb/images/turtle-pay.png" alt="" />
    </div>
</div>

<div class="columns margin-bottom">
    <div class="column">
        <div class="p-default" style="padding-top:10px;"> 
            <?php 
                echo $Current->deniedText; 
                echo '<br><br>';
                echo 'För information kontakta Turtle Pay AB på info@turtle-pay.com eller tel. 08-806220.';
            ?>
        </div>
    </div>
</div>

<?php  /*
 $onImage = false;

 if (isset($Action->event['header_image'])) {
     $logo = $Action->event['header_image'];
     $title = $Action->event['header_title'];
     if ($Action->event['header_image_on'] == 'y') {
        $onImage = true;
     }
 }
 else {
    $logo = $Action->companyLogo;
    $title = $Action->companyKnownAs;
    if ($Action->headerImageOn == "y") {
        $onImage = true;
    }
 }
 
if ($onImage) {
    echo '<div class="columns has-text-centered-of" id="header-image-panel" >';
        echo '<div class="column">';
            echo '<img id="header-image-src" src="' . SITE_URL . '/logo/' . $logo . '" alt="" />';
        echo '</div>';
    echo '</div>';
}
else {
    // --
    // -- Header-text-panel
    // --
    echo '<div class="columns">';
        echo '<div class="column">';
            //echo '<h1 id="header-text-title" style="color:' . $Action->event['header_tcolor'] . '; background-color:' . $Action->event['header_bcolor'] . '">' . $title . '</h1>';
            echo '<h1 id="header-text-title">' . $title . '</h1>';
        echo '</div>';
    echo '</div>';
}


 echo htmlColumns(); // has-text-centered - padding-top: 80px
    echo htmlColumn();  
        echo htmlSubHeader($DeniedText, 'status-header');
    echo htmlDivEnd();
echo htmlDivEnd();

// echo '<p class="p-default" id="status-text" style="padding-top:10px;"></p>';
echo htmlColumns(); 
    echo htmlColumn();  
        echo '<div class="p-default" id="status-text" style="padding-top:10px;">' . $DeniedHtml . '</div>';
    echo htmlDivEnd();
echo htmlDivEnd();
*/
?>
