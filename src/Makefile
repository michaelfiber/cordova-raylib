.ONESHELL:

# Add any project C files here to have them built as part of the project.
PROJECT_SOURCE_FILES ?= main.c

# This is hardcoded to the path that `install-linux.sh` and `install-windows.bat` 
# place emsdk files to avoid needing to set up the environment to build.
CC=../emsdk/emsdk-main/upstream/emscripten/emcc 

# This is the directory within `src` where the finished files will be placed.
DEST=../www

# Any C functions that you want callable from JS should added to this comma separated list.
EXPORTED_FUNCTIONS=_main,_cordova_battery_set_level,_cordova_battery_set_charging,_cordova_camera_success,_cordova_camera_failure,_cordova_orientation_onchange_mode,_cordova_geolocation_onchange_position,_cordova_inappbrowser_execute_script_callback,_cordova_dialog_confirm_callback

CFLAGS=-I./external -s USE_GLFW=3 --preload-file resources
MAKE=make

OBJ=$(patsubst %.c, %.o, $(PROJECT_SOURCE_FILES)) ./external/libraylib.a

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

game.js: $(OBJ)
	mkdir -p $(DEST)
	$(CC) -o $(DEST)/$@ $^ $(CFLAGS) -sEXPORTED_FUNCTIONS=$(EXPORTED_FUNCTIONS) -sEXPORTED_RUNTIME_METHODS=ccall,cwrap --js-library cordova-library.js

clean:
	rm *.o