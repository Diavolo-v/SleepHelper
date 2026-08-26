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
    int calculateLightExposure(float averageLight);
    int calculateNoiseExposure();
    int calculateTemperature(float averageTemp);
    int calculateHumidity(float averageHumidity);
    int calculatePhoneUsageBeforeBed();
    int calculateCarbonDioxide();
    int phoneLeftonDevice();
    int userOpinionOnSleep();
    int calculateTotalScore(int avgTemp, int avgHum);
    int returnTotalScore();
};

#endif