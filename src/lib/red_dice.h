#ifndef RED_DICE_H
#define RED_DICE_H

#include "common.h"
#include "dice.h"
#include "cell.h"

class RedDice : public Dice{
  public:
    RedDice(Cell position, int nMoves);
    RedDice();
    RedDice(const RedDice &rd1); //copying constructor, invoked in situation as: RedDice rd1 = rd2.
    bool move(string direction, list<Dice *> dices, char const * callerName) override;
    string getActualType();

  private:
    bool moveSx(int x, int y, list<Dice *> dices) override;
    bool moveDx(int x, int y, list<Dice *> dices) override;
    bool moveUp(int x, int y, list<Dice *> dices) override;
    bool moveDown(int x, int y, list<Dice *> dices) override;
};

#endif