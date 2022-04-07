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
  pair<bool, int> res;
  bool pushedMove = this->getNMoves() == 0 && (strcmp(callerName, "moveSx") == 0 || strcmp(callerName, "moveDx") == 0 || strcmp(callerName, "moveUp") == 0 || strcmp(callerName, "moveDown") == 0);

  if(this->getNMoves() > 0 || pushedMove){
    if(direction.compare("sx") == 0){
      res = moveSx(x, y, dices);
      if(res.first && !pushedMove)
        return makeMove(x-res.second, y, res.second);
      else if(res.first && pushedMove)
        return makeMove(x-res.second, y, 0);
    }else if(direction.compare("dx") == 0){
      res = moveDx(x, y, dices);
      if(res.first && !pushedMove)
        return makeMove(x+res.second, y, res.second);
      else if(res.first && pushedMove)
        return makeMove(x+res.second, y, 0);
    }else if(direction.compare("up") == 0){
      res = moveUp(x, y, dices);
      if(res.first && !pushedMove)
        return makeMove(x, y-res.second, res.second);
      else if(res.first && pushedMove)
        return makeMove(x, y-res.second, 0);
    }else if(direction.compare("down") == 0){
      res = moveDown(x, y, dices);
      if(res.first && !pushedMove)
        return makeMove(x, y+res.second, res.second);
      else if(res.first && pushedMove)
        return makeMove(x, y+res.second, res.second);
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

bool Dice::makeMove(int x, int y, int nMovesDone){
  Cell arrivalCell(x, y);
  this->setPosition(arrivalCell);
  this->setNMoves(this->getNMoves()-nMovesDone);
  return true;
}