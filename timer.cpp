#include "timer.h"

Timer::Timer()
{
}

void Timer::start()
{
    m_startTime = std::chrono::high_resolution_clock::now();
}

void Timer::restart()
{
    m_startTime = std::chrono::high_resolution_clock::now();
}

long long Timer::elapsedNanoseconds()
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - m_startTime).count();
}

long long Timer::elapsedMicroseconds()
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(currentTime - m_startTime).count();
}

long long Timer::elapsedMilliseconds()
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - m_startTime).count();
}

long long Timer::elapsedSeconds()
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::seconds>(currentTime - m_startTime).count();
}
