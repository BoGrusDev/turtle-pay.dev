<?php

function _BankIDAuth($data) {

    $reply = new StdClass();
    if (!isset($data->_bankid_personal_id_number)) {
        $reply->code = "0";
        $reply->denied_code = "bankid_personal_id_number_is_missing";
        return $reply;
        die('');
    }

    $json = '{"personalNumber":"' . $data->_bankid_personal_id_number . '", "endUserIp":"176.57.88.50"}';
    $curl = curl_init();
    curl_setopt( $curl, CURLOPT_URL, 'https://appapi2.bankid.com/rp/v5/auth');
    curl_setopt($curl, CURLOPT_CUSTOMREQUEST, "POST");
    curl_setopt($curl, CURLOPT_POSTFIELDS, $json);
    curl_setopt($curl, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($curl, CURLOPT_HTTPHEADER, array(
        'Content-Type: application/json',
        'Content-Length: ' . strlen($json))
    );

    curl_setopt($curl, CURLOPT_CAINFO, 'bankid.ca.pem');
    //curl_setopt($curl, CURLOPT_SSLKEY, 'TurtlePayAB.key');
    //curl_setopt($curl, CURLOPT_SSLCERT, 'TurtlePayAB.pem');
    curl_setopt($curl, CURLOPT_SSLKEY, 'turtlepay2.key');
    curl_setopt($curl, CURLOPT_SSLCERT, 'turtlepay2.pem');
    curl_setopt($curl, CURLOPT_SSLCERTPASSWD, 'Fk&1618BKl@tp');
    curl_setopt($curl, CURLOPT_SSL_VERIFYHOST, 0);
    curl_setopt($curl, CURLOPT_SSL_VERIFYPEER, 0);
    $result = curl_exec($curl);
    curl_close($curl);

    if(!$result) {
        $reply->code = "0";
            $reply->denied_code = "bankid_problem";
    }
    else {
        $authObject = json_decode($result);
        if (isset($authObject->orderRef)) {
            $reply->code = "1";
            $reply->order_ref = $authObject->orderRef;
            $reply->denied_code = "";
        }
        else if (isset($authObject->errorCode)) {
            $reply->code = "0";
            $reply->denied_code = $authObject->errorCode;
        }
        else {
            $reply->code = "0";
            $reply->denied_code = "bankid_problem";
        }
    }

    return $reply;
    }

function _BankIDAuthCollect($data) {

    $reply = new StdClass();
    if (!isset($data->_order_ref)) {
        $reply->code = "0";
        $reply->denied_code = "order_ref_is_missing";
        return $reply;
        die('');
    }
    $json = '{"orderRef":"' . $data->_order_ref . '"}';
    $curlCheck = curl_init();
    curl_setopt( $curlCheck, CURLOPT_URL, 'https://appapi2.bankid.com/rp/v5/collect');
    curl_setopt($curlCheck, CURLOPT_CUSTOMREQUEST, "POST");
    curl_setopt($curlCheck, CURLOPT_POSTFIELDS, $json);
    curl_setopt($curlCheck, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($curlCheck, CURLOPT_HTTPHEADER, array(
        'Content-Type: application/json',
        'Content-Length: ' . strlen($json))
    );
    curl_setopt($curlCheck, CURLOPT_CAINFO, 'bankid.ca.pem');
    //curl_setopt($curlCheck, CURLOPT_SSLKEY, 'TurtlePayAB.key');
    //curl_setopt($curlCheck, CURLOPT_SSLCERT, 'TurtlePayAB.pem');
    curl_setopt($curlCheck, CURLOPT_SSLKEY, 'turtlepay2.key');
    curl_setopt($curlCheck, CURLOPT_SSLCERT, 'turtlepay2.pem');
    curl_setopt($curlCheck, CURLOPT_SSLCERTPASSWD, 'Fk&1618BKl@tp');

    curl_setopt($curlCheck, CURLOPT_SSL_VERIFYHOST, 0);
    curl_setopt($curlCheck, CURLOPT_SSL_VERIFYPEER, 0);

    sleep(5);

    $status = false; // Set true when a complete, fail or inknown error occur
    while ($status== false) {

        $result = curl_exec($curlCheck);
        if(!$result) {
            $reply->code = "0";
                $reply->denied_code = "bankid_problem";
            return $reply;
            die('');
        }
        else {
            $collectObject = json_decode($result);
            if (isset($collectObject->errorCode)) {
                $reply->code = '0';
                $reply->denied_code = $collectObject->details;
                $status = true;
            } else {
                switch ($collectObject->status) {
                    case 'pending':
                        sleep(3);
                        break;
                    case 'failed':
                        $reply->code = '0';
                        $reply->denied_code = $collectObject->hintCode;
                        $status = true;
                        break;
                    case 'complete':
                        $reply->code = '1';
                        $reply->name = $collectObject->completionData->user->name;
                        $reply->givenName = $collectObject->completionData->user->givenName;
                        $reply->surname = $collectObject->completionData->user->surname;
                        $reply->ipAddress = $collectObject->completionData->device->ipAddress;
                        $status = true;
                        break;
                    default:
                        $reply->code = '0';
                        $reply->denied_code = "bankid_problem";
                        $status = true;
                }
            }
        }
    }
    return $reply;
}

function _BankIDCancel($data) {

    $reply = new StdClass();

    if (!isset($data->_order_ref)) {
        $reply->code = "0";
        $reply->denied_code = "order_ref_is_missing";
        return $reply;
        die('');
    }

    $json = '{"orderRef":"' . $data->_order_ref . '"}';
    $curl = curl_init();
    curl_setopt( $curl, CURLOPT_URL, 'https://appapi2.bankid.com/rp/v5/cancel');
    curl_setopt($curl, CURLOPT_CUSTOMREQUEST, "POST");
    curl_setopt($curl, CURLOPT_POSTFIELDS, $json);
    curl_setopt($curl, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($curl, CURLOPT_HTTPHEADER, array(
        'Content-Type: application/json',
        'Content-Length: ' . strlen($json))
    );

    curl_setopt($curl, CURLOPT_CAINFO, 'bankid.ca.pem');
    //curl_setopt($curl, CURLOPT_SSLKEY, 'TurtlePayAB.key');
    //curl_setopt($curl, CURLOPT_SSLCERT, 'TurtlePayAB.pem');
    curl_setopt($curl, CURLOPT_SSLKEY, 'turtlepay2.key');
    curl_setopt($curl, CURLOPT_SSLCERT, 'turtlepay2.pem');
    curl_setopt($curl, CURLOPT_SSLCERTPASSWD, 'Fk&1618BKl@tp');
    curl_setopt($curl, CURLOPT_SSL_VERIFYHOST, 0);
    curl_setopt($curl, CURLOPT_SSL_VERIFYPEER, 0);

    $result = curl_exec($curl);
    curl_close($curl);

    if(!$result) {
    $reply->code = "0";
        $reply->denied_code = "bankid_problem";
        return $reply;
        die('');
    }

    $cancelObject = json_encode($result);

    $reply->code = "1";

    return $reply;
}

function _BankIDSignInit($data) {

    $reply = new StdClass();

    if (!isset($data->_bankid_personal_id_number)) {
        $reply->code = "0";
        $reply->denied_code = "bankid_personal_id_number_is_missing";
        return $reply;
        die('');
    }
    if (!isset($data->_bankid_text)) {
        $reply->code = "0";
        $reply->denied_code = "bankid_text_is_missing";
        return $reply;
        die('');
    }

    $signMessage = base64_encode($data->_bankid_text);
    $json = '{"personalNumber":"' . $data->_bankid_personal_id_number . '", "endUserIp":"176.57.88.50", "userVisibleData" : "' . $signMessage . '"}';
    $curl = curl_init();
    curl_setopt( $curl, CURLOPT_URL, 'https://appapi2.bankid.com/rp/v5/sign');
    //curl_setopt( $curl, CURLOPT_URL, 'https://appapi2.test.bankid.com/rp/v5/sign');
    curl_setopt($curl, CURLOPT_CUSTOMREQUEST, "POST");
    curl_setopt($curl, CURLOPT_POSTFIELDS, $json);
    curl_setopt($curl, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($curl, CURLOPT_HTTPHEADER, array(
        'Content-Type: application/json',
        'Content-Length: ' . strlen($json))
    );
    //curl_setopt($curl, CURLOPT_CAINFO, 'appapi.test.bankid.com.pem');
    //curl_setopt($curl, CURLOPT_SSLCERT, '_test.pem');
    //curl_setopt($curl, CURLOPT_SSLCERTPASSWD, 'qwerty123');
    curl_setopt($curl, CURLOPT_CAINFO, 'bankid.ca.pem');
    //curl_setopt($curl, CURLOPT_SSLKEY, 'TurtlePayAB.key');
    //curl_setopt($curl, CURLOPT_SSLCERT, 'TurtlePayAB.pem');
    curl_setopt($curl, CURLOPT_SSLKEY, 'turtlepay2.key');
    curl_setopt($curl, CURLOPT_SSLCERT, 'turtlepay2.pem');
    curl_setopt($curl, CURLOPT_SSLCERTPASSWD, 'Fk&1618BKl@tp');
    curl_setopt($curl, CURLOPT_SSL_VERIFYHOST, 0);
    curl_setopt($curl, CURLOPT_SSL_VERIFYPEER, 0);
    $result = curl_exec($curl);
    curl_close($curl);

    if(!$result) {
        $reply->code = "0";
        $reply->denied_code = "bankid_problem";
        return $reply;
        die('');
    }

    $authObject = json_decode($result);
    if (isset($authObject->orderRef)) {
        $reply->code = "1";
        $reply->order_ref = $authObject->orderRef;
        $reply->denied_code = "";
        $reply->auto_start_token = $authObject->autoStartToken; // Till lögg för Web App
        
    }
    else if (isset($authObject->errorCode)) {
        $reply->code = "0";
        $reply->denied_code = $authObject->errorCode;
    }
    else {
        $reply->code = "0";
        $reply->denied_code = "bankid_problem";
    }

    return $reply;
}

function _BankIDSignCollect($data) {

    $reply = new StdClass();

    $json = '{"orderRef":"' . $data->_order_ref . '"}';
    $curlCheck = curl_init();
    curl_setopt( $curlCheck, CURLOPT_URL, 'https://appapi2.bankid.com/rp/v5/collect');
    //curl_setopt( $curlCheck, CURLOPT_URL, 'https://appapi2.test.bankid.com/rp/v5/collect');
    curl_setopt($curlCheck, CURLOPT_CUSTOMREQUEST, "POST");
    curl_setopt($curlCheck, CURLOPT_POSTFIELDS, $json);
    curl_setopt($curlCheck, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($curlCheck, CURLOPT_HTTPHEADER, array(
        'Content-Type: application/json',
        'Content-Length: ' . strlen($json))
    );
    //curl_setopt($curlCheck, CURLOPT_CAINFO, 'appapi.test.bankid.com.pem');
    //curl_setopt($curlCheck, CURLOPT_SSLCERT, '_test.pem');
    //curl_setopt($curlCheck, CURLOPT_SSLCERTPASSWD, 'qwerty123');
    curl_setopt($curlCheck, CURLOPT_CAINFO, 'bankid.ca.pem');
    //curl_setopt($curlCheck, CURLOPT_SSLKEY, 'TurtlePayAB.key');
    //curl_setopt($curlCheck, CURLOPT_SSLCERT, 'TurtlePayAB.pem');
    curl_setopt($curlCheck, CURLOPT_SSLKEY, 'turtlepay2.key');
    curl_setopt($curlCheck, CURLOPT_SSLCERT, 'turtlepay2.pem');
    curl_setopt($curlCheck, CURLOPT_SSLCERTPASSWD, 'Fk&1618BKl@tp');

    curl_setopt($curlCheck, CURLOPT_SSL_VERIFYHOST, 0);
    curl_setopt($curlCheck, CURLOPT_SSL_VERIFYPEER, 0);

    $status = false; // Set true when a complete, fail or inknown error occur

    $result = curl_exec($curlCheck);
    if(!$result) {
        $reply->code = "0";
        $reply->denied_code = "bankid_problem";
        return $reply;
        die('');
    }
    else {
        $collectObject = json_decode($result);
        if (isset($collectObject->errorCode)){
            $reply->code = 0;
            $reply->denied_code = $collectObject->details;
            $status = true;
        } else {
            $collectObject = json_decode($result);
            switch ($collectObject->status) {
                case 'pending':
                    $reply->code = "2";
                    $reply->denied_code = 'Pending';
                    $status = true;
                    break;
                case 'failed':
                    $reply->code = "0";
                    $reply->denied_code = $collectObject->hintCode;
                    $status = true;
                    break;
                case 'complete':
                    $reply->code = "1";
                    $reply->name = $collectObject->completionData->user->name;
                    $reply->givenName = $collectObject->completionData->user->givenName;
                    $reply->surname = $collectObject->completionData->user->surname;
                    $reply->ipAddress = $collectObject->completionData->device->ipAddress;
                    $reply->signature = $collectObject->completionData->signature;
                    $reply->ocspResponse = $collectObject->completionData->ocspResponse;
                    $status = true;
                    break;
                default:
                    $reply->code = "0";
                    $reply->denied_code = "bankid_problem";
                    $status = true;
                    //echo "Okänt fel";
            }
        }
    }
    //print_r($bankIdResult);
    return $reply;
}