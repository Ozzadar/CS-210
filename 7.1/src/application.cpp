/*
 *  Application.cpp
 *
 *  Date: January 31st 2022
 *  Author: Paul Mauviel
 */

#include <application.h>
#include <iostream>
#include <string>
#include <utils.h>

// Initializes the application
Application::Application(unsigned char terminalWidth) : m_TerminalWidth{terminalWidth} {
    // Initialize the python interpreter and pull in the appropriate python module
    Py_Initialize();
    m_PythonModule = PyImport_ImportModule("python.my_math");

    // if the module is not in it's correct location, we print the error and exit the application
    if (PyErr_Occurred()) {
        PyErr_Print();
        exit();
    }
}

// shuts down the python interpreter and clears the reference to the module
Application::~Application() {
    // decrease reference count for module
    Py_DECREF(m_PythonModule);
    m_PythonModule = nullptr;

    Py_Finalize();
}

// Reference: This function is mostly lifted from my 3-1 (Project One) submission
void Application::Run() {
    // start the application only if the python module has successfully been loaded
    m_running = bool(m_PythonModule);

    while (m_running) {
        // Display the menu
        displayMenu();

        // Get user input as an integer
        auto userInput = getValidInteger();

        // Perform appropriate action based on user selection
        switch (userInput) {
            case 1: {
                multiplicationTable();
                break;
            }
            case 2: {
                doubleNumber();
                break;
            }
            case 3: {
                exit();
                break;
            }
            default: {
                std::cout << "Invalid selection. Please select options 1 to 3." << std::endl;
            }
        }
    }
}


// Reference: This function is mostly lifted from my 3-1 (Project One) submission
void Application::displayMenu() const {

    // Build the 'lid' which will begin and end the menu
    std::string lid (m_TerminalWidth, '*');

    // Build the menu options of the requested width
    std::string option1 {"* 1 - Display Multiplication Table"};
    option1.resize(m_TerminalWidth, ' ');
    option1[m_TerminalWidth - 1] = '*';
    std::string option2 {"* 2 - Double a value"};
    option2.resize(m_TerminalWidth, ' ');
    option2[m_TerminalWidth - 1] = '*';
    std::string option3 {"* 3 - Exit"};
    option3.resize(m_TerminalWidth, ' ');
    option3[m_TerminalWidth - 1] = '*';

    // Center the menu
    std::string frontPadding (m_TerminalWidth / 2 + 3, ' ');

    // Print the menu options, remembering to properly cap them with the lid
    std::cout << frontPadding << lid << std::endl;
    std::cout << frontPadding << option1 << std::endl;
    std::cout << frontPadding << option2 << std::endl;
    std::cout << frontPadding << option3 << std::endl;
    std::cout << frontPadding << lid << std::endl;
}

// ends the application
void Application::exit() {
    m_running = false;
}

// Calls a python function to double a number
void Application::doubleNumber() const {
    // Build the 'lid' which will begin and end the menu
    std::string lid (m_TerminalWidth, '*');

    std::cout << lid << std::endl;
    std::cout << "What number would you like to double? " << std::endl;

    auto num = getValidInteger();

    // The provided sample code was pretty over-engineered for such a simple process.
    // I stripped it down to the essentials.
    PyObject* doubled_result = PyObject_CallMethod(m_PythonModule, "DoubleValue", "i", num);
    std::cout << "Your doubled number is (from Python): " << _PyLong_AsInt(doubled_result) << std::endl;

    // Clear the object we allocated
    Py_DECREF(doubled_result);
}

// calls a python function to display a multiplication table
void Application::multiplicationTable() const {
    // Build the 'lid' which will begin and end the menu
    std::string lid (m_TerminalWidth, '*');

    std::cout << lid << std::endl;
    std::cout << "Enter which multiplication table you'd like: " << std::endl;

    auto num = getValidInteger();

    // The provided sample code was pretty over-engineered for such a simple process.
    // I stripped it down to the essentials.
    PyObject_CallMethod(m_PythonModule, "MultiplicationTable", "i", num);
}



