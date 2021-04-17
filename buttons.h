#ifndef BUTTONS_H
#define BUTTONS_H

#include <QPushButton>
#include <QWidget>
#include <QDebug>
#include <observerable.h>

#define directionalButton 1
#define powerButton 2
#define returnButton 3
#define menuButton 4
#define okButton 5
#define electrodes 6

#define upButton 1
#define downButton 2
#define leftButton 3
#define rightButton 4



class Buttons:public QPushButton,public Observerable
{
    Q_OBJECT
public:
    Buttons(QWidget* widget);
    void setTypeAndID(int type,int id = 1);
    virtual void addObserver(Observer* ob) override;
    virtual void notify() override;



public slots:
     void onClick();



private:
     QVector<Observer*> obs;
     int type;
     int id;


};

#endif // BUTTONS_H
