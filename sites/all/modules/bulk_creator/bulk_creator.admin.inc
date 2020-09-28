<?php

/**
 * @file
 * Bulk admin configuration functions.
 */

/**
 * Returns the array of node types options.
 *
 * @return array
 *   An array of node types options.
 */
function bulk_get_options_node_types() {
  $types = node_type_get_types();
  $options = array();

  foreach ($types as $type) {
    $options[$type->type] = $type->name;
  }
  return $options;
}

/**
 * The options related to a field.
 *
 * @param string $type
 *   The type of the field.
 * @param bool   $empty
 *   The field has an empty choice.
 *
 * @return array
 *   The array of options
 */
function bulk_get_options_fields($type, $empty = FALSE) {
  $all_fields = field_info_field_map();
  $options = array();
  if ($empty) {
    $options[""] = "";
  }
  foreach ($all_fields as $k => $f) {
    if ($f['type'] == $type) {
      $options[$k] = $k;
    }
  }
  return $options;
}

/**
 * Menu callback: Bulk Settings Form.
 */
function bulk_creator_admin_settings() {
  $form = array();
  $form['#submit'][] = 'bulk_creator_admin_settings_submit';

  $text_example = "# Add a new_type content, because it does not exists, and a field on it:
new_type; number_integer; field_price_01; My new Price Field; This is the price of the item; FALSE; 0; group_new; €
# Add the fields field_text_b8, ...b9, ...c0, ...c1, field_text_c2 to article
article; text; field_text_[b8--c2]; My New Text Field in Article;
# Add a new text field in new_type, take care of all the labels.
new_type; text; new_text_field;";

  $line_syntax = "&lt;line_command&gt; := &lt;content_type&gt;; &lt;field_type&gt;; &lt;field_machine_name&gt;; \n" .
      "     [&lt;field_label&gt;;] [&lt;field_required&gt;;] [&lt;field_description&gt;;] [&lt;field_default&gt;;] \n".
      "     [&lt;field_group&gt;;] [&lt;field_prefix&gt;;] [&lt;field_suffix&gt;;]";

  $log_tokens = array(
    '!readme' => '<a href="/' . BULK_PATH . '/README.txt' . '" target="_blank">README.txt</a>',
    '!text_example' => $text_example,
    '!line_syntax' => $line_syntax);

  $form['bulk_creator_field_creator'] = array(
    '#type' => 'textarea',
    '#default_value' => variable_get('bulk_field_creator', $text_example),
    '#size' => 100,
    '#title' => t('The bulk creator script'),
    '#required' => TRUE,
    '#description' => t(
        'Paste your Bulk Script here and submit the form to launch it. <br />
        See the file !readme to know more.
        <p /><b>Line Syntax:</b><br />
        <pre>!line_syntax</pre>
        <p /><b>Example:</b><br />
        <pre>!text_example</pre>', $log_tokens
    ),
  );

  $form['bulk_creator_parse_script_callback'] = array(
    '#type' => 'textfield',
    '#default_value' => variable_get('bulk_creator_parse_script_callback', ''),
    '#size' => 30,
    '#maxlength' => 100,
    '#title' => t('Call this callback to parse a line'),
    '#required' => FALSE,
    '#description' => t(
        "If you fill this field, your callback will be called.<br />
        The parameter is each line of the bulk script.<br />
        See <i>bulk_custom_field_add_balance</i> as an example."
    ),
  );

  $form['bulk_creator_separator_field'] = array(
    '#type' => 'select',
    '#options' => array(';' => ';', '\t' => '\t'),
    '#default_value' => variable_get('bulk_creator_separator_field', ';'),
    '#title' => t('Fields separator'),
    '#required' => TRUE,
    '#description' => t('Select the character that separates fields in a script line.'),
  );

  return system_settings_form($form);
}

/**
 * The submit callback of the form.
 */
function bulk_creator_admin_settings_submit($form, &$form_state) {
  $b_script = $form['bulk_creator_field_creator']['#value'];
  $b_callback = $form['bulk_creator_parse_script_callback']['#value'];

  bulk_field_create_from_script($b_script, $b_callback);
}
