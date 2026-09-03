#ifndef DISPLAY_MANAGER
#define DISPLAY_MANAGER
#include <Adafruit_SSD1306.h>
#include "sleep_session.h"
#include "alarm_manager.h"
#include "settings_manager.h"
class DisplayManager
{
private:
    Adafruit_SSD1306 *display;

public:
    DisplayManager(Adafruit_SSD1306 *display);
    void drawClock(int hours, int minutes, int seconds);
    void drawHomeScreen(
        float temperature,
        float humidity,
        int light,
        int hours,
        int minutes,
        int seconds,
        AlarmManager alarm);
    void drawMenu(int selectedScreen);
    void drawAlarmSetInfo(AlarmManager alarm);

    void drawNightMode(int hours, int minutes, int seconds, AlarmManager alarm);
    void drawStatistics(const Summary &summary, int score);
    void drawAlarm(int selectedAlarmOption);
    void drawSettings(int selectedOption);
    void drawAlarmSettings(int selectedAlarmOption);
    void drawAlarmSetup(int hour, int minute, AlarmSetupState setupstate);

    void drawSetTime(int hour, int minute, TimeSetupState clockSetup);
    void drawTimeFormat();
    void drawDisplaySettings();
    void drawSleepSettings();

    //
    void tempAndHumidity(float temperature, float humdity);
    void timeOfDay(int light);
};

#endif