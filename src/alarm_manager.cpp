#include "alarm_manager.h"
#include <Arduino.h>
AlarmManager::AlarmManager(int pin)
{
    alarmHour = 0;
    alarmMinute = 0;
    enabled = false;
    triggered = false;

    buzzer = pin;
    pinMode(buzzer, OUTPUT);
    digitalWrite(buzzer, LOW);
}

void AlarmManager::setAlarm(int hour, int minute)
{
    alarmHour = hour;
    alarmMinute = minute;
    lastTrigegredMinute = -1;
    lastTriggeredHour = -1;
    enabled = true;
    triggered = false;
}
void AlarmManager::disableAlarm()
{
    lastTrigegredMinute = -1;
    lastTriggeredHour = -1;
    enabled = false;
    triggered = false;
}

void AlarmManager::update(int currentHour, int currentMinute)
{
    if (!enabled || triggered)
    {
        return;
    }
    if (currentHour == alarmHour && currentMinute == alarmMinute && (lastTrigegredMinute != currentMinute || lastTriggeredHour != currentHour))
    {
        triggered = true;
        lastTrigegredMinute = currentMinute;
        lastTriggeredHour = currentHour;
    }

    if (triggered)
    {
        tone(buzzer, 1000);
    }
}

bool AlarmManager::isEnabled()
{
    return enabled;
}
bool AlarmManager::isTrigered()
{
    return triggered;
}

int AlarmManager::getHour()
{
    return alarmHour;
}
int AlarmManager::getMinutes()
{
    return alarmMinute;
}
void AlarmManager::stopRinging()
{
    triggered = false;
    noTone(buzzer);
}