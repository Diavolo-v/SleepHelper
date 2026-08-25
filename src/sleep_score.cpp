#include "sleep_score.h"

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
    if (hours > 10)
    {
        return 8;
    }
}
int SleepScore::calculateTotalScore()
{
    int total = 0;

    // total += calculateSleepDuration();

    return total;
}

int SleepScore::returnTotalScore()
{
    return score;
}