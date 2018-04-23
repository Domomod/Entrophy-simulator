#ifndef MYTIME_H
#define MYTIME_H

#include <chrono>
#include <ctime>

class MyTime
{
public:
    static void initialize();
    static void update();
    static double getDelta();

private:
    static std::chrono::time_point<std::chrono::system_clock> m_start;
    static std::chrono::time_point<std::chrono::system_clock> m_end;
};

#endif // MYTIME_H
