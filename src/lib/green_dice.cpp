#include "common.h"
#include "red_dice.h"
#include "white_dice.h"
#include "yellow_dice.h"
#include "green_dice.h"
#include "p2d.h"
#include <typeinfo>
#include <typeindex>

int MAP_WIDTH;
int MAP_HEIGHT;
int TOTAL_MOVES;

GreenDice::GreenDice(Cell position, int nMoves, int initial_moves) : Dice(position, nMoves, initial_moves){}

GreenDice::GreenDice() : Dice(){}

GreenDice::GreenDice(const GreenDice &gd1) : Dice(gd1){position = gd1.position; nMoves = gd1.nMoves;}

string GreenDice::print_dice_to_string (bool print_with_initial_moves) {
  string t = "";
  if(!print_with_initial_moves)
    t = BGGRE(this->get_n_moves());
  else
    t = BGGRE(this->get_initial_moves());
  return t;
}

string GreenDice::get_actual_type(){
  type_index ti(typeid(*this));
  RedDice rd;
  WhiteDice wd;
  YellowDice yd;
  GreenDice gd;
  if (ti == type_index(typeid(rd)))
    return "RedDice";
  else if (ti == type_index(typeid(wd)))
    return "WhiteDice";
  else if (ti == type_index(typeid(yd)))
    return "YellowDice";
  else if (ti == type_index(typeid(gd)))
    return "GreenDice"; 
  else
    return "Dice";
}

int GreenDice::get_actual_type_int(){
  type_index ti(typeid(*this));
  RedDice rd;
  WhiteDice wd;
  YellowDice yd;
  GreenDice gd;
  if (ti == type_index(typeid(wd)))
    return 0;
  else if (ti == type_index(typeid(rd)))
    return 1;
  else if (ti == type_index(typeid(yd)))
    return 2;
  else if (ti == type_index(typeid(gd)))
    return 3; 
  else
    return -1;
}

