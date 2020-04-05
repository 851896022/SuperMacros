#include "findgamewindow.h"
#include <windows.h>
#include "global.h"
FindGameWindow::FindGameWindow(QObject *parent) : QObject(parent)
{
    connect(&timer,SIGNAL(timeout()),this,SLOT(onTimerOut()));
    timer.start(10000);
    onTimerOut();
}
#include <QWidget>
#include <QWindow>
#include <QScreen>
#include <QPixmap>
void FindGameWindow::onTimerOut()
{
    HWND hq=FindWindow("KGWin32App",NULL);
    g->w=QWindow::fromWinId((WId)hq);
    if(g->w==NULL)
    {
        g->isWindowOk=false;
    }
    else
    {
        g->isWindowOk=true;
    }
}
