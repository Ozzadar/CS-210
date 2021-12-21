//
// Created by ozzadar on 2021-12-20.
//

#ifndef INC_3_1_APPLICATION_H
#define INC_3_1_APPLICATION_H

#include <chrono>

class Application {
public:
    explicit Application(uint32_t t_faceWidth = 25);

    void Run();
private:
    void displayClocks();
    void displayMenu() const;

    void addMinute();
    void addSecond();
    void addHour();
    void exit();

    int getUserInput();

    std::chrono::time_point<std::chrono::system_clock> m_currentTime { std::chrono::system_clock::now() };
    uint32_t m_faceWidth { 25 };
    bool m_running { false };
};


#endif //INC_3_1_APPLICATION_H
