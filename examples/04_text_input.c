#include <raylib.h>
#include <math.h>

#define RAYUI_IMPLEMENTATION
#include <rayui.h>

int main() {
    InitWindow(800, 600, "RayUI Basic Text Input Example");
    SetTargetFPS(60);

    RayUITextInput textInput = RayUICreateTextInput(300, 250, 200, 50, "Enter text here...", INPUT_TYPE_TEXT);
    Font font = GetFontDefault();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        RayUIUpdateTextInput(&textInput);

        RayUIDrawTextInput(&textInput, font, 20, DARKGRAY, WHITE, LIGHTGRAY);

        const char* inputText = RayUITextInputValue(&textInput);
        if (inputText) {
            DrawText(TextFormat("Input: %s", inputText), 300, 200, 20, GREEN);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
