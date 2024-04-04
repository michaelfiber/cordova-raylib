#include "raylib.h"
#include "emscripten/emscripten.h"
#include "cordova.h"

float camera_timeout = 5.0f;

void update()
{
    camera_timeout-=GetFrameTime();
    
    if (camera_timeout < 0)
    {
        camera_timeout = 9999999.0f;
        cordova_camera_get_picture();
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

    EndDrawing();
}

int main(void)
{
    InitWindow(800, 600, "HelloRaylib");

    emscripten_set_main_loop(update, 60, 1);

    CloseWindow();
}