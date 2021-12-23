/*
 *  Clock.cpp
 *
 *  Date: January 3rd 2022
 *  Author: Paul Mauviel
 */

#include <clock.h>
#include <cmath>


Clock::Clock(uint32_t t_faceWidth) : m_faceWidth(t_faceWidth) {}

std::array<std::string, 4> Clock::GetClockFace(bool isTwentyFourHour) const {
    // convert the current time from chrono into time_t for formatting
    auto time = std::chrono::system_clock::to_time_t(m_currentTime);

    //create array to hold each line of the clock face
    std::array<std::string, 4> clockFace;

    // build the lid of appropriate size
    std::string lid (m_faceWidth, '*');

    // create the title string depending on parameter
    std::string title { isTwentyFourHour ? "24-Hour Clock" : "12-Hour Clock" };
    // create the time string depending on parameter
    std::string timeString = formatTimeToString(time, isTwentyFourHour ? TWENTY_FOUR_HOUR_FORMAT_STRING
                                                                       : TWELVE_HOUR_FORMAT_STRING);

    // This is the size of the whitespace between the * denoting a clock face
    size_t innerSize = m_faceWidth - 2;

    // pad the title in the middle of the inner size
    std::string paddedTitle (m_faceWidth, ' ');
    paddedTitle[0] = '*';
    paddedTitle[m_faceWidth - 1] = '*';
    size_t titlePaddingLeft = std::ceil(static_cast<float>(innerSize - title.size() + 1) / 2.0);

    // add the title to the appropriate location in the string
    for (size_t i = titlePaddingLeft, k = 0;  k < title.size(); i++, k++) {
        paddedTitle[i] = title[k];
    }

    // pad the time in the middle of the inner size
    std::string paddedTime (m_faceWidth, ' ');
    paddedTime[0] = '*';
    paddedTime[m_faceWidth - 1] = '*';
    size_t timePaddingLeft = std::ceil(static_cast<float>(innerSize - timeString.size() + 1) / 2.0);

    // add the time to the appropriate location in the string
    for (size_t i = timePaddingLeft, k = 0;  k < timeString.size(); i++, k++) {
        paddedTime[i] = timeString[k];
    }

    // build the clock face
    clockFace[0] = lid;
    clockFace[1] = paddedTitle;
    clockFace[2] = paddedTime;
    clockFace[3] = lid;

    return clockFace;
}

void Clock::addMinute() {
    using namespace std::chrono_literals;
    m_currentTime += 1min;
}

void Clock::addSecond() {
    using namespace std::chrono_literals;
    m_currentTime += 1s;
}

void Clock::addHour() {
    using namespace std::chrono_literals;
    m_currentTime += 1h;
}

std::string Clock::formatTimeToString(const time_t& time, const std::string& format) {
    // string that will hold the formatted time
    std::string formattedString {};
    // resize the string to properly hold the formatted time
    formattedString.resize(format.size() + 1);

    // temporary time type buffer
    tm buf {};
    // safe function for converting time_t to tm types
    localtime_s(&buf, &time);

    // format the string with the given format into the formatted time string
    strftime(formattedString.data(), sizeof(char) * formattedString.size(), format.c_str(), &buf);

    return formattedString;
}


