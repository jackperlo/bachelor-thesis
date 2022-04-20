#ifndef GREEN_DICE_H
#define GREEN_DICE_H

#include "common.h"
#include "dice.h"
#include "cell.h"

class GreenDice : public Dice{
  public:
    GreenDice(Cell position, int nMoves);
    GreenDice();
    operator string ();
    GreenDice(const GreenDice &gd1); //copying constructor, invoked in situation as: GreenDice gd1 = gd2.
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