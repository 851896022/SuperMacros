#ifndef FINDKILL_H
#define FINDKILL_H

#include <QObject>
#include <QThread>
#include <QList>

#include <QGuiApplication>
#include <QRect>
#include "global.h"
#include <QBitArray>
#include <QPixmap>
class FindKill : public QThread
{
    Q_OBJECT
public:
    explicit FindKill(QThread *parent = nullptr);
    QRect rect;
    QImage image;
signals:

public slots:
    void initTHis();
    void run();

};

#endif // FINDKILL_H
