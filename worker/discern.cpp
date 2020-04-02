#include "discern.h"

Discern::Discern(QObject *parent) : QObject(parent)
{
    timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(onTimerOut()));
    for(int i=0;i<24;i++)
    {
        findIcon[i]=new FindIcon;
        findIcon[i]->initThis(i);
    }


    findHp = new FindHp;


    timer->start(480);
    list_screen =  QGuiApplication::screens(); //可能电脑接了多个屏幕
}
void Discern::onTimerOut()
{

    if(!g->isWindowOk)
    {
        return;
    }
    g->nowScreen = list_screen.at(0)->grabWindow(0,0,0,g->targetBuffRect[11].x()+45,g->targetBuffRect[11].y()+45);
    findHp->start();
    for(int i=0;i<24;i++)
    {
        findIcon[i]->start();
    }
    /*
    qDebug()<<g->buffDb.count()<<g->numDb.count();
    qDebug()<<"m"<<g->myBuffID[0]
           <<g->myBuffID[1]
                <<g->myBuffID[2]
                  <<g->myBuffID[3]
                    <<g->myBuffID[4]
                      <<g->myBuffID[5]
                        <<g->myBuffID[6]
                          <<g->myBuffID[7]
                            <<g->myBuffID[8]
                              <<g->myBuffID[9]
                                <<g->myBuffID[10]
                                    <<g->myBuffID[11]
                                   <<g->nowHP
                                  <<g->maxHP;
    qDebug()<<"t"<<g->targetBuffID[0]
              <<g->targetBuffID[1]
                <<g->targetBuffID[2]
                  <<g->targetBuffID[3]
                    <<g->targetBuffID[4]
                      <<g->targetBuffID[5]
                        <<g->targetBuffID[6]
                          <<g->targetBuffID[7]
                            <<g->targetBuffID[8]
                              <<g->targetBuffID[9]
                                <<g->targetBuffID[10]
                                    <<g->targetBuffID[11];
                                    */
}
