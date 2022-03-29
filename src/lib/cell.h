#ifndef CELL_H
#define CELL_H

class Cell{
  public:
    Cell(int x, int y);
    int getCoordinates();

  private:
    int x, y;

  //TODO: develop .equals to compare 2 different cell instead of 
  //using getCoordinates

};

#endif