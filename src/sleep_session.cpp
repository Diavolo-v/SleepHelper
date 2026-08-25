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
    lastNoiseMasurement = millis();
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
    endTime.seconds = minutes;
    state = FINISHED;
}
void SleepSession::update(const SensorData &data)
{
    if (state != RUNNING)
    {
        return;
    }
    unsigned long currentTime = millis();

    if (currentTime - lastEnvironmentMeasurement > envionmentalInterval)
    {

        lastEnvironmentMeasurement = currentTime;
    }

    if (currentTime - lastLightMeasurement > lightInterval)
    {
        lastLightMeasurement = currentTime;
    }
    if (currentTime - lastNoiseMasurement > noiseInterval)
    {
        lastNoiseMasurement = currentTime;
    }
    if (currentTime - lastCo2Measurement > co2Interval)
    {
        lastCo2Measurement = currentTime;
    }
}

bool SleepSession::isActive()
{
    return state == RUNNING;
}