#ifndef WHITE_DICE_H
#define WHITE_DICE_H

#include "common.h"
#include "dice.h"
#include "cell.h"

class WhiteDice : public Dice{
  public:
    WhiteDice(Cell position, int nMoves);
    WhiteDice(const WhiteDice &wd1); //copying constructor, invoked in situation as: WhiteDice wd1 = wd2.
    bool move(string direction, list<Dice *> dices) override;

  private:
    bool moveSx(int x, int y, list<Dice *> dices) override;
    bool moveDx(int x, int y, list<Dice *> dices) override;
    bool moveUp(int x, int y, list<Dice *> dices) override;
    bool moveDown(int x, int y, list<Dice *> dices) override;
    string stringToLower(string inputString);
    int checkArrivalCellIsEmpty(int x, int y, list<Dice *> dices); //returns -1 if it's Empty
    void makeMove(int x, int y);
};

#endif