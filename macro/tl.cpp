#include "tl.h"

TL::TL(QObject *parent) : QObject(parent)
{
    timer= new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(onTimeOut()));
}
void TL::onTimeOut()
{
    if(g->mNoBuff(3192)) g->sendCache.append((char)0x60);
}
void TL::control()
{
    if(timer->isActive())
    {
        timer->stop();
    }
    else
    {
        timer->start(1000);
    }
}
