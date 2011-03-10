function group_confirm(){

// ----------------------------------------------------------------
// a few global items
// ----------------------------------------------------------------

	// LFS main group ID is 8
	// this check is hardcoded for LFS
	main_group_id = "8";
		

// ----------------------------------------------------------------
// code to determine checkbox version or select box version
// ----------------------------------------------------------------

	var og_groups_is_selectbox = Boolean(document.getElementById('edit-og-groups'));
	// debug alert
	// alert("og_groups_is_selectbox is " + og_groups_is_selectbox);

	if (!og_groups_is_selectbox){

// ----------------------------------------------------------------
// code for checkbox version
// ----------------------------------------------------------------

		// if this is the main checkbox
		// this is the checkbox that og_groups creates via drupal
		// ID is hardcoded by drupal
		var main_group_checkbox = document.getElementById('edit-og-groups-8');
		if (main_group_checkbox.checked == true){

			// if the user is CHECKING and not UNCHECKING the box
			
			// debug alert
			// alert("edit-og-groups-8");

			// check to see if main group is ALREADY confirmed (hidden checkbox)
			// ID is hardcoded by drupal
			var main_group_confirmed = document.getElementById('edit-main-group-confirmed');
			if (main_group_confirmed.checked == true) {
				// if main group is confirmed then DO NOT pop up the confirm again
				
				// debug alert
				// alert("main group already confirmed");
	
			} else if (main_group_confirmed.checked == false) {
				// if main group is not confirmed yet then ask

				// ask the confirm
				// actual confirmation code
				var confirmation = confirm("Are you sure that you want to send to main group??");
				if (confirmation){
		
					// debug alert
					// alert("yes");
		
					// check checkbox programatically
					main_group_confirmed.checked = true;
				}
				else {
				// uncheck main
					// make sure the confirmation checkbox is NOT checked
					main_group_confirmed.checked = false;
					// make sure the main group checkbox is NOT checked
					main_group_checkbox.checked = false;
				}
			}
		}
	} else {	

// ----------------------------------------------------------------
// code for selectbox version
// ----------------------------------------------------------------

		// this is the select box that og_groups creates via drupal
		// ID is hardcoded by drupal
		var this_selector = document.getElementById('edit-og-groups');
		
		var this_value = this_selector.value;
		if (this_value == main_group_id){
			// debug alert
			// alert("[" + this_value + "]");
	
			// check to see if main group is ALREADY confirmed (hidden checkbox)
			// ID is hardcoded by drupal
			var main_group_confirmed = document.getElementById('edit-main-group-confirmed');
			if (main_group_confirmed.checked == true) {
				// if main group is confirmed then do not pop up the confirm again
				
				// debug alert
				// alert("main group already confirmed");
	
			} else if (main_group_confirmed.checked == false) {
				// if main group is not confirmed yet then ask
				
				// debug alert
				// alert("main group not confirmed");
	
				// actual confirmation code
				var confirmation = confirm("Are you sure that you want to send to main group??");
				if (confirmation){
	
					// debug alert
					// alert("yes");
	
					// check checkbox programatically
					main_group_confirmed.checked = true;
				}
				else{
	
					// debug alert
					// alert("no");
	
					// store all selected options
					var NewOptions = new Array();
					var this_selected = false;
					for(var i=0; i < this_selector.options.length; i++){
						// debug alert
						// alert("doing " + i);
						var current = this_selector.options[i];
						NewOptions[i] = new Option();
						NewOptions[i].text = current.text;
						NewOptions[i].value = current.value;
						NewOptions[i].selected = current.selected;
						if(current.selected == true){
							// debug alerts
							// alert(current.value + " " + current.selected);
							// alert(NewOptions[i].value + " " + NewOptions[i].selected);
							if (current.value == main_group_id){
								NewOptions[i].selected = false;
								// debug alert
								// alert(main_group_id + " " + NewOptions[i].selected);
							}
						}
					}
	
					// reset select box to NO options selected
					this_selector.selectedIndex = -1;
	
					// restore all selected options EXCEPT Main Group
	
					// debug alert
					/*
					var alertText = "options: ";
					for(i=0; i < NewOptions.length; i++){
						alertText += "[" + NewOptions[i].value + "]";
					}
					alert(alertText);
					*/
	
					for(i=0; i < NewOptions.length; i++){
						this_selector.options[i] =  new Option();
						this_selector.options[i] = NewOptions[i];
	
						if (NewOptions[i].selected == true){
							// debug alert
							// alert(NewOptions[i].value);
							this_selector.options[i].selected = true;	
						}
					}
	
					// make sure the checkbox is NOT checked
					main_group_confirmed.checked = false;
				}
			}
		}
	}
}
