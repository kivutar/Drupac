<?php

function ilsdi_connector_admin_settings() {
    $form['ilsdi_server'] = array(
        '#type' => 'textfield',
        '#title' => t('ILSDI Server address'),
        '#default_value' => variable_get('ilsdi_server', 'http://opac.koha.localhost/cgi-bin/koha/ilsdi.pl'),
        '#description' => t('Address of the ILSDI you want to connect.'),
    );
    return system_settings_form($form);
}

