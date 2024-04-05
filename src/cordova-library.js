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
	}
});