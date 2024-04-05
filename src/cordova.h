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

#endif