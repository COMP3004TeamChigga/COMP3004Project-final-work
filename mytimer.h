#ifndef MYTIMER_H
#define MYTIMER_H


#include <QTimer>
#include <QElapsedTimer>
#include <QDebug>

QString secToQString();
class MyTimer:public QObject
{
    Q_OBJECT
public:
    MyTimer();
    qint64 startCountDown(int sec);
    QString getCurrentTimePassed();
    QString getCurrentTimeLeft();
    void stop();

public slots:
    void handleTimeOut();
    void handleTimeOutReverse();

signals:
    void oneSecPassed(QString time);
    void oneSecPassedReverse(QString time);
    void oneSecPassedinInt(int);

private:
    QTimer *qtimer;
    QElapsedTimer *qElapsedTimer;
    int secCount;
};

#endif // MYTIMER_H
