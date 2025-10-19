#include <raylib.h>

#define RAYUI_IMPLEMENTATION
#include <rayui.h>

int main() {
    InitWindow(800, 600, "RayUI Numeric Input Example");
    SetTargetFPS(60);

    RayUINumericInput numericInput = RayUICreateNumericInput(300, 250, 50, 60, 0.0f, 0.0f, 2.0f, 0.1f, 1);
    Font font = GetFontDefault();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        RayUIUpdateNumericInput(&numericInput);
        RayUIDrawNumericInputEx(&numericInput, font, 20, RAYWHITE, DARKGRAY, DARKGRAY, BLACK, 2, BLACK);

        float value = RayUIGetNumericInputValue(&numericInput);
        DrawText(TextFormat("Numeric Input Value: %.2f", value), 250, 500, 20, RAYWHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}