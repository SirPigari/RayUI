// RayUI: A simple immediate-mode UI library for Raylib
// Copyright (c) 2025 SirPigari (https://github.com/SirPigari/RayUI)

#ifndef RAYUI_H
#define RAYUI_H

#include <raylib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#ifndef DEFAULT_HOVER_INFO_DELAY
#define DEFAULT_HOVER_INFO_DELAY 0.7
#endif
#ifndef MAX_HOVERABLES
#define MAX_HOVERABLES 256
#endif
#ifndef CHECKBOX_DEFAULT_TEXTURE_SIZE
#define CHECKBOX_DEFAULT_TEXTURE_SIZE 32
#endif

#ifndef MIN_INT
#define MIN_INT -2147483648
#endif
#ifndef MAX_INT
#define MAX_INT 2147483647
#endif

#ifndef MIN_FLOAT
#define MIN_FLOAT -3.402823466e+38F
#endif
#ifndef MAX_FLOAT
#define MAX_FLOAT 3.402823466e+38F
#endif

#ifndef RAYUI_WITH_PREFIX
    #ifdef RAYUI_STRIP_PREFIX
        #define RAYUI_WITH_PREFIX(name) name

    #elif defined(RAYUI_PREFIX)
        #define RAYUI_WITH_PREFIX(name) RAYUI_CONCAT(RAYUI_PREFIX, name)

    #else
        #define RAYUI_WITH_PREFIX(name) RAYUI_CONCAT(RayUI, name)
    #endif
#endif

#ifndef RAYUI_CONCAT
    #define RAYUI_CONCAT_(a, b) a##b
    #define RAYUI_CONCAT(a, b) RAYUI_CONCAT_(a, b)
#endif

#if defined(RAYLIB_VERSION_MAJOR) && defined(RAYLIB_VERSION_MINOR)
    // Add missing GetKeyName for raylib 5.5.x and 5.6.x
    #if RAYLIB_VERSION_MAJOR == 5 && (RAYLIB_VERSION_MINOR == 5 || RAYLIB_VERSION_MINOR == 6) && !defined(OVERRIDE_RAYLIB_GETKEYNAME)
        #define OVERRIDE_RAYLIB_GETKEYNAME
    #endif
#endif

#ifndef Clamp
#define Clamp(x, lo, hi) ((x) < (lo) ? (lo) : ((x) > (hi) ? (hi) : (x)))
#endif

#define RAYUI_VERSION_MAJOR  1
#define RAYUI_VERSION_MINOR  1
#define RAYUI_VERSION_PATCH  0
#define RAYUI_VERSION_STRING "1.1.0"

