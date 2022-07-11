#include "cell.h"
#include "common.h"

Cell::Cell(int x, int y){
  this->x = x;
  this->y = y;
}

Cell::Cell(){}

int Cell::get_x(){
  return x;
}

void Cell::setX(int x){
  this->x = x;
}

int Cell::get_y(){
  return y;
}

void Cell::setY(int y){
  this->y = y;
}