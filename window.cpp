#include "window.h"
#include "ui_window.h"
#include "QApplication"
#include "QPixmap"
#include "QImage"
#include "QColor"
#include "QScreen"
#include "QDebug"
#include <QMessageBox>
window::window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::window)
{
    ui->setupUi(this);

    delayCount.setSingleShot(true);

    ui->comList->addItems(g->comNameList);
    ui->textEdit->setText(g->macro);
    QTimer *timer=new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(on_test_clicked()));
    timer->start(1000);

    for(int i=0;i<12;i++)
    {
        hBoxMy.addWidget(&lbMy[i]);
        hBoxT.addWidget(&lbT[i]);
    }

    ui->groupBox_1->setLayout(&hBoxMy);
    ui->groupBox_2->setLayout(&hBoxT);


}

window::~window()
{
    delete ui;
}

void window::on_test_clicked()
{
    QString hp=QString::number(g->nowHP)+"/"+QString::number(g->maxHP)
            +"("+QString::number(g->perHP())+"%)";
    ui->HP->setText(hp);

    QString mbuff="自身";
    QString tbuff="目标";
    for(int i=0;i<12;i++)
    {
        if(g->myBuffID[i]>0 && g->myBuffID[i]<g->buffName.count())
        {
            mbuff.append(g->buffName.at(g->myBuffID[i]));
            mbuff.append("|");
        }
        if(g->targetBuffID[i]>0 && g->targetBuffID[i]<g->buffName.count())
        {
            tbuff.append(g->buffName.at(g->targetBuffID[i]));
            tbuff.append("|");
        }
    }
    ui->tbuff->setText(tbuff);
    ui->mbuff->setText(mbuff);

    //修改图标显示
    if(ui->tabWidget->currentIndex()==2)
    {
        for(int i=0;i<12;i++)
        {
            lbT[i].setPixmap(g->buffImgCacheT[i]);
            lbMy[i].setPixmap(g->buffImgCacheMy[i]);
        }
    }


#ifdef sdaa
    int x ;
        int y ;
      // QPixmap pixmap = QPixmap::grabWindow(QApplication::desktop()->winId(), x, y, 1, 1);

        QList<QScreen *> list_screen =  QGuiApplication::screens(); //可能电脑接了多个屏幕
        int w=list_screen.at(0)->geometry().width();
        int h=list_screen.at(0)->geometry().height();
        x=w-392;
        y=h-460;
        QPixmap pixmap = list_screen.at(0)->grabWindow(0,x,y,1,1);
        if (!pixmap.isNull()) //如果像素图不为NULL
        {
            QImage image = pixmap.toImage();//将像素图转换为QImage
            if (!image.isNull()) //如果image不为空
            {
                QColor color1,color2(250,237,189);
                if (image.valid(0, 0)) //坐标位置有效
                {

                    color1 = image.pixel(0, 0);
                    if(colorDiff(color1,color2)<10)
                    {
                        //g->siMingD.start();
                        //qDebug()<<"开始！！！！！！！！！！！！";
                    }
                    else
                    {
                        //g->siMingD.stop();
                        //qDebug()<<"停止！！！！！！！！！！！！";
                    }


                }

            }
        }
#endif
}






void window::on_startLink_clicked()
{
    if(g->startLink(ui->comList->currentText()))
    {
        ui->comList->setEnabled(false);
        ui->startLink->setEnabled(false);
    }
    else
    {

    }
}

#include <QSettings>
double window::colorDiff(QColor hsv1,QColor hsv2)
{


    //self-defined
    static double R = 100;
    static double angle = 30;
    static double h = R * cos(angle / 180 * PI);
    static double r = R * sin(angle / 180 * PI);


    double x1 = r * hsv1.valueF() * hsv1.hsvSaturationF() * cos(hsv1.hsvHueF() / 180 * PI);
    double y1 = r * hsv1.valueF() * hsv1.hsvSaturationF() * sin(hsv1.hsvHueF() / 180 * PI);
    double z1 = h * (1 - hsv1.valueF());
    double x2 = r * hsv2.valueF() * hsv2.hsvSaturationF() * cos(hsv2.hsvHueF() / 180 * PI);
    double y2 = r * hsv2.valueF() * hsv2.hsvSaturationF() * sin(hsv2.hsvHueF() / 180 * PI);
    double z2 = h * (1 - hsv2.valueF());
    double dx = x1 - x2;
    double dy = y1 - y2;
    double dz = z1 - z2;
    return sqrt(dx * dx + dy * dy + dz * dz);

}

