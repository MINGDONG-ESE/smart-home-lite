#ifndef SERVERCOMMUNICATION_H
#define SERVERCOMMUNICATION_H

#include <QTcpSocket>
#include <QObject>

class ServerCommunication : public QObject
{
    Q_OBJECT
public:
    //使用c++设计模式：单例模式（整个代码只有一个对象，外界不允许额外创建对象）
    //3、定义一个静态成员方法，去获取内部创建的对象的地址
    static ServerCommunication *setServerCommunication(const QString &ip, const quint16 &port);
    static ServerCommunication *getServerCommunication();

    bool sendToServer(const QString &msg);
    void messageHandle(const QString &msg);

signals:
    void recvMessage(const QString &msg);
    void recvTemp(const int temp);
    void recvHum(const int hum);

public slots:
    void recvFromServer();

private:
    //1、将构造函数设置为私有权限，只有自己内部能创建对象
    ServerCommunication(const QString &ip, const quint16 &port);
    //2、定义当前类的对象指针
    static ServerCommunication *serverCommunication;

    QTcpSocket *tcp;//成员对象指针

};

#endif // SERVERCOMMUNICATION_H
