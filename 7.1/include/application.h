/*
 *  Application.h
 *
 *  Date: January 31st 2022
 *  Author: Paul Mauviel
 */

#ifndef INC_6_3_APPLICATION_H
#define INC_6_3_APPLICATION_H

#include <Python.h>

/**
 * Main application
 */
class Application {
public:
    explicit Application(unsigned char terminalWidth);
    ~Application();
    // The main application entry point and loop
    void Run();
private:
    // Displays the user menu options
    void displayMenu() const;

    void doubleNumber() const;
    void multiplicationTable() const;

    // Exits the application
    void exit();

private:

    // Variable for indicating whether application is running
    bool m_running { false };
    unsigned char m_TerminalWidth;
    PyObject* m_PythonModule { nullptr };
};

#endif //INC_6_3_APPLICATION_H
