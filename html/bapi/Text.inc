<?php
/*
    Text.inc

*/

$text = new StdClass();

$text->deniedInfo = 'För mera information kontakta Turtle Pay AB på telefon 08-806220 eller via e-post info@turtle-pay.com.';

// Invoice Request
$text->creditMinOption = "Lägsta lånebelopp är <MinAmount> kronor, ändra belopp eller avbryt fakturaförfrågan";
$text->borrowSpaceOption = "Kundens låneutrymme är <BorrowSpace> kronor. Ändra belopp eller avbryt fakturaförfrågan";
$text->interestFree = 'Räntefritt 30 dagar';
$text->invoiceAmount = 'Köpesumma: ' . '<RequestAmount>' . ' kr';



$text->possibleInstallment = "Lägsta månadsbelopp";
$text->possibleInstallment2 = "<MonthNo> mån - ca <MonthlyPayment> kronor";
