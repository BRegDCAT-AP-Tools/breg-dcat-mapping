<?php

/**
 * @file
 * Bulk creator helper file.
 *
 * Helper functions for the Bulk creator module.
 */

/**
 * Convert a text to its corresponding machine name.
 *
 * @param string $text
 *   The string to convert to drupal field machine name.
 *
 * @return string
 *   A drupal field machine name.
 */
function bulk_helper_tomachinename($text) {
    $machine_name = preg_replace('@[^a-z0-9_]+@', '_', strtolower($text));
    // I fields consentono solo 32 caratteri!
    // Viva il risparmio nell'unico punto in cui non serve.
    $machine_name_cut = substr($machine_name, 0, 32);
    return $machine_name_cut;
}

/**
 * This is an example of a personal callback.
 *
 * Each $line is only a bunch of column pasted from a spreadsheet.
 * An integer field with prefix '€' to the content type 'bilancio' is added.
 * The voices are also added to the desired field group 'group_bilancio_b_1'.
 * Machine names will be used to compose the labels where they are not
 * available.
 *
 * @param string $line
 *   The line script.
 */
function bulk_custom_field_add_balance($line) {
    $bundle_name = 'bilancio';
    $group_name = 'group_ii_crediti';
    $field_description = 'Voce di bilancio ' . $line;
    $field_name = bulk_field_create($bundle_name, 'number_integer', $line, '', $field_description, FALSE, '', $group_name, '€');
    // bulk_field_add_to_group($field_name, $bundle_name, $group_name);
}

/**
 * This method adds a field to a field group.
 *
 * If the field group does not exist, it is created.
 *
 * @param string $field_name
 *   The machine name of the field.
 * @param string $bundle_name
 *   The name of the bundle that hosts the field group.
 * @param string $group_name
 *   The machine name of the group.
 * @param string $group_label
 *   The label of the field group. If left empty it will be composed from
 *   the machine name.
 */
function bulk_field_add_to_group($field_name, $bundle_name, $group_name, $group_label = '') {

    $entity_type = 'node';
    $entity_mode = 'form';
    if (empty($group_label)) {
        $group_label = ucwords(str_replace("_", " ", strtolower($group_name)));
    }

    if (!function_exists('field_group_exists')) {
        bulk_log(t('field_group is not installed.'), 'error');
        return;
    }

    if (!field_group_exists($group_name, $entity_type, $bundle_name, $entity_mode)) {
        $group = (object) array(
                    'identifier' => $group_name . '|' . $entity_type . '|' . $bundle_name . '|' . $entity_mode,
                    'group_name' => $group_name,
                    'entity_type' => $entity_type,
                    'bundle' => $bundle_name,
                    'mode' => $entity_mode,
                    'label' => $group_label,
                    'weight' => '1',
                    'children' => array(),
                    'format_type' => 'fieldset',
                    'format_settings' => array(
                        'formatter' => 'collapsible',
                        'instance_settings' => array(
                            'description' => '',
                            'classes' => '',
                            'required_fields' => 1,
                        ),
                    ),
        );
        field_group_group_save($group);
    }

    $groups = field_group_read_groups(array(
        'name' => $entity_type,
        'bundle' => $bundle_name,
        'view_mode' => 'full'));
    $my_group = $groups[$entity_type][$bundle_name][$entity_mode][$group_name];
    $my_group->children[] = $field_name;
    field_group_group_save($my_group);

    bulk_log(t('Field added to the field group !field_group.', array('!field_group' => $group_name)));
}

/**
 * Logs a system message.
 *
 * @param string $message
 *   The Message to log.
 */
function bulk_log($message, $status = 'status') {
    $allowed_html = array();
    $message = filter_xss($message, $allowed_html);
    watchdog('bulk', $message);
    drupal_set_message($message, $status);
}

/**
 * Build a range of character for the jolly parameters in the script.
 *
 * This function is more powerful than the PHP range() which is limited to one
 * character. Provides an "Excel Style" range.
 *
 * @param string $lower
 *   The lower range.
 * @param string $upper
 *   The upper range.
 *
 * @return array
 *   The array of strings between $lower and $upper.
 */
function bulk_helper_column_range($lower, $upper) {
    if ($lower > $upper) {
        $tmp = $lower;
        $lower = $upper;
        $upper = $tmp;
    }
    ++$upper;
    $counter = 0;
    $result = array();
    for ($i = $lower; $i !== $upper; ++$i) {
        $result[] = $i;
        if (++$counter > 100) {
            // Stop at 100 item for safety.
            $message = t('Automatic field name creation has reached its maximum.');
            bulk_log($message, 'warning');
            break;
        }
        // Debug: echo $i . "\n";
    }
    return $result;
}

/**
 * Importa contenuti e menu precedentemente esportati sul sito corrente.
 * Questa funzione dipende da node_export, menu_import. * 
 * 
 * @param string $description_nodes
 *   La descrizione dei nodi, esportata con node_export.
 * @param string $description_menus
 *   La descrizione dei menu, esportata con menu import.
 * @param string $destination_menu
 *   Il nome macchina dei menu sotto il quale importare.
 */
function bulk_helper_import_contents_and_menu($description_nodes, $description_menus, $destination_menu) {
    node_export_import($description_nodes);
    menu_import_string($description_menus, $destination_menu);  // Attenzione gli accapi vanno preservati con " "
}
