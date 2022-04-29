#ifndef RED_DICE_H
#define RED_DICE_H

#include "common.h"
#include "dice.h"
#include "cell.h"

class RedDice : public Dice{
  public:
    RedDice(Cell position, int nMoves, int initialMoves);
    RedDice();
    RedDice(const RedDice &rd1); //copying constructor, invoked in situation as: RedDice rd1 = rd2.
    operator string () override;
    string getActualType() override;
    int getActualTypeInt() override;
    pair<bool, int> reverseMove(string direction, unordered_map<P2D, Dice *, P2D::HashFun> &dices, char const * callerName, bool isJustForSimulation, int movementType = 0) override;

  protected:
    pair<bool, int> call4reverseMove(string direction, unordered_map<P2D, Dice *, P2D::HashFun> &dices, char const * callerName, bool isJustForSimulation, int movementType = 0);
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