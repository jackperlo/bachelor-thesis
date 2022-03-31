#ifndef DICE_H
#define DICE_H

#include "common.h"
#include "cell.h"

class Dice{
  protected:
    Cell position;
    int nMoves;
    bool virtual moveSx(int x, int y, list<Dice *> dices) = 0;
    bool virtual moveDx(int x, int y, list<Dice *> dices) = 0;
    bool virtual moveUp(int x, int y, list<Dice *> dices) = 0;
    bool virtual moveDown(int x, int y, list<Dice *> dices) = 0;

  public:
    Dice(Cell position, int nMoves);
    Dice();
    void setPosition(Cell position);
    Cell getPosition();
    void setNMoves(int nMoves);
    int getNMoves();
    void printDice();
    bool virtual move(string direction, list<Dice *> dices) = 0;
};

#endif