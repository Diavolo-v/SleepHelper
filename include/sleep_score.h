#ifndef SLEEP_SCORE
#define SLEEP_SCORE

class SleepScore
{
private:
    int score;

public:
    SleepScore();
    int calculateSleepDuration(int hours);
    int calculateSleepSchedule();
    int calculateLightExposure();
    int calculateNoiseExposure();
    int calculateTemperature();
    int calculateHumidity();
    int calculatePhoneUsageBeforeBed();
    int calculateCarbonDioxide();
    int phoneLeftonDevice();
    int userOpinionOnSleep();
    int calculateTotalScore();
    int returnTotalScore();
};

#endif