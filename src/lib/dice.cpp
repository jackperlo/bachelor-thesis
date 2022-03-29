#include "dice.h"
#include "cell.h"

Dice::Dice(Cell *position, int nMoves){
  setPosition(position);
  setNMoves(nMoves);
}

void Dice::setPosition(Cell *position){
  position = position;
}

void Dice::setNMoves(int nMoves){
  this->nMoves = nMoves;
}