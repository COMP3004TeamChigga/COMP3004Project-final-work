#include "display.h"
#include "QDebug"
#include "QLabel"


Display::Display(QWidget *parent) : QStackedWidget(parent)
{
    currentSelection = -1;
    previousPage = 0;

}
int Display::getSelection(){
    QListWidget* list = this->currentWidget()->findChild<QListWidget*>();
    if(list!=nullptr){
        return list->currentRow();
    }
    return -1;
}
int Display::getCurrentPage(){
    return this->currentIndex();
}

int Display::getTherapyMode(){
    return therapyMode;
}
void Display::goToPage(int page){
    previousPage = this->getCurrentPage() == powerPage?previousPage:this->getCurrentPage();
    this->setCurrentIndex(page);
    QListWidget* list = this->currentWidget()->findChild<QListWidget*>();
    if(list!=nullptr){
       list->setCurrentRow(0);
    }

}
void Display::initializePages(QVector<std::string> programVecor,QVector<std::string> frequencyVector){
    QListWidget *menu =this->findChild<QListWidget*>("MainMnueWidget");

    menu->addItem(new MyListWidgetItem("Program",programList));
    menu->addItem(new MyListWidgetItem("Frequency",frequencyList));
    menu->addItem(new MyListWidgetItem("History",historyPage));


    QListWidget *program = this->findChild<QListWidget*>("programWidget");


    for (int i = 0;i<programVecor.length() ;++i ) {
        program->addItem(new MyListWidgetItem(programVecor.at(i),placeOnYourSkinPage));
    }


    QListWidget *frequency = this->findChild<QListWidget*>("frequencyWidget");
    for (int i = 0;i<frequencyVector.length() ;++i ) {
        frequency->addItem(new MyListWidgetItem(frequencyVector.at(i),placeOnYourSkinPage));
    }


    this->findChild<QProgressBar*>("powerPageBar")->setValue(0);

    QListWidget *historyList = this->findChild<QListWidget*>("historyWidget");
    historyList->addItem(new MyListWidgetItem("View",historyListPage));
    historyList->addItem(new MyListWidgetItem("Clear",clearPage));

    this->setCurrentIndex(0);

}
void Display::changeFunctionPageTitle(QString s,int page){




    if(page == placeOnYourSkinPage){
        QLabel *title = this->findChild<QLabel*>("picturPageTitle");
        QLabel *title2 = this->findChild<QLabel*>("countDownTitle");
        QLabel *title3 = this->findChild<QLabel*>("countUpTitle");
        title->setText(s);
        title2->setText(s);
        title3->setText(s);
    }



}

int Display::toNextPage(){
    if(this->getCurrentPage() == programList){
        therapyMode = 1;
    }
    if(this->getCurrentPage() == frequencyList){
        therapyMode = 2;
    }
    QListWidget* list = this->currentWidget()->findChild<QListWidget*>();
    if(list!=nullptr){// make sure that this is a listwidget
        QListWidgetItem* tmp = list->currentItem();
        MyListWidgetItem *myLI = dynamic_cast<MyListWidgetItem *>(tmp);
        if(myLI != nullptr){// make sure the listItem exists
            int nextPage = myLI->getNextPage();
            if(nextPage > 0){
                goToPage(nextPage);
                changeFunctionPageTitle(myLI->text(),nextPage);
                return nextPage;
            }
        }
    }
    return -1;
}


//@return the index of the last selection, -1 at fail
//@input bool int UpOrDown is the the value for whether the selection goes up or down

//change the Highlisght to the the next selection that may goes up or goes down
int Display::changeSelection(bool UpOrDown){

    QWidget *currentWidget = this->currentWidget();
    QListWidget* list = currentWidget->findChild<QListWidget*>();
    if(list==nullptr){
       return -1;
    }
    int cs = list->currentRow();
    int toRow = (UpOrDown?--cs:++cs)%list->count();
    toRow = toRow<0?list->count()-1:toRow;
    toRow = toRow > list->count()-1?0:toRow;
    list->setCurrentRow(toRow);




    return list->currentRow();
}

int Display::changePower(bool leftOrRight){
    QProgressBar *powerBar = this->findChild<QProgressBar*>("powerPageBar");
    int value = powerBar->value();
    if(!leftOrRight){
        powerBar->setValue(value-5);
    }else{
        powerBar->setValue(value+5);
    }

    value = powerBar->value();
    QLabel *powerLable = this->findChild<QLabel*>("powerPageLabel");
    powerLable->setText(QString().setNum(value));
    powerLable->setAlignment(Qt::AlignCenter);
    return value;
}

void Display::toTheapyPage(){

    if(therapyMode == 1){
        goToPage(countDownPage);
    }
    if(therapyMode == 2){
        goToPage(countUpPage);
    }
}

void Display::startCountDown(QString time){
    QLabel *countLabel = this->findChild<QLabel*>("countDownLabel");
    countLabel->setText(time);
    countLabel->setAlignment(Qt::AlignCenter);
}

void Display::startCountUp(QString time){

    QLabel *countLabel = this->findChild<QLabel*>("countUpLabel");
    countLabel->setText(time);
    countLabel->setAlignment(Qt::AlignCenter);
}


// this function is used spicifically for the left and right button
void Display::backToPreviousPage(){
    goToPage(previousPage);
}

void Display::addHistory(QVector<therapy> historyVector){
    QListWidget *historyListWidget = this->findChild<QListWidget*>("historyListWidget");
    historyListWidget->clear();
    foreach( therapy t,historyVector){
        QString res = t.date +QString(" \n Treatment: ")+ t.treatment
                +QString(" \n power level:")+ t.powerlvl + QString(" \n duration:")+t.duration;
        historyListWidget->addItem(res);
    }
}

void Display::changeBettery(int bettery){
    QLabel *bettLabel = this->findChild<QLabel*>("batteryLabel");
    if(bettLabel!=nullptr){
        bettLabel->setText(QString().setNum(bettery)+QString("%"));
    }
}

void Display::clearTimer(){
    QLabel *countLabel1 = this->findChild<QLabel*>("countUpLabel");
    QLabel *countLabel2 = this->findChild<QLabel*>("countDownLabel");
    countLabel1->clear();
    countLabel2->clear();
}
