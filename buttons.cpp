#include "buttons.h"
#include "observer.h"

Buttons::Buttons(QWidget *widget):QPushButton(widget)
{
    connect(this, &QAbstractButton::clicked, this, &Buttons::onClick);

}

void Buttons:: onClick(){

    notify();
}

void Buttons::setTypeAndID(int type, int id){
    this->type = type;
    this->id = id;
}



void Buttons::addObserver(Observer* ob){
    this->obs.append(ob);
}

void Buttons::notify(){
    for (int i = 0;i<obs.length() ;++i ) {
        obs.at(i)->update(this->type,this->id);
    }
}
