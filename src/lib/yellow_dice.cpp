#include "common.h"
#include "red_dice.h"
#include "white_dice.h"
#include "yellow_dice.h"

YellowDice::YellowDice(Cell position, int nMoves) : Dice(position, nMoves){}

YellowDice::YellowDice() : Dice(){}

YellowDice::YellowDice(const YellowDice &yd1){position = yd1.position; nMoves = yd1.nMoves;}

string YellowDice::getActualType(){
  type_index ti(typeid(*this));
  RedDice rd;
  WhiteDice wd;
  YellowDice yd;
  if (ti == type_index(typeid(rd)))
    return "RedDice";
  else if (ti == type_index(typeid(wd)))
    return "WhiteDice";
  else if(ti == type_index(typeid(yd)))
    return "YellowDice";
  else
      return "Dice";
}


bool YellowDice::move(string direction, list<Dice *> dices, char const * callerName){
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

bool YellowDice::moveSx(int x, int y, list<Dice *> dices){}
bool YellowDice::moveDx(int x, int y, list<Dice *> dices){}
bool YellowDice::moveUp(int x, int y, list<Dice *> dices){}
bool YellowDice::moveDown(int x, int y, list<Dice *> dices){}