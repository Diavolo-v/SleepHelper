#ifndef SENSOR_MANAGER
#define SENSOR_MANAGER
#include "sensors.h"
class SensorManager
{
private:
    SensorData currentData;

public:
    SensorManager();
    void update();
    SensorData getCurrentData();
};

#endif
