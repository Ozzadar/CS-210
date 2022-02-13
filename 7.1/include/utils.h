/*
 *  utils.h
 *
 *  Date: January 31st 2022
 *  Author: Paul Mauviel
 */

#ifndef INC_6_3_UTILS_H
#define INC_6_3_UTILS_H

// Reference: I wrote this function for assignment 5-1 (Project 2)
// Throws an error if the string is not a valid positive number.
static void assertValidInteger(const std::string &str) {
    if (str.find_first_not_of("0123456789-.") != std::string::npos) throw std::runtime_error("Not a valid integer!");
}

// Reference: I wrote this function for assignment 5-1 (Project 2)
static void assertIndexIsAtEndOfString(const std::string &str, size_t index) {
    if (index < str.length()) throw std::runtime_error("Extra characters at end of number (must not contain decimals)!");
}

// Continues to attempt to get a valid integer until one is supplied
static int getValidInteger() {
    bool success { false };
    int num { -1 };
    while (!success) {
        try {
            std::string number;
            std::getline(std::cin, number);

            size_t idx;
            num = std::stoi(number, &idx);

            assertValidInteger(number);
            assertIndexIsAtEndOfString(number, idx);
            success = true;
        } catch (const std::exception& e) {
            std::cout << "Invalid number: " << e.what() << std::endl;
        }
    }

    return num;
}
#endif //INC_6_3_UTILS_H
