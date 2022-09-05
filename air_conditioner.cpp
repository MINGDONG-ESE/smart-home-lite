#include "air_conditioner.h"

Air_Conditioner::Air_Conditioner(const QString &name)
    :Device(name)
{
    //初始化
    this->temp =  20; //空调初始温度设置为20℃
    //this->server = ServerCommunication::getServerCommunication();
}

bool Air_Conditioner::tempUp()
{
    //向服务器上传加温指令
    QString msg = this->name + " up";
    bool ok = this->server->sendToServer(msg);
    if(ok){
        return true;
    }
    return false;
}

bool Air_Conditioner::tempDown()
{
    //向服务器上传降温指令
    QString msg = this->name + " down";
    bool ok = this->server->sendToServer(msg);
    if(ok){
        return true;
    }
    return false;
}
