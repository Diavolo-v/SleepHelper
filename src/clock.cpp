#include <Arduino.h>
#include "clock.h"

Clock::Clock(int startHour, int startMinutes, int startSeconds)
{
  hour = startHour;
  minutes = startMinutes;
  seconds = startSeconds;
  previousMillis = millis();
}

void Clock::update()
{
  if (millis() - previousMillis >= 1000)
  {
    previousMillis += 1000;
    seconds++;
    if (seconds >= 60)
    {
      seconds = 0;
      minutes++;
    }
    if (minutes >= 60)
    {
      minutes = 0;
      hour++;
    }
    if (hour >= 24)
    {
      hour = 0;
    }
  }
}

int Clock::getHours()
{
  return hour;
}
int Clock::getMinutes()
{
  return minutes;
}
int Clock::getSeconds()
{
  return seconds;
}

void Clock::setTime(int hours, int minutes, int seconds)
{

  if (hours < 0 || hours > 24)
  {
    return;
  }
  if (minutes < 0 || minutes > 59)
  {
    return;
  }
  if (seconds < 0 || seconds > 59)
  {
    return;
  }

  hour = hours;
  this->minutes = minutes;
  this->seconds = seconds;

  previousMillis = millis();
}