# Cordova-raylib
I am building an app that is coded in C99 using raylib. The goal is to take that app and compile it to WASM and then use Cordova to package it for web, Android and iOS.  This project is the basis for that.  All the code that is specifically for making raylib+WASM work with Cordova will go here.  

# Plugin Support
The goal is to provide support for the C99 raylib program to leverage any of the main, supported Cordova plugins.  

| Plugin | Implementation | Status |
| --- | --- |
| cordova-plugin-battery-status | cordova_battery_* | done |