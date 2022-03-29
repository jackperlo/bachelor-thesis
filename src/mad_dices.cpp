#include <iostream>
#include "./lib/white_dice.h"

using namespace std;

void makeMap();

int main(){ 
  makeMap();

  Cell c(1, 2);
  WhiteDice wd(c, 3);
  cout << "Test " << wd.getPosition() << endl;

  return 0;
}

void makeMap(){

}