#ifdef __cplusplus
extern "C" {
#endif

// DECLARATIONS


typedef struct RAYUI_WITH_PREFIX(Hoverable) {
    const char* hoverInfo;
    double hoverStartTime;
    float delay;
    bool hovered;
    bool drawAtTop;
    bool active;
    Vector2 lastMousePos;
} RAYUI_WITH_PREFIX(Hoverable);

typedef struct RAYUI_WITH_PREFIX(HoverText) {
    const char* text;
    Vector2 position;
    RAYUI_WITH_PREFIX(Hoverable) hover;
} RAYUI_WITH_PREFIX(HoverText);

typedef struct RAYUI_WITH_PREFIX(Button) {
    Rectangle rect;
    const char* text;
    bool hovered;
    Sound hoverSound;
    Sound clickSound;
    RAYUI_WITH_PREFIX(Hoverable) hover;
} RAYUI_WITH_PREFIX(Button);

typedef struct RAYUI_WITH_PREFIX(ToggleLabel) {
    Rectangle rect;
    bool value;
    bool hovered;
    Sound hoverSound;
    Sound clickSound;
    RAYUI_WITH_PREFIX(Hoverable) hover;
    const char* onLabel;
    const char* offLabel;
} RAYUI_WITH_PREFIX(ToggleLabel);

typedef struct RAYUI_WITH_PREFIX(Checkbox) {
    Rectangle rect;
    bool value;
    bool hovered;
    Sound hoverSound;
    Sound clickSound;
    Texture checkboxOnImage;
    Texture checkboxOffImage;
    RAYUI_WITH_PREFIX(Hoverable) hover;
} RAYUI_WITH_PREFIX(Checkbox);

typedef struct RAYUI_WITH_PREFIX(Slider) {
    Rectangle bar;
    float value;
    int minVal, maxVal;
    bool dragging;
    RAYUI_WITH_PREFIX(Hoverable) hover;
} RAYUI_WITH_PREFIX(Slider);

typedef struct RAYUI_WITH_PREFIX(OptionSlider) {
    Rectangle bar;
    int selectedIndex;
    int optionCount;
    const char** options;
    bool dragging;
    RAYUI_WITH_PREFIX(Hoverable) hover;
} RAYUI_WITH_PREFIX(OptionSlider);

typedef struct RAYUI_WITH_PREFIX(KeybindInput) {
    Rectangle rect;
    KeyboardKey key;
    bool listening;
    bool hovered;
    Sound hoverSound;
    Sound clickSound;
    RAYUI_WITH_PREFIX(Hoverable) hover;
} RAYUI_WITH_PREFIX(KeybindInput);

typedef enum {
    INPUT_TYPE_TEXT,
    INPUT_TYPE_INT,
    INPUT_TYPE_FLOAT,
    INPUT_TYPE_PASSWORD
} RAYUI_WITH_PREFIX(InputType);

typedef struct RAYUI_WITH_PREFIX(TextInput) {
    Rectangle rect;
    char text[128];
    bool focused;
    bool cleared;
    bool hovered;
    Sound hoverSound;
    Sound clickSound;
    float backspaceTimer;
    float backspaceHoldTime;
    bool backspacePressed;
    RAYUI_WITH_PREFIX(InputType) inputType;
    RAYUI_WITH_PREFIX(Hoverable) hover;
} RAYUI_WITH_PREFIX(TextInput);

typedef struct RAYUI_WITH_PREFIX(ProgressBar) {
    Rectangle bar;
    float progress; // 0.0 to 1.0
    RAYUI_WITH_PREFIX(Hoverable) hover;
} RAYUI_WITH_PREFIX(ProgressBar);

typedef struct RAYUI_WITH_PREFIX(Dropdown) {
    Rectangle rect;
    const char** options;
    int optionCount;
    int selectedIndex;
    bool expanded;
    bool hovered;
    Sound hoverSound;
    Sound clickSound;
    RAYUI_WITH_PREFIX(Hoverable) hover;
} RAYUI_WITH_PREFIX(Dropdown);

typedef enum {
    COLOR_PICKER_MODE_RGB,
    COLOR_PICKER_MODE_RGBA,
    COLOR_PICKER_MODE_HSV,
    COLOR_PICKER_MODE_HSVA,
} RAYUI_WITH_PREFIX(ColorPickerMode);

typedef struct RAYUI_WITH_PREFIX(ColorPicker) {
    Rectangle rect;
    Rectangle alphaRect;
    Color selectedColor;
    Vector2 selectorPos;
    Rectangle sliderR, sliderG, sliderB;
    bool draggingSliderR;
    bool draggingSliderG;
    bool draggingSliderB;
    bool draggingAlpha;
    bool draggingColor;
    RAYUI_WITH_PREFIX(ColorPickerMode) mode;
    bool expanded;
    bool hovered;
    bool showAlpha;
    Sound hoverSound;
    Sound clickSound;
    RAYUI_WITH_PREFIX(Hoverable) hover;
} RAYUI_WITH_PREFIX(ColorPicker);

typedef struct Triangle {
    Vector2 a;
    Vector2 b;
    Vector2 c;
} Triangle;

typedef struct RAYUI_WITH_PREFIX(NumericInput) {
    Rectangle rect;
    float value;
    float step;
    float minValue;
    float maxValue;
    int decimalPlaces;
    bool hoveredUp;
    bool hoveredDown;
    Triangle upTriangle;
    Triangle downTriangle;
    Sound hoverSound;
    Sound clickSound;
    RAYUI_WITH_PREFIX(Hoverable) hover;
} RAYUI_WITH_PREFIX(NumericInput);

static RAYUI_WITH_PREFIX(Hoverable)* HOVER_INFO_ARRAY[MAX_HOVERABLES];
static int HOVER_INFO_COUNT = 0;

static Sound _rayui_DefaultSound = {0};

static Texture defaultCheckboxOnTexture = {0};
static Texture defaultCheckboxOffTexture = {0};

#ifdef OVERRIDE_RAYLIB_GETKEYNAME
const char* GetKeyName(int key);
#endif

void RAYUI_WITH_PREFIX(SetHoverInfo)(RAYUI_WITH_PREFIX(Hoverable)* h, const char* info, bool drawAtTop);
void RAYUI_WITH_PREFIX(DisableHoverInfo)(RAYUI_WITH_PREFIX(Hoverable)* h);
void RAYUI_WITH_PREFIX(EnableHoverInfo)(RAYUI_WITH_PREFIX(Hoverable)* h);
void RAYUI_WITH_PREFIX(DrawHoverables)(Font font, int fontSize);

RAYUI_WITH_PREFIX(HoverText) RAYUI_WITH_PREFIX(CreateHoverText)(const char* text, Vector2 position, float delay);
void RAYUI_WITH_PREFIX(DrawHoverText)(Font font, int fontSize, RAYUI_WITH_PREFIX(HoverText)* hoverText);
void RAYUI_WITH_PREFIX(UpdateHoverText)(RAYUI_WITH_PREFIX(HoverText)* hoverText, Vector2 mousePoint);

RAYUI_WITH_PREFIX(Button) RAYUI_WITH_PREFIX(CreateButton)(float x, float y, float width, float height, const char* text);
RAYUI_WITH_PREFIX(Button) RAYUI_WITH_PREFIX(CreateButtonWithSound)(float x, float y, float width, float height, const char* text, Sound hoverSound, Sound clickSound);
bool RAYUI_WITH_PREFIX(UpdateButton)(RAYUI_WITH_PREFIX(Button)* b);
bool RAYUI_WITH_PREFIX(UpdateButtonWithMousePoint)(RAYUI_WITH_PREFIX(Button)* b, Vector2 mousePoint);
bool RAYUI_WITH_PREFIX(ButtonDown)(RAYUI_WITH_PREFIX(Button)* b);
void RAYUI_WITH_PREFIX(DrawButton)(RAYUI_WITH_PREFIX(Button)* b, Font font, int fontSize, Color color, Color hoverColor);
void RAYUI_WITH_PREFIX(DrawButtonEx)(RAYUI_WITH_PREFIX(Button)* b, Font font, int fontSize,
                                     Color color, Color hoverColor, int outline_width,
                                     Color outlineColor, Color backgroundColor);
void RAYUI_WITH_PREFIX(DrawButtonPro)(RAYUI_WITH_PREFIX(Button)* b, Font font, int fontSize,
                                     Color color, Color hoverColor, int outline_width,
                                     Color outlineColor, Color backgroundColor,
                                     int textPressOffsetRight, int textPressOffsetDown, Color shadowColor, bool shadowEnabled);

RAYUI_WITH_PREFIX(ToggleLabel) RAYUI_WITH_PREFIX(CreateToggle)(float x, float y, float width, float height, bool initial, const char* onLabel, const char* offLabel);
RAYUI_WITH_PREFIX(ToggleLabel) RAYUI_WITH_PREFIX(CreateToggleWithSound)(float x, float y, float width, float height, bool initial, const char* onLabel, const char* offLabel, Sound hoverSound, Sound clickSound);
void RAYUI_WITH_PREFIX(UpdateToggleLabel)(RAYUI_WITH_PREFIX(ToggleLabel)* t, Vector2 mousePoint);
void RAYUI_WITH_PREFIX(DrawToggleLabel)(RAYUI_WITH_PREFIX(ToggleLabel)* t, Font font, int fontSize, Color color, Color hoverColor, Color backgroundColor);
void RAYUI_WITH_PREFIX(DrawToggleLabelEx)(RAYUI_WITH_PREFIX(ToggleLabel)* t, Font font, int fontSize,
                                         Color color, Color hoverColor, Color backgroundColor,
                                         int outline_width, Color outlineColor);
bool RAYUI_WITH_PREFIX(GetToggleValue)(RAYUI_WITH_PREFIX(ToggleLabel)* t);
void RAYUI_WITH_PREFIX(SetToggleValue)(RAYUI_WITH_PREFIX(ToggleLabel)* t, bool value);

RAYUI_WITH_PREFIX(Checkbox) RAYUI_WITH_PREFIX(CreateCheckbox)(float x, float y, float size, bool initial);
RAYUI_WITH_PREFIX(Checkbox) RAYUI_WITH_PREFIX(CreateCheckboxWithSound)(float x, float y, float size, bool initial, Sound hoverSound, Sound clickSound);
void RAYUI_WITH_PREFIX(UpdateCheckbox)(RAYUI_WITH_PREFIX(Checkbox)* c, Vector2 mousePoint);
void RAYUI_WITH_PREFIX(DrawCheckbox)(RAYUI_WITH_PREFIX(Checkbox)* c);
void RAYUI_WITH_PREFIX(DrawCheckboxColors)(RAYUI_WITH_PREFIX(Checkbox)* c, Color onColor, Color offColor);
void RAYUI_WITH_PREFIX(DrawCheckboxColorsEx)(RAYUI_WITH_PREFIX(Checkbox)* c, Color onColor, Color offColor, int outline_width, Color outlineColor);
bool RAYUI_WITH_PREFIX(GetCheckboxValue)(RAYUI_WITH_PREFIX(Checkbox)* c);
void RAYUI_WITH_PREFIX(SetCheckboxValue)(RAYUI_WITH_PREFIX(Checkbox)* c, bool value);
void RAYUI_WITH_PREFIX(SetCheckboxTextures)(RAYUI_WITH_PREFIX(Checkbox)* c, Texture onTexture, Texture offTexture);
void RAYUI_WITH_PREFIX(FreeCheckboxTextures)(RAYUI_WITH_PREFIX(Checkbox)* c);
Texture RAYUI_WITH_PREFIX(GetCheckboxOnTexture)(void);
Texture RAYUI_WITH_PREFIX(GetCheckboxOffTexture)(void);

RAYUI_WITH_PREFIX(Slider) RAYUI_WITH_PREFIX(CreateSlider)(int x, int y, int width, int minVal, int maxVal, float initial);
void RAYUI_WITH_PREFIX(UpdateSlider)(RAYUI_WITH_PREFIX(Slider)* s, Vector2 mousePoint);
int RAYUI_WITH_PREFIX(SliderValue)(RAYUI_WITH_PREFIX(Slider)* s);
void RAYUI_WITH_PREFIX(DrawSlider)(RAYUI_WITH_PREFIX(Slider)* s, Color color, Color knobColor);

RAYUI_WITH_PREFIX(OptionSlider) RAYUI_WITH_PREFIX(CreateOptionSlider)(int x, int y, int width, const char** options, int optionCount, int initialIndex);
void RAYUI_WITH_PREFIX(UpdateOptionSlider)(RAYUI_WITH_PREFIX(OptionSlider)* s, Vector2 mousePoint);
const char* RAYUI_WITH_PREFIX(OptionSliderValue)(RAYUI_WITH_PREFIX(OptionSlider)* s);
void RAYUI_WITH_PREFIX(DrawOptionSlider)(RAYUI_WITH_PREFIX(OptionSlider)* s, Color color, Color knobColor);

RAYUI_WITH_PREFIX(KeybindInput) RAYUI_WITH_PREFIX(CreateKeybindInput)(float x, float y, float width, float height, int initialKey, Sound hoverSound, Sound clickSound);
bool RAYUI_WITH_PREFIX(UpdateKeybindInput)(RAYUI_WITH_PREFIX(KeybindInput)* k, Vector2 mousePoint);
void RAYUI_WITH_PREFIX(DrawKeybindInput)(RAYUI_WITH_PREFIX(KeybindInput)* k, Font font, int fontSize, Color bgColor, Color textColor, Color textHoverColor);

RAYUI_WITH_PREFIX(TextInput) RAYUI_WITH_PREFIX(CreateTextInput)(int x, int y, int width, int height, const char* initial, RAYUI_WITH_PREFIX(InputType) type);
RAYUI_WITH_PREFIX(TextInput) RAYUI_WITH_PREFIX(CreateTextInputWithSound)(int x, int y, int width, int height, const char* initial, RAYUI_WITH_PREFIX(InputType) type, Sound hoverSound, Sound clickSound);
void RAYUI_WITH_PREFIX(UpdateTextInput)(RAYUI_WITH_PREFIX(TextInput)* ti);
void RAYUI_WITH_PREFIX(UpdateTextInputWithMousePoint)(RAYUI_WITH_PREFIX(TextInput)* ti, Vector2 mousePoint);
void RAYUI_WITH_PREFIX(DrawTextInput)(RAYUI_WITH_PREFIX(TextInput)* ti, Font font, int fontSize, Color bgColor, Color textColor, Color textHoverColor);
const char* RAYUI_WITH_PREFIX(TextInputValue)(RAYUI_WITH_PREFIX(TextInput)* ti);
void RAYUI_WITH_PREFIX(SetTextInputValue)(RAYUI_WITH_PREFIX(TextInput)* ti, const char* value);

RAYUI_WITH_PREFIX(ProgressBar) RAYUI_WITH_PREFIX(CreateProgressBar)(int x, int y, int width, int height, float initialValue);
void RAYUI_WITH_PREFIX(UpdateProgressBar)(RAYUI_WITH_PREFIX(ProgressBar)* pb);
void RAYUI_WITH_PREFIX(UpdateProgressBarValue)(RAYUI_WITH_PREFIX(ProgressBar)* pb, float delta);
void RAYUI_WITH_PREFIX(SetProgressBarValue)(RAYUI_WITH_PREFIX(ProgressBar)* pb, float value);
void RAYUI_WITH_PREFIX(DrawProgressBar)(RAYUI_WITH_PREFIX(ProgressBar)* pb, Color barColor, Color progressColor);
void RAYUI_WITH_PREFIX(DrawProgressBarEx)(RAYUI_WITH_PREFIX(ProgressBar)* pb, Color barColor, Color progressColor, int outline_width, Color outlineColor);
bool RAYUI_WITH_PREFIX(IsProgressBarFull)(RAYUI_WITH_PREFIX(ProgressBar)* pb);
bool RAYUI_WITH_PREFIX(IsProgressBarEmpty)(RAYUI_WITH_PREFIX(ProgressBar)* pb);

RAYUI_WITH_PREFIX(Dropdown) RAYUI_WITH_PREFIX(CreateDropdown)(float x, float y, float width, float height, const char** options, int optionCount, int initialIndex);
RAYUI_WITH_PREFIX(Dropdown) RAYUI_WITH_PREFIX(CreateDropdownWithSound)(float x, float y, float width, float height, const char** options, int optionCount, int initialIndex, Sound hoverSound, Sound clickSound);
bool RAYUI_WITH_PREFIX(UpdateDropdown)(RAYUI_WITH_PREFIX(Dropdown)* d);
bool RAYUI_WITH_PREFIX(UpdateDropdownWithMousePoint)(RAYUI_WITH_PREFIX(Dropdown)* d, Vector2 mousePoint);
void RAYUI_WITH_PREFIX(DrawDropdown)(RAYUI_WITH_PREFIX(Dropdown)* d, Font font, int fontSize,
                                    Color bgColor, Color textColor, Color hoverColor,
                                    Color optionBgColor, Color optionHoverColor);
void RAYUI_WITH_PREFIX(DrawDropdownEx)(RAYUI_WITH_PREFIX(Dropdown)* d, Font font, int fontSize,
                                       Color bgColor, Color textColor, Color hoverColor,
                                       Color optionBgColor, Color optionHoverColor,
                                       int outlineWidth, Color outlineColor, const char* placeholderText);
const char* RAYUI_WITH_PREFIX(DropdownValue)(RAYUI_WITH_PREFIX(Dropdown)* d);
void RAYUI_WITH_PREFIX(SetDropdownValue)(RAYUI_WITH_PREFIX(Dropdown)* d, int index);
int RAYUI_WITH_PREFIX(GetDropdownIndex)(RAYUI_WITH_PREFIX(Dropdown)* d);
void RAYUI_WITH_PREFIX(SetDropdownIndex)(RAYUI_WITH_PREFIX(Dropdown)* d, int index);

RAYUI_WITH_PREFIX(ColorPicker) RAYUI_WITH_PREFIX(CreateColorPicker)(float x, float y, float size, Color initialColor, RAYUI_WITH_PREFIX(ColorPickerMode) mode);
RAYUI_WITH_PREFIX(ColorPicker) RAYUI_WITH_PREFIX(CreateColorPickerWithSound)(float x, float y, float size, Color initialColor, RAYUI_WITH_PREFIX(ColorPickerMode) mode, Sound hoverSound, Sound clickSound);
void RAYUI_WITH_PREFIX(UpdateColorPicker)(RAYUI_WITH_PREFIX(ColorPicker)* cp);
void RAYUI_WITH_PREFIX(DrawColorPicker)(RAYUI_WITH_PREFIX(ColorPicker)* cp);
void RAYUI_WITH_PREFIX(DrawColorPickerEx)(RAYUI_WITH_PREFIX(ColorPicker)* cp,
                                          int outlineWidth,
                                          Color outlineColor,
                                          Color thumbColor);
Color RAYUI_WITH_PREFIX(GetColorPickerValue)(RAYUI_WITH_PREFIX(ColorPicker)* cp);
void RAYUI_WITH_PREFIX(SetColorPickerValue)(RAYUI_WITH_PREFIX(ColorPicker)* cp, Color color);

RAYUI_WITH_PREFIX(NumericInput) RAYUI_WITH_PREFIX(CreateNumericInput)(
    float x, float y, float width, float height, float initialValue,
    float minValue, float maxValue, float step, int decimalPlaces);
void RAYUI_WITH_PREFIX(UpdateNumericInput)(RAYUI_WITH_PREFIX(NumericInput)* n);
void RAYUI_WITH_PREFIX(DrawNumericInput)(RAYUI_WITH_PREFIX(NumericInput)* n, Font font, int fontSize, Color bgColor, Color textColor);
void RAYUI_WITH_PREFIX(DrawNumericInputEx)(RAYUI_WITH_PREFIX(NumericInput)* n,
                                         Font font, int fontSize,
                                         Color bgColor, Color textColor, Color triangleColor, Color triangleHoverColor, int outline_width, Color outlineColor);
float RAYUI_WITH_PREFIX(GetNumericInputValue)(RAYUI_WITH_PREFIX(NumericInput)* n);
void RAYUI_WITH_PREFIX(SetNumericInputValue)(RAYUI_WITH_PREFIX(NumericInput)* n, float value);


// IMPLEMENTATION
#ifdef RAYUI_IMPLEMENTATION

#ifdef OVERRIDE_RAYLIB_GETKEYNAME
const char* GetKeyName(int key) {
    switch (key) {
        case KEY_NULL: return "NONE";

        // Android special buttons
        case KEY_BACK: return "BACK";
        case KEY_MENU: return "MENU";
        case KEY_VOLUME_UP: return "VOLUME UP";
        case KEY_VOLUME_DOWN: return "VOLUME DOWN";

        // Symbols
        case KEY_APOSTROPHE: return "'";
        case KEY_COMMA: return ",";
        case KEY_MINUS: return "-";
        case KEY_PERIOD: return ".";
        case KEY_SLASH: return "/";
        case KEY_SEMICOLON: return ";";
        case KEY_EQUAL: return "=";
        case KEY_LEFT_BRACKET: return "[";
        case KEY_BACKSLASH: return "\\";
        case KEY_RIGHT_BRACKET: return "]";
        case KEY_GRAVE: return "`";

        // Numbers
        case KEY_ZERO: return "0";
        case KEY_ONE: return "1";
        case KEY_TWO: return "2";
        case KEY_THREE: return "3";
        case KEY_FOUR: return "4";
        case KEY_FIVE: return "5";
        case KEY_SIX: return "6";
        case KEY_SEVEN: return "7";
        case KEY_EIGHT: return "8";
        case KEY_NINE: return "9";

        // Letters
        case KEY_A: return "A";
        case KEY_B: return "B";
        case KEY_C: return "C";
        case KEY_D: return "D";
        case KEY_E: return "E";
        case KEY_F: return "F";
        case KEY_G: return "G";
        case KEY_H: return "H";
        case KEY_I: return "I";
        case KEY_J: return "J";
        case KEY_K: return "K";
        case KEY_L: return "L";
        case KEY_M: return "M";
        case KEY_N: return "N";
        case KEY_O: return "O";
        case KEY_P: return "P";
        case KEY_Q: return "Q";
        case KEY_R: return "R";
        case KEY_S: return "S";
        case KEY_T: return "T";
        case KEY_U: return "U";
        case KEY_V: return "V";
        case KEY_W: return "W";
        case KEY_X: return "X";
        case KEY_Y: return "Y";
        case KEY_Z: return "Z";

        // Function keys
        case KEY_F1: return "F1";
        case KEY_F2: return "F2";
        case KEY_F3: return "F3";
        case KEY_F4: return "F4";
        case KEY_F5: return "F5";
        case KEY_F6: return "F6";
        case KEY_F7: return "F7";
        case KEY_F8: return "F8";
        case KEY_F9: return "F9";
        case KEY_F10: return "F10";
        case KEY_F11: return "F11";
        case KEY_F12: return "F12";

        // Control keys
        case KEY_SPACE: return "SPACE";
        case KEY_ESCAPE: return "ESC";
        case KEY_ENTER: return "ENTER";
        case KEY_TAB: return "TAB";
        case KEY_BACKSPACE: return "BACKSPACE";
        case KEY_INSERT: return "INSERT";
        case KEY_DELETE: return "DELETE";
        case KEY_HOME: return "HOME";
        case KEY_END: return "END";
        case KEY_PAGE_UP: return "PAGE UP";
        case KEY_PAGE_DOWN: return "PAGE DOWN";

        // Navigation
        case KEY_UP: return "UP";
        case KEY_DOWN: return "DOWN";
        case KEY_LEFT: return "LEFT";
        case KEY_RIGHT: return "RIGHT";

        // Locks and toggles
        case KEY_CAPS_LOCK: return "CAPS LOCK";
        case KEY_SCROLL_LOCK: return "SCROLL LOCK";
        case KEY_NUM_LOCK: return "NUM LOCK";
        case KEY_PRINT_SCREEN: return "PRINT SCREEN";
        case KEY_PAUSE: return "PAUSE";

        // Modifiers
        case KEY_LEFT_SHIFT: return "LEFT SHIFT";
        case KEY_RIGHT_SHIFT: return "RIGHT SHIFT";
        case KEY_LEFT_CONTROL: return "LEFT CTRL";
        case KEY_RIGHT_CONTROL: return "RIGHT CTRL";
        case KEY_LEFT_ALT: return "LEFT ALT";
        case KEY_RIGHT_ALT: return "RIGHT ALT";
        case KEY_LEFT_SUPER: return "LEFT SUPER";
        case KEY_RIGHT_SUPER: return "RIGHT SUPER";
        case KEY_KB_MENU: return "KB MENU";

        // Numpad
        case KEY_KP_0: return "NUMPAD 0";
        case KEY_KP_1: return "NUMPAD 1";
        case KEY_KP_2: return "NUMPAD 2";
        case KEY_KP_3: return "NUMPAD 3";
        case KEY_KP_4: return "NUMPAD 4";
        case KEY_KP_5: return "NUMPAD 5";
        case KEY_KP_6: return "NUMPAD 6";
        case KEY_KP_7: return "NUMPAD 7";
        case KEY_KP_8: return "NUMPAD 8";
        case KEY_KP_9: return "NUMPAD 9";
        case KEY_KP_DECIMAL: return "NUMPAD .";
        case KEY_KP_DIVIDE: return "NUMPAD /";
        case KEY_KP_MULTIPLY: return "NUMPAD *";
        case KEY_KP_SUBTRACT: return "NUMPAD -";
        case KEY_KP_ADD: return "NUMPAD +";
        case KEY_KP_ENTER: return "NUMPAD ENTER";
        case KEY_KP_EQUAL: return "NUMPAD =";

        default: return "UNKNOWN";
    }
}
#endif

void RAYUI_WITH_PREFIX(SetHoverInfo)(RAYUI_WITH_PREFIX(Hoverable)* h, const char* info, bool drawAtTop) {
    h->hoverInfo = info;
    h->drawAtTop = drawAtTop;
    h->lastMousePos = (Vector2){-1, -1};
    h->active = true;
    HOVER_INFO_ARRAY[HOVER_INFO_COUNT++] = h;
}

void RAYUI_WITH_PREFIX(DisableHoverInfo)(RAYUI_WITH_PREFIX(Hoverable)* h) {
    h->active = false;
    for (int i = 0; i < HOVER_INFO_COUNT; i++) {
        if (HOVER_INFO_ARRAY[i] == h) {
            for (int j = i; j < HOVER_INFO_COUNT - 1; j++) {
                HOVER_INFO_ARRAY[j] = HOVER_INFO_ARRAY[j + 1];
            }
            HOVER_INFO_COUNT--;
            break;
        }
    }
}

void RAYUI_WITH_PREFIX(EnableHoverInfo)(RAYUI_WITH_PREFIX(Hoverable)* h) {
    h->active = true;
    bool found = false;
    for (int i = 0; i < HOVER_INFO_COUNT; i++) {
        if (HOVER_INFO_ARRAY[i] == h) {
            found = true;
            break;
        }
    }
    if (!found && HOVER_INFO_COUNT < MAX_HOVERABLES) {
        HOVER_INFO_ARRAY[HOVER_INFO_COUNT++] = h;
    }
}

void RAYUI_WITH_PREFIX(DrawHoverables)(Font font, int fontSize) {
    Vector2 mousePoint = GetMousePosition();

    for (int i = 0; i < HOVER_INFO_COUNT; i++) {
        RAYUI_WITH_PREFIX(Hoverable)* h = HOVER_INFO_ARRAY[i];
        if (!h->hoverInfo) continue;

        if (h->hoverStartTime > 0 &&
            (h->lastMousePos.x != mousePoint.x || h->lastMousePos.y != mousePoint.y ||
             IsMouseButtonDown(MOUSE_LEFT_BUTTON) || IsMouseButtonDown(MOUSE_RIGHT_BUTTON))) {
            h->hoverStartTime = 0;
        }

        if (h->hovered && h->hoverStartTime == 0) {
            h->hoverStartTime = GetTime();
        }

        if (h->lastMousePos.x == -1 && h->lastMousePos.y == -1) {
            h->lastMousePos = mousePoint;
        } else {
            h->lastMousePos = mousePoint;
        }

        double t = GetTime() - h->hoverStartTime;
        if (h->hovered && t >= h->delay) {
            Vector2 infoSize = MeasureTextEx(font, h->hoverInfo, fontSize, 1);
            float boxX = h->drawAtTop ? 10 : mousePoint.x + 16;
            float boxY = h->drawAtTop ? 10 : mousePoint.y + 16;

            DrawRectangle((int)boxX, (int)boxY, (int)infoSize.x + 10, (int)infoSize.y + 6, BLACK);
            DrawTextEx(font, h->hoverInfo, (Vector2){boxX + 5, boxY + 3}, fontSize, 1, RAYWHITE);

            break;
        }
    }
}

// ---------------- HOVER TEXT ----------------
RAYUI_WITH_PREFIX(HoverText) RAYUI_WITH_PREFIX(CreateHoverText)(const char* text, Vector2 position, float delay) {
    RAYUI_WITH_PREFIX(HoverText) ht;
    ht.text = text;
    ht.position = position;
    ht.hover.hoverInfo = text;
    ht.hover.hoverStartTime = 0;
    ht.hover.hovered = false;
    ht.hover.drawAtTop = true;
    ht.hover.delay = delay;
    ht.hover.active = false;
    ht.hover.lastMousePos = (Vector2){-1, -1};
    return ht;
}

void RAYUI_WITH_PREFIX(DrawHoverText)(Font font, int fontSize, RAYUI_WITH_PREFIX(HoverText)* hoverText) {
    if (!hoverText || !hoverText->text) return;

    DrawTextEx(font, hoverText->text, hoverText->position, fontSize, 1, RAYWHITE);
}

void RAYUI_WITH_PREFIX(UpdateHoverText)(RAYUI_WITH_PREFIX(HoverText)* hoverText, Vector2 mousePoint) {
    if (!hoverText) return;

    Rectangle rect = {hoverText->position.x, hoverText->position.y,
                      MeasureTextEx(GetFontDefault(), hoverText->text, 20, 1).x,
                      MeasureTextEx(GetFontDefault(), hoverText->text, 20, 1).y};

    if (!hoverText->hover.active) return;
    hoverText->hover.hovered = CheckCollisionPointRec(mousePoint, rect);
}

// ---------------- BUTTON ----------------

RAYUI_WITH_PREFIX(Button) RAYUI_WITH_PREFIX(CreateButton)(float x, float y, float width, float height, const char* text) {
    RAYUI_WITH_PREFIX(Button) b;
    b.rect = (Rectangle){x, y, width, height};
    b.text = text;
    b.hovered = false;
    b.hover.hoverInfo = NULL;
    b.hover.hoverStartTime = 0;
    b.hover.hovered = false;
    b.hover.delay = DEFAULT_HOVER_INFO_DELAY;
    b.hover.active = false;
    b.hoverSound = _rayui_DefaultSound;
    b.clickSound = _rayui_DefaultSound;
    return b;
}

RAYUI_WITH_PREFIX(Button) RAYUI_WITH_PREFIX(CreateButtonWithSound)(float x, float y, float width, float height, const char* text, Sound hoverSound, Sound clickSound) {
    RAYUI_WITH_PREFIX(Button) b;
    b.rect = (Rectangle){x, y, width, height};
    b.text = text;
    b.hovered = false;
    b.hover.hoverInfo = NULL;
    b.hover.hoverStartTime = 0;
    b.hover.hovered = false;
    b.hover.delay = DEFAULT_HOVER_INFO_DELAY;
    b.hover.active = false;
    b.hoverSound = hoverSound;
    b.clickSound = clickSound;
    return b;
}

bool RAYUI_WITH_PREFIX(UpdateButton)(RAYUI_WITH_PREFIX(Button)* b) {
    b->hovered = CheckCollisionPointRec(GetMousePosition(), b->rect);
    b->hover.hovered = b->hovered;

    if (b->hover.hovered && b->hover.hoverStartTime == 0) {
        b->hover.hoverStartTime = GetTime();
        if (b->hoverSound.frameCount > 0 && b->hover.active) PlaySound(b->hoverSound);
    }

    if (!b->hover.hovered) {
        b->hover.hoverStartTime = 0;
    }

    if (b->hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (b->clickSound.frameCount > 0 && b->hover.active) PlaySound(b->clickSound);
        return true;
    }

    return false;
}

bool RAYUI_WITH_PREFIX(UpdateButtonWithMousePoint)(RAYUI_WITH_PREFIX(Button)* b, Vector2 mousePoint) {
    b->hovered = CheckCollisionPointRec(mousePoint, b->rect);
    b->hover.hovered = b->hovered;

    if (b->hover.hovered && b->hover.hoverStartTime == 0) {
        b->hover.hoverStartTime = GetTime();
        if (b->hoverSound.frameCount > 0 && b->hover.active) PlaySound(b->hoverSound);
    }

    if (!b->hover.hovered) {
        b->hover.hoverStartTime = 0;
    }

    if (b->hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (b->clickSound.frameCount > 0 && b->hover.active) PlaySound(b->clickSound);
        return true;
    }

    return false;
}

bool RAYUI_WITH_PREFIX(ButtonDown)(RAYUI_WITH_PREFIX(Button)* b) {
    b->hovered = CheckCollisionPointRec(GetMousePosition(), b->rect);
    return b->hovered && IsMouseButtonDown(MOUSE_LEFT_BUTTON);
}

void RAYUI_WITH_PREFIX(DrawButton)(RAYUI_WITH_PREFIX(Button)* b, Font font, int fontSize, Color color, Color hoverColor) {
    Color col = b->hovered ? hoverColor : color;

    Vector2 textSize = MeasureTextEx(font, b->text, fontSize, 2);
    Vector2 pos = {
        b->rect.x + b->rect.width/2 - textSize.x/2,
        b->rect.y + b->rect.height/2 - textSize.y/2
    };
    DrawTextEx(font, b->text, pos, fontSize, 2, col);
}

void RAYUI_WITH_PREFIX(DrawButtonEx)(RAYUI_WITH_PREFIX(Button)* b, Font font, int fontSize,
                                     Color color, Color hoverColor, int outline_width,
                                     Color outlineColor, Color backgroundColor) 
{
    Color textCol = b->hovered ? hoverColor : color;

    DrawRectangleRounded(b->rect, 0.1f, 0, backgroundColor);

    if (outline_width > 0) {
        Rectangle borderRect = {b->rect.x - outline_width/2.0f, b->rect.y - outline_width/2.0f,
                                b->rect.width + outline_width, b->rect.height + outline_width};
        DrawRectangleRoundedLines(borderRect, 0.1f, 0, outlineColor);
    }

    Vector2 textSize = MeasureTextEx(font, b->text, fontSize, 2);

    Vector2 textPos = {
        b->rect.x + b->rect.width/2 - textSize.x/2,
        b->rect.y + b->rect.height/2 - textSize.y/2
    };

    if (RAYUI_WITH_PREFIX(ButtonDown)(b)) {
        textPos.x += 2;
        textPos.y += 2;
    }

    DrawTextEx(font, b->text, textPos, fontSize, 2, textCol);
}

void RAYUI_WITH_PREFIX(DrawButtonPro)(RAYUI_WITH_PREFIX(Button)* b, Font font, int fontSize,
                                     Color color, Color hoverColor, int outline_width,
                                     Color outlineColor, Color backgroundColor,
                                     int textPressOffsetRight, int textPressOffsetDown,
                                     Color shadowColor, bool shadowEnabled) 
{
    Color textCol = b->hovered ? hoverColor : color;

    DrawRectangleRounded(b->rect, 0.1f, 0, backgroundColor);

    if (outline_width > 0) {
        Rectangle borderRect = {b->rect.x - outline_width/2.0f, b->rect.y - outline_width/2.0f,
                                b->rect.width + outline_width, b->rect.height + outline_width};
        DrawRectangleRoundedLines(borderRect, 0.1f, 0, outlineColor);
    }

    Vector2 textSize = MeasureTextEx(font, b->text, fontSize, 2);

    Vector2 textPos = {
        b->rect.x + b->rect.width/2 - textSize.x/2,
        b->rect.y + b->rect.height/2 - textSize.y/2
    };

    if (RAYUI_WITH_PREFIX(ButtonDown)(b)) {
        textPos.x += textPressOffsetRight;
        textPos.y += textPressOffsetDown;
    }

    if (shadowEnabled) {
        Vector2 shadowPos = { textPos.x + textPressOffsetRight, textPos.y + textPressOffsetDown };
        DrawTextEx(font, b->text, shadowPos, fontSize, 2, shadowColor);
    }

    DrawTextEx(font, b->text, textPos, fontSize, 2, textCol);
}


// ---------------- TOGGLE ----------------

RAYUI_WITH_PREFIX(ToggleLabel) RAYUI_WITH_PREFIX(CreateToggle)(float x, float y, float width, float height, bool initial, const char* onLabel, const char* offLabel) {
    RAYUI_WITH_PREFIX(ToggleLabel) t;
    t.rect = (Rectangle){x, y, width, height};
    t.value = initial;
    t.hovered = false;
    t.hover.hoverInfo = NULL;
    t.onLabel = onLabel;
    t.offLabel = offLabel;
    t.hover.hoverStartTime = 0;
    t.hover.hovered = false;
    t.hover.delay = DEFAULT_HOVER_INFO_DELAY;
    t.hover.active = false;
    t.hoverSound = _rayui_DefaultSound;
    t.clickSound = _rayui_DefaultSound;
    return t;
}

RAYUI_WITH_PREFIX(ToggleLabel) RAYUI_WITH_PREFIX(CreateToggleWithSound)(float x, float y, float width, float height, bool initial, const char* onLabel, const char* offLabel, Sound hoverSound, Sound clickSound) {
    RAYUI_WITH_PREFIX(ToggleLabel) t;
    t.rect = (Rectangle){x, y, width, height};
    t.value = initial;
    t.hovered = false;
    t.hover.hoverInfo = NULL;
    t.onLabel = onLabel;
    t.offLabel = offLabel;
    t.hover.hoverStartTime = 0;
    t.hover.hovered = false;
    t.hover.delay = DEFAULT_HOVER_INFO_DELAY;
    t.hover.active = false;
    t.hoverSound = hoverSound;
    t.clickSound = clickSound;
    return t;
}

void RAYUI_WITH_PREFIX(UpdateToggleLabel)(RAYUI_WITH_PREFIX(ToggleLabel)* t, Vector2 mousePoint) {
    t->hovered = CheckCollisionPointRec(mousePoint, t->rect);
    t->hover.hovered = t->hovered;

    if (t->hover.hovered && t->hover.hoverStartTime == 0) {
        t->hover.hoverStartTime = GetTime();
        if (t->hoverSound.frameCount > 0 && t->hover.active) PlaySound(t->hoverSound);
    }

    if (!t->hover.hovered) {
        t->hover.hoverStartTime = 0;
    }

    if (t->hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (t->clickSound.frameCount > 0 && t->hover.active) PlaySound(t->clickSound);
        t->value = !t->value;
    }
}

void RAYUI_WITH_PREFIX(DrawToggleLabel)(RAYUI_WITH_PREFIX(ToggleLabel)* t, Font font, int fontSize, Color color, Color hoverColor, Color backgroundColor) {
    Color col = t->hovered ? hoverColor : color;
    DrawRectangleRec(t->rect, backgroundColor);
    DrawTextEx(font, t->value ? t->onLabel : t->offLabel, (Vector2){t->rect.x + 5, t->rect.y + 5}, fontSize, 2, col);
}

void RAYUI_WITH_PREFIX(DrawToggleLabelEx)(
    RAYUI_WITH_PREFIX(ToggleLabel)* t, Font font, int fontSize,
    Color color, Color hoverColor, Color backgroundColor,
    int outline_width, Color outlineColor
) {
    Color col = t->hovered ? hoverColor : color;

    DrawRectangleRec(t->rect, backgroundColor);

    if (outline_width > 0) {
        
        DrawRectangleLinesEx(t->rect, (float)outline_width, outlineColor);
    }

    const char* text = t->value ? t->onLabel : t->offLabel;
    Vector2 textSize = MeasureTextEx(font, text, fontSize, 2);

    Vector2 textPos = {
        t->rect.x + t->rect.width / 2 - textSize.x / 2,
        t->rect.y + t->rect.height / 2 - textSize.y / 2
    };

    DrawTextEx(font, text, textPos, fontSize, 2, col);
}

bool RAYUI_WITH_PREFIX(GetToggleValue)(RAYUI_WITH_PREFIX(ToggleLabel)* t) {
    return t->value;
}

void RAYUI_WITH_PREFIX(SetToggleValue)(RAYUI_WITH_PREFIX(ToggleLabel)* t, bool value) {
    t->value = value;
}


// ---------------- CHECKBOX ----------------

RAYUI_WITH_PREFIX(Checkbox) RAYUI_WITH_PREFIX(CreateCheckbox)(float x, float y, float size, bool initial) {
    RAYUI_WITH_PREFIX(Checkbox) c;
    c.value = initial;
    c.hovered = false;
    c.hover.hoverInfo = NULL;
    c.hover.hoverStartTime = 0;
    c.hover.hovered = false;
    c.hover.delay = DEFAULT_HOVER_INFO_DELAY;
    c.hover.active = false;
    c.hoverSound = _rayui_DefaultSound;
    c.clickSound = _rayui_DefaultSound;

    c.checkboxOnImage = RAYUI_WITH_PREFIX(GetCheckboxOnTexture)();
    c.checkboxOffImage = RAYUI_WITH_PREFIX(GetCheckboxOffTexture)();

    c.rect = (Rectangle){ x, y, size, size };

    return c;
}

void RAYUI_WITH_PREFIX(UpdateCheckbox)(RAYUI_WITH_PREFIX(Checkbox)* c, Vector2 mousePoint) {
    c->hovered = CheckCollisionPointRec(mousePoint, c->rect);
    c->hover.hovered = c->hovered;

    if (c->hover.hovered && c->hover.hoverStartTime == 0) {
        c->hover.hoverStartTime = GetTime();
        if (c->hoverSound.frameCount > 0 && c->hover.active) PlaySound(c->hoverSound);
    }

    if (!c->hover.hovered) {
        c->hover.hoverStartTime = 0;
    }

    if (c->hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (c->clickSound.frameCount > 0 && c->hover.active) PlaySound(c->clickSound);
        c->value = !c->value;
    }
}

void RAYUI_WITH_PREFIX(DrawCheckboxColors)(RAYUI_WITH_PREFIX(Checkbox)* c, Color onColor, Color offColor) {
    DrawRectangleRec(c->rect, c->value ? onColor : offColor);
}

void RAYUI_WITH_PREFIX(DrawCheckboxColorsEx)(RAYUI_WITH_PREFIX(Checkbox)* c, Color onColor, Color offColor, int outline_width, Color outlineColor) {
    DrawRectangleRec(c->rect, c->value ? onColor : offColor);

    if (outline_width > 0) {
        DrawRectangleLinesEx(c->rect, (float)outline_width, outlineColor);
    }
}

void RAYUI_WITH_PREFIX(DrawCheckbox)(RAYUI_WITH_PREFIX(Checkbox)* c) {
    Texture tex = c->value ? c->checkboxOnImage : c->checkboxOffImage;

    Rectangle src = { 0, 0, (float)tex.width, (float)tex.height };

    Rectangle dest = c->rect;

    DrawTexturePro(tex, src, dest, (Vector2){0, 0}, 0.0f, RAYWHITE);
}

bool RAYUI_WITH_PREFIX(GetCheckboxValue)(RAYUI_WITH_PREFIX(Checkbox)* c) {
    return c->value;
}

void RAYUI_WITH_PREFIX(SetCheckboxValue)(RAYUI_WITH_PREFIX(Checkbox)* c, bool value) {
    c->value = value;
}

void RAYUI_WITH_PREFIX(SetCheckboxTextures)(RAYUI_WITH_PREFIX(Checkbox)* c, Texture onTexture, Texture offTexture) {
    c->checkboxOnImage = onTexture;
    c->checkboxOffImage = offTexture;
}

void RAYUI_WITH_PREFIX(FreeCheckboxTextures)(RAYUI_WITH_PREFIX(Checkbox)* c) {
    UnloadTexture(c->checkboxOnImage);
    UnloadTexture(c->checkboxOffImage);
}

Texture RAYUI_WITH_PREFIX(GetCheckboxOnTexture)(void) {
    if (defaultCheckboxOnTexture.id) return defaultCheckboxOnTexture;

    int size = CHECKBOX_DEFAULT_TEXTURE_SIZE;
    Image img = GenImageColor(size, size, RAYWHITE);
    ImageDrawRectangleLines(&img, (Rectangle){0, 0, size, size}, 1, BLACK);
    ImageDrawLine(&img, 8, 16, 14, 24, DARKGREEN);
    ImageDrawLine(&img, 14, 24, 24, 8, DARKGREEN);

    TraceLog(LOG_INFO, "CHECKBOX: Generating default checkbox ON texture");

    defaultCheckboxOnTexture = LoadTextureFromImage(img);
    UnloadImage(img);
    return defaultCheckboxOnTexture;
}

Texture RAYUI_WITH_PREFIX(GetCheckboxOffTexture)(void) {
    if (defaultCheckboxOffTexture.id) return defaultCheckboxOffTexture;

    int size = CHECKBOX_DEFAULT_TEXTURE_SIZE;
    Image img = GenImageColor(size, size, RAYWHITE);
    ImageDrawRectangleLines(&img, (Rectangle){0, 0, size, size}, 1, BLACK);
    ImageDrawLine(&img, 8, 8, 24, 24, MAROON);
    ImageDrawLine(&img, 24, 8, 8, 24, MAROON);

    TraceLog(LOG_INFO, "CHECKBOX: Generating default checkbox OFF texture");

    defaultCheckboxOffTexture = LoadTextureFromImage(img);
    UnloadImage(img);
    return defaultCheckboxOffTexture;
}

// ---------------- SLIDER ----------------

RAYUI_WITH_PREFIX(Slider) RAYUI_WITH_PREFIX(CreateSlider)(int x, int y, int width, int minVal, int maxVal, float initial) {
    RAYUI_WITH_PREFIX(Slider) s;
    s.bar = (Rectangle){x, y, width, 5};
    s.value = initial;
    s.minVal = minVal;
    s.maxVal = maxVal;
    s.dragging = false;
    s.hover.hoverInfo = NULL;
    s.hover.hoverStartTime = 0;
    s.hover.hovered = false;
    s.hover.delay = DEFAULT_HOVER_INFO_DELAY;
    s.hover.active = false;
    return s;
}

void RAYUI_WITH_PREFIX(UpdateSlider)(RAYUI_WITH_PREFIX(Slider)* s, Vector2 mousePoint) {
    float knobX = s->bar.x + s->value * s->bar.width;
    Rectangle knob = {knobX - 8, s->bar.y - 5, 16, 15};

    if (s->hover.active) {
        s->hover.hovered = CheckCollisionPointRec(mousePoint, s->bar) || 
                        CheckCollisionPointRec(mousePoint, knob);

        if (s->hover.hovered && s->hover.hoverStartTime == 0) s->hover.hoverStartTime = GetTime();
        if (!s->hover.hovered) s->hover.hoverStartTime = 0;
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePoint, knob))
        s->dragging = true;

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        s->dragging = false;

    if (s->dragging) {
        float ratio = (mousePoint.x - s->bar.x) / s->bar.width;
        if (ratio < 0) ratio = 0;
        if (ratio > 1) ratio = 1;
        s->value = ratio;
    }
}

