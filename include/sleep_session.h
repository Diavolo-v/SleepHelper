#ifndef SLEEO_SESSION
#define SLEEP_SESSION
#include "sensors.h"
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

class SleepSession
{
private:
    SleepSessionState state;
    Time startTime;
    Time endTime;

    unsigned long lastEnvironmentMeasurement;
    unsigned long lastLightMeasurement;
    unsigned long lastNoiseMasurement;
    unsigned long lastCo2Measurement;

    const unsigned long envionmentalInterval = 30UL * 60UL * 1000UL;
    const unsigned long lightInterval = 5UL * 60UL * 1000UL;
    const unsigned long noiseInterval = 5UL * 60UL * 1000UL;
    const unsigned long co2Interval = 5UL * 60UL * 1000UL;

public:
    SleepSession();
    void update(const SensorData &data);
    void start(int hours, int minutes, int seconds);
    void end(int hours, int minutes, int seconds);
    bool isActive();
};

#endif