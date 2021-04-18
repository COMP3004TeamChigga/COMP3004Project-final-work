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
    systemTimer = new MyTimer();
    singleShotTimer = new QTimer();
    singleShotTimer->setSingleShot(true);
    battery = 100;
    onSkin = false;

    programVecor.append("Gyn. Pain");
    programVecor.append("Gynecology");
    programVecor.append("Head");
    programVecor.append("Throat");

    frequencyVector.append("180Hz");
    frequencyVector.append("120Hz");
    frequencyVector.append("50Hz");
    frequencyVector.append("30Hz");


}




void Control::setDisplay(Display* d){
    this->display = d;
    display->initializePages(programVecor,frequencyVector);
    connect(countDownTimer,&MyTimer::oneSecPassedReverse,display,&Display::startCountDown);
    connect(countDownTimer,&MyTimer::oneSecPassed,display,&Display::startCountUp);
    connect(singleShotTimer,&QTimer::timeout,display,&Display::backToPreviousPage);
    connect(systemTimer,&MyTimer::oneSecPassedinInt,this,&Control::changeBetteryLevel);

}
void Control::setBetteryLabel(QLabel* b){
    this->batteryScreen = b;
    this->batteryScreen->setAlignment(Qt::AlignRight);
}



// this functon wrap up everything (time ,dureation,powerlvl,treatment) in the therapy struct and send it to
// display to store it
void Control::makeRecord(){
    struct therapy t;

    QDateTime date = QDateTime::currentDateTime();
    QString formattedTime = date.toString("ddd MMMM d yy");



    t.date = formattedTime;
    t.duration = countDownTimer->getCurrentTimePassed();
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



void Control::update(int type,int id){
    qDebug()<< "this is just a test :"<<type << id;
    handleButtonRequests(type,id);
}



//@input int type is the type of buttons, int id is the id of the button

//this function is the handler for all buttons,
//you may create your own helper method for this function
void Control::handleButtonRequests(int type, int id){
    if(!power&&type!=powerButton){
        return;
    }

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
    if(!power&&battery>0){
        power=true;
        systemTimer->startCountDown(100000);
        display->changePage(mainMenu);
    }
    else if(power){
        power=false;
        countDownTimer->stop();
        systemTimer->stop();
        display->changePage(powerOffScreen);
        historyVector.clear();
        display->addHistory(historyVector);

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
        if(!singleShotTimer->isActive()){
            qDebug()<<"this timer is get started and is "<<singleShotTimer->isActive();
            singleShotTimer->start(1000);
        }
       }
}
void Control::handleMenuButton(){
    if(display->getCurrentPage() == countDownPage || display->getCurrentPage() == countUpPage){
        makeRecord();
        countDownTimer->stop();
    }

    display->changePage(mainMenu);
}
void Control::handleOkButton(){


    previousPage = display->getCurrentPage();
    int CurrentPage = display->toNextPage();

    if(CurrentPage == countDownPage||CurrentPage==countUpPage){
        countDownTimer->startCountDown(600);
    }


}
void Control::handleElectrodes(){

    if(display->getCurrentPage()==placeOnYourSkinPage){
        countDownTimer->startCountDown(600);
        display->toTheapyPage();
    }
}
void Control::handleReturnButton(){

    int currentpage = display->getCurrentPage();
    switch (currentpage) {
    case programList:
    case frequencyList:
    case historyPage:
    {display->goToPage(mainMenu);}
        break;
    case countDownPage:
    case placeOnYourSkinPage:
    {
        display->goToPage(programList);
        makeRecord();
        countDownTimer->stop();
    }
        break;
    case countUpPage:
    {
        display->goToPage(frequencyList);
        makeRecord();
        countDownTimer->stop();
    }
        break;
    case historyListPage:
    {display->goToPage(historyPage);}
        break;
    }
}


//this function should change the powerBar accroding to the time initialed and the and the power level of the therapy
void Control::changeBetteryLevel(int timePassedInSec){
    int nextBettery = floor(100 - 0.1*timePassedInSec -0.05*powerlvl);
    qDebug()<<"powerlvl = "<<powerlvl;
    this->battery = nextBettery;
    this->batteryScreen->setText(QString("Bettery:")+QString().setNum(nextBettery)+QString("%"));
    if(this->battery == 0){
        handlePowerButton();
    }
}


