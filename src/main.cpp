#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
#include "clock.h"
#include "display_manager.h"
#define LED_PIN 2
#define POT_PIN 34
#define NEXT_BUTTON_PIN 4
#define SELECT_BUTTON 5
#define LIGHT_PIN 35

bool lastNextReading = HIGH;
bool nextButtonState = HIGH;

bool lastSelectReading = HIGH;
bool selectButtonState = HIGH;

unsigned long lastDebounceTime = 0;
unsigned long lastSelectDebounce = 0;

const unsigned long debounceDelay = 50;

DHT dht(27, DHT22);
Adafruit_SSD1306 display(128, 64, &Wire, -1);

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

Screen currentScreen = HOME;

Clock myClock(16, 10, 0);

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
        }
        else if (uistate == SCREEN_VIEW)
        {
          uistate = MENU;
        }
      }
    }
  }
  lastSelectReading = reading;
}

void drawMenu()
{
  display.setTextSize(1);

  display.setCursor(5, 0);
  display.print("MENU");

  display.setCursor(10, 12);
  if (selectedScreen == 0)
  {
    display.print("> HOME");
  }
  else
  {
    display.print(" HOME");
  }

  display.setCursor(10, 22);
  if (selectedScreen == 1)
  {
    display.print("> NIGHT MODE");
  }
  else
  {
    display.print(" NIGHT MODE");
  }

  display.setCursor(10, 32);
  if (selectedScreen == 2)
  {
    display.print("> STATISTICS");
  }
  else
  {
    display.print(" STATISTICS");
  }

  display.setCursor(10, 42);
  if (selectedScreen == 3)
  {
    display.print("> ALARM");
  }
  else
  {
    display.print(" ALARM");
  }
  display.setCursor(10, 52);
  if (selectedScreen == 4)
  {
    display.print("> SETTINGS");
  }
  else
  {
    display.print(" SETTINGS");
  }

  display.display();
}

//=======================SYSEM FUNC===========================

void setup()
{

  dht.begin();
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  // ledcAttach(LED_PIN, 5000, 8);
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
  int value = analogRead(34);
  int brightness = map(value, 0, 4095, 30, 255);
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int light = analogRead(LIGHT_PIN);

  updateNextButton();
  updateSelectButton();
  display.clearDisplay();

  if (uistate == MENU)
  {
    drawMenu();
  }
  else if (uistate == SCREEN_VIEW)
  {
    switch (currentScreen)
    {
    case HOME:
      displayManager.drawHomeScreen(temperature, humidity, light, myClock.getHours(), myClock.getMinutes(), myClock.getSeconds());
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
