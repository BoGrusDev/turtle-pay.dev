 <?php
 // --
 // -- This handling message 
 //
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
 
/*
if ($onImage) {
    echo 'on';
}
else {
    echo 'off';
}
die(''); 
*/

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
?>