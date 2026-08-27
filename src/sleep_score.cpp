#include "sleep_score.h"
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

int SleepScore::calculateTotalScore(const Summary &summary)
{
    int total = 0;
    total += calculateSleepDuration(summary.durationHours);
    if (summary.hasTemperature)
    {
        total += calculateTemperature(summary.averageTemp);
    }
    if (summary.hasHumidity)
    {
        total += calculateHumidity(summary.averageHum);
    }
    // if (summary.hasLight)
    // {
    //     total += calculateLightExposure(summary.averageLight);
    // }

    score = total;
    return total;
}

int SleepScore::returnTotalScore()
{
    return score;
}