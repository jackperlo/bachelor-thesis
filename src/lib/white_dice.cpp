#include "common.h"
#include "white_dice.h"

WhiteDice::WhiteDice(Cell position, int nMoves) : Dice(position, nMoves){}

WhiteDice::WhiteDice(const WhiteDice &wd1){position = wd1.position; nMoves = wd1.nMoves;}

void WhiteDice::move(string direction){
  cout << "TESTAMI MOVE WD";
}