<?php

function sigb_connector_admin_settings() {
    $form['sigb_connector'] = array(
        '#type' => 'textfield',
        '#title' => t('SIGB Connector'),
        '#default_value' => variable_get('sigb_connector', 'ilsdi_connector'),
        '#description' => t('Name of the SIGB connector to use.'),
    );
    return system_settings_form($form);
}

