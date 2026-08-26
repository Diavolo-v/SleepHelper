#include "sleep_score.h"
SleepScore::SleepScore()
{
    score = 0;
}
int SleepScore::calculateSleepDuration(int hours)
{
    if (hours < 4)
    {
        return 0;
    }
    if (hours <= 5)
    {
        return 4;
    }
    if (hours <= 6)
    {
        return 8;
    }
    if (hours <= 7)
    {
        return 12;
    }
    if (hours <= 9)
    {
        return 15;
    }
    if (hours <= 10)
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

int SleepScore::calculateTotalScore(int avgTemp, int avgHum)
{
    int total = 0;

    total += calculateTemperature(avgTemp);
    total += calculateHumidity(avgHum);

    return total;
}

int SleepScore::returnTotalScore()
{
    return score;
}