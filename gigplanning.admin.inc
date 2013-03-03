<?php
//$Id$

/**
 * @file
 * Administration page for Gigplanning
 */

function gigplanning_admin_settings() {
  $sql = "SELECT fid, name FROM {profile_field}";
  $result = db_query($sql);
  // TODO simplify: $field array contains profile fields
  $fields = array();
  while ($row = $result->fetchAssoc()) {
    $fields[$row['fid']] = $row['name'];
  }
  $gp_roles = user_roles();
  //debug - drupal_set_message(print_r($fields));

  $form['gigplanning_email_from_name'] = array (
    '#type' => 'textfield',
  '#maxlength' => 32,
  '#size' => 24,
  '#title' => 'From-name used in emails',
  '#description' => 'This name will be used in emails send by Gigplanning',
  '#default_value' => variable_get('gigplanning_email_from_name', ''),
  );
  $form['gigplanning_podium_indeling'] = array (
    '#type' => 'radios',
  '#title' => 'Podium indeling',
  '#description' => 'If you select this option, you can select which player(s) within a section is selected for the gig. (In case more than one available for one section-position)',
  '#options' => array('0' => 'No', '1' => 'Yes'),
  '#default_value' => variable_get('gigplanning_podium_indeling', 0),
  );

    $form['gigplanning_maybe_option'] = array (
    '#type' => 'radios',
  '#title' => 'Maybe Option',
  '#description' => 'If you select this option, players can select the option - Maybe - on the gig form',
  '#options' => array('0' => 'No', '1' => 'Yes'),
  '#default_value' => variable_get('gigplanning_maybe_option', 1),
  );
  $form['gigplanning_role_bandmembers'] = array (
    '#type' => 'select',
  '#maxlength' => 32,
  '#title' => 'User Role for permanent band members',
  '#description' => 'Set this field to the Role defining the permanent bandmembers',
  '#options' => $gp_roles,
  '#default_value' => variable_get('gigplanning_role_bandmembers', ''),
  );

  $form['gigplanning_section'] = array (
    '#type' => 'select',
  '#maxlength' => 32,
  '#title' => 'Profile field containing band sections',
  '#description' => 'Set this field to the profile field defining the band sections',
  '#options' => $fields,
  '#default_value' => variable_get('gigplanning_section', 'profile-sectie'),
  );

  return system_settings_form($form);
}

function gigplanning_flex_settings() {
  $sections = gp_get_all_sections();
  //debug - drupal_set_message(print_r($sections));
  $form['gigplanning_flex_sections'] = array (
    '#type' => 'checkboxes',
  '#title' => 'Sections not always required for gigs',
  '#description' => 'Sections marked here are flexible. They are not required for all gigs. You you determine per gig if they should be included or not.',
  '#options' => $sections,
  '#default_value' => variable_get('gigplanning_flex_sections', array()),
  );
  return system_settings_form($form);
}

function gigplanning_section_size_settings() {
  $sections_full = gp_get_all_sections_full();
  if (!empty($sections_full)) {
    foreach ($sections_full as $row) {
      $form['gigplanning_section_size_' . $row['id']] = array(
      '#prefix' => "<div class = 'gp-section-size'>",
      '#suffix' => '</div>',
      '#type' => 'textfield',
      '#title' => $row['value'],
      '#length' => 2,
      '#size' => 2,
      '#default_value' => variable_get('gigplanning_section_size_' . $row['id'], 0),
      '#description' => '0 = unlimited',
      );
     }

  return system_settings_form($form);
  }
  else {
  drupal_set_message ('no data loaded');
  }

}
