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

bool Dice::move(string direction, list<Dice *> dices, char const * callerName){
  direction = stringToLower(direction);
  int x = this->getPosition().getX();
  int y = this->getPosition().getY();
  if(this->getNMoves() > 0){
    if(direction.compare("sx") == 0){
      if(moveSx(x, y, dices))
        return makeActiveMove(x-1, y);
    }else if(direction.compare("dx") == 0){
      if(moveDx(x, y, dices))
        return makeActiveMove(x+1, y);
    }else if(direction.compare("up") == 0){
      if(moveUp(x, y, dices))
        return makeActiveMove(x, y-1);
    }else if(direction.compare("down") == 0){
      if(moveDown(x, y, dices))
        return makeActiveMove(x, y+1);
    }
  }else if(this->getNMoves() == 0 && (strcmp(callerName, "moveSx") == 0 || strcmp(callerName, "moveDx") == 0 || strcmp(callerName, "moveUp") == 0 || strcmp(callerName, "moveDown") == 0)){
    //you come here if the dice has nMoves=0 and is pushed by another dice
    if(direction.compare("sx") == 0){
      if(moveSx(x, y, dices))
        return makePassiveMove(x-1, y);
    }else if(direction.compare("dx") == 0){
      if(moveDx(x, y, dices))
        return makePassiveMove(x+1, y);
    }else if(direction.compare("up") == 0){
      if(moveUp(x, y, dices))
        return makePassiveMove(x, y-1);
    }else if(direction.compare("down") == 0){
      if(moveDown(x, y, dices))
        return makePassiveMove(x, y+1);
    }
  }
  return false;
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

bool Dice::makeActiveMove(int x, int y){
  Cell arrivalCell(x, y);
  this->setPosition(arrivalCell);
  this->setNMoves(this->getNMoves()-1);
  return true;
}

bool Dice::makePassiveMove(int x, int y){
  Cell arrivalCell(x, y);
  this->setPosition(arrivalCell);
  return true;
}