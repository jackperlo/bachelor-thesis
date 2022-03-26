#include "Cell.h"

Cell::Cell(int x, int y){
    setX(x);
    setY(y);
}

void Cell::setX(int x){this->x = x;}
void Cell::setY(int y){this->y = y;}

int Cell::getCoordinates(){
    return x+y;
}