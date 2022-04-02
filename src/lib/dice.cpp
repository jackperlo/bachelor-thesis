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

int Dice::getNMoves(){
  return nMoves;
}

void Dice::printDice(){
  cout << this->getActualType() << ": (position: " << this->position.getX() << \
        ", " << this->position.getY() << ", nMoves: " << this->nMoves << ")" << std::endl;
}

string Dice::stringToLower(string inputString){
  for_each(inputString.begin(), inputString.end(), [](char &c){c = tolower(c);}); 
  return inputString;
}

int Dice::checkArrivalCellIsEmpty(int x, int y, list<Dice *> dices){
  int ret = -1, i=0;
  for(auto dice : dices){
    if(dice->getPosition().getX() == x && dice->getPosition().getY() == y){
      ret = i; //cell busy. Return the index(in the list) of the occupant Dice
      break;
    }
    i++;
  }
  
  return ret;
}

void Dice::makeMove(int x, int y){
  Cell arrivalCell(x, y);
  this->setPosition(arrivalCell);
  this->setNMoves(this->getNMoves()-1);
}