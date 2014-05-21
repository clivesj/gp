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
      'parameter' => _mail_parameters(),
      'base' => 'gp_rehearsal_rules_action_mail',
      //'access callback' => 'rules_system_integration_access',
    ),

    'gigplanning_action_mail_gigplayers' => array(
      'label' => t('Send mail to players of a Gig'), // Name displayed to admins
      'group' => t('Gigplanning'), // Used for grouping actions in select lists
      'parameter' => _mail_parameters() + _node_parameter(),
      'base' => 'mail_to_gig_players',
    )
  );
  return $actions;
}

function gp_rehearsal_rules_action_mail($subject, $message, $from = NULL) {
  //debug($to,'to');
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
   // 'langcode' => $langcode,
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

function mail_to_gig_players($subject, $message, $from, $node) {
  require_once('gigplanning.inc');
  /*debug($subject, 'subject');
  debug($message, 'message');
  debug($from,'From');
  debug($node-> nid, 'This node is passed to mail_to_gig_players')*/;

  $players = gp_get_players_gig($node-> nid, true);

  // Now, actually send the mails.
  $params = array(
    'subject' => $subject,
    'mail_body' => $message,
    //'langcode' => $langcode,
    );

  //key for hook_mail.
  $key = 'gp_notify_gig';

  $message = array('result' => TRUE);

  foreach ($players as $player) {
    $params['to_name'] = $player['name'];
    $result = drupal_mail('gigplanning', $key, $player['mail'], language_default(), $params, $from);
    if ($result['result']) {
      //watchdog('gigplanning', 'Sent notification email to %player_name.', array('%player_name' => $player['name']));
    }
  }
}

function _mail_parameters() {
  return array(
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
  );
}


function _node_parameter() {
  return
    array(
      'node' => array('type' => 'node', 'label' => t('Content'), 'save' => TRUE),
    );
}
