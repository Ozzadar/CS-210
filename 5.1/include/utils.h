/*
 *  utils.h
 *
 *  Date: January 31st 2022
 *  Author: Paul Mauviel
 */

#ifndef UTILS_H
#define UTILS_H

#include <stdexcept>

#ifdef WIN32
    #include <conio.h>

    #define NOMINMAX
    #include <Windows.h>
    #define ESCAPE_KEY VK_ESCAPE
    #define GETCH() _getch()
#else
    // Always return true on platforms other than windows as to not block the thread.
    #define GETCH() true
    #define ESCAPE_KEY

#endif

// Reference: I wrote this function for assignment 3-1. Re-using it here.
static void clearScreen() {
    // "Clear" is defined both on newer windows, mac, and most linux terminals
    if (system("clear") != 0) {
        // if it returns an error we'll try CLS. This should work on older windows terminals
        system("cls");
    }
}

// Reference: I wrote this function for assignment 3-1. Re-using it here.
static inline bool isKeyDown(int key) {
#if _WIN32
    return GetAsyncKeyState(key) != 0;
#endif

    // if the platform we're running on isn't supported --
    // automatically assume the key has been pressed and show the menu
    // The reason for this is that I don't really feel like taking this code over to Mac / Linux,
    // figuring out NCurses or similar, and then doing. At least this way, the things will work on Windows.
    return true;
}


// Throws an error if the string is not a valid positive number.
static void assertValidPositiveNumber(const std::string &str) {
    if (str.find_first_not_of("0123456789.") != std::string::npos) throw std::runtime_error("Not a valid positive number!");
}

static void assertIndexIsAtEndOfString(const std::string &str, size_t index) {
    if (index < str.length()) throw std::runtime_error("Extra characters at end of number!");
}

#endif