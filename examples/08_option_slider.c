#include <raylib.h>

#define RAYUI_IMPLEMENTATION
#include <rayui.h>

int main() {
    InitWindow(800, 600, "RayUI OptionSlider Example");
    SetTargetFPS(60);

    const char* options[] = {"Low", "Medium", "High", "Ultra"};
    int optionCount = 4;
    RayUIOptionSlider optionSlider = RayUICreateOptionSlider(200, 250, 400, options, optionCount, 1);
    Font font = GetFontDefault();

    while (!WindowShouldClose()) {
        Vector2 mousePoint = GetMousePosition();

        BeginDrawing();
        ClearBackground(DARKGRAY);

        RayUIUpdateOptionSlider(&optionSlider, mousePoint);
        RayUIDrawOptionSlider(&optionSlider, GRAY, BLUE);

        const char* selected = RayUIOptionSliderValue(&optionSlider);
        DrawText(TextFormat("Selected: %s", selected), 350, 280, 20, RAYWHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
