#ifndef YELLOW_DICE_H
#define YELLOW_DICE_H

#include "common.h"
#include "dice.h"
#include "cell.h"

class YellowDice : public Dice{
  public:
    YellowDice(Cell position, int nMoves, int initialMoves);
    YellowDice();
    YellowDice(const YellowDice &yd1); //copying constructor, invoked in situation as: YellowDice yd1 = yd2.
    operator string ();
    string getActualType();
    int getActualTypeInt();
    pair<bool, int> reverseMove(string direction, unordered_map<P2D, Dice *, P2D::HashFun> &dices, char const * callerName, bool isJustForSimulation, int movementType = 0) override;

  protected:
    pair<bool, int> moveSx(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool isJustForSimulation) override;
    pair<bool, int> moveDx(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool isJustForSimulation) override;
    pair<bool, int> moveUp(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool isJustForSimulation) override;
    pair<bool, int> moveDown(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool isJustForSimulation) override;
    pair<bool, int> reverseMoveSx(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool isJustForSimulation) override;
    pair<bool, int> reverseMoveDx(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool isJustForSimulation) override;
    pair<bool, int> reverseMoveUp(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool isJustForSimulation) override;
    pair<bool, int> reverseMoveDown(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool isJustForSimulation) override;
};

#endif