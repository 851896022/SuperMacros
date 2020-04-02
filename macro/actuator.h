#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <QThread>
#include <QObject>
#include <QTimer>
#include "global.h"
class Actuator : public QThread
{
    Q_OBJECT
public:
    explicit Actuator(QThread *parent = nullptr);
    QTimer *timer;
    QMap<QString,bool> boolMap;
signals:

public slots:
    void run();
    bool stringToBoolLine(QString str);
    bool stringToBoolLPoint(QString str);
    void control();
};

#endif // ACTUATOR_H
