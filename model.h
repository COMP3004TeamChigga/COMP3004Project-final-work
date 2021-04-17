#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include "view.h"


class Model: public QObject
{
    Q_OBJECT
public:
    Model();

public slots:
    void handleSelections(int type,int id);
//    void handle55


private:
    int selected;
    int menu;
    View *view;

};

#endif // MODEL_H
