#include "sleep_session.h"
#include <Arduino.h>
SleepSession::SleepSession()
{
    state = IDLE;
}

void SleepSession::start(int hours, int minutes, int seconds)
{

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

    if (updateEnvironment || updateLight)
    {
        if (measurementCount < MAX_MEASUREMENTS)
        {
            Measurement &measurement = measurements[measurementCount];
            measurement.timeStamp = currentTime;
            measurement.hasTemperature = updateEnvironment;
            measurement.hasHumidity = updateEnvironment;
            measurement.hasLight = updateLight;

            if (updateEnvironment)
            {
                measurement.temperature = data.temperature;
                measurement.humidity = data.humidity;
            }
            if (updateLight)
            {
                measurement.light = data.light;
            }
            measurementCount++;
        }
    }
    // if (currentTime - lastNoiseMeasurement > noiseInterval)
    // {
    //     lastNoiseMeasurement = currentTime;
    // }
    // if (currentTime - lastCo2Measurement > co2Interval)
    // {
    //     lastCo2Measurement = currentTime;
    // }
}

bool SleepSession::isActive()
{
    return state == RUNNING;
}

// test function
void SleepSession::printMeasurements()
{
    for (int i = 0; i < measurementCount; i++)
    {
        Serial.print("Measurement ");
        Serial.println(i);

        Serial.print("Temprerature: ");
        if (measurements[i].hasTemperature)
        {
            Serial.println(measurements[i].temperature);
        }
        else
        {
            Serial.println("N/A");
        }
        Serial.print("Humidity: ");
        if (measurements[i].hasHumidity)
        {
            Serial.println(measurements[i].humidity);
        }
        else
        {
            Serial.println("N/A");
        }
        Serial.print("Light: ");
        if (measurements[i].hasLight)
        {
            Serial.println(measurements[i].light);
        }
        else
        {
            Serial.println("N/A");
        }
        Serial.println("------------------");
    }
}