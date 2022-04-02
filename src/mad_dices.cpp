#include "lib/common.h"
#include "./lib/white_dice.h"
#include "./lib/red_dice.h"
#include "./lib/yellow_dice.h"

bool checkIfDiceAlreadyExists(list<Dice *> dices, Cell c);
list <Dice *> generateDices();
void printDices(list<Dice *> dices);

int main(){ 
  list<Dice *> dices = generateDices();
  
  printDices(dices);

  //list<Dice *>::iterator it = dices.begin(); //returns a pointer to a pointer of type Dice
  //(*it)->move("sx", dices);
  //printDices(dices);
  
  return 0;
}

list<Dice *> generateDices(){
  list<Dice *> dices;

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
  
    alreadyExists = checkIfDiceAlreadyExists(dices, c);
    if(!alreadyExists){
      dices.push_back(d);
      i++;
    }
  }

  return dices;
}

bool checkIfDiceAlreadyExists(list<Dice *> dices, Cell c){
  for(auto dice : dices)
    if(dice->getPosition().getX() == c.getX() && dice->getPosition().getY() == c.getY())
      return true;
  
  return false;
}

void printDices(list<Dice *> dices){
  for (auto dice : dices)
    dice->printDice();
}








