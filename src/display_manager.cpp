#include "display_manager.h"
#include "sleep_session.h"
#include "sleep_score.h"
#include <Wire.h>
#include "clock.h"
extern Clock myClock;
extern AlarmManager alarmClock;
DisplayManager::DisplayManager(Adafruit_SSD1306 *display)
{
    this->display = display;
}
void DisplayManager::drawClock(int hours, int minutes, int seconds)
{
    display->setTextSize(3);
    display->setCursor(15, 5);

    if (hours < 10)
    {
        display->print("0");
    }
    display->print(hours);

    if (seconds % 2 == 0)
    {
        display->print(":");
    }
    else
    {
        display->print(" ");
    }
    if (seconds < 10)
    {
        display->print("0");
    }
    display->print(minutes);
}
void DisplayManager::timeOfDay(int light)
{
    display->setTextSize(1);
    display->setCursor(48, 54);
    if (light > 3000)
    {
        display->print("NIGHT");
    }
    else if (light > 1800)
    {
        display->print("EVENING");
    }
    else if (light > 800)
    {
        display->print("DAY");
    }
    else
    {
        display->print("BRIGHT DAY");
    }
}
void DisplayManager::tempAndHumidity(float temperature, float humidity)
{
    display->setTextSize(1);
    display->setCursor(5, 38);
    display->print(temperature, 1);
    display->println(" C");
    display->setCursor(78, 38);
    display->print(humidity, 0);
    display->println(" %");
}

void DisplayManager::drawHomeScreen(float temperature, float humidity, int light, int hours, int minutes, int seconds, AlarmManager alarm)
{
    drawClock(hours, minutes, seconds);
    tempAndHumidity(temperature, humidity);
    timeOfDay(light);
    drawAlarmSetInfo(alarm);
    display->display();
}
void DisplayManager::drawAlarmSetInfo(AlarmManager alarm)
{
    if (alarm.isEnabled())
    {
        display->setTextSize(1);
        display->setCursor(80, 54);
        display->print("AL ");
        if (alarm.getHour() < 10)
        {
            display->print("0");
        }

        display->print(alarm.getHour());
        display->print(":");
        if (alarm.getMinutes() < 10)
        {
            display->print("0");
        }

        display->print(alarm.getMinutes());
    }
}

void DisplayManager::drawNightMode(int hours, int minutes, int seconds, AlarmManager alarm)
{
    drawClock(hours, minutes, seconds);
    display->setTextSize(1);
    display->setCursor(48, 54);
    display->print("NIGHT MODE");
    drawAlarmSetInfo(alarm);
    display->display();
}

void DisplayManager::drawAlarm(int selectedAlarmOption)
{
    display->setTextSize(2);
    display->setCursor(32, 2);
    display->print("ALARM");
    drawAlarmSettings(selectedAlarmOption);
    display->display();
}

void DisplayManager::drawStatistics(const Summary &summary, int score)
{

    display->setTextSize(1);
    display->setCursor(20, 0);
    display->print("SLEEP STATISTICS");
    display->setCursor(5, 14);
    if (summary.hasTemperature)
    {
        display->print(summary.averageTemp, 1);
        display->println(" C");
    }
    else
    {
        display->println("N/A");
    }

    display->setCursor(5, 25);
    if (summary.hasHumidity)
    {
        display->print(summary.averageHum, 1);
        display->println(" %");
    }
    else
    {
        display->println("N/A");
    }

    display->setCursor(5, 36);
    if (summary.hasLight)
    {
        display->print(summary.averageLight, 0);
        display->println(" LUX");
    }
    else
    {
        display->println("N/A");
    }
    display->setCursor(60, 14);
    if (summary.hasCO2)
    {
        display->print(summary.averageCO2, 1);
        display->println(" ppm");
    }
    else
    {
        display->println("N/A");
    }
    display->setCursor(60, 25);
    if (summary.hasNoise)
    {
        display->print(summary.averageNoise, 1);
        display->println(" dB");
    }
    else
    {
        display->println("N/A");
    }

    display->setCursor(5, 49);
    display->print("Today's sleep score: ");
    display->print(score);
    display->print(" / 100");
    display->display();
}

void DisplayManager::drawSettings()
{
    display->setTextSize(2);
    display->setCursor(28, 30);
    display->print("Settings");
    display->display();
}

void DisplayManager::drawMenu(int selectedScreen)
{
    display->setTextSize(1);

    display->setCursor(5, 0);
    display->print("MENU");

    display->setCursor(10, 12);
    if (selectedScreen == 0)
        display->print("> HOME");
    else
        display->print(" HOME");

    display->setCursor(10, 22);
    if (selectedScreen == 1)
        display->print("> NIGHT MODE");
    else
        display->print(" NIGHT MODE");

    display->setCursor(10, 32);
    if (selectedScreen == 2)
        display->print("> STATISTICS");
    else
        display->print(" STATISTICS");

    display->setCursor(10, 42);
    if (selectedScreen == 3)
        display->print("> ALARM");
    else
        display->print(" ALARM");

    display->setCursor(10, 52);
    if (selectedScreen == 4)
        display->print("> SETTINGS");
    else
        display->print(" SETTINGS");

    display->display();
}
void DisplayManager::drawAlarmSettings(int selectedAlarmOption)
{
    display->setTextSize(1);
    display->setCursor(10, 25);
    if (selectedAlarmOption == 0)
    {
        display->print("> SET ALARM");
    }
    else
    {
        display->print("  SET ALARM");
    }
    if (selectedAlarmOption == 1)
    {
        if (alarmClock.isEnabled())
        {
            display->setCursor(10, 35);
            display->print("> DISABLE ALARM");
        }
    }
    else
    {
        if (alarmClock.isEnabled())
        {
            display->setCursor(10, 35);
            display->print("  DISABLE ALARM");
        }
    }

    display->setCursor(10, 45);

    if (selectedAlarmOption == 2)
    {
        display->print("> BACK");
    }
    else
    {
        display->print("  BACK");
    }
    display->display();
}
void DisplayManager::drawAlarmSetup(int hour, int minute, AlarmSetupState setupstate)
{
    display->setTextSize(2);
    display->setCursor(35, 20);
    if (hour < 10)
    {
        display->print("0");
    }
    display->print(hour);
    display->print(":");
    if (minute < 10)
    {
        display->print("0");
    }
    display->print(minute);

    if (setupstate == SET_HOUR)
    {
        display->setCursor(40, 42);
        display->print("^");
    }
    else if (setupstate == SET_MINUTE)
    {
        display->setCursor(75, 42);
        display->print("^");
    }
    display->setCursor(38, 55);
    display->setTextSize(1);
    if (setupstate == CONFIRM)
    {
        display->print("> DONE");
    }
    else
    {
        display->print("  DONE");
    }

    display->display();
}