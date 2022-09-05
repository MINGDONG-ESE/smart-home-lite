#include "humidity.h"
#include "debug.h"
Humidity::Humidity(const QString &name)
{
    this->name = name;
    this->server= ServerCommunication::getServerCommunication();
}

bool Humidity::getCurrentHumidityValue()
{
//    qDebug() << " 老弟准备查看你的家居环境的湿度值吧！";
    qDebug() << " get current humidity value! ";
    //向服务器发送获取请求，服务器反馈湿度数据
    QString msg = this->name + " hum";
    qDebug() << msg;
    bool ok = this->server->sendToServer(msg);
    if(ok){
        return true;
    }
    return false;
}
