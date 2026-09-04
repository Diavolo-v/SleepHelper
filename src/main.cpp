#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "button_manager.h"
#include "clock.h"
#include "display_manager.h"
#include "sensor_manager.h"
#include "sleep_session.h"
#include "sleep_score.h"
#include "alarm_manager.h"
#include "ui_manager.h"
#include "settings_manager.h"

#define ALARM_BUZZER_PIN 25

Adafruit_SSD1306 display(128, 64, &Wire, -1);
SensorManager sensors;
SleepScore sleepscore;
AlarmManager alarmClock(ALARM_BUZZER_PIN);
DisplayManager displayManager(&display);
SleepSession sleepsession;
ButtonManager buttons;
SettingsManager settingsManager;
Clock myClock(18, 10, 0);
Summary summary;
UIManager ui(&buttons, &myClock, &alarmClock, &sleepsession, &sleepscore, &displayManager, &settingsManager, &summary);

//=======================SYSEM FUNC===========================

void setup()
{
  Serial.begin(9600);
  buttons.begin();
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println("Oled not found");
    while (true)
      ;
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.display();
}

void loop()
{
  myClock.update();
  sensors.update();

  SensorData data = sensors.getCurrentData();

  sleepsession.update(data);

  alarmClock.update(myClock.getHours(), myClock.getMinutes());

  ui.update();

  display.clearDisplay();
  ui.draw(&data);
}
