#include "sleep_session.h"
#include <Arduino.h>

int tempCount = 0;
int humCount = 0;
int lightCount = 0;
int co2Count = 0;
int noiseCount = 0;
SleepSession::SleepSession()
{
    state = IDLE;
}

void SleepSession::start(int hours, int minutes, int seconds)
{

    measurementCount = 0;
    summary = {};

    startTime.hours = hours;
    startTime.minutes = minutes;
    startTime.seconds = seconds;

    lastEnvironmentMeasurement = millis();
    lastLightMeasurement = millis();
    lastCo2Measurement = millis();
    lastNoiseMeasurement = millis();
    state = RUNNING;
}
void SleepSession::end(int hours, int minutes, int seconds)
{
    if (state != RUNNING)
    {
        return;
    }

    endTime.hours = hours;
    endTime.minutes = minutes;
    endTime.seconds = seconds;

    calculateSummary();
    state = FINISHED;
}
void SleepSession::update(const SensorData &data)
{
    if (state != RUNNING)
    {
        return;
    }
    unsigned long currentTime = millis();
    bool updateEnvironment = false;
    bool updateLight = false;
    bool updateNoise = false;
    bool updateCO2 = false;
    hasNewMeasurement = false;

    if (currentTime - lastEnvironmentMeasurement > environmentalInterval)
    {
        updateEnvironment = true;
        lastEnvironmentMeasurement = currentTime;
    }

    if (currentTime - lastLightMeasurement > lightInterval)
    {
        updateLight = true;
        lastLightMeasurement = currentTime;
    }
    if (currentTime - lastCo2Measurement > co2Interval)
    {
        updateCO2 = true;
        lastCo2Measurement = currentTime;
    }
    if (currentTime - lastNoiseMeasurement > noiseInterval)
    {
        updateNoise = true;
        lastNoiseMeasurement = currentTime;
    }

    if (updateEnvironment ||
        updateLight ||
        updateCO2 ||
        updateNoise)
    {
        if (measurementCount < MAX_MEASUREMENTS)
        {
            Measurement &measurement = measurements[measurementCount];
            measurement.timeStamp = currentTime;
            measurement.hasTemperature = updateEnvironment;
            measurement.hasHumidity = updateEnvironment;
            measurement.hasLight = updateLight;
            measurement.hasCO2 = updateCO2;
            measurement.hasNoise = updateNoise;

            if (updateEnvironment)
            {
                measurement.temperature = data.temperature;
                measurement.humidity = data.humidity;
            }
            if (updateLight)
            {
                measurement.light = data.light;
            }
            if (updateCO2)
            {
                measurement.CO2 = data.co2;
            }
            if (updateNoise)
            {
                measurement.noise = data.noise;
            }

            measurementCount++;
            hasNewMeasurement = true;
        }
    }
}
bool SleepSession::newMeasurement()
{
    return hasNewMeasurement;
}
bool SleepSession::isActive()
{
    return state == RUNNING;
}

// test function
void SleepSession::printMeasurements()
{
    if (measurementCount == 0)
    {
        return;
    }

    int lastMeasuredIndex = measurementCount - 1;
    Serial.print("Measurement ");
    Serial.println(measurementCount);

    Serial.print("Temprerature: ");
    if (measurements[lastMeasuredIndex].hasTemperature)
    {
        Serial.println(measurements[lastMeasuredIndex].temperature);
    }
    else
    {
        Serial.println("N/A");
    }
    Serial.print("Humidity: ");
    if (measurements[lastMeasuredIndex].hasHumidity)
    {
        Serial.println(measurements[lastMeasuredIndex].humidity);
    }
    else
    {
        Serial.println("N/A");
    }
    Serial.print("Light: ");
    if (measurements[lastMeasuredIndex].hasLight)
    {
        Serial.println(measurements[lastMeasuredIndex].light);
    }
    else
    {
        Serial.println("N/A");
    }
    if (measurements[lastMeasuredIndex].hasCO2)
    {
        Serial.println(measurements[lastMeasuredIndex].CO2);
    }
    else
    {
        Serial.println("N/A");
    }
    if (measurements[lastMeasuredIndex].hasNoise)
    {
        Serial.println(measurements[lastMeasuredIndex].noise);
    }
    else
    {
        Serial.println("N/A");
    }
    Serial.println("------------------");
}

