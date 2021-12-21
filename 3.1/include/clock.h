//
// Created by ozzadar on 2021-12-20.
//

#ifndef INC_3_1_CLOCK_H
#define INC_3_1_CLOCK_H

#include <string>
#include <ctime>
#include <array>

static const std::string TWELVE_HOUR_FORMAT_STRING {"%I:%M:%S %p"};
static const std::string TWENTY_FOUR_HOUR_FORMAT_STRING {"%H:%M:%S"};

class Clock {
public:
    static std::array<std::string, 4> GetClockFace(bool isTwentyFourHour, time_t time, uint32_t faceWidth);

private:
    static std::string formatTimeToString(const time_t& time, const std::string& format);
};


#endif //INC_3_1_CLOCK_H
