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

bool WhiteDice::moveSx(int x, int y, list<Dice *> dices){
  if(x-1 < 0) //out of map bound
    return false;
  
  int occupantDiceIndex = checkArrivalCellIsEmpty(x-1, y, dices);
  
  if(occupantDiceIndex == -1) //arrival cell is empty
    return true;
  else{ //arrival cell is busy
    list<Dice *>::iterator it = dices.begin();
    advance(it, occupantDiceIndex);
    
    string actualType = (*it)->getActualType();
    if(actualType.compare("RedDice") != 0 && actualType.compare("Dice") != 0) //redDices cannot be pushed  
      return (*it)->move("sx", dices, __func__); //calls recursevely the move on left for the dice on his left (if it can be done moves in turn)
    else
      return false;
  } 
}

bool WhiteDice::moveDx(int x, int y, list<Dice *> dices){
  if(x+1 >= MAP_WIDTH) //out of map bound
    return false;

  int occupantDiceIndex = checkArrivalCellIsEmpty(x+1, y, dices);
  
  if(occupantDiceIndex == -1) //arrival cell is empty
    return true;
  else{ //arrival cell is busy
    list<Dice *>::iterator it = dices.begin();
    advance(it, occupantDiceIndex);
    
    string actualType = (*it)->getActualType();
    if(actualType.compare("RedDice") != 0 && actualType.compare("Dice") != 0) 
      return (*it)->move("dx", dices, __func__);
    else
      return false;
  } 
}

bool WhiteDice::moveUp(int x, int y, list<Dice *> dices){
  if(y-1 < 0) //out of map bound
    return false;

  int occupantDiceIndex = checkArrivalCellIsEmpty(x, y-1, dices);
  
  if(occupantDiceIndex == -1) //arrival cell is empty
    return true;
  else{ //arrival cell is busy
    list<Dice *>::iterator it = dices.begin();
    advance(it, occupantDiceIndex);
    
    string actualType = (*it)->getActualType();
    if(actualType.compare("RedDice") != 0 && actualType.compare("Dice") != 0)
      return (*it)->move("up", dices, __func__);
    else
      return false;      
  } 
}

bool WhiteDice::moveDown(int x, int y, list<Dice *> dices){
  if(y+1 >= MAP_HEIGHT) //out of map bound{}
    return false;

  int occupantDiceIndex = checkArrivalCellIsEmpty(x, y+1, dices);
  
  if(occupantDiceIndex == -1) //arrival cell is empty
    return true;
  else{ //arrival cell is busy
    list<Dice *>::iterator it = dices.begin();
    advance(it, occupantDiceIndex);
    
    string actualType = (*it)->getActualType();
    if(actualType.compare("RedDice") != 0 && actualType.compare("Dice") != 0)
      return (*it)->move("down", dices, __func__);
    else
      return false;
  } 
}