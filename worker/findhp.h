#ifndef FINDHP_H
#define FINDHP_H


#include <QObject>
#include <QThread>
#include <QList>

#include <QGuiApplication>
#include <QRect>
#include "global.h"
#include <QBitArray>
#include <QPixmap>
class FindHp : public QThread
{
    Q_OBJECT
public:
    explicit FindHp(QThread *parent = nullptr);
    QRect rect;
    QImage image;
signals:

public slots:
    void initTHis();
    void run();
    bool lineIsHaveColor(int y);
    int imageToNumber(QImage img);
};

#endif // FINDHP_H
