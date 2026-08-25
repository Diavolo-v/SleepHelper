#include "display_manager.h"
#include <Wire.h>
#include "clock.h"
extern Clock myClock;
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

void DisplayManager::drawHomeScreen(float temperature, float humidity, int light, int hours, int minutes, int seconds)
{
    drawClock(hours, minutes, seconds);
    tempAndHumidity(temperature, humidity);
    timeOfDay(light);
    display->display();
}

void DisplayManager::drawNightMode(int hours, int minutes, int seconds)
{
    drawClock(hours, minutes, seconds);
    display->setTextSize(1);
    display->setCursor(48, 54);
    display->print("NIGHT MODE");
    display->display();
}

void DisplayManager::drawAlarm()
{
    display->setTextSize(2);
    display->setCursor(28, 30);
    display->print("ALARM");
    display->display();
}

void DisplayManager::drawStatistics()
{
    display->setTextSize(1);
    display->setCursor(1, 30);
    display->print("Sleep Score : 84");
    display->display();
}

void DisplayManager::drawSettings()
{
    display->setTextSize(2);
    display->setCursor(28, 30);
    display->print("Settings");
    display->display();
}
