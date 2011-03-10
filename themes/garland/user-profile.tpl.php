<?php
// $Id: user-profile.tpl.php,v 1.2.2.1 2008/10/15 13:52:04 dries Exp $

/**
 * @file user-profile.tpl.php
 * Default theme implementation to present all user profile data.
 *
 * This template is used when viewing a registered member's profile page,
 * e.g., example.com/user/123. 123 being the users ID.
 *
 * By default, all user profile data is printed out with the $user_profile
 * variable. If there is a need to break it up you can use $profile instead.
 * It is keyed to the name of each category or other data attached to the
 * account. If it is a category it will contain all the profile items. By
 * default $profile['summary'] is provided which contains data on the user's
 * history. Other data can be included by modules. $profile['user_picture'] is
 * available by default showing the account picture.
 *
 * Also keep in mind that profile items and their categories can be defined by
 * site administrators. They are also available within $profile. For example,
 * if a site is configured with a category of "contact" with
 * fields for of addresses, phone numbers and other related info, then doing a
 * straight print of $profile['contact'] will output everything in the
 * category. This is useful for altering source order and adding custom
 * markup for the group.
 *
 * To check for all available data within $profile, use the code below.
 *
 * @code
 *   print '<pre>'. check_plain(print_r($profile, 1)) .'</pre>';
 * @endcode
 *
 * @see user-profile-category.tpl.php
 *   Where the html is handled for the group.
 * @see user-profile-field.tpl.php
 *   Where the html is handled for each item in the group.
 *
 * Available variables:
 *   - $user_profile: All user profile data. Ready for print.
 *   - $profile: Keyed array of profile categories and their items or other data
 *     provided by modules.
 *
 * @see template_preprocess_user_profile()
 */
?>
<div class="profile">
<?php print theme('user_picture', $account); ?>
<?php if($account->profile_firstname): ?>
<h3>First Name:</h3>
<?php echo $account->profile_firstname; ?>
<?php endif ?>
<br />
<br />
<?php if($account->profile_lastname): ?>
<h3>Last Name:</h3>
<?php echo $account->profile_lastname; ?>
<?php endif ?>
<br />
<br />
<?php if($account->profile_organization): ?>
<h3>Company or Organization:</h3>
<?php echo $account->profile_organization; ?>
<?php endif ?>
<br />
<br />
<?php if($account->profile_position): ?>
<h3>Position:</h3>
<?php echo $account->profile_position; ?>
<?php endif ?>
<br />
<br />
<?php if($account->profile_url): ?>
<h3>Website Address:</h3>
<a href="<?php echo $account->profile_url; ?>"><?php echo $account->profile_url; ?></a>
<?php endif ?>
<br />
<br />
<?php if($account->profile_about): ?>
<h3>About Me:</h3>
<?php echo $account->profile_about; ?>
<?php endif ?>
<br />
<br />
<?php if($user->uid == arg(1) && arg(0) == 'user'): ?> 
<h1>My Groups</h1>
<?php print(views_embed_view('og_my', 'page_1')); ?>
<?php endif ?>
<br />
<br />
<br />
<h1>My Posts</h1>
<br />
<h1><a href="/blog/<? print $account->uid; ?>">View my recent posts</a></h1>

