#ifndef DISPLAY_H
#define DISPLAY_H

#include <QWidget>
#include "QStackedWidget"
#include <QListWidget>

#define powerOffScreen 0
#define mainMenu 1


class Display : public QStackedWidget
{
    Q_OBJECT
public:
    explicit Display(QWidget *parent = nullptr);
    int changePage(int page);
    int changeSelection(bool UpOrDown);
    int getSelection();
    void initializePages();


signals:

private:
    //QStacked widget provied getter and setters for all its pages,
    //check the documentation for more detail, we can create pages in the design mode, and change
    // the element in each page can be done by just call the getter and adjust the element inside

    // for example, if you wanna change a page's selection

//    void changeSelection(int selection){
//        if(currentIndex() == 1){
//            this->currentWidget()->setcurrentRow(selection);
//            // let's suppose 1 is the menu page, we make sure that this is a QListWidget

//        }
//    }
    // all the other operations in the page can be done in this way
    int currentSelection;
    QTimer* timer;


};

#endif // DISPLAY_H
