#ifndef YELLOW_DICE_H
#define YELLOW_DICE_H

#include "common.h"
#include "dice.h"
#include "cell.h"

class YellowDice : public Dice{
  public:
    YellowDice(Cell position, int nMoves);
    YellowDice();
    YellowDice(const YellowDice &yd1); //copying constructor, invoked in situation as: YellowDice yd1 = yd2.
    bool move(string direction, list<Dice *> dices) override;
    string getActualType();

  private:
    bool moveSx(int x, int y, list<Dice *> dices) override;
    bool moveDx(int x, int y, list<Dice *> dices) override;
    bool moveUp(int x, int y, list<Dice *> dices) override;
    bool moveDown(int x, int y, list<Dice *> dices) override;
};

#endif