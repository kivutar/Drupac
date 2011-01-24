<?php

function sigb_connector_drush_command() {
    $items = array();

    $items['sigb-connector-scrape-bib'] = array(
        'callback'    => 'sigb_connector_drush_scrape_bib',
        'description' => dt('Grabs bib info from the SIGB and returns it in a Drupac-ready array.'),
        'arguments'   => array(
            'id'      => dt('Mandatory. Bib number to scrape.'),
        ),
        'aliases'     => array('csb'),
    );
    $items['sigb-connector-item-status'] = array(
        'callback'    => 'sigb_connector_drush_item_status',
        'description' => dt('Parses item status for a particular bib item.'),
        'arguments'   => array(
            'id'      => dt('Mandatory. Bib number to query.'),
        ),
        'aliases'     => array('cis'),
    );
    $items['sigb-connector-patron-info'] = array(
        'callback'    => 'sigb_connector_drush_patron_info',
        'description' => dt('Returns an array of patron information.'),
        'arguments'   => array(
            'cardnum' => dt('Mandatory. Patron card number.'),
        ),
        'aliases'     => array('cpi'),
    );
    $items['sigb-connector-patron-checkouts'] = array(
        'callback'    => 'sigb_connector_drush_patron_checkouts',
        'description' => dt('Returns an array of patron checkouts.'),
        'arguments'   => array(
            'cardnum' => dt('Mandatory. Patron card number.'),
            'pin'     => dt('Optional. Patron pin/password.'),
        ),
        'aliases'     => array('cpc'),
    );
    $items['sigb-connector-patron-holds'] = array(
        'callback'    => 'sigb_connector_drush_patron_holds',
        'description' => dt('Returns an array of patron holds.'),
        'arguments'   => array(
            'cardnum' => dt('Mandatory. Patron card number.'),
            'pin'     => dt('Optional. Patron pin/password.'),
        ),
        'aliases'     => array('cph'),
    );
    $items['sigb-connector-renew-items'] = array(
        'callback'    => 'sigb_connector_drush_renew_items',
        'description' => dt('Renews items and returns the renewal result.'),
        'arguments'   => array(
            'cardnum' => dt('Mandatory. Patron card number.'),
            'pin'     => dt('Optional. Patron pin/password.'),
            'items'   => dt('Optional. Array of varname => item numbers to be renewed, or NULL for everything.'),
        ),
        'aliases'     => array('cri'),
    );
    $items['sigb-connector-cancel-holds'] = array(
        'callback'    => 'sigb_connector_drush_cancel_holds',
        'description' => dt('Cancels holds.'),
        'arguments'   => array(
            'cardnum' => dt('Mandatory. Patron card number.'),
            'pin'     => dt('Optional. Patron pin/password.'),
            'items'   => dt('Optional. Array of varname => item numbers to be renewed, or NULL for everything.'),
        ),
        'aliases'     => array('cch'),
    );
    $items['sigb-connector-place-hold'] = array(
        'callback'    => 'sigb_connector_drush_place_hold',
        'description' => dt('Places holds.'),
        'arguments'   => array(
            'cardnum'    => dt('Mandatory. Patron card number.'),
            'bnum'       => dt('Mandatory. Bib item record number to place a hold on.'),
            'inum'       => dt('Optional. Item number to place a hold on if required'),
            'pin'        => dt('Optional. Patron pin/password.'),
            'pickup_loc' => dt('Optional. Pickup location value.'),
        ),
        'aliases'     => array('cplh'),
    );
    $items['sigb-connector-patron-fines'] = array(
        'callback'    => 'sigb_connector_drush_patron_fines',
        'description' => dt('Returns an array of patron fines.'),
        'arguments'   => array(
            'cardnum' => dt('Mandatory. Patron card number.'),
            'pin'     => dt('Optional. Patron pin/password.'),
        ),
        'aliases'     => array('cpf'),
    );
    $items['sigb-connector-pay-patron-fines'] = array(
        'callback'    => 'sigb_connector_drush_pay_patron_fines',
        'description' => dt('Pays patron fines.'),
        'arguments'   => array(
            'cardnum'         => dt('Mandatory. Patron card number.'),
            'pin'             => dt('Optional. Patron pin/password.'),
            'payment_details' => dt('Mandatory. Payment details.'),
        ),
        'aliases'     => array('cppf'),
    );

    return $items;
}

function sigb_connector_drush_help($section) {
    switch ($section) {
        case 'drush:sigb-connector-scrape-bib':
            return dt('Grabs bib info from the SIGB and returns it in a Drupac-ready array.');
        case 'drush:sigb-connector-item-status':
            return dt('Parses item status for a particular bib item.');
        case 'drush:sigb-connector-patron-info':
            return dt('Returns an array of patron information.');
        case 'drush:sigb-connector-patron-checkouts':
            return dt('Returns an array of patron checkouts.');
        case 'drush:sigb-connector-patron-holds':
            return dt('Returns an array of patron holds.');
        case 'drush:sigb-connector-renew-items':
            return dt('Renews items and returns the renewal result.');
        case 'drush:sigb-connector-cancel-holds':
            return dt('Cancels holds.');
        case 'drush:sigb-connector-place-hold':
            return dt('Places holds.');
        case 'drush:sigb-connector-patron-fines':
            return dt('Returns an array of patron fines.');
        case 'drush:sigb-connector-pay-patron-fines':
            return dt('Pays patron fines.');
    }
}

function sigb_connector_drush_scrape_bib() {
    $args = func_get_args();
    if (count($args) == 1) {
        print_r(sigb_connector_scrape_bib($args[0]));
    }
}

function sigb_connector_drush_item_status() {
    $args = func_get_args();
    if (count($args) == 1) {
        print_r(sigb_connector_item_status($args[0]));
    }
}

function sigb_connector_drush_patron_info() {
    $args = func_get_args();
    if (count($args) == 1) {
        print_r(sigb_connector_patron_info($args[0]));
    }
}

function sigb_connector_drush_patron_checkouts() {
    $args = func_get_args();
    if (count($args) == 1) {
        print_r(sigb_connector_patron_checkouts($args[0]));
    } elseif (count($args) == 2) {
        print_r(sigb_connector_patron_checkouts($args[0], $args[1]));
    }
}

function sigb_connector_drush_patron_holds() {
    $args = func_get_args();
    if (count($args) == 1) {
        print_r(sigb_connector_patron_holds($args[0]));
    } elseif (count($args) == 2) {
        print_r(sigb_connector_patron_holds($args[0], $args[1]));
    }
}

function sigb_connector_drush_renew_items() {
    $args = func_get_args();
    #TODO
}

function sigb_connector_drush_cancel_holds() {
    $args = func_get_args();
    #TODO
}

function sigb_connector_drush_place_hold() {
    $args = func_get_args();
    #TODO
}

function sigb_connector_drush_patron_fines() {
    $args = func_get_args();
    if (count($args) == 1) {
        print_r(sigb_connector_patron_fines($args[0]));
    } elseif (count($args) == 2) {
        print_r(sigb_connector_patron_fines($args[0], $args[1]));
    }
}

function sigb_connector_drush_pay_patron_fines() {
    $args = func_get_args();
    #TODO
}

