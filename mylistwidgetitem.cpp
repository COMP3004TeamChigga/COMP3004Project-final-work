#include "mylistwidgetitem.h"

MyListWidgetItem::MyListWidgetItem(const QString &text, QListWidget *parent , int type)
    :QListWidgetItem(text,parent,type){
    nextPage = -1;
}

MyListWidgetItem::MyListWidgetItem(std::string text,int nextPage = -1)
    :MyListWidgetItem(QString::fromStdString(text)){
    this->setNextPage(nextPage);
}

void MyListWidgetItem::setNextPage(int i){
    nextPage  = i;
}
int MyListWidgetItem::getNextPage(){
    return nextPage;
}
