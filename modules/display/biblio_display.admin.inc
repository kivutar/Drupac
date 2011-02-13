<?php

function biblio_display_admin_theme_fields_form($form, &$form_state, $theme_name = 'simple') {

	drupal_add_css(drupal_get_path('module', 'biblio_display') . '/field.css');
	$config = get_biblio_display_theme_config($theme_name);
	$form['fields'] = array();
	foreach ( $config['fields'] as $name => $data ) {
		$form['fields'][$name]['field_label'] = array(
      		'#type' => 'item',
      		'#markup' => $data['label'],
    	);
		$form['fields'][$name]['field_name'] = array(
      		'#type' => 'item',
      		'#markup' => $name,
    	);
		$form['fields'][$name]['field_region'] = array(
    		'#type' => 'select',
    		'#default_value' => $data['region'],
    		'#options' => $config['regions'],
    	);
	}
	$form['submit'] = array(
		'#type' => 'submit',
  		'#value' => t('Save configuration'),
	);
	return $form;
}

function template_preprocess_biblio_display_admin_theme_fields_form(&$variables) {
	$variables['field_listing'] = array();
	foreach (element_children($variables['form']['fields']) as $name) {
		$field = $variables['form']['fields'][$name];
		$variables['field_listing'][$name] = new stdClass();
		$variables['field_listing'][$name]->label = drupal_render($field['field_label']);
		$variables['field_listing'][$name]->name = drupal_render($field['field_name']);
		$variables['field_listing'][$name]->region = drupal_render($field['field_region']);
		$variables['field_listing'][$name]->printed = FALSE;
	}

	$variables['form_submit'] = drupal_render($variables['form']['submit']);
}

function biblio_display_admin_settings_form($form, &$form_state) {
	$current_theme = variable_get('bd_current_theme', 'simple');
	$config = get_biblio_display_theme_config($current_theme);

    $output = biblio_display_theme_settings_table($config);
	$themes_list = biblio_display_get_availables_themes();
	$form['bd_current_theme'] = array(
		'#type' => 'tableselect',
		'#title' => t('Sub theme'),
		'#header' => array( 'theme_name' => t('Theme Name'), 'configure' => t('Operation')),
		'#options' => $themes_list,
		'#default_value' => $current_theme,
		'#description' => t('Name of the theme to use.'),
		'#multiple' => FALSE,
		'#empty' => t('No subtheme available'),
		'#ajax' => array(
			'wrapper' => 'wrapper-themesettings',
			'callback' => 'ajax_biblio_display_settings_callback',
			'method' => 'replace',
			'effect' => 'fade',
			'event' => 'change',
		),
	);
	$form['config_overview'] =array(
    	'#type' => 'fieldset',
    	'#title' => t('Theme configuration overview'),
    	'#collapsible' => TRUE,
    	'#collapsed' => TRUE,
	);
	$form['config_overview']['wrapper_themesettings'] = array(
		'#prefix' => '<div id="wrapper-themesettings">',
		'#suffix' => '</div>',
		'#type' => 'item',
		'#markup' => $output,
	);
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Save configuration'),
	);
    return $form;
}

function biblio_display_admin_settings_form_submit($form, &$form_state) {
	$themename = $form_state['values']['bd_current_theme'];
	variable_set('bd_current_theme', $themename);
}

function ajax_biblio_display_settings_callback($form, $form_state) {
	$theme_name = $form_state['values']['bd_current_theme'];
	$config = get_biblio_display_theme_config($theme_name);

	$output = biblio_display_theme_settings_table($config);

	$form['wrapper_themesettings'] = array(
			'#prefix' => '<div id="wrapper-themesettings">',
    		'#suffix' => '</div>',
			'#type' => 'item',
			'#markup' => $output,
		);
	return $form['wrapper_themesettings'];
}

function biblio_display_theme_settings_table($config) {
	$header = array( 'field_label' => t('Field Label'), 'field_name' => t('Field Name'), 'region' => t('Region'));
	$rows = array();
	foreach ($config['fields'] as $id => $field) {
		$rows[ $id ] = array(
			'field_label' => $field['label'],
			'field_name' => $id,
			'region'     => $field['region'],
		);
		
	}
	$output = theme('table', array('header' => $header, 'rows' => $rows));
	return $output;
}
