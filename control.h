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
struct therapy{
    int program;
    int frequency;
};

class Control :public QObject,public Observer
{
    Q_OBJECT

public:
    Control();
    void setBars(QSlider* pb,QSlider* bb,QSlider* fb);
    void setDisplay(Display* d);
    void setBatteryScreen(QLabel*);
    void setPowerScreen(QLabel*);
     void setFrequencyScreen(QLabel*);
     void setInitPage(int);
     void makeRecord(QString,int);

public slots:
    virtual void update(int type, int id) override;
    void countdown();
     void changeBetteryLevel();
    void powerToLabel(int value);
    void batteryToLabel(int value);
    void frequencyToLabel(int value);
    void running_batt_down();
    void battchange();
private:
    void handleButtonRequests(int type, int id);
    void handlePowerButton();
    void handleDirectionalButton(int id);
    void handleMenuButton();
    void handleOkButton();


    Display *display;
    QSlider *powerBar;
    QSlider *batteryBar;
    QSlider *frequencyBar;

    QTimer *timer = new QTimer(this);
    QTimer *standingBy = new QTimer(this);
    QTimer *running = new QTimer(this);

    QLabel *batteryScreen;
    QLabel *powerScreen;
    QLabel *frequencyScreen;


    int countdown_time;
    int batt=100;
    int frequency;
    int powerlvl=1;
    bool power;
    bool ready=false;
    int lastPage;
    bool frequency_page=false;
    bool record_page=false;
    QVector<therapy*> history;


};

#endif // CONTROL_H
