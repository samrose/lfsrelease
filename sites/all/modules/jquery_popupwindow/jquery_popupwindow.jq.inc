<?php
// $Id: jquery_popupwindow.jq.inc,v 1.1.2.1 2009/10/14 19:50:47 aaron Exp $

/**
 * @file
 * The jQ include file for jQuery Media.
 *
 * This file is loaded when called by jQ.
 */

/**
 *  Implement hook_jq (hook supplied by the jQ module)
 *
 *  The preferred method to invoke this plugin is to use the jQ module, available at http://drupal.org/project/jq
 *  and then call jq_add('jquery_media'); on the pages requiring this.
 *
 *  If you don't wish the jQ module installed, then use jquery_media_add() instead.
 *
 *  This gives the info for the plugin, plus adds any required settings on invocation.
 *  Also adds the required settings form items.
 */
function jquery_popupwindow_jq($op, $plugin = NULL) {
  switch ($op) {
    case 'info':
      return array(
          'jquery_popupwindow' => array(
              'name' => t('jQuery PopupWindow'),
              'description' => t('By rip747. Takes a link and will create a popupwindow based on the href of the link. You can override the default setting by passing your own settings or profile name in the REL attribute of the link.'),
                'version' => '2.0 (02/20/2008)',
                'url' => 'http://rip747.wordpress.com/2008/01/22/popupwindow-v200-now-available/',
              'files' => array(
                  'js' => array(
                      drupal_get_path('module', 'jquery_popupwindow') .'/js/jquery.popupwindow.js',
                  ),
              ),
          ),
      );
    break;
  }
}
