#include "common.h"
#include "red_dice.h"
#include "white_dice.h"
#include "yellow_dice.h"
#include "green_dice.h"
#include "p2d.h"

YellowDice::YellowDice(Cell position, int nMoves, int initialMoves) : Dice(position, nMoves, initialMoves){}

YellowDice::YellowDice() : Dice(){}

YellowDice::YellowDice(const YellowDice &yd1){position = yd1.position; nMoves = yd1.nMoves;}

YellowDice::operator string () {
  string t = "";
  t = BGYEL(this->getNMoves());
  return t;
}

string YellowDice::getActualType(){
  type_index ti(typeid(*this));
  RedDice rd;
  WhiteDice wd;
  YellowDice yd;
  GreenDice gd;
  if (ti == type_index(typeid(rd)))
    return "RedDice";
  else if (ti == type_index(typeid(wd)))
    return "WhiteDice";
  else if (ti == type_index(typeid(yd)))
    return "YellowDice";
  else if (ti == type_index(typeid(gd)))
    return "GreenDice"; 
  else
    return "Dice";
}

int YellowDice::getActualTypeInt(){
  type_index ti(typeid(*this));
  RedDice rd;
  WhiteDice wd;
  YellowDice yd;
  GreenDice gd;
  if (ti == type_index(typeid(wd)))
    return 0;
  else if (ti == type_index(typeid(rd)))
    return 1;
  else if (ti == type_index(typeid(yd)))
    return 2;
  else if (ti == type_index(typeid(gd)))
    return 3; 
  else
    return -1;
}

pair<bool, int> YellowDice::reverseMove(string direction, unordered_map<P2D, Dice *, P2D::HashFun> &dices, char const * callerName, bool isJustForSimulation, int movementType){
  direction = stringToLower(direction);
  int x = this->getPosition().getX();
  int y = this->getPosition().getY();
  pair<bool, int> res = NO_MOVE;
  bool isGoingToCallThirdParty = !((direction.compare("sx") == 0 && checkArrivalCellIsEmpty(x-1, y, dices)) || (direction.compare("dx") == 0 && checkArrivalCellIsEmpty(x+1, y, dices)) || (direction.compare("up") == 0 && checkArrivalCellIsEmpty(x, y-1, dices)) || (direction.compare("down") == 0 && checkArrivalCellIsEmpty(x, y+1, dices)));
  if(!isGoingToCallThirdParty){
    if(this->getNMoves() > 0)
      return call4reverseMove(direction, dices, callerName, isJustForSimulation, movementType);
  }else
    return call4reverseMove(direction, dices, callerName, isJustForSimulation, movementType);
  return NO_MOVE;
}

pair<bool, int> YellowDice::call4reverseMove(string direction, unordered_map<P2D, Dice *, P2D::HashFun> &dices, char const * callerName, bool isJustForSimulation, int movementType){
  direction = stringToLower(direction);
  int x = this->getPosition().getX();
  int y = this->getPosition().getY();
  pair<bool, int> res = NO_MOVE;
  bool isMovingActively = this->getNMoves() > 0 && !(strcmp(callerName, "reverseMoveSx") == 0 || strcmp(callerName, "reverseMoveDx") == 0 || strcmp(callerName, "reverseMoveUp") == 0 || strcmp(callerName, "reverseMoveDown") == 0);
  if(direction.compare("sx") == 0){
    res = reverseMoveSx(x, y, dices, isJustForSimulation);
    if(res.first && !isJustForSimulation){
      if(res.second == 2 && checkArrivalCellIsEmpty(x-2, y, dices)){
        if(isMovingActively)this->makeMove(x-2, y, 1, dices);
        else this->makeMove(x-2, y, 0, dices);
      }else if(res.second == 1 && checkArrivalCellIsEmpty(x-1, y, dices)){
        if(isMovingActively)this->makeMove(x-1, y, 1, dices);
        else this->makeMove(x-2, y, 0, dices);
      }else{
        if(isMovingActively) this->makeMove(x-1, y, 0, dices);
        else this->makeMove(x-1, y, 1, dices);
      }
    }
  }
  else if(direction.compare("dx") == 0){
    res = reverseMoveDx(x, y, dices, isJustForSimulation);
    if(res.first && !isJustForSimulation){
      if(res.second == 2 && checkArrivalCellIsEmpty(x+2, y, dices)){
        if(isMovingActively) this->makeMove(x+2, y, 1, dices);
        else this->makeMove(x+2, y, 0, dices);
      }else if(res.second == 1 && checkArrivalCellIsEmpty(x+1, y, dices)){
        if(isMovingActively)this->makeMove(x+1, y, 1, dices);
        else this->makeMove(x+1, y, 0, dices);
      }else{
        if(isMovingActively) this->makeMove(x+1, y, 0, dices);
        else this->makeMove(x+1, y, 1, dices);
      }
    }
  }
  else if(direction.compare("up") == 0){
    res = reverseMoveUp(x, y, dices, isJustForSimulation);
    if(res.first && !isJustForSimulation){
      if(res.second == 2 && checkArrivalCellIsEmpty(x, y-2, dices)){
        if(isMovingActively) this->makeMove(x, y-2, 1, dices);
        else this->makeMove(x, y-2, 0, dices);
      }else if(res.second == 1 && checkArrivalCellIsEmpty(x, y-1, dices)){
        if(isMovingActively)this->makeMove(x, y-1, 1, dices);
        else this->makeMove(x, y-1, 0, dices);
      }else{
        if(isMovingActively) this->makeMove(x, y-1, 0, dices);
        else this->makeMove(x, y-1, 1, dices);
      }
    }
  }
  else if(direction.compare("down") == 0){
    res = reverseMoveDown(x, y, dices, isJustForSimulation);
    if(res.first && !isJustForSimulation){
      if(res.second == 2 && checkArrivalCellIsEmpty(x, y+2, dices)){
        if(isMovingActively) this->makeMove(x, y+2, 1, dices);
        else this->makeMove(x, y+2, 0, dices);
      }else if(res.second == 1 && checkArrivalCellIsEmpty(x, y+1, dices)){
        if(isMovingActively)this->makeMove(x, y+1, 1, dices);
        else this->makeMove(x, y+1, 0, dices);
      }else{
        if(isMovingActively) this->makeMove(x, y+1, 0, dices);
        else this->makeMove(x, y+1, 1, dices);
      }
    }
  }
  return res;
}

