#include <raylib.h>

#define RAYUI_IMPLEMENTATION
#include <rayui.h>

int main() {
    InitWindow(800, 600, "RayUI KeybindInput Example");
    SetTargetFPS(60);

    RayUIKeybindInput keybind = RayUICreateKeybindInput(300, 250, 200, 50, KEY_SPACE, (Sound){0}, (Sound){0});
    Font font = GetFontDefault();

    while (!WindowShouldClose()) {
        Vector2 mousePoint = GetMousePosition();

        BeginDrawing();
        ClearBackground(DARKGRAY);

        RayUIUpdateKeybindInput(&keybind, mousePoint);
        RayUIDrawKeybindInput(&keybind, font, 20, LIGHTGRAY, RAYWHITE, YELLOW);

        DrawText("Click to change keybind", 280, 320, 20, RAYWHITE);
        DrawText(TextFormat("Current Keybind: %s", GetKeyName(RayUIGetKeybindValue(&keybind))), 280, 350, 20, GREEN);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
