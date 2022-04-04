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
    bool move(string direction, list<Dice *> dices, char const * callerName) override;
    string getActualType();

  private:
    bool moveSx(int x, int y, list<Dice *> dices) override;
    bool moveDx(int x, int y, list<Dice *> dices) override;
    bool moveUp(int x, int y, list<Dice *> dices) override;
    bool moveDown(int x, int y, list<Dice *> dices) override;
};

//#define move(direction, dices) move(direction, dices, __func__)

#endif