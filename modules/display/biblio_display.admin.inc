<?php

function biblio_display_admin_settings_form($form, &$form_state) {
	$current_theme = variable_get('bd_current_theme', 'simple');
	$config = get_biblio_display_theme_config($current_theme);

    $output = '<table>';
	$output .= '<tr><td>Field name</td></tr>';
	foreach ($config['fields'] as $field) {
		$output .= '<tr><td>' . $field['label'] . '</td></tr>';
	}
	$output .= '</table>';
	$themes_list = get_biblio_display_availables_themes();
	if ( !count($themes_list) ) {
		$form['notheme'] = array(
    		'#type' => 'markup',
    		'#value' => '<h2>no subtheme available</h2>',
  		);
	} else {
    	$form['bd_current_theme'] = array(
        	'#type' => 'radios',
        	'#title' => t('Sub theme'),
      	  	'#default_value' => $current_theme,
			'#options' => $themes_list,
        	'#description' => t('Name of the theme to use.'),
			'#ajax' => array(
				'wrapper' => 'wrapper-themesettings',
				'callback' => 'ajax_biblio_display_settings_callback',
				'method' => 'replace',
				'effect' => 'fade',
				'event' => 'change',
			),
    	);
		$form['wrapper_themesettings'] = array(
			'#prefix' => '<div id="wrapper-themesettings">',
    		'#suffix' => '</div>',
			'#type' => 'item',
			'#markup' => $output,
		);
	}
    return $form;
}

function biblio_display_admin_settings_form_submit($form, &$form_state) {
	$themename = $form_state['values']['bd_current_theme'];
	variable_set('bd_current_theme', $themename);
}

function ajax_biblio_display_settings_callback($form, $form_state) {
	$theme_name = $form_state['values']['bd_current_theme'];
	$config = get_biblio_display_theme_config($theme_name);
#	var_dump($config['regions']);
	$output2 = biblio_display_theme_settings_table($config);

	$output = '<table>';
	$output .= '<tr><td>Field name</td></tr>';
	foreach ($config['fields'] as $field) {
		$output .= '<tr><td>' . $field['label'] . ' - ' . $field['region'] . '</td></tr>';
	}
	$output .= '</table>';
	$form['wrapper_themesettings'] = array(
			'#prefix' => '<div id="wrapper-themesettings">',
    		'#suffix' => '</div>',
			'#type' => 'item',
			'#markup' => $output2,
		);
	return $form['wrapper_themesettings'];
}

function biblio_display_theme_settings_table($config) {
	$output = '<table>';
	$output .= '<tr><th>Field</th><th>Region</th></tr>';
	foreach ($config['fields'] as $field) {
		$select = '<select>';
		foreach ($config['regions'] as $name => $label ) {
			if ( $name == $field['region']) {
				$select .= '<option selected="selected" value="' . $name . '">' . $label . '</option>';
			} else {
				$select .= '<option value="' . $name . '">' . $label . '</option>';
			}
		}
		$select .= '</select>';
		$output .= '<tr><td>' . $field['label'] . '</td><td>' . $select . '</td></tr>';
	}
	$output .= '</table>';
	return $output;
}
