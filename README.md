# RayUI

A simple, immediate-mode UI library for [Raylib](https://www.raylib.com/), designed for ease of use and integration with Raylib projects.

## Features

- **Immediate-mode UI**: No state management required, perfect for games and interactive applications
- **Hover tooltips**: Built-in hover information system with customizable delays
- **Sound integration**: Optional sound effects for hover and click events
- **Customizable appearance**: Flexible drawing functions with various styling options
- **Cross-platform**: Works on any platform supported by Raylib
- **Single header**: Easy to integrate into existing projects

## Supported UI Elements

- **Button**: Clickable buttons with text
- **ToggleLabel**: On/off toggle switches with custom labels
- **Slider**: Draggable value sliders
- **OptionSlider**: Slider that snaps to predefined options
- **KeybindInput**: Input field for keyboard key bindings
- **TextInput**: Text input fields with validation (text, int, float, password)
- **ProgressBar**: Visual progress indicators
- **Dropdown**: Expandable dropdown menus
- **HoverText**: Text that displays hover information

## Installation

1. Download `rayui.h` and place it in your project
2. Include it in your code:

```c
#define RAYUI_IMPLEMENTATION
#include "rayui.h"
```

Make sure Raylib is properly installed and linked in your project.

## Basic Usage

```c
#include <raylib.h>

#define RAYUI_IMPLEMENTATION
#include "rayui.h"

int main() {
    InitWindow(800, 600, "My App");
    SetTargetFPS(60);

    // Create a button
    RayUIButton button = RayUICreateButton(300, 250, 200, 50, "Click Me");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        // Update and draw the button
        RayUIUpdateButton(&button);
        RayUIDrawButton(&button, GetFontDefault(), 20, RAYWHITE, YELLOW);

        if (RayUIButtonDown(&button)) {
            // Button was clicked
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
```

## API Reference

### Hover System

All UI elements support optional hover tooltips. Enable them using:

```c
RayUISetHoverInfo(&element.hover, "Tooltip text", false);  // false = draw at mouse position
RayUIEnableHoverInfo(&element.hover);
```

Then call `RayUIDrawHoverables(font, fontSize)` after drawing your UI elements.

### Button

```c
// Creation
RayUIButton button = RayUICreateButton(x, y, width, height, "Text");
RayUIButton button = RayUICreateButtonWithSound(x, y, width, height, "Text", hoverSound, clickSound);

// Update
bool clicked = RayUIUpdateButton(&button);
bool clicked = RayUIUpdateButtonWithMousePoint(&button, mousePoint);
bool held = RayUIButtonDown(&button);

// Drawing
RayUIDrawButton(&button, font, fontSize, color, hoverColor);
RayUIDrawButtonEx(&button, font, fontSize, color, hoverColor, outlineWidth, outlineColor, backgroundColor);
RayUIDrawButtonPro(&button, font, fontSize, color, hoverColor, outlineWidth, outlineColor, backgroundColor,
                   textPressOffsetX, textPressOffsetY, shadowColor, shadowEnabled);
```

### ToggleLabel

```c
// Creation
RayUIToggleLabel toggle = RayUICreateToggle(x, y, width, height, initialValue, "ON", "OFF");
RayUIToggleLabel toggle = RayUICreateToggleWithSound(x, y, width, height, initialValue, "ON", "OFF", hoverSound, clickSound);

// Update
RayUIUpdateToggleLabel(&toggle, mousePoint);

// Drawing
RayUIDrawToggleLabel(&toggle, font, fontSize, color, hoverColor, backgroundColor);
RayUIDrawToggleLabelEx(&toggle, font, fontSize, color, hoverColor, backgroundColor, outlineWidth, outlineColor);

// Value access
bool value = RayUIGetToggleValue(&toggle);
RayUISetToggleValue(&toggle, true);
```

### Slider

```c
// Creation
RayUISlider slider = RayUICreateSlider(x, y, width, minValue, maxValue, initialValue);

// Update
RayUIUpdateSlider(&slider, mousePoint);

// Drawing
RayUIDrawSlider(&slider, barColor, knobColor);

// Value access
int value = RayUISliderValue(&slider);
```

### OptionSlider

```c
// Creation
const char* options[] = {"Low", "Medium", "High"};
RayUIOptionSlider slider = RayUICreateOptionSlider(x, y, width, options, 3, initialIndex);

// Update
RayUIUpdateOptionSlider(&slider, mousePoint);

// Drawing
RayUIDrawOptionSlider(&slider, barColor, knobColor);

// Value access
const char* selected = RayUIOptionSliderValue(&slider);
```

### KeybindInput

```c
// Creation
RayUIKeybindInput keybind = RayUICreateKeybindInput(x, y, width, height, initialKey, hoverSound, clickSound);

// Update
bool changed = RayUIUpdateKeybindInput(&keybind, mousePoint);

// Drawing
RayUIDrawKeybindInput(&keybind, font, fontSize, bgColor, textColor, textHoverColor);

// Value access
KeyboardKey key = RayUIGetKeybindValue(&keybind);
```

### TextInput

```c
// Creation
RayUITextInput input = RayUICreateTextInput(x, y, width, height, "initial", INPUT_TYPE_TEXT);
RayUITextInput input = RayUICreateTextInputWithSound(x, y, width, height, "initial", INPUT_TYPE_TEXT, hoverSound, clickSound);

// Update
RayUIUpdateTextInput(&input);
RayUIUpdateTextInputWithMousePoint(&input, mousePoint);

// Drawing
RayUIDrawTextInput(&input, font, fontSize, bgColor, textColor, textHoverColor);

// Value access
const char* text = RayUITextInputValue(&input);
RayUISetTextInputValue(&input, "new text");
```

Input types: `INPUT_TYPE_TEXT`, `INPUT_TYPE_INT`, `INPUT_TYPE_FLOAT`, `INPUT_TYPE_PASSWORD`

### ProgressBar

```c
// Creation
RayUIProgressBar progress = RayUICreateProgressBar(x, y, width, height, initialValue);

// Update
RayUIUpdateProgressBar(&progress);
RayUIUpdateProgressBarValue(&progress, delta);
RayUISetProgressBarValue(&progress, value);

// Drawing
RayUIDrawProgressBar(&progress, barColor, progressColor);
RayUIDrawProgressBarEx(&progress, barColor, progressColor, outlineWidth, outlineColor);

// Value access
float value = RayUIGetProgressBarValue(&progress);
bool full = RayUIIsProgressBarFull(&progress);
bool empty = RayUIIsProgressBarEmpty(&progress);
```

### Dropdown

```c
// Creation
const char* options[] = {"Option 1", "Option 2", "Option 3"};
RayUIDropdown dropdown = RayUICreateDropdown(x, y, width, height, options, 3, initialIndex);
RayUIDropdown dropdown = RayUICreateDropdownWithSound(x, y, width, height, options, 3, initialIndex, hoverSound, clickSound);

// Update
bool changed = RayUIUpdateDropdown(&dropdown);
bool changed = RayUIUpdateDropdownWithMousePoint(&dropdown, mousePoint);

// Drawing
RayUIDrawDropdown(&dropdown, font, fontSize, bgColor, textColor, hoverColor, optionBgColor, optionHoverColor);
RayUIDrawDropdownEx(&dropdown, font, fontSize, bgColor, textColor, hoverColor, optionBgColor, optionHoverColor,
                    outlineWidth, outlineColor, "Placeholder");

// Value access
const char* selected = RayUIDropdownValue(&dropdown);
int index = RayUIGetDropdownIndex(&dropdown);
RayUISetDropdownIndex(&dropdown, newIndex);
```

### HoverText

```c
// Creation
RayUIHoverText hoverText = RayUICreateHoverText("Text", position, delay);

// Update
RayUIUpdateHoverText(&hoverText, mousePoint);

// Drawing
RayUIDrawHoverText(font, fontSize, &hoverText);
```

## Examples

See the [examples/](examples/) directory for complete working examples of each UI element.

## Configuration

You can customize the hover delay by defining `DEFAULT_HOVER_INFO_DELAY` before including rayui.h:

```c
#define DEFAULT_HOVER_INFO_DELAY 1.0f  // 1 second delay
#define RAYUI_IMPLEMENTATION
#include "rayui.h"
```

## Prefix Customization

By default, all functions are prefixed with `RayUI`. You can change this:

```c
#define RAYUI_PREFIX MyUI  // Functions become MyUIButton, MyUICreateButton, etc.
#define RAYUI_IMPLEMENTATION
#include "rayui.h"
```

Or strip the prefix entirely:

```c
#define RAYUI_STRIP_PREFIX
#define RAYUI_IMPLEMENTATION
#include "rayui.h"
// Functions become Button, CreateButton, etc.
```

## License

See [LICENSE](LICENSE) for details.

## Version

Current version: 1.0.0