int RAYUI_WITH_PREFIX(SliderValue)(RAYUI_WITH_PREFIX(Slider)* s) {
    return (int)(s->minVal + s->value * (s->maxVal - s->minVal));
}

void RAYUI_WITH_PREFIX(DrawSlider)(RAYUI_WITH_PREFIX(Slider)* s, Color color, Color knobColor) {
    DrawRectangleRec(s->bar, color);
    float knobX = s->bar.x + s->value * s->bar.width;
    DrawRectangle(knobX - 8, s->bar.y - 5, 16, 15, knobColor);
}

// ---------------- OPTION SLIDER ----------------

RAYUI_WITH_PREFIX(OptionSlider) RAYUI_WITH_PREFIX(CreateOptionSlider)(int x, int y, int width, const char** options, int optionCount, int initialIndex) {
    RAYUI_WITH_PREFIX(OptionSlider) s;
    s.bar = (Rectangle){x, y, width, 5};
    s.options = options;
    s.optionCount = optionCount;
    s.selectedIndex = initialIndex;
    s.dragging = false;
    s.hover.hoverInfo = NULL;
    s.hover.hoverStartTime = 0;
    s.hover.hovered = false;
    s.hover.delay = DEFAULT_HOVER_INFO_DELAY;
    s.hover.active = false;
    return s;
}

