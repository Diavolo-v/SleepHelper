#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include "button_manager.h"
#include "clock.h"
#include "alarm_manager.h"
#include "sleep_session.h"
#include "sleep_score.h"
#include "display_manager.h"
#include "settings_manager.h"

enum UIState
{
    MENU,
    SCREEN_VIEW,
    ALARM_SETUP
};

enum Screen
{
    HOME,
    NIGHT_MODE,
    STATISTICS,
    ALARM,
    SETTINGS
};

enum AlarmOption
{
    SET,
    DISABLE,
    BACK
};

class UIManager
{
private:
    UIState uistate = MENU;
    Screen currentScreen = HOME;

    int selectedScreen = 0;
    int selectedAlarmOption = 0;

    int hour = 0;
    int minutes = 0;
    AlarmSetupState alarmSetupState = SET_HOUR;

    ButtonManager *buttons;
    Clock *clock;
    AlarmManager *alarmClock;
    SleepSession *sleepSession;
    SleepScore *sleepScore;
    DisplayManager *displayManager;
    SettingsManager *settingsManager;
    Summary *summary;

    void handleMenuNext();
    void handleAlarmMenuNext();
    void handleAlarmSetupNext();

    void handleMenuSelect();
    void handleScreenSelect();
    void handleAlarmSelect();
    void handleAlarmSetupSelect();

    void handleAlarmButton();
    void handleNextButton();
    void handleSelectButton();

    void handleSettingsNext();
    void handleSettingsSelect();
    void handleSettingClockSelect();
    void handleClockSetupNext();
    void handleTimeFormatSetupNext();
    void handleTimeFormatSelect();

    void handleDisplaySettingsNext();
    void handleDisplayBrightnessSelect();

    void handleSleepSettingsNext();
    void handleSleepGoalNext();
    void handleSleepSettingsSelect();
    void handleSleepGoalselect();

public:
    UIManager(ButtonManager *buttons,
              Clock *clock,
              AlarmManager *alarmClock,
              SleepSession *sleepSession,
              SleepScore *sleepScore,
              DisplayManager *displayManager,
              SettingsManager *settingsManager,
              Summary *summary);
    void update();
    UIState getUIState();
    Screen getCurrentScreen();

    int getSelectedScreen();
    int getSelectedAlarmOption();

    int getAlarmHour();
    int getAlarmMinutes();
    AlarmSetupState getAlarmSetupState();

    void draw(SensorData *data);
};

#endif