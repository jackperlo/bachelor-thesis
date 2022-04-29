#include "common.h"
#include "white_dice.h"
#include "red_dice.h"
#include "yellow_dice.h"
#include "green_dice.h"
#include "p2d.h"
#include <typeinfo>
#include <typeindex>

WhiteDice::WhiteDice(Cell position, int nMoves, int initialMoves) : Dice(position, nMoves, initialMoves){}

WhiteDice::WhiteDice() : Dice(){}

WhiteDice::WhiteDice(const WhiteDice &wd1) : Dice(wd1){position = wd1.position; nMoves = wd1.nMoves;}

WhiteDice::operator string () {
  string t = "";
  t = BGWHT(this->getNMoves());
  return t;
}

string WhiteDice::getActualType(){
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

int WhiteDice::getActualTypeInt(){
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

pair<bool, int> WhiteDice::reverseMove(string direction, unordered_map<P2D, Dice *, P2D::HashFun> &dices, char const * callerName, bool isJustForSimulation, int movementType){
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
  return res;
}

pair<bool, int> WhiteDice::call4reverseMove(string direction, unordered_map<P2D, Dice *, P2D::HashFun> &dices, char const *, bool isJustForSimulation, int /* movementType unused */){
  direction = stringToLower(direction);
  int x = this->getPosition().getX();
  int y = this->getPosition().getY();
  pair<bool, int> res = NO_MOVE;
  if(direction.compare("sx") == 0){
    res = reverseMoveSx(x, y, dices, isJustForSimulation);
    if(res.first && !isJustForSimulation){
      if(res.second == 1) this->makeMove(x-1, y, 1, dices);
      else this->makeMove(x-1, y, 0, dices);
    }
  }
  else if(direction.compare("dx") == 0){
    res = reverseMoveDx(x, y, dices, isJustForSimulation);
    if(res.first && !isJustForSimulation){
      if(res.second == 1) this->makeMove(x+1, y, 1, dices);
      else this->makeMove(x+1, y, 0, dices);
    }
  }
  else if(direction.compare("up") == 0){
    res = reverseMoveUp(x, y, dices, isJustForSimulation);
    if(res.first && !isJustForSimulation){
      if(res.second == 1) this->makeMove(x, y-1, 1, dices);
      else this->makeMove(x, y-1, 0, dices);
    }
  }
  else if(direction.compare("down") == 0){
    res = reverseMoveDown(x, y, dices, isJustForSimulation);
    if(res.first && !isJustForSimulation){
      if(res.second == 1) this->makeMove(x, y+1, 1, dices);
      else this->makeMove(x, y+1, 0, dices);
    }
  }
  return res;
}

pair<bool, int> WhiteDice::reverseMoveSx(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool isJustForSimulation){
  pair<bool, int> res = NO_MOVE;
  if(x-1>=0){
    if(checkArrivalCellIsEmpty(x-1, y, dices))
      return MOVE_BY_1;
  
    if(dices.at(P2D::cellToP2D(Cell(x-1, y)))->getActualType().compare("RedDice") == 0 || dices.at(P2D::cellToP2D(Cell(x-1, y)))->getActualType().compare("WhiteDice") == 0){
      res = dices.at(P2D::cellToP2D(Cell(x-1, y)))->reverseMove("sx", dices, __func__, isJustForSimulation);
      if(res.first)
        res.second++;
    }
  }
  return res;
}

pair<bool, int> WhiteDice::reverseMoveDx(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool isJustForSimulation){
  pair<bool, int> res = NO_MOVE;
  if(x+1<MAP_WIDTH){
    if(checkArrivalCellIsEmpty(x+1, y, dices))
      return MOVE_BY_1;
    
    if(dices.at(P2D::cellToP2D(Cell(x+1, y)))->getActualType().compare("RedDice") == 0 || dices.at(P2D::cellToP2D(Cell(x+1, y)))->getActualType().compare("WhiteDice") == 0){
      res = dices.at(P2D::cellToP2D(Cell(x+1, y)))->reverseMove("dx", dices, __func__, isJustForSimulation);
      if(res.first)
        res.second++;
    }
  }
  return res;
}

pair<bool, int> WhiteDice::reverseMoveUp(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool isJustForSimulation){
  pair<bool, int> res = NO_MOVE;
  if(y-1>=0){
    if(checkArrivalCellIsEmpty(x, y-1, dices))
      return MOVE_BY_1;
    
    if(dices.at(P2D::cellToP2D(Cell(x, y-1)))->getActualType().compare("RedDice") == 0 || dices.at(P2D::cellToP2D(Cell(x, y-1)))->getActualType().compare("WhiteDice") == 0){
      res = dices.at(P2D::cellToP2D(Cell(x, y-1)))->reverseMove("up", dices, __func__, isJustForSimulation);
      if(res.first)
        res.second++;
    }
  }
  return res;
}

pair<bool, int> WhiteDice::reverseMoveDown(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool isJustForSimulation){
  pair<bool, int> res = NO_MOVE;
  if(y+1<MAP_HEIGHT){
    if(checkArrivalCellIsEmpty(x, y+1, dices))
      return MOVE_BY_1;
  
    if(dices.at(P2D::cellToP2D(Cell(x, y+1)))->getActualType().compare("RedDice") == 0 || dices.at(P2D::cellToP2D(Cell(x, y+1)))->getActualType().compare("WhiteDice") == 0){
      res = dices.at(P2D::cellToP2D(Cell(x, y+1)))->reverseMove("down", dices, __func__, isJustForSimulation);
      if(res.first)
        res.second++;
    }
  }
  return res;
}

pair<bool, int> WhiteDice::moveSx(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool isJustForSimulation){
  if(checkArrivalCellIsEmpty(x-1, y, dices)) //arrival cell is empty
    return MOVE_BY_1;
  else{ //arrival cell is busy
    string actualType = dices.at(P2D (x-1, y))->getActualType();
    if(actualType.compare("RedDice") != 0 && actualType.compare("Dice") != 0){ //redDices cannot be pushed  
      if(dices.at(P2D (x-1, y))->move("sx", dices, __func__, isJustForSimulation)) //calls recursevely the move on left for the dice on his left (if it can be done moves in turn)
        return MOVE_BY_1;
      else 
        return NO_MOVE;
    }
    return NO_MOVE;
  } 
}

pair<bool, int> WhiteDice::moveDx(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool isJustForSimulation){
  if(checkArrivalCellIsEmpty(x+1, y, dices)) //arrival cell is empty
    return MOVE_BY_1;
  else{ //arrival cell is busy
    string actualType = dices.at(P2D (x+1, y))->getActualType();
    if(actualType.compare("RedDice") != 0 && actualType.compare("Dice") != 0){ //redDices cannot be pushed  
      if(dices.at(P2D (x+1, y))->move("dx", dices, __func__, isJustForSimulation)) //calls recursevely the move on left for the dice on his left (if it can be done moves in turn)
        return MOVE_BY_1;
      else 
        return NO_MOVE;
    }
    return NO_MOVE;
  } 
}

pair<bool, int> WhiteDice::moveUp(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool isJustForSimulation){
  if(checkArrivalCellIsEmpty(x, y-1, dices)) //arrival cell is empty
    return MOVE_BY_1;
  else{ //arrival cell is busy
    string actualType = dices.at(P2D (x, y-1))->getActualType();
    if(actualType.compare("RedDice") != 0 && actualType.compare("Dice") != 0){ //redDices cannot be pushed  
      if(dices.at(P2D (x, y-1))->move("up", dices, __func__, isJustForSimulation)) //calls recursevely the move on left for the dice on his left (if it can be done moves in turn)
        return MOVE_BY_1;
      else 
        return NO_MOVE;
    }
    return NO_MOVE;
  } 
}

pair<bool, int> WhiteDice::moveDown(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool isJustForSimulation){
  if(checkArrivalCellIsEmpty(x, y+1, dices)) //arrival cell is empty
    return MOVE_BY_1;
  else{ //arrival cell is busy
    string actualType = dices.at(P2D (x, y+1))->getActualType();
    if(actualType.compare("RedDice") != 0 && actualType.compare("Dice") != 0){ //redDices cannot be pushed  
      if(dices.at(P2D (x, y+1))->move("down", dices, __func__, isJustForSimulation)) //calls recursevely the move on left for the dice on his left (if it can be done moves in turn)
        return MOVE_BY_1;
      else 
        return NO_MOVE;
    }
    return NO_MOVE;
  } 
}