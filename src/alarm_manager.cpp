#include "alarm_manager.h"

AlarmManager::AlarmManager()
{
    alarmHour = 0;
    alarmMinute = 0;
    enabled = false;
    triggered = false;
}

void AlarmManager::setAlarm(int hour, int minute)
{
    alarmHour = hour;
    alarmMinute = minute;
    enabled = true;
    triggered = false;
}
void AlarmManager::disableAlarm()
{
    enabled = false;
    triggered = false;
}

void AlarmManager::update(int currentHour, int currentMinute)
{
    if (!enabled || triggered)
    {
        return;
    }
    if (currentHour == alarmHour && currentMinute == alarmMinute)
    {
        triggered = true;
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

void AlarmManager::setHour()
{
}