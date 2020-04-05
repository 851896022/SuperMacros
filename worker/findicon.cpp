#include "findicon.h"

FindIcon::FindIcon(QThread *parent) : QThread(parent)
{

}
void FindIcon::initThis(int No)
{
    //this->No=No;
    if(No>11)//如果是目标
    {
        isMy=false;
        this->No=No-12;
        rect=g->targetBuffRect[this->No];
    }
    else
    {
        isMy=true;
        this->No=No;
        rect=g->myBuffRect[this->No];
    }
}
void FindIcon::run()
{
    //qDebug()<<QThread::currentThread();
    //if(No==2)qDebug()<<rect;
    //QPixmap pixmap = list_screen.at(0)->grabWindow(0,rect.x(),rect.y(),rect.width(),rect.height());
    QPixmap screen = g->nowScreen;
    QPixmap pixmap=screen.copy(rect);
    if(isMy)
    {
        pixmap.save("A:/A"+QString::number(No)+".bmp");
        g->buffImgCacheMy[No]=pixmap;
    }
    else
    {
       pixmap.save("A:/B"+QString::number(No)+".bmp");
       g->buffImgCacheT[No]=pixmap;
    }


    QImage image = pixmap.toImage();//将像素图转换为QImage
    if(image.width()<8 || image.height()<9)
    {
        if(isMy)
        {
            g->myBuffID[No]=-1;
        }
        else
        {
            g->targetBuffID[No]=-1;
        }
        return;
    }
    image=image.scaled(8,9,Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QBitArray hash(64);
    for(int x=0;x<8;x++)
    {
        for(int y=0;y<8;y++)
        {
            QColor a=image.pixelColor((x),(y));
            QColor b=image.pixelColor((x),((y+1)));
            float GrayA= a.valueF();
            float GrayB= b.valueF();
            if(GrayA>GrayB)
            {
                hash.setBit(x*8+y,true);
            }
            else
            {
                hash.setBit(x*8+y,false);
            }

        }
    }
    int ID=-1;
    //if(No==2)qDebug()<<hash;
    for(int i=0;i<g->buffDb.count();i++)//对比每个图
    {
        int c=0;
        for(int j=0;j<64;j++)
        {
            if(hash.at(j) == g->buffDb.at(i).toBitArray().at(j))
            {

            }
            else
            {
                c++;
            }

        }
        if(c<10)
        {
            ID = i;
            //qDebug()<<c;
        }
    }

    if(isMy)
    {
        g->myBuffID[No]=ID;
    }
    else
    {
        g->targetBuffID[No]=ID;
    }

}
















