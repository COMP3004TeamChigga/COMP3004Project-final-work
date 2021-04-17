#ifndef OBSERVERABLE_H
#define OBSERVERABLE_H

#include "observer.h"
#include <QVector>

class Observerable
{
public:
    virtual ~Observerable() {};
    virtual void addObserver(Observer *ob) = 0;
    virtual void  notify() = 0;



};

#endif // OBSERVERABLE_H
