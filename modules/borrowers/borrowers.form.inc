<?php

function borrowers_patron_card_checking_form() {
    global $user;

    if ( $user->uid != 0 ) {
	$cardnumber = borrowers_get_cardnumber($user->uid);
	$form['patron_card'] = array(
	    '#type' => 'textfield',
	    '#title' => t('Your cardnumber:'),
	    '#size' => 60,
	    '#default_value' => $cardnumber,
	    '#maxlength' => 64,
	    '#description' => t('Enter here your library cardnumber'),
	);

	if ( variable_get('drupac_adress_check', 0) ) {
	    $form['patron_adress'] = array(
		'#type' => 'textfield',
		'#title' => t('Your adress:'),
		'#size' => 60,
		'#maxlength' => 64,
		'#description' => t('Enter here your adress'),
	    );
	}

	if ( variable_get('drupac_phone_check', 0) ) {
	    $form['patron_phone'] = array(
		'#type' => 'textfield',
		'#title' => t('Your phone number:'),
		'#size' => 60,
		'#maxlength' => 64,
		'#description' => t('Enter here your phone number'),
	    );
	}

	if ( variable_get('drupac_email_check', 0) ) {
	    $form['patron_email'] = array(
		'#type' => 'textfield',
		'#title' => t('Your email adress:'),
		'#size' => 60,
		'#maxlength' => 64,
		'#description' => t('Enter here your email adress'),
	    );
	}

	$form['submit'] = array(
	    '#type' => 'submit',
	    '#value' => t('Valid'),
	);
    } else {
	$form['invalid_user'] = array(
	    '#type' => 'item',
	    '#markup' => '<h3>You must be logged</h3>',
	);
    }
    return $form;
}

function borrowers_admin_settings_form() {
    global $base_url;
    $form['patron_card_check'] = array(
	'#type' => 'fieldset',
	'#title' => t('Patron card checking'),
        '#collapsible' => TRUE,
        '#collapsed' => FALSE,
    );
    $form['patron_card_check']['drupac_adress_check'] = array(
	'#type' => 'checkbox',
	'#title' => t('Ask for adress'),
	'#default_value' => variable_get('drupac_adress_check', 0),
    );
    $form['patron_card_check']['drupac_phone_check'] = array(
	'#type' => 'checkbox',
	'#title' => t('Ask for phone number'),
	'#default_value' => variable_get('drupac_phone_check', 0),
    );
    $form['patron_card_check']['drupac_email_check'] = array(
	'#type' => 'checkbox',
	'#title' => t('Ask for email adress'),
	'#default_value' => variable_get('drupac_email_check', 0),
    );
    $form['patron_card_check']['check_page'] = array(
	'#type' => 'item',
	'#markup' => '<a href="' . $base_url . '/drupac/patron_card">View checking page</a>',
    );
    return system_settings_form($form);
}

function borrowers_patron_card_checking_form_validate($form, &$form_state) {
    if ( !$form_state['values']['patron_card'] ) {
	drupal_set_message( 'Please enter a cardnumber', 'error');
    }
}

function borrowers_patron_card_checking_form_submit($form, &$form_state) {
    global $user;
    $uid = $user->uid;

    $cardnumber = $form_state['values']['patron_card'];
    $patron_info = sigb_connector_patron_info( $cardnumber );
    $is_valid = 1;

    if ( $patron_info ) {
	if ( variable_get('drupac_adress_check', 0) && $patron_info['address'] != $form_state['values']['patron_adress'] ) {
	    $is_valid = 0;
	}
	if ( variable_get('drupac_phone_check', 0) && $patron_info['tel1'] != $form_state['values']['patron_phone'] ) {
	    $is_valid = 0;
	}
	if ( variable_get('drupac_email_check', 0) && $patron_info['email'] != $form_state['values']['patron_email'] ) {
	    $is_valid = 0;
	}
    } else {
	$is_valid = 0;
	drupal_set_message( 'Invalid cardnumber', 'error');
    }

    if ( $is_valid ) {
	db_query("INSERT INTO {borrowers_card_verify} VALUES ($uid, '$cardnum', 1, NOW())");
    }
}
