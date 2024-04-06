#ifndef CORDOVA_H
#define CORDOVA_H

#include <stdbool.h>
#include <stdio.h>

// ==========================================================================================
// BATTERY PLUGIN

// The battery level as an int between 0 and 100 inclusive.
int cordova_battery_level = 0;

// Whether or not the device is plugged in.
bool cordova_battery_charging = false;

void cordova_battery_set_level(int level)
{
    cordova_battery_level = level;
}

void cordova_battery_set_charging(int plugged_in)
{
    cordova_battery_charging = plugged_in > 0;
}

// BATTERY PLUGIN
// ==========================================================================================

// ==========================================================================================
// CAMERA PLUGIN

char cordova_camera_path[1024] = {0};

bool cordova_camera_image_path_ready()
{
    return cordova_camera_path[0] != '\0';
}

void cordova_camera_success(char *image_path)
{
    sprintf(cordova_camera_path, "%s", image_path);
}

void cordova_camera_failure()
{
    cordova_camera_path[0] = '\0';
}

// Defined in cordova-library.js
void cordova_camera_get_picture();

// CAMERA PLUGIN
// ==========================================================================================

// ==========================================================================================
// ORIENTATION PLUGIN

// Defined in cordova-library.js
void cordova_orientation_lock(char *mode);

// Defined in cordova-library.js
void cordova_orientation_unlock();

// Defined in cordova-library.js. The char * returned should be freed when no longer needed.
char *cordova_orientation_current_mode();

char cordova_orientation_mode[1024] = {0};

char *cordova_orientation_modes[] = {
    "portrait-primary",
    "portrait-secondary",
    "landscape-primary",
    "landscape-secondary",
    "portrait",
    "landscape",
    "any"
};

#define CORDOVA_ORIENTATION_PORTRAIT_PRIMARY 0
#define CORDOVA_ORIENTATION_PORTRAIT_SECONDARY 1
#define CORDOVA_ORIENTATION_LANDSCAPE_PRIMARY 2
#define CORDOVA_ORIENTATION_LANDSCAPE_SECONDARY 3
#define CORDOVA_ORIENTATION_PORTRAIT 4
#define CORDOVA_ORIENTATION_LANDSCAPE 5
#define CORDOVA_ORIENTATION_ANY 6

void cordova_orientation_lock_int(int mode)
{
    if (mode <= CORDOVA_ORIENTATION_ANY)
    {
        cordova_orientation_lock(cordova_orientation_modes[mode]);
    }
}

void cordova_orientation_onchange_mode(char *mode)
{
    sprintf(cordova_orientation_mode, "%s", mode);
}

// ORIENTATION PLUGIN
// ==========================================================================================


// ==========================================================================================
// ORIENTATION PLUGIN

float cordova_geolocation_latitude = 0.0f;
float cordova_geolocation_longitude = 0.0f;
int cordova_geolocation_accuracy = 9999;

void cordova_geolocation_onchange_position(float lat, float lng, int accuracy)
{
    cordova_geolocation_latitude = lat;
    cordova_geolocation_longitude = lng;
    cordova_geolocation_accuracy = accuracy;
}

// defined in cordova-library.js
void cordova_geolocation_watch_start();

// defined in cordova-library.js
void cordova_geolocation_watch_stop();

// ORIENTATION PLUGIN
// ==========================================================================================


// ==========================================================================================
// STATUSBAR PLUGIN

// defined in cordova-library.js
void cordova_statusbar_overlays_webview(bool val);
void cordova_statusbar_style_default();
void cordova_statusbar_style_light();
void cordova_statusbar_background_by_color_name(char *colorNamePtr);
void cordova_statusbar_background_by_hex_string(char *hexStringPtr);
void cordova_statusbar_hide();
void cordova_statusbar_show();
bool cordova_statusbar_is_visible();

// STATUSBAR PLUGIN
// ==========================================================================================


// ==========================================================================================
// INAPPBROWSER PLUGIN

#define CORDOVA_INAPPBROWSER_TARGET_BLANK 0
#define CORDOVA_INAPPBROWSER_TARGET_SELF 1
#define CORDOVA_INAPPBROWSER_TARGET_SYSTEM 2

// defined in cordova-library.js
void cordova_inappbrowser_open(char *url, int target);

// Visit the github repo for the plugin to see ALLLL the possible options: https://github.com/apache/cordova-plugin-inappbrowser/blob/master/README.md#cordovainappbrowseropen
void cordova_inappbrowser_set_option(char *name, char *value);

// defined in cordova-library.js, type=0 means the value will be URL, type=1 means the value will be script contents.
void cordova_inappbrowser_execute_script(int type, char *value);

void cordova_inappbrowser_execute_script_callback(int count, char *return_values)
{
    // TODO - store what is returned from executing the script.
}

// defined in cordova-library.js, type=0 means the value will be URL, type=1 means the value will be CSS contents.
void cordova_inappbrowser_insert_css(int type, char *value);

// INAPPBROWSER PLUGIN
// ==========================================================================================


// ==========================================================================================
// VIBRATION PLUGIN

// defined in cordova-library.js
void cordova_vibration_start(int count, int *duration);

// VIBRATION PLUGIN
// ==========================================================================================

#endif