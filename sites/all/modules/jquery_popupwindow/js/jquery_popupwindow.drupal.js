// $Id: jquery_popupwindow.drupal.js,v 1.1.2.3 2009/10/15 14:44:38 aaron Exp $

/**
 * Set specified links to popup with the preset settings.
 */
Drupal.behaviors.jqueryPopupWindow = function (context) {
  // Loop through each preset selector.
  for (preset in Drupal.settings.jqueryPopupwindowPresets) {
    // Only process a preset selector if we haven't already.
    $(Drupal.settings.jqueryPopupwindowPresets[preset]['preset'], context).addClass('jqueryPopupwindowProcessed').each(function() {
      // Create an array suitable for the popupwindow function.
      popup_options = Drupal.settings.jqueryPopupwindowPresets[preset]['options'];
      settings = new Array();
      settings[preset] = popup_options;

      // Create the popup window behavior.
      $(this).attr('rel', preset).popupwindow(settings);
    })
  }
}
