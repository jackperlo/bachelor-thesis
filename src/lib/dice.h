#ifndef DICE_H
#define DICE_H

#include "cell.h"

class Dice{
  protected:
    Cell position;
    int nMoves;

  public:
    Dice(Cell position, int nMoves);
    Dice();
    void setPosition(Cell position);
    int getPosition();
    void setNMoves(int nMoves);
    void virtual move(Cell toCoordinate);
    void printDice();
};

#endif