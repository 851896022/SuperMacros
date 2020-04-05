#include "findhp.h"
#include <QTime>
FindHp::FindHp(QThread *parent) : QThread(parent)
{

}
void FindHp::initTHis()
{
    rect=g->hpRect;
}
void FindHp::run()
{

    //qDebug()<<rect;
    QPixmap screen = g->nowScreen;
    QPixmap pixmap=screen.copy(rect);
    pixmap.save("A:/001.bmp");
    image = pixmap.toImage();//将像素图转换为QImage
    for(int x=0;x<image.width();x++)
    {
        for(int y=0;y<image.height();y++)
        {
            if(image.pixelColor(x,y).red()==image.pixelColor(x,y).green())
            {

            }
            else
            {
                image.setPixelColor(x,y,Qt::black);
            }
            if(image.pixelColor(x,y).value()<100)
            {
                image.setPixelColor(x,y,Qt::black);
            }
            else
            {
                image.setPixelColor(x,y,Qt::white);
            }

        }
    }
    image.save("A:/002.bmp");
    int A=0;
    int B=0;
    bool state=false;
    QList<QImage> numberList;
    for(int x=0;x<image.width();x++)
    {
        if(state)//处于记录状态
        {
            if(lineIsHaveColor(x))//有颜色
            {
                B=x;//修改终点
            }
            else//断开了
            {
                //记录图片
                QImage tmp=image.copy(A,0,B-A+1,image.height());
                numberList.append(tmp);
                state = false;
            }
        }
        else//处于非记录状态
        {
            if(lineIsHaveColor(x))//有颜色
            {
                A=x;//修改起点
                state=true;
            }
            else//还是没颜色
            {

            }
        }

    }
    if(true)
    {
        for(int i=0;i<numberList.count();i++)
        {
            numberList.at(i).save("A:/c"+QString::number(i)+".bmp");
        }
    }

    //===========================
    QList<int> lmaxHP;
    QList<int> lnowHP;
    bool finishNowHP=false;
    for(int i=0;i<numberList.count();i++)
    {
        int tmp=imageToNumber(numberList.at(i));
        numberList.at(i).save("A:/d"+QString::number(tmp)+".bmp");
        if(tmp==10)
        {
            finishNowHP = true;
        }
        else
        {
            if(finishNowHP)
            {
                lmaxHP.append(tmp);
            }
            else
            {
                lnowHP.append(tmp);
            }
        }
    }
    int MaxHp=0;
    int nowHp=0;
    for(int i=0;i<lnowHP.count();i++)
    {
        nowHp=nowHp*10+lnowHP.at(i);
    }
    for(int i=0;i<lmaxHP.count();i++)
    {
        MaxHp=MaxHp*10+lmaxHP.at(i);
    }
    g->nowHP=nowHp;
    g->maxHP=MaxHp;


}
bool FindHp::lineIsHaveColor(int x)
{
    for(int y=0;y<image.height();y++)
    {
        if(image.pixelColor(x,y).value()>100)
        {
            return true;
        }
    }
    return false;
}
int FindHp::imageToNumber(QImage img)
{
    if(image.width()<8 || image.height()<9)
    {

        return 9;
    }
    img=img.scaled(8,9,Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QBitArray hash(64);
    for(int x=0;x<8;x++)
    {
        for(int y=0;y<8;y++)
        {
            QColor a=img.pixelColor((x),(y));
            QColor b=img.pixelColor((x),((y+1)));
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
    //if(No==2)qDebug()<<hash;
    for(int i=0;i<g->numDb.count();i++)//对比每个图
    {
        int c=0;
        for(int j=0;j<64;j++)
        {
            if(hash.at(j) == g->numDb.at(i).toBitArray().at(j))
            {

            }
            else
            {
                c++;
            }

        }

        if(c<2)
        {


            return i;
        }
    }
    return 9;
}
