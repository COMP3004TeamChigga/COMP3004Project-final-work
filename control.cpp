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

    countDownTimer = new MyTimer();
    singleShotTimer = new QTimer();
    singleShotTimer->setSingleShot(true);

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

}



void Control::setDisplay(Display* d){
    this->display = d;
    display->initializePages(programVecor,frequencyVector);
    connect(countDownTimer,&MyTimer::oneSecPassedReverse,display,&Display::startCountDown);
    connect(countDownTimer,&MyTimer::oneSecPassed,display,&Display::startCountUp);
    connect(singleShotTimer,&QTimer::timeout,display,&Display::backToPreviousPage);

}
void Control::makeRecord(QString duration){
    struct therapy t;

    QDateTime date = QDateTime::currentDateTime();
    QString formattedTime = date.toString("ddd MMMM d yy");


    t.date = formattedTime;
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
    display->addHistory(historyVector);



}


void Control::battchange(){
    batteryBar->setValue(batt);
}


void Control::update(int type,int id){
    qDebug()<< "this is just a test :"<<type << id;
    handleButtonRequests(type,id);
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
        historyVector.clear();
        display->addHistory(historyVector);

    }
}
void Control::handleDirectionalButton(int id){
    if(!power){
        return;
    }

    if(id==upButton||id == downButton){
        display->changeSelection(id == upButton);
    }
    if(id==rightButton||id == leftButton){
        display->goToPage(powerPage);
        powerlvl = display->changePower(id==rightButton);

        // start a one time timer, return to the previous page after 1 secs of setting power
        if(!singleShotTimer->isActive()){
            qDebug()<<"this timer is get started and is "<<singleShotTimer->isActive();
            singleShotTimer->start(1000);
        }
       }
}
void Control::handleMenuButton(){
    if(!power){
        return;
    }

    display->changePage(mainMenu);
}
void Control::handleOkButton(){
    if(!power){
        return;
    }

    int nextPage = display->toNextPage();

    if(nextPage == countDownPage||nextPage==countUpPage){
        countDownTimer->startCountDown(600);
    }


}
void Control::handleElectrodes(){
    if(!power){
        return;
    }
    if(display->getCurrentPage()==placeOnYourSkinPage){
        countDownTimer->startCountDown(600);
        display->goToPage(countDownPage);
    }
}
void Control::handleReturnButton(){
    if(!power){
        return;
    }
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
        makeRecord(countDownTimer->getCurrentTimePassed());
        countDownTimer->stop();
    }
        break;
    case countUpPage:
    {
        display->goToPage(frequencyList);
        makeRecord(countDownTimer->getCurrentTimeLeft());
        countDownTimer->stop();
    }
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


