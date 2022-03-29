#ifndef WHITE_DICE_H
#define WHITE_DICE_H

#include "dice.h"
#include "cell.h"

class WhiteDice : public Dice{
  public:
    WhiteDice(Cell position, int nMoves);
    WhiteDice(const WhiteDice &wd1); //copying constructor
    void move(Cell toCoordinate) override;
};

#endif