/*
 *  Application.h
 *
 *  Date: January 9th 2022
 *  Author: Paul Mauviel
 */

#pragma once

#include <chrono>
#include "clock.h"

/**
 * Main application for manipulating and displaying a clock
 */
class Application {
public:
    // Constructor, receiving clock face width as parameter for consistent sizing.
    explicit Application(uint32_t t_faceWidth = 25);

    // The main application entry point and loop
    void Run();
private:
    // Displays the clock with 12 and 24 hour time side by side
    void displayClocks() const;
    // Displays the user menu options
    void displayMenu() const;
    // Exits the application
    void exit();

    // Gets an integer input from the user. -1 indicates an error
    static int getUserInput();

private:
    // The main clock
    Clock m_clock;

    // Variable for indicating whether application is running
    bool m_running { false };
};
