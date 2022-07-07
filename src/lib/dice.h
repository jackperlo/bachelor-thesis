#ifndef DICE_H
#define DICE_H

#include "common.h"
#include "cell.h"
#include "p2d.h"

class Dice{
  protected:
    Cell position;
    int nMoves;
    int initialMoves;
    pair<bool, int> virtual moveSx(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool isJustForSimulation, int movementType = SIMPLE_MOVE) = 0; 
    pair<bool, int> virtual moveDx(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool isJustForSimulation, int movementType = SIMPLE_MOVE) = 0;
    pair<bool, int> virtual moveUp(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool isJustForSimulation, int movementType = SIMPLE_MOVE) = 0;
    pair<bool, int> virtual moveDown(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool isJustForSimulation, int movementType = SIMPLE_MOVE) = 0;
    pair<bool, int> virtual reverseMoveSx(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool isJustForSimulation) = 0;
    pair<bool, int> virtual reverseMoveDx(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool isJustForSimulation) = 0;
    pair<bool, int> virtual reverseMoveUp(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool isJustForSimulation) = 0;
    pair<bool, int> virtual reverseMoveDown(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool isJustForSimulation) = 0;
    int checkArrivalCellIsEmpty(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> dices); //returns -1 if it's Empty
    bool makeMove(int x, int y, int nMovesDone, unordered_map<P2D, Dice *, P2D::HashFun> &dices);
    string stringToLower(string inputString);

  public:
    Dice(Cell position, int nMoves, int initialMoves);
    Dice();
    string virtual print_dice_to_string (bool print_with_initial_moves) = 0;
    bool operator==(Dice *other_dice);
    void setPosition(Cell position);
    Cell getPosition() const;
    void setNMoves(int nMoves);
    int getNMoves();
    int getInitialMoves();
    void printDice();
    pair<bool, int> move(string direction, unordered_map<P2D, Dice *, P2D::HashFun> &dices, char const * callerName, bool isJustForSimulation, int movementType = SIMPLE_MOVE);
    pair<bool, int> virtual reverseMove(string direction, unordered_map<P2D, Dice *, P2D::HashFun> &dices, char const * callerName, bool isJustForSimulation, int movementType = SIMPLE_MOVE) = 0;
    string virtual getActualType() = 0;
    int virtual getActualTypeInt() = 0;
};

#endif