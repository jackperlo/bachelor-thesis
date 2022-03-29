#include "white_dice.h"

#include <iostream>
using namespace std;

WhiteDice::WhiteDice(Cell position, int nMoves) : Dice(position, nMoves){}

void WhiteDice::move(Cell toCoordinate){
  cout << "Moving a White Dice";
}