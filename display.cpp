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
void Display::goToPage(int page){
    previousPage = this->getCurrentPage();
    this->setCurrentIndex(page);
}
void Display::initializePages(QVector<std::string> programVecor,QVector<std::string> frequencyVector){
    QListWidget *menu =this->findChild<QListWidget*>("MainMnueWidget");
    QLabel *title = this->findChild<QLabel*>("label");
    menu->clear();
    title->setText("             Main Menu");
    title->setStyleSheet("QLabel { background-color : white; color : blue; }");
    menu->addItem(new MyListWidgetItem("Program",programList));
    menu->addItem(new MyListWidgetItem("Frequency",frequencyList));
    menu->addItem(new MyListWidgetItem("History",historyPage));


    QListWidget *program = this->findChild<QListWidget*>("programWidget");
    QLabel *title_2= this->findChild<QLabel*>("label_2");
//    program->clear();
    title_2->setText("             Program");
    title_2->setStyleSheet("QLabel { background-color : white; color : blue; }");
    for (int i = 0;i<programVecor.length() ;++i ) {
        program->addItem(new MyListWidgetItem(programVecor.at(i),placeOnYourSkinPage));
    }


    QListWidget *frequency = this->findChild<QListWidget*>("frequencyWidget");
    QLabel *title_3= this->findChild<QLabel*>("label_16");
//    frequency->clear();
    title_3->setText("            Frequency");
    title_3->setStyleSheet("QLabel { background-color : white; color : blue; }");

    for (int i = 0;i<frequencyVector.length() ;++i ) {
        frequency->addItem(new MyListWidgetItem(frequencyVector.at(i),countUpPage));
    }


    this->findChild<QProgressBar*>("powerPageBar")->setValue(0);

    QListWidget *historyList = this->findChild<QListWidget*>("HistoryWidget");
//    historyList->clear();
    qDebug()<<"historylist is null or not?"<< (historyList==nullptr?"yes":"no");

    historyList->addItem(new MyListWidgetItem("View"));
    historyList->addItem(new MyListWidgetItem("Clear"));


}

int Display::toNextPage(){
    QListWidget* list = this->currentWidget()->findChild<QListWidget*>();
    if(list!=nullptr){
        QListWidgetItem* tmp = list->currentItem();
        MyListWidgetItem *myLI = dynamic_cast<MyListWidgetItem *>(tmp);
        if(myLI != nullptr){
            int nextPage = myLI->getNextPage();
            if(nextPage > 0){
                changePage(nextPage);
                return nextPage;
            }
        }
    }
    return -1;
}

int Display::changePage(int page){
    previousPage = this->getCurrentPage();
    this->setCurrentIndex(page);
    QListWidget* list = this->currentWidget()->findChild<QListWidget*>();
    if(list!=nullptr){
       list->setCurrentRow(0);
    }
    return 0;
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
    return powerBar->value();
}

void Display::startCountDown(QString time){
    this->findChild<QLabel*>("countDownLabel")->setText(time);
}

void Display::startCountUp(QString time){

    this->findChild<QLabel*>("countUpLabel")->setText(time);
}

QString Display::secToQString(int sec){
    int seconds = sec%60;
    int minutes = floor(sec/60);
    QString a = QString();
    QString b = QString();
    a.setNum(seconds);
    b.setNum(minutes);

    qDebug()<<"the time is:" <<b+QString(":")+a;
    return b+QString(":")+a;
}

void Display::backToPreviousPage(){
    qDebug()<<"previousPage page is "<< previousPage;
    changePage(previousPage);
}


