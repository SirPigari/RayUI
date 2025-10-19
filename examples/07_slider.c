#include <raylib.h>

#define RAYUI_IMPLEMENTATION
#include <rayui.h>

int main() {
    InitWindow(800, 600, "RayUI Slider Example");
    SetTargetFPS(60);

    RayUISlider slider = RayUICreateSlider(200, 250, 400, 0, 100, 0.5f);
    Font font = GetFontDefault();

    while (!WindowShouldClose()) {
        Vector2 mousePoint = GetMousePosition();

        BeginDrawing();
        ClearBackground(DARKGRAY);

        RayUIUpdateSlider(&slider, mousePoint);
        RayUIDrawSlider(&slider, GRAY, BLUE);

        int value = RayUISliderValue(&slider);
        DrawText(TextFormat("Slider Value: %d", value), 350, 280, 20, RAYWHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
