#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "mainwindow.h"
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_pushButton_Login_clicked()
{
    //登录按钮底色变绿
    ui->pushButton_Login->setStyleSheet("#pushButton_Login{\
     background-color: rgb(0, 193, 93);\
     border-style: inset;\
     border-width: 3px;\
     border-radius: 10px;\
     border-color: rgb(0, 255, 255);\
     color: rgb(0, 255, 127);}");

#ifdef PROJECT_DEBUG
    QString user = "6602190210";
    QString password = "123456";
    QString ip = "192.168.0.15";
    QString port = "7777";
#else
    //获取登录界面输入的信息
    QString user = ui->lineEdit_UserId->text();
    QString password = ui->lineEdit_UserPassword->text();
    QString ip = ui->lineEdit_IP->text();
    QString port = ui->lineEdit_PortNum->text();
#endif
    //核对登录界面输入的信息
    if(user.isEmpty() || password.isEmpty() || ip.isEmpty() || port.isEmpty()){
        QMessageBox msgBox;
        msgBox.warning(this, "缺少内容","用户、密码、IPv4地址、端口号都必须填写!",QMessageBox::Yes);
        if(msgBox.exec() == QMessageBox::Ok){
             //登录按钮底色透明
            ui->pushButton_Login->setStyleSheet("#pushButton_Login{background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.506, stop:0 rgba(255, 255, 255, 100));border-style: inset;border-width: 3px;border-radius: 10px;border-color: rgb(0, 255, 255);color: rgb(0, 255, 127);}");
            return;
        }
    }
    else if((user.compare("6602190210") != 0) || (password.compare("123456") != 0)){
        QMessageBox msgBox;
        msgBox.warning(this,"内容错误","用户名或密码错误，请重新填写!",QMessageBox::Yes);
        if(msgBox.exec() == QMessageBox::Ok){
           //登录按钮底色透明
           ui->pushButton_Login->setStyleSheet("#pushButton_Login{background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.506, stop:0 rgba(255, 255, 255, 100));border-style: inset;border-width: 3px;border-radius: 10px;border-color: rgb(0, 255, 255);color: rgb(0, 255, 127);}");
           return;
        }
    }
    //核对正确,开启主界面
    MainWindow *w = new MainWindow(ip, port.toInt());
    w->show();
    this->close();
}