pair<bool, int> GreenDice::reverse_move(string direction, unordered_map<P2D, Dice *, P2D::HashFun> &dices, char const * /* caller_name unused */, bool is_a_simulation, int movement_type){
  direction = string_to_lower(direction);
  int x = this->get_position().get_x();
  int y = this->get_position().get_y();
  pair<bool, int> res = NO_MOVE;
  int i = 1;
  if(movement_type == PUSHED_MOVE){
    if(direction.compare("left") == 0){
      while(x-i>=0){
        if(dices.find(P2D::cellToP2D(Cell(x-i, y))) != dices.end() && (x == MAP_WIDTH-1 || dices.find(P2D::cellToP2D(Cell(x+1, y))) != dices.end())){ //if there's a right side or is a boundary cell 
          if(dices.at(P2D::cellToP2D(Cell(x-i, y)))->get_actual_type().compare("WhiteDice") == 0 || dices.at(P2D::cellToP2D(Cell(x-i, y)))->get_actual_type().compare("RedDice") == 0){
            res = dices.at(P2D::cellToP2D(Cell(x-i, y)))->reverse_move("left", dices, __func__, is_a_simulation, movement_type);
            if(res.first){
              res.second += i;
              if(!is_a_simulation)
                this->make_move(x-i, y, 0, dices);
            } 
          }
          break;
        }
        i++;
      }
    }
    else if(direction.compare("right") == 0){
      while(x+i<MAP_WIDTH){
        if(dices.find(P2D::cellToP2D(Cell(x+i, y))) != dices.end() && (x == 0 || dices.find(P2D::cellToP2D(Cell(x-1, y))) != dices.end())){ //if there's a left side or is a boundary cell 
          if(dices.at(P2D::cellToP2D(Cell(x+i, y)))->get_actual_type().compare("WhiteDice") == 0 || dices.at(P2D::cellToP2D(Cell(x+i, y)))->get_actual_type().compare("RedDice") == 0){
            res = dices.at(P2D::cellToP2D(Cell(x+i, y)))->reverse_move("right", dices, __func__, is_a_simulation, movement_type);
            if(res.first){
              res.second += i;
              if(!is_a_simulation)
                this->make_move(x+i, y, 0, dices);
            } 
          }
          break;
        }
        i++;
      }
    }
    else if(direction.compare("up") == 0){
      while(y-i>=0){
        if(dices.find(P2D::cellToP2D(Cell(x, y-i))) != dices.end() && (y == MAP_HEIGHT-1 || dices.find(P2D::cellToP2D(Cell(x, y+1))) != dices.end())){ //if there's a down side or is a boundary cell          
          if(dices.at(P2D::cellToP2D(Cell(x, y-i)))->get_actual_type().compare("WhiteDice") == 0 || dices.at(P2D::cellToP2D(Cell(x, y-i)))->get_actual_type().compare("RedDice") == 0){
            res = dices.at(P2D::cellToP2D(Cell(x, y-i)))->reverse_move("up", dices, __func__, is_a_simulation, movement_type);
            if(res.first){
              res.second += i;
              if(!is_a_simulation)
                this->make_move(x, y-i, 0, dices);
            } 
          }
          break;
        }
        i++;
      }
    }
    else if(direction.compare("down") == 0){
      while(y+i<MAP_HEIGHT){
        if(dices.find(P2D::cellToP2D(Cell(x, y+i))) != dices.end() && (y == 0 || dices.find(P2D::cellToP2D(Cell(x, y-1))) != dices.end())){ //if there's an up side or is a boundary cell 
          if(dices.at(P2D::cellToP2D(Cell(x, y+i)))->get_actual_type().compare("WhiteDice") == 0 || dices.at(P2D::cellToP2D(Cell(x, y+i)))->get_actual_type().compare("RedDice") == 0){
            res = dices.at(P2D::cellToP2D(Cell(x, y+i)))->reverse_move("down", dices, __func__, is_a_simulation, movement_type);
            if(res.first){
              res.second += i;
              if(!is_a_simulation)
                this->make_move(x, y+i, 0, dices);
            } 
          }
          break;
        }
        i++;
      }
    }
  }else{ //dice moving by itself
    if(direction.compare("left") == 0){
      res = reverse_move_left(x, y, dices, is_a_simulation);
      if(res.first && !is_a_simulation)
        this->make_move(x-res.second, y, res.second, dices);  
    }
    else if(direction.compare("right") == 0){
      res = reverse_move_right(x, y, dices, is_a_simulation);
      if(res.first && !is_a_simulation)
        this->make_move(x+res.second, y, res.second, dices);  
    }
    else if(direction.compare("up") == 0){
      res = reverse_move_up(x, y, dices, is_a_simulation);
      if(res.first && !is_a_simulation)
        this->make_move(x, y-res.second, res.second, dices);  
    }
    else if(direction.compare("down") == 0){
      res = reverse_move_down(x, y, dices, is_a_simulation);
      if(res.first && !is_a_simulation)
        this->make_move(x, y+res.second, res.second, dices);
    }
  }
  return res;
}

pair<bool, int> GreenDice::reverse_move_left(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool /* is_a_simulation unused */){
  int i = 1;
  pair<bool, int> res = NO_MOVE;
  while(x-i >= 0 && this->get_n_moves()-res.second > 0 && check_arrival_cell_is_empty(x-i, y, dices)){ 
    res.first = true;
    res.second ++;
    i++;
  }
  
  return res;
}

pair<bool, int> GreenDice::reverse_move_right(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool /* is_a_simulation unused */){
  int i = 1;
  pair<bool, int> res = NO_MOVE;
  while(x+i < MAP_WIDTH && this->get_n_moves()-res.second > 0 && check_arrival_cell_is_empty(x+i, y, dices)){ 
    res.first = true;
    res.second ++;
    i++;
  }
  
  return res;
}

