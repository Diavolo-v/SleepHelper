#ifndef DISPLAY_MANAGER
#define DISPLAY_MANAGER
#include <Adafruit_SSD1306.h>
#include "sleep_session.h"
#include "alarm_manager.h"
#include "settings_manager.h"
enum BrightnessLevel
{
    LOW_B,
    MID_B,
    HIGH_B
};
class DisplayManager
{
private:
    Adafruit_SSD1306 *display;
    BrightnessLevel brightness = HIGH_B;
    int brightnessOptionCount = 0;

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
    void drawTimeFormat(int selectedFormatOption);
    void drawDisplaySettings(int brightnessOptionCount);
    void drawSleepSettings(int selectedSleepSettingOption);
    void drawSleepGoalSettings(int selectedSleepGoalOption);

    //
    void tempAndHumidity(float temperature, float humdity);
    void timeOfDay(int light);
    void drawTimeFor24HFormat(int hours, int minutes, int seconds);
    void drawTimeFor12HFormat(int hours, int minutes, int seconds);

    void setBrightness(int value);
    int getBrightness();
    int getBrightnessOption();
    void handleDisplayNext();
};

#endif