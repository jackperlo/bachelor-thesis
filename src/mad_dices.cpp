#include <iostream>
#include <random>
#include <bits/stdc++.h>
#include "./lib/white_dice.h"
using namespace std;

#define N_DICES 5
#define MAP_WIDTH 5
#define MAP_HEIGHT 7

void printDices(list<Dice> dices);
void generateDices(list<Dice> *dices);

int main(){ 
  list<Dice> dices;
  generateDices(&dices);
  printDices(dices);

  Cell c(1, 2);
  WhiteDice wd(c, 3);
  cout << "Test " << wd.getPosition() << endl;

  return 0;
}

void printDices(list<Dice> dices){
  for (auto dice : dices)
    dice.printDice();
}

void generateDices(list<Dice> *dices){
  random_device rd;
  mt19937 rng(rd());
  uniform_int_distribution<int> distDice(1, 6); //distribution in range [1, 6]
  uniform_int_distribution<int> distWidth(0, MAP_WIDTH); 
  uniform_int_distribution<int> distHeight(0, MAP_HEIGHT);

  for (int i = 0; i < N_DICES; i++){
    Cell c(distWidth(rng), distHeight(rng));

    WhiteDice d(c, distDice(rng));
    (*dices).push_front(d);
  }
}









