#include "raylib.h"
#include "emscripten/emscripten.h"
#include "cordova.h"

void update()
{
    BeginDrawing();
    ClearBackground(BLACK);
    
    int x = 10;
    int y = 10;
    int s = GetFontDefault().baseSize;

    if (cordova_battery_plugged_in)
    {
        DrawText("[battery] plugged in", x, y, s, GREEN);
    }
    else
    {
        DrawText("[battery] not plugged in", x, y, s, RED);
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