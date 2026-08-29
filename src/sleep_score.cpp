#include "sleep_score.h"
#include <Arduino.h>
SleepScore::SleepScore()
{
    score = 0;
}
int SleepScore::calculateSleepDuration(float time)
{
    if (time < 4)
    {
        return 0;
    }
    if (time <= 5)
    {
        return 4;
    }
    if (time <= 6)
    {
        return 8;
    }
    if (time <= 7)
    {
        return 12;
    }
    if (time <= 9)
    {
        return 15;
    }
    if (time <= 10)
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

int SleepScore::calculateTotalScore(const Summary &summary)
{

    int total = 0;

    Serial.println(summary.durationHours);

    total += calculateSleepDuration(summary.durationHours);

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