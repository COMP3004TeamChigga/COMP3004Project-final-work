#ifndef MYLISTWIDGETITEM_H
#define MYLISTWIDGETITEM_H

#include <QListWidgetItem>
#include <QListWidget>
#include <QString>
#include <string>

class MyListWidgetItem:public QListWidgetItem
{
public:
    MyListWidgetItem(std::string text,int nextPage );
    MyListWidgetItem(const QString &text, QListWidget *parent = nullptr, int type = Type);
    void setNextPage(int i);
    int getNextPage();
private:
    int nextPage = 0;
};

#endif // MYLISTWIDGETITEM_H
