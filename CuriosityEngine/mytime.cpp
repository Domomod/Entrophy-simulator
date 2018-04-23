#include "mytime.h"

std::chrono::time_point<std::chrono::system_clock> MyTime::m_start;
std::chrono::time_point<std::chrono::system_clock> MyTime::m_end;

void MyTime::initialize()
{
    m_end=std::chrono::system_clock::now();
}
void MyTime::update()
{
    m_start = m_end;
    m_end = std::chrono::system_clock::now();
}
double MyTime::getDelta()
{
    std::chrono::duration<double> elapsed_seconds = m_end - m_start;
    return elapsed_seconds.count();
}
