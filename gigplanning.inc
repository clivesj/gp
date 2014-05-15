<?php
/**
 * @file helper functions for Gigplanning module
 */

function gp_get_players_role_id() {
  return variable_get('gigplanning_role_bandmembers', '9999');
}

/**
 * Returns an array of sections that are not required for gigs
 * They can be added per Gig
 * sample output:
 * array (
 *   'by_section_titles' => array (
 *     0 => 'Barisax',
 *     1 => 'Euphonium',
 *    ),
 *   'by_players' => array (
 *      0 => array (
 *         'uid' => '83',
 *         'name' => 'thefra',
 *    ),
 *      1 => array ('uid' => '84','name' => 'culipupro',
 *    ),
 * 'ids' => array (
 *   0 => '83',
 *   1 => '84',
 */

function gp_get_flex_sections() {
  $sql = "SELECT pv.uid, u.`name` FROM {profile_value} pv
            LEFT JOIN users u ON (pv.uid = u.uid) WHERE `value` = :section_name";
  $flex_sections = array();
  $sections = variable_get('gigplanning_flex_sections', NULL);
  foreach ($sections as $section) {
    if ($section) {
      $flex_sections['by_section_titles'][] = $section;
      $result = db_query($sql, array(':section_name' => $section));
      foreach ($result as $row) {
        $flex_sections['by_players'][] = (array)$row;
        $flex_sections['ids'][] = $row->uid;
      }
    }
  }
 return $flex_sections;
}

/**
 * @return array Array of players. Array key = uid
 */

/*Sample output:
  array (
    9 =>
      array (
        'uid' => '9',
        'name' => 'brubro',
      ),
    10 =>
      array (
        'uid' => '10',
        'name' => 'jevama',
    ),
  );
*/
function gp_get_players_rehearsal() {
  $players = array();
  $sql = "SELECT u.uid, u.`name`, u.`mail` FROM users u
          LEFT JOIN users_roles ur
            ON (u.uid = ur.uid)
               WHERE (rid = :rid) AND (u.`status` = :user_status)";

  $result = db_query($sql, array(':rid' => gp_get_players_role_id(), ':user_status' => 1,));
  foreach ($result as $row) {
    $players[$row->uid] = (array)($row);
  }
  // unset the non-required users
  $flex = gp_get_flex_sections();
  foreach ($flex['ids'] as $id) {
    unset($players[$id]);
  }
  return $players;
}
