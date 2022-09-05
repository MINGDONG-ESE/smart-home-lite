#include "temperature.h"
#include "debug.h"

Temperature::Temperature(const QString &name)
    :Device(name)
{

}

bool Temperature::getCurrentTemp()
{
    qDebug() << "getCurrentTemp";
    //向服务器发送获取请求，服务器反馈温度数据
    QString msg = this->name + " temp";
    qDebug() << msg;
    bool ok = this->server->sendToServer(msg);
    if(ok){
        return true;
    }
    return false;
}
