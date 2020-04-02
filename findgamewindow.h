#ifndef FINDGAMEWINDOW_H
#define FINDGAMEWINDOW_H

#include <QObject>
#include "global.h"
#include "QTimer"
class FindGameWindow : public QObject
{
    Q_OBJECT
public:
    explicit FindGameWindow(QObject *parent = nullptr);
    QTimer timer;
signals:

public slots:
   void onTimerOut();
};

#endif // FINDGAMEWINDOW_H
