#ifndef WHITE_DICE_H
#define WHITE_DICE_H

#include "common.h"
#include "dice.h"
#include "cell.h"

class WhiteDice : public Dice{
  public:
    WhiteDice(Cell position, int nMoves);
    WhiteDice(const WhiteDice &wd1); //copying constructor
    void move(string direction) override;
};

#endif