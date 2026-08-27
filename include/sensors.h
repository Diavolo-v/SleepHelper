#ifndef SENSORS
#define SENSORS

struct SensorData
{
    float temperature;
    float humidity;
    int light;
    int noise;
    int co2;
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

    bool hasCO2;
    int CO2;

    bool hasNoise;
    int noise;
};
#endif
