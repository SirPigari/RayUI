#include <raylib.h>
#include <math.h>

#define RAYUI_IMPLEMENTATION
#include <rayui.h>

int main() {
    InitWindow(800, 600, "RayUI Basic Progress Bar Example");
    SetTargetFPS(60);

    int count = 0;

    RayUIProgressBar progressBar = RayUICreateProgressBar(300, 250, 200, 50, 0.0f);
    Font font = GetFontDefault();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        RayUIUpdateProgressBar(&progressBar);

        // RayUIDrawProgressBar(&progressBar, DARKGRAY, YELLOW);
        RayUIDrawProgressBarEx(&progressBar, DARKGRAY, YELLOW, 2, BLACK);

        RayUIUpdateProgressBarValue(&progressBar, (sin(GetTime()) + 1) / 20);

        if (RayUIIsProgressBarFull(&progressBar)) {
            count++;
            RayUISetProgressBarValue(&progressBar, 0.0f);
        }

        DrawFPS(10, 40);
        DrawText(TextFormat("Progress Bar Full Count: %d", count), 10, 10, 20, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
