/*
 *  Clock.h
 *
 *  Date: January 3rd 2022
 *  Author: Paul Mauviel
 */

#ifndef INC_3_1_CLOCK_H
#define INC_3_1_CLOCK_H

#include <string>
#include <ctime>
#include <array>
#include <chrono>

// static strings used for formatting the 12 and 24 hour time
static const std::string TWELVE_HOUR_FORMAT_STRING {"%I:%M:%S %p"};
static const std::string TWENTY_FOUR_HOUR_FORMAT_STRING {"%H:%M:%S"};

/**
 * Clock class which holds current time, allows basic time manipulation and provides a formatted clock face
 */
class Clock {
public:
    // Constructor taking face width for consistent sizing
    explicit Clock(uint32_t t_faceWidth);

    // Returns an array of strings representing a clock face
    [[nodiscard]] std::array<std::string, 4> GetClockFace(bool isTwentyFourHour) const;

    // Add a minute to the current time
    void addMinute();

    // Add a second to the current time
    void addSecond();

    // Add an hour to the current time
    void addHour();

    // return the clock face width setting
    [[nodiscard]] inline uint32_t GetClockFaceWidth() const { return m_faceWidth; }

private:
    // Utility function for turning a time into a formatted string
    static std::string formatTimeToString(const time_t& time, const std::string& format);

private:
    // Clock face display width
    uint32_t m_faceWidth;

    // The current time setting on the clock -- defaults to the current local system clock time
    std::chrono::time_point<std::chrono::system_clock> m_currentTime { std::chrono::system_clock::now() };
};


#endif //INC_3_1_CLOCK_H
