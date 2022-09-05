#ifndef HUMIDITY_H
#define HUMIDITY_H

#include <QObject>
#include "servercommunication.h"

class Humidity : public QObject
{
    Q_OBJECT
public:
    explicit Humidity(const QString &name);

signals:

public slots:
    bool getCurrentHumidityValue();
private:
    QString name;
    ServerCommunication *server;
};

#endif // HUMIDITY_H
