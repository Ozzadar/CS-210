/*
 *  Application.h
 *
 *  Date: Feb 13th 2022
 *  Author: Paul Mauviel
 */

#ifndef INC_7_1_APPLICATION_H
#define INC_7_1_APPLICATION_H

#include <python_module.h>
#include <filesystem>
#include <utils_ref.h>

/**
 * Main application
 */
class Application {
public:
    explicit Application(std::filesystem::path inputfile, unsigned char terminalWidth = 60);
    ~Application() = default;

    // The main application entry point and loop
    void Run();
private:
    // Displays the user menu options
    void displayMenu() const;

    // Option 1
    void optionListPurchases() const;
    // Option 2
    void optionCalculateFrequencyOfItem() const;
    // Option 3
    void optionHistogram() const;
    // Option 4 -- Exits the application
    void exit();

private:

    // Variable for indicating whether application is running
    bool m_running { false };
    unsigned char m_terminalWidth;
    PythonModule m_pythonModule;

    std::filesystem::path m_inputFile;
    std::filesystem::path m_outputFile;
};

#endif //INC_7_1_APPLICATION_H