pair<bool, int> GreenDice::reverse_move_up(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool /* is_a_simulation unused */){
  int i = 1;
  pair<bool, int> res = NO_MOVE;
  while(y-i >= 0 && this->get_n_moves()-res.second > 0 && check_arrival_cell_is_empty(x, y-i, dices)){ 
    res.first = true;
    res.second ++;
    i++;
  }
  
  return res;
}

pair<bool, int> GreenDice::reverse_move_down(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool /* is_a_simulation unused */){
  int i = 1;
  pair<bool, int> res = NO_MOVE;
  while(y+i < MAP_HEIGHT && this->get_n_moves()-res.second > 0 && check_arrival_cell_is_empty(x, y+i, dices)){ 
    res.first = true;
    res.second ++;
    i++;
  }
  
  return res;
}

pair<bool, int> GreenDice::move_left(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool /* is_a_simulation unused */, int movement_type){
  int i = 1;
  pair<bool, int> res = NO_MOVE;
  if(movement_type == PUSHED_MOVE || this->get_n_moves() == 0){ //moving when pushed
    while(x-i >= 0 && check_arrival_cell_is_empty(x-i, y, dices)){ //arrival cell is not out of map bounds and empty
      res.first = true;
      res.second ++;
      i++;
    }
  }else{ //moving actively
    while(x-i >= 0 && check_arrival_cell_is_empty(x-i, y, dices) && this->get_n_moves()-res.second > 0){ //arrival cell is not out of map bounds, is empty and there are moves available
      res.first = true;
      res.second ++;
      i++;
    }
  }
  return res;
}

pair<bool, int> GreenDice::move_right(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool /* is_a_simulation unused */, int movement_type){
  int i = 1;
  pair<bool, int> res = NO_MOVE;
  if(movement_type == PUSHED_MOVE || this->get_n_moves() == 0){ //moving when pushed
    while(x+i < MAP_WIDTH && check_arrival_cell_is_empty(x+i, y, dices)){ //arrival cell is not out of map bounds and empty
      res.first = true;
      res.second ++;
      i++;
    }
  }else{ //moving actively
    while(x+i < MAP_WIDTH && check_arrival_cell_is_empty(x+i, y, dices) && this->get_n_moves()-res.second > 0){ //arrival cell is not out of map bounds, is empty and there are moves available
      res.first = true;
      res.second ++;
      i++;
    }
  }
  return res;
}

pair<bool, int> GreenDice::move_up(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool /* is_a_simulation unused */, int movement_type){
  int i = 1;
  pair<bool, int> res = NO_MOVE;
  if(movement_type == PUSHED_MOVE || this->get_n_moves() == 0){ //moving when pushed
    while(y-i >= 0 && check_arrival_cell_is_empty(x, y-i, dices)){ //arrival cell is not out of map bounds and empty
      res.first = true;
      res.second ++;
      i++;
    }
  }else{ //moving actively
    while(y-i >= 0 && check_arrival_cell_is_empty(x, y-i, dices) && this->get_n_moves()-res.second > 0){ //arrival cell is not out of map bounds, is empty and there are moves available
      res.first = true;
      res.second ++;
      i++;
    }
  }
  return res;
}

pair<bool, int> GreenDice::move_down(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool /* is_a_simulation unused */, int movement_type){
  int i = 1;
  pair<bool, int> res = NO_MOVE;
  if(movement_type == PUSHED_MOVE || this->get_n_moves() == 0){ //moving when pushed
    while(y+i < MAP_HEIGHT && check_arrival_cell_is_empty(x, y+i, dices)){ //arrival cell is not out of map bounds and empty
      res.first = true;
      res.second ++;
      i++;
    }
  }else{ //moving actively
    while(y+i < MAP_HEIGHT && check_arrival_cell_is_empty(x, y+i, dices) && this->get_n_moves()-res.second > 0){ //arrival cell is not out of map bounds, is empty and there are moves available
      res.first = true;
      res.second ++;
      i++;
    }
  }
  return res;
}