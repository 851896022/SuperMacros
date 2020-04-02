#include "findgamewindow.h"
#include <windows.h>
FindGameWindow::FindGameWindow(QObject *parent) : QObject(parent)
{
    connect(&timer,SIGNAL(timeout()),this,SLOT(onTimerOut()));
    timer.start(10000);
    onTimerOut();
}
void FindGameWindow::onTimerOut()
{
    HWND hq=FindWindow("KGWin32App",NULL);
    RECT rect;
    rect.left=0;
    rect.top=0;
    rect.right=1920;
    rect.bottom=1080;
    if(GetWindowRect(hq,&rect))
    {
        g->isWindowOk=true;
    }
    else
    {
        g->isWindowOk=false;
    }
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
    g->hpRect.setRect(x+100,y+53,194,12);
}
