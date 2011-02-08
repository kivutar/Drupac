<?php

function biblio_display_admin_settings() {
	$fields = field_info_instances('node', 'biblio_record');
    $output = '<table>';
	$output .= '<tr><td>Field name</td></tr>';
	foreach ($fields as $field) {
		$output .= '<tr><td>' . $field['label'] . '</td></tr>';
	}
	$output .= '</table>';
	$themes_list = biblio_display_themes_list();
	$form = array();
	if ( !count($themes_list) ) {
		$form['notheme'] = array(
    		'#type' => 'markup',
    		'#value' => '<h2>no subtheme available</h2>',
  		);
	} else {
    	$form['bd_current_theme'] = array(
        	'#type' => 'radios',
        	'#title' => t('Sub theme'),
      	  	'#default_value' => variable_get('bd_current_theme', 'simple'),
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

function ajax_biblio_display_settings_callback($form, $form_state) {
	$theme_name = $form_state['values']['bd_current_theme'];
	$fields = field_info_instances('node', 'biblio_record');
	$output = '<table>';
	$output .= '<tr><td>Field name</td></tr>';
	foreach ($fields as $field) {
		$output .= '<tr><td>' . $field['label'] . '</td></tr>';
	}
	$output .= '</table>';
	$form['wrapper_themesettings'] = array(
			'#prefix' => '<div id="wrapper-themesettings">',
    		'#suffix' => '</div>',
			'#type' => 'item',
			'#markup' => $output,
		);
	return $form['wrapper_themesettings'];
}

function biblio_display_theme_settings() {
	$content = '<div>Coucou</div>';
	print drupal_to_js(array('data' => $content, 'status' => true));
	exit();
}

function biblio_display_themes_list() {
	$base_dir = drupal_get_path('module', 'biblio_display') . '/themes';
	$dir = opendir($base_dir);

	$themes_list = array();
	$folders = array();

	while($element = readdir($dir)) {
		if($element != '.' && $element != '..') {
			if (is_dir($base_dir.'/'.$element)) {
				$folders[] = $element;
			}
		}
	}
	closedir($dir);
	if ( count($folders) ) {
		foreach ( $folders as $theme ) {
			$config = array();
			$config = biblio_display_get_theme_config($theme);
			$themes_list[ $theme ] = $config['name'];
		}
	}
	return $themes_list;
}
