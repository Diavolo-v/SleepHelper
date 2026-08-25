#ifndef CLOCK_H
#define CLOCK_H

class Clock
{
private:
  int hour;
  int minutes;
  int seconds;
  unsigned long previousMillis;

public:
  Clock(int startHour, int startMinutes, int startSeconds);

  void update();

  int getHours();
  int getMinutes();
  int getSeconds();
};
#endif
