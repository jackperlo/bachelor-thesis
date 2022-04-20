#ifndef RED_DICE_H
#define RED_DICE_H

#include "common.h"
#include "dice.h"
#include "cell.h"

class RedDice : public Dice{
  public:
    RedDice(Cell position, int nMoves);
    RedDice();
    RedDice(const RedDice &rd1); //copying constructor, invoked in situation as: RedDice rd1 = rd2.
    operator string ();
    string getActualType();
    int getActualTypeInt();
    pair<bool, int> reverseMove(string direction, unordered_map<P2D, Dice *, P2D::HashFun> dices, char const * callerName, bool isJustForSimulation, bool isPushed = false) override;

  protected:
    pair<bool, int> moveSx(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> dices, bool isJustForSimulation) override;
    pair<bool, int> moveDx(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> dices, bool isJustForSimulation) override;
    pair<bool, int> moveUp(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> dices, bool isJustForSimulation) override;
    pair<bool, int> moveDown(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> dices, bool isJustForSimulation) override;
    pair<bool, int> reverseMoveSx(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> dices, bool isJustForSimulation) override;
    pair<bool, int> reverseMoveDx(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> dices, bool isJustForSimulation) override;
    pair<bool, int> reverseMoveUp(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> dices, bool isJustForSimulation) override;
    pair<bool, int> reverseMoveDown(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> dices, bool isJustForSimulation) override;
};

#endif