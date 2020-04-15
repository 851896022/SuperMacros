#include "findkill.h"

FindKill::FindKill(QThread *parent) : QThread(parent)
{

}
void FindKill::initTHis()
{
    rect=g->killRect;
}
void FindKill::run()
{
    QPixmap screen = g->nowScreen;
    QPixmap pixmap=screen.copy(rect);
    g->killImgCache=pixmap;
}
