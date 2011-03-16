<?php

function sigb_connector_admin_settings() {
    $form['sigb_connector'] = array(
        '#type' => 'textfield',
        '#title' => t('SIGB Connector'),
        '#default_value' => variable_get('sigb_connector', 'ilsdi_connector'),
        '#description' => t('Name of the SIGB connector to use.'),
    );

    $form['sigb_connector_fields_settings'] = array(
        '#type' => 'fieldset',
        '#title' => t('Fields settings'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
    );

    $fields_of_biblio_record = field_info_instances('node', 'biblio_record');
    foreach ( $fields_of_biblio_record as $name => $field) {
        $form['sigb_connector_fields_settings'][ $name ] = array(
            '#type' => 'select',
            '#title' => $field['label'],
            '#default_value' => 'un',
            '#options' => array( 'un' => 'Un', 'deux' => 'Deux' ),
            '#description' => t('Enter the name for this group of settings'),
        );

    }
    return system_settings_form($form);
}

