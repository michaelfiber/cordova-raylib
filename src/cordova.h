#ifndef CORDOVA_H
#define CORDOVA_H

#include <stdbool.h>

// ==========================================================================================
// BATTERY PLUGIN

// The battery level as an int between 0 and 100 inclusive.
int cordova_battery_level = 0;

// Whether or not the device is plugged in.
bool cordova_battery_plugged_in = false;

void cordova_set_battery_level(int level)
{
    cordova_battery_level = level;
}

void cordova_set_battery_plugged_in(int plugged_in)
{
    cordova_battery_plugged_in = plugged_in > 0;
}

// BATTERY PLUGIN
// ==========================================================================================

#endif