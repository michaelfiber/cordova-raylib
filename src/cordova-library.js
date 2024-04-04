function cameraSuccess(path) {
	alert('camera success');
	let pathPtr = stringToNewUTF8(path);
	_cordova_camera_success(pathPtr);
	_free(pathPtr);
}

function cameraFailure(errorMessage) {
	alert(errorMessage);
	_cordova_camera_failure();
}

// Merge JS functions into the Library for the WASM Build.  
// Functions provided here are available within the C code.
mergeInto(LibraryManager.library, {
	cordova_camera_get_picture: function () {
		alert('take picture');

		if ('camera' in navigator) {
			alert('found camera' + navigator.camera.getPicture);
			navigator.camera.getPicture(cameraSuccess, cameraFailure)
		}
	},
});