#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>
#include "model.h"
#include <observer.h>
#include "display.h"
#include <QProgressBar>
#include <QTimer>
#include <QVector>
#include<QLabel>
#include "mytimer.h"
#include <QDateTime>

struct therapy{
    QString date;
    QString treatment;
    QString powerlvl;
    QString duration;
};

class Control :public QObject,public Observer
{
    Q_OBJECT

public:
    Control();
    void setBars(QSlider* pb,QSlider* bb,QSlider* fb);
    void setDisplay(Display* d);
     void setInitPage(int);
     void makeRecord(QString time);

public slots:
    virtual void update(int type, int id) override;

    void changeBetteryLevel();
    void powerToLabel(int value);
    void batteryToLabel(int value);
    void frequencyToLabel(int value);
    void battchange();
private:
    void handleButtonRequests(int type, int id);
    void handlePowerButton();
    void handleDirectionalButton(int id);
    void handleMenuButton();
    void handleOkButton();
    void handleElectrodes();
    void handleReturnButton();


    Display *display;
    QSlider *powerBar;
    QSlider *batteryBar;
    QSlider *frequencyBar;

    MyTimer *countDownTimer;
    QDateTime *dateTime;


    QLabel *batteryScreen;
    QLabel *powerScreen;
    QLabel *frequencyScreen;



    int batt=100;
    int frequency;
    int powerlvl=1;
    bool power;
    bool ready=false;


    QVector<therapy> historyVector;
    QVector<std::string> programVecor;
    QVector<std::string> frequencyVector;


};

#endif // CONTROL_H
