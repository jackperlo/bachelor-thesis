#include "common.h"
#include "red_dice.h"
#include "white_dice.h"
#include "yellow_dice.h"
#include "green_dice.h"
#include "p2d.h"
#include <typeinfo>
#include <typeindex>

int MAP_WIDTH;
int MAP_HEIGHT;
int TOTAL_MOVES;

GreenDice::GreenDice(Cell position, int nMoves, int initialMoves) : Dice(position, nMoves, initialMoves){}

GreenDice::GreenDice() : Dice(){}

GreenDice::GreenDice(const GreenDice &gd1) : Dice(gd1){position = gd1.position; nMoves = gd1.nMoves;}

GreenDice::operator string () {
  string t = "";
  t = BGGRE(this->getNMoves());
  return t;
}

string GreenDice::getActualType(){
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

int GreenDice::getActualTypeInt(){
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

pair<bool, int> GreenDice::reverseMove(string direction, unordered_map<P2D, Dice *, P2D::HashFun> &dices, char const * /* callerName unused */, bool isJustForSimulation, int movementType){
  direction = stringToLower(direction);
  int x = this->getPosition().getX();
  int y = this->getPosition().getY();
  pair<bool, int> res = NO_MOVE;
  int i = 1;
  if(movementType == 1){
    if(direction.compare("sx") == 0){
      while(x-i>=0){
        if(dices.find(P2D::cellToP2D(Cell(x-i, y))) != dices.end() && (x == MAP_WIDTH-1 || dices.find(P2D::cellToP2D(Cell(x+1, y))) != dices.end())){ //if there's a right side or is a boundary cell 
          if(dices.at(P2D::cellToP2D(Cell(x-i, y)))->getActualType().compare("WhiteDice") == 0 || dices.at(P2D::cellToP2D(Cell(x-i, y)))->getActualType().compare("RedDice") == 0){
            res = dices.at(P2D::cellToP2D(Cell(x-i, y)))->reverseMove("sx", dices, __func__, isJustForSimulation);
            if(res.first){
              res.second += i;
              if(!isJustForSimulation)
                this->makeMove(x-i, y, 0, dices);
            } 
          }
          break;
        }
        i++;
      }
    }
    else if(direction.compare("dx") == 0){
      while(x+i<MAP_WIDTH){
        if(dices.find(P2D::cellToP2D(Cell(x+i, y))) != dices.end() && (x == 0 || dices.find(P2D::cellToP2D(Cell(x-1, y))) != dices.end())){ //if there's a left side or is a boundary cell 
          if(dices.at(P2D::cellToP2D(Cell(x+i, y)))->getActualType().compare("WhiteDice") == 0 || dices.at(P2D::cellToP2D(Cell(x+i, y)))->getActualType().compare("RedDice") == 0){
            res = dices.at(P2D::cellToP2D(Cell(x+i, y)))->reverseMove("dx", dices, __func__, isJustForSimulation);
            if(res.first){
              res.second += i;
              if(!isJustForSimulation)
                this->makeMove(x+i, y, 0, dices);
            } 
          }
          break;
        }
        i++;
      }
    }
    else if(direction.compare("up") == 0){
      while(y-i>=0){
        if(dices.find(P2D::cellToP2D(Cell(x, y-i))) != dices.end() && (y == MAP_HEIGHT-1 || dices.find(P2D::cellToP2D(Cell(x, y+1))) != dices.end())){ //if there's a down side or is a boundary cell          
          if(dices.at(P2D::cellToP2D(Cell(x, y-i)))->getActualType().compare("WhiteDice") == 0 || dices.at(P2D::cellToP2D(Cell(x, y-i)))->getActualType().compare("RedDice") == 0){
            res = dices.at(P2D::cellToP2D(Cell(x, y-i)))->reverseMove("up", dices, __func__, isJustForSimulation);
            if(res.first){
              res.second += i;
              if(!isJustForSimulation)
                this->makeMove(x, y-i, 0, dices);
            } 
          }
          break;
        }
        i++;
      }
    }
    else if(direction.compare("down") == 0){
      while(y+i<MAP_HEIGHT){
        if(dices.find(P2D::cellToP2D(Cell(x, y+i))) != dices.end() && (y == 0 || dices.find(P2D::cellToP2D(Cell(x, y-1))) != dices.end())){ //if there's an up side or is a boundary cell 
          if(dices.at(P2D::cellToP2D(Cell(x, y+i)))->getActualType().compare("WhiteDice") == 0 || dices.at(P2D::cellToP2D(Cell(x, y+i)))->getActualType().compare("RedDice") == 0){
            res = dices.at(P2D::cellToP2D(Cell(x, y+i)))->reverseMove("down", dices, __func__, isJustForSimulation);
            if(res.first){
              res.second += i;
              if(!isJustForSimulation)
                this->makeMove(x, y+i, 0, dices);
            } 
          }
          break;
        }
        i++;
      }
    }
  }else{ //dice moving by itself
    if(direction.compare("sx") == 0){
      res = reverseMoveSx(x, y, dices, isJustForSimulation);
      if(res.first && !isJustForSimulation)
        this->makeMove(x-res.second, y, res.second, dices);  
    }
    else if(direction.compare("dx") == 0){
      res = reverseMoveDx(x, y, dices, isJustForSimulation);
      if(res.first && !isJustForSimulation)
        this->makeMove(x+res.second, y, res.second, dices);  
    }
    else if(direction.compare("up") == 0){
      res = reverseMoveUp(x, y, dices, isJustForSimulation);
      if(res.first && !isJustForSimulation)
        this->makeMove(x, y-res.second, res.second, dices);  
    }
    else if(direction.compare("down") == 0){
      res = reverseMoveDown(x, y, dices, isJustForSimulation);
      if(res.first && !isJustForSimulation)
        this->makeMove(x, y+res.second, res.second, dices);
    }
  }
  return res;
}

pair<bool, int> GreenDice::reverseMoveSx(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool /* isJustForSimulation unused */){
  int i = 1;
  pair<bool, int> res = NO_MOVE;
  while(x-i >= 0 && this->getNMoves()-res.second > 0 && checkArrivalCellIsEmpty(x-i, y, dices)){ 
    res.first = true;
    res.second ++;
    i++;
  }
  
  return res;
}

pair<bool, int> GreenDice::reverseMoveDx(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool /* isJustForSimulation unused */){
  int i = 1;
  pair<bool, int> res = NO_MOVE;
  while(x+i < MAP_WIDTH && this->getNMoves()-res.second > 0 && checkArrivalCellIsEmpty(x+i, y, dices)){ 
    res.first = true;
    res.second ++;
    i++;
  }
  
  return res;
}

pair<bool, int> GreenDice::reverseMoveUp(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool /* isJustForSimulation unused */){
  int i = 1;
  pair<bool, int> res = NO_MOVE;
  while(y-i >= 0 && this->getNMoves()-res.second > 0 && checkArrivalCellIsEmpty(x, y-i, dices)){ 
    res.first = true;
    res.second ++;
    i++;
  }
  
  return res;
}

pair<bool, int> GreenDice::reverseMoveDown(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool /* isJustForSimulation unused */){
  int i = 1;
  pair<bool, int> res = NO_MOVE;
  while(y+i < MAP_HEIGHT && this->getNMoves()-res.second > 0 && checkArrivalCellIsEmpty(x, y+i, dices)){ 
    res.first = true;
    res.second ++;
    i++;
  }
  
  return res;
}

pair<bool, int> GreenDice::moveSx(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool /* isJustForSimulation unused */){
  int i = 1;
  pair<bool, int> res = NO_MOVE;
  if(this->getNMoves() == 0){ //moving when pushed
    while(x-i >= 0 && checkArrivalCellIsEmpty(x-i, y, dices)){ //arrival cell is not out of map bounds and empty
      res.first = true;
      res.second ++;
      i++;
    }
  }else{ //moving actively
    while(x-i >= 0 && checkArrivalCellIsEmpty(x-i, y, dices) && this->getNMoves()-res.second > 0){ //arrival cell is not out of map bounds, is empty and there are moves available
      res.first = true;
      res.second ++;
      i++;
    }
  }
  return res;
}

pair<bool, int> GreenDice::moveDx(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool /* isJustForSimulation unused */){
  int i = 1;
  pair<bool, int> res = NO_MOVE;
  if(this->getNMoves() == 0){ //moving when pushed
    while(x+i >= 0 && checkArrivalCellIsEmpty(x+i, y, dices)){ //arrival cell is not out of map bounds and empty
      res.first = true;
      res.second ++;
      i++;
    }
  }else{ //moving actively
    while(x+i >= 0 && checkArrivalCellIsEmpty(x+i, y, dices) && this->getNMoves()-res.second > 0){ //arrival cell is not out of map bounds, is empty and there are moves available
      res.first = true;
      res.second ++;
      i++;
    }
  }
  return res;
}

pair<bool, int> GreenDice::moveUp(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool /* isJustForSimulation unused */){
  int i = 1;
  pair<bool, int> res = NO_MOVE;
  if(this->getNMoves() == 0){ //moving when pushed
    while(y-i >= 0 && checkArrivalCellIsEmpty(x, y-i, dices)){ //arrival cell is not out of map bounds and empty
      res.first = true;
      res.second ++;
      i++;
    }
  }else{ //moving actively
    while(y-i >= 0 && checkArrivalCellIsEmpty(x, y-i, dices) && this->getNMoves()-res.second > 0){ //arrival cell is not out of map bounds, is empty and there are moves available
      res.first = true;
      res.second ++;
      i++;
    }
  }
  return res;
}

pair<bool, int> GreenDice::moveDown(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool /* isJustForSimulation unused */){
  int i = 1;
  pair<bool, int> res = NO_MOVE;
  if(this->getNMoves() == 0){ //moving when pushed
    while(y+i >= 0 && checkArrivalCellIsEmpty(x, y+i, dices)){ //arrival cell is not out of map bounds and empty
      res.first = true;
      res.second ++;
      i++;
    }
  }else{ //moving actively
    while(y+i >= 0 && checkArrivalCellIsEmpty(x, y+i, dices) && this->getNMoves()-res.second > 0){ //arrival cell is not out of map bounds, is empty and there are moves available
      res.first = true;
      res.second ++;
      i++;
    }
  }
  return res;
}