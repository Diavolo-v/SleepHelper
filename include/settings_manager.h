#ifndef SETTINGS_MANAGER_H
#define SETTINGS_MANAGER_H
#include "clock.h"
enum SettingState
{
    MENU_SETTINGS,
    SET_TIME,
    SET_TIME_FORMAT,
    DISPLAY_SETTINGS,
    SLEEP_SETTINGS,
    BACK_SETTINGS
};
enum SleepSettingState
{
    SLEEP_SETTING_MENU,
    SLEEP_GOAL
};

enum SettingOption
{
    TIME_OPTION,
    TIME_FORMAT_OPTION,
    DISPLAY_OPTION,
    SLEEP_OPTION,
    BACK_OPTION
};
enum TimeSetupState
{
    SET_HOUR_CLOCK,
    SET_MINUTE_CLOCK,
    CONFIRM_TIME
};
enum SleepGoal
{
    H730,
    H8,
    H830,
    H9
};
class SettingsManager
{
private:
    SettingState state = MENU_SETTINGS;
    TimeSetupState clockSetup = SET_HOUR_CLOCK;
    SleepSettingState sleepSettings = SLEEP_SETTING_MENU;
    int selectedSettingOption = TIME_OPTION;
    int selectedTimeFormatOption = 0;
    int selectedSleepSettingOption = 0;
    int selectedSleepGoalOption = 0;
    int sleepGoalMinutes = 480;

public:
    void update();
    SettingState getState();
    TimeSetupState getClockSettingState();
    void setClockSettingState(TimeSetupState state);
    int getSelectedOption();
    void handleNext();
    void handleSelect();
    void setState(SettingState state);
    int getTimeFormatOption();
    void handleTimeFormatNext();
    void setSleepSettingState(SleepSettingState state);
    SleepSettingState getSleepSettingState();
    int getSelectedSleepOption();
    void handleSleepSettingNext();
    int getSelectedSleepGoalOption();
    SleepGoal getSelectedSleepGoal();
    void setSelectedSleepGoal(int goal);
    void handleSleepGoalOptionNext();
    int getSleepGoalMinutes();
};

#endif
