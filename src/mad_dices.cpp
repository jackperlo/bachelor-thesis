#include "lib/common.h"
#include "./lib/white_dice.h"

void generateDices(list<Dice *> *dices);
void printDices(list<Dice *> dices);

int main(){ 
  list<Dice *> dices;

  generateDices(&dices);
  printDices(dices);

  return 0;
}

void generateDices(list<Dice *> *dices){
  random_device rd;
  mt19937 rng(rd());
  uniform_int_distribution<int> distDice(1, 6);
  uniform_int_distribution<int> distWidth(0, MAP_WIDTH); 
  uniform_int_distribution<int> distHeight(0, MAP_HEIGHT);

  bool alreadyExists = false;
  int i = 0;
  while(i < N_DICES){
    alreadyExists = false;
    Cell c(distWidth(rng), distHeight(rng));
    WhiteDice *d = new WhiteDice(c, distDice(rng));
  
    for(auto dice : *dices){
      if(dice->getPosition().getX() == c.getX() && dice->getPosition().getY() == c.getY())
        alreadyExists = true;
    }
    if(!alreadyExists){
      (*dices).push_back(d);
      i++;
    }

  }
}

void printDices(list<Dice *> dices){
  for (auto dice : dices)
    (*dice).printDice();
}








