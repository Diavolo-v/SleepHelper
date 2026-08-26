#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
#include "clock.h"
#include "display_manager.h"
#include "sensor_manager.h"
#include "sleep_session.h"
#define LED_PIN 2
#define POT_PIN 34
#define NEXT_BUTTON_PIN 4
#define SELECT_BUTTON 5

bool lastNextReading = HIGH;
bool nextButtonState = HIGH;

bool lastSelectReading = HIGH;
bool selectButtonState = HIGH;

unsigned long lastDebounceTime = 0;
unsigned long lastSelectDebounce = 0;

const unsigned long debounceDelay = 50;

Adafruit_SSD1306 display(128, 64, &Wire, -1);
SensorManager sensors;
DisplayManager displayManager(&display);

enum UIState
{
  MENU,
  SCREEN_VIEW
};

UIState uistate = MENU;

enum Screen
{
  HOME,
  NIGHT_MODE,
  STATISTICS,
  ALARM,
  SETTINGS
};
int selectedScreen = 0;
SleepSession sleepsession;
Screen currentScreen = HOME;

Clock myClock(18, 10, 0);

void updateNextButton()
{

  bool reading = digitalRead(NEXT_BUTTON_PIN);

  if (reading != lastNextReading)
  {
    lastDebounceTime = millis();
  }

  if (millis() - lastDebounceTime > debounceDelay)
  {

    if (reading != nextButtonState)
    {

      nextButtonState = reading;

      if (nextButtonState == LOW)
      {
        if (uistate == MENU)
        {
          selectedScreen++;
          if (selectedScreen > 4)
          {
            selectedScreen = 0;
          }
        }
      }
    }
  }

  lastNextReading = reading;
}

void updateSelectButton()
{
  bool reading = digitalRead(SELECT_BUTTON);

  if (reading != lastSelectReading)
  {
    lastSelectDebounce = millis();
  }

  if (millis() - lastSelectDebounce > debounceDelay)
  {
    if (reading != selectButtonState)
    {
      selectButtonState = reading;

      if (selectButtonState == LOW)
      {
        if (uistate == MENU)
        {
          currentScreen = (Screen)selectedScreen;
          uistate = SCREEN_VIEW;
          if (currentScreen == NIGHT_MODE && myClock.getHours() >= 18)
          {
            sleepsession.start(myClock.getHours(), myClock.getMinutes(), myClock.getSeconds());
          }
        }
        else if (uistate == SCREEN_VIEW)
        {
          if (currentScreen == NIGHT_MODE && sleepsession.isActive())
          {
            sleepsession.end(myClock.getHours(), myClock.getMinutes(), myClock.getSeconds());
            Serial.println("sleep session ended");
          }
          uistate = MENU;
        }
      }
    }
  }
  lastSelectReading = reading;
}

//=======================SYSEM FUNC===========================

void setup()
{
  Serial.begin(9600);
  pinMode(NEXT_BUTTON_PIN, INPUT_PULLUP);
  pinMode(SELECT_BUTTON, INPUT_PULLUP);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println("Oled not found");
    while (true)
      ;
  }
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 20);
  display.display();
}

void loop()
{
  myClock.update();
  sensors.update();
  SensorData data = sensors.getCurrentData();
  sleepsession.update(data);
  if (sleepsession.newMeasurement())
  {
    sleepsession.printMeasurements();
  }

  updateNextButton();
  updateSelectButton();
  display.clearDisplay();

  if (uistate == MENU)
  {
    displayManager.drawMenu(selectedScreen);
  }
  else if (uistate == SCREEN_VIEW)
  {
    switch (currentScreen)
    {
    case HOME:
      displayManager.drawHomeScreen(data.temperature, data.humidity, data.light, myClock.getHours(), myClock.getMinutes(), myClock.getSeconds());
      break;
    case NIGHT_MODE:
      displayManager.drawNightMode(myClock.getHours(), myClock.getMinutes(), myClock.getSeconds());
      break;
    case STATISTICS:
      displayManager.drawStatistics();
      break;
    case ALARM:
      displayManager.drawAlarm();
      break;
    case SETTINGS:
      displayManager.drawSettings();
      break;
    }
  }
}
