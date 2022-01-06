#ifndef INC_3_1_INPUT_UTIL_H
#define INC_3_1_INPUT_UTIL_H

#if _WIN32
    #include <Windows.h>
    #define ESCAPE_KEY VK_ESCAPE
#endif

static bool IsKeyDown(int key) {
#if _WIN32
    return GetAsyncKeyState(key) == 0;
#endif
    return false;
}

#endif //INC_3_1_INPUT_UTIL_H
