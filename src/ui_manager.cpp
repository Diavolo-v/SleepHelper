#include "ui_manager.h"

UIManager::UIManager(ButtonManager *buttons, Clock *clock, AlarmManager *alarmClock, SleepSession *sleepSession, SleepScore *sleepScore, DisplayManager *displayManager, SettingsManager *settingsManager, Summary *summary)
{
    this->buttons = buttons;
    this->clock = clock;
    this->alarmClock = alarmClock;
    this->sleepSession = sleepSession;
    this->sleepScore = sleepScore;
    this->displayManager = displayManager;
    this->settingsManager = settingsManager;
    this->summary = summary;
}

void UIManager::handleMenuNext()
{
    selectedScreen++;
    if (selectedScreen > 4)
    {
        selectedScreen = 0;
    }
}

void UIManager::handleSettingsNext()
{
    settingsManager->handleNext();
}
void UIManager::handleDisplaySettingsNext()
{
    displayManager->handleDisplayNext();
}
void UIManager::handleAlarmMenuNext()
{
    if (alarmClock->isEnabled())
    {
        selectedAlarmOption++;
        if (selectedAlarmOption > BACK)
        {
            selectedAlarmOption = SET;
        }
    }
    else
    {
        if (selectedAlarmOption == SET)
        {
            selectedAlarmOption = BACK;
        }
        else if (selectedAlarmOption == BACK)
        {
            selectedAlarmOption = SET;
        }
    }
}

void UIManager::handleClockSetupNext()
{
    if (settingsManager->getClockSettingState() == SET_HOUR_CLOCK)
    {
        hour++;
        if (hour > 23)
        {
            hour = 0;
        }
    }
    else if (settingsManager->getClockSettingState() == SET_MINUTE_CLOCK)
    {
        minutes++;
        if (minutes > 59)
        {
            minutes = 0;
        }
    }
}

void UIManager::handleAlarmSetupNext()
{
    if (alarmSetupState == SET_HOUR)
    {
        hour++;
        if (hour > 23)
        {
            hour = 0;
        }
    }
    else if (alarmSetupState == SET_MINUTE)
    {
        minutes = minutes + 5;
        if (minutes > 59)
        {
            minutes = 0;
        }
    }
}

void UIManager::handleMenuSelect()
{
    currentScreen = (Screen)selectedScreen;
    uistate = SCREEN_VIEW;
    if (currentScreen == NIGHT_MODE && clock->getHours() >= 18)
    {
        sleepSession->start(clock->getHours(), clock->getMinutes(), clock->getSeconds());
    }
}
void UIManager::handleScreenSelect()
{

    if (currentScreen == NIGHT_MODE && sleepSession->isActive())
    {

        sleepSession->end(
            clock->getHours(),
            clock->getMinutes(),
            clock->getSeconds());

        *summary = sleepSession->getSummary();

        sleepScore->calculateTotalScore(*summary);
    }

    if (currentScreen == ALARM)
    {
        handleAlarmSelect();
    }
    else if (currentScreen == SETTINGS)
    {
    }
    else
    {
        uistate = MENU;
    }
}
void UIManager::handleAlarmSelect()
{
    if (selectedAlarmOption == SET)
    {
        if (alarmClock->isEnabled())
        {
            hour = alarmClock->getHour();
            minutes = alarmClock->getMinutes();
        }
        else
        {
            hour = 7;
            minutes = 15;
        }

        alarmSetupState = SET_HOUR;
        uistate = ALARM_SETUP;
    }
    else if (selectedAlarmOption == DISABLE)
    {
        alarmClock->disableAlarm();
        selectedAlarmOption = SET;
        uistate = MENU;
    }
    else if (selectedAlarmOption == BACK)
    {
        uistate = MENU;
    }
}

void UIManager::handleSettingsSelect()
{
    if (settingsManager->getSelectedOption() == TIME_OPTION)
    {
        hour = clock->getHours();
        minutes = clock->getMinutes();

        settingsManager->setClockSettingState(SET_HOUR_CLOCK);
        settingsManager->setState(SET_TIME);
    }
    else if (settingsManager->getSelectedOption() == TIME_FORMAT_OPTION)
    {
        settingsManager->setState(SET_TIME_FORMAT);
    }
    else if (settingsManager->getSelectedOption() == DISPLAY_OPTION)
    {
        settingsManager->setState(DISPLAY_SETTINGS);
    }
    else if (settingsManager->getSelectedOption() == SLEEP_OPTION)
    {
        settingsManager->setState(SLEEP_SETTINGS);
    }
    else if (settingsManager->getSelectedOption() == BACK_OPTION)
    {
        uistate = MENU;
    }
}
void UIManager::handleTimeFormatSetupNext()
{
    settingsManager->handleTimeFormatNext();
}

