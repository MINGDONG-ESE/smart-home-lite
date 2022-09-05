#include <QApplication>


#include "loginwindow.h"

//#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginWindow lw;
    lw.show();/*显示登录界面*/

  //MainWindow w;
  //w.show();

    return a.exec();
}
