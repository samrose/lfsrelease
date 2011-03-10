<?php
// $Id: message.pages.inc,v 1.6.2.1 2008/02/08 21:15:12 goba Exp $

/**
 * @file
 * Page callback file for the message module.
 */

/**
 * Menu callback; displays a Drupal page containing recent message entries of a given user.
 */
function message_page_user($account) {
  global $user;

  drupal_set_title($title = t("@name's messages", array('@name' => $account->name)));

  $items = array();

  if (($account->uid == $user->uid) && user_access('create message entries')) {
    $items[] = l(t('Post new message entry.'), "node/add/message");
  }
  else if ($account->uid == $user->uid) {
    $items[] = t('You are not allowed to post a new message entry.');
  }

  $output = theme('item_list', $items);

  $result = pager_query(db_rewrite_sql("SELECT n.nid, n.sticky, n.created FROM {node} n WHERE n.type = 'message' AND n.uid = %d AND n.status = 1 ORDER BY n.sticky DESC, n.created DESC"), variable_get('default_nodes_main', 10), 0, NULL, $account->uid);
  $has_posts = FALSE;
  
  while ($node = db_fetch_object($result)) {
    $output .= node_view(node_load($node->nid), 1);
    $has_posts = TRUE;
  }
  
  if ($has_posts) {
    $output .= theme('pager', NULL, variable_get('default_nodes_main', 10));
  }
  else {
    if ($account->uid == $user->uid) {
      drupal_set_message(t('You have not created any message entries.'));
    }
    else {
      drupal_set_message(t('!author has not created any message entries.', array('!author' => theme('username', $account))));
    }
  }
  drupal_add_feed(url('message/'. $account->uid .'/feed'), t('RSS - !title', array('!title' => $title)));

  return $output;
}

/**
 * Menu callback; displays a Drupal page containing recent message entries of all users.
 */
function message_page_last() {
  global $user;

  $output = '';
  $items = array();

  if (user_access('edit own message')) {
    $items[] = l(t('Create new message entry.'), "node/add/message");
  }

  $output = theme('item_list', $items);

  $result = pager_query(db_rewrite_sql("SELECT n.nid, n.created FROM {node} n WHERE n.type = 'message' AND n.status = 1 ORDER BY n.sticky DESC, n.created DESC"), variable_get('default_nodes_main', 10));
  $has_posts = FALSE;

  while ($node = db_fetch_object($result)) {
    $output .= node_view(node_load($node->nid), 1);
    $has_posts = TRUE;
  }
  
  if ($has_posts) {
    $output .= theme('pager', NULL, variable_get('default_nodes_main', 10));
  }
  else {
    drupal_set_message(t('No message entries have been created.'));
  }
  drupal_add_feed(url('message/feed'), t('RSS - messages'));

  return $output;
}

/**
 * Menu callback; displays an RSS feed containing recent message entries of a given user.
 */
function message_feed_user($account) {
  $result = db_query_range(db_rewrite_sql("SELECT n.nid, n.created FROM {node} n  WHERE n.type = 'message' AND n.uid = %d AND n.status = 1 ORDER BY n.created DESC"), $account->uid, 0, variable_get('feed_default_items', 10));
  $channel['title'] = $account->name ."'s message";
  $channel['link'] = url('message/'. $account->uid, array('absolute' => TRUE));

  $items = array();
  while ($row = db_fetch_object($result)) {
    $items[] = $row->nid;
  }
  node_feed($items, $channel);
}

/**
 * Menu callback; displays an RSS feed containing recent message entries of all users.
 */
function message_feed_last() {
  $result = db_query_range(db_rewrite_sql("SELECT n.nid, n.created FROM {node} n WHERE n.type = 'message' AND n.status = 1 ORDER BY n.created DESC"), 0, variable_get('feed_default_items', 10));
  $channel['title'] = variable_get('site_name', 'Drupal') .' messages';
  $channel['link'] = url('message', array('absolute' => TRUE));

  $items = array();
  while ($row = db_fetch_object($result)) {
    $items[] = $row->nid;
  }

  node_feed($items, $channel);
}
