<?php
/*
	Handling all types of Validation

*/
class Validate {
	
    public function dateFormat($date) { // }, $format = 'Y-m-d' {
        $checkDate = DateTime::createFromFormat('Y-m-d', $date);
           return $checkDate && $checkDate->format('Y-m-d') === $date;
    }

}