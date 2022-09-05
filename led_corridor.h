#ifndef LED_CORRIDOR_H
#define LED_CORRIDOR_H

#include "device.h"

class Led_Corridor : public Device
{
public:
    Led_Corridor(const QString &name);
};

#endif // LED_CORRIDOR_H
