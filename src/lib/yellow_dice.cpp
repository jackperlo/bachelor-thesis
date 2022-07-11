#include "common.h"
#include "red_dice.h"
#include "white_dice.h"
#include "yellow_dice.h"
#include "green_dice.h"
#include "p2d.h"
#include <typeinfo>
#include <typeindex>

YellowDice::YellowDice(Cell position, int nMoves, int initial_moves) : Dice(position, nMoves, initial_moves){}

YellowDice::YellowDice() : Dice(){}

YellowDice::YellowDice(const YellowDice &yd1) : Dice(yd1){position = yd1.position; nMoves = yd1.nMoves;}

string YellowDice::print_dice_to_string (bool print_with_initial_moves){
  string t = "";
  if(!print_with_initial_moves)
    t = BGYEL(this->get_n_moves());
  else
    t = BGYEL(this->get_initial_moves());
  return t;
}

string YellowDice::get_actual_type(){
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

int YellowDice::get_actual_type_int(){
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

pair<bool, int> YellowDice::reverse_move(string direction, unordered_map<P2D, Dice *, P2D::HashFun> &dices, char const * caller_name, bool is_a_simulation, int movement_type){
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

pair<bool, int> YellowDice::call4reverse_move(string direction, unordered_map<P2D, Dice *, P2D::HashFun> &dices, char const * caller_name, bool is_a_simulation, int /* movement_type unused */){
  direction = string_to_lower(direction);
  int x = this->get_position().get_x();
  int y = this->get_position().get_y();
  pair<bool, int> res = NO_MOVE;
  bool isMovingActively = this->get_n_moves() > 0 && !(strcmp(caller_name, "reverse_move_left") == 0 || strcmp(caller_name, "reverse_move_right") == 0 || strcmp(caller_name, "reverse_move_up") == 0 || strcmp(caller_name, "reverse_move_down") == 0);
  if(direction.compare("left") == 0){
    res = reverse_move_left(x, y, dices, is_a_simulation);
    if(res.first && !is_a_simulation){
      if(res.second == 2 && check_arrival_cell_is_empty(x-2, y, dices)){
        if(isMovingActively)this->make_move(x-2, y, 1, dices);
        else this->make_move(x-2, y, 0, dices);
      }else if(res.second == 1 && check_arrival_cell_is_empty(x-1, y, dices)){
        if(isMovingActively)this->make_move(x-1, y, 1, dices);
        else this->make_move(x-2, y, 0, dices);
      }else{
        if(isMovingActively) this->make_move(x-1, y, 0, dices);
        else this->make_move(x-1, y, 1, dices);
      }
    }
  }
  else if(direction.compare("right") == 0){
    res = reverse_move_right(x, y, dices, is_a_simulation);
    if(res.first && !is_a_simulation){
      if(res.second == 2 && check_arrival_cell_is_empty(x+2, y, dices)){
        if(isMovingActively) this->make_move(x+2, y, 1, dices);
        else this->make_move(x+2, y, 0, dices);
      }else if(res.second == 1 && check_arrival_cell_is_empty(x+1, y, dices)){
        if(isMovingActively)this->make_move(x+1, y, 1, dices);
        else this->make_move(x+1, y, 0, dices);
      }else{
        if(isMovingActively) this->make_move(x+1, y, 0, dices);
        else this->make_move(x+1, y, 1, dices);
      }
    }
  }
  else if(direction.compare("up") == 0){
    res = reverse_move_up(x, y, dices, is_a_simulation);
    if(res.first && !is_a_simulation){
      if(res.second == 2 && check_arrival_cell_is_empty(x, y-2, dices)){
        if(isMovingActively) this->make_move(x, y-2, 1, dices);
        else this->make_move(x, y-2, 0, dices);
      }else if(res.second == 1 && check_arrival_cell_is_empty(x, y-1, dices)){
        if(isMovingActively)this->make_move(x, y-1, 1, dices);
        else this->make_move(x, y-1, 0, dices);
      }else{
        if(isMovingActively) this->make_move(x, y-1, 0, dices);
        else this->make_move(x, y-1, 1, dices);
      }
    }
  }
  else if(direction.compare("down") == 0){
    res = reverse_move_down(x, y, dices, is_a_simulation);
    if(res.first && !is_a_simulation){
      if(res.second == 2 && check_arrival_cell_is_empty(x, y+2, dices)){
        if(isMovingActively) this->make_move(x, y+2, 1, dices);
        else this->make_move(x, y+2, 0, dices);
      }else if(res.second == 1 && check_arrival_cell_is_empty(x, y+1, dices)){
        if(isMovingActively)this->make_move(x, y+1, 1, dices);
        else this->make_move(x, y+1, 0, dices);
      }else{
        if(isMovingActively) this->make_move(x, y+1, 0, dices);
        else this->make_move(x, y+1, 1, dices);
      }
    }
  }
  return res;
}

pair<bool, int> YellowDice::reverse_move_left(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool is_a_simulation){
  pair<bool, int> res = NO_MOVE;
  if(x-1>= 0 && check_arrival_cell_is_empty(x-1, y, dices))
    return MOVE_BY_1;
  if(x-2>= 0 && check_arrival_cell_is_empty(x-2, y, dices))
    return JUMP_BY_1;

  if(dices.at(P2D::cellToP2D(Cell(x-1, y)))->get_actual_type().compare("RedDice") == 0 || dices.at(P2D::cellToP2D(Cell(x-1, y)))->get_actual_type().compare("WhiteDice") == 0){
    res = dices.at(P2D::cellToP2D(Cell(x-1, y)))->reverse_move("left", dices, __func__, is_a_simulation);
    if(res.first)
      res.second++;
  }
  return res;
}

pair<bool, int> YellowDice::reverse_move_right(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool is_a_simulation){
  pair<bool, int> res = NO_MOVE;
  if(x+1 < MAP_WIDTH && check_arrival_cell_is_empty(x+1, y, dices))
    return MOVE_BY_1;
  if(x+2 < MAP_WIDTH && check_arrival_cell_is_empty(x+2, y, dices))
    return JUMP_BY_1;

  if(dices.at(P2D::cellToP2D(Cell(x+1, y)))->get_actual_type().compare("RedDice") == 0  || dices.at(P2D::cellToP2D(Cell(x+1, y)))->get_actual_type().compare("WhiteDice") == 0){
    res = dices.at(P2D::cellToP2D(Cell(x+1, y)))->reverse_move("right", dices, __func__, is_a_simulation);
    if(res.first)
      res.second++;
  }
  return res;
}

pair<bool, int> YellowDice::reverse_move_up(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool is_a_simulation){
  pair<bool, int> res = NO_MOVE;
  if(y-1 >= 0 && check_arrival_cell_is_empty(x, y-1, dices))
    return MOVE_BY_1;
  if(y-2 >= 0 && check_arrival_cell_is_empty(x, y-2, dices))
    return JUMP_BY_1;

  if(dices.at(P2D::cellToP2D(Cell(x, y-1)))->get_actual_type().compare("RedDice") == 0 || dices.at(P2D::cellToP2D(Cell(x, y-1)))->get_actual_type().compare("WhiteDice") == 0){
    res = dices.at(P2D::cellToP2D(Cell(x, y-1)))->reverse_move("up", dices, __func__, is_a_simulation);
    if(res.first)
      res.second++;
  }
  return res;
}

pair<bool, int> YellowDice::reverse_move_down(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool is_a_simulation){
  pair<bool, int> res = NO_MOVE;
  if(y+1 < MAP_HEIGHT && check_arrival_cell_is_empty(x, y+1, dices))
    return MOVE_BY_1;
  if(y+2 < MAP_HEIGHT && check_arrival_cell_is_empty(x, y+2, dices))
    return JUMP_BY_1;

  if(dices.at(P2D::cellToP2D(Cell(x, y+1)))->get_actual_type().compare("RedDice") == 0 || dices.at(P2D::cellToP2D(Cell(x, y+1)))->get_actual_type().compare("WhiteDice") == 0){
    res = dices.at(P2D::cellToP2D(Cell(x, y+1)))->reverse_move("down", dices, __func__, is_a_simulation);
    if(res.first)
      res.second++;
  }
  return res;
}

pair<bool, int> YellowDice::move_left(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool /* is_a_simulation unused */, int /*movement_type unused */){
  pair<bool, int> res = NO_MOVE;
  if(x-1 >= 0 && check_arrival_cell_is_empty(x-1, y, dices))
    return MOVE_BY_1;
  else if(x-2 >= 0 && check_arrival_cell_is_empty(x-2, y, dices))
    return JUMP_BY_1;
  return res;
}

pair<bool, int> YellowDice::move_right(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool /* is_a_simulation unused */, int /*movement_type unused */){
  pair<bool, int> res = NO_MOVE;
  if(x+1 < MAP_WIDTH && check_arrival_cell_is_empty(x+1, y, dices))
    return MOVE_BY_1;
  else if(x+2 < MAP_WIDTH && check_arrival_cell_is_empty(x+2, y, dices))
    return JUMP_BY_1;
  return res;
}

pair<bool, int> YellowDice::move_up(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool /* is_a_simulation unused */, int /*movement_type unused */){
  pair<bool, int> res = NO_MOVE;
  if(y-1 >= 0 && check_arrival_cell_is_empty(x, y-1, dices))
    return MOVE_BY_1;
  else if(y-2 >= 0 && check_arrival_cell_is_empty(x, y-2, dices))
    return JUMP_BY_1;
  return res;
}

pair<bool, int> YellowDice::move_down(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool /* is_a_simulation unused */, int /*movement_type unused */){
  pair<bool, int> res = NO_MOVE;
  if(y+1 < MAP_HEIGHT && check_arrival_cell_is_empty(x, y+1, dices))
    return MOVE_BY_1;
  else if(y+2 < MAP_HEIGHT && check_arrival_cell_is_empty(x, y+2, dices))
    return JUMP_BY_1;
  return res;
}