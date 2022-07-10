<?php
    function FormItemCreate($label, $name, $id, $class, $labelClass="", $required=true) {
        $html = '<div class="field is-horizontal">';
            if ($labelClass != 'no-label') {
                $html .= '<div class="field-label is-small">';
                    $html .= '<label class="label is-small has-text-black-ter ' . $labelClass . '">' . $label . '</label>';
                $html .= '</div>';
            }
            $html .= '<div class="field-body">';
                $html .= '<div class="field">';
                    $html .= '<div class="control">';
                        $html .= '<input class="input is-dark is-small ' . $class . '" ';
                        if (isset($name)) {
                            $html .= 'name="'. $name . '" ';
                        }
                        if (isset($id)) {
                            $html .= 'id="'. $id . '" ';
                        }
                        if (isset($name)) {
                            $html .= 'name="'. $name . '" ';
                        }
                        if ($required) {
                            $html .= ' require="yes" ';
                        }
                        $html .= '>';
                    $html .= '</div>';
                $html .= '</div>';
            $html .= '</div>';
        $html .= '</div>';
        return $html;
    }
?>
