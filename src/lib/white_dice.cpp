#include "common.h"
#include "white_dice.h"

WhiteDice::WhiteDice(Cell position, int nMoves) : Dice(position, nMoves){}

WhiteDice::WhiteDice(const WhiteDice &wd1){position = wd1.position; nMoves = wd1.nMoves;}

bool WhiteDice::move(string direction, list<Dice *> dices){
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

string WhiteDice::stringToLower(string inputString){
  for_each(inputString.begin(), inputString.end(), [](char &c){c = tolower(c);}); 
  return inputString;
}

bool WhiteDice::moveSx(int x, int y, list<Dice *> dices){
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
      
      //!TODO: do the recursive call only...
      //if(typeid(*it) != red_dice){
      bool call4neighourMove = (*it)->move("sx", dices);
      if(call4neighourMove) //calls recursevely the move on left for the dice on his left (if it can be done moves in turn)
        makeMove(x-1, y);
      //}

      return call4neighourMove;
    } 
  }
}

bool WhiteDice::moveDx(int x, int y, list<Dice *> dices){
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
      
      //!TODO: do the recursive call only...
      //if(typeid(*it) != red_dice){
      bool call4neighourMove = (*it)->move("dx", dices);
      if(call4neighourMove) //calls recursevely the move on left for the dice on his left (if it can be done moves in turn)
        makeMove(x+1, y);
      //}

      return call4neighourMove;
    } 
  }
}

bool WhiteDice::moveUp(int x, int y, list<Dice *> dices){
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
      
      //!TODO: do the recursive call only...
      //if(typeid(*it) != red_dice){
      bool call4neighourMove = (*it)->move("up", dices);
      if(call4neighourMove) //calls recursevely the move on left for the dice on his left (if it can be done moves in turn)
        makeMove(x, y-1);
      //}

      return call4neighourMove;
    } 
  }
}

bool WhiteDice::moveDown(int x, int y, list<Dice *> dices){
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
      
      //!TODO: do the recursive call only...
      //if(typeid(*it) != red_dice){
      bool call4neighourMove = (*it)->move("down", dices);
      if(call4neighourMove) //calls recursevely the move on left for the dice on his left (if it can be done moves in turn)
        makeMove(x, y+1);
      //}

      return call4neighourMove;
    } 
  }
}

int WhiteDice::checkArrivalCellIsEmpty(int x, int y, list<Dice *> dices){
  int ret = -1, i=0;
  for(auto dice : dices){
    if(dice->getPosition().getX() == x && dice->getPosition().getY() == y){
      ret = i; //cell busy. Return the index(in the list) of the occupant Dice
      break;
    }
    i++;
  }
    
  
  return ret;
}

void WhiteDice::makeMove(int x, int y){
  Cell arrivalCell(x, y);
  this->setPosition(arrivalCell);
  this->setNMoves(this->getNMoves());
}