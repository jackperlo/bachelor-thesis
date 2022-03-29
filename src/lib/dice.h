#ifndef DICE_H
#define DICE_H

#include <string>
#include "cell.h"
using namespace std;

class Dice{
  protected:
    Cell *position;
    int nMoves;

  public:
    Dice(Cell *position, int nMoves);
    void virtual move(Cell *toCoordinate) = 0;
    void setPosition(Cell *position);
    void setNMoves(int nMoves);
};

#endif