#-------------------------------------------------
#
# Project created by QtCreator 2020-03-23T08:57:31
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SmartHomeClient    #Windows下生成SmartHomeClient.exe , Linux下生成SmartHomeClient
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    device.cpp \
    led_room.cpp \
    led_corridor.cpp \
    air_conditioner.cpp \
    temperature.cpp \
    humidity.cpp \
    servercommunication.cpp \
    loginwindow.cpp \
    air_conditioner.cpp

HEADERS += \
        mainwindow.h \
    debug.h \
    device.h \
    led_room.h \
    led_corridor.h \
    air_conditioner.h \
    temperature.h \
    humidity.h \
    servercommunication.h \
    loginwindow.h \
    air_conditioner.h

FORMS += \
        mainwindow.ui \
    loginwindow.ui

RESOURCES += \
    rsc.qrc
