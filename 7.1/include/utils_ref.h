/*
 *  utils_ref.h
 *
 *  Function exclusively lifted from external sources. References provided below.
 *
 *  Date: Feb 13th 2022
 *  Author: Paul Mauviel
 */

// String trimming functions lifted from: https://stackoverflow.com/questions/216823/how-to-trim-a-stdstring
// because I didn't feel like implementing them myself

#ifndef INC_7_1_UTILS_REF_H
#define INC_7_1_UTILS_REF_H

#include <algorithm>
#include <cctype>
#include <locale>

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

// trim from start (copying)
static inline std::string ltrim_copy(std::string s) {
    ltrim(s);
    return s;
}

// trim from end (copying)
static inline std::string rtrim_copy(std::string s) {
    rtrim(s);
    return s;
}

// trim from both ends (copying)
static inline std::string trim_copy(std::string s) {
    trim(s);
    return s;
}
#endif //INC_7_1_UTILS_REF_H
