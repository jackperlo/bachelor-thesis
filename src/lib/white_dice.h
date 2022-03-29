#ifndef WHITE_DICE_H
#define WHITE_DICE_H

#include <string>
#include "cell.h"
using namespace std;

class WhiteDice : public Dice{
  protected:
    Cell *position;
    int nMoves;
    string color;

  public:
    WhiteDice(Cell *position, int nMoves);
    void move(Cell *toCoordinate) override;
};

#endif