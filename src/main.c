#include "raylib.h"
#include "emscripten/emscripten.h"
#include "cordova.h"

int timer_ran = 0;
float timeout = 2.0f;

Texture2D preview_texture = {0};

void update()
{
    if (timer_ran == 0) 
    {
        timeout -= GetFrameTime();
        if (timeout < 0) 
        {
            timer_ran = 1;
            // android emulator says lock is not supported.
            //cordova_orientation_lock_int(CORDOVA_ORIENTATION_LANDSCAPE);
            
            //cordova_geolocation_watch_start();
            
            //cordova_camera_get_picture();
            
            //cordova_statusbar_hide();
            
            //cordova_inappbrowser_set_option("hidden", "no");
            //cordova_inappbrowser_open("https://google.com", CORDOVA_INAPPBROWSER_TARGET_BLANK);

            int *pattern = malloc(3 * sizeof(int));
            pattern[0] = 1000;
            pattern[1] = 1000;
            pattern[2] = 1000;

            cordova_vibration_start(3, pattern);

            free(pattern);
        }
    }

    BeginDrawing();
    ClearBackground(BLACK);
    
    int x = 10;
    int y = 10;
    int s = GetFontDefault().baseSize;

    if (cordova_battery_charging)
    {
        DrawText("[battery] charging", x, y, s, GREEN);
    }
    else
    {
        DrawText("[battery] not charging", x, y, s, RED);
    }
    
    y += 10;
    DrawFPS(x, y);

    y += 20;
    DrawText(TextFormat("[battery] %d%%", cordova_battery_level), x, y, s, BLUE);

    y += 10;
    DrawText(TextFormat("[camera] received file: %s", cordova_camera_path), x, y, s, BLUE);

    y += 10;
    DrawText(TextFormat("[orientation] mode: %s", cordova_orientation_mode), x, y, s, BLUE);
    
    y += 10;
    DrawText(TextFormat("[geolocation] lat: %f, long: %f, accuracy: %d", cordova_geolocation_latitude, cordova_geolocation_longitude, cordova_geolocation_accuracy), x, y, s, BLUE);

    y += 10;
    DrawText(TextFormat("[statusbar] is visible: %d", cordova_statusbar_is_visible()), x, y, s, BLUE);

    EndDrawing();
}

int main(void)
{
    InitWindow(800, 600, "HelloRaylib");

    cordova_statusbar_hide();

    emscripten_set_main_loop(update, 60, 1);

    CloseWindow();
}