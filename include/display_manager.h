#ifndef DISPLAY_MANAGER
#define DISPLAY_MANAGER
#include <Adafruit_SSD1306.h>
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
        int seconds);
    void drawMenu(int selectedScreen);

    void drawNightMode(int hours, int minutes, int seconds);
    void drawStatistics();
    void drawAlarm();
    void drawSettings();

    //
    void tempAndHumidity(float temperature, float humdity);
    void timeOfDay(int light);
};

#endif