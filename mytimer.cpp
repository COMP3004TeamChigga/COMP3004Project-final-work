#include "mytimer.h"

MyTimer::MyTimer()
{
    qtimer = new QTimer(this);
    qElapsedTimer = new QElapsedTimer();

    connect(qtimer,&QTimer::timeout,this,&MyTimer::handleTimeOut);
    connect(qtimer,&QTimer::timeout,this,&MyTimer::handleTimeOutReverse);
}

qint64 MyTimer::startCountDown(int sec){

    qtimer->start(1000);
    qElapsedTimer->start();
    secCount = sec;
    return sec;

}

QString secToQString(int sec){
    int seconds = sec%60;
    int minutes = floor(sec/60);
    QString a = QString();
    QString b = QString();
    a.setNum(seconds);
    b.setNum(minutes);

    qDebug()<<"the time is:" <<b+QString(":")+a;
    return b+QString(":")+a;
}

void MyTimer::handleTimeOut(){
    if(qElapsedTimer->elapsed()/1000 >= secCount){
        qtimer->stop();
    }

    QString res =secToQString(qElapsedTimer->elapsed()/1000);
    emit oneSecPassed(res);
}

void MyTimer::handleTimeOutReverse(){
    if(qElapsedTimer->elapsed()/1000 >= secCount){
        qtimer->stop();
    }
    QString res =secToQString(secCount-qElapsedTimer->elapsed()/1000);
    emit oneSecPassedReverse(res);
}


QString MyTimer::getCurrentTimePassed(){
    return secToQString(qElapsedTimer->elapsed()/1000);
}

QString MyTimer::getCurrentTimeLeft(){
    return secToQString(secCount-qElapsedTimer->elapsed()/1000);
}

void MyTimer::stop(){
    this->qtimer->stop();
}



