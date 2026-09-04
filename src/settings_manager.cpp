#include "settings_manager.h"

int SettingsManager::getSelectedOption()
{
    return selectedSettingOption;
}
SettingState SettingsManager::getState()
{
    return state;
}

void SettingsManager::handleNext()
{
    selectedSettingOption++;
    if (selectedSettingOption > BACK_OPTION)
    {
        selectedSettingOption = TIME_OPTION;
    }
}
void SettingsManager::handleTimeFormatNext()
{
    selectedTimeFormatOption++;
    if (selectedTimeFormatOption > 2)
    {
        selectedTimeFormatOption = 0;
    }
}

void SettingsManager::setState(SettingState settingState)
{
    this->state = settingState;
}
TimeSetupState SettingsManager::getClockSettingState()
{
    return clockSetup;
}
void SettingsManager::setClockSettingState(TimeSetupState state)
{
    this->clockSetup = state;
}

int SettingsManager::getTimeFormatOption()
{
    return selectedTimeFormatOption;
}
void SettingsManager::setSleepSettingState(SleepSettingState state)
{
    this->sleepSettings = state;
}
SleepSettingState SettingsManager::getSleepSettingState()
{
    return sleepSettings;
}
int SettingsManager::getSelectedSleepOption()
{
    return selectedSleepSettingOption;
}

void SettingsManager::handleSleepSettingNext()
{
    selectedSleepSettingOption++;
    if (selectedSleepSettingOption > 1)
    {
        selectedSleepSettingOption = 0;
    }
}
int SettingsManager::getSelectedSleepGoalOption()
{
    return selectedSleepGoalOption;
}
void SettingsManager::handleSleepGoalOptionNext()
{
    selectedSleepGoalOption++;
    if (selectedSleepGoalOption > 4)
    {
        selectedSleepGoalOption = 0;
    }
}
void SettingsManager::setSelectedSleepGoal(int goal)
{
    this->sleepGoalMinutes = goal;
}
int SettingsManager::getSleepGoalMinutes()
{
    return sleepGoalMinutes;
}