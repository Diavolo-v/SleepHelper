#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
#include "clock.h"
#include "display_manager.h"
#include "sensor_manager.h"
#include "sleep_session.h"
#include "sleep_score.h"
#include "alarm_manager.h"
#define LED_PIN 2
#define POT_PIN 34
#define NEXT_BUTTON_PIN 4
#define SELECT_BUTTON 5
#define ALARM_BUTTON 15
#define ALARM_BUZZER_PIN 25
bool lastNextReading = HIGH;
bool nextButtonState = HIGH;

bool lastSelectReading = HIGH;
bool selectButtonState = HIGH;

unsigned long lastDebounceTime = 0;
unsigned long lastSelectDebounce = 0;

const unsigned long debounceDelay = 50;

Adafruit_SSD1306 display(128, 64, &Wire, -1);
SensorManager sensors;
Summary summary;
SleepScore sleepscore;
AlarmManager alarmClock(ALARM_BUZZER_PIN);
AlarmSetupState alarmsetupstate = SET_HOUR;
DisplayManager displayManager(&display);

enum UIState
{
  MENU,
  SCREEN_VIEW,
  ALARM_SETUP
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
enum AlarmOption
{
  SET,
  DISABLE,
  BACK
};
int selectedScreen = 0;
int selectedAlarmOption = 0;
SleepSession sleepsession;
Screen currentScreen = HOME;
AlarmOption alarmoption = SET;
Clock myClock(18, 10, 0);
int hour = 0;
int minutes = 0;

void updateAlarmButton()
{
  if (digitalRead(ALARM_BUTTON) == LOW)
  {
    alarmClock.stopRinging();
  }
}
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
        else if (uistate == SCREEN_VIEW && currentScreen == ALARM)
        {

          if (alarmClock.isEnabled())
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
            else
            {
              selectedAlarmOption = SET;
            }
          }
        }
        else if (uistate == ALARM_SETUP)
        {
          if (alarmsetupstate == SET_HOUR)
          {
            hour++;
            if (hour > 23)
            {
              hour = 0;
            }
          }
          else if (alarmsetupstate == SET_MINUTE)
          {
            minutes = minutes + 5;
            if (minutes > 59)
            {
              minutes = 0;
            }
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
            summary = sleepsession.getSummary();
            sleepscore.calculateTotalScore(summary);
            Serial.println("sleep session ended");
          }
          if (currentScreen == ALARM)
          {
            if (selectedAlarmOption == SET)
            {
              if (alarmClock.isEnabled())
              {
                hour = alarmClock.getHour();
                minutes = alarmClock.getMinutes();
              }
              else
              {
                hour = 7;
                minutes = 15;
              }

              alarmsetupstate = SET_HOUR;
              uistate = ALARM_SETUP;
            }
            else if (selectedAlarmOption == DISABLE)
            {
              alarmClock.disableAlarm();
              selectedAlarmOption = SET;
              uistate = MENU;
            }
            else if (selectedAlarmOption == BACK)
            {
              uistate = MENU;
            }
          }
          else
          {
            uistate = MENU;
          }
        }
        else if (uistate == ALARM_SETUP)
        {
          if (alarmsetupstate == SET_HOUR)
          {
            alarmsetupstate = SET_MINUTE;
          }
          else if (alarmsetupstate == SET_MINUTE)
          {
            alarmsetupstate = CONFIRM;
          }
          else if (alarmsetupstate == CONFIRM)
          {
            alarmClock.setAlarm(hour, minutes);
            uistate = MENU;
            Serial.println("ALARM SAVED!.");
          }
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
  pinMode(ALARM_BUTTON, INPUT_PULLUP);
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
  alarmClock.update(myClock.getHours(), myClock.getMinutes());
  if (alarmClock.isTrigered())
  {
    Serial.println("ALARM RINGS!!");
  }

  if (sleepsession.newMeasurement())
  {
    sleepsession.printMeasurements();
  }
  updateAlarmButton();
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
      displayManager.drawHomeScreen(data.temperature, data.humidity, data.light, myClock.getHours(), myClock.getMinutes(), myClock.getSeconds(), alarmClock);
      break;
    case NIGHT_MODE:
      displayManager.drawNightMode(myClock.getHours(), myClock.getMinutes(), myClock.getSeconds(), alarmClock);
      break;
    case STATISTICS:
      displayManager.drawStatistics(summary, sleepscore.returnTotalScore());
      break;
    case ALARM:
      displayManager.drawAlarm(selectedAlarmOption);
      break;
    case SETTINGS:
      displayManager.drawSettings();
      break;
    }
  }
  else if (uistate == ALARM_SETUP)
  {
    displayManager.drawAlarmSetup(hour, minutes, alarmsetupstate);
  }
}