pair<bool, int> YellowDice::reverseMoveSx(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool isJustForSimulation){
  pair<bool, int> res = NO_MOVE;
  if(x-1>= 0 && checkArrivalCellIsEmpty(x-1, y, dices))
    return MOVE_BY_1;
  if(x-2>= 0 && checkArrivalCellIsEmpty(x-2, y, dices))
    return JUMP_BY_1;

  if(dices.at(P2D::cellToP2D(Cell(x-1, y)))->getActualType().compare("RedDice") == 0 || dices.at(P2D::cellToP2D(Cell(x-1, y)))->getActualType().compare("WhiteDice") == 0){
    res = dices.at(P2D::cellToP2D(Cell(x-1, y)))->reverseMove("sx", dices, __func__, isJustForSimulation);
    if(res.first)
      res.second++;
  }
  return res;
}

pair<bool, int> YellowDice::reverseMoveDx(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool isJustForSimulation){
  pair<bool, int> res = NO_MOVE;
  if(x+1 < MAP_WIDTH && checkArrivalCellIsEmpty(x+1, y, dices))
    return MOVE_BY_1;
  if(x+2 < MAP_WIDTH && checkArrivalCellIsEmpty(x+2, y, dices))
    return JUMP_BY_1;

  if(dices.at(P2D::cellToP2D(Cell(x+1, y)))->getActualType().compare("RedDice") == 0  || dices.at(P2D::cellToP2D(Cell(x+1, y)))->getActualType().compare("WhiteDice") == 0){
    res = dices.at(P2D::cellToP2D(Cell(x+1, y)))->reverseMove("dx", dices, __func__, isJustForSimulation);
    if(res.first)
      res.second++;
  }
  return res;
}

pair<bool, int> YellowDice::reverseMoveUp(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool isJustForSimulation){
  pair<bool, int> res = NO_MOVE;
  if(y-1 >= 0 && checkArrivalCellIsEmpty(x, y-1, dices))
    return MOVE_BY_1;
  if(y-2 >= 0 && checkArrivalCellIsEmpty(x, y-2, dices))
    return JUMP_BY_1;

  if(dices.at(P2D::cellToP2D(Cell(x, y-1)))->getActualType().compare("RedDice") == 0 || dices.at(P2D::cellToP2D(Cell(x, y-1)))->getActualType().compare("WhiteDice") == 0){
    res = dices.at(P2D::cellToP2D(Cell(x, y-1)))->reverseMove("up", dices, __func__, isJustForSimulation);
    if(res.first)
      res.second++;
  }
  return res;
}

pair<bool, int> YellowDice::reverseMoveDown(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool isJustForSimulation){
  pair<bool, int> res = NO_MOVE;
  if(y+1 < MAP_HEIGHT && checkArrivalCellIsEmpty(x, y+1, dices))
    return MOVE_BY_1;
  if(y+2 < MAP_HEIGHT && checkArrivalCellIsEmpty(x, y+2, dices))
    return JUMP_BY_1;

  if(dices.at(P2D::cellToP2D(Cell(x, y+1)))->getActualType().compare("RedDice") == 0 || dices.at(P2D::cellToP2D(Cell(x, y+1)))->getActualType().compare("WhiteDice") == 0){
    res = dices.at(P2D::cellToP2D(Cell(x, y+1)))->reverseMove("down", dices, __func__, isJustForSimulation);
    if(res.first)
      res.second++;
  }
  return res;
}

pair<bool, int> YellowDice::moveSx(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool isJustForSimulation){
  pair<bool, int> res = NO_MOVE;
  if(x-1 >= 0 && checkArrivalCellIsEmpty(x-1, y, dices))
    return MOVE_BY_1;
  else if(x-2 >= 0 && checkArrivalCellIsEmpty(x-2, y, dices))
    return JUMP_BY_1;
  return res;
}

pair<bool, int> YellowDice::moveDx(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool isJustForSimulation){
  pair<bool, int> res = NO_MOVE;
  if(x+1 < MAP_WIDTH && checkArrivalCellIsEmpty(x+1, y, dices))
    return MOVE_BY_1;
  else if(x+2 < MAP_WIDTH && checkArrivalCellIsEmpty(x+2, y, dices))
    return JUMP_BY_1;
  return res;
}

pair<bool, int> YellowDice::moveUp(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool isJustForSimulation){
  pair<bool, int> res = NO_MOVE;
  if(y-1 >= 0 && checkArrivalCellIsEmpty(x, y-1, dices))
    return MOVE_BY_1;
  else if(y-2 >= 0 && checkArrivalCellIsEmpty(x, y-2, dices))
    return JUMP_BY_1;
  return res;
}

pair<bool, int> YellowDice::moveDown(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool isJustForSimulation){
  pair<bool, int> res = NO_MOVE;
  if(y+1 < MAP_HEIGHT && checkArrivalCellIsEmpty(x, y+1, dices))
    return MOVE_BY_1;
  else if(y+2 < MAP_HEIGHT && checkArrivalCellIsEmpty(x, y+2, dices))
    return JUMP_BY_1;
  return res;
}