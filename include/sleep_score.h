#ifndef SLEEP_SCORE
#define SLEEP_SCORE
#include "sleep_session.h"
class SleepScore
{
private:
    int score;

public:
    SleepScore();
    int calculateSleepDuration(float time);
    int calculateSleepSchedule();
    int calculateLightExposure(float averageLight);
    int calculateNoiseExposure();
    int calculateTemperature(float averageTemp);
    int calculateHumidity(float averageHumidity);
    int calculatePhoneUsageBeforeBed();
    int calculateCarbonDioxide();
    int phoneLeftonDevice();
    int userOpinionOnSleep();
    int calculateTotalScore(const Summary &summary);
    int returnTotalScore();
};

#endif