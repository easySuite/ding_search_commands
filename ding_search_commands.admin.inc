<?php
/**
 * @file
 * Ding search commands module settings.
 */

/**
 * Implements hook_block_view().
 */
function ding_search_commands_block_view($delta = '') {
  $form = drupal_get_form('ding_search_commands_settings_form');

  $output = '';
  $output .= drupal_render($form);
  $output .= ding_search_commands_terms_table();

  $block = array(
    'content' => array(
      '#markup' => $output,
    ),
  );

  return $block;
}

function ding_search_commands_settings_form($form, &$form_state, $no_js_use = FALSE) {
  $form['terms_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Manage terms'),
  );

  $form['terms_fieldset']['term'] = array(
    '#type' => 'textfield',
    '#title' => t('Term name'),
    '#required' => TRUE,
  );

  $form['terms_fieldset']['description'] = array(
    '#type' => 'textfield',
    '#title' => t('Term description'),
    '#required' => TRUE,
  );

  $form['terms_fieldset']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

function ding_search_commands_settings_form_submit($form, &$form_state) {
  db_insert('search_commands')
    ->fields(array(
      'term' => $form_state['values']['term'],
      'description' => $form_state['values']['description'],
    ))
    ->execute();

  drupal_set_message(t('Term was saved to the database.'));
}

function ding_search_commands_terms_table() {
  $header = array('Term', 'Description', 'Actions');
  $rows = array();

  // Fill table rows with info.
  $query = db_select('search_commands', 's')
    ->fields('s')
    ->execute();

  foreach ($query as $result) {
    $rows[] = array(
      $result->term,
      $result->description,
      l(t('Delete'), 'search_commands/delete/' . $result->id),
    );
  }

  return theme('table', array('header' => $header, 'rows' => $rows));
}

function ding_search_commands_delete_confirm($form, &$form_state, $term_id) {
  $form['term'] = array(
    '#type' => 'value',
    '#value' => $term_id,
  );

  return confirm_form($form, t('Are you sure you want to delete term?'), 'admin/config/ding/search_commands');
}

function ding_search_commands_delete_confirm_submit($form, &$form_state) {
  $term_id = $form_state['values']['term'];
  if (!empty($term_id)) {
    db_delete('search_commands')
      ->condition('id', $term_id)
      ->execute();

    drupal_set_message(t('Term was deleted successfuly.'), 'status');
    drupal_goto('admin/config/ding/search_commands');
  }
}
