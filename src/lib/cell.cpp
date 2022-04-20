#include "cell.h"
#include "common.h"

Cell::Cell(int x, int y){
  this->x = x;
  this->y = y;
}

Cell::Cell(){}

Cell::Cell(const Cell &c1){x = c1.x; y = c1.y;}

int Cell::getX(){
  return x;
}

void Cell::setX(int x){
  this->x = x;
}

int Cell::getY(){
  return y;
}

void Cell::setY(int y){
  this->y = y;
}