#ifndef ALARM_MANAGER_H
#define ALARM_MANAGER_H

enum AlarmSetupState
{
    SET_HOUR,
    SET_MINUTE,
    CONFIRM
};
class AlarmManager
{
private:
    int alarmHour;
    int alarmMinute;
    bool enabled;
    bool triggered;
    int buzzer;
    int lastTrigegredMinute = -1;
    int lastTriggeredHour = -1;

public:
    AlarmManager(int pin);
    void setAlarm(int hour, int minutes);
    void disableAlarm();
    void update(int currentHour, int currentMinute);
    void setHour();
    void setMinute();
    bool isEnabled();
    bool isTrigered();
    void displayAlarmSettings();
    int getHour();
    int getMinutes();

    void stopRinging();
};

#endif
