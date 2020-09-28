<?php

echo 'form_alter';
function dynamic_fields_form_node_form_alter(&$form, &$form_state, $form_id) {

  $node = $form['#node'];
  $form['dynamic_field_1'] = array(
    '#type' => 'checkbox',
    '#title' => t('test 1'),
    '#description' => t('test'),
    '#default_value' => $node->dynamic_fields['dynamic_field_1'],
    '#ajax' => array(
      'callback' => 'dynamic_fields_form_node_callback',
      'wrapper' => 'dynamic-fields-form-node',
      'effect' => 'fade',
    ),
  );
  
  
  $form['container'] = array(
    '#prefix' => '<div id="dynamic-fields-form-node">',
    '#suffix' => '</div>',
  );

  // If the state values exist and 'ajax_example_1' state value is 1 or
  // if the state values don't exist and 'example1' variable is 1 then
  // display the ajax_example_2 field.
 if (!empty($form_state['values']['dynamic_field_1']) && $form_state['values']['dynamic_field_1'] == 1
      || empty($form_state['values']) && $node->dynamic_fields['example_1']) {

    $form['container']['dynamic_field_2'] = array(
      '#type' => 'textfield',
      '#title' => t('AJAX Example 2'),
      '#description' => t('AJAX Example 2'),
      '#default_value' => empty($form_state['values']['dynamic_field_2']) ? $node->dynamic_fields['dynamic_field_2'] : $form_state['values']['dynamic_field_2'],
    );
  }
}

function dynamic_fields_form_node_callback($form, $form_state) {
  return $form['container'];
}

/**
 * Implements hook_node_submit().
 * @see ajax_example_form_node_form_alter()
 */
function dynamic_fields_node_submit($node, $form, &$form_state) {
  $values = $form_state['values'];
  // Move the new data into the node object.
  $node->dynamic_fields['dynamic_field_1'] = $values['dynamic_field_1'];
  // Depending on the state of ajax_example_1; it may not exist.
  $node->dynamic_fields['dynamic_field_2'] = isset($values['dynamic_field_2']) ? $values['dynamic_field_2'] : '';
}

/**
 * Implements hook_node_prepare().
 *
 * @see ajax_example_form_node_form_alter()
 */
function dynamic_fields_node_prepare($node) {
  if (empty($node->dynamic_fields)) {
    // Set default values, since this only runs when adding a new node.
    $node->dynamic_fields['dynamic_field_1'] = 0;
    $node->dynamic_fields['dynamic_field_2'] = '';
  }
}
                                      
/**
 * Implements hook_node_load().
 *
 * @see dynamic_fields_form_node_form_alter()
 */
function dynamic_fields_node_load($nodes, $types) {
  $result = db_query('SELECT * FROM {dynamic_fields_node_form_alter} WHERE nid IN(:nids)', array(':nids' => array_keys($nodes)))->fetchAllAssoc('nid');

  foreach ($nodes as &$node) {
    $node->dynamic_fields['dynamic_field_1']
      = isset($result[$node->nid]->dynamic_field_1) ?
      $result[$node->nid]->dynamic_field_2 : 0;
    $node->dynamic_fields['example_2']
      = isset($result[$node->nid]->dynamic_field_2) ?
      $result[$node->nid]->dynamic_field_2 : '';
  }
}

/**
 * Implements hook_node_insert().
 *
 * @see ajax_example_form_node_form_alter()
 */
function dynamic_fields_node_insert($node) {
  if (isset($node->dynamic_fields)) {
    db_insert('dynamic_fields_node_form_alter')
      ->fields(array(
        'nid' => $node->nid,
        'dynamic_field_1' => $node->dynamic_fields['dynamic_field_1'],
        'dynamic_field_2' => $node->dynamic_fields['dynamic_field_2'],
      ))
      ->execute();
  }
}

/**
 * Implements hook_node_update().
 * @see ajax_example_form_node_form_alter()
 */
function dynamic_fields_node_update($node) {
  if (db_select('dynamic_fields_node_form_alter', 'a')->fields('a')->condition('nid', $node->nid, '=')->execute()->fetchAssoc()) {
    db_update('dynamic_fields_node_form_alter')
      ->fields(array(
        'dynamic_field_1' => $node->dynamic_fields['dynamic_field_1'],
        'dynamic_field_2' => $node->dynamic_fields['dynamic_field_2'],
      ))
      ->condition('nid', $node->nid)
      ->execute();
  }
  else {
    // Cleaner than doing it again.
    dynamic_fields_node_insert($node);
  }
}

/**
 * Implements hook_node_delete().
 * @see dynamic_fields_form_node_form_alter()
 */
function dynamic_fields_node_delete($node) {
  db_delete('dynamic_fields_node_form_alter')
    ->condition('nid', $node->nid)
    ->execute();
}
