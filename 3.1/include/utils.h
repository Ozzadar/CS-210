/*
 *  utils.h
 *
 *  Date: January 9th 2022
 *  Author: Paul Mauviel
 */

#pragma once

#if _WIN32
    #define NOMINMAX
    #include <Windows.h>
    #define ESCAPE_KEY VK_ESCAPE
#endif

static inline bool IsKeyDown(int key) {
#if _WIN32
    return GetAsyncKeyState(key) != 0;
#endif

    // if the platform we're running on isn't supported --
    // automatically assume the key has been pressed and show the menu
    // The reason for this is that I don't really feel like taking this code over to Mac / Linux,
    // figuring out NCurses or similar, and then doing. At least this way, the things will work on Windows.
    return true;
}

static void ClearScreen() {
    // "Clear" is defined both on newer windows, mac, and most linux terminals
    if (system("clear") != 0) {
        // if it returns an error we'll try CLS. This should work on older windows terminals
        system("cls");
    }
}
