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
      'base' => 'gp_rehearsal_rules_action_mail',
      //'access callback' => 'rules_system_integration_access',
    ),
  );
  return $actions;
}

function gp_rehearsal_rules_action_mail($to, $subject, $message, $from = NULL, $langcode) {
  debug($to,'to');
  debug($subject, 'subject');
  debug($message, 'message');
  debug($from,'From');
  


  require_once('gigplanning.inc');

 // $from = !empty($from) ? str_replace(array("\r", "\n"), '', $from) : NULL;
  $form = 'info@gigplanning.com';

  // Now, actually send the mails.
  $params = array(
    'subject' => $subject,
    'message' => $message,
    'langcode' => $langcode,
  );

  $players = gp_get_players_rehearsal();

  // Set a unique key for this mail.
  $key = 'gp_action_send_mail_rehearsal';
  $languages = language_list();

  $message = array('result' => TRUE);

  foreach ($players as $player) {
    $message = drupal_mail('gigplanning', $key, $player['mail'], language_default(), $params, $from);
    if ($message['result']) {
      watchdog('gigplanning', 'Sent notification email to %player_name.', array('%player_name' => $player['name']));
    }
  }
}
