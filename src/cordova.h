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

#endif