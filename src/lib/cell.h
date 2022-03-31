#ifndef CELL_H
#define CELL_H

#include "common.h"

class Cell{
  public:
    Cell(int x, int y);
    Cell();
    Cell(const Cell &c1); //copying constructor
    int getX();
    int getY();

  private:
    int x, y;
};

#endif