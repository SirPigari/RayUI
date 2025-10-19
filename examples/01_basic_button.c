#include <raylib.h>

#define RAYUI_IMPLEMENTATION
#include <rayui.h>

int main() {
    InitWindow(800, 600, "RayUI Basic Button Example");
    SetTargetFPS(60);

    RayUIButton button = RayUICreateButton(300, 250, 200, 50, "Click Me");
    Font font = GetFontDefault();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        RayUIUpdateButton(&button);

        // RayUIDrawButton(&button, font, 20, RAYWHITE, YELLOW);
        // RayUIDrawButtonEx(&button, font, 20, RAYWHITE, YELLOW, 2, DARKGRAY, LIGHTGRAY);
        RayUIDrawButtonPro(&button, font, 25, RAYWHITE, YELLOW, 2, DARKGRAY, LIGHTGRAY, -2, 2, DARKGRAY, true);

        if (RayUIButtonDown(&button)) {
            DrawText("Button Clicked!", 350, 320, 20, GREEN);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
