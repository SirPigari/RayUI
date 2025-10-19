#include <raylib.h>

#define RAYUI_IMPLEMENTATION
#include <rayui.h>

int main() {
    InitWindow(800, 600, "RayUI Checkbox Example");
    SetTargetFPS(60);

    RayUICheckbox checkbox = RayUICreateCheckbox(300, 250, 32, false); // 32 is the default size for the default texture ()
    Font font = GetFontDefault();

    while (!WindowShouldClose()) {
        Vector2 mousePoint = GetMousePosition();

        BeginDrawing();
        ClearBackground(DARKGRAY);

        RayUIUpdateCheckbox(&checkbox, mousePoint);
        RayUIDrawCheckbox(&checkbox);
        // RayUIDrawCheckboxColorsEx(&checkbox, LIGHTGRAY, DARKGRAY, 2, BLACK);

        DrawText(TextFormat("Checkbox is: %s", RayUIGetCheckboxValue(&checkbox) ? "ON" : "OFF"), 300, 320, 20, RAYWHITE);

        EndDrawing();
    }

    RayUIFreeCheckboxTextures(&checkbox);
    CloseWindow();
    return 0;
}
