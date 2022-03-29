#include "cell.h"

Cell::Cell(int x, int y){
    this->x = x;
    this->y = y;
}

Cell::Cell(){}

Cell::Cell(const Cell &c1){x = c1.x; y = c1.y;}

int Cell::getCoordinates(){
    return x+y;
}

int Cell::getX(){
    return x;
}

int Cell::getY(){
    return y;
}