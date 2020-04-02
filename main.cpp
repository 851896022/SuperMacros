#include "window.h"
#include <QApplication>
#include "global.h"
#include <QDir>
#include <QFile>
#include <QDateTime>
#include "hotkey/MyGlobalShortCut.h"
#include "test.h"
#include "findgamewindow.h"
#include "worker/discern.h"
#include "macro/tl.h"
void setDebugOutput(const QString &targetFilePath, const bool &argDateFlag = false);
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QString log_dir;
    log_dir=qApp->applicationDirPath()+"/log/%1.log";
    setDebugOutput( log_dir, true );

    test t;
    g=new GLobal;
    window w;
    MyGlobalShortCut *shortcut = new MyGlobalShortCut("F9",&w);



    w.setWindowFlags(Qt::WindowStaysOnTopHint);
    w.show();
    FindGameWindow fgw;
    Discern dis;
    TL tl;
    QObject::connect(shortcut,SIGNAL(activated()),&tl,SLOT(control()));
    return a.exec();
}
//日志生成
void setDebugOutput(const QString &rawTargetFilePath_, const bool &argDateFlag_)
{
    static QString rawTargetFilePath;
    static bool argDateFlag;

    rawTargetFilePath = rawTargetFilePath_;
    argDateFlag = argDateFlag_;

    class HelperClass
    {
    public:
        static void messageHandler(QtMsgType type, const QMessageLogContext &, const QString &message_)
        {
            QString message;

            switch ( type )
            {
                case QtDebugMsg:
                {
                    message = message_;
                    break;
                }
                case QtWarningMsg:
                {
                    message.append("Warning: ");
                    message.append(message_);
                    break;
                }
                case QtCriticalMsg:
                {
                    message.append("Critical: ");
                    message.append(message_);
                    break;
                }
                case QtFatalMsg:
                {
                    message.append("Fatal: ");
                    message.append(message_);
                    break;
                }
                default: { break; }
            }

            QString currentTargetFilePath;

            if ( argDateFlag )
            {
                currentTargetFilePath = rawTargetFilePath.arg( ( ( argDateFlag ) ? ( QDateTime::currentDateTime().toString("yyyy_MM_dd") ) : ( "" ) ) );
            }
            else
            {
                currentTargetFilePath = rawTargetFilePath;
            }

            if ( !QFileInfo::exists( currentTargetFilePath ) )
            {
                QDir().mkpath( QFileInfo( currentTargetFilePath ).path() );
            }

            QFile file( currentTargetFilePath );
            file.open( QIODevice::WriteOnly | QIODevice::Append );

            QTextStream textStream( &file );
            //textStream << QDateTime::currentDateTime().toString( "yyyy-MM-dd hh:mm:ss" ) << ": " << message << "\r"<<endl;
            QTextStream textStreamc( stdout );
            textStreamc << QDateTime::currentDateTime().toString( "yyyy-MM-dd hh:mm:ss" ) << ": " << message << "\r"<<endl;
        }
    };

    qInstallMessageHandler( HelperClass::messageHandler );
}
