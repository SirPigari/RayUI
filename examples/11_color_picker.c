#include <raylib.h>

#define RAYUI_IMPLEMENTATION
#include <rayui.h>

int main() {
    InitWindow(800, 600, "RayUI Color Picker Example");
    SetTargetFPS(60);

    RayUIColorPicker colorPicker = RayUICreateColorPicker(300, 250, 200, RAYWHITE, COLOR_PICKER_MODE_HSVA);
    Font font = GetFontDefault();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        RayUIUpdateColorPicker(&colorPicker);
        RayUIDrawColorPickerEx(&colorPicker, 1, BLACK, GRAY);

        Color selected = RayUIGetColorPickerValue(&colorPicker);
        DrawText(TextFormat("Selected Color: R:%d G:%d B:%d A:%d",
                            selected.r,
                            selected.g,
                            selected.b,
                            selected.a),
                 250, 500, 20, RAYWHITE);
        DrawRectangle(600, 250, 100, 100, BLACK); // its literally alpha so you need to have a black bg
        DrawRectangle(600, 250, 100, 100, selected);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
