#ifndef WHITE_DICE_H
#define WHITE_DICE_H

#include "common.h"
#include "dice.h"
#include "cell.h"

class WhiteDice : public Dice{
  public:
    WhiteDice(Cell position, int nMoves);
    WhiteDice();
    WhiteDice(const WhiteDice &wd1); //copying constructor, invoked in situation as: WhiteDice wd1 = wd2.
    string getActualType();

  protected:
    pair<bool, int> moveSx(int x, int y, list<Dice *> dices) override;
    pair<bool, int> moveDx(int x, int y, list<Dice *> dices) override;
    pair<bool, int> moveUp(int x, int y, list<Dice *> dices) override;
    pair<bool, int> moveDown(int x, int y, list<Dice *> dices) override;
};

//#define move(direction, dices) move(direction, dices, __func__)

#endif