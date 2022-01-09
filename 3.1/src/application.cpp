/*
 *  Application.cpp
 *
 *  Date: January 9th 2022
 *  Author: Paul Mauviel
 */

#include <application.h>
#include <iostream>
#include <clock.h>
#include <cmath>
#include <utils.h>
#include <thread>

// Clamps the clock face to sane values to ensure proper display on reasonably sized terminals
Application::Application(uint32_t t_faceWidth) : m_clock(std::clamp(t_faceWidth, 25U, 60U)) {}

void Application::Run() {
    // start the application
    m_running = true;

    while (m_running) {
        bool blink = true;

        while (!IsKeyDown(ESCAPE_KEY)) {
            // Clear the screen before beginning
            ClearScreen();

            // Display the clocks
            displayClocks();

            // Blinks directions at the user every other frame
            if (blink) {
                std::string padding(m_clock.GetClockFaceWidth() / 2, ' ');
                std::cout << padding << "*** Press Escape for Menu ***" << std::endl;
            }
            blink = !blink;

            // sleep for a second, then add one second to the current time.
            std::this_thread::sleep_for(std::chrono::seconds(1));
            m_clock.addSecond();
        }

        // Display the menu
        displayMenu();

        // Get user input as an integer
        auto userInput = getUserInput();

        // Perform appropriate action based on user selection
        switch (userInput) {
            case 1: {
                m_clock.addHour();
                break;
            }
            case 2: {
                m_clock.addMinute();
                break;
            }
            case 3: {
                m_clock.addSecond();
                break;
            }
            case 4: {
                exit();
                break;
            }
            default: {
                std::cout << "Invalid input" << std::endl;
            }
        }
    }
}

void Application::displayClocks() const {
    // Retrieve both 24 and 12-hour clock faces as an array of 4 strings each
    auto twelveHourTime = m_clock.GetClockFace(false);
    auto twentyFourHourTime = m_clock.GetClockFace(true);

    // Display them side by side
    for (size_t i = 0; i < twelveHourTime.size(); i++) {
        std::cout << twelveHourTime[i] << "     " << twentyFourHourTime[i] << std::endl;
    }
}

void Application::displayMenu() const {
    // Retrieve the face width
    auto faceWidth = m_clock.GetClockFaceWidth();

    // Build the 'lid' which will begin and end the menu
    std::string lid (faceWidth, '*');

    // Build the menu options of the same width as the clock face for visual consistency
    std::string option1 {"* 1 - Add One Hour"};
    option1.resize(faceWidth, ' ');
    option1[faceWidth - 1] = '*';
    std::string option2 {"* 2 - Add One Minute"};
    option2.resize(faceWidth, ' ');
    option2[faceWidth - 1] = '*';
    std::string option3 {"* 3 - Add One Second"};
    option3.resize(faceWidth, ' ');
    option3[faceWidth - 1] = '*';
    std::string option4 {"* 4 - Exit"};
    option4.resize(faceWidth, ' ');
    option4[faceWidth - 1] = '*';

    // Calculate front padding to properly center the menu below the clock faces
    // 3 is an evil magic number, but I think it's fine
    std::string frontPadding (faceWidth / 2 + 3, ' ');

    // Print the menu options, remembering to properly cap them with the lid
    std::cout << frontPadding << lid << std::endl;
    std::cout << frontPadding << option1 << std::endl;
    std::cout << frontPadding << option2 << std::endl;
    std::cout << frontPadding << option3 << std::endl;
    std::cout << frontPadding << option4 << std::endl;
    std::cout << frontPadding << lid << std::endl;
}


void Application::exit() {
    // ends the application
    m_running = false;
}

int Application::getUserInput() {
    // Default to -1 to indicate error
    int userInput { -1 };

    // Retrieve user input as integer
    std::cin >> userInput;

    // if an invalid character is input, cin will report a failure
    if (std::cin.fail()) {
        // clear the failure flag
        std::cin.clear();
        // ignore any remaining characters  in the buffer up to the first new line.
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return userInput;
}



