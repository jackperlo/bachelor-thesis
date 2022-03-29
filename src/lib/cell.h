#ifndef CELL_H
#define CELL_H

class Cell{
  public:
    Cell(int x, int y);
    Cell();
    Cell(const Cell &c1); //copying constructor
    int getCoordinates();

  private:
    int x, y;
};

#endif