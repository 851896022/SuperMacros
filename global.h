#ifndef GLOBAL_H
#define GLOBAL_H

#include <QObject>
#include <QString>
#include <QDir>
#include <QFile>
#include <QTimer>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QRect>
#include <QVariant>
#include <QPixmap>
#include <QStringList>
#include <QMap>
#include <QPoint>
class GLobal : public QObject
{

    Q_OBJECT
public:
    explicit GLobal(QObject *parent = nullptr);
    ~GLobal();
    QStringList keyNameList;
    QList<int> keyNoList;
    QStringList comNameList;
    QSerialPort *serialPort=NULL;
    QList<char> sendCache;
    QTimer sendTimer;
    int temp=600;
    //窗口
    bool isWindowOk=false;
    QWindow *w;
    QPoint mDev;
    QPoint tDev;
    QRect mHp;
    QPixmap buffImgCacheMy[12];
    QPixmap buffImgCacheT[12];
    QPixmap hpImgCacheMy;
    QPixmap killImgCache;
    //技能
    QRect windowRect;
    QRect myBuffRect[12];
    QRect targetBuffRect[12];
    int myBuffID[12];
    int targetBuffID[12];
    QList<QVariant> buffDb;
    QStringList buffName;
    QPixmap nowScreen;
    QMap<QString,int> buffNameMap;
    //血量
    int maxHP;
    int nowHP;
    QRect hpRect;
    QList<QVariant> numDb;
    //宏
    QString macro;
    //技能
    QRect killRect;

signals:

public slots:
    bool startLink(QString name);
    void onReceived();
    void sendData();
    bool tNoBuff(int id);
    bool tBuff(int id);
    bool mNoBuff(int id);
    bool mBuff(int id);
    float perHP();//百分比血量
};
extern GLobal *g;
#endif // GLOBAL_H
