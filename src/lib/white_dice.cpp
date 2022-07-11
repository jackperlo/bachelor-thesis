#include "common.h"
#include "white_dice.h"
#include "red_dice.h"
#include "yellow_dice.h"
#include "green_dice.h"
#include "p2d.h"
#include <typeinfo>
#include <typeindex>

WhiteDice::WhiteDice(Cell position, int nMoves, int initial_moves) : Dice(position, nMoves, initial_moves){}

WhiteDice::WhiteDice() : Dice(){}

WhiteDice::WhiteDice(const WhiteDice &wd1) : Dice(wd1){position = wd1.position; nMoves = wd1.nMoves;}

string WhiteDice::print_dice_to_string (bool print_with_initial_moves){
  string t = "";
  if(!print_with_initial_moves)
    t = BGWHT(this->get_n_moves());
  else
    t = BGWHT(this->get_initial_moves());
  return t;
}

string WhiteDice::get_actual_type(){
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

int WhiteDice::get_actual_type_int(){
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

pair<bool, int> WhiteDice::reverse_move(string direction, unordered_map<P2D, Dice *, P2D::HashFun> &dices, char const * caller_name, bool is_a_simulation, int movement_type){
  direction = string_to_lower(direction);
  int x = this->get_position().get_x();
  int y = this->get_position().get_y();
  pair<bool, int> res = NO_MOVE;
  bool isGoingToCallThirdParty = !((direction.compare("left") == 0 && check_arrival_cell_is_empty(x-1, y, dices)) || (direction.compare("right") == 0 && check_arrival_cell_is_empty(x+1, y, dices)) || (direction.compare("up") == 0 && check_arrival_cell_is_empty(x, y-1, dices)) || (direction.compare("down") == 0 && check_arrival_cell_is_empty(x, y+1, dices)));
  if(!isGoingToCallThirdParty){
    if(this->get_n_moves() > 0)
      return call4reverse_move(direction, dices, caller_name, is_a_simulation, movement_type);
  }else
    return call4reverse_move(direction, dices, caller_name, is_a_simulation, movement_type);
  return res;
}

pair<bool, int> WhiteDice::call4reverse_move(string direction, unordered_map<P2D, Dice *, P2D::HashFun> &dices, char const *, bool is_a_simulation, int /* movement_type unused */){
  direction = string_to_lower(direction);
  int x = this->get_position().get_x();
  int y = this->get_position().get_y();
  pair<bool, int> res = NO_MOVE;
  if(direction.compare("left") == 0){
    res = reverse_move_left(x, y, dices, is_a_simulation);
    if(res.first && !is_a_simulation){
      if(res.second == 1) this->make_move(x-1, y, 1, dices);
      else this->make_move(x-1, y, 0, dices);
    }
  }
  else if(direction.compare("right") == 0){
    res = reverse_move_right(x, y, dices, is_a_simulation);
    if(res.first && !is_a_simulation){
      if(res.second == 1) this->make_move(x+1, y, 1, dices);
      else this->make_move(x+1, y, 0, dices);
    }
  }
  else if(direction.compare("up") == 0){
    res = reverse_move_up(x, y, dices, is_a_simulation);
    if(res.first && !is_a_simulation){
      if(res.second == 1) this->make_move(x, y-1, 1, dices);
      else this->make_move(x, y-1, 0, dices);
    }
  }
  else if(direction.compare("down") == 0){
    res = reverse_move_down(x, y, dices, is_a_simulation);
    if(res.first && !is_a_simulation){
      if(res.second == 1) this->make_move(x, y+1, 1, dices);
      else this->make_move(x, y+1, 0, dices);
    }
  }
  return res;
}

pair<bool, int> WhiteDice::reverse_move_left(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool is_a_simulation){
  pair<bool, int> res = NO_MOVE;
  if(x-1>=0){
    if(check_arrival_cell_is_empty(x-1, y, dices))
      return MOVE_BY_1;
  
    if(dices.at(P2D::cellToP2D(Cell(x-1, y)))->get_actual_type().compare("RedDice") == 0 || dices.at(P2D::cellToP2D(Cell(x-1, y)))->get_actual_type().compare("WhiteDice") == 0){
      res = dices.at(P2D::cellToP2D(Cell(x-1, y)))->reverse_move("left", dices, __func__, is_a_simulation);
      if(res.first)
        res.second++;
    }
  }
  return res;
}

pair<bool, int> WhiteDice::reverse_move_right(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool is_a_simulation){
  pair<bool, int> res = NO_MOVE;
  if(x+1<MAP_WIDTH){
    if(check_arrival_cell_is_empty(x+1, y, dices))
      return MOVE_BY_1;
    
    if(dices.at(P2D::cellToP2D(Cell(x+1, y)))->get_actual_type().compare("RedDice") == 0 || dices.at(P2D::cellToP2D(Cell(x+1, y)))->get_actual_type().compare("WhiteDice") == 0){
      res = dices.at(P2D::cellToP2D(Cell(x+1, y)))->reverse_move("right", dices, __func__, is_a_simulation);
      if(res.first)
        res.second++;
    }
  }
  return res;
}

pair<bool, int> WhiteDice::reverse_move_up(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool is_a_simulation){
  pair<bool, int> res = NO_MOVE;
  if(y-1>=0){
    if(check_arrival_cell_is_empty(x, y-1, dices))
      return MOVE_BY_1;
    
    if(dices.at(P2D::cellToP2D(Cell(x, y-1)))->get_actual_type().compare("RedDice") == 0 || dices.at(P2D::cellToP2D(Cell(x, y-1)))->get_actual_type().compare("WhiteDice") == 0){
      res = dices.at(P2D::cellToP2D(Cell(x, y-1)))->reverse_move("up", dices, __func__, is_a_simulation);
      if(res.first)
        res.second++;
    }
  }
  return res;
}

pair<bool, int> WhiteDice::reverse_move_down(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool is_a_simulation){
  pair<bool, int> res = NO_MOVE;
  if(y+1<MAP_HEIGHT){
    if(check_arrival_cell_is_empty(x, y+1, dices))
      return MOVE_BY_1;
  
    if(dices.at(P2D::cellToP2D(Cell(x, y+1)))->get_actual_type().compare("RedDice") == 0 || dices.at(P2D::cellToP2D(Cell(x, y+1)))->get_actual_type().compare("WhiteDice") == 0){
      res = dices.at(P2D::cellToP2D(Cell(x, y+1)))->reverse_move("down", dices, __func__, is_a_simulation);
      if(res.first)
        res.second++;
    }
  }
  return res;
}

pair<bool, int> WhiteDice::move_left(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool is_a_simulation, int movement_type){
  if(x-1>=0){
    if(check_arrival_cell_is_empty(x-1, y, dices)) //arrival cell is empty
      return MOVE_BY_1;
    else{ //arrival cell is busy
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
}

pair<bool, int> WhiteDice::move_right(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool is_a_simulation, int movement_type){
  if(x+1<MAP_WIDTH){
    if(check_arrival_cell_is_empty(x+1, y, dices)) //arrival cell is empty
      return MOVE_BY_1;
    else{ //arrival cell is busy
      string actualType = dices.at(P2D(x+1, y))->get_actual_type();
      if(actualType.compare("RedDice") != 0 && actualType.compare("Dice") != 0){ //redDices cannot be pushed  
        if(dices.at(P2D(x+1, y))->move("right", dices, __func__, is_a_simulation, movement_type).first) //calls recursevely the move on left for the dice on his left (if it can be done moves in turn)
          return MOVE_BY_1;
        else 
          return NO_MOVE;
      }
      return NO_MOVE;
    } 
  }
  return NO_MOVE;
}

pair<bool, int> WhiteDice::move_up(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool is_a_simulation, int movement_type){
  if(y-1>=0){
    if(check_arrival_cell_is_empty(x, y-1, dices)) //arrival cell is empty
      return MOVE_BY_1;
    else{ //arrival cell is busy
      string actualType = dices.at(P2D(x, y-1))->get_actual_type();
      if(actualType.compare("RedDice") != 0 && actualType.compare("Dice") != 0){ //redDices cannot be pushed  
        if(dices.at(P2D(x, y-1))->move("up", dices, __func__, is_a_simulation, movement_type).first) //calls recursevely the move on left for the dice on his left (if it can be done moves in turn)
          return MOVE_BY_1;
        else 
          return NO_MOVE;
      }
      return NO_MOVE;
    } 
  }
  return NO_MOVE;
}

pair<bool, int> WhiteDice::move_down(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool is_a_simulation, int movement_type){
  if(y+1<MAP_HEIGHT){
    if(check_arrival_cell_is_empty(x, y+1, dices)) //arrival cell is empty
      return MOVE_BY_1;
    else{ //arrival cell is busy
      string actualType = dices.at(P2D(x, y+1))->get_actual_type();
      if(actualType.compare("RedDice") != 0 && actualType.compare("Dice") != 0){ //redDices cannot be pushed  
        if(dices.at(P2D(x, y+1))->move("down", dices, __func__, is_a_simulation, movement_type).first) //calls recursevely the move on left for the dice on his left (if it can be done moves in turn)
          return MOVE_BY_1;
        else 
          return NO_MOVE;
      }
      return NO_MOVE;
    } 
  }
  return NO_MOVE;
}