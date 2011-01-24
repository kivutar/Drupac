<?php

function harvest_drush_command() {
    $items = array();

    $items['harvest-import-records'] = array(
        'callback'    => 'harvest_drush_import_records',
        'description' => dt('Import a set of records into Drupac.'),
        'arguments'   => array(
            'offset'  => dt('Mandatory. Number of record to skip.'),
            'number'  => dt('Mandatory. Number of records to import.'),
            
        ),
        'aliases'     => array('hir'),
    );

    return $items;
}

function harvest_drush_help($section) {
    switch ($section) {
        case 'drush:harvest-import-records':
            return dt('Import a set of records into Drupac.');
    }
}

function harvest_drush_import_records() {
    $args = func_get_args();
    if (count($args) == 2) {
        print harvest_import_records($args[0], $args[1]);
    }
}

