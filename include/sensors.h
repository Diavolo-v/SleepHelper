#ifndef SENSORS
#define SENSORS

struct SensorData
{
    float temperature;
    float humidity;
    int light;
    // float noise;
    // float co2;
};
struct Measurement
{
    unsigned long timeStamp;
    bool hasTemperature;
    float temperature;

    bool hasHumidity;
    float humidity;

    bool hasLight;
    int light;
};
#endif
