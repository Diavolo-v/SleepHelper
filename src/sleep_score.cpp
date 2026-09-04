#include "sleep_score.h"
#include <Arduino.h>
SleepScore::SleepScore()
{
    score = 0;
}
int SleepScore::calculateSleepDuration(float time, int sleepGoal)
{
    float ratio = time / (sleepGoal / 60.0);

    if (ratio < 0.5)
    {
        return 0;
    }

    if (ratio < 0.625)
    {
        return 4;
    }

    if (ratio < 0.75)
    {
        return 8;
    }

    if (ratio < 0.875)
    {
        return 12;
    }

    if (ratio <= 1.125)
    {
        return 15;
    }

    if (ratio <= 1.25)
    {
        return 12;
    }

    return 8;
}

int SleepScore::calculateTemperature(float averageTemp)
{
    if (averageTemp < 15)
    {
        return 5;
    }
    if (averageTemp <= 19)
    {
        return 10;
    }
    if (averageTemp < 21)
    {
        return 3;
    }

    return 1;
}

int SleepScore::calculateHumidity(float averageHumidity)
{
    if (averageHumidity < 30)
    {
        return 1;
    }
    if (averageHumidity <= 50)
    {
        return 8;
    }
    if (averageHumidity <= 60)
    {
        return 6;
    }
    return 1;
}
// int SleepScore::calculateLightExposure(float averageLight)
// {
// }
int SleepScore::calculateCarbonDioxide(float averageCO2)
{
    if (averageCO2 <= 800)
    {
        return 8;
    }
    if (averageCO2 <= 1000)
    {
        return 6;
    }
    if (averageCO2 <= 1200)
    {
        return 4;
    }
    if (averageCO2 <= 1500)
    {
        return 2;
    }
    return 0;
}
int SleepScore::calculateNoiseExposure(float averageNoise)
{
    if (averageNoise <= 30)
    {
        return 12;
    }
    if (averageNoise <= 35)
    {
        return 10;
    }
    if (averageNoise <= 40)
    {
        return 8;
    }
    if (averageNoise <= 45)
    {
        return 5;
    }
    if (averageNoise <= 50)
    {
        return 2;
    }
    return 0;
}

int SleepScore::calculateTotalScore(const Summary &summary, int sleepGoal)
{

    int total = 0;

    Serial.println(summary.durationHours);

    total += calculateSleepDuration(summary.durationHours, sleepGoal);

    if (summary.hasTemperature)
    {
        total += calculateTemperature(summary.averageTemp);
    }

    if (summary.hasHumidity)
    {
        total += calculateHumidity(summary.averageHum);
    }

    if (summary.hasLight)
    {
    }

    if (summary.hasCO2)
    {
        total += calculateCarbonDioxide(summary.averageCO2);
    }

    if (summary.hasNoise)
    {
        total += calculateNoiseExposure(summary.averageNoise);
    }

    score = total;

    return total;
}

int SleepScore::returnTotalScore()
{
    return score;
}