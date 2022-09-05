#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

//#include <QWidget>
#include <QDialog>

#define PROJECT_DEBUG


namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();

private slots:
    void on_pushButton_Login_clicked();

private:
    Ui::LoginWindow *ui;
};

#endif // LOGINWINDOW_H
