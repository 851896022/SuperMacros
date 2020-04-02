#ifndef TEST_H
#define TEST_H

#include <QObject>
#include <QBitArray>
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <QImage>
#include <QRgb>
#include <QBitArray>
#include <QDir>
#include <QList>
#include <QSettings>
#include <QVariant>
//#include "global.h"
class test : public QObject
{
    Q_OBJECT
public:
    explicit test(QObject *parent = nullptr);

signals:

public slots:
    void buff();
    void num();
};

#endif // TEST_H
