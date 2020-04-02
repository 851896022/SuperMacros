#ifndef FINDICON_H
#define FINDICON_H

#include <QObject>
#include <QThread>
#include <QList>

#include <QGuiApplication>
#include <QRect>
#include "global.h"
#include <QBitArray>
#include <QPixmap>
class FindIcon : public QThread
{
    Q_OBJECT
public:
    explicit FindIcon(QThread *parent = nullptr);
    bool isMy=true;
    int No=0;
    QRect rect;

signals:

public slots:
    void run();
    void initThis(int No);
};

#endif // FINDICON_H