float SleepSession::getAverageTemperature()
{
    float sumOfTemp = 0;
    float averageTemp = 0;
    for (int i = 0; i < measurementCount; i++)
    {
        if (measurements[i].hasTemperature)
        {
            sumOfTemp += measurements[i].temperature;
            tempCount++;
        }
    }
    if (tempCount > 0)
    {
        averageTemp = sumOfTemp / tempCount;
    }

    return averageTemp;
}

float SleepSession::getAverageHumidity()
{
    float sumOfHumidity = 0;
    float averageHumidity = 0;

    for (int i = 0; i < measurementCount; i++)
    {
        if (measurements[i].hasHumidity)
        {
            sumOfHumidity += measurements[i].humidity;
            humCount++;
        }
    }
    if (humCount > 0)
    {
        averageHumidity = sumOfHumidity / humCount;
    }

    return averageHumidity;
}
float SleepSession::getAverageLight()
{
    float sumOfLight = 0;
    float averageLight = 0;

    for (int i = 0; i < measurementCount; i++)
    {
        if (measurements[i].hasLight)
        {
            sumOfLight += measurements[i].light;
            lightCount++;
        }
    }
    if (lightCount > 0)
    {
        averageLight = sumOfLight / lightCount;
    }

    return averageLight;
}
float SleepSession::getAverageCO2()
{
    float sumOfCo2 = 0;
    float averageCO2 = 0;
    for (int i = 0; i < measurementCount; i++)
    {
        if (measurements[i].hasCO2)
        {
            sumOfCo2 += measurements[i].CO2;
            co2Count++;
        }
    }
    if (co2Count > 0)
    {
        averageCO2 = sumOfCo2 / co2Count;
    }
    return averageCO2;
}
float SleepSession::getAverageNoise()
{
    float sumOfNoise = 0;
    float averageNoise = 0;

    for (int i = 0; i < measurementCount; i++)
    {
        if (measurements[i].hasNoise)
        {
            sumOfNoise += measurements[i].noise;
            noiseCount++;
        }
    }
    if (noiseCount > 0)
    {
        averageNoise = sumOfNoise / noiseCount;
    }
    return averageNoise;
}
int SleepSession::getSleepDurationSeconds()
{
    int startSeconds = startTime.hours * 3600 + startTime.minutes * 60 + startTime.seconds;
    int endSeconds = endTime.hours * 3600 + endTime.minutes * 60 + endTime.seconds;

    int totalSleepSeconds = endSeconds - startSeconds;

    if (totalSleepSeconds < 0)
    {
        totalSleepSeconds += 24 * 3600;
    }
    return totalSleepSeconds;
}
float SleepSession::getTotalSleepDuration()
{
    return getSleepDurationSeconds() / 3600.0f;
}

void SleepSession::calculateSummary()
{
    if (measurementCount == 0)
    {
        summary = {};
        return;
    }

    summary.durationHours = getTotalSleepDuration();
    summary.averageTemp = getAverageTemperature();
    summary.averageHum = getAverageHumidity();
    summary.averageLight = getAverageLight();
    summary.averageCO2 = getAverageCO2();
    summary.averageNoise = getAverageNoise();

    summary.hasTemperature = tempCount > 0;
    summary.hasHumidity = humCount > 0;
    summary.hasLight = lightCount > 0;
    summary.hasCO2 = co2Count > 0;
    summary.hasNoise = noiseCount > 0;
}
Summary SleepSession::getSummary()
{
    return summary;
}