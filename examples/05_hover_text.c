#include <raylib.h>

#define RAYUI_IMPLEMENTATION
#include <rayui.h>

int main() {
    InitWindow(800, 600, "RayUI HoverText Example");
    SetTargetFPS(60);

    RayUIHoverText hoverText = RayUICreateHoverText("Hover over me!", (Vector2){350, 280}, 0.25f);
    RayUISetHoverInfo(&hoverText.hover, "This is hover information!", false);
    RayUIEnableHoverInfo(&hoverText.hover);

    Font font = GetFontDefault();

    while (!WindowShouldClose()) {
        Vector2 mousePoint = GetMousePosition();

        BeginDrawing();
        ClearBackground(DARKGRAY);

        RayUIUpdateHoverText(&hoverText, mousePoint);
        RayUIDrawHoverText(font, 20, &hoverText);
        RayUIDrawHoverables(font, 20);

        DrawText("Hover over the text to see info", 250, 350, 20, RAYWHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