void RAYUI_WITH_PREFIX(UpdateOptionSlider)(RAYUI_WITH_PREFIX(OptionSlider)* s, Vector2 mousePoint) {
    float knobX = s->bar.x + ((float)s->selectedIndex / (s->optionCount - 1)) * s->bar.width;
    Rectangle knob = {knobX - 8, s->bar.y - 5, 16, 15};

    if (s->hover.active) {
        s->hover.hovered = CheckCollisionPointRec(mousePoint, s->bar) || 
                        CheckCollisionPointRec(mousePoint, knob);

        if (s->hover.hovered && s->hover.hoverStartTime == 0) s->hover.hoverStartTime = GetTime();
        if (!s->hover.hovered) s->hover.hoverStartTime = 0;
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePoint, knob))
        s->dragging = true;

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        s->dragging = false;

    if (s->dragging) {
        float ratio = (mousePoint.x - s->bar.x) / s->bar.width;
        if (ratio < 0) ratio = 0;
        if (ratio > 1) ratio = 1;
        s->selectedIndex = (int)(ratio * (s->optionCount - 1) + 0.5f);
    }
}

const char* RAYUI_WITH_PREFIX(OptionSliderValue)(RAYUI_WITH_PREFIX(OptionSlider)* s) {
    if (s->selectedIndex < 0 || s->selectedIndex >= s->optionCount) return s->options[0];
    return s->options[s->selectedIndex];
}

