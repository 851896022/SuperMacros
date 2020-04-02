#include "test.h"
#include <QStringList>
#include <QApplication>
test::test(QObject *parent) : QObject(parent)
{
   //num();


}
void test::buff()
{
    QString m_sProjectPath = tr("C:/c");/*文件夹全路径名*/
    QDir dir(m_sProjectPath);
    dir.exists(); /*判断文件夹是否存在*/
    dir.setFilter(QDir::Files); /*设置dir的过滤模式,表示只遍历本文件夹内的文件*/
    QFileInfoList fileList = dir.entryInfoList();  /*获取本文件夹内所有文件的信息*/
    int fileCount = fileList.count(); /*获取本文件夹内的文件个数*/
    QList<QVariant> list;
    QStringList name;
    QSettings iniFile(qApp->applicationDirPath() +"/test.ini", QSettings::IniFormat);
    for(int i=0;i<fileCount;i++)  /*遍历每个文件*/
    {
        QFileInfo fileInfo = fileList[i]; /*获取每个文件信息*/

        //QString suffix = fileInfo.suffix(); /*获取文件后缀名*/
        //qDebug()<<suffix;
        //QString base = QString("%1").arg(fileInfo.baseName().toInt(), 5, 10, QLatin1Char('0'));
        //qDebug()<<fileInfo.filePath()<<fileInfo.absolutePath() +"/"+ base+"."+suffix;
        //QFile::rename(fileInfo.filePath(),fileInfo.absolutePath() +"/"+ base+"."+suffix);

        QImage image= QImage(fileInfo.filePath());
        image=image.scaled(8,9,Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        //image.save("A:/tmp/"+QString::number(i)+".bmp");
        QBitArray hash(64);
        for(int x=0;x<8;x++)
        {
            for(int y=0;y<8;y++)
            {
                QColor a=image.pixelColor((x),(y));
                QColor b=image.pixelColor((x),((y+1)));
                //QColor a=image.pixelColor((x*3+4),(y*2+5));
                //QColor b=image.pixelColor((x*3+4),((y+1)*2+5));
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
        //qDebug()<<fileInfo.fileName()<<hash;
        list.append(hash);
        name.append(fileInfo.baseName());



    }
        iniFile.setValue("buff", list);
        iniFile.setValue("name", name);
}
void test::num()
{
    QString m_sProjectPath = tr("C:/num");/*文件夹全路径名*/
    QDir dir(m_sProjectPath);
    dir.exists(); /*判断文件夹是否存在*/
    dir.setFilter(QDir::Files); /*设置dir的过滤模式,表示只遍历本文件夹内的文件*/
    QFileInfoList fileList = dir.entryInfoList();  /*获取本文件夹内所有文件的信息*/
    int fileCount = fileList.count(); /*获取本文件夹内的文件个数*/
    QList<QVariant> list;
    QStringList name;
    QSettings iniFile(qApp->applicationDirPath() +"/test.ini", QSettings::IniFormat);
    for(int i=0;i<fileCount;i++)  /*遍历每个文件*/
    {
        QFileInfo fileInfo = fileList[i]; /*获取每个文件信息*/

        //QString suffix = fileInfo.suffix(); /*获取文件后缀名*/
        //qDebug()<<suffix;
        //QString base = QString("%1").arg(fileInfo.baseName().toInt(), 5, 10, QLatin1Char('0'));
        //qDebug()<<fileInfo.filePath()<<fileInfo.absolutePath() +"/"+ base+"."+suffix;
        //QFile::rename(fileInfo.filePath(),fileInfo.absolutePath() +"/"+ base+"."+suffix);

        QImage image= QImage(fileInfo.filePath());
        image=image.scaled(8,9,Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        //image.save("A:/tmp/"+QString::number(i)+".bmp");
        QBitArray hash(64);
        for(int x=0;x<8;x++)
        {
            for(int y=0;y<8;y++)
            {
                QColor a=image.pixelColor((x),(y));
                QColor b=image.pixelColor((x),((y+1)));
                //QColor a=image.pixelColor((x*3+4),(y*2+5));
                //QColor b=image.pixelColor((x*3+4),((y+1)*2+5));
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
        //qDebug()<<fileInfo.fileName()<<hash;
        list.append(hash);
        name.append(fileInfo.baseName());



    }
        iniFile.setValue("num", list);
        iniFile.setValue("numname",name);
}


