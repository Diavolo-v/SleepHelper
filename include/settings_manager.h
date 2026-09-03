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
class SettingsManager
{
private:
    SettingState state = MENU_SETTINGS;
    TimeSetupState clockSetup = SET_HOUR_CLOCK;
    int selectedSettingOption = TIME_OPTION;
    int selectedTimeFormatOption = 0;

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
};

#endif
