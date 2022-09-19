#include "common.h"
#include "red_dice.h"
#include "white_dice.h"
#include "yellow_dice.h"
#include "green_dice.h"
#include "p2d.h"
#include <typeinfo>
#include <typeindex>

RedDice::~RedDice(){}

RedDice::RedDice(Cell position, int nMoves, int initial_moves, P2D last_action_performed_direction) : Dice(position, nMoves, initial_moves, last_action_performed_direction){}

RedDice::RedDice() : Dice(){}

RedDice::RedDice(const RedDice &rd1) : Dice(rd1){position = rd1.position; nMoves = rd1.nMoves;}

string RedDice::print_dice_to_string (bool print_with_initial_moves){
  string t = "";
  if(!print_with_initial_moves)
    t = BGRED(this->get_n_moves());
  else
    t = BGRED(this->get_initial_moves());
  return t;
}

string RedDice::get_actual_type(){
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

int RedDice::get_actual_type_int(){
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

pair<bool, int> RedDice::reverse_move(string direction, unordered_map<P2D, Dice *, P2D::HashFun> &dices, char const * caller_name, bool is_a_simulation, int movement_type){
  direction = string_to_lower(direction);
  int x = this->get_position().get_x();
  int y = this->get_position().get_y();
  bool isGoingToCallThirdParty = !((direction.compare("left") == 0 && check_arrival_cell_is_empty(x-1, y, dices)) || (direction.compare("right") == 0 && check_arrival_cell_is_empty(x+1, y, dices)) || (direction.compare("up") == 0 && check_arrival_cell_is_empty(x, y-1, dices)) || (direction.compare("down") == 0 && check_arrival_cell_is_empty(x, y+1, dices)));
  if(!isGoingToCallThirdParty){
    if(this->get_n_moves() > 0)
      return call4reverse_move(direction, dices, caller_name, is_a_simulation, movement_type);
  }else
    return call4reverse_move(direction, dices, caller_name, is_a_simulation, movement_type);
  return NO_MOVE;
}

pair<bool, int> RedDice::call4reverse_move(string direction, unordered_map<P2D, Dice *, P2D::HashFun> &dices, char const * /* caller_name unused */, bool is_a_simulation, int /* movement_type unused */){
  direction = string_to_lower(direction);
  int x = this->get_position().get_x();
  int y = this->get_position().get_y();
  pair<bool, int> res = NO_MOVE;
  if(direction.compare("left") == 0){
    res = reverse_move_left(x, y, dices, is_a_simulation);
    if(res.first && !is_a_simulation) this->make_move(x-1, y, 1, dices);
  }
  if(direction.compare("right") == 0){
    res = reverse_move_right(x, y, dices, is_a_simulation);
    if(res.first && !is_a_simulation) this->make_move(x+1, y, 1, dices);
  }
  if(direction.compare("up") == 0){
    res = reverse_move_up(x, y, dices, is_a_simulation);
    if(res.first && !is_a_simulation) this->make_move(x, y-1, 1, dices);
  }
  if(direction.compare("down") == 0){
    res = reverse_move_down(x, y, dices, is_a_simulation);
    if(res.first && !is_a_simulation) this->make_move(x, y+1, 1, dices);
  }
  return res;
}

pair<bool, int> RedDice::reverse_move_left(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool /* is_a_simulation unused */, int /* movement_type unused*/){
  if(x-1>=0 && check_arrival_cell_is_empty(x-1, y, dices)) 
    return MOVE_BY_1;
  return NO_MOVE;
}

pair<bool, int> RedDice::reverse_move_right(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool /* is_a_simulation unused */, int /* movement_type unused*/){
  if(x+1<MAP_WIDTH && check_arrival_cell_is_empty(x+1, y, dices)) 
    return MOVE_BY_1;
  return NO_MOVE;
}

pair<bool, int> RedDice::reverse_move_up(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool /* is_a_simulation unused */, int /* movement_type unused*/){
  if(y-1>=0 && check_arrival_cell_is_empty(x, y-1, dices)) 
    return MOVE_BY_1;
  return NO_MOVE;
}

pair<bool, int> RedDice::reverse_move_down(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool /*is_a_simulation unused*/, int /* movement_type unused*/){
  if(y+1<MAP_HEIGHT && check_arrival_cell_is_empty(x, y+1, dices))
    return MOVE_BY_1;
  return NO_MOVE;
}

pair<bool, int> RedDice::move_left(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool is_a_simulation, int movement_type){
  if(x-1>=0){
    if(check_arrival_cell_is_empty(x-1, y, dices)) //arrival cell is empty
      return MOVE_BY_1;
    else{ //arrival cell is busy
      string actualType = dices.at(P2D (x-1, y))->get_actual_type();
      if(actualType.compare("RedDice") != 0 && actualType.compare("Dice") != 0){ //redDices cannot be pushed  
        if(dices.at(P2D (x-1, y))->move("left", dices, __func__, is_a_simulation, movement_type).first) //calls recursevely the move on left for the dice on his left (if it can be done moves in turn)
          return MOVE_BY_1;
        else 
          return NO_MOVE;
      }
      return NO_MOVE;
    } 
  }
  return NO_MOVE;
}

pair<bool, int> RedDice::move_right(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool is_a_simulation, int movement_type){
  if(x+1<MAP_WIDTH){
    if(check_arrival_cell_is_empty(x+1, y, dices)) //arrival cell is empty
      return MOVE_BY_1;
    else{ //arrival cell is busy
      string actualType = dices.at(P2D (x+1, y))->get_actual_type();
      if(actualType.compare("RedDice") != 0 && actualType.compare("Dice") != 0){ //redDices cannot be pushed  
        if(dices.at(P2D (x+1, y))->move("right", dices, __func__, is_a_simulation, movement_type).first) //calls recursevely the move on left for the dice on his left (if it can be done moves in turn)
          return MOVE_BY_1;
        else 
          return NO_MOVE;
      }
      return NO_MOVE;
    } 
  }
  return NO_MOVE;
}

pair<bool, int> RedDice::move_up(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool is_a_simulation, int movement_type){
  if(y-1>=0){
    if(check_arrival_cell_is_empty(x, y-1, dices)) //arrival cell is empty
      return MOVE_BY_1;
    else{ //arrival cell is busy
      string actualType = dices.at(P2D (x, y-1))->get_actual_type();
      if(actualType.compare("RedDice") != 0 && actualType.compare("Dice") != 0){ //redDices cannot be pushed  
        if(dices.at(P2D (x, y-1))->move("up", dices, __func__, is_a_simulation, movement_type).first) //calls recursevely the move on left for the dice on his left (if it can be done moves in turn)
          return MOVE_BY_1;
        else 
          return NO_MOVE;
      }
      return NO_MOVE;
    } 
  }
  return NO_MOVE;
}

pair<bool, int> RedDice::move_down(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool is_a_simulation, int movement_type){
  if(y+1<MAP_HEIGHT){
    if(check_arrival_cell_is_empty(x, y+1, dices)) //arrival cell is empty
      return MOVE_BY_1;
    else{ //arrival cell is busy
      string actualType = dices.at(P2D (x, y+1))->get_actual_type();
      if(actualType.compare("RedDice") != 0 && actualType.compare("Dice") != 0){ //redDices cannot be pushed  
        if(dices.at(P2D (x, y+1))->move("down", dices, __func__, is_a_simulation, movement_type).first) //calls recursevely the move down for the dice on his down (if it can be done moves in turn)
          return MOVE_BY_1;
        else 
          return NO_MOVE;
      }
      return NO_MOVE;
    } 
  }
  return NO_MOVE;
}