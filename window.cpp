#include "window.h"
#include "ui_window.h"
#include "QApplication"
#include "QPixmap"
#include "QImage"
#include "QColor"
#include "QScreen"
#include "QDebug"
window::window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::window)
{
    ui->setupUi(this);

    delayCount.setSingleShot(true);

    ui->comList->addItems(g->comNameList);

    QTimer *timer=new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(on_test_clicked()));
    timer->start(1000);

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
    qDebug()<<ui->textEdit->document()->toRawText();
}
