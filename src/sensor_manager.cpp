#include "sensor_manager.h"
#include <Arduino.h>
#include <DHT.h>
#define DHT_PIN 27
#define DHT_TYPE 22
#define LIGHT_SENSOR 35

DHT dht(DHT_PIN, DHT_TYPE);

SensorManager::SensorManager()
{
    dht.begin();

    pinMode(LIGHT_SENSOR, INPUT);
}
void SensorManager::update()
{
    currentData.temperature = dht.readTemperature();
    currentData.humidity = dht.readHumidity();
    currentData.light = analogRead(LIGHT_SENSOR);
}
SensorData SensorManager::getCurrentData()
{
    return currentData;
}