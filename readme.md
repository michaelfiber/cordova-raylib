# Cordova-raylib
I am building an app that is coded in C99 using raylib. The goal is to take that app and compile it to WASM and then use Cordova to package it for web, Android and iOS.  This project is the basis for that.  All the code that is specifically for making raylib+WASM work with Cordova will go here.  

# Plugin Support
The goal is to provide support for the C99 raylib program to leverage any of the main, supported Cordova plugins.  

| Plugin                             | Android | iOS | Web | electron | Implementation        | Status  |
| ------                             | ------- | --- | --- | -------- | --------------------  | ------- |
| cordova-plugin-battery-status      | X       | X   | X   |          | cordova_battery_*     | done    |
| cordova-plugin-camera              | X       | X   | X   |          | cordova_camera_*      | partial |
| cordova-plugin-device              | X       | X   | X   | X        |                       |         |
| cordova-plugin-dialogs             | X       | X   | X   |          |                       |         |
| cordova-plugin-file                | X       | X   | X   |          |                       |         |
| cordova-plugin-geolocation         | X       | X   |     |          | cordova_geolocation_* | done    |
| cordova-plugin-inappbrowser        | X       | X   | X   |          | cordova_inappbrowser_*| partial |
| cordova-plugin-media               | X       | X   | X   |          |                       |         |
| cordova-plugin-media-capture       | X       | X   | X   |          |                       |         |
| cordova-plugin-network-information | X       | X   | X   |          |                       |         |
| cordova-plugin-screen-orientation  | X       | X   |     |          | cordova_orientation_* | done    |
| cordova-plugin-splashscreen        |         |     | X   |          |                       |         |
| cordova-plugin-statusbar           | X       | X   |     |          | cordova_statusbar_*   | done    |
| cordova-plugin-vibration           | X       | X   |     |          |                       |         |