void RAYUI_WITH_PREFIX(DrawOptionSlider)(RAYUI_WITH_PREFIX(OptionSlider)* s, Color color, Color knobColor) {
    DrawRectangleRec(s->bar, color);
    float knobX = s->bar.x + ((float)s->selectedIndex / (s->optionCount - 1)) * s->bar.width;
    DrawRectangle(knobX - 8, s->bar.y - 5, 16, 15, knobColor);
}

// ---------------- KEYBIND INPUT ----------------

RAYUI_WITH_PREFIX(KeybindInput) RAYUI_WITH_PREFIX(CreateKeybindInput)(float x, float y, float width, float height, int initialKey, Sound hoverSound, Sound clickSound) {
    RAYUI_WITH_PREFIX(KeybindInput) k;
    k.rect = (Rectangle){x, y, width, height};
    k.key = initialKey;
    k.listening = false;
    k.hovered = false;
    k.hoverSound = hoverSound;
    k.clickSound = clickSound;
    k.hover.hoverInfo = NULL;
    k.hover.hoverStartTime = 0;
    k.hover.hovered = false;
    k.hover.delay = DEFAULT_HOVER_INFO_DELAY;
    k.hover.active = false;
    return k;
}

bool RAYUI_WITH_PREFIX(UpdateKeybindInput)(RAYUI_WITH_PREFIX(KeybindInput)* k, Vector2 mousePoint) {
    k->hovered = CheckCollisionPointRec(mousePoint, k->rect);
    k->hover.hovered = k->hovered;

    if (k->hover.hovered && k->hover.hoverStartTime == 0 && k->hover.active) {
        k->hover.hoverStartTime = GetTime();
        if (k->hoverSound.frameCount > 0) PlaySound(k->hoverSound);
    }

    if (!k->hover.hovered)
        k->hover.hoverStartTime = 0;

    if (k->hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (k->clickSound.frameCount > 0 && k->hover.active) PlaySound(k->clickSound);
        k->listening = true;
        return false;
    }

    if (k->listening) {
        int pressed = GetKeyPressed();
        if (pressed != 0) {
            k->key = pressed;
            k->listening = false;
            return true;
        }
        if (IsKeyPressed(KEY_ESCAPE) || IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
            k->listening = false;
        }
    }

    return false;
}

void RAYUI_WITH_PREFIX(DrawKeybindInput)(RAYUI_WITH_PREFIX(KeybindInput)* k, Font font, int fontSize, Color bgColor, Color textColor, Color textHoverColor) {
    Color bg = bgColor;
    Color textColorI = (k->hovered || k->listening) ? textHoverColor : textColor;
    DrawRectangleRec(k->rect, bg);

    static char buffer[32];
    const char* text;
    if (k->listening) {
        snprintf(buffer, sizeof(buffer), "| %s |", GetKeyName(k->key));
        text = buffer;
    } else {
        text = GetKeyName(k->key);
    }

    Vector2 textSize = MeasureTextEx(font, text, fontSize, 1);
    Vector2 pos = { k->rect.x + (k->rect.width - textSize.x)/2,
                    k->rect.y + (k->rect.height - textSize.y)/2 };
    DrawTextEx(font, text, pos, fontSize, 1, textColorI);
}

KeyboardKey RAYUI_WITH_PREFIX(GetKeybindValue)(RAYUI_WITH_PREFIX(KeybindInput)* k) {
    return k->key;
}

// ---------------- TEXT INPUT ----------------

