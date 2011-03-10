<?php
// $Id: jquery_popupwindow.admin.inc,v 1.1.2.5 2009/10/15 14:44:38 aaron Exp $
/**
 * @file
 * Provides the administration page for jQuery PopupWindow.
 */

/**
 * Administration settings page
 */
function jquery_popupwindow_admin() {
  // Clear the previously cached presets, which will be restored in hook_init.
  cache_clear_all('jquery_popupwindow_presets', 'cache');

  // Add the CSS for this page, which separates the form into two columns.
  drupal_add_css(drupal_get_path('module', 'jquery_popupwindow') .'/jquery_popupwindow.admin.css');

  // Get our current presets.
  $presets = variable_get('jquery_popupwindow_presets', array());

  $form = array(
    'jquery_popupwindow_presets' =>  array(
      '#type' => 'fieldset',
      '#tree' => TRUE,
      '#description' => t('You may add as many link presets as you would like.  To add additional presets, save to add @count more.', array('@count' => variable_get('jquery_popupwindow_additional_form_elements', 3))),
    ),
  );
  $i = 0;

  // Add a form element for each current preset, and add 3 more blank elements.
  while ($i < (count($presets) + variable_get('jquery_popupwindow_additional_form_elements', 3))) {
    $form['jquery_popupwindow_presets'][$i] = array(
      'preset' => array(
        '#type' => 'textarea',
        '#title' => t('jQuery link selector'),
        '#cols' => 40,
        '#rows' => 3,
        '#prefix' => '<div class="jquery-popupwindow-preset">',
        '#suffix' => '</div>',
        '#description' => t('Please enter the jQuery link selectors here, separated by commas. For example, you might have .more-link a, #my-link.'),
      ),
      'options' => array(
        '#tree' => TRUE,
        '#prefix' => '<div class="jquery-popupwindow-options">',
        '#suffix' => '</div>',
      ),
      '#prefix' => '<div class="jquery-popupwindow-settings-row clear-block">',
      '#suffix' => '</div>',
    );
    $form['jquery_popupwindow_presets'][$i]['options']['height'] = array(
      '#type' => 'textfield',
      '#title' => t('Height'),
      '#default_value' => variable_get('jquery_popupwindow_default_height', 600),
      '#description' => t('Sets the height of the popup window in pixels.'),
    );
    $form['jquery_popupwindow_presets'][$i]['options']['width'] = array(
      '#type' => 'textfield',
      '#title' => t('Height'),
      '#default_value' => variable_get('jquery_popupwindow_default_width', 600),
      '#description' => t('Sets the height of the popup window in pixels.'),
    );
    $form['jquery_popupwindow_presets'][$i]['options']['toolbar'] = array(
      '#type' => 'checkbox',
      '#title' => t('Toolbar'),
      '#default_value' => variable_get('jquery_popupwindow_default_toolbar', 0),
      '#description' => t('Determines whether a toolbar (includes the forward and back buttons) is displayed.'),
    );
    $form['jquery_popupwindow_presets'][$i]['options']['scrollbars'] = array(
      '#type' => 'checkbox',
      '#title' => t('Scrollbars'),
      '#default_value' => variable_get('jquery_popupwindow_default_scrollbars', 0),
      '#description' => t('Determines whether scrollbars appear on the window.'),
    );
    $form['jquery_popupwindow_presets'][$i]['options']['status'] = array(
      '#type' => 'checkbox',
      '#title' => t('Status'),
      '#default_value' => variable_get('jquery_popupwindow_default_status', 0),
      '#description' => t('Determines whether the status bar appears at the bottom of the window.'),
    );
    $form['jquery_popupwindow_presets'][$i]['options']['resizable'] = array(
      '#type' => 'checkbox',
      '#title' => t('Resizable'),
      '#default_value' => variable_get('jquery_popupwindow_default_resizable', 1),
      '#description' => t('Determines whether the window can be resized.'),
    );
    $form['jquery_popupwindow_presets'][$i]['options']['left'] = array(
      '#type' => 'textfield',
      '#title' => t('Left position'),
      '#default_value' => variable_get('jquery_popupwindow_default_left', 0),
      '#description' => t('Placement of the left of the popup window (in pixels).'),
    );
    $form['jquery_popupwindow_presets'][$i]['options']['top'] = array(
      '#type' => 'textfield',
      '#title' => t('Top position'),
      '#default_value' => variable_get('jquery_popupwindow_default_top', 0),
      '#description' => t('Placement of the top of the popup window (in pixels).'),
    );
    $form['jquery_popupwindow_presets'][$i]['options']['center'] = array(
      '#type' => 'checkbox',
      '#title' => t('Center popup window'),
      '#default_value' => variable_get('jquery_popupwindow_default_center', 0),
      '#description' => t('Should we center the popup window? (If checked, then the left and top settings above will be ignored.)'),
    );
    $form['jquery_popupwindow_presets'][$i]['options']['createnew'] = array(
      '#type' => 'checkbox',
      '#title' => t('Create new popup window'),
      '#default_value' => variable_get('jquery_popupwindow_default_createnew', 1),
      '#description' => t('If checked, then a new popup window will be created for each instance.'),
    );

    // Set any existing preset defaults.
    if ($s = $presets[$i]) {
      $form['jquery_popupwindow_presets'][$i]['preset']['#default_value'] = $s['preset'];
      $form['jquery_popupwindow_presets'][$i]['options']['height']['#default_value'] = $s['options']['height'];
      $form['jquery_popupwindow_presets'][$i]['options']['width']['#default_value'] = $s['options']['width'];
      $form['jquery_popupwindow_presets'][$i]['options']['toolbar']['#default_value'] = $s['options']['toolbar'];
      $form['jquery_popupwindow_presets'][$i]['options']['scrollbars']['#default_value'] = $s['options']['scrollbars'];
      $form['jquery_popupwindow_presets'][$i]['options']['status']['#default_value'] = $s['options']['status'];
      $form['jquery_popupwindow_presets'][$i]['options']['resizable']['#default_value'] = $s['options']['resizable'];
      $form['jquery_popupwindow_presets'][$i]['options']['left']['#default_value'] = $s['options']['left'];
      $form['jquery_popupwindow_presets'][$i]['options']['top']['#default_value'] = $s['options']['top'];
      $form['jquery_popupwindow_presets'][$i]['options']['center']['#default_value'] = $s['options']['center'];
      $form['jquery_popupwindow_presets'][$i]['options']['createnew']['#default_value'] = $s['options']['createnew'];
    }
    $i++;
  }

  // Remove any blank presets on submit.
  $form['#submit'][] = 'jquery_popupwindow_admin_submit';
  return system_settings_form($form);
}

/**
 * Submit callback for jquery_popupwindow administrative settings
 *
 * Filters out empty form elements.
 */
function jquery_popupwindow_admin_submit($form, &$form_state) {
  foreach ($form_state['values']['jquery_popupwindow_presets'] as $row => $options) {
    if (empty($options['preset'])) {
      unset($form_state['values']['jquery_popupwindow_presets'][$row]);
    }
  }
}
