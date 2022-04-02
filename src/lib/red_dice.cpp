#include "common.h"
#include "red_dice.h"
#include "white_dice.h"

RedDice::RedDice(Cell position, int nMoves) : Dice(position, nMoves){}

RedDice::RedDice() : Dice(){}

RedDice::RedDice(const RedDice &rd1){position = rd1.position; nMoves = rd1.nMoves;}

string RedDice::getActualType(){
  type_index ti(typeid(*this));
  RedDice rd;
  WhiteDice wd;
  if (ti == type_index(typeid(rd)))
      return "RedDice";
  else if (ti == type_index(typeid(wd)))
      return "WhiteDice";
  else
      return "Dice";
}


bool RedDice::move(string direction, list<Dice *> dices){
  if(this->getNMoves() > 0){
    direction = stringToLower(direction);
    int x = this->getPosition().getX();
    int y = this->getPosition().getY();
    
    if(direction.compare("sx") == 0)
      return moveSx(x, y, dices);
    else if(direction.compare("dx") == 0)
      return moveDx(x, y, dices);
    else if(direction.compare("up") == 0)
      return moveUp(x, y, dices);
    else if(direction.compare("down") == 0)
      return moveDown(x, y, dices);
    else
      return false;
  }else
    return false;
}

bool RedDice::moveSx(int x, int y, list<Dice *> dices){
  if(x-1 < 0) //out of map bound
    return false;
  else{
    int occupantDiceIndex = checkArrivalCellIsEmpty(x-1, y, dices);
    
    if(occupantDiceIndex == -1){ //arrival cell is empty
      makeMove(x-1, y);
      return true;
    }else{ //arrival cell is busy
      list<Dice *>::iterator it = dices.begin();
      advance(it, occupantDiceIndex);
      
      string actualType = (*it)->getActualType();
      if(actualType.compare("RedDice") != 0 && actualType.compare("Dice") != 0){ //redDices cannot be pushed
        bool call4neighourMove = (*it)->move("sx", dices);
        if(call4neighourMove) //calls recursevely the move on left for the dice on his left (if it can be done moves in turn)
          makeMove(x-1, y);
        return call4neighourMove;
      }else
        return false;
    } 
  }
}

bool RedDice::moveDx(int x, int y, list<Dice *> dices){
  if(x+1 >= MAP_WIDTH) //out of map bound
    return false;
  else{
    int occupantDiceIndex = checkArrivalCellIsEmpty(x+1, y, dices);
    
    if(occupantDiceIndex == -1){ //arrival cell is empty
      makeMove(x+1, y);
      return true;
    }else{ //arrival cell is busy
      list<Dice *>::iterator it = dices.begin();
      advance(it, occupantDiceIndex);
      
      string actualType = (*it)->getActualType();
      if(actualType.compare("RedDice") != 0 && actualType.compare("Dice") != 0){ //redDices cannot be pushed
        bool call4neighourMove = (*it)->move("dx", dices);
        if(call4neighourMove) //calls recursevely the move on left for the dice on his left (if it can be done moves in turn)
          makeMove(x+1, y);
        return call4neighourMove;
      }else
        return false;
    } 
  }
}

bool RedDice::moveUp(int x, int y, list<Dice *> dices){
  if(y-1 < 0) //out of map bound
    return false;
  else{
    int occupantDiceIndex = checkArrivalCellIsEmpty(x, y-1, dices);
    
    if(occupantDiceIndex == -1){ //arrival cell is empty
      makeMove(x, y-1);
      return true;
    }else{ //arrival cell is busy
      list<Dice *>::iterator it = dices.begin();
      advance(it, occupantDiceIndex);
      
      string actualType = (*it)->getActualType();
      if(actualType.compare("RedDice") != 0 && actualType.compare("Dice") != 0){ //redDices cannot be pushed
        bool call4neighourMove = (*it)->move("up", dices);
        if(call4neighourMove) //calls recursevely the move on left for the dice on his left (if it can be done moves in turn)
          makeMove(x, y-1);
        return call4neighourMove;
      }else
        return false;
    } 
  }
}

bool RedDice::moveDown(int x, int y, list<Dice *> dices){
  if(y+1 >= MAP_HEIGHT){ //out of map bound{}
    return false;
  }else{
    int occupantDiceIndex = checkArrivalCellIsEmpty(x, y+1, dices);
    
    if(occupantDiceIndex == -1){ //arrival cell is empty
      makeMove(x, y+1);
      return true;
    }else{ //arrival cell is busy
      list<Dice *>::iterator it = dices.begin();
      advance(it, occupantDiceIndex);
      
       string actualType = (*it)->getActualType();
      if(actualType.compare("RedDice") != 0 && actualType.compare("Dice") != 0){ //redDices cannot be pushed
        bool call4neighourMove = (*it)->move("down", dices);
        if(call4neighourMove) //calls recursevely the move on left for the dice on his left (if it can be done moves in turn)
          makeMove(x, y+1);
        return call4neighourMove;
      }else
        return false;
    } 
  }
}