#ifndef BUTTON_MANAGER_H
#define BUTTON_MANAGER_H

#include <Arduino.h>
class ButtonManager
{
private:
    bool alarmButtonPressed = false;
    bool selectPressed = false;
    bool nextPressed = false;
    bool lastNextReading = HIGH;
    bool nextButtonState = HIGH;
    bool lastSelectReading = HIGH;
    bool selectButtonState = HIGH;
    unsigned long lastNextDebounceTime = 0;
    unsigned long lastSelectDebounce = 0;
    const unsigned long debounceDelay = 50;

public:
    ButtonManager();
    void update();
    void begin();
    bool isNextPressedBtn();
    bool isSelectPressedBtn();
    bool isAlarmPressedBtn();
};

#endif