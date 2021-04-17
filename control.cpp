#include "control.h"
#include "QDebug"
#include "buttons.h"
#include"QTime"
#include <QTimer>
#include <QElapsedTimer>
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "QLabel"


Control::Control():Observer()
{
    power = false;
//    lastPage = 0;
    countDownTimer = new MyTimer();
    dateTime = new QDateTime();
    programVecor.append("Gyn. Pain");
    programVecor.append("Gynecology");
    programVecor.append("Head");
    programVecor.append("Throat");

    frequencyVector.append("180Hz");
    frequencyVector.append("120Hz");
    frequencyVector.append("50Hz");
    frequencyVector.append("30Hz");


}
void Control::setBars(QSlider* pb,QSlider* bb,QSlider* fb){
    this->powerBar = pb;
    this->batteryBar = bb;
    this->frequencyBar = fb;
    connect(batteryBar, SIGNAL(valueChanged(int)),this,SLOT(batteryToLabel(int)));
    connect(powerBar, SIGNAL(valueChanged(int)),this,SLOT(powerToLabel(int)));
    connect(frequencyBar, SIGNAL(valueChanged(int)),this,SLOT(frequencyToLabel(int)));

}



void Control::setDisplay(Display* d){
    this->display = d;
    display->initializePages(programVecor,frequencyVector);
    connect(countDownTimer,&MyTimer::oneSecPassedReverse,display,&Display::startCountDown);
    connect(countDownTimer,&MyTimer::oneSecPassed,display,&Display::startCountUp);

}
void Control::makeRecord(QString duration){
    struct therapy t;

    t.date = dateTime->toString("ddd MMMM d yy");
    t.duration = duration;
    t.powerlvl = QString().setNum(powerlvl);
    int page = display->getCurrentPage();
    int selection = display->getSelection();
    if(page == programList){
        t.treatment = QString::fromStdString("Programed") + QString::fromStdString(programVecor.at(selection));
    }
    if(page == frequencyList){
        t.treatment = QString::fromStdString("Frequency")+ QString::fromStdString(frequencyVector.at(selection));

    }

    historyVector.append(t);





}

void Control::batteryToLabel(int value){





        QString str;
        str.setNum(value);
        str="                                 Battery: "+str+"%";
        this->batteryScreen->setText(str);
        batt=value;

}

void Control::powerToLabel(int value){

    QString str;
    str.setNum(value);
    str="PowerLevel: "+str;

    powerlvl=value;

}
void Control::frequencyToLabel(int value){
QString str;
str.setNum(value);
str="Frequency: "+str;
this->frequencyScreen->setText(str);
frequency=value;
}

void Control::battchange(){
    batteryBar->setValue(batt);
}


void Control::update(int type,int id){
    qDebug()<< "this is just a test :"<<type << id;
    handleButtonRequests(type,id);
}
void Control::setInitPage(int value){
    display->setCurrentIndex(0);
    qInfo()<<value;
}


//@input int type is the type of buttons, int id is the id of the button

//this function is the handler for all buttons,
//you may create your own helper method for this function
void Control::handleButtonRequests(int type, int id){

    switch (type) {
      case directionalButton:
       {handleDirectionalButton(id);}
        break;

      case powerButton:
    {handlePowerButton();}
        break;

      case returnButton:
    {handleReturnButton();}
        break;

      case menuButton:
    {handleMenuButton();}
        break;

      case okButton:
    {handleOkButton();}
        break;

      case electrodes:
    {handleElectrodes();}
        break;
    }
}

void Control::handlePowerButton(){
    if(!power){
        power=true;
        display->changePage(mainMenu);
    }
    else if(power){
        power=false;
        display->changePage(powerOffScreen);

    }
}
void Control::handleDirectionalButton(int id){

    if(id==upButton||id == downButton){
        display->changeSelection(id == upButton);
    }
    if(id==rightButton||id == leftButton){
        display->goToPage(powerPage);
        powerlvl = display->changePower(id==rightButton);

        // start a one time timer, return to the previous page after 1 secs of setting power
        QTimer *singleShotTimer = new QTimer();
        singleShotTimer->setSingleShot(true);
        connect(singleShotTimer,&QTimer::timeout,display,&Display::backToPreviousPage);
        singleShotTimer->start(1000);
       }
}
void Control::handleMenuButton(){
    display->changePage(mainMenu);
}
void Control::handleOkButton(){
    int nextPage = display->toNextPage();

    if(nextPage == countDownPage||nextPage==countUpPage){
        countDownTimer->startCountDown(600);
    }


}
void Control::handleElectrodes(){
    if(display->getCurrentPage()==placeOnYourSkinPage){
        countDownTimer->startCountDown(600);
        display->goToPage(countDownPage);
    }
}
void Control::handleReturnButton(){
    int currentpage = display->getCurrentPage();
    switch (currentpage) {
    case programList:
    case frequencyList:
    {display->goToPage(mainMenu);}
        break;
    case countDownPage:
    case placeOnYourSkinPage:
    {
        display->goToPage(programList);
        countDownTimer->stop();
    }
        break;
    case countUpPage:
    {display->goToPage(frequencyList);
    countDownTimer->stop();}
        break;
    }
}


//this function should change the powerBar accroding to the time initialed and the and the power level of the therapy
void Control::changeBetteryLevel(){
    if(batt>0){
        batt--;

    }
    QString str;

    str.setNum(batt);
    str="                                 Battery: "+str+"%";

    batteryScreen->setText(str);




}


