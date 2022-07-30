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
  if(movement_type == PUSHED_MOVE){
    if(direction.compare("left") == 0){
      if(dices.find(P2D::cellToP2D(Cell(x-1, y))) != dices.end()){ //if there's a right side or is a boundary cell 
        if(dices.at(P2D::cellToP2D(Cell(x-1, y)))->get_actual_type().compare("WhiteDice") == 0 || dices.at(P2D::cellToP2D(Cell(x-1, y)))->get_actual_type().compare("RedDice") == 0){
          res = dices.at(P2D::cellToP2D(Cell(x-1, y)))->reverse_move("left", dices, __func__, is_a_simulation, movement_type);
          if(res.first){
            res.second = 1;
            if(!is_a_simulation)
              this->make_move(x-1, y, 0, dices);
          } 
        }
      }
    }
    else if(direction.compare("right") == 0){
      if(dices.find(P2D::cellToP2D(Cell(x+1, y))) != dices.end()){ //if there's a left side or is a boundary cell 
        if(dices.at(P2D::cellToP2D(Cell(x+1, y)))->get_actual_type().compare("WhiteDice") == 0 || dices.at(P2D::cellToP2D(Cell(x+1, y)))->get_actual_type().compare("RedDice") == 0){
          res = dices.at(P2D::cellToP2D(Cell(x+1, y)))->reverse_move("right", dices, __func__, is_a_simulation, movement_type);
          if(res.first){
            res.second = 1;
            if(!is_a_simulation)
              this->make_move(x+1, y, 0, dices);
          } 
        }
      }
    }
    else if(direction.compare("up") == 0){
      if(dices.find(P2D::cellToP2D(Cell(x, y-1))) != dices.end()){ //if there's a down side or is a boundary cell          
        if(dices.at(P2D::cellToP2D(Cell(x, y-1)))->get_actual_type().compare("WhiteDice") == 0 || dices.at(P2D::cellToP2D(Cell(x, y-1)))->get_actual_type().compare("RedDice") == 0){
          res = dices.at(P2D::cellToP2D(Cell(x, y-1)))->reverse_move("up", dices, __func__, is_a_simulation, movement_type);
          if(res.first){
            res.second = 1;
            if(!is_a_simulation)
              this->make_move(x, y-1, 0, dices);
          } 
        }
      }
    }
    else if(direction.compare("down") == 0){
      if(dices.find(P2D::cellToP2D(Cell(x, y+1))) != dices.end()){ //if there's an up side or is a boundary cell 
        if(dices.at(P2D::cellToP2D(Cell(x, y+1)))->get_actual_type().compare("WhiteDice") == 0 || dices.at(P2D::cellToP2D(Cell(x, y+1)))->get_actual_type().compare("RedDice") == 0){
          res = dices.at(P2D::cellToP2D(Cell(x, y+1)))->reverse_move("down", dices, __func__, is_a_simulation, movement_type);
          if(res.first){
            res.second = 1;
            if(!is_a_simulation)
              this->make_move(x, y+1, 0, dices);
          } 
        }
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

pair<bool, int> GreenDice::move_left(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool is_a_simulation, int movement_type){
  int i = 1;
  pair<bool, int> res = NO_MOVE;
  if(movement_type == PUSHED_MOVE || this->get_n_moves() == 0){ //moving when pushed
    if(x-1 >= 0){
      if(check_arrival_cell_is_empty(x-1, y, dices))
        return MOVE_BY_1;
      else{
        string actualType = dices.at(P2D(x-1, y))->get_actual_type();
        if(actualType.compare("RedDice") != 0 && actualType.compare("Dice") != 0){ //redDices cannot be pushed  
          if(dices.at(P2D(x-1, y))->move("left", dices, __func__, is_a_simulation, movement_type).first) //calls recursevely the move on left for the dice on his left (if it can be done moves in turn)
            return MOVE_BY_1;
          else 
            return NO_MOVE;
        }
        return NO_MOVE;
      }
    }
    return NO_MOVE;
  }else{ //moving actively
    while(x-i >= 0 && check_arrival_cell_is_empty(x-i, y, dices) && this->get_n_moves()-res.second > 0){ //arrival cell is not out of map bounds, is empty and there are moves available
      res.first = true;
      res.second ++;
      i++;
    }
  }
  return res;
}

pair<bool, int> GreenDice::move_right(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool is_a_simulation, int movement_type){
  int i = 1;
  pair<bool, int> res = NO_MOVE;
  if(movement_type == PUSHED_MOVE || this->get_n_moves() == 0){ //moving when pushed
     if(x+1 < MAP_HEIGHT){
      if(check_arrival_cell_is_empty(x+1, y, dices))
        return MOVE_BY_1;
      else{
        string actualType = dices.at(P2D(x+1, y))->get_actual_type();
        if(actualType.compare("RedDice") != 0 && actualType.compare("Dice") != 0){ //redDices cannot be pushed  
          if(dices.at(P2D(x+1, y))->move("right", dices, __func__, is_a_simulation, movement_type).first) //calls recursevely the move on right for the dice on his right (if it can be done moves in turn)
            return MOVE_BY_1;
          else 
            return NO_MOVE;
        }
        return NO_MOVE;
      }
    }
    return NO_MOVE;
  }else{ //moving actively
    while(x+i < MAP_WIDTH && check_arrival_cell_is_empty(x+i, y, dices) && this->get_n_moves()-res.second > 0){ //arrival cell is not out of map bounds, is empty and there are moves available
      res.first = true;
      res.second ++;
      i++;
    }
  }
  return res;
}

pair<bool, int> GreenDice::move_up(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool is_a_simulation, int movement_type){
  int i = 1;
  pair<bool, int> res = NO_MOVE;
  if(movement_type == PUSHED_MOVE || this->get_n_moves() == 0){ //moving when pushed
     if(y-1 >= 0){
      if(check_arrival_cell_is_empty(x, y-1, dices))
        return MOVE_BY_1;
      else{
        string actualType = dices.at(P2D(x, y-1))->get_actual_type();
        if(actualType.compare("RedDice") != 0 && actualType.compare("Dice") != 0){ //redDices cannot be pushed  
          if(dices.at(P2D(x, y-1))->move("up", dices, __func__, is_a_simulation, movement_type).first) //calls recursevely the move up (if it can be done moves in turn)
            return MOVE_BY_1;
          else 
            return NO_MOVE;
        }
        return NO_MOVE;
      }
    }
    return NO_MOVE;
  }else{ //moving actively
    while(y-i >= 0 && check_arrival_cell_is_empty(x, y-i, dices) && this->get_n_moves()-res.second > 0){ //arrival cell is not out of map bounds, is empty and there are moves available
      res.first = true;
      res.second ++;
      i++;
    }
  }
  return res;
}

pair<bool, int> GreenDice::move_down(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool is_a_simulation, int movement_type){
  int i = 1;
  pair<bool, int> res = NO_MOVE;
  if(movement_type == PUSHED_MOVE || this->get_n_moves() == 0){ //moving when pushed
     if(y+1 >= 0){
      if(check_arrival_cell_is_empty(x, y+1, dices))
        return MOVE_BY_1;
      else{
        string actualType = dices.at(P2D(x, y+1))->get_actual_type();
        if(actualType.compare("RedDice") != 0 && actualType.compare("Dice") != 0){ //redDices cannot be pushed  
          if(dices.at(P2D(x, y+1))->move("down", dices, __func__, is_a_simulation, movement_type).first) //calls recursevely the move down (if it can be done moves in turn)
            return MOVE_BY_1;
          else 
            return NO_MOVE;
        }
        return NO_MOVE;
      }
    }
    return NO_MOVE;
  }else{ //moving actively
    while(y+i < MAP_HEIGHT && check_arrival_cell_is_empty(x, y+i, dices) && this->get_n_moves()-res.second > 0){ //arrival cell is not out of map bounds, is empty and there are moves available
      res.first = true;
      res.second ++;
      i++;
    }
  }
  return res;
}