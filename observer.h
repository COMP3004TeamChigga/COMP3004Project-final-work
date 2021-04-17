#ifndef OBSERVER_H
#define OBSERVER_H



class Observer
{
public:
    virtual ~Observer() = default;
    virtual void update(int type,int id) = 0;
};

#endif // OBSERVER_H