void window::on_btnSave_clicked()
{
    isOk=true;

    QString allstr=ui->textEdit->toPlainText();
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
                    QMessageBox::information(this,"错误！","键值错误");
                    isOk=false;
                }
                //g->sendCache.append((char)wordList.at(2).toInt());
            }
        }
        else
        {
            QMessageBox::information(this,"错误！","未知错误1");
            isOk=false;
        }
    }
    if(isOk)
    {
        QMessageBox::information(this,"通过！","测试通过");
        QSettings iniFile(qApp->applicationDirPath() +"/test.ini", QSettings::IniFormat);
        iniFile.setValue("macro",allstr);
        ui->btn3->setEnabled(true);
    }

}
bool window::stringToBoolLine(QString str)
{

    int c1=str.count("|");
    int c2=str.count("&");
    if(c1>0&&c2>0)
    {
        QMessageBox::information(this,"错误！","不能同时|和&");
        isOk=false;
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
bool window::stringToBoolLPoint(QString str)
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
                QMessageBox::information(this,"错误！","未知图标1");
                isOk=false;
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
                QMessageBox::information(this,"错误！","未知图标2");
                isOk=false;
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
                QMessageBox::information(this,"错误！","未知图标3");
                isOk=false;
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
                QMessageBox::information(this,"错误！","未知图标4");
                isOk=false;
                return false;
            }
            else
            {
                return g->tBuff(c);
            }
        }
        else
        {
            QMessageBox::information(this,"错误！","未知名称");
            isOk=false;
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
            QMessageBox::information(this,"错误！","未知变量1");
            isOk=false;
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
            QMessageBox::information(this,"错误！","未知变量2");
            isOk=false;
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
            QMessageBox::information(this,"错误！","没有找到变量");
            isOk=false;
            return false;
        }

    }
}






void window::on_btn3_clicked()
{
    QSettings iniFile(qApp->applicationDirPath() +"/test.ini", QSettings::IniFormat);
    g->macro=iniFile.value("macro").toString();
    ui->btn3->setEnabled(false);
}





void window::on_textEdit_textChanged()
{
    ui->btn3->setEnabled(false);
}

void window::on_btnup_1_clicked()
{
    g->mDev.setY(g->mDev.y()+1);
    QSettings iniFile(qApp->applicationDirPath() +"/test.ini", QSettings::IniFormat);
    iniFile.setValue("mdev", g->mDev);
}

void window::on_btndown_1_clicked()
{
    g->mDev.setY(g->mDev.y()-1);
    QSettings iniFile(qApp->applicationDirPath() +"/test.ini", QSettings::IniFormat);
    iniFile.setValue("mdev", g->mDev);
}

void window::on_btnleft_1_clicked()
{
    g->mDev.setX(g->mDev.x()+1);
    QSettings iniFile(qApp->applicationDirPath() +"/test.ini", QSettings::IniFormat);
    iniFile.setValue("mdev", g->mDev);
}

void window::on_btnright_1_clicked()
{
    g->mDev.setX(g->mDev.x()-1);
    QSettings iniFile(qApp->applicationDirPath() +"/test.ini", QSettings::IniFormat);
    iniFile.setValue("mdev", g->mDev);
}


void window::on_btnup_2_clicked()
{
    g->tDev.setY(g->tDev.y()+1);
    QSettings iniFile(qApp->applicationDirPath() +"/test.ini", QSettings::IniFormat);
    iniFile.setValue("tdev", g->tDev);
}

void window::on_btndown_2_clicked()
{
    g->tDev.setY(g->tDev.y()-1);
    QSettings iniFile(qApp->applicationDirPath() +"/test.ini", QSettings::IniFormat);
    iniFile.setValue("tdev", g->tDev);
}

void window::on_btnleft_2_clicked()
{
    g->tDev.setX(g->tDev.x()+1);
    QSettings iniFile(qApp->applicationDirPath() +"/test.ini", QSettings::IniFormat);
    iniFile.setValue("tdev", g->tDev);
}

void window::on_btnright_2_clicked()
{
    g->tDev.setX(g->tDev.x()-1);
    QSettings iniFile(qApp->applicationDirPath() +"/test.ini", QSettings::IniFormat);
    iniFile.setValue("tdev", g->tDev);
}


