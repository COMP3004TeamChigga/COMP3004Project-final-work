#include "display.h"
#include "QDebug"
#include "QLabel"

Display::Display(QWidget *parent) : QStackedWidget(parent)
{
    currentSelection = -1;
}
int Display::getSelection(){
    return this->currentSelection;
}

void Display::initializePages(){
    QListWidget *menu =this->findChild<QListWidget*>("MainMnueWidget");
    QLabel *title = this->findChild<QLabel*>("label");
    menu->clear();
    title->setText("             Main Menu");
    title->setStyleSheet("QLabel { background-color : white; color : blue; }");
    menu->addItem("Programs");
    menu->addItem("Frequency");
    menu->addItem("MED");
    menu->addItem("Screening");
    menu->addItem("Children");
    menu->addItem("Records");
    menu->setCurrentRow(0);

    QListWidget *program = this->findChild<QListWidget*>("programWidget");
    QLabel *title_2= this->findChild<QLabel*>("label_2");
    program->clear();
    title_2->setText("             Program");
    title_2->setStyleSheet("QLabel { background-color : white; color : blue; }");
    program->addItem("Gyn. Pain");
    program->addItem("Gynecology");
    program->addItem("Hypertension");
    program->addItem("Hypotonia");
    program->addItem("Head");
    program->addItem("Throat");
    program->setCurrentRow(0);

    QListWidget *frequency = this->findChild<QListWidget*>("frequencyWidget");
    QLabel *title_3= this->findChild<QLabel*>("label_16");
    frequency->clear();
    title_3->setText("            Frequency");
    title_3->setStyleSheet("QLabel { background-color : white; color : blue; }");
    frequency->addItem("180Hz");
    frequency->addItem("150Hz");
    frequency->addItem("120Hz");
    frequency->addItem("100Hz");
    frequency->addItem("50Hz");
    frequency->addItem("30Hz");
    frequency->setCurrentRow(0);
     qInfo()<<this->currentIndex();

     QListWidget *record= this->findChild<QListWidget*>("recordWidget");
     QLabel *title_4= this->findChild<QLabel*>("label_33");
     title_4->setText("            Record");
     title_4->setStyleSheet("QLabel { background-color : white; color : blue; }");
     record->addItem("View");
     record->addItem("Clear");



}

int Display::changePage(int page){

    switch (page) {

      case 1: //MainMnue
    {

        this->setCurrentIndex(0);
         currentSelection = 0;
         this->findChild<QListWidget*>("MainMnueWidget")->setCurrentRow(0);

          break;
    }
      case 2: // Program
    {

        this->setCurrentIndex(1);
         currentSelection = 0;

        this->findChild<QListWidget*>("programWidget")->setCurrentRow(0);

    }


        break;
      case 3: // program 1 gyn.pain
    {

        this->setCurrentIndex(2);

        QLabel *program1= this->findChild<QLabel*>("label_6");
        program1->setText("             Gyn. Pain");
        program1->setStyleSheet("QLabel { background-color : white; color : blue; }");
        QLabel *program1_time= this->findChild<QLabel*>("label_7");
        program1_time->setText("Start");

    }

        break;
      case 4: // program 2
       {
        this->setCurrentIndex(3);

        QLabel *program2= this->findChild<QLabel*>("label_8");
        program2->setText("           Gynecology");
        program2->setStyleSheet("QLabel { background-color : white; color : blue; }");
        QLabel *program2_time= this->findChild<QLabel*>("label_9");
        program2_time->setText("Start");
    }
        break;

    case 5:// program 3
    {
      this->setCurrentIndex(4);

      QLabel *program3= this->findChild<QLabel*>("label_10");
      program3->setText("           Hypertension");
      program3->setStyleSheet("QLabel { background-color : white; color : blue; }");
      QLabel *program3_time= this->findChild<QLabel*>("label_11");
      program3_time->setText("Start");

    }
      break;

    case 6: // program 4
    {
      this->setCurrentIndex(5);

      QLabel *program4= this->findChild<QLabel*>("label_12");
      program4->setText("           Hypotonia");
      program4->setStyleSheet("QLabel { background-color : white; color : blue; }");
      QLabel *program4_time= this->findChild<QLabel*>("label_13");
      program4_time->setText("Start");

    }
      break;

    case 7:// program 5
    {
      this->setCurrentIndex(6);

      QLabel *program5= this->findChild<QLabel*>("label_14");
      program5->setText("           Head");
      program5->setStyleSheet("QLabel { background-color : white; color : blue; }");
      QLabel *program5_time= this->findChild<QLabel*>("label_15");
      program5_time->setText("Start");

    }
      break;


    case 8:// frequency menu
        {
        this->setCurrentIndex(7);
         currentSelection = 0;
         this->findChild<QListWidget*>("frequencyWidget")->setCurrentRow(0);

        }
          break;




    case 9:// blank, powerOff
        {
          this->setCurrentIndex(10);



        }
          break;
    case 10:// frequency 1
        {
        this->setCurrentIndex(8);
      QLabel *frequency1= this->findChild<QLabel*>("label_25");
      frequency1->setText("           180Hz");
      frequency1->setStyleSheet("QLabel { background-color : white; color : blue; }");
      QLabel *frequency1_time= this->findChild<QLabel*>("label_26");
     frequency1_time->setText("Start");

    }
      break;



    case 11:// frequency 2
        {
        this->setCurrentIndex(10);
      QLabel *frequency2= this->findChild<QLabel*>("label_27");
      frequency2->setText("           150Hz");
      frequency2->setStyleSheet("QLabel { background-color : white; color : blue; }");
      QLabel *frequency2_time= this->findChild<QLabel*>("label_28");
      frequency2_time->setText("Start");

    }
      break;

    case 12://frequency 3
        {
        this->setCurrentIndex(11);
      QLabel *frequency3= this->findChild<QLabel*>("label_29");
     frequency3->setText("           120Hz");
      frequency3->setStyleSheet("QLabel { background-color : white; color : blue; }");
      QLabel *frequency3_time= this->findChild<QLabel*>("label_30");
      frequency3_time->setText("Start");

    }
      break;
    case 13:// frequency 4
        {
        this->setCurrentIndex(12);
      QLabel *frequency4= this->findChild<QLabel*>("label_31");
     frequency4->setText("           100Hz");
      frequency4->setStyleSheet("QLabel { background-color : white; color : blue; }");
      QLabel *frequency4_time= this->findChild<QLabel*>("label_32");
      frequency4_time->setText("Start");

    }
      break;

    case 14:
        {
        this->setCurrentIndex(13);
        currentSelection = 0;
        this->findChild<QListWidget*>("recordWidget")->setCurrentRow(0);



    }
      break;

    case 15:
        {
        this->setCurrentIndex(14);
        currentSelection = 0;
        this->findChild<QListWidget*>("record")->setCurrentRow(0);



    }
      break;


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

    if(UpOrDown){
            if(currentSelection>0){
            currentSelection--;
            list->setCurrentRow(currentSelection);
            }
        }
        if(!UpOrDown){
        if(currentSelection<5){
            currentSelection++;
            list->setCurrentRow(currentSelection);
        }
        }


    return list->currentRow();
}
