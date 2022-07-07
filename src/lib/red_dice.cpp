#include "common.h"
#include "red_dice.h"
#include "white_dice.h"
#include "yellow_dice.h"
#include "green_dice.h"
#include "p2d.h"
#include <typeinfo>
#include <typeindex>

RedDice::RedDice(Cell position, int nMoves, int initialMoves) : Dice(position, nMoves, initialMoves){}

RedDice::RedDice() : Dice(){}

RedDice::RedDice(const RedDice &rd1) : Dice(rd1){position = rd1.position; nMoves = rd1.nMoves;}

string RedDice::print_dice_to_string (bool print_with_initial_moves){
  string t = "";
  if(!print_with_initial_moves)
    t = BGRED(this->getNMoves());
  else
    t = BGRED(this->getInitialMoves());
  return t;
}

string RedDice::getActualType(){
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

int RedDice::getActualTypeInt(){
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

pair<bool, int> RedDice::reverseMove(string direction, unordered_map<P2D, Dice *, P2D::HashFun> &dices, char const * callerName, bool isJustForSimulation, int movementType){
  direction = stringToLower(direction);
  int x = this->getPosition().getX();
  int y = this->getPosition().getY();
  bool isGoingToCallThirdParty = !((direction.compare("sx") == 0 && checkArrivalCellIsEmpty(x-1, y, dices)) || (direction.compare("dx") == 0 && checkArrivalCellIsEmpty(x+1, y, dices)) || (direction.compare("up") == 0 && checkArrivalCellIsEmpty(x, y-1, dices)) || (direction.compare("down") == 0 && checkArrivalCellIsEmpty(x, y+1, dices)));
  if(!isGoingToCallThirdParty){
    if(this->getNMoves() > 0)
      return call4reverseMove(direction, dices, callerName, isJustForSimulation, movementType);
  }else
    return call4reverseMove(direction, dices, callerName, isJustForSimulation, movementType);
  return NO_MOVE;
}

pair<bool, int> RedDice::call4reverseMove(string direction, unordered_map<P2D, Dice *, P2D::HashFun> &dices, char const * /* callerName unused */, bool isJustForSimulation, int /* movementType unused */){
  direction = stringToLower(direction);
  int x = this->getPosition().getX();
  int y = this->getPosition().getY();
  pair<bool, int> res = NO_MOVE;
  if(direction.compare("sx") == 0){
    res = reverseMoveSx(x, y, dices, isJustForSimulation);
    if(res.first && !isJustForSimulation) this->makeMove(x-1, y, 1, dices);
  }
  if(direction.compare("dx") == 0){
    res = reverseMoveDx(x, y, dices, isJustForSimulation);
    if(res.first && !isJustForSimulation) this->makeMove(x+1, y, 1, dices);
  }
  if(direction.compare("up") == 0){
    res = reverseMoveUp(x, y, dices, isJustForSimulation);
    if(res.first && !isJustForSimulation) this->makeMove(x, y-1, 1, dices);
  }
  if(direction.compare("down") == 0){
    res = reverseMoveDown(x, y, dices, isJustForSimulation);
    if(res.first && !isJustForSimulation) this->makeMove(x, y+1, 1, dices);
  }
  return res;
}

pair<bool, int> RedDice::reverseMoveSx(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool /* isJustForSimulation unused */){
  if(x-1>=0 && checkArrivalCellIsEmpty(x-1, y, dices)) 
    return MOVE_BY_1;
  return NO_MOVE;
}

pair<bool, int> RedDice::reverseMoveDx(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool /* isJustForSimulation unused */){
  if(x+1<MAP_WIDTH && checkArrivalCellIsEmpty(x+1, y, dices)) 
    return MOVE_BY_1;
  return NO_MOVE;
}

pair<bool, int> RedDice::reverseMoveUp(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool /* isJustForSimulation unused */){
  if(y-1>=0 && checkArrivalCellIsEmpty(x, y-1, dices)) 
    return MOVE_BY_1;
  return NO_MOVE;
}

pair<bool, int> RedDice::reverseMoveDown(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool /*isJustForSimulation unused*/){
  if(y+1<MAP_HEIGHT && checkArrivalCellIsEmpty(x, y+1, dices))
    return MOVE_BY_1;
  return NO_MOVE;
}

pair<bool, int> RedDice::moveSx(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool isJustForSimulation, int movementType){
  if(x-1>=0){
    if(checkArrivalCellIsEmpty(x-1, y, dices)) //arrival cell is empty
      return MOVE_BY_1;
    else{ //arrival cell is busy
      string actualType = dices.at(P2D (x-1, y))->getActualType();
      if(actualType.compare("RedDice") != 0 && actualType.compare("Dice") != 0){ //redDices cannot be pushed  
        if(dices.at(P2D (x-1, y))->move("sx", dices, __func__, isJustForSimulation, movementType).first) //calls recursevely the move on left for the dice on his left (if it can be done moves in turn)
          return MOVE_BY_1;
        else 
          return NO_MOVE;
      }
      return NO_MOVE;
    } 
  }
  return NO_MOVE;
}

pair<bool, int> RedDice::moveDx(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool isJustForSimulation, int movementType){
  if(x+1<MAP_WIDTH){
    if(checkArrivalCellIsEmpty(x+1, y, dices)) //arrival cell is empty
      return MOVE_BY_1;
    else{ //arrival cell is busy
      string actualType = dices.at(P2D (x+1, y))->getActualType();
      if(actualType.compare("RedDice") != 0 && actualType.compare("Dice") != 0){ //redDices cannot be pushed  
        if(dices.at(P2D (x+1, y))->move("dx", dices, __func__, isJustForSimulation, movementType).first) //calls recursevely the move on left for the dice on his left (if it can be done moves in turn)
          return MOVE_BY_1;
        else 
          return NO_MOVE;
      }
      return NO_MOVE;
    } 
  }
  return NO_MOVE;
}

pair<bool, int> RedDice::moveUp(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool isJustForSimulation, int movementType){
  if(y-1>=0){
    if(checkArrivalCellIsEmpty(x, y-1, dices)) //arrival cell is empty
      return MOVE_BY_1;
    else{ //arrival cell is busy
      string actualType = dices.at(P2D (x, y-1))->getActualType();
      if(actualType.compare("RedDice") != 0 && actualType.compare("Dice") != 0){ //redDices cannot be pushed  
        if(dices.at(P2D (x, y-1))->move("up", dices, __func__, isJustForSimulation, movementType).first) //calls recursevely the move on left for the dice on his left (if it can be done moves in turn)
          return MOVE_BY_1;
        else 
          return NO_MOVE;
      }
      return NO_MOVE;
    } 
  }
  return NO_MOVE;
}

pair<bool, int> RedDice::moveDown(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool isJustForSimulation, int movementType){
  if(y+1<MAP_HEIGHT){
    if(checkArrivalCellIsEmpty(x, y+1, dices)) //arrival cell is empty
      return MOVE_BY_1;
    else{ //arrival cell is busy
      string actualType = dices.at(P2D (x, y+1))->getActualType();
      if(actualType.compare("RedDice") != 0 && actualType.compare("Dice") != 0){ //redDices cannot be pushed  
        if(dices.at(P2D (x, y+1))->move("down", dices, __func__, isJustForSimulation, movementType).first) //calls recursevely the move down for the dice on his down (if it can be done moves in turn)
          return MOVE_BY_1;
        else 
          return NO_MOVE;
      }
      return NO_MOVE;
    } 
  }
  return NO_MOVE;
}