void UIManager::handleSettingClockSelect()
{
    if (settingsManager->getClockSettingState() == SET_HOUR_CLOCK)
    {
        settingsManager->setClockSettingState(SET_MINUTE_CLOCK);
    }
    else if (settingsManager->getClockSettingState() == SET_MINUTE_CLOCK)
    {
        settingsManager->setClockSettingState(CONFIRM_TIME);
    }
    else if (settingsManager->getClockSettingState() == CONFIRM_TIME)
    {
        clock->setTime(hour, minutes, 0);
        settingsManager->setClockSettingState(SET_HOUR_CLOCK);
        settingsManager->setState(MENU_SETTINGS);
    }
}
void UIManager::handleAlarmSetupSelect()
{
    if (alarmSetupState == SET_HOUR)
    {
        alarmSetupState = SET_MINUTE;
    }
    else if (alarmSetupState == SET_MINUTE)
    {
        alarmSetupState = CONFIRM;
    }
    else if (alarmSetupState == CONFIRM)
    {
        alarmClock->setAlarm(hour, minutes);
        uistate = MENU;
    }
}
void UIManager::handleTimeFormatSelect()
{
    if (settingsManager->getTimeFormatOption() == 0)
    {
        clock->setTimeFormat(FORMAT_24H);
        uistate = MENU;
    }
    else if (settingsManager->getTimeFormatOption() == 1)
    {
        clock->setTimeFormat(FORMAT_12H);
        uistate = MENU;
    }
    else
    {
        settingsManager->setState(MENU_SETTINGS);
    }
}

void UIManager::handleDisplayBrightnessSelect()
{
    if (displayManager->getBrightnessOption() == LOW_B)
    {
        displayManager->setBrightness(80);
    }
    else if (displayManager->getBrightnessOption() == MID_B)
    {
        displayManager->setBrightness(160);
    }
    else if (displayManager->getBrightnessOption() == HIGH_B)
    {
        displayManager->setBrightness(255);
    }
    else
    {
        settingsManager->setState(MENU_SETTINGS);
    }
}

void UIManager::handleAlarmButton()
{
    if (buttons->isAlarmPressedBtn())
    {
        alarmClock->stopRinging();
    }
}
void UIManager::handleNextButton()
{
    if (!buttons->isNextPressedBtn())
    {
        return;
    }

    if (uistate == MENU)
    {
        handleMenuNext();
    }
    else if (uistate == SCREEN_VIEW && currentScreen == ALARM)
    {
        handleAlarmMenuNext();
    }
    else if (uistate == SCREEN_VIEW && currentScreen == SETTINGS)
    {
        handleSettingsNext();
        if (settingsManager->getState() == SET_TIME)
        {
            handleClockSetupNext();
        }
        else if (settingsManager->getState() == SET_TIME_FORMAT)
        {
            handleTimeFormatSetupNext();
        }
        else if (settingsManager->getState() == DISPLAY_SETTINGS)
        {
            handleDisplaySettingsNext();
        }
    }
    else if (uistate == ALARM_SETUP)
    {
        handleAlarmSetupNext();
    }
}
void UIManager::handleSelectButton()
{
    if (!buttons->isSelectPressedBtn())
    {
        return;
    }

    if (uistate == MENU)
    {
        handleMenuSelect();
    }
    else if (uistate == SCREEN_VIEW && currentScreen == SETTINGS)
    {
        if (settingsManager->getState() == SET_TIME)
        {
            handleSettingClockSelect();
        }
        else if (settingsManager->getState() == SET_TIME_FORMAT)
        {
            handleTimeFormatSelect();
        }
        else if (settingsManager->getState() == DISPLAY_SETTINGS)
        {
            handleDisplayBrightnessSelect();
        }

        else
        {
            handleSettingsSelect();
        }
    }
    else if (uistate == SCREEN_VIEW)
    {
        handleScreenSelect();
    }
    else if (uistate == ALARM_SETUP)
    {
        handleAlarmSetupSelect();
    }
}

void UIManager::update()
{
    buttons->update();
    handleAlarmButton();
    handleNextButton();
    handleSelectButton();
}
void UIManager::draw(SensorData *data)
{
    if (uistate == MENU)
    {
        displayManager->drawMenu(selectedScreen);
    }
    else if (uistate == SCREEN_VIEW)
    {
        switch (currentScreen)
        {
        case HOME:
            displayManager->drawHomeScreen(data->temperature, data->humidity, data->light, clock->getHours(), clock->getMinutes(), clock->getSeconds(), *alarmClock);
            break;
        case NIGHT_MODE:
            displayManager->drawNightMode(clock->getHours(), clock->getMinutes(), clock->getSeconds(), *alarmClock);
            break;
        case STATISTICS:
            displayManager->drawStatistics(*summary, sleepScore->returnTotalScore());
            break;
        case ALARM:
            displayManager->drawAlarm(selectedAlarmOption);
            break;
        case SETTINGS:

            if (settingsManager->getState() == MENU_SETTINGS)
            {
                displayManager->drawSettings(settingsManager->getSelectedOption());
            }
            else if (settingsManager->getState() == SET_TIME)
            {
                displayManager->drawSetTime(hour, minutes, settingsManager->getClockSettingState());
            }
            else if (settingsManager->getState() == SET_TIME_FORMAT)
            {
                displayManager->drawTimeFormat(settingsManager->getTimeFormatOption());
            }
            else if (settingsManager->getState() == DISPLAY_SETTINGS)
            {
                displayManager->drawDisplaySettings(displayManager->getBrightnessOption());
            }
            else if (settingsManager->getState() == SLEEP_SETTINGS)
            {
                /* code */
            }

            break;
        }
    }
    else if (uistate == ALARM_SETUP)
    {
        displayManager->drawAlarmSetup(hour, minutes, alarmSetupState);
    }
}