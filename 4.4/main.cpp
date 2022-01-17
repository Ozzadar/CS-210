/*
 *  main.cpp
 *
 *  Date: January 16th 2022
 *  Author: Paul Mauviel
 */

#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <cassert>

// Declare a handle to make working with it easier
using FilePath = std::filesystem::path;

// Class that stores a city name and farenheit temperature reading,
// calculates temperature in celsius
class TemperatureReading {
public:
    // Constructor for building object
    TemperatureReading(const std::string& city, int fahrenheit) {
        m_City = city;
        m_Fahrenheit = fahrenheit;

        // C = (F - 32) x (5/9)
        m_Celsius = (static_cast<float>(m_Fahrenheit) - 32.f) * (5.f / 9.f);
    }

    [[nodiscard]] float GetCelsius() const{
        return m_Celsius;
    }

    [[nodiscard]] int GetFahrenheit() const{
        return m_Fahrenheit;
    }

    [[nodiscard]] const std::string& GetCity() const { return m_City; }

private:
    int m_Fahrenheit;
    float m_Celsius;
    std::string m_City;
};

// Takes a temperature reading as a string and parses it into a TemperatureReading
TemperatureReading parseTemperatureReadingFromFile(const std::string& reading) {
    /*
     * Assumptions:
     * City Name will not have spaces or special characters
     * Temperature is provided as an integer
     * "CityName 100"
     */

    // Get the city name from the reading
    std::string cityName = reading.substr(0, reading.find(' '));

    // Get the temperature from the reading
    std::string temperature = reading.substr(reading.find(' ') + 1, reading.size());

    // Convert the temperature to an int
    int temp = std::stoi(temperature);
    return TemperatureReading {cityName, temp};
}

// Main Method
int main() {
    // Path's we'll be working with
    FilePath currentWorkingDirectory = std::filesystem::current_path();
    FilePath pathToInputFile = currentWorkingDirectory / "FahrenheitTemperature.txt" ;
    FilePath pathToOutputFile = currentWorkingDirectory / "CelsiusTemperature.txt";

    // vector for holding temperature readings
    std::vector<TemperatureReading> readings {};

    // Open input file for reading and assert if there's a problem
    std::ifstream inputFile {pathToInputFile, std::ios::in};
    if (!inputFile.is_open()) assert(false && "Failed to open input file!");

    // Go through the file line by line, parsing each into TemperatureReading and
    // adding to the readings vector
    std::string currentLine {};
    while(std::getline(inputFile, currentLine)) {
        readings.push_back(parseTemperatureReadingFromFile(currentLine));
    }
    // close the file
    inputFile.close();

    // Open file for writing, truncating the file if it already exists
    std::ofstream outputFile {pathToOutputFile, std::ios::out | std::ios::trunc };

    // assert if there's a problem
    if (!outputFile.is_open()) assert(false && "Failed to open output file!");

    // For each reading, write it to the file on its own line
    for (auto& temp : readings) {
        // we don't use std::endl here to avoid flushing the buffer every time
        outputFile << temp.GetCity() << " " << std::fixed << std::setprecision(2) << temp.GetCelsius() << "\n";
    }

    // flush the output buffer to ensure the contents are written to the screen
    outputFile << std::flush;

    // close the file
    outputFile.close();

    // Print success message
    std::cout << "All temperatures (Fahrenheit) in " << pathToInputFile
        << " written as Celsius to " << pathToOutputFile << std::endl;

    return 0;
}
