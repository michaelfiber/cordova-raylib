#include "raylib.h"
#include "emscripten/emscripten.h"
#include "cordova.h"

int timer_ran = 0;
float timeout = 1.0f;

Texture2D preview_texture = {0};

void update()
{
    if (timer_ran == 0) 
    {
        timeout -= GetFrameTime();
        if (timeout < 0) 
        {
            timer_ran = 1;
            cordova_orientation_lock_int(CORDOVA_ORIENTATION_LANDSCAPE);
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
    DrawText(TextFormat("[battery] %d%%", cordova_battery_level), x, y, s, BLUE);

    y += 10;
    DrawText(TextFormat("[camera] received file: %s", cordova_camera_path), x, y, s, BLUE);

    y += 10;
    DrawText(TextFormat("[orientation] mode: %s", cordova_orientation_mode), x, y, s, BLUE);
    
    EndDrawing();
}

int main(void)
{
    InitWindow(800, 600, "HelloRaylib");

    emscripten_set_main_loop(update, 60, 1);

    CloseWindow();
}