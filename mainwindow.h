#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "debug.h"
#include "led_room.h"
#include "led_corridor.h"
#include "temperature.h"
#include "air_conditioner.h"
#include "humidity.h"
#include "servercommunication.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const QString &ip, quint16 port, QWidget *parent = 0);
    ~MainWindow();
    void showMessage(const QString &msg);

signals://指定下列为信号函数,信号函数只声明，不具体实现
    void getHumidityValue();

private slots:   //指定下列为槽函数,槽函数既要声明，也要具体实现
    void showRecvMessage(const QString &msg);
    void showRecvTemp(const int temp);
    void showRecvHum(const int hum);

    void on_pushButton_led_room_clicked();

    void on_adjust_led_room_valueChanged(int value);

    void on_pushButton_led_corridor_clicked();

    void on_adjust_led_corridor_valueChanged(int value);

    void on_pushButton_temperature_clicked();

    void on_pushButton_getTemp_clicked();

    void on_pushButton_air_conditioner_clicked();

    void on_pushButton_up_temp_air_conditioner_clicked();

    void on_pushButton_down_temp_air_conditioner_clicked();

private:
    bool isOpen_getTempPushButton;
    bool isOpen_upTempAirConditioner;
    bool isOpen_downTempAirConditioner;
    Led_Room *led_room;
    Led_Corridor *led_corridor;
    Temperature *temperature;
    Air_Conditioner *air_conditioner;
    QStandardItemModel *model;
    Humidity *humidity;
    ServerCommunication *serverCommunication;

    Ui::MainWindow *ui; //用于操作窗口界面的对象指针

};

#endif // MAINWINDOW_H
