#include "actuator.h"

Actuator::Actuator(QThread *parent) : QThread(parent)
{
    timer=new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(run()));
    timer->start(500);

}
void Actuator::control()
{
    if(timer->isActive())
    {
        timer->stop();
    }
    else
    {
        timer->start(500);
    }
}

void Actuator::run()
{




    QString allstr=g->macro;
    allstr.remove("\r");
    QStringList lineList=allstr.split("\n");
    boolMap.clear();
    for(int line=0;line<lineList.count();line++)
    {
        QStringList wordList=lineList.at(line).split(" ");
        if(wordList.count()<2 || wordList.at(0)==QString("/z"))//如果太短或者为注释
        {
            continue;
        }
        else if(wordList.at(0)==QString("/b"))
        {
            boolMap.insert(wordList.at(2),stringToBoolLine(wordList.at(1)));
        }
        else if(wordList.at(0)==QString("/k"))
        {
            if(stringToBoolLine(wordList.at(1)))
            {
                if(wordList.at(2).toInt()>150||wordList.at(2).toInt()<4)
                {

                }
                else
                {
                    g->sendCache.append((char)wordList.at(2).toInt());
                    return;
                }

            }
        }
        else
        {

        }
    }


}
bool Actuator::stringToBoolLine(QString str)
{

    int c1=str.count("|");
    int c2=str.count("&");
    if(c1>0&&c2>0)
    {

        return false;
    }
    else if(c1>0)
    {
        QStringList point=str.split("|");
        bool t=stringToBoolLPoint(point.at(0));
        for(int i=1;i<point.count();i++)
        {
            t = t || stringToBoolLPoint(point.at(i));
        }
        return t;
    }
    else if(c2>0)
    {
        QStringList point=str.split("&");
        bool t=stringToBoolLPoint(point.at(0));
        for(int i=1;i<point.count();i++)
        {
            t = t && stringToBoolLPoint(point.at(i));
        }
        return t;

    }
    else
    {
        return stringToBoolLPoint(str);
    }

}
bool Actuator::stringToBoolLPoint(QString str)
{
    if(str.count(":")>0)
    {
        QStringList t=str.split(":");
        if(t.at(0)==QString("nobuff"))
        {
            int c=-1;
            c=g->buffNameMap[t.at(1)];
            if(c==0)
            {

                return false;
            }
            else
            {
                return g->mNoBuff(c);
            }

        }
        else if(t.at(0)==QString("buff"))
        {
            int c=-1;
            c=g->buffNameMap[t.at(1)];
            if(c==0)
            {

                return false;
            }
            else
            {
                return g->mBuff(c);
            }
        }
        else if(t.at(0)==QString("tnobuff"))
        {
            int c=-1;
            c=g->buffNameMap[t.at(1)];
            if(c==0)
            {

                return false;
            }
            else
            {
                return g->tNoBuff(c);
            }
        }
        else if(t.at(0)==QString("tbuff"))
        {
            int c=-1;
            c=g->buffNameMap[t.at(1)];
            if(c==0)
            {

                return false;
            }
            else
            {
                return g->tBuff(c);
            }
        }
        else
        {

            return false;
        }
    }
    else if(str.count("<")>0)
    {
        QStringList t=str.split("<");
        if(t.at(0)==QString("HP"))
        {
            float f=t.at(1).toFloat();
            if(f<1)
            {
                return g->perHP()<f;
            }
            else
            {
                return g->nowHP<f;
            }
        }
        else
        {

            return false;
        }
    }
    else if(str.count(">")>0)
    {
        QStringList t=str.split(">");
        if(t.at(0)==QString("HP"))
        {
            float f=t.at(1).toFloat();
            if(f<1)
            {
                return g->perHP()>f;
            }
            else
            {
                return g->nowHP>f;
            }
        }
        else
        {

            return false;
        }
    }
    else//如果没符号，认为是之前设定的键值
    {
        if(boolMap.contains(str))
        {
            return boolMap[str];
        }
        else
        {

            return false;
        }

    }
}
