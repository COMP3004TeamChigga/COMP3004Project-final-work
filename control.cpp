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
    lastPage = 0;

}
void Control::setBars(QSlider* pb,QSlider* bb,QSlider* fb){
    this->powerBar = pb;
    this->batteryBar = bb;
    this->frequencyBar = fb;
    connect(batteryBar, SIGNAL(valueChanged(int)),this,SLOT(batteryToLabel(int)));
    connect(powerBar, SIGNAL(valueChanged(int)),this,SLOT(powerToLabel(int)));
    connect(frequencyBar, SIGNAL(valueChanged(int)),this,SLOT(frequencyToLabel(int)));

}


void Control::setBatteryScreen(QLabel* l){

    this->batteryScreen=l;

}
void Control::setPowerScreen(QLabel* p){

    this->powerScreen=p;

}
void Control::setFrequencyScreen(QLabel* f){

    this->frequencyScreen=f;

}
void Control::setDisplay(Display* d){
    this->display = d;
    display->initializePages();




}
void Control::makeRecord(QString name, int t){
    QString powerstr;
    QString frequencystr;
    QString timestr;
    powerstr.setNum(powerlvl);
    frequencystr.setNum(frequency);
    timestr.setNum(t);
    QString str;
    str=name+": "+"Power: "+powerstr+"/"+" Frequency: "+frequencystr+"/"+" Time: "+timestr;

   display->findChild<QListWidget*>("record")->addItem(str);




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
    this->powerScreen->setText(str);
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
    display->setCurrentIndex(value);
    qInfo()<<display->currentIndex();
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
        break;

      case menuButton:
    {handleMenuButton();}
        break;

      case okButton:
    {handleOkButton();}
        break;

    }
}

