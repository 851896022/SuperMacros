#include "discern.h"
#include <QDateTime>
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
    findHp->initTHis();

    findKill = new FindKill;
    findKill->initTHis();

    timer->start(480);
    list_screen =  QGuiApplication::screens(); //可能电脑接了多个屏幕
}
#include "QPixmap"
#include <QApplication>
#include <QWindow>
void Discern::onTimerOut()
{


    g->nowScreen=g->w->screen()->grabWindow(g->w->winId());
    g->nowScreen.save("A:/sss.bmp");
    int w=g->nowScreen.width();
    int h=g->nowScreen.height();
    float stdScale = 4.0/3.0;
    float nowScale = (w*1.0)/(h*1.0);
    float scale ;
    if(nowScale>stdScale)//宽了，以高为准
    {
        scale = (h*1.0)/(1080.0);
    }
    else//窄了，以宽为准
    {
        scale = (w*1.0)/(1440.0);
    }
    g->hpRect.setRect(100*scale+g->mHp.x(),52*scale+g->mHp.y(),190*scale+g->mHp.width(),12*scale+g->mHp.height());
    for(int i=0;i<12;i++)
    {
        g->myBuffRect[i].setRect((w/2)-307+g->mDev.x()+(48*i),(h/2)-128+g->mDev.y(),42,42);
        g->targetBuffRect[i].setRect((w/2)-109+g->tDev.x()+(48*i),(h/2)+53+g->tDev.y(),42,42);
    }
    //---------技能-------------

        int kx;
        int ky;
        int kw;
        int kh;
        ky=h-(198*scale);
        kh=44*scale;
        kw=683*scale;
        kx=(w/2)-(kw/2)+(24*scale);


    g->killRect.setRect(kx,ky,kw,kh);







#ifdef asdlkjasf
    int x=(int)rect.left+8;
    int y=(int)rect.top+32;
    int w=(int)(rect.right-rect.left)-17;
    int h=(int)(rect.bottom-rect.top)-41;
    g->windowRect.setRect(x,y,w,h);
    //g->myBuffRect[0].setRect(x+653,y+413,42,42);
    //g->targetBuffRect[0].setRect(x+1079,y+594,42,42);
    for(int i=0;i<12;i++)
    {
        g->myBuffRect[i].setRect(x+653+(48*i),y+413,42,42);
        g->targetBuffRect[i].setRect(x+1079+(48*i),y+594,42,42);
    }

#endif











    //刷新坐标
    for(int i=0;i<24;i++)
    {
        findIcon[i]->initThis(i);
    }
    findHp->initTHis();
    findKill->initTHis();

    if(!g->isWindowOk)
    {
        return;
    }
    //WId ss = 0;
    // = list_screen.at(0)->grabWindow(0,0,0,g->targetBuffRect[11].x()+45,g->targetBuffRect[11].y()+45);
    //g->nowScreen=list_screen.at(0)->grabWindow(qApp->desktop().winId());
    findHp->start();
    findKill->start();
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
