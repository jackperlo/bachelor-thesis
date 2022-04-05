#include "common.h"
#include "red_dice.h"
#include "white_dice.h"
#include "yellow_dice.h"
#include "green_dice.h"

RedDice::RedDice(Cell position, int nMoves) : Dice(position, nMoves){}

RedDice::RedDice() : Dice(){}

RedDice::RedDice(const RedDice &rd1){position = rd1.position; nMoves = rd1.nMoves;}

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

bool RedDice::moveSx(int x, int y, list<Dice *> dices){
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

bool RedDice::moveDx(int x, int y, list<Dice *> dices){
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

bool RedDice::moveUp(int x, int y, list<Dice *> dices){
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

bool RedDice::moveDown(int x, int y, list<Dice *> dices){
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