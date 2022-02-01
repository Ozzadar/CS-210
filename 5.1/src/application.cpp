/*
 *  application.cpp
 *
 *  Date: January 31st 2022
 *  Author: Paul Mauviel
 */

#include "application.h"
#include <utils.h>
#include <iostream>
#include <iomanip>
#include <thread>
#include <fmt/format.h>

Application::Application(unsigned char terminalWidth) : m_TerminalWidth { terminalWidth }, m_Running{ false }, m_PreviousReports{}, m_TerminalLine(m_TerminalWidth, '*') {}

void Application::run() {
    m_Running = true;

#ifdef WIN32
    // On windows, we give the option to escape the program using the escape key
    // On other platforms, we'll have to quit in a less graceful fashion.
    std::thread escapeThread {
            [this](){
                while (true) {
                    if (isKeyDown(ESCAPE_KEY)) {
                        this->m_Running = false;
                        return;
                    }
                }
            }
    };
#endif

    while (m_Running) {
        try {
            auto parameters = readReportParameters();

            // Spawn a thread that will listen for user input using platform specific code.
            // This is different from how I accomplished it in 3-1.
            bool receivedUserInput { false };
            std::thread inputThread {
                [&receivedUserInput](){
                    if (GETCH()) {
                        receivedUserInput = true;
                        return;
                    }
                }
            };

            std::cout << "Press any key to continue..." << std::endl;
            // Wait for thread to report that a key has been pressed
            while (!receivedUserInput) {}
            // Joins the thread to avoid dangling references
            inputThread.join();

            // Clears the screen
            clearScreen();

            // Generate the reports and add them history
            auto parametersWithout = parameters;
            parametersWithout.MonthlyDeposit = 0.0;

            auto [noDepositReport, withDepositReport] = m_PreviousReports.emplace_back(
            Report("Balance and Interest Without Additional Monthly Deposits", parametersWithout),
            Report("Balance and Interest With Additional Monthly Deposits", parameters)
            );

            // Print the reports
            noDepositReport.printYearly(m_TerminalWidth);
            withDepositReport.printYearly(m_TerminalWidth);

            // Wait for user input to go again
            // Spawn a thread that will listen for user input using platform specific code.
            // This is different from how I accomplished it in 3-1.
            receivedUserInput = false;
            inputThread = std::thread {
                    [&receivedUserInput](){
                        if (GETCH()) {
                            receivedUserInput = true;
                            return;
                        }
                    }
            };

            std::cout << "Press any key to try new values... " << std::endl;
            // Wait for thread to report that a key has been pressed
            while (!receivedUserInput) {}
            // Joins the thread to avoid dangling references
            inputThread.join();

#ifdef WIN32
            // Currently our asynchronous input monitoring doesn't work on not windows platforms,
            // so we ensure that we don't clear the screen after printing reports so users have a chance to
            // look at them
            clearScreen();
#endif
        } catch (const std::exception& e) {
            // Display the error message
            clearScreen();
            std::cout << m_TerminalLine << std::endl;
            std::cout << "!!!" << std::setw(m_TerminalWidth) << std::right <<fmt::format("Invalid user input: {} !!!", e.what()) << std::endl;
            std::cout << m_TerminalLine << std::endl;
        }
    }

#ifdef WIN32
    escapeThread.join();
#endif
}

ReportParameters Application::readReportParameters() {
    ReportParameters input;

    std::cout << m_TerminalLine << '\n';
    const std::string title = " Data Input ";
    std::cout << m_TerminalLine.substr(0, (m_TerminalLine.length() / 2) - (title.length() / 2))
        << title
        << m_TerminalLine.substr(0, (m_TerminalLine.length() / 2) - (title.length() / 2)) << '\n';

#if WIN32
    std::string instruction { "  Press escape at any time to quit after the next report  " };
    std::cout << m_TerminalLine.substr(0, (m_TerminalLine.length() / 2) - (instruction.length() / 2))
              << instruction
              << m_TerminalLine.substr(0, (m_TerminalLine.length() / 2) - (instruction.length() / 2)) << '\n';
#endif
    std::cout << m_TerminalLine << '\n';
    std::cout << m_TerminalLine << '\n';

    std::string tempInput;
    size_t numberIdx;

    std::cout << std::setfill(' ') <<  std::setw(28) << std::left <<  "Initial Investment Amount:" << "$";
    std::getline(std::cin, tempInput);
    assertValidPositiveNumber(tempInput);
    input.InitialInvestment = std::stod(tempInput, &numberIdx);
    assertIndexIsAtEndOfString(tempInput, numberIdx);

    std::cout << std::setfill(' ') <<   std::setw(28) << std::left <<  "Monthly Deposit:" << "$";
    std::getline(std::cin, tempInput);
    assertValidPositiveNumber(tempInput);
    input.MonthlyDeposit = std::stod(tempInput, &numberIdx);
    assertIndexIsAtEndOfString(tempInput, numberIdx);

    std::cout << std::setfill(' ') <<    std::setw(28) << std::left << "Annual Interest:" << "%";
    std::getline(std::cin, tempInput);
    assertValidPositiveNumber(tempInput);
    input.AnnualInterest = std::stod(tempInput, &numberIdx) / 100.0;
    assertIndexIsAtEndOfString(tempInput, numberIdx);

    std::cout << std::setfill(' ') <<   std::setw(29) << std::left << "Number of years:" << std::flush;
    std::getline(std::cin, tempInput);
    assertValidPositiveNumber(tempInput);
    input.NumberOfMonths = std::stoi(tempInput, &numberIdx) * 12;
    assertIndexIsAtEndOfString(tempInput, numberIdx);

    std::cout << std::endl;

    return input;
}

