#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include "global.h"
#include "math.h"
using namespace std;
#define PI 3.1415926535897932384626433832795
#include <QLabel>
#include <QHBoxLayout>
namespace Ui {
class window;
}

class window : public QMainWindow
{
    Q_OBJECT

public:
    explicit window(QWidget *parent = 0);
    ~window();
    QTimer delayCount;
    QMap<QString,bool> boolMap;
    bool isOk;
    QHBoxLayout hBoxMy;
    QHBoxLayout hBoxT;
    QLabel lbMy[12];
    QLabel lbT[12];
    QHBoxLayout hBoxKill;
    QLabel lbKill[16];
private slots:
    void on_test_clicked();
    void on_startLink_clicked();

    double colorDiff(QColor hsv1,QColor hsv2);
    void on_btnSave_clicked();
    bool stringToBoolLine(QString str);
    bool stringToBoolLPoint(QString str);

    void on_btn3_clicked();

    void on_textEdit_textChanged();

    void on_btnup_1_clicked();

    void on_btndown_1_clicked();

    void on_btnleft_1_clicked();

    void on_btnright_1_clicked();

    void on_btnup_2_clicked();

    void on_btndown_2_clicked();

    void on_btnleft_2_clicked();

    void on_btnright_2_clicked();

    void on_btnup_3_clicked();

    void on_btndown_3_clicked();

    void on_btnleft_3_clicked();

    void on_btnright_3_clicked();

    void on_btnwa_3_clicked();

    void on_btnwd_3_clicked();

    void on_btnha_3_clicked();

    void on_btnhd_3_clicked();

private:
    Ui::window *ui;
};

#endif // WINDOW_H
