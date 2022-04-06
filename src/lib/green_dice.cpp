#include "common.h"
#include "red_dice.h"
#include "white_dice.h"
#include "yellow_dice.h"
#include "green_dice.h"

GreenDice::GreenDice(Cell position, int nMoves) : Dice(position, nMoves){}

GreenDice::GreenDice() : Dice(){}

GreenDice::GreenDice(const GreenDice &gd1){position = gd1.position; nMoves = gd1.nMoves;}

//!TODO: valutarne l'utilità e successiva rimozione da questa classe
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

pair<bool, int> GreenDice::moveSx(int x, int y, list<Dice *> dices){
  int i = 1;
  pair<bool, int> res = NO_MOVE;
  if(this->getNMoves() == 0){ //moving when pushed
    while(x-i >= 0 && checkArrivalCellIsEmpty(x-i, y, dices) == -1){ //arrival cell is not out of map bounds and empty
      res.first = true;
      res.second ++;
      i++;
    }
  }else{ //moving actively
    while(checkArrivalCellIsEmpty(x-i, y, dices) == -1 && this->getNMoves()-res.second > 0){ //arrival cell is not out of map bounds, is empty and there are moves available
      res.first = true;
      res.second ++;
      i++;
    }
  }
  return res;
}

pair<bool, int> GreenDice::moveDx(int x, int y, list<Dice *> dices){
  int i = 1;
  pair<bool, int> res = NO_MOVE;
  if(this->getNMoves() == 0){ //moving when pushed
    while(x+i >= 0 && checkArrivalCellIsEmpty(x+i, y, dices) == -1){ //arrival cell is not out of map bounds and empty
      res.first = true;
      res.second ++;
      i++;
    }
  }else{ //moving actively
    while(checkArrivalCellIsEmpty(x+i, y, dices) == -1 && this->getNMoves()-res.second > 0){ //arrival cell is not out of map bounds, is empty and there are moves available
      res.first = true;
      res.second ++;
      i++;
    }
  }
  return res;
}

pair<bool, int> GreenDice::moveUp(int x, int y, list<Dice *> dices){
  int i = 1;
  pair<bool, int> res = NO_MOVE;
  if(this->getNMoves() == 0){ //moving when pushed
    while(y-i >= 0 && checkArrivalCellIsEmpty(x, y-i, dices) == -1){ //arrival cell is not out of map bounds and empty
      res.first = true;
      res.second ++;
      i++;
    }
  }else{ //moving actively
    while(checkArrivalCellIsEmpty(x, y-i, dices) == -1 && this->getNMoves()-res.second > 0){ //arrival cell is not out of map bounds, is empty and there are moves available
      res.first = true;
      res.second ++;
      i++;
    }
  }
  return res;
}

pair<bool, int> GreenDice::moveDown(int x, int y, list<Dice *> dices){
  int i = 1;
  pair<bool, int> res = NO_MOVE;
  if(this->getNMoves() == 0){ //moving when pushed
    while(y+i >= 0 && checkArrivalCellIsEmpty(x, y+i, dices) == -1){ //arrival cell is not out of map bounds and empty
      res.first = true;
      res.second ++;
      i++;
    }
  }else{ //moving actively
    while(checkArrivalCellIsEmpty(x, y+i, dices) == -1 && this->getNMoves()-res.second > 0){ //arrival cell is not out of map bounds, is empty and there are moves available
      res.first = true;
      res.second ++;
      i++;
    }
  }
  return res;
}