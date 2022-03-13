/*
 *  Application.cpp
 *
 *  Date: Feb 13th 2022
 *  Author: Paul Mauviel
 */

#include <application.h>
#include <iostream>
#include <string>
#include <utils.h>
#include <filesystem>
#include <utility>
#include <fstream>
#include <cstddef>

// Initializes the application
Application::Application(std::filesystem::path inputfile, unsigned char terminalWidth) :
        m_inputFile{std::move(inputfile) },
        m_terminalWidth{terminalWidth},
        m_pythonModule{std::string{"python.CornerGrocer"}},
        m_outputFile {std::filesystem::current_path() / "data" / "frequency.dat"} {
    // Initialize the python interpreter and pull in the appropriate python module
    Py_Initialize();

    // if the module is not in it's correct location, we print the error and exit the application
    if (PyErr_Occurred()) {
        PyErr_Print();
        exit();
    }
}

// Reference: This function is mostly lifted from my 3-1 (Project One) submission
void Application::Run() {
    // start the application only if the python module has successfully been loaded
    m_running = m_pythonModule.IsValid();

    while (m_running) {
        // Display the menu
        displayMenu();

        // Get user input as an integer
        auto userInput = getValidInteger();

        // Perform appropriate action based on user selection
        switch (userInput) {
            case 1: {
                optionListPurchases();
                break;
            }
            case 2: {
                optionCalculateFrequencyOfItem();
                break;
            }
            case 3: {
                optionHistogram();
                break;
            }
            case 4: {
                exit();
                break;
            }
            default: {
                std::cout << "Invalid selection. Please select options 1 to 4." << std::endl;
            }
        }
    }
}

// Reference: This function is mostly lifted from my 3-1 (Project One) submission
void Application::displayMenu() const {

    // Build the 'lid' which will begin and end the menu
    std::string lid (m_terminalWidth, '*');

    // Build the menu options of the requested width
    std::string option1 {"* 1 - All Item Stats for Day"};
    option1.resize(m_terminalWidth, ' ');
    option1[m_terminalWidth - 1] = '*';
    std::string option2 {"* 2 - Individual Item Stats for Day"};
    option2.resize(m_terminalWidth, ' ');
    option2[m_terminalWidth - 1] = '*';
    std::string option3 {"* 3 - Create Histogram"};
    option3.resize(m_terminalWidth, ' ');
    option3[m_terminalWidth - 1] = '*';
    std::string option4 {"* 4 - Exit"};
    option4.resize(m_terminalWidth, ' ');
    option4[m_terminalWidth - 1] = '*';

    // Center the menu
    std::string frontPadding (m_terminalWidth / 2 + 3, ' ');

    // Print the menu options, remembering to properly cap them with the lid
    std::cout << frontPadding << lid << std::endl;
    std::cout << frontPadding << option1 << std::endl;
    std::cout << frontPadding << option2 << std::endl;
    std::cout << frontPadding << option3 << std::endl;
    std::cout << frontPadding << option4 << std::endl;
    std::cout << frontPadding << lid << std::endl;
}

// ends the application
void Application::exit() {
    m_running = false;
}

void Application::optionListPurchases() const {
    m_pythonModule.CallFunc<void>("print_item_frequencies_in_file", {
            {
                .type = ParamType::String,
                .value = m_inputFile.string(),
            }
    });
}

void Application::optionCalculateFrequencyOfItem() const {
    std::string padding (m_terminalWidth * 0.66f, ' ');

    // First we prompt the user for an item
    std::string item {};
    std::cout << "Which item would you like to look for? ";
    std::getline(std::cin, item);
    std::cout << std::endl;

    // Then we call the python function to get the frequency from the file
    auto freq = m_pythonModule.CallFunc<int>("get_frequency_for_item_in_file", {
            {
                .type = ParamType::String,
                .value = item,
            },
            {
                .type = ParamType::String,
                .value = m_inputFile.string(),
            }
    });

    // and output it to the screen
    std::cout << padding << std::string(43, '_') << std::endl;
    std::cout << padding << "Number of " << item << ": " << freq << std::endl;
    std::cout << padding << std::string(43, '_') << std::endl;

}

void Application::optionHistogram() const {
    std::string padding (m_terminalWidth * 0.66f, ' ');

    // First we generate the data file from which we'll read
    m_pythonModule.CallFunc<void>("output_frequencies_to_file", {
            {
                    .type = ParamType::String,
                    .value = m_inputFile.string(),
            },
            {
                    .type = ParamType::String,
                    .value = m_outputFile.string(),
            }
    });

    // Open input file for reading and assert if there's a problem
    std::ifstream inputFile {m_outputFile, std::ios::in};
    if (!inputFile.is_open()) assert(false && "Failed to open input file!");

    // With the last space found we can now create two tokens
    std::cout << padding << std::string(43, '_') << std::endl;
    std::cout << padding << "Purchase Histogram" << std::endl;
    std::cout << padding << std::string(43, '_') << std::endl;

    // Go through the file line by line
    std::string currentLine {};
    while(std::getline(inputFile, currentLine)) {
        // Trim any whitespace
        trim(currentLine);
        // Do not add empty line
        if (currentLine.length() == 0) continue;

        // to support multi-token item names, it's only necessary to get the integer
        // at the end of the string. Therefore, we'll look for the first space from the end
        // (or the last space in the string)
        uint64_t lastSpace;
        bool lastSpaceFound { false };

        for (uint64_t i = currentLine.length() - 1; i >= 0; i--) {
            if (currentLine[i] == ' ') {
                lastSpace = i;
                lastSpaceFound = true;
                break;
            }
        }

        if (lastSpaceFound) {
            auto name = currentLine.substr(0, lastSpace);
            auto freq = currentLine.substr(lastSpace + 1, currentLine.length());

            int freqCount = std::stoi(freq);

            std::cout << padding << std::setw(20) << std::right << name << " | " << std::setw(20) <<
                      std::right << std::string(freqCount, '@') << std::endl;
        }
    }
    std::cout << padding << std::string(43, '-') << std::endl;

    // close the file
    inputFile.close();


}

