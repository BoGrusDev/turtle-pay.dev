<?php
/*

    FirstInvoicePdf

    2018-07

	sudo chmod -R 777 /var/www/html/f-invoice
*/

use setasign\Fpdi;

$invoiceObj = new StdClass();
$invoiceObj->date = "2019-02-11";
$invoiceObj->duedate = "2019-02-28";
$invoiceObj->name = "Bengt Olof Christian Holm";
$invoiceObj->address = "ALLÉVÄGEN 1";
$invoiceObj->postaddress = "14139 HUDDINGE";
$invoiceObj->monthly_no = "12";
$invoiceObj->monthly_payment_total = "0";
$invoiceObj->monthly_invoice_fee = "29.00";

//$controlNumber = "2790131" . mt_rand(1000, 9999);
//$ocrno = ocrnoCreate($controlNumber);
// 1 23 44 41 05514
//echo $ocrno; die('');

$ocrno = "279013156963";
$invoiceObj->ocrno = $ocrno;

$invoiceObj->invoice_filename = "279013156963-201902.pdf";

$invoiceObj->spec = array();
$invoiceObj->spec[] = new StdClass();
$index = 0;
$invoiceObj->spec[$index]->date = "2018-12-16";
$invoiceObj->spec[$index]->type = "Köp";
$invoiceObj->spec[$index]->ref = "Sweden Snowsport";
$invoiceObj->spec[$index]->amount = "-3,995.00";
$invoiceObj->spec[$index]->balance = "-3,995.00";

$invoiceObj->spec[] = new StdClass();
$index = 1;
$invoiceObj->spec[$index]->date = "2018-12-21";
$invoiceObj->spec[$index]->type = "Inbet";
$invoiceObj->spec[$index]->ref = "";
$invoiceObj->spec[$index]->amount = "1,000.00";
$invoiceObj->spec[$index]->balance = "-2,995.00";

$invoiceObj->spec[] = new StdClass();
$index = 2;
$invoiceObj->spec[$index]->date = "2019-01-28";
$invoiceObj->spec[$index]->type = "Ränta";
$invoiceObj->spec[$index]->ref = ""; //2018-12-29 - 2019-01-28";
$invoiceObj->spec[$index]->amount = "-16.00";
$invoiceObj->spec[$index]->balance = "-3,011.00";

$invoiceObj->spec[] = new StdClass();
$index = 3;
$invoiceObj->spec[$index]->date = "2019-01-28";
$invoiceObj->spec[$index]->type = "Aviavgift";
$invoiceObj->spec[$index]->ref = ""; //2018-12-29 - 2019-01-28";
$invoiceObj->spec[$index]->amount = "-29.00";
$invoiceObj->spec[$index]->balance = "-3,040.00";

$invoice = new InvoicePdfClass('../turtlepay-finvoice/');
$invoice->Create($invoiceObj);

class InvoicePdfClass {


	public function __construct($folder, $mall = "") {
		$this->folder = $folder;
        $this->mall = "fakturamall.pdf";;
	}

