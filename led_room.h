#ifndef LED_ROOM_H
#define LED_ROOM_H

#include "device.h"

class Led_Room : public Device
{
public:
    Led_Room(const QString &name);
};

#endif // LED_ROOM_H
