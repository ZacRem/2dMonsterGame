#include "pivot.h"
#include <iostream>

using namespace std;

pivot :: pivot(){
    value = 0;
    index = 0;
}

pivot :: pivot(int setValue, int setIndex){
    value = setValue;
    index = setIndex;
}

int pivot :: getIndex(){
    return index;
}

void pivot :: setIndex(int newIndex){
    index = newIndex;
}

int pivot :: getPivot(){
    return value;
}

void pivot :: setPivot(int newValue){
    value = newValue;
}