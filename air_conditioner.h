#ifndef AIR_CONDITIONER_H
#define AIR_CONDITIONER_H

#include "device.h"
//#include "servercommunication.h"

class Air_Conditioner : public Device
{
public:
    Air_Conditioner(const QString &name);

    bool tempUp();
    bool tempDown();
private:
    //ServerCommunication *server;
    int temp;
};

#endif // AIR_CONDITIONER_H
