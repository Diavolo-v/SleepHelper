#pragma once
enum TimeFormat
{
  FORMAT_24H,
  FORMAT_12H
};
class Clock
{
private:
  int hour;
  int minutes;
  int seconds;
  unsigned long previousMillis;
  TimeFormat timeFormat = FORMAT_24H;

public:
  Clock(int startHour, int startMinutes, int startSeconds);

  void update();

  int getHours();
  int getMinutes();
  int getSeconds();
  void setTime(int hours, int minutes, int seconds);
  void setTimeFormat(TimeFormat timeFormat);
  TimeFormat getTimeFormat();
};
