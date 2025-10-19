#include <raylib.h>
#include <math.h>

#define RAYUI_IMPLEMENTATION
#include <rayui.h>

int main() {
    InitWindow(800, 600, "RayUI Basic Dropdown Example");
    SetTargetFPS(60);

    const char* dropdownOptions[] = {
        "Option 1",
        "Option 2",
        "Option 3",
        "Option 4",
        "Option 5"
    };

    RayUIDropdown dropdown = RayUICreateDropdown(300, 250, 200, 50, dropdownOptions, 5, -1);  // -1 for no initial selection
    Font font = GetFontDefault();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        RayUIUpdateDropdown(&dropdown);

        // RayUIDrawDropdown(&dropdown, font, 20, DARKGRAY, WHITE, LIGHTGRAY, DARKGRAY, LIGHTGRAY);
        RayUIDrawDropdownEx(&dropdown, font, 20, DARKGRAY, WHITE, LIGHTGRAY, DARKGRAY, LIGHTGRAY, 2, BLACK, "Select an option");

        const char* selectedValue = RayUIDropdownValue(&dropdown);
        if (selectedValue) {
            DrawText(TextFormat("Selected: %s", selectedValue), 300, 200, 20, GREEN);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
