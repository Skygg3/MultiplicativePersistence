#pragma once

#include <chrono>

class Timer
{
public:
    Timer();
    void start();
    void restart();

    long long elapsedNanoseconds();
    long long elapsedMicroseconds();
    long long elapsedMilliseconds();
    long long elapsedSeconds();

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime;
};
