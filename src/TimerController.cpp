#include "TimerController.hpp"
#include "Timer.h"
#include "swRTC.h"

Timer t;
swRTC rtc;

int currentSeconds = 0;
int maxSeconds = 5;

void UpdateTimer()
{
    if (MaxTimeReached())
        ResetTimer();
    t.update();
}

bool MaxTimeReached()
{
    return currentSeconds > maxSeconds;
}

void Cycle()
{
    currentSeconds++;
}

void ResetTimer()
{
    currentSeconds = 0;
}

void ConfigureTimer()
{
    t.every(1000, Cycle);
}

void SetCurrentTime()
{

    rtc.stopRTC();

    // Adjust the following values to match the current date and time
    // and power on Arduino at the time set (use GMT timezone!)
    rtc.setDate(27, 10, 2020);
    rtc.setTime(16, 05, 30); // +7 hours current time

    rtc.startRTC();
}

unsigned long GetTimestamp()
{
    return rtc.getTimestamp();
}