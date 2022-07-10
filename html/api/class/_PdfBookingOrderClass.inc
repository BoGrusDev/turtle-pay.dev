<?php

$includes = 'Gui';

use setasign\Fpdi;

class PdfBookingOrder {

	public function __construct($package) {
        // 
        // Ladda package
        //
        
        if (sizeof($package) > 0 ) {
            foreach ($package as $key => $value) {
                $this->$key = $value;
            }
        }
        
	}

    public function Run($data) {
		$actionMethod = 'action' . $data->_action;
		echo $this->$actionMethod($data);
    }

	private function actionTest($data) {
		echo 'inside';
    }

	private function actionCreate($data) {

        /*
            {
				"_key" : "test-key",
				"_group" : "PdfBookingOrder",
				"_action" : "Create",
				"booking_date" : "2020-10-15",
				"ocrno" : "123444109680",
				"amount" : "2000"
			}		
            SetFontSize(float size)
        */

        //print_r($data); 

        $font = 'Helvetica';

		require('fpdf181/fpdf.php');
		require_once('ftpi/autoload.php');
		$pdf = new Fpdi\Fpdi();
        
        for ($i = 0; $i < sizeof($data->_list); $i++) {
			//echo $data->_list[$i]->date;
		
            $pdf->AddPage();
            $pdf->SetFont($font,'',14);

            $pdf->SetFontSize(14);
            $pdf->SetXY(14, 4);
            $pdf->Write(14, utf8_decode($data->_company_name));
            $pdf->SetFont($font,'');
            $pdf->SetFontSize(10);
            $pdf->SetXY(14, 9);
            $pdf->Write(14, utf8_decode($data->_address));
            $pdf->SetXY(14, 13);
            $pdf->Write(14, utf8_decode($data->_postcode . ' ' . $data->_city));
            $pdf->SetXY(14, 17);
            $pdf->Write(14, utf8_decode('Orgnr: ' . $data->_orgno));
      
            $pdf->SetFont($font);
            $pdf->SetFontSize(14);
            $pdf->SetXY(111, 4); // 2
            $pdf->Write(16, utf8_decode('Bokföringsorder'));

            $pdf->SetFont($font,'B');
            $pdf->SetFontSize(9);
            $pdf->SetXY(111, 14); // 11
            $pdf->Write(11, 'Utskriftsdatum');
            $pdf->SetFont('');
            $pdf->SetFont($font);
            $pdf->SetFontSize(10);
            $pdf->SetXY(111, 18); // 16
            $pdf->Write(11, date('Y-m-d'));

            $pdf->SetFont($font,'B');
            $pdf->SetFontSize(10);
            $pdf->SetXY(18, 46);
            $pdf->SetFillColor(220,220,220);
            $pdf->Cell(184,9,' Datum             Text                        Namn                                         Konto                       Debet                     Kredit','BTLR',0,'L',true);        

            $pdf->SetFont($font);
            $pdf->SetFontSize(11);
            
            $line = 56;
            //for ($i = $startIndex; $i < sizeof($invoice->spec); $i++) {
               
            $pdf->SetXY(19, $line);
            $pdf->Write(10, utf8_decode($data->_list[$i]->date));

            $pdf->SetXY(43, $line);
            $pdf->Write(10, utf8_decode($data->_bo_text));
            $line += 5;

            for ($j = 0; $j < sizeof($data->_list[$i]->trans); $j++) {
                $pdf->SetXY(73, $line);
                $pdf->Write(11, utf8_decode($data->_list[$i]->trans[$j]->name));
                $pdf->SetXY(123, $line);
                $pdf->Write(11, utf8_decode($data->_list[$i]->trans[$j]->account_no));

                $amount = (float) $data->_list[$i]->trans[$j]->amount;
                if ($amount >= 0) {
                    $pdf->SetXY(152, $line);  
                }
                else {
                    $amount = $amount * -1;
                    $pdf->SetXY(182, $line);
                }
                $amount = number_format($amount, 2);
                $pdf->Cell(16, 10, utf8_decode($amount), 0, 0, "R");
               
                $line += 5;
            }                
        }
        $fileName = $this->Gui->_create();
        $pdfUrl = '../pdf-files/' . $fileName . '.pdf';
        $pdf->Output($pdfUrl, 'F');
        $reply = new stdClass();
        $reply->code = '1';
        $reply->filename =  $fileName;
        return json_encode($reply);
    }
}