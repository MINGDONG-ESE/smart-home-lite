#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(const QString &ip, quint16 port, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //设置控件属性
    //设置卧室灯滑动条
    ui->adjust_led_room->setMinimum(0);
    ui->adjust_led_room->setMaximum(3);
    ui->adjust_led_room->setSingleStep(1);
    //设置走廊灯滑动条
    ui->adjust_led_corridor->setMinimum(0);
    ui->adjust_led_corridor->setMaximum(3);
    ui->adjust_led_corridor->setSingleStep(1);
    //设置温度显示
    ui->lcdNumber_temperature->setDecMode();//以十进制数进行显示
    ui->lcdNumber_temperature->setDigitCount(3);
    ui->lcdNumber_temperature->setSegmentStyle(QLCDNumber::Flat);//设置内容显示样式偏平
    //设置湿度显示
    ui->lcdNumber_humidity->setDecMode();//以十进制数进行显示
    ui->lcdNumber_humidity->setDigitCount(3);
    ui->lcdNumber_humidity->setSegmentStyle(QLCDNumber::Flat);//设置内容显示样式偏平

    //显示屏幕初始化
    this->model = new QStandardItemModel(this); //需要model,创建model
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置屏幕只读
    this->isOpen_getTempPushButton = false;
    this->isOpen_upTempAirConditioner = false;
    this->isOpen_downTempAirConditioner = false;

    //创建通讯模块
    this->serverCommunication = ServerCommunication::setServerCommunication(ip, port);

    //设备列表
    this->led_room = new Led_Room("led_room");
    this->led_corridor = new Led_Corridor("led_corridor");
    this->temperature = new Temperature("temperature");
    this->air_conditioner = new Air_Conditioner("air_conditioner");
    this->humidity = new Humidity("humidity");

    // 连接信号与槽
    //实现MainWindow类中的信号函数getHumidityValue() 与Humidity类中的槽函数getCurrentHumidityValue()相连
    connect(this,SIGNAL(getHumidityValue()),this->humidity,SLOT(getCurrentHumidityValue()));

    connect(this->serverCommunication, SIGNAL(recvMessage(QString)), this, SLOT(showRecvMessage(QString)));
    connect(this->serverCommunication, SIGNAL(recvTemp(int)), this, SLOT(showRecvTemp(int)));
    connect(this->serverCommunication, SIGNAL(recvHum(int)), this, SLOT(showRecvHum(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showRecvMessage(const QString &msg)
{
    showMessage(msg);
}

void MainWindow::showRecvTemp(const int temp)
{
    ui->lcdNumber_temperature->display(temp);
    if(temp > 20){
        ui->lineEdit_status->setText(QStringLiteral("温度过高"));
    }else{
        ui->lineEdit_status->setText(QStringLiteral("温度正常"));
    }
}

void MainWindow::showRecvHum(const int hum)
{
    ui->lcdNumber_humidity->display(hum);
}


void MainWindow::showMessage(const QString &msg)
{
    QStandardItem *item = new QStandardItem(msg);
    this->model->insertRow(0,item);//在屏幕的第一行插入消息，保证最新消息置顶
    ui->listView->setModel(this->model);//更新屏幕内容
}

void MainWindow::on_pushButton_led_room_clicked()
{
    if(this->led_room->getIsOpen() == false){  //开卧室灯
        qDebug() << "button led room on";
        ui->pushButton_led_room->setStyleSheet("border-image: url(:/img/switch_on.png);");
        this->led_room->open();//向服务器上传led_room open
        showMessage(QStringLiteral("房间的灯打开了，温馨且浪漫！"));
        //如果卧室灯亮度为0，那么亮度调整为1
        if(ui->adjust_led_room->value() == 0){
            ui->adjust_led_room->setValue(1);//将界面滑动条设置为1
            this->led_room->adjust("**");//向服务器上传，设置led_room的亮度为1
        }
    }
    else{   //关卧室灯
        qDebug() << "button led room off";
        ui->pushButton_led_room->setStyleSheet("border-image: url(:/img/switch_off.png);");
        this->led_room->close();/*向服务器上传led_room close*/
        showMessage(QStringLiteral("房间的灯关闭了，享受美好的黑夜！"));
        //如果卧室灯亮度不为0，那么亮度调整为0
        if(ui->adjust_led_room->value() != 0){
            ui->adjust_led_room->setValue(0);//将界面滑动条设置为0
            //this->led_room->adjust("");//向服务器上传，设置led_room的亮度为0
        }
    }

}

void MainWindow::on_adjust_led_room_valueChanged(int value)
{
    qDebug() << "led_room_value: " << QString::number(value);
    if(this->led_room->getIsOpen() == false){//如果卧室灯未开
        ui->adjust_led_room->setValue(0);//如果没开，滑条不允许滑动
    }
    else{//如果卧室灯已开
        if(ui->adjust_led_room->value() == 0){
            ui->pushButton_led_room->setStyleSheet("border-image: url(:/img/switch_off.png);");
            this->led_room->close();
            showMessage(QStringLiteral("亮度为0， 房间的灯被关闭！"));
        }
        else{//亮度不为0
            //向服务器上传，调整led_room的亮度
                this->led_room->adjust(ui->adjust_led_room->value());
                showMessage(QStringLiteral("调整房间的灯亮度为：")+QString::number(ui->adjust_led_room->value()));
            }
    }
}


void MainWindow::on_pushButton_led_corridor_clicked()
{
    if(this->led_corridor->getIsOpen() == false)
    {  //开走廊灯
        qDebug() << "button led corridor on";
        ui->pushButton_led_corridor->setStyleSheet("border-image: url(:/img/switch_on.png);");
        this->led_corridor->open();
         showMessage(QStringLiteral("走廊的灯打开了，光明回来了！"));

        //如果走廊灯亮度为0，那么亮度调整为1
        if(ui->adjust_led_corridor->value() == 0){
            ui->adjust_led_corridor->setValue(1);
            this->led_corridor->adjust("**"); // "**" = 1
        }
    }
    else
    {   //关走廊灯
        qDebug() << "button led corridor off";
        ui->pushButton_led_corridor->setStyleSheet("border-image: url(:/img/switch_off.png);");
        this->led_corridor->close();
        showMessage(QStringLiteral("走廊的灯关闭了，暗淡且忧伤！"));

        //如果走廊灯亮度不为0，那么亮度调整为0
        if(ui->adjust_led_corridor->value() != 0){
            ui->adjust_led_corridor->setValue(0);
            //this->led_corridor->adjust("");
        }
    }
}

void MainWindow::on_adjust_led_corridor_valueChanged(int value)
{
    qDebug() << "led_corridor_value: " << QString::number(value);//QString::number(value) : value translate "value"
    if(this->led_corridor->getIsOpen() == false)
    {//走廊灯未开
        ui->adjust_led_corridor->setValue(0);//禁止滑条移动
    }
    else
    {//走廊灯已开
        if(ui->adjust_led_corridor->value() == 0)
        {//滑条值为0时
            ui->pushButton_led_corridor->setStyleSheet("border-image: url(:/img/switch_off.png);");
            this->led_corridor->close();
        }
        else
        {//滑条值不为0时
            this->led_corridor->adjust(ui->adjust_led_corridor->value());
            showMessage(QStringLiteral("调整走廊的灯亮度为: ")+QString::number(ui->adjust_led_corridor->value()));
        }
    }
}

void MainWindow::on_pushButton_temperature_clicked()
{
    if(this->temperature->getIsOpen() == false)
    {
        qDebug() << "button temperature on";
        ui->pushButton_temperature->setStyleSheet("border-image: url(:/img/switch_on.png);");
        this->temperature->open();
        emit getHumidityValue(); //向Humidity类中的getCurrentHumidityValue()槽发送信号，并执行其函数
         showMessage(QStringLiteral("温控模块打开了"));
    }
    else
    {
        qDebug() << "button temperature off";
        ui->pushButton_temperature->setStyleSheet("border-image: url(:/img/switch_off.png);");
        this->temperature->close();
        showMessage(QStringLiteral("温控模块关闭了"));
        //红底
        ui->pushButton_getTemp->setStyleSheet("border-image: url(:/img/icons8_ubuntu_48px.png);background-color: rgb(170, 0, 0);");
        this->isOpen_getTempPushButton = false;

    }
}

//温控模块手动刷新温度
void MainWindow::on_pushButton_getTemp_clicked()
{
   if(this->temperature->getIsOpen() == true)
   {//温控模块已开
        //按钮底色红白切换，实现按钮动态效果
        if(this->isOpen_getTempPushButton == false)
        {//白底

            this->temperature->getCurrentTemp();//向服务器发送获取当前温度的请求

            ui->pushButton_getTemp->setStyleSheet("border-image: url(:/img/icons8_ubuntu_48px.png);background-color: rgb(255, 255, 255);");
            this->isOpen_getTempPushButton = true;
        }
        else
        {//红底
            ui->pushButton_getTemp->setStyleSheet("border-image: url(:/img/icons8_ubuntu_48px.png);background-color: rgb(170, 0, 0);");
            this->isOpen_getTempPushButton = false;
        }
   }

}

void MainWindow::on_pushButton_air_conditioner_clicked()
{
    if(this->air_conditioner->getIsOpen() == false)
    {
        qDebug() << "button air_conditioner on";
        ui->pushButton_air_conditioner->setStyleSheet("border-image: url(:/img/switch_on.png);");
        this->air_conditioner->open();
        showMessage(QStringLiteral("空调模块打开了"));
    }
    else
    {
        qDebug() << "button air_conditioner off";
        //空调加减温度按钮恢复原状
        ui->pushButton_up_temp_air_conditioner->setStyleSheet("border-image: url(:/img/key_up.png);");
        ui->pushButton_down_temp_air_conditioner->setStyleSheet("border-image: url(:/img/key_down.png);");
        ui->pushButton_air_conditioner->setStyleSheet("border-image: url(:/img/switch_off.png);");
        this->air_conditioner->close();
        showMessage(QStringLiteral("空调模块关闭了"));
    }
}

void MainWindow::on_pushButton_up_temp_air_conditioner_clicked()
{
    if(this->air_conditioner->getIsOpen() == true)
    {
        if(this->isOpen_upTempAirConditioner == false)
        {
            qDebug() << "up temp air conditioner";
            this->air_conditioner->tempUp();

            //按键变白
            ui->pushButton_up_temp_air_conditioner->setStyleSheet("border-image: url(:/img/key_up.png);background-color: rgb(255, 255, 255);");
            this->isOpen_upTempAirConditioner = true;
        }
        else
        {
            //按键保持原状
            ui->pushButton_up_temp_air_conditioner->setStyleSheet("border-image: url(:/img/key_up.png);");
            this->isOpen_upTempAirConditioner = false;
        }
    }
}

void MainWindow::on_pushButton_down_temp_air_conditioner_clicked()
{
    if(this->air_conditioner->getIsOpen() == true)
    {
        if(this->isOpen_downTempAirConditioner == false)
        {
            qDebug() << "down temp air conditioner";
            this->air_conditioner->tempDown();

            //按键变白
            ui->pushButton_down_temp_air_conditioner->setStyleSheet("border-image: url(:/img/key_down.png);background-color: rgb(255, 255, 255);");
            this->isOpen_downTempAirConditioner = true;
        }
        else
        {
            //按键保持原状
            ui->pushButton_down_temp_air_conditioner->setStyleSheet("border-image: url(:/img/key_down.png);");
            this->isOpen_downTempAirConditioner = false;
        }
    }
}