RAYUI_WITH_PREFIX(TextInput) RAYUI_WITH_PREFIX(CreateTextInput)(int x, int y, int width, int height, const char* initial, RAYUI_WITH_PREFIX(InputType) type) {
    RAYUI_WITH_PREFIX(TextInput) t;
    t.rect = (Rectangle){x, y, width, height};
    t.focused = false;
    t.cleared = false;
    t.hovered = false;
    t.hoverSound = _rayui_DefaultSound;
    t.clickSound = _rayui_DefaultSound;
    t.inputType = type;
    t.hover.hoverInfo = NULL;
    t.hover.hoverStartTime = 0;
    t.hover.hovered = false;
    t.hover.delay = DEFAULT_HOVER_INFO_DELAY;
    t.hover.active = false;
    t.backspaceTimer = 0;
    t.backspacePressed = false;
    t.backspaceHoldTime = 0;
    strncpy(t.text, initial, sizeof(t.text));
    t.text[sizeof(t.text)-1] = '\0';
    return t;
}

RAYUI_WITH_PREFIX(TextInput) RAYUI_WITH_PREFIX(CreateTextInputWithSound)(int x, int y, int width, int height, const char* initial, RAYUI_WITH_PREFIX(InputType) type, Sound hoverSound, Sound clickSound) {
    RAYUI_WITH_PREFIX(TextInput) t;
    t.rect = (Rectangle){x, y, width, height};
    t.focused = false;
    t.cleared = false;
    t.hovered = false;
    t.hoverSound = hoverSound;
    t.clickSound = clickSound;
    t.inputType = type;
    t.hover.hoverInfo = NULL;
    t.hover.hoverStartTime = 0;
    t.hover.hovered = false;
    t.hover.delay = DEFAULT_HOVER_INFO_DELAY;
    t.hover.active = false;
    t.backspaceTimer = 0;
    t.backspacePressed = false;
    t.backspaceHoldTime = 0;
    strncpy(t.text, initial, sizeof(t.text));
    t.text[sizeof(t.text)-1] = '\0';
    return t;
}

void RAYUI_WITH_PREFIX(UpdateTextInput)(RAYUI_WITH_PREFIX(TextInput)* t) {
    RAYUI_WITH_PREFIX(UpdateTextInputWithMousePoint)(t, GetMousePosition());
}

void RAYUI_WITH_PREFIX(UpdateTextInputWithMousePoint)(RAYUI_WITH_PREFIX(TextInput)* t, Vector2 mousePoint) {
    t->hovered = CheckCollisionPointRec(mousePoint, t->rect);
    t->hover.hovered = t->hovered;

    if (t->hover.hovered && t->hover.hoverStartTime == 0 && t->hover.active) {
        t->hover.hoverStartTime = GetTime();
        if (t->hoverSound.frameCount > 0) PlaySound(t->hoverSound);
    }

    if (!t->hover.hovered)
        t->hover.hoverStartTime = 0;

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        t->focused = t->hovered;
        if (t->focused) {
            t->cleared = false;
            if (t->clickSound.frameCount > 0 && t->hover.active) PlaySound(t->clickSound);
        }
    }

    if (t->focused) {
        int key;
        while ((key = GetCharPressed()) > 0) {
            int len = strlen(t->text);
            if (!t->cleared) { t->text[0] = '\0'; t->cleared = true; len = 0; }

            if ((t->inputType == INPUT_TYPE_INT && (key < '0' || key > '9')) ||
                (t->inputType == INPUT_TYPE_FLOAT && (key < '0' || key > '9') && key != '.')) continue;

            if (len < sizeof(t->text)-1) { t->text[len] = (char)key; t->text[len+1] = '\0'; }
        }

        const float initialHoldThreshold = 0.3f;
        const float backspaceCooldown = 0.02f;
        float currentTime = GetTime();

        if (IsKeyDown(KEY_BACKSPACE)) {
            if (!t->backspacePressed) {
                int len = strlen(t->text);
                if (len > 0) t->text[len-1] = '\0';
                t->backspacePressed = true;
                t->backspaceHoldTime = currentTime;
                t->backspaceTimer = currentTime;
            } else {
                float heldTime = currentTime - t->backspaceHoldTime;
                if (heldTime > initialHoldThreshold) {
                    if (currentTime - t->backspaceTimer >= backspaceCooldown) {
                        int len = strlen(t->text);
                        if (len > 0) t->text[len-1] = '\0';
                        t->backspaceTimer = currentTime;
                    }
                }
            }
        } else {
            t->backspacePressed = false;
            t->backspaceHoldTime = 0;
            t->backspaceTimer = 0;
        }
    }
}

void RAYUI_WITH_PREFIX(DrawTextInput)(RAYUI_WITH_PREFIX(TextInput)* t, Font font, int fontSize, Color bgColor, Color textColor, Color textHoverColor) {
    Color textColorI = (t->hovered || t->focused) ? textHoverColor : textColor;
    DrawRectangleRec(t->rect, bgColor);

    static double lastTime = 0;
    static bool showCursor = false;
    double currentTime = GetTime();
    if (currentTime - lastTime >= 0.5) { showCursor = !showCursor; lastTime = currentTime; }

    char buffer[256];
    strncpy(buffer, t->text, sizeof(buffer)-2);
    buffer[sizeof(buffer)-2] = '\0';

    if (t->inputType == INPUT_TYPE_PASSWORD) {
        for (int i = 0; i < (int)strlen(buffer); i++) buffer[i] = '*';
    }

    if (t->focused && showCursor) {
        int len = strlen(buffer);
        buffer[len] = '_';
        buffer[len+1] = '\0';
    }

    Vector2 pos = { t->rect.x + 8, t->rect.y + (t->rect.height - fontSize)/2 };
    DrawTextEx(font, buffer, pos, fontSize, 1, textColorI);
}

const char* RAYUI_WITH_PREFIX(TextInputValue)(RAYUI_WITH_PREFIX(TextInput)* t) {
    return t->text;
}

void RAYUI_WITH_PREFIX(SetTextInputValue)(RAYUI_WITH_PREFIX(TextInput)* t, const char* value) {
    strncpy(t->text, value, sizeof(t->text));
    t->text[sizeof(t->text)-1] = '\0';
}

// --------------- PROGRESS BAR ----------------
RAYUI_WITH_PREFIX(ProgressBar) RAYUI_WITH_PREFIX(CreateProgressBar)(int x, int y, int width, int height, float initialValue) {
    RAYUI_WITH_PREFIX(ProgressBar) p;
    p.bar = (Rectangle){x, y, width, height};
    p.progress = (initialValue < 0) ? 0 : (initialValue > 1) ? 1 : initialValue;
    p.hover.hoverInfo = NULL;
    p.hover.hoverStartTime = 0;
    p.hover.hovered = false;
    p.hover.delay = DEFAULT_HOVER_INFO_DELAY;
    p.hover.active = false;
    return p;
}

void RAYUI_WITH_PREFIX(DrawProgressBar)(RAYUI_WITH_PREFIX(ProgressBar)* p, Color backColor, Color fillColor) {
    DrawRectangleRec(p->bar, backColor);
    DrawRectangleRec((Rectangle){p->bar.x, p->bar.y, p->bar.width * p->progress, p->bar.height}, fillColor);
}

void RAYUI_WITH_PREFIX(DrawProgressBarEx)(RAYUI_WITH_PREFIX(ProgressBar)* p, Color backColor, Color fillColor, int outlineWidth, Color outlineColor) {
    DrawRectangleRec(p->bar, backColor);
    DrawRectangleRec((Rectangle){p->bar.x, p->bar.y, p->bar.width * p->progress, p->bar.height}, fillColor);
    DrawRectangleLinesEx(p->bar, outlineWidth, outlineColor);
}

void RAYUI_WITH_PREFIX(UpdateProgressBar)(RAYUI_WITH_PREFIX(ProgressBar)* p) {
    if (p->hover.active) {
        p->hover.hovered = CheckCollisionPointRec(GetMousePosition(), p->bar);

        if (p->hover.hovered && p->hover.hoverStartTime == 0) p->hover.hoverStartTime = GetTime();
        if (!p->hover.hovered) p->hover.hoverStartTime = 0;
    }
}

void RAYUI_WITH_PREFIX(SetProgressBarValue)(RAYUI_WITH_PREFIX(ProgressBar)* p, float value) {
    if (value < 0) value = 0;
    if (value > 1) value = 1;
    p->progress = value;
}

void RAYUI_WITH_PREFIX(UpdateProgressBarValue)(RAYUI_WITH_PREFIX(ProgressBar)* p, float delta) {
    p->progress += delta;
    if (p->progress < 0) p->progress = 0;
    if (p->progress > 1) p->progress = 1;
}

float RAYUI_WITH_PREFIX(GetProgressBarValue)(RAYUI_WITH_PREFIX(ProgressBar)* p) {
    return p->progress;
}

bool RAYUI_WITH_PREFIX(IsProgressBarFull)(RAYUI_WITH_PREFIX(ProgressBar)* p) {
    return p->progress >= 1.0f;
}

bool RAYUI_WITH_PREFIX(IsProgressBarEmpty)(RAYUI_WITH_PREFIX(ProgressBar)* p) {
    return p->progress <= 0.0f;
}

// ---------------- DROPDOWN ----------------

RAYUI_WITH_PREFIX(Dropdown) RAYUI_WITH_PREFIX(CreateDropdown)(float x, float y, float width, float height, const char** options, int optionCount, int initialIndex) {
    RAYUI_WITH_PREFIX(Dropdown) d;
    d.rect = (Rectangle){x, y, width, height};
    d.options = options;
    d.optionCount = optionCount;
    d.selectedIndex = initialIndex;
    d.expanded = false;
    d.hovered = false;
    d.hoverSound = _rayui_DefaultSound;
    d.clickSound = _rayui_DefaultSound;
    d.hover.hoverInfo = NULL;
    d.hover.hoverStartTime = 0;
    d.hover.hovered = false;
    d.hover.delay = DEFAULT_HOVER_INFO_DELAY;
    d.hover.active = false;
    return d;
}

RAYUI_WITH_PREFIX(Dropdown) RAYUI_WITH_PREFIX(CreateDropdownWithSound)(float x, float y, float width, float height, const char** options, int optionCount, int initialIndex, Sound hoverSound, Sound clickSound) {
    RAYUI_WITH_PREFIX(Dropdown) d;
    d.rect = (Rectangle){x, y, width, height};
    d.options = options;
    d.optionCount = optionCount;
    d.selectedIndex = initialIndex;
    d.expanded = false;
    d.hovered = false;
    d.hoverSound = hoverSound;
    d.clickSound = clickSound;
    d.hover.hoverInfo = NULL;
    d.hover.hoverStartTime = 0;
    d.hover.hovered = false;
    d.hover.delay = DEFAULT_HOVER_INFO_DELAY;
    d.hover.active = false;
    return d;
}

