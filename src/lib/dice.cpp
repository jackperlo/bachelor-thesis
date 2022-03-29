#include "dice.h"

Dice::Dice(Cell position, int nMoves){
  setPosition(position);
  setNMoves(nMoves);
}

void Dice::setPosition(Cell position){
  this->position = position;
}

int Dice::getPosition(){
  return position.getCoordinates();
}

void Dice::setNMoves(int nMoves){
  this->nMoves = nMoves;
}