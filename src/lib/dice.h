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
    //bool: check map bound and limit cases, int: offest movement
    pair<bool, int> virtual moveSx(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> dices, bool isJustForSimulation) = 0; 
    pair<bool, int> virtual moveDx(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> dices, bool isJustForSimulation) = 0;
    pair<bool, int> virtual moveUp(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> dices, bool isJustForSimulation) = 0;
    pair<bool, int> virtual moveDown(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> dices, bool isJustForSimulation) = 0;
    pair<bool, int> virtual reverseMoveSx(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> dices, bool isJustForSimulation) = 0;
    pair<bool, int> virtual reverseMoveDx(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> dices, bool isJustForSimulation) = 0;
    pair<bool, int> virtual reverseMoveUp(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> dices, bool isJustForSimulation) = 0;
    pair<bool, int> virtual reverseMoveDown(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> dices, bool isJustForSimulation) = 0;
    int checkArrivalCellIsEmpty(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> dices); //returns -1 if it's Empty
    bool makeMove(int x, int y, int nMovesDone, unordered_map<P2D, Dice *, P2D::HashFun> dices);
    string stringToLower(string inputString);

  public:
    Dice(Cell position, int nMoves, int initialMoves);
    Dice();
    virtual operator string () = 0;
    void setPosition(Cell position);
    Cell getPosition() const;
    void setNMoves(int nMoves);
    int getNMoves();
    int getInitialMoves();
    void printDice();
    bool move(string direction, unordered_map<P2D, Dice *, P2D::HashFun> dices, char const * callerName, bool isJustForSimulation);
    pair<bool, int> virtual reverseMove(string direction, unordered_map<P2D, Dice *, P2D::HashFun> dices, char const * callerName, bool isJustForSimulation, bool isPushed = false) = 0;
    string virtual getActualType() = 0;
    int virtual getActualTypeInt() = 0;
};

#endif