#include <iostream>
#include <typeinfo>
#include "dice.h"

Dice::Dice(Cell position, int nMoves){
  setPosition(position);
  setNMoves(nMoves);
}

Dice::Dice(){}

void Dice::setPosition(Cell position){
  this->position = position;
}

int Dice::getPosition(){
  return position.getCoordinates();
}

void Dice::setNMoves(int nMoves){
  this->nMoves = nMoves;
}

void Dice::move(Cell toCoordinate){}

void Dice::printDice(){
  std::cout << typeid(this).name() << ": (position: " << this->position.getX() << \
            ", " << this->position.getY() << ", nMoves: " << this->nMoves << ")" << std::endl;
}