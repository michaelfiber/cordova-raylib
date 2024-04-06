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
	}
});