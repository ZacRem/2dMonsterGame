#ifndef PIVOT_H
#define PIVOT_H

#include <iostream>

using namespace std;

class pivot{
    private:
        int value;
        int index;
    public:
        pivot();
        pivot(int value, int index);
        int getIndex();
        void setIndex(int newIndex);
        int getPivot();
        void setPivot(int newValue);
};

#endif