	public function Create($invoice) {

		$font = 'Helvetica';
		$extra = 0;

		// Init PDF
		$mall = "fakturamall.pdf";
		require('fpdf181/fpdf.php');
		require_once('ftpi/autoload.php');
		$pdf = new Fpdi\Fpdi();
		$pdf->AddFont('OCR-B','','ocrb.php');
		$pdf->setSourceFile($mall);
		$templateId = $pdf->importPage(1);
		$size = $pdf->getTemplateSize($templateId);
		$pdf->AddPage('P', array($size['width'], 310));
		$pdf->useTemplate($templateId);

		/*
		$pdf->SetFont($font);
		$pdf->SetFontSize(16);
		$pdf->SetXY(18, 2-12-21
		$pdf->Write(16, utf8_decode($invoice->company_name));

		$pdf->SetFont($font,'I');
		$pdf->SetFontSize(9);
		$pdf->SetXY(18, 9);
		$pdf->Write(14, 'i samarbete med Turtle Pay');
		*/
		$pdf->SetXY(18, 2);
		$pdf->Image('faktura-logo.jpg', null,null,42,23); // 60 / 31
		$pdf->SetFont($font);
		$pdf->SetFontSize(14);
		$pdf->SetXY(111, 2);
		$pdf->Write(16, utf8_decode('MÅNADSFAKTURA'));

		$pdf->SetFont($font,'B');
		$pdf->SetFontSize(9);
		$pdf->SetXY(111, 11);
		$pdf->Write(11, 'Utskriftsdatum');
		$pdf->SetFont('');
		$pdf->SetFont($font);
		$pdf->SetFontSize(10);
		$pdf->SetXY(111, 16);
		$pdf->Write(10, $invoice->date);

		$pdf->SetFont($font,'B');
		$pdf->SetFontSize(9);
		$pdf->SetXY(111, 20);
		$pdf->Write(11, utf8_decode('Förfallodatum'));
		$pdf->SetFont('');
		$pdf->SetFont($font);
		$pdf->SetFontSize(10);
		$pdf->SetXY(111, 25);
		$pdf->Write(10, $invoice->duedate);

		$pdf->SetFontSize(10);
		$pdf->SetXY(111, 37);
		$pdf->Write(10, utf8_decode($invoice->name));
		$pdf->SetXY(111, 42);
		$pdf->Write(10, utf8_decode($invoice->address));
		$pdf->SetXY(111, 47);
		$pdf->Write(10, utf8_decode($invoice->postaddress));

		$pdf->SetFont($font,'B');
		$pdf->SetFontSize(11);
		$pdf->SetXY(18, 68);
		$pdf->SetFillColor(220,220,220);
		//$pdf->Cell(184,9,'   Specifikation','BTLR',0,'L',true);
		$pdf->Cell(184,9,'   Datum         Typ                Referens                                                     Belopp             Balans','BTLR',0,'L',true);
		//$pdf->Write(10, utf8_decode('Specifikation'));

		$pdf->SetFont('');
		$pdf->SetFont($font);
		$pdf->SetFontSize(10);
		$line = 76;
		for ($i = 0; $i < sizeof($invoice->spec); $i++) {
			$pdf->SetXY(20, $line);
			$pdf->Write(10, utf8_decode($invoice->spec[$i]->date));
			$pdf->SetXY(44, $line);
			$pdf->Write(11, utf8_decode($invoice->spec[$i]->type));
			$pdf->SetXY(67, $line);
			$pdf->Write(10, utf8_decode($invoice->spec[$i]->ref));
			$pdf->SetXY(140, $line);
			//$pdf->Write(10, utf8_decode($invoice->spec[$i]->amount));
			$pdf->Cell(16, 10, utf8_decode($invoice->spec[$i]->amount), 0, 0, "R");
			$pdf->SetXY(167, $line);
			$pdf->Cell(16, 10, utf8_decode($invoice->spec[$i]->balance), 0, 0, "R");
			//$pdf->Write(10, utf8_decode($invoice->spec[$i]->balance));
			$line += 5;
		}

		$pdf->SetXY(160, 60);
		$pdf->Write(10, utf8_decode('Er skuld (-) / fordran (+)'));

		$endLine = 128;

		$line =0 ;

		$pdf->SetXY(70, $endLine + $line);
		$pdf->SetFont($font,'B');
		$pdf->Write(10, utf8_decode( $invoice->monthly_payment_total . ' kronor,'));
		$pdf->SetFont('');
		$pdf->SetFont($font);
		$pdf->SetFontSize(10);

		//$line +=5;
		$pdf->SetXY(20, $endLine + $line);
		$pdf->Write(10, utf8_decode('Betala valfritt belopp dock lägst '));

		$len = strlen($invoice->monthly_payment_total);
		if ($len <= 2) {
		 	// under 100
			$posPlus = 0;
		}
		else if ($len == 3) {
			// over 99 and under 1000
			$posPlus = 2;
		}
		else if ($len >= 4) {
			// over 1000
			$posPlus = 5;
		}

		$pdf->SetXY(86 + $posPlus, $endLine + $line);
		$pdf->Write(10, utf8_decode('inkl. ränta (14.9%) ')); // på denna faktura senast ' . $invoice->duedate ));

		/*
		$interestText = "(Räntefritt " . $invoice->grace_days . " dagar, årsränta " . $invoice->interest . "%" ;
		if ($invoice->admin_fee > 0) {
			$interestText .= ', adm.avg. ' . $invoice->admin_fee . ' kr/mån)';
		}
		else {
			$interestText .= ")";
		}
		$pdf->SetXY(20, 131 + $extra);
		$pdf->Write(10, utf8_decode($interestText));
		*/

		$line +=5;
		$pdf->SetXY(20, $endLine + $line);
		$pdf->Write(10, utf8_decode('på denna faktura senast ' . $invoice->duedate . '.'));  //Ange fakturans ocr-nummer vid inbetalningen. '));

		//$line +=5;
		//$pdf->SetXY(20, $line);
		//$pdf->Write(10, utf8_decode('(Räntefritt 30 dagar, årsränta 14.5%)'));

		$line +=5;
		$pdf->SetXY(20, $endLine + $line);
		$pdf->Write(10, utf8_decode('Se villkor på följande länk: www.turtle-pay.com/villkor.'));

		$line +=5;
		$pdf->SetXY(20, $endLine + $line);
		$pdf->Write(10, utf8_decode('Ange fakturans ocr-nummer vid inbetalningen.'));

		$line +=5;

		$pdf->SetXY(20, $endLine + $line); // 101
		$pdf->Write(10, utf8_decode('OCR-nummer: ' . $invoice->ocrno));
		//$pdf->SetXY(46, $endLine + $line); // 101
		//$pdf->Write(10, utf8_decode($invoice->ocrno));

		$line +=5;

		$pdf->SetXY(20, $endLine + $line);
		$pdf->Write(10, utf8_decode('Bankgiro: 5258-0016'));

		$line +=5;

		$pdf->SetXY(20, $endLine + $line);
		$pdf->Write(10, utf8_decode('Nästa månadsfaktura kommer i april.'));

		$pdf->Line(18,174,201,174);

		$pdf->SetXY(18, 174);
		$pdf->Write(10, utf8_decode('Org nr: '));
		$pdf->SetXY(30, 174);
		$pdf->Write(10, utf8_decode('559101-6786'));

		$pdf->SetXY(166, 174);
		$pdf->Write(10, utf8_decode('www.turtle-pay.com'));

		$pdf->SetFontSize(8);
		$pdf->SetXY(18, 188);
		$pdf->Write(10, utf8_decode('Turtle Pay AB,   Döbelnsgatan 55,   SE-113 52 Stockholm,   Telefon 08-80 62 20,   Öppet vardagar 9-18,  helger 11-16,    info@turtle-pay.com'));
		/*
		$pdf->SetFontSize(8);
		$pdf->SetXY(18, 188);
		$pdf->Write(10, utf8_decode('Turtle Pay AB'));
		$pdf->SetXY(37, 190);
		$pdf->Write(10, utf8_decode('Döbelnsgatan 55'));
		$pdf->SetXY(61, 188);
		$pdf->Write(10, utf8_decode('SE-113 52 Stockholm'));
		$pdf->SetXY(92, 188);
		$pdf->Write(10, utf8_decode('Telefon 08-80 62 20'));
		$pdf->SetXY(122, 188);
		$pdf->Write(10, utf8_decode('Öppet vardagar 9-18, helger 11-16.'));
		$pdf->SetXY(172, 188);
		$pdf->Write(10, utf8_decode('info@turtle-pay.com'));
		*/
			$pdf->SetFontSize(8);
			$pdf->SetXY(20, 230);
			$pdf->Write(10, utf8_decode($invoice->name));
			$pdf->SetXY(20, 234);
			$pdf->Write(10, utf8_decode($invoice->address));
			$pdf->SetXY(20, 238);
			$pdf->Write(10, utf8_decode($invoice->postaddress));

			$pdf->SetFontSize(12);
			//$pdf->SetXY(134, 218);
			$pdf->SetXY(90, 238);
			$pdf->Write(12, utf8_decode('Fyll i valfritt belopp'));

			// Write the OCR
			//$pdf->SetFont('OCRB10PitchBT-Regular');
			$pdf->SetFont('OCR-B','',12);
			//$pdf->SetFontSize(10);

			$pdf->SetXY(12, 272);
			$pdf->Write(10, utf8_decode('#'));

			$pdf->SetXY(49, 272);

			$pdf->Write(10, utf8_decode($invoice->ocrno . ' #'));

			$pdf->SetXY(167, 272);
			$pdf->Write(10, utf8_decode('52580016#42#'));

		$filename = $this->folder . '/' . $invoice->invoice_filename;
		try {
			$pdf->Output($filename,'F');
		}
		catch(Exception $e) {
			echo 'Message: ' .$e->getMessage();
		}
	}


}

function ocrnoCreate($ocrno) {
	$sum = 0;
	for ($i=0; $i < strlen($ocrno); $i++) {
	// Even
		if ($i % 2 == 0) {
			$res = $ocrno[$i] * 2;
			//echo 'even: ' . $ocrno[$i] . ' ';
		} else {
			$res = $ocrno[$i];
		}

		if ($res > 9) {
			$res = $res -9;
		}
		//echo $sum . '<br>';
		$sum = $sum + $res;
	}
	//echo $sum . '<br>';
	$nerast10 = ceil($sum / 10) * 10;
	//echo $nerast10 . '<br>';
	$checksum =  $nerast10 - $sum;
	$ocr_number = $ocrno . $checksum; // 11
	return $ocr_number;
}


 ?>
