#include "dice.h"
#include "common.h"

Dice::Dice(Cell position, int nMoves){
  setPosition(position);
  setNMoves(nMoves);
}

Dice::Dice(){}

void Dice::setPosition(Cell position){
  this->position = position;
}

Cell Dice::getPosition() const{
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

bool Dice::move(string direction, unordered_map<P2D, Dice *, P2D::HashFun> dices, char const * callerName, bool isJustForSimulation){
  direction = stringToLower(direction);
  int x = this->getPosition().getX();
  int y = this->getPosition().getY();
  pair<bool, int> res;
  bool pushedMove = this->getNMoves() == 0 && (strcmp(callerName, "moveSx") == 0 || strcmp(callerName, "moveDx") == 0 || strcmp(callerName, "moveUp") == 0 || strcmp(callerName, "moveDown") == 0);

  if(this->getNMoves() > 0 || pushedMove){
    if(direction.compare("sx") == 0){
      res = moveSx(x, y, dices, isJustForSimulation);
      if(res.first && !pushedMove && !isJustForSimulation)
        return makeMove(x-res.second, y, res.second, dices);
      else if(res.first && pushedMove && !isJustForSimulation)
        return makeMove(x-res.second, y, 0, dices);
    }else if(direction.compare("dx") == 0){
      res = moveDx(x, y, dices, isJustForSimulation);
      if(res.first && !pushedMove && !isJustForSimulation)
        return makeMove(x+res.second, y, res.second, dices);
      else if(res.first && pushedMove && !isJustForSimulation)
        return makeMove(x+res.second, y, 0, dices);
    }else if(direction.compare("up") == 0){
      res = moveUp(x, y, dices, isJustForSimulation);
      if(res.first && !pushedMove && !isJustForSimulation)
        return makeMove(x, y-res.second, res.second, dices);
      else if(res.first && pushedMove && !isJustForSimulation)
        return makeMove(x, y-res.second, 0, dices);
    }else if(direction.compare("down") == 0){
      res = moveDown(x, y, dices, isJustForSimulation);
      if(res.first && !pushedMove && !isJustForSimulation)
        return makeMove(x, y+res.second, res.second, dices);
      else if(res.first && pushedMove && !isJustForSimulation)
        return makeMove(x, y+res.second, res.second, dices);
    }
  }
  return false;
}

string Dice::stringToLower(string inputString){
  for_each(inputString.begin(), inputString.end(), [](char &c){c = tolower(c);}); 
  return inputString;
}

int Dice::checkArrivalCellIsEmpty(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> dices){
  P2D arrival_position(x, y); 
  if(dices.find(arrival_position) == dices.end())
    return 1;
  
  return 0;
}

bool Dice::makeMove(int x, int y, int nMovesDone, unordered_map<P2D, Dice *, P2D::HashFun> dices){
  dices.erase(P2D (this->getPosition().getX(), this->getPosition().getY()));
  dices.insert(pair<P2D, Dice *>(P2D::cellToP2D(Cell(x, y)), this));
  this->setPosition(Cell(x, y));
  this->setNMoves(this->getNMoves()-nMovesDone);
  return true;
}