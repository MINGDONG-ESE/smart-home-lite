#ifndef DEVICE_H
#define DEVICE_H

#include <QString>
#include "servercommunication.h"

class Device
{
public:
    Device(const QString &name);
    bool open();
    bool close();
    bool adjust(int num);
    bool adjust(const QString &level);
    bool getIsOpen()const;//const 关键字修饰成员函数，表示，函数内不允许修改成员变量的值

protected:
    ServerCommunication *server;
    QString name;
    QString level;
    bool isOpen;
};

#endif // DEVICE_H
