#ifndef GREEN_DICE_H
#define GREEN_DICE_H

#include "common.h"
#include "dice.h"
#include "cell.h"

class GreenDice : public Dice{
  public:
    GreenDice(Cell position, int nMoves);
    GreenDice();
    GreenDice(const GreenDice &gd1); //copying constructor, invoked in situation as: GreenDice gd1 = gd2.
    string getActualType();

  protected:
    bool moveSx(int x, int y, list<Dice *> dices) override;
    bool moveDx(int x, int y, list<Dice *> dices) override;
    bool moveUp(int x, int y, list<Dice *> dices) override;
    bool moveDown(int x, int y, list<Dice *> dices) override;
};

#endif