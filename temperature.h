#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include "device.h"

class Temperature : public Device
{
public:
    Temperature(const QString &name);
    bool getCurrentTemp();

private:
    //int temp;
};

#endif // TEMPERATURE_H
