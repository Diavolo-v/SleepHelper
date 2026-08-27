#include "sensor_manager.h"
#include <Arduino.h>
#include <DHT.h>
#define DHT_PIN 27
#define DHT_TYPE 22
#define LIGHT_SENSOR 35
#define CO2_SENSOR 34
#define NOISE_SENSOR 32

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
    currentData.co2 = readCO2();
    currentData.noise = readNoise();
}
SensorData SensorManager::getCurrentData()
{
    return currentData;
}
int SensorManager::readCO2()
{
    int rawValue = analogRead(CO2_SENSOR);
    return map(rawValue, 0, 4095, 400, 2000);
}
int SensorManager::readNoise()
{
    int rawValue = analogRead(NOISE_SENSOR);
    return map(rawValue, 0, 4095, 20, 70);
}