#include "common.h"
#include "red_dice.h"
#include "white_dice.h"
#include "yellow_dice.h"
#include "green_dice.h"

YellowDice::YellowDice(Cell position, int nMoves) : Dice(position, nMoves){}

YellowDice::YellowDice() : Dice(){}

YellowDice::YellowDice(const YellowDice &yd1){position = yd1.position; nMoves = yd1.nMoves;}

//!TODO: valutarne l'utilità e successiva rimozione da questa classe
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

pair<bool, int> YellowDice::moveSx(int x, int y, list<Dice *> dices){
  pair<bool, int> res = NO_MOVE;
  if(checkArrivalCellIsEmpty(x-1, y, dices) == -1)
    return MOVE_BY_1;
  else if(checkArrivalCellIsEmpty(x-2, y, dices) == -1){
    res.first = true;
    res.second = 2;
  }
  return res;
}

pair<bool, int> YellowDice::moveDx(int x, int y, list<Dice *> dices){
  pair<bool, int> res = NO_MOVE;
  if(checkArrivalCellIsEmpty(x+1, y, dices) == -1)
    return MOVE_BY_1;
  else if(checkArrivalCellIsEmpty(x+2, y, dices) == -1){
    res.first = true;
    res.second = 2;
  }
  return res;
}

pair<bool, int> YellowDice::moveUp(int x, int y, list<Dice *> dices){
  pair<bool, int> res = NO_MOVE;
  if(checkArrivalCellIsEmpty(x, y-1, dices) == -1)
    return MOVE_BY_1;
  else if(checkArrivalCellIsEmpty(x, y-2, dices) == -1){
    res.first = true;
    res.second = 2;
  }
  return res;
}

pair<bool, int> YellowDice::moveDown(int x, int y, list<Dice *> dices){
  pair<bool, int> res = NO_MOVE;
  if(checkArrivalCellIsEmpty(x, y+1, dices) == -1)
    return MOVE_BY_1;
  else if(checkArrivalCellIsEmpty(x, y+2, dices) == -1){
    res.first = true;
    res.second = 2;
  }
  return res;
}