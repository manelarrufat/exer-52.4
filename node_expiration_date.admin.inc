<?php
/**
* @file
* Resultado de llamadas a páginas de administración para el módulo 
* Node Expiration Date.
*/

/**
* Constructor del formulario para configurar el módulo.
*
*/
function node_expiration_date_admin_settings() {
  /**
  * Con node_type_get_types() se obtiene la información de todos los tipos 
  * de contenido, cada uno como un objeto, por lo que hay que seleccionar 
  * sólo los nombres de los tipo de contenido para mostrarlos en las opciones.
  */
  $content_types_list = node_type_get_types();
  foreach ($content_types_list as $key => $type) {
    $list[$key] = $type->name;
  }
  $form['node_expiration_date_node_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Add an expiration date to these content types'),
    '#options' => $list,
    //la variable usada para guardar el valor de la configuración 
    //es aconsejable que se llame igual al campo del formulario 
    //usado, en este caso 'node_expiration_date_node_types'.
    '#default_value' => variable_get('node_expiration_date_node_types',
      array('page')),
    '#description' => t( 'The selected content types will have an expiration date.'),
  );
  //Definimos la fecha que será considerada por defecto
  $actual_date = array ('day' => date('d'), 'month' => date('m'), 'year' => date('Y'));
  $form['default_expiration_date'] = array(
    '#type' => 'date',
    '#title' => t('Default expiration date'),
    //Si no está definida la fecha asignamos fecha actual
    '#default_value' => variable_get('default_expiration_date', $actual_date),
    '#description' => t('Select the default expiration date'),
  );
  return system_settings_form($form);
}

function node_expiration_date_admin_settings_validate($form, &$form_state) {
  $actual_date = array ('day' => date('d'), 'month' => date('m'), 'year' => date('Y'));
  $date_form = $form_state['values']['default_expiration_date'];
  if ($actual_date['year'] >= $date_form['year'] && 
      $actual_date['month'] >= $date_form['month'] &&
      $actual_date['day'] >= $date_form['day']) {
    form_set_error('default_expiration_date', t('The date must be higher than today'));
  }
}