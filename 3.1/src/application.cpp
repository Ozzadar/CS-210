//
// Created by ozzadar on 2021-12-20.
//

#include "application.h"
#include <iostream>
#include <clock.h>
#include <cmath>

Application::Application(uint32_t t_faceWidth) : m_faceWidth(std::clamp(t_faceWidth, 25U, 60U)) {}

void Application::Run() {
    m_running = true;

    while (m_running) {
        displayClocks();
        displayMenu();

        auto userInput = getUserInput();

        switch (userInput) {
            case 1: {
                addHour();
                break;
            }
            case 2: {
                addMinute();
                break;
            }
            case 3: {
                addSecond();
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

void Application::displayClocks() {
    auto currentTime = std::chrono::system_clock::to_time_t(m_currentTime);

    auto twelveHourTime = Clock::GetClockFace(false, currentTime, m_faceWidth);
    auto twentyFourHourTime = Clock::GetClockFace(true, currentTime, m_faceWidth);

    for (size_t i = 0; i < twelveHourTime.size(); i++) {
        std::cout << twelveHourTime[i] << "     " << twentyFourHourTime[i] << std::endl;
    }
}


void Application::displayMenu() const {
    std::string lid (m_faceWidth, '*');
    std::string option1 {"* 1 - Add One Hour"};
    option1.resize(m_faceWidth, ' ');
    option1[m_faceWidth - 1] = '*';
    std::string option2 {"* 2 - Add One Minute"};
    option2.resize(m_faceWidth, ' ');
    option2[m_faceWidth - 1] = '*';
    std::string option3 {"* 3 - Add One Second"};
    option3.resize(m_faceWidth, ' ');
    option3[m_faceWidth - 1] = '*';
    std::string option4 {"* 4 - Exit"};
    option4.resize(m_faceWidth, ' ');
    option4[m_faceWidth - 1] = '*';

    std::string frontPadding (m_faceWidth / 2 + 3, ' ');

    std::cout << frontPadding << lid << std::endl;
    std::cout << frontPadding << option1 << std::endl;
    std::cout << frontPadding << option2 << std::endl;
    std::cout << frontPadding << option3 << std::endl;
    std::cout << frontPadding << option4 << std::endl;
    std::cout << frontPadding << lid << std::endl;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-convert-member-functions-to-static"
int Application::getUserInput() {
    int userInput {0};

    std::cin >> userInput;
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    return userInput;
}
#pragma clang diagnostic pop

void Application::addMinute() {
    using namespace std::chrono_literals;
    m_currentTime += 1min;
}

void Application::addSecond() {
    using namespace std::chrono_literals;
    m_currentTime += 1s;
}

void Application::addHour() {
    using namespace std::chrono_literals;
    m_currentTime += 1h;
}

void Application::exit() {
    m_running = false;
}


