#include "common.h"
#include "dice.h"

Dice::Dice(Cell position, int nMoves){
  setPosition(position);
  setNMoves(nMoves);
}

Dice::Dice(){}

void Dice::setPosition(Cell position){
  this->position = position;
}

Cell Dice::getPosition(){
  return position;
}

void Dice::setNMoves(int nMoves){
  this->nMoves = nMoves;
}

void Dice::move(string direction){}

void Dice::printDice(){
  cout << typeid(this).name() << ": (position: " << this->position.getX() << \
        ", " << this->position.getY() << ", nMoves: " << this->nMoves << ")" << std::endl;
}