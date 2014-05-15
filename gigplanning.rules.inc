<?php

/**
 * @file
 * Gigplanning Rules: actions, conditions and events.
 */

/**
 * Implements hook_rules_action_info().
 *
 * Declares any meta-data about actions for Rules in a big, associative, nested
 * array. See also hook_rules_action_info in the rules.api.php file, and the
 * online documentation at http://drupal.org/node/878928.
 */
function gigplanning_rules_action_info() {
  $actions = array(
    // The base-level keys in the array are the machine names for the actions,
    // and by default also the function name for the action callback. Prefix
    // with your module name to avoid name conflicts.
    'gigplanning_action_send_mail_rehearsal' => array(
      'label' => t('Send mail to GP rehearsal players'), // Name displayed to admins
      'group' => t('Gigplanning'), // Used for grouping actions in select lists
      'parameter' => array(
        /*'roles' => array(
          'type' => 'list<integer>',
          'options list' => 'entity_metadata_user_roles',
          'description' => t('Select the roles whose users should receive the mail.'),*/
        'subject' => array(
          'type' => 'text',
          'label' => t('Subject'),
          'description' => t("The mail's subject."),
        ),
        'message' => array(
          'type' => 'text',
          'label' => t('Message'),
          'description' => t("The mail's message body."),
        ),
        'from' => array(
          'type' => 'text',
          'label' => t('From'),
          'description' => t("The mail's from address. Leave it empty to use the site-wide configured address."),
          'optional' => TRUE,
        ),
      ),
      'base' => 'gp_action_send_mail_rehearsal',
      //'access callback' => 'rules_system_integration_access',
    ),
  );
  return $actions;
}

function gp_action_send_mail_rehearsal($to, $subject, $message, $from = NULL,
                                               $langcode, $settings, RulesState $state, RulesPlugin $element) {
  require_once('gigplanning.inc');

  $from = !empty($from) ? str_replace(array("\r", "\n"), '', $from) : NULL;

  // All authenticated users, which is everybody.
  if (in_array(DRUPAL_AUTHENTICATED_RID, $roles)) {
    $result = db_query('SELECT mail FROM {users} WHERE uid > 0');
  }
  else {
    $rids = implode(',', $roles);
    // Avoid sending emails to members of two or more target role groups.
    $result = db_query('SELECT DISTINCT u.mail FROM {users} u INNER JOIN {users_roles} r ON u.uid = r.uid WHERE r.rid IN (' . $rids . ')');
  }

  // Now, actually send the mails.
  $params = array(
    'subject' => $subject,
    'message' => $message,
  );

  // Set a unique key for this mail.
  $name = isset($element->root()->name) ? $element->root()->name : 'unnamed';
  $key = 'rules_action_mail_to_users_of_role_' . $name . '_' . $element->elementId();
  $languages = language_list();


  $message = array('result' => TRUE);

  $players = gp_get_players_rehearsal();
  foreach ($players as $player) {
    $message = drupal_mail('rules', $key, $player['mail'], language_default(), $params, $from);
    if ($message['result']) {
      watchdog('gigplaning', 'Sent notification email to %player_name.', array('%player_name' => $player['name']));
    }
  }
}
