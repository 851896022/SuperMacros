#ifndef TL_H
#define TL_H

#include <QObject>
#include <QTimer>
#include "global.h"
class TL : public QObject
{
    Q_OBJECT
public:
    explicit TL(QObject *parent = nullptr);
    QTimer *timer;


signals:

public slots:
    void onTimeOut();
    void control();
};

#endif // TL_H
