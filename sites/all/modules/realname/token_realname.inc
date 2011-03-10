<?php
// $Id: token_realname.inc,v 1.1.2.9 2009/03/06 20:07:19 nancyw Exp $ */
/**
* @file
*   Token module support for the realname module.
*/

function realname_token_list($type = 'all') {
  $tokens = array();
  switch ($type) {
    case 'user':
    case 'node':
    case 'all':
    case 'global':
    case 'comment':
      $tokens[$type]['realname'] = t('The RealName for the user.');
      $tokens[$type]['realname-link'] = t('Themed username link.');
      $tokens[$type]['homepage'] = t('The home page for the user.');
      $tokens[$type]['realname-comment-author'] = t('The Realname of comment author.');
      return $tokens;
  }
}

function realname_token_values($type, $object = NULL, $options = array()) {
  global $user;
  $tokens = array();
  if (!$object) {
    $object = $user;
  }
  switch ($type) {
    case 'user':
    case 'node':
//    case 'all':
    case 'global':
    case 'comment':
      //If there's a cid, then create a token with the realname of
      //author of the comment
      if(!empty($object->cid)) {
       $comment_user = user_load(array('uid' => $object->uid));
       $tokens['realname-comment-author'] = $comment_user->realname;
      }

      if (!isset($object->uid)) {
        return;
      }
      $tokens['realname'] = realname_make_name($object);
      $tokens['realname-link'] = theme('username', $object);
      $tokens['homepage'] = isset($object->homepage) ? $object->homepage : NULL;
      return $tokens;
      
  }
}
