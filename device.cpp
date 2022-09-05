#include "device.h"
#include "debug.h"

Device::Device(const QString &name)
{
    //初始化工作
    this->server = ServerCommunication::getServerCommunication();//获取通讯对象的地址
    this->name = name;

    this->level = "**";
    /* 调整等级划分
    0 ""
    1 "**"
    2 "****"
    3 "******"
    */
    //设备默认为关
    this->isOpen = false;
}

bool Device::open()
{
    qDebug() << this->name << " open!";
    //向服务器上传打开指令
    QString msg = this->name + " open";
    bool ok = this->server->sendToServer(msg);
    if(ok){
        this->isOpen = true;
        return true;
    }
    else{
        return false;
    }

}

bool Device::close()
{
    qDebug() << this->name << " close!";
    //向服务器上传关闭指令
    QString msg = this->name + " close";
    bool ok = this->server->sendToServer(msg);
    if(ok){
        this->isOpen = false;
        return true;
    }
    else{
        return false;
    }
}

bool Device::adjust(int num)
{
    switch (num) {
    case 1:
        adjust("**");
        break;
    case 2:
        adjust("****");
        break;
    case 3:
        adjust("******");
        break;
    default:
        return false;
    }
    return true;
}

bool Device::adjust(const QString &level)
{
    this->level = level;
    qDebug() << this->name << " adjust " << this->level;
    //向服务器上传调整指令
    QString msg = this->name + " adjust " + this->level;
    bool ok = this->server->sendToServer(msg);
    if(ok){
        return true;
    }
    else{
        return false;
    }
}

bool Device::getIsOpen()const
{
    return isOpen;
}
