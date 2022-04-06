#include "common.h"
#include "white_dice.h"
#include "red_dice.h"
#include "yellow_dice.h"
#include "green_dice.h"

WhiteDice::WhiteDice(Cell position, int nMoves) : Dice(position, nMoves){}

WhiteDice::WhiteDice() : Dice(){}

WhiteDice::WhiteDice(const WhiteDice &wd1){position = wd1.position; nMoves = wd1.nMoves;}

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

pair<bool, int> WhiteDice::moveSx(int x, int y, list<Dice *> dices){
  int occupantDiceIndex = checkArrivalCellIsEmpty(x-1, y, dices);
  
  if(occupantDiceIndex == -1) //arrival cell is empty
    return MOVE_BY_1;
  else{ //arrival cell is busy
    list<Dice *>::iterator it = dices.begin();
    advance(it, occupantDiceIndex);
    
    string actualType = (*it)->getActualType();
    if(actualType.compare("RedDice") != 0 && actualType.compare("Dice") != 0){ //redDices cannot be pushed  
      if((*it)->move("sx", dices, __func__)) //calls recursevely the move on left for the dice on his left (if it can be done moves in turn)
        return MOVE_BY_1;
      else 
        return NO_MOVE;
    }else
      return NO_MOVE;
  } 
}

pair<bool, int> WhiteDice::moveDx(int x, int y, list<Dice *> dices){
  int occupantDiceIndex = checkArrivalCellIsEmpty(x+1, y, dices);
  
  if(occupantDiceIndex == -1) //arrival cell is empty
    return MOVE_BY_1;
  else{ //arrival cell is busy
    list<Dice *>::iterator it = dices.begin();
    advance(it, occupantDiceIndex);
    
    string actualType = (*it)->getActualType();
    if(actualType.compare("RedDice") != 0 && actualType.compare("Dice") != 0){
      if((*it)->move("dx", dices, __func__))
        return MOVE_BY_1;
      else
        return NO_MOVE;
    }else
      return NO_MOVE;
  } 
}

pair<bool, int> WhiteDice::moveUp(int x, int y, list<Dice *> dices){
  int occupantDiceIndex = checkArrivalCellIsEmpty(x, y-1, dices);
  
  if(occupantDiceIndex == -1) //arrival cell is empty
    return MOVE_BY_1;
  else{ //arrival cell is busy
    list<Dice *>::iterator it = dices.begin();
    advance(it, occupantDiceIndex);
    
    string actualType = (*it)->getActualType();
    if(actualType.compare("RedDice") != 0 && actualType.compare("Dice") != 0){
      if((*it)->move("up", dices, __func__))
        return MOVE_BY_1;
      else
        return NO_MOVE;
    }else
      return NO_MOVE;      
  } 
}

pair<bool, int> WhiteDice::moveDown(int x, int y, list<Dice *> dices){
  int occupantDiceIndex = checkArrivalCellIsEmpty(x, y+1, dices);
  
  if(occupantDiceIndex == -1) //arrival cell is empty
    return MOVE_BY_1;
  else{ //arrival cell is busy
    list<Dice *>::iterator it = dices.begin();
    advance(it, occupantDiceIndex);
    
    string actualType = (*it)->getActualType();
    if(actualType.compare("RedDice") != 0 && actualType.compare("Dice") != 0){
      if((*it)->move("down", dices, __func__))
        return MOVE_BY_1;
      else
        return NO_MOVE;
    }else
      return NO_MOVE;
  } 
}