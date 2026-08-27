#pragma once
#include "sensors.h"
#define MAX_MEASUREMENTS 100
enum SleepSessionState
{
    IDLE,
    RUNNING,
    FINISHED
};
struct Time
{
    int hours;
    int minutes;
    int seconds;
};
struct Summary
{
    float durationHours;
    float averageTemp;
    float averageHum;
    float averageLight;
    float averageCO2;
    float averageNoise;

    bool hasTemperature;
    bool hasHumidity;
    bool hasLight;
    bool hasCO2;
    bool hasNoise;
};

class SleepSession
{
private:
    SleepSessionState state;
    Summary summary;
    Time startTime;
    Time endTime;
    Measurement measurements[MAX_MEASUREMENTS];
    int measurementCount = 0;
    bool hasNewMeasurement = false;

    unsigned long lastEnvironmentMeasurement;
    unsigned long lastLightMeasurement;
    unsigned long lastNoiseMeasurement;
    unsigned long lastCo2Measurement;

    const unsigned long environmentalInterval = 10000;
    const unsigned long lightInterval = 3000;
    const unsigned long noiseInterval = 3000;
    const unsigned long co2Interval = 3000;

public:
    SleepSession();
    void update(const SensorData &data);
    void start(int hours, int minutes, int seconds);
    void end(int hours, int minutes, int seconds);
    bool isActive();
    void printMeasurements();
    bool newMeasurement();
    float getAverageTemperature();
    float getAverageHumidity();
    float getAverageLight();
    float getAverageCO2();
    float getAverageNoise();
    int getSleepDurationSeconds();
    float getTotalSleepDuration();
    void calculateSummary();
    Summary getSummary();
};
