#include "dice.h"
#include "common.h"

Dice::Dice(Cell position, int nMoves, int initialMoves){
  setPosition(position);
  setNMoves(nMoves);
  this->initialMoves = initialMoves;
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

int Dice::getInitialMoves(){
  return initialMoves;
}

void Dice::printDice(){
  cout << this->getActualType() << ": (position: " << this->position.getX() << \
        ", " << this->position.getY() << ", nMoves: " << this->nMoves << ")" << std::endl;
}

pair<bool, int> Dice::move(string direction, unordered_map<P2D, Dice *, P2D::HashFun> &dices, char const * callerName, bool isJustForSimulation){
  direction = stringToLower(direction);
  int x = this->getPosition().getX();
  int y = this->getPosition().getY();
  pair<bool, int> res;
  bool pushedMove = (this->getNMoves() == 0 && (strcmp(callerName, "moveSx") == 0 || strcmp(callerName, "moveDx") == 0 || strcmp(callerName, "moveUp") == 0 || strcmp(callerName, "moveDown") == 0)) || (strcmp(callerName, "moveSx") == 0 || strcmp(callerName, "moveDx") == 0 || strcmp(callerName, "moveUp") == 0 || strcmp(callerName, "moveDown") == 0);

  if(this->getNMoves() > 0 || pushedMove){
    if(direction.compare("sx") == 0){
      res = moveSx(x, y, dices, isJustForSimulation);
      if(res.first && !pushedMove && !isJustForSimulation){
        if(this->getActualType().compare("YellowDice") == 0)
          return make_pair(makeMove(x-res.second, y, 1, dices), res.second);
        else
          return make_pair(makeMove(x-res.second, y, res.second, dices), res.second);
      }
      else if(res.first && pushedMove && !isJustForSimulation)
        return make_pair(makeMove(x-res.second, y, 0, dices), res.second);
      else if(isJustForSimulation)
        return res;
    }else if(direction.compare("dx") == 0){
      res = moveDx(x, y, dices, isJustForSimulation);
      if(res.first && !pushedMove && !isJustForSimulation){
        if(this->getActualType().compare("YellowDice") == 0)
          return make_pair(makeMove(x+res.second, y, 1, dices), res.second);
        else
          return make_pair(makeMove(x+res.second, y, res.second, dices), res.second);
      }
      else if(res.first && pushedMove && !isJustForSimulation)
        return make_pair(makeMove(x+res.second, y, 0, dices), res.second);
      else if(isJustForSimulation)
        return res;
    }else if(direction.compare("up") == 0){
      res = moveUp(x, y, dices, isJustForSimulation);
      if(res.first && !pushedMove && !isJustForSimulation){
        if(this->getActualType().compare("YellowDice") == 0)
          return make_pair(makeMove(x, y-res.second, 1, dices), res.second);
        else
          return make_pair(makeMove(x, y-res.second, res.second, dices), res.second);
      }
      else if(res.first && pushedMove && !isJustForSimulation)
        return make_pair(makeMove(x, y-res.second, 0, dices), res.second);
      else if(isJustForSimulation)
        return res;
    }else if(direction.compare("down") == 0){
      res = moveDown(x, y, dices, isJustForSimulation);
      if(res.first && !pushedMove && !isJustForSimulation){
        if(this->getActualType().compare("YellowDice") == 0)
          return make_pair(makeMove(x, y+res.second, 1, dices), res.second);
        else
          return make_pair(makeMove(x, y+res.second, res.second, dices), res.second);
      }
      else if(res.first && pushedMove && !isJustForSimulation)
        return make_pair(makeMove(x, y+res.second, 0, dices), res.second);
      else if(isJustForSimulation)
        return res;
    }
  }
  return NO_MOVE;
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

bool Dice::makeMove(int x, int y, int nMovesDone, unordered_map<P2D, Dice *, P2D::HashFun> &dices){
  dices.erase(P2D(this->getPosition().getX(), this->getPosition().getY()));
  if(dices.find(P2D(this->getPosition().getX(), this->getPosition().getY())) != dices.end()){
    cout<<"\nDice.cpp: Error while trying to erase old dice position.\n"; 
    exit(1);
  }
  dices.insert(pair<P2D, Dice *>(P2D(x, y), this));
  if(dices.find(P2D(x, y)) == dices.end()){
    cout<<"\nDice.cpp: Error while trying to insert new dice position.\n"; 
    exit(1);
  }
  this->setPosition(Cell(x, y));
  if(this->getNMoves()-nMovesDone < 0){
    cout<<"\nDice.cpp: Error while decreasing nMoves to this dice:.\n"; 
    this->printDice();
    exit(1);
  }
  this->setNMoves(this->getNMoves()-nMovesDone);
  return true;
}