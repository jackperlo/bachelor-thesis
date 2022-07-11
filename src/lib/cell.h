#ifndef CELL_H
#define CELL_H

#include "common.h"

class Cell{
  public:
    Cell(int x, int y);
    Cell();
    int get_x();
    void setX(int x);
    int get_y();
    void setY(int y);

  private:
    int x, y;
};

#endif