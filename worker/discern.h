#ifndef DISCERN_H
#define DISCERN_H

#include <QObject>
#include "findicon.h"
#include "QTimer"
#include <QScreen>
#include "findhp.h"
class Discern : public QObject
{
    Q_OBJECT
public:
    explicit Discern(QObject *parent = nullptr);
    FindIcon *findIcon[24];
    FindHp *findHp;
    QTimer *timer;
    QList<QScreen *> list_screen;
signals:

public slots:
    void onTimerOut();
};

#endif // DISCERN_H