bool RAYUI_WITH_PREFIX(UpdateDropdown)(RAYUI_WITH_PREFIX(Dropdown)* d) {
    d->hovered = CheckCollisionPointRec(GetMousePosition(), d->rect);
    d->hover.hovered = d->hovered;

    if (d->hover.hovered && d->hover.hoverStartTime == 0 && d->hover.active) {
        d->hover.hoverStartTime = GetTime();
        if (d->hoverSound.frameCount > 0) PlaySound(d->hoverSound);
    }

    if (!d->hover.hovered)
        d->hover.hoverStartTime = 0;

    if (d->hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (d->clickSound.frameCount > 0 && d->hover.active) PlaySound(d->clickSound);
        d->expanded = !d->expanded;
        return false;
    }

    if (d->expanded) {
        for (int i = 0; i < d->optionCount; i++) {
            Rectangle optionRect = {d->rect.x, d->rect.y + d->rect.height * (i + 1), d->rect.width, d->rect.height};
            if (CheckCollisionPointRec(GetMousePosition(), optionRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                d->selectedIndex = i;
                d->expanded = false;
                if (d->clickSound.frameCount > 0 && d->hover.active) PlaySound(d->clickSound);
                return true;
            }
        }
    }

    return false;
}

bool RAYUI_WITH_PREFIX(UpdateDropdownWithMousePoint)(RAYUI_WITH_PREFIX(Dropdown)* d, Vector2 mousePoint) {
    d->hovered = CheckCollisionPointRec(mousePoint, d->rect);
    d->hover.hovered = d->hovered;

    if (d->hover.hovered && d->hover.hoverStartTime == 0 && d->hover.active) {
        d->hover.hoverStartTime = GetTime();
        if (d->hoverSound.frameCount > 0) PlaySound(d->hoverSound);
    }

    if (!d->hover.hovered)
        d->hover.hoverStartTime = 0;

    if (d->hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (d->clickSound.frameCount > 0 && d->hover.active) PlaySound(d->clickSound);
        d->expanded = !d->expanded;
        return false;
    }

    if (d->expanded) {
        for (int i = 0; i < d->optionCount; i++) {
            Rectangle optionRect = {d->rect.x, d->rect.y + d->rect.height * (i + 1), d->rect.width, d->rect.height};
            if (CheckCollisionPointRec(mousePoint, optionRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                d->selectedIndex = i;
                d->expanded = false;
                if (d->clickSound.frameCount > 0 && d->hover.active) PlaySound(d->clickSound);
                return true;
            }
        }
    }

    return false;
}

void RAYUI_WITH_PREFIX(DrawDropdown)(RAYUI_WITH_PREFIX(Dropdown)* d, Font font, int fontSize, Color bgColor, Color textColor, Color hoverColor, Color optionBgColor, Color optionHoverColor) {
    Color textCol = (d->hovered) ? hoverColor : textColor;
    DrawRectangleRec(d->rect, bgColor);

    const char* selectedText = (d->selectedIndex >= 0 && d->selectedIndex < d->optionCount) ? d->options[d->selectedIndex] : "Select";
    Vector2 textSize = MeasureTextEx(font, selectedText, fontSize, 1);
    Vector2 pos = { d->rect.x + 8, d->rect.y + (d->rect.height - textSize.y)/2 };
    DrawTextEx(font, selectedText, pos, fontSize, 1, textCol);

    if (d->expanded) {
        for (int i = 0; i < d->optionCount; i++) {
            Rectangle optionRect = {d->rect.x, d->rect.y + d->rect.height * (i + 1), d->rect.width, d->rect.height};
            Color optionBg = CheckCollisionPointRec(GetMousePosition(), optionRect) ? optionHoverColor : optionBgColor;
            DrawRectangleRec(optionRect, optionBg);

            const char* optionText = d->options[i];
            Vector2 optTextSize = MeasureTextEx(font, optionText, fontSize, 1);
            Vector2 optPos = { optionRect.x + 8, optionRect.y + (optionRect.height - optTextSize.y)/2 };
            DrawTextEx(font, optionText, optPos, fontSize, 1, textColor);
        }
    }
}

void RAYUI_WITH_PREFIX(DrawDropdownEx)(RAYUI_WITH_PREFIX(Dropdown)* d, Font font, int fontSize,
                                       Color bgColor, Color textColor, Color hoverColor,
                                       Color optionBgColor, Color optionHoverColor,
                                       int outlineWidth, Color outlineColor, const char* placeholderText)
{
    Color textCol = (d->hovered) ? hoverColor : textColor;

    DrawRectangleRec(d->rect, bgColor);

    const char* selectedText = (d->selectedIndex >= 0 && d->selectedIndex < d->optionCount) ? d->options[d->selectedIndex] : placeholderText;
    Vector2 textSize = MeasureTextEx(font, selectedText, fontSize, 1);
    Vector2 pos = { d->rect.x + 8, d->rect.y + (d->rect.height - textSize.y)/2 };
    DrawTextEx(font, selectedText, pos, fontSize, 1, textCol);

    if (d->expanded) {
        for (int i = 0; i < d->optionCount; i++) {
            Rectangle optionRect = { d->rect.x, d->rect.y + d->rect.height * (i + 1), d->rect.width, d->rect.height };
            Color optionBg = CheckCollisionPointRec(GetMousePosition(), optionRect) ? optionHoverColor : optionBgColor;
            DrawRectangleRec(optionRect, optionBg);

            const char* optionText = d->options[i];
            Vector2 optTextSize = MeasureTextEx(font, optionText, fontSize, 1);
            Vector2 optPos = { optionRect.x + 8, optionRect.y + (optionRect.height - optTextSize.y)/2 };
            DrawTextEx(font, optionText, optPos, fontSize, 1, textColor);

            if (outlineWidth > 0) {
                Rectangle divider = { d->rect.x, optionRect.y, d->rect.width, (float)outlineWidth };
                DrawRectangleRec(divider, outlineColor);
            }
        }

        if (outlineWidth > 0) {
            Rectangle divider = { d->rect.x, d->rect.y + d->rect.height, d->rect.width, (float)outlineWidth };
            DrawRectangleRec(divider, outlineColor);
        }
    }

    if (outlineWidth > 0) {
        float totalHeight = d->rect.height + (d->expanded ? d->rect.height * d->optionCount : 0);
        Rectangle totalRect = { d->rect.x, d->rect.y, d->rect.width, totalHeight };
        DrawRectangleLinesEx(totalRect, outlineWidth, outlineColor);
    }
}

const char* RAYUI_WITH_PREFIX(DropdownValue)(RAYUI_WITH_PREFIX(Dropdown)* d) {
    if (d->selectedIndex < 0 || d->selectedIndex >= d->optionCount) return NULL;
    return d->options[d->selectedIndex];
}

void RAYUI_WITH_PREFIX(SetDropdownValue)(RAYUI_WITH_PREFIX(Dropdown)* d, int index) {
    if (index < 0 || index >= d->optionCount) return;
    d->selectedIndex = index;
}

int RAYUI_WITH_PREFIX(GetDropdownIndex)(RAYUI_WITH_PREFIX(Dropdown)* d) {
    return d->selectedIndex;
}

void RAYUI_WITH_PREFIX(SetDropdownIndex)(RAYUI_WITH_PREFIX(Dropdown)* d, int index) {
    if (index < 0 || index >= d->optionCount) return;
    d->selectedIndex = index;
}

// ---------------- COLOR PICKER ----------------

RAYUI_WITH_PREFIX(ColorPicker) RAYUI_WITH_PREFIX(CreateColorPicker)(float x, float y, float size, Color initialColor, RAYUI_WITH_PREFIX(ColorPickerMode) mode) {
    RAYUI_WITH_PREFIX(ColorPicker) cp;
    cp.rect = (Rectangle){x, y, size, size};
    cp.selectedColor = initialColor;
    cp.mode = mode;
    cp.hovered = false;
    cp.hover.hoverInfo = NULL;
    cp.hover.hoverStartTime = 0;
    cp.hover.hovered = false;
    cp.hover.delay = DEFAULT_HOVER_INFO_DELAY;
    cp.hover.active = false;
    cp.hoverSound = _rayui_DefaultSound;
    cp.clickSound = _rayui_DefaultSound;
    cp.expanded = true;
    cp.showAlpha = (mode == COLOR_PICKER_MODE_RGBA || mode == COLOR_PICKER_MODE_HSVA);
    cp.draggingAlpha = false;
    cp.draggingColor = false;

    // HSV selector
    if (mode == COLOR_PICKER_MODE_HSV || mode == COLOR_PICKER_MODE_HSVA) {
        Vector3 hsv = ColorToHSV(initialColor);
        cp.selectorPos = (Vector2){hsv.x / 360.0f, hsv.y};
    } else {
        cp.selectorPos = (Vector2){0, 0};
    }

    // RGB sliders
    float sliderWidth = 12;
    float sliderSpacing = 2;
    if (mode == COLOR_PICKER_MODE_RGB || mode == COLOR_PICKER_MODE_RGBA) {
        cp.sliderR = (Rectangle){x, y, sliderWidth, size};
        cp.sliderG = (Rectangle){x + sliderWidth + sliderSpacing, y, sliderWidth, size};
        cp.sliderB = (Rectangle){x + 2*(sliderWidth + sliderSpacing), y, sliderWidth, size};
    }

    // Alpha slider
    if (cp.showAlpha) {
        if (mode == COLOR_PICKER_MODE_RGBA) {
            cp.alphaRect = (Rectangle){x + 3*(sliderWidth + sliderSpacing) + sliderSpacing, y, sliderWidth, size};
        } else {
            cp.alphaRect = (Rectangle){x + size + 4, y, 12, size};
        }
    }

    cp.draggingSliderR = false;
    cp.draggingSliderG = false;
    cp.draggingSliderB = false;

    return cp;
}

RAYUI_WITH_PREFIX(ColorPicker) RAYUI_WITH_PREFIX(CreateColorPickerWithSound)(float x, float y, float size, Color initialColor, RAYUI_WITH_PREFIX(ColorPickerMode) mode, Sound hoverSound, Sound clickSound) {
    RAYUI_WITH_PREFIX(ColorPicker) cp = RAYUI_WITH_PREFIX(CreateColorPicker)(x, y, size, initialColor, mode);
    cp.hoverSound = hoverSound;
    cp.clickSound = clickSound;
    return cp;
}

void RAYUI_WITH_PREFIX(UpdateColorPicker)(RAYUI_WITH_PREFIX(ColorPicker)* cp) {
    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && CheckCollisionPointRec(mouse, cp->rect))
        cp->expanded = !cp->expanded;
    if (!cp->expanded) return;

    cp->hovered = CheckCollisionPointRec(mouse, cp->rect);
    cp->hover.hovered = cp->hovered;

    // Reset dragging flags only when mouse released
    if (!IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        cp->draggingAlpha = false;
        cp->draggingColor = false;
        cp->draggingSliderR = false;
        cp->draggingSliderG = false;
        cp->draggingSliderB = false;
    }

    // Priority: if already dragging something, continue dragging it
    if (cp->draggingColor) {
        // HSV square or RGB sliders
        if (cp->mode == COLOR_PICKER_MODE_HSV || cp->mode == COLOR_PICKER_MODE_HSVA) {
            float rx = Clamp((mouse.x - cp->rect.x) / cp->rect.width, 0.0f, 1.0f);
            float ry = Clamp((mouse.y - cp->rect.y) / cp->rect.height, 0.0f, 1.0f);
            cp->selectorPos = (Vector2){rx, ry};
            float h = rx * 360.0f;
            float s = ry;
            Color c = ColorFromHSV(h, s, 1.0f);
            if (cp->mode == COLOR_PICKER_MODE_HSVA) c.a = cp->selectedColor.a;
            cp->selectedColor = c;
        } else {
            struct {Rectangle* r; bool* dragging; unsigned char* channel;} sliders[3] = {
                {&cp->sliderR, &cp->draggingSliderR, &cp->selectedColor.r},
                {&cp->sliderG, &cp->draggingSliderG, &cp->selectedColor.g},
                {&cp->sliderB, &cp->draggingSliderB, &cp->selectedColor.b},
            };
            for (int i = 0; i < 3; i++) {
                if (*sliders[i].dragging) {
                    float rel = Clamp((mouse.y - sliders[i].r->y) / sliders[i].r->height, 0.0f, 1.0f);
                    *sliders[i].channel = (unsigned char)(rel * 255);
                }
            }
        }
        return; // do not allow alpha while dragging color
    }

    if (cp->draggingAlpha) {
        float rel = Clamp((mouse.y - cp->alphaRect.y) / cp->alphaRect.height, 0.0f, 1.0f);
        cp->selectedColor.a = (unsigned char)(rel * 255);
        return; // do not allow color while dragging alpha
    }

    // Start dragging: check which area the mouse pressed first
    if (cp->mode == COLOR_PICKER_MODE_HSV || cp->mode == COLOR_PICKER_MODE_HSVA) {
        if (CheckCollisionPointRec(mouse, cp->rect) && IsMouseButtonDown(MOUSE_LEFT_BUTTON))
            cp->draggingColor = true;
    } else {
        struct {Rectangle* r; bool* dragging;} sliders[3] = {
            {&cp->sliderR, &cp->draggingSliderR},
            {&cp->sliderG, &cp->draggingSliderG},
            {&cp->sliderB, &cp->draggingSliderB},
        };
        for (int i = 0; i < 3; i++) {
            if (CheckCollisionPointRec(mouse, *sliders[i].r) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                *sliders[i].dragging = true;
                cp->draggingColor = true;
            }
        }
    }

    if (cp->showAlpha && CheckCollisionPointRec(mouse, cp->alphaRect) && IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        cp->draggingAlpha = true;
}

void RAYUI_WITH_PREFIX(DrawColorPicker)(RAYUI_WITH_PREFIX(ColorPicker)* cp) {
    RAYUI_WITH_PREFIX(DrawColorPickerEx)(cp, 1, GRAY, WHITE);
}

void RAYUI_WITH_PREFIX(DrawColorPickerEx)(RAYUI_WITH_PREFIX(ColorPicker)* cp,
                                          int outlineWidth,
                                          Color outlineColor,
                                          Color thumbColor) {
    if (!cp->expanded) {
        DrawRectangleRec(cp->rect, cp->selectedColor);
        DrawTriangle((Vector2){cp->rect.x + cp->rect.width / 2 - 4, cp->rect.y + cp->rect.height / 2 - 2},
                     (Vector2){cp->rect.x + cp->rect.width / 2 + 4, cp->rect.y + cp->rect.height / 2 - 2},
                     (Vector2){cp->rect.x + cp->rect.width / 2, cp->rect.y + cp->rect.height / 2 + 4},
                     DARKGRAY);
        return;
    }

    if (cp->mode == COLOR_PICKER_MODE_HSV || cp->mode == COLOR_PICKER_MODE_HSVA) {
        for (int y = 0; y < (int)cp->rect.height; y++)
            for (int x = 0; x < (int)cp->rect.width; x++)
                DrawPixel((int)(cp->rect.x + x), (int)(cp->rect.y + y), ColorFromHSV((float)x / cp->rect.width * 360.0f, (float)y / cp->rect.height, 1.0f));

        if (outlineWidth > 0)
            DrawRectangleLinesEx(cp->rect, outlineWidth, outlineColor);

        float dotX = cp->rect.x + cp->selectorPos.x * cp->rect.width;
        float dotY = cp->rect.y + cp->selectorPos.y * cp->rect.height;
        DrawCircle((int)dotX, (int)dotY, 4, BLACK);
        DrawCircleLines((int)dotX, (int)dotY, 4, thumbColor);

    } else {
        struct {Rectangle* r; unsigned char val; Color color;} sliders[3] = {
            {&cp->sliderR, cp->selectedColor.r, RED},
            {&cp->sliderG, cp->selectedColor.g, GREEN},
            {&cp->sliderB, cp->selectedColor.b, BLUE},
        };
        for (int i = 0; i < 3; i++) {
            Rectangle rect = *sliders[i].r;
            for (int y = 0; y < (int)rect.height; y++) {
                float t = (float)y / rect.height;
                unsigned char v = (unsigned char)(t * 255);
                Color c = sliders[i].color;
                c.r = (i==0)? v : 0;
                c.g = (i==1)? v : 0;
                c.b = (i==2)? v : 0;
                DrawRectangle((int)rect.x, (int)(rect.y + y), (int)rect.width, 1, c);
            }

            if (outlineWidth > 0)
                DrawRectangleLinesEx(rect, outlineWidth, outlineColor);

            float thumbY = rect.y + ((float)sliders[i].val / 255.0f) * rect.height;
            DrawRectangle((int)rect.x - 1, (int)thumbY - 2, (int)rect.width + 2, 4, thumbColor);
        }
    }

    if (cp->showAlpha) {
        for (int y = 0; y < (int)cp->alphaRect.height; y++) {
            float t = (float)y / cp->alphaRect.height;
            Color c = cp->selectedColor;
            c.a = (unsigned char)(t * 255);
            DrawRectangle((int)cp->alphaRect.x, (int)(cp->alphaRect.y + y), (int)cp->alphaRect.width, 1, Fade(c, t));
        }

        if (outlineWidth > 0)
            DrawRectangleLinesEx(cp->alphaRect, outlineWidth, outlineColor);

        float thumbY = cp->alphaRect.y + ((float)cp->selectedColor.a / 255.0f) * cp->alphaRect.height;
        DrawRectangle((int)cp->alphaRect.x - 1, (int)thumbY - 2, (int)cp->alphaRect.width + 2, 4, thumbColor);
    }
}

Color RAYUI_WITH_PREFIX(GetColorPickerValue)(RAYUI_WITH_PREFIX(ColorPicker)* cp) {
    return cp->selectedColor;
}

void RAYUI_WITH_PREFIX(SetColorPickerValue)(RAYUI_WITH_PREFIX(ColorPicker)* cp, Color color) {
    cp->selectedColor = color;
}

// ---------------- NUMERIC INPUT ----------------

RAYUI_WITH_PREFIX(NumericInput) RAYUI_WITH_PREFIX(CreateNumericInput)(
    float x, float y, float width, float height, float initialValue,
    float minValue, float maxValue, float step, int decimalPlaces) {
    RAYUI_WITH_PREFIX(NumericInput) n;

    n.rect = (Rectangle){x, y, width, height};
    n.value = initialValue;
    n.minValue = minValue;
    n.maxValue = maxValue;
    n.decimalPlaces = decimalPlaces;
    n.step = step;
    n.hoveredUp = false;
    n.hoveredDown = false;
    n.hoverSound = _rayui_DefaultSound;
    n.clickSound = _rayui_DefaultSound;
    n.hover.hoverInfo = NULL;
    n.hover.hoverStartTime = 0;
    n.hover.hovered = false;
    n.hover.delay = DEFAULT_HOVER_INFO_DELAY;
    n.hover.active = false;

    float triHeight = height / 6.0f;
    float triWidth = width / 5.0f;

    n.upTriangle = (Triangle){
        {x + width / 2, y + 2},
        {x + width / 2 - triWidth, y + triHeight},
        {x + width / 2 + triWidth, y + triHeight}
    };

    n.downTriangle = (Triangle){
        {x + width / 2 + triWidth, y + height - 2 - triHeight},
        {x + width / 2 - triWidth, y + height - 2 - triHeight},
        {x + width / 2, y + height - 2}
    };


    return n;
}

RAYUI_WITH_PREFIX(NumericInput) RAYUI_WITH_PREFIX(CreateNumericInputWithSound)(float x, float y, float width, float height, float initialValue, float minValue, float maxValue, float step, int decimalPlaces, Sound hoverSound, Sound clickSound) {
    RAYUI_WITH_PREFIX(NumericInput) n = RAYUI_WITH_PREFIX(CreateNumericInput)(x, y, width, height, initialValue, minValue, maxValue, step, decimalPlaces);
    n.hoverSound = hoverSound;
    n.clickSound = clickSound;
    return n;
}

void RAYUI_WITH_PREFIX(UpdateNumericInput)(RAYUI_WITH_PREFIX(NumericInput)* n) {
    Vector2 mouse = GetMousePosition();

    bool prevHoveredUp = n->hoveredUp;
    bool prevHoveredDown = n->hoveredDown;

    n->hoveredUp   = CheckCollisionPointTriangle(mouse, n->upTriangle.a, n->upTriangle.b, n->upTriangle.c);
    n->hoveredDown = CheckCollisionPointTriangle(mouse, n->downTriangle.a, n->downTriangle.b, n->downTriangle.c);

    // Hover sound
    if (n->hoveredUp && !prevHoveredUp && n->hoverSound.frameCount > 0) PlaySound(n->hoverSound);
    if (n->hoveredDown && !prevHoveredDown && n->hoverSound.frameCount > 0) PlaySound(n->hoverSound);

    // Click
    if (n->hoveredUp && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        n->value += n->step;
        if (n->value > n->maxValue) n->value = n->maxValue;
        if (n->clickSound.frameCount > 0) PlaySound(n->clickSound);
    }
    else if (n->hoveredDown && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        n->value -= n->step;
        if (n->value < n->minValue) n->value = n->minValue;
        if (n->clickSound.frameCount > 0) PlaySound(n->clickSound);
    }
}

void RAYUI_WITH_PREFIX(DrawNumericInput)(
    RAYUI_WITH_PREFIX(NumericInput)* n,
    Font font, int fontSize,
    Color bgColor, Color textColor) {
    RAYUI_WITH_PREFIX(DrawNumericInputEx)(n, font, fontSize, bgColor, textColor, GRAY, DARKGRAY, 0, BLACK);
}

void RAYUI_WITH_PREFIX(DrawNumericInputEx)(
    RAYUI_WITH_PREFIX(NumericInput)* n,
    Font font, int fontSize,
    Color bgColor, Color textColor,
    Color triangleColor, Color triangleHoverColor, int outlineWidth, Color outlineColor) {
    DrawRectangleRec(n->rect, bgColor);

    float triHeight = n->rect.height / 6.0f;

    DrawTriangle(
        n->upTriangle.a,
        n->upTriangle.b,
        n->upTriangle.c,
        n->hoveredUp ? triangleHoverColor : triangleColor
    );

    DrawTriangle(
        n->downTriangle.a,
        n->downTriangle.b,
        n->downTriangle.c,
        n->hoveredDown ? triangleHoverColor : triangleColor
    );

    if (outlineWidth > 0) {
        Rectangle outlineRect = {
            n->rect.x - outlineWidth,
            n->rect.y - outlineWidth,
            n->rect.width + outlineWidth * 2,
            n->rect.height + outlineWidth * 2
        };
        DrawRectangleLinesEx(outlineRect, outlineWidth, outlineColor);
    }

    char buffer[32];
    snprintf(buffer, sizeof(buffer), "%.*f", n->decimalPlaces, n->value);
    Vector2 size = MeasureTextEx(font, buffer, fontSize, 1);
    Vector2 pos = {
        n->rect.x + (n->rect.width - size.x)/2,
        n->rect.y + triHeight + ((n->rect.height - 2*triHeight - size.y)/2)
    };
    DrawTextEx(font, buffer, pos, fontSize, 1, textColor);
}

float RAYUI_WITH_PREFIX(GetNumericInputValue)(RAYUI_WITH_PREFIX(NumericInput)* n) {
    return n->value;
}

void RAYUI_WITH_PREFIX(SetNumericInputValue)(RAYUI_WITH_PREFIX(NumericInput)* n, float value) {
    if (value < n->minValue) value = n->minValue;
    if (value > n->maxValue) value = n->maxValue;
    n->value = value;
}

#endif // RAYUI_IMPLEMENTATION

#ifdef __cplusplus
}
#endif
#endif // RAYUI_H