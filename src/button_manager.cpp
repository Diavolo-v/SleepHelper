#include <Arduino.h>
#include "button_manager.h"

#define NEXT_BUTTON_PIN 4
#define SELECT_BUTTON 5
#define ALARM_BUTTON 15

ButtonManager::ButtonManager()
{
}
void ButtonManager::begin()
{
    pinMode(NEXT_BUTTON_PIN, INPUT_PULLUP);
    pinMode(SELECT_BUTTON, INPUT_PULLUP);
    pinMode(ALARM_BUTTON, INPUT_PULLUP);
}
void ButtonManager::update()
{
    alarmButtonPressed = false;
    nextPressed = false;
    selectPressed = false;

    bool nextReading = digitalRead(NEXT_BUTTON_PIN);

    if (nextReading != lastNextReading)
    {
        lastNextDebounceTime = millis();
    }
    if (millis() - lastNextDebounceTime > debounceDelay)
    {
        if (nextReading != nextButtonState)
        {
            nextButtonState = nextReading;
            if (nextButtonState == LOW)
            {
                nextPressed = true;
            }
        }
    }
    lastNextReading = nextReading;
    bool selectReading = digitalRead(SELECT_BUTTON);
    if (selectReading != lastSelectReading)
    {
        lastSelectDebounce = millis();
    }
    if (millis() - lastSelectDebounce > debounceDelay)
    {
        if (selectReading != selectButtonState)
        {
            selectButtonState = selectReading;
            if (selectButtonState == LOW)
            {
                selectPressed = true;
            }
        }
    }
    lastSelectReading = selectReading;

    if (digitalRead(ALARM_BUTTON) == LOW)
    {
        alarmButtonPressed = true;
    }
}

bool ButtonManager::isNextPressedBtn()
{
    return nextPressed;
}
bool ButtonManager::isSelectPressedBtn()
{
    return selectPressed;
}
bool ButtonManager::isAlarmPressedBtn()
{
    return alarmButtonPressed;
}
