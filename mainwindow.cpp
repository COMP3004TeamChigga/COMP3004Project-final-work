#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "buttons.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init(){
    /* set all button in this way, the button object and its pointer in created by qt and we cannot change it
     * so we add the stuff here
    */
    ui->up->setTypeAndID(directionalButton, upButton);
    ui->down->setTypeAndID(directionalButton, downButton);
    ui->left->setTypeAndID(directionalButton, leftButton);
    ui->right->setTypeAndID(directionalButton, rightButton);
    ui->ok->setTypeAndID(okButton, 5);
    ui->return_2->setTypeAndID(returnButton, 6);
    ui->menu->setTypeAndID(menuButton, 7);
    ui->off->setTypeAndID(powerButton, 8);
    ui->SkinOnOrOff->setTypeAndID(electrodes, 9);


//    we also do all the initalizations of objects here

    control = new Control();
    ui->up->addObserver(this->control);
    ui->down->addObserver(this->control);
    ui->left->addObserver(this->control);
    ui->right->addObserver(this->control);
    ui->ok->addObserver(this->control);
    ui->return_2->addObserver(this->control);
    ui->menu->addObserver(this->control);
    ui->off->addObserver(this->control);
    ui->SkinOnOrOff->addObserver(this->control);
    ui->stackedWidget->currentWidget();
    control->setDisplay(ui->stackedWidget);
    control->setBars(ui->powerLevel, ui->batteryLevel, ui->frequencyLevel);








}

