// Merge JS functions into the Library for the WASM Build.  
// Functions provided here are available within the C code.
mergeInto(LibraryManager.library, {
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
});