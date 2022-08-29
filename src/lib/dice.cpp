#include "dice.h"
#include "common.h"

int MAP_WIDTH;
int MAP_HEIGHT;
int TOTAL_MOVES;
int CENTROID_X;
int CENTROID_Y;

Dice::~Dice(){}

Dice::Dice(Cell position, int nMoves, int initial_moves){
  this->position = position;
  this->nMoves = nMoves;
  this->initial_moves = initial_moves;
}

Dice::Dice(){}

bool Dice::operator==(Dice *other_dice){
  return (this->nMoves == other_dice->get_n_moves()) && 
          (this->get_actual_type_int() == other_dice->get_actual_type_int());
}

void Dice::set_position(Cell position){
  this->position = position;
}

Cell Dice::get_position() const{
  return position;
}

int Dice::get_n_moves(){
  return nMoves;
}

void Dice::set_n_moves(int n_moves){
  this->nMoves = n_moves;
}

int Dice::get_initial_moves(){
  return initial_moves;
}

void Dice::print_dice(){
  cout << this->get_actual_type() << ": (position: " << this->position.get_x() << \
        ", " << this->position.get_y() << ", nMoves: " << this->nMoves << ")" << std::endl;
}

pair<bool, int> Dice::move(string direction, unordered_map<P2D, Dice *, P2D::HashFun> &dices, char const * caller_name, bool is_a_simulation, int movement_type){
  direction = string_to_lower(direction);
  int x = this->position.get_x();
  int y = this->position.get_y();
  pair<bool, int> res;
  bool pushedMove = (this->nMoves == 0 && (strcmp(caller_name, "move_left") == 0 || strcmp(caller_name, "move_right") == 0 || strcmp(caller_name, "move_up") == 0 || strcmp(caller_name, "move_down") == 0)) || (strcmp(caller_name, "move_left") == 0 || strcmp(caller_name, "move_right") == 0 || strcmp(caller_name, "move_up") == 0 || strcmp(caller_name, "move_down") == 0);

  if(this->nMoves > 0 || pushedMove){
    if(direction.compare("left") == 0){
      if(this->get_actual_type().compare("GreenDice") == 0 && pushedMove)
        res = move_left(x, y, dices, is_a_simulation, PUSHED_MOVE);
      else
        res = move_left(x, y, dices, is_a_simulation, movement_type);
        
      if(res.first && !pushedMove && !is_a_simulation){
        if(this->get_actual_type().compare("YellowDice") == 0)
          return make_pair(make_move(x-res.second, y, 1, dices), res.second);
        else
          return make_pair(make_move(x-res.second, y, res.second, dices), res.second);
      }
      else if(res.first && pushedMove && !is_a_simulation)
        return make_pair(make_move(x-res.second, y, 0, dices), res.second);
      else if(is_a_simulation)
        return res;
    }else if(direction.compare("right") == 0){
      if(this->get_actual_type().compare("GreenDice") == 0 && pushedMove)
        res = move_right(x, y, dices, is_a_simulation, PUSHED_MOVE);
      else
        res = move_right(x, y, dices, is_a_simulation, movement_type);

      if(res.first && !pushedMove && !is_a_simulation){
        if(this->get_actual_type().compare("YellowDice") == 0)
          return make_pair(make_move(x+res.second, y, 1, dices), res.second);
        else
          return make_pair(make_move(x+res.second, y, res.second, dices), res.second);
      }
      else if(res.first && pushedMove && !is_a_simulation)
        return make_pair(make_move(x+res.second, y, 0, dices), res.second);
      else if(is_a_simulation)
        return res;
    }else if(direction.compare("up") == 0){
      if(this->get_actual_type().compare("GreenDice") == 0 && pushedMove)
        res = move_up(x, y, dices, is_a_simulation, PUSHED_MOVE);
      else
        res = move_up(x, y, dices, is_a_simulation, movement_type);
      
      if(res.first && !pushedMove && !is_a_simulation){
        if(this->get_actual_type().compare("YellowDice") == 0)
          return make_pair(make_move(x, y-res.second, 1, dices), res.second);
        else
          return make_pair(make_move(x, y-res.second, res.second, dices), res.second);
      }
      else if(res.first && pushedMove && !is_a_simulation)
        return make_pair(make_move(x, y-res.second, 0, dices), res.second);
      else if(is_a_simulation)
        return res;
    }else if(direction.compare("down") == 0){
      if(this->get_actual_type().compare("GreenDice") == 0 && pushedMove)
        res = move_down(x, y, dices, is_a_simulation, PUSHED_MOVE);
      else
        res = move_down(x, y, dices, is_a_simulation, movement_type);
      
      if(res.first && !pushedMove && !is_a_simulation){
        if(this->get_actual_type().compare("YellowDice") == 0)
          return make_pair(make_move(x, y+res.second, 1, dices), res.second);
        else
          return make_pair(make_move(x, y+res.second, res.second, dices), res.second);
      }
      else if(res.first && pushedMove && !is_a_simulation)
        return make_pair(make_move(x, y+res.second, 0, dices), res.second);
      else if(is_a_simulation)
        return res;
    }
  }
  return NO_MOVE;
}

string Dice::string_to_lower(string input_string){
  for_each(input_string.begin(), input_string.end(), [](char &c){c = tolower(c);}); 
  return input_string;
}

int Dice::check_arrival_cell_is_empty(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> dices){ 
  if(dices.find(P2D(x, y)) == dices.end())
    return 1;
  
  return 0;
}

bool Dice::make_move(int x, int y, int nMoves_done, unordered_map<P2D, Dice *, P2D::HashFun> &dices){
  dices.erase(P2D(this->position.get_x(), this->position.get_y()));
  if(dices.find(P2D(this->position.get_x(), this->position.get_y())) != dices.end()){
    cout<<"\nDice.cpp: Error while trying to erase old dice position.\n"; 
    exit(1);
  }
  dices.insert(pair<P2D, Dice *>(P2D(x, y), this));
  if(dices.find(P2D(x, y)) == dices.end()){
    cout<<"\nDice.cpp: Error while trying to insert new dice position.\n"; 
    exit(1);
  }
  this->position = Cell(x, y);
  if(this->nMoves-nMoves_done < 0){
    cout<<"\nDice.cpp: Error while decreasing nMoves to this dice:\n"; 
    this->print_dice();
    exit(1);
  }
  this->nMoves = this->nMoves-nMoves_done;
  return true;
}