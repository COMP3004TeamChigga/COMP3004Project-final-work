#ifndef DISPLAY_H
#define DISPLAY_H

#include <QWidget>
#include "QStackedWidget"
#include <QListWidget>
#include "mylistwidgetitem.h"
#include <QProgressBar>


#define powerOffScreen 0
#define mainMenu 1
#define programList 2
#define frequencyList 3
#define countDownPage 4
#define placeOnYourSkinPage 5
#define powerPage 6
#define countUpPage 7
#define historyPage 8


class Display : public QStackedWidget
{
    Q_OBJECT
public:
    void initializePages(QVector<std::string> programVecor,QVector<std::string> frequencyVector);
    explicit Display(QWidget *parent = nullptr);
    int changePage(int page);
    int changeSelection(bool UpOrDown);
    int getSelection();
    int getCurrentPage();
    void goToPage(int page);
    int toNextPage();
    int changePower(bool leftOrRight);


public slots:
    void startCountDown(QString time);
    void startCountUp(QString time);
    void backToPreviousPage();


private:
    int currentSelection;
    QString secToQString(int sec);
    QTimer* timer;
    int previousPage;


};

#endif // DISPLAY_H
