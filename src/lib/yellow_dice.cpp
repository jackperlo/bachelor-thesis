#include "common.h"
#include "red_dice.h"
#include "white_dice.h"
#include "yellow_dice.h"
#include "green_dice.h"

YellowDice::YellowDice(Cell position, int nMoves) : Dice(position, nMoves){}

YellowDice::YellowDice() : Dice(){}

YellowDice::YellowDice(const YellowDice &yd1){position = yd1.position; nMoves = yd1.nMoves;}

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

bool YellowDice::moveSx(int x, int y, list<Dice *> dices){
  if(x-1 < 0) //out of map bound
    return false;
  if(checkArrivalCellIsEmpty(x-1, y, dices) == -1) //arrival cell is empty
    return true;
  return false;
}

bool YellowDice::moveDx(int x, int y, list<Dice *> dices){
  if(x+1 < 0) //out of map bound
    return false;
  if(checkArrivalCellIsEmpty(x+1, y, dices) == -1) //arrival cell is empty
    return true;
  return false;
}
bool YellowDice::moveUp(int x, int y, list<Dice *> dices){
  if(y-1 < 0) //out of map bound
    return false;
  if(checkArrivalCellIsEmpty(x, y-1, dices) == -1) //arrival cell is empty
    return true;
  return false;
}
bool YellowDice::moveDown(int x, int y, list<Dice *> dices){
  if(y+1 < 0) //out of map bound
    return false;
  if(checkArrivalCellIsEmpty(y+1, y, dices) == -1) //arrival cell is empty
    return true;
  return false;
}