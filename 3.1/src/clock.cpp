//
// Created by ozzadar on 2021-12-20.
//

#include "clock.h"
#include <cmath>

std::array<std::string, 4> Clock::GetClockFace(bool isTwentyFourHour, time_t time, uint32_t faceWidth) {

    //create array
    std::array<std::string, 4> clockFace;

    std::string lid (faceWidth, '*');
    std::string title { isTwentyFourHour ? "24-Hour Clock" : "12-Hour Clock" };
    std::string timeString = FormatTimeToString(time, isTwentyFourHour ? TWENTY_FOUR_HOUR_FORMAT_STRING : TWELVE_HOUR_FORMAT_STRING);

    size_t innerSize = faceWidth - 2;

    // pad the title
    std::string paddedTitle (faceWidth, ' ');
    paddedTitle[0] = '*';
    paddedTitle[faceWidth - 1] = '*';

    size_t titlePaddingLeft = std::ceil(static_cast<float>(innerSize - title.size() + 1) / 2.0);

    for (size_t i = titlePaddingLeft, k = 0;  k < title.size(); i++, k++) {
        paddedTitle[i] = title[k];
    }

    std::string paddedTime (faceWidth, ' ');
    paddedTime[0] = '*';
    paddedTime[faceWidth - 1] = '*';

    size_t timePaddingLeft = std::ceil(static_cast<float>(innerSize - timeString.size() + 1) / 2.0);

    for (size_t i = timePaddingLeft, k = 0;  k < timeString.size(); i++, k++) {
        paddedTime[i] = timeString[k];
    }

    clockFace[0] = lid;
    clockFace[1] = paddedTitle;
    clockFace[2] = paddedTime;
    clockFace[3] = lid;

    return clockFace;
}

std::string Clock::FormatTimeToString(const time_t& time, const std::string& format) {
    std::string formattedString {};
    formattedString.resize(format.size() + 1);

    tm buf {};
    localtime_s(&buf, &time);

    strftime(formattedString.data(), sizeof(char) * formattedString.size(), format.c_str(), &buf);

    return formattedString;
}

