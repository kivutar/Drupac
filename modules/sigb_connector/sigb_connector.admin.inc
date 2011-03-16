<?php

function sigb_connector_admin_settings() {
    $fields_config =  sigb_connector_get_fields_config();

    $form['sigb_connector'] = array(
        '#type' => 'textfield',
        '#title' => t('SIGB Connector'),
        '#default_value' => variable_get('sigb_connector', 'ilsdi_connector'),
        '#description' => t('Name of the SIGB connector to use.'),
    );

    $form['sigb_connector_fields_settings'] = array(
        '#type' => 'fieldset',
        '#title' => t('View fields settings'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
    );

    foreach ( $fields_config as $name => $field) {
	$repetable = $field['repeatable'] ? 'repeatable' : 'no repeatable';
        $form['sigb_connector_fields_settings'][ $name ] = array(
            '#type' => 'item',
            '#markup' => '<div><b>' . $field['label'] . ': </b>' . $field['bindto'] . ' (' . $repetable . ')</div>',
        );

    }
    return system_settings_form($form);
}
