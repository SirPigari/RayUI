#include <raylib.h>

#define RAYUI_IMPLEMENTATION
#include <rayui.h>

int main() {
    InitWindow(800, 600, "RayUI ToggleLabel Example");
    SetTargetFPS(60);

    RayUIToggleLabel toggle = RayUICreateToggle(300, 250, 200, 50, false, "ON", "OFF");
    Font font = GetFontDefault();

    while (!WindowShouldClose()) {
        Vector2 mousePoint = GetMousePosition();

        BeginDrawing();
        ClearBackground(DARKGRAY);

        RayUIUpdateToggleLabel(&toggle, mousePoint);
        RayUIDrawToggleLabelEx(&toggle, font, 20, RAYWHITE, YELLOW, LIGHTGRAY, 2, BLACK);

        DrawText(TextFormat("Toggle is: %s", RayUIGetToggleValue(&toggle) ? "ON" : "OFF"), 300, 320, 20, RAYWHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
