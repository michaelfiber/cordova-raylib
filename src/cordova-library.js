// Merge JS functions into the Library for the WASM Build.  
// Functions provided here are available within the C code.
mergeInto(LibraryManager.library, {

	// camera plugin support
	cordova_camera_get_picture: function () {
		function cameraSuccess(path) {
			let pathPtr = stringToNewUTF8(path);
			_cordova_camera_success(pathPtr);
			_free(pathPtr);
		}

		function cameraFailure(errorMessage) {
			_cordova_camera_failure();
		}

		let Camera = window.Camera,
			options = {
				quality: 75,
				destinationType: Camera.DestinationType.FILE_URI,
				sourceType: Camera.PictureSourceType.CAMERA,
				allowEdit: false,
				encodingType: Camera.EncodingType.JPEG,
				targetWidth: 1024,
				targetHeight: 1024,
				correctOrientation: true
			};
		if ('camera' in navigator) {
			try {
				navigator.camera.getPicture(cameraSuccess, cameraFailure, options)
			} catch (ex) {
				alert(ex);
			}
		}
	},

	// orientation plugin support
	cordova_orientation_lock: async function (modePtr) {
		let mode = UTF8ToString(modePtr);
		try {
			let result = await window.screen.orientation.lock(mode);
		} catch (ex) {
			alert(ex);
		}
	},
	cordova_orientation_unlock: function () {
		window.screen.orientation.unlock();
	},
	cordova_orientation_current_mode: function () {
		return stringToNewUTF8(window.screen.orientation.type);
	},

	// geolocation plugin support
	cordova_geolocation_watch_start: function () {
		window.cordova_geolocation_watch_id = navigator.geolocation.watchPosition((position) => {
			_cordova_geolocation_onchange_position(position.coords.latitude, position.coords.longitude, position.coords.accuracy.toFixed(0));
		},
			(error) => {
				alert('code: ' + error.code + '\n' +
					'message: ' + error.message + '\n');
			},
			{ enableHighAccuracy: true })
	},
	cordova_geolocation_watch_stop: function () {
		navigator.geolocation.clearWatch(window.cordova_geolocation_watch_id);
	},

	// statusbar plugin support
	cordova_statusbar_overlays_webview: function(val) {
		StatusBar.overlaysWebView(val);
	},
	cordova_statusbar_style_default: function() {
		StatusBar.styleDefault();
	},
	cordova_statusbar_style_light: function() {
		StatusBar.styleLightContent();
	},
	cordova_statusbar_background_by_color_name: function (colorNamePtr) {
		let colorName = UTF8ToString(colorNamePtr);
		StatusBar.backgroundColorByName(colorName)
	},
	cordova_statusbar_background_by_hex_string: function (hexStringPtr) {
		let hexString = UTF8ToString(hexStringPtr);
		StatusBar.backgroundColorByHexString(hexString);
	},
	cordova_statusbar_hide: function() {
		StatusBar.hide();
	},
	cordova_statusbar_show: function() {
		StatusBar.show();
	},
	cordova_statusbar_is_visible: function() {
		return StatusBar.isVisible;
	},

	// inappbrowser plugin support
	cordova_inappbrowser_open: function(urlPtr, target) {
		let targetString = ["_blank", "_self", "_system"][target];
		let url = UTF8ToString(urlPtr);

		if (window.cordova_inappbrowser_ref) {
			window.cordova_inappbrowser_ref.close();
			delete window.cordova_inappbrowser_ref
		}

		window.cordova_inappbrowser_ref = cordova.InAppBrowser.open(url, targetString, window.cordova_inappbrowser_options ? window.cordova_inappbrowser_options.map(o => o.key + "=" + o.value).join(",") : "");
	},
	cordova_inappbrowser_set_option: function(keyPtr, valuePtr) {
		let key = UTF8ToString(keyPtr);
		let value = UTF8ToString(valuePtr);
		if (!Array.isArray(window.cordova_inappbrowser_options)) window.cordova_inappbrowser_options = [];
		
		for (let i = 0; i < window.cordova_inappbrowser_options.length; i++) {
			if (window.cordova_inappbrowser_options[i].key == key) {
				window.cordova_inappbrowser_options[i].value = value;
				return;
			}
		}

		window.cordova_inappbrowser_options.push({
			key,
			value
		});
	},
	cordova_inappbrowser_close: function() {
		if (!window.cordova_inappbrowser_ref) return;

		window.cordova_inappbrowser_ref.close();
		delete window.cordova_inappbrowser_ref
	},
	cordova_inappbrowser_show: function() {
		if (!window.cordova_inappbrowser_ref) return;

		window.cordova_inappbrowser_ref.show();
	},
	cordova_inappbrowser_execute_script: function(injectType, injectValuePtr) {
		if (!window.cordova_inappbrowser_ref) return;

		let details = {};
		let injectValue = UTF8ToString(injectValuePtr);

		switch (injectType) {
			case 0:
				details.file = injectValue;
				break;
			case 1:
				details.code = injectValue;
				break;
		}

		function cb(something) {
			let values = [];

			if (Array.isArray(something)) {
				values = something.map(s => stringToNewUTF8(s));
			} else {
				values = [stringToNewUTF8(something)];
			}

			_cordova_inappbrowser_execute_script_callback(values.length, values);

			values.forEach(s => _free(s));
		}

		window.cordova_inappbrowser_ref.executeScript(details, cb);
	},
	cordova_inappbrowser_insert_css: function(injectType, injectValuePtr) {
		if (!window.cordova_inappbrowser_ref) return;

		let details = {};
		let injectValue = UTF8ToString(injectValuePtr);

		switch (injectType) {
			case 0:
				details.file = injectValue;
				break;
			case 1:
				details.code = injectValue;
				break;
		}

		window.cordova_inappbrowser_ref.insertCSS(detials, ()=>{});
	},

	// vibration plugin
	cordova_vibration_start: function(count, durationArrayPtr) {
		let sequence = [];
		for (let current = durationArrayPtr; current < durationArrayPtr + count * 4; current += 4) {
			sequence.push(HEAP32[current >> 2]);
		}

		if ('vibrate' in navigator) {
			navigator.vibrate(sequence);
		}
	},

	// dialog plugin
	cordova_dialog_confirm: function (messagePtr, titlePtr, button1Ptr, button2Ptr, button3Ptr) {
		let message = UTF8ToString(messagePtr);
		let title = UTF8ToString(titlePtr);
		
		let buttons = [];

		if (button1Ptr != null) {
			buttons.push(UTF8ToString(button1Ptr))
		}

		if (button2Ptr != null) {
			buttons.push(UTF8ToString(button2Ptr))
		}

		if (button3Ptr != null) {
			buttons.push(UTF8ToString(button3Ptr))
		}
		navigator.notification.confirm(message, _cordova_dialog_confirm_callback, title, buttons);
	}
});