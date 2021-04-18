#include "mytimer.h"

MyTimer::MyTimer()
{
    qtimer = new QTimer(this);
    qElapsedTimer = new QElapsedTimer();
    timeAlreadyElapsed = 0;

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
    int minutes = static_cast<int>(sec/60);
    QString a = QString();
    QString b = QString();
    if(seconds == 0){
        a = QString::fromStdString("00");
    }else{
            a.setNum(seconds);
    }
    if(minutes == 0){
        b = QString::fromStdString("00");
    }else{
            b.setNum(minutes);
    }



    return b+QString(":")+a;
}

void MyTimer::handleTimeOut(){
    if(elapsedTIme() >= secCount){
        qtimer->stop();
    }

    QString res =secToQString(elapsedTIme());
    emit oneSecPassed(res);
    emit oneSecPassedinInt();
}

void MyTimer::handleTimeOutReverse(){
    if(elapsedTIme() >= secCount){
        qtimer->stop();
    }
    QString res =secToQString(secCount-elapsedTIme());
    emit oneSecPassedReverse(res);
}


QString MyTimer::getCurrentTimePassed(){
    return secToQString(elapsedTIme());
}

QString MyTimer::getCurrentTimeLeft(){
    return secToQString(secCount - elapsedTIme());
}

void MyTimer::stop(){
    this->qtimer->stop();
}

void MyTimer::pause(){
    qtimer->stop();
    timeAlreadyElapsed = elapsedTIme();

}

void MyTimer::restart(){
    qtimer->start(1000);
    qElapsedTimer->restart();
}

int MyTimer::elapsedTIme(){
    return timeAlreadyElapsed+qElapsedTimer->elapsed()/1000 ;
}


