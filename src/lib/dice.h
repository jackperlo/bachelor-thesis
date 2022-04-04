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
    int checkArrivalCellIsEmpty(int x, int y, list<Dice *> dices); //returns -1 if it's Empty
    bool makeActiveMove(int x, int y); //nMoves -= 1
    bool makePassiveMove(int x, int y); //nMoves remains the same (used when a dice having nMoves=0 is pushed)
    string stringToLower(string inputString);

  public:
    Dice(Cell position, int nMoves);
    Dice();
    void setPosition(Cell position);
    Cell getPosition();
    void setNMoves(int nMoves);
    int getNMoves();
    void printDice();
    bool virtual move(string direction, list<Dice *> dices, char const * callerName) = 0;
    string virtual getActualType() = 0;
};

#endif