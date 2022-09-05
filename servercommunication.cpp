#include "servercommunication.h"
#include "debug.h"

ServerCommunication *ServerCommunication::serverCommunication = NULL;

ServerCommunication::ServerCommunication(const QString &ip, const quint16 &port)
{
    this->tcp = new QTcpSocket;
    this->tcp->connectToHost(ip, port);
    bool ok = this->tcp->waitForConnected(2000); //超时检测
    if(!ok){
        qDebug() << "connect server fail!";
    }
    //QTcpSocket类的信号函数readyRead()与ServerCommunication类的槽函数recvFromServer()相连
    connect(this->tcp, SIGNAL(readyRead()), this, SLOT(recvFromServer()));

}

ServerCommunication *ServerCommunication::setServerCommunication(const QString &ip, const quint16 &port)
{
    if(serverCommunication == NULL){
        serverCommunication = new ServerCommunication(ip, port);
    }

    return serverCommunication;
}

ServerCommunication *ServerCommunication::getServerCommunication()
{
    if(serverCommunication == NULL){
        qDebug() << "no server communication";
    }
    return serverCommunication;
}

bool ServerCommunication::sendToServer(const QString &msg)
{
    qDebug() << "sendToServer";
    qint64 len = msg.size();
    qDebug() << msg.toStdString().c_str();
    QString buf(msg);
    int res = this->tcp->write(buf.toStdString().c_str(), len);
    if(res == -1){
        qDebug() << "write data fail!";
    }
    this->tcp->flush();
    qDebug() << "write end" ;
    return true;

}

void ServerCommunication::messageHandle(const QString &msg)
{
    QString buf(msg);
    QStringList list = buf.split(" ");//将字符串通过 “ ” 拆分为 多个字符
    if(list.value(0) == "message"){
        QString contect = buf.mid(8);
        qDebug() << contect;
        emit recvMessage(contect);//向mainWindow 发信号显示信息
    }
    else if(list.value(0) == "temp"){
        int temp = buf.mid(5).toInt();  //字符串型数值转化为整型数值
        qDebug() << temp;
        emit recvTemp(temp);//向mainWindow 发信号显示温度
    }
    else if(list.value(0) == "hum"){    //hum<空格><数据>
        int hum = buf.mid(4).toInt();
        qDebug() << hum;
        emit recvHum(hum);//向mainWindow 发信号显示湿度
    }

}

void ServerCommunication::recvFromServer()
{
    QByteArray buf = this->tcp->readAll();//读取服务器发送过来的数据包
    QString recv_buf = QString::fromUtf8(buf);//数据包编码转换
    messageHandle(recv_buf);//解析服务器发送过来的数据包
    qDebug() << recv_buf.toStdString().c_str();//qDebug() 打印中文乱码问题
}