void Control::handlePowerButton(){
    if(!power){
        power=true;
        display->changePage(mainMenu);
        standingBy->start(10000);
        connect(standingBy, SIGNAL(timeout()), this, SLOT(changeBetteryLevel()));


    }
    else if(power){
        power=false;


        display->setCurrentIndex(4);
        lastPage=0;
        display->changeSelection(0);
        timer->stop();
        standingBy->stop();
        disconnect(timer, SIGNAL(timeout()), nullptr, nullptr);
        disconnect(standingBy, SIGNAL(timeout()), nullptr, nullptr);
        disconnect(running, SIGNAL(timeout()), nullptr, nullptr);

        frequency_page=false;
        powerlvl=0;
        ready=false;
        frequency=0;
        frequencyBar->setEnabled(true);
        frequencyBar->setValue(0);
        powerBar->setValue(0);
        this->powerToLabel(0);
        this->frequencyToLabel(0);
    }
}
void Control::handleDirectionalButton(int id){

    if(id==upButton){
        if(lastPage==0||lastPage==1){
            display->changeSelection(true);
            qDebug()<<"index: "<<display->getSelection();

        }

    }
    if(id==downButton){
        if(lastPage==0||lastPage == 1){
            display->changeSelection(false);
            qDebug()<<"index: "<<display->getSelection();

        }

    }
    if(id==rightButton){
        if(powerlvl<=90){
            powerlvl+=10;
            powerBar->setValue(powerlvl);
            qInfo()<<powerlvl;
        }
       }
       if(id==leftButton){
            if(powerlvl>=10){
            powerlvl-=10;
            powerBar->setValue(powerlvl);
            qInfo()<<powerlvl;
           }

        }
}
void Control::handleMenuButton(){
    display->changePage(mainMenu);

    display->findChild<QListWidget*>("MainMnueWidget")->setCurrentRow(0);
    lastPage=0;

    display->changeSelection(0);
    timer->stop();
    disconnect(timer, SIGNAL(timeout()), nullptr, nullptr);
    disconnect(running, SIGNAL(timeout()), nullptr, nullptr);
    frequency_page=false;
    powerlvl=0;
    ready=false;
    record_page=false;
    frequency=0;
    frequencyBar->setEnabled(true);
    frequencyBar->setValue(0);
    powerBar->setValue(0);
    this->powerToLabel(0);
    this->frequencyToLabel(0);
}
void Control::handleOkButton(){
    if(power==true){
        if(ready){

           timer->start(1000);
           running->start(5000);

           disconnect(timer, SIGNAL(timeout()), nullptr, nullptr);
            disconnect(running, SIGNAL(timeout()), nullptr, nullptr);


        }
     if(lastPage==0&&display->getSelection()==0&&frequency_page==false){
         display->changePage(2);
         lastPage++;
     }
     else if(lastPage==0&&display->getSelection()==5&&frequency_page==false){
         display->changePage(14);
         lastPage++;
         record_page=true;
     }
     else if(lastPage==1&&display->getSelection()==0&&record_page==true&&frequency_page==false){
         display->changePage(15);


     }
     else if(lastPage==1&&display->getSelection()==1&&record_page==true&&frequency_page==false){
         display->findChild<QListWidget*>("record")->clear();


     }
     else if(lastPage==0&&display->getSelection()==1&&frequency_page==false){
         display->changePage(8);
         lastPage++;
         frequency_page=true;


     }
     else if(lastPage==1&&display->getSelection()==0&&frequency_page==false){


        display->changePage(3);
        ready=true;


        countdown_time=70;
       connect(timer, SIGNAL(timeout()), this, SLOT(countdown()));
       connect(running, SIGNAL(timeout()), this, SLOT(running_batt_down()));
       connect(timer, SIGNAL(timeout()),this,SLOT(battchange()));

       if(timer->isActive()==true){
       this->makeRecord("Gyn. Pain",70);
       }



     }
     else if(lastPage==1&&display->getSelection()==1&&frequency_page==false){


        display->changePage(4);
        ready=true;


        countdown_time=50;
       connect(timer, SIGNAL(timeout()), this, SLOT(countdown()));
       connect(running, SIGNAL(timeout()), this, SLOT(running_batt_down()));
       connect(timer, SIGNAL(timeout()),this,SLOT(battchange()));
       if(timer->isActive()==true){
       this->makeRecord("Gynecology",50);
       }



     }
     else if(lastPage==1&&display->getSelection()==2&&frequency_page==false){


        display->changePage(5);
        ready=true;


        countdown_time=30;
       connect(timer, SIGNAL(timeout()), this, SLOT(countdown()));
       connect(running, SIGNAL(timeout()), this, SLOT(running_batt_down()));
       connect(timer, SIGNAL(timeout()),this,SLOT(battchange()));
       if(timer->isActive()==true){
       this->makeRecord("Hypertension",30);
       }


     }
     else if(lastPage==1&&display->getSelection()==3&&frequency_page==false){


        display->changePage(6);
        ready=true;

        //timer->start(1000);
        //running->start(5000);
        countdown_time=10;
       connect(timer, SIGNAL(timeout()), this, SLOT(countdown()));
       connect(running, SIGNAL(timeout()), this, SLOT(running_batt_down()));
       connect(timer, SIGNAL(timeout()),this,SLOT(battchange()));
       if(timer->isActive()==true){
       this->makeRecord("Hypotonia",30);
       }



     }
     else if(lastPage==1&&display->getSelection()==0&&frequency_page==true){

        display->changePage(10);


        ready=true;
        countdown_time=60;
       connect(timer, SIGNAL(timeout()), this, SLOT(countdown()));
       connect(running, SIGNAL(timeout()), this, SLOT(running_batt_down()));
       frequencyBar->setValue(180);
       frequencyBar->setEnabled(false);
       this->frequencyToLabel(180);

       connect(timer, SIGNAL(timeout()),this,SLOT(battchange()));
       if(timer->isActive()==true){
      this->makeRecord("180Hz",60);
       }



     }
     else if(lastPage==1&&display->getSelection()==1&&frequency_page==true){


        display->changePage(11);

        ready=true;
        countdown_time=60;
       connect(timer, SIGNAL(timeout()), this, SLOT(countdown()));
       connect(running, SIGNAL(timeout()), this, SLOT(running_batt_down()));
       frequencyBar->setValue(150);
       frequencyBar->setEnabled(false);
       this->frequencyToLabel(150);
       connect(timer, SIGNAL(timeout()),this,SLOT(battchange()));
       if(timer->isActive()==true){
       this->makeRecord("150Hz",60);
       }



     }

     else if(lastPage==1&&display->getSelection()==2&&frequency_page==true){


        display->changePage(12);

        ready=true;
        countdown_time=60;
       connect(timer, SIGNAL(timeout()), this, SLOT(countdown()));
       connect(running, SIGNAL(timeout()), this, SLOT(running_batt_down()));
       frequencyBar->setValue(120);
       frequencyBar->setEnabled(false);
       this->frequencyToLabel(120);
       connect(timer, SIGNAL(timeout()),this,SLOT(battchange()));
       if(timer->isActive()==true){
       this->makeRecord("120Hz",60);
       }



     }
     else if(lastPage==1&&display->getSelection()==3&&frequency_page==true){


        display->changePage(13);

        ready=true;
        countdown_time=60;
       connect(timer, SIGNAL(timeout()), this, SLOT(countdown()));
       connect(running, SIGNAL(timeout()), this, SLOT(running_batt_down()));
       frequencyBar->setValue(100);
       frequencyBar->setEnabled(false);
       this->frequencyToLabel(100);
       connect(timer, SIGNAL(timeout()),this,SLOT(battchange()));
       if(timer->isActive()==true){
       this->makeRecord("100Hz",60);
       }



     }
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
void Control::countdown(){


    int selection=0;
     selection=display->getSelection();
     qDebug()<<"index: "<<display->getSelection();

    if(lastPage==1&&frequency_page==false){

         switch(selection){
            case 0:
         {

             QTime time(0,0,0);
             countdown_time--;
             qDebug()<<countdown_time;
             time=time.addSecs(countdown_time);
              QString time_text = time.toString("mm:ss");
              QLabel *program1_time= display->findChild<QLabel*>("label_7");
              program1_time->setText(time_text);
             if(time_text=="00:00"){
                 timer->stop();
              disconnect(running, SIGNAL(timeout()), nullptr, nullptr);

             }

         }
          break;


         case 1:
      {

          QTime time(0,0,0);
          countdown_time--;
          qDebug()<<countdown_time;
          time=time.addSecs(countdown_time);
           QString time_text = time.toString("mm:ss");
           QLabel *program2_time= display->findChild<QLabel*>("label_9");
           program2_time->setText(time_text);
          if(time_text=="00:00"){
              timer->stop();
              disconnect(running, SIGNAL(timeout()), nullptr, nullptr);

            }


         }
          break;



         case 2:
      {
          QTime time(0,0,0);
          countdown_time--;
          qDebug()<<countdown_time;
          time=time.addSecs(countdown_time);
           QString time_text = time.toString("mm:ss");
           QLabel *program3_time= display->findChild<QLabel*>("label_11");
           program3_time->setText(time_text);
          if(time_text=="00:00"){
              timer->stop();
              disconnect(running, SIGNAL(timeout()), nullptr, nullptr);

            }


         }
          break;


         case 3:
      {
          QTime time(0,0,0);
          countdown_time--;
          qDebug()<<countdown_time;
          time=time.addSecs(countdown_time);
           QString time_text = time.toString("mm:ss");
           QLabel *program4_time= display->findChild<QLabel*>("label_13");
           program4_time->setText(time_text);
          if(time_text=="00:00"){
              timer->stop();
              disconnect(running, SIGNAL(timeout()), nullptr, nullptr);

            }


         }
          break;
         }
    }
   if(lastPage==1&&frequency_page==true){
      switch(selection){
         case 0:
      {
          QTime time(0,0,0);
          countdown_time--;
          qDebug()<<countdown_time;
          time=time.addSecs(countdown_time);
           QString time_text = time.toString("mm:ss");
           QLabel *frequency1_time= display->findChild<QLabel*>("label_26");
           frequency1_time->setText(time_text);
          if(time_text=="00:00"){
              timer->stop();
              disconnect(running, SIGNAL(timeout()), nullptr, nullptr);

            }


         }
          break;
         case 1:
      {
          QTime time(0,0,0);
          countdown_time--;
          qDebug()<<countdown_time;
          time=time.addSecs(countdown_time);
           QString time_text = time.toString("mm:ss");
           QLabel *frequency2_time= display->findChild<QLabel*>("label_28");
           frequency2_time->setText(time_text);
          if(time_text=="00:00"){
              timer->stop();
              disconnect(running, SIGNAL(timeout()), nullptr, nullptr);

            }


         }
          break;
         case 2:
      {
          QTime time(0,0,0);
          countdown_time--;
          qDebug()<<countdown_time;
          time=time.addSecs(countdown_time);
           QString time_text = time.toString("mm:ss");
           QLabel *frequency3_time= display->findChild<QLabel*>("label_30");
           frequency3_time->setText(time_text);
          if(time_text=="00:00"){
              timer->stop();
              disconnect(running, SIGNAL(timeout()), nullptr, nullptr);

            }


         }
          break;
         case 3:
      {
          QTime time(0,0,0);
          countdown_time--;
          qDebug()<<countdown_time;
          time=time.addSecs(countdown_time);
           QString time_text = time.toString("mm:ss");
           QLabel *frequency4_time= display->findChild<QLabel*>("label_32");
           frequency4_time->setText(time_text);
          if(time_text=="00:00"){
              timer->stop();
              disconnect(running, SIGNAL(timeout()), nullptr, nullptr);

            }


         }
          break;

       }

}
}
void Control::running_batt_down(){
if(batt>0){
    if(powerlvl<=40){
         batt--;
         QString str;
         str.setNum(batt);
         str="                                 Battery: "+str+"%";

         batteryScreen->setText(str);


    }

    else if(powerlvl>40&&powerlvl<70){
         batt=batt-2;
         QString str;

         str.setNum(batt);
         str="                                 Battery: "+str+"%";
         batteryScreen->setText(str);



    }
    else {
         batt=batt-3;
         QString str;

         str.setNum(batt);
         str="                                 Battery: "+str+"%";
         batteryScreen->setText(str);



    }
}
}
