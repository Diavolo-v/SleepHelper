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
    const unsigned long noiseInterval = 5UL * 60UL * 1000UL;
    const unsigned long co2Interval = 5UL * 60UL * 1000UL;

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
    int getSleepDurationSeconds();
    float getTotalSleepDuration();
    void calculateSummary();
    Summary getSummary();
};
