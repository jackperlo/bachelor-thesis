#include "cell.h"

Cell::Cell(int x, int y){
    this->x = x;
    this->y = y;
}

int Cell::getCoordinates(){
    return x+y;
}