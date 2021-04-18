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



class Control :public QObject,public Observer
{
    Q_OBJECT

public:
    Control();

    void setDisplay(Display* d);
    void setBatteryLabel(QLabel*);


public slots:
    virtual void update(int type, int id) override;
    void changeBatteryLevel();
signals:
    void battchange(int);

private:

    void makeRecord();
    //
    void handleButtonRequests(int type, int id);
    void handlePowerButton();
    void handleDirectionalButton(int id);
    void handleMenuButton();
    void handleOkButton();
    void handleElectrodes();
    void handleReturnButton();


    Display *display;


    MyTimer *countDownTimer;
    MyTimer *systemTimer;
    QTimer *singleShotTimer;


    QLabel *batteryScreen;



    int previousPage;
    float battery;
    int powerlvl;
    bool power;
    bool onSkin;


    QVector<therapy> historyVector;
    QVector<std::string> programVecor;
    QVector<std::string> frequencyVector;


};

#endif // CONTROL_H
