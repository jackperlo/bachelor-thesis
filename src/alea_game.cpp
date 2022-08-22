/**
  This class contains the work logic of AleaGame 
  @file astar.h astar.cpp
  @authors Mirko Polato, Giacomo Perlo
*/
#include "alea_game.h"
#include "lib/common.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <unordered_set>
#include <string>
#include <queue>
#include <stack>
#include <list>
#include <limits>

AleaGame::~AleaGame(){
  for(pair<P2D, Dice *> pair : dices) delete pair.second;
}

//empty constructor
AleaGame::AleaGame(){}

//copying constructor
AleaGame::AleaGame(const AleaGame& game) {
  last_action_performed = game.last_action_performed;
  for (const auto& elem: game.terminals) {
    terminals.insert(P2D(elem));
  }
  for (auto const& elem : game.dices) {
    Dice *dice;
    Cell c(elem.second->get_position().get_x(), elem.second->get_position().get_y());
    switch (elem.second->get_actual_type_int()){
      case 0: dice = new WhiteDice(c, elem.second->get_n_moves(), elem.second->get_initial_moves()); break;
      case 1: dice = new RedDice(c, elem.second->get_n_moves(), elem.second->get_initial_moves()); break;
      case 2: dice = new YellowDice(c, elem.second->get_n_moves(), elem.second->get_initial_moves()); break;
      case 3: dice = new GreenDice(c, elem.second->get_n_moves(), elem.second->get_initial_moves()); break;
    }
    dices.insert(pair<P2D, Dice *>(P2D(elem.first), dice));
  }
}

//constructor 
AleaGame::AleaGame(string filename, bool is_backward, string type) : AleaGame(json::parse(read_json(filename)), is_backward, type) { }

//generates the game instance starting from the .json file
AleaGame::AleaGame(json json_dict, bool is_backward, string type) {
  /* the parameters needed from the .json file are different 
  according to the analysis we want to make (forward) */
  if(is_backward)
    generateMapForBackwardMovements(json_dict);
  else
    generateMapForExpectedForwardMovements(json_dict, type);
}

void AleaGame::generateMapForBackwardMovements(json json_dict){
  last_action_performed = Action::null_action;
  int cols = json_dict["columns"];
  int max_row = 0;

  for (auto& e : json_dict["terminals"].items()) {
    json terminal_j = e.value();
    terminals.insert(P2D((int)terminal_j["x"]+1, (int)terminal_j["y"]+1));
    max_row = MAX((int)terminal_j["y"]+1, max_row);
  }

  for (auto& e : json_dict["dice"].items()) {
    json dice_j = e.value();
    int x = dice_j["x"];
    int y = dice_j["y"];
    max_row = MAX(y + 1, max_row);
    Dice *dice;
    Cell c(x+1, y+1);
    switch ((int)dice_j["type"]){
      case 0: dice = new WhiteDice(c, dice_j["num"], dice_j["num"]); break;
      case 1: dice = new RedDice(c, dice_j["num"], dice_j["num"]); break;
      case 2: dice = new YellowDice(c, dice_j["num"], dice_j["num"]); break;
      case 3: dice = new GreenDice(c, dice_j["num"], dice_j["num"]); break;
    }
    dices.insert(pair<P2D, Dice *>(P2D(x + 1, y + 1), dice));
  }
  MAP_WIDTH = cols + 2;
  MAP_HEIGHT = max_row + 2;
  TOTAL_MOVES = remaining_moves();

  if(!is_valid_ending_configuration_backward_search()){
    cout << "\n\nPlease insert a valid Final Configuration of the Map.\nMismatches between Dices and Terminals positions.\n\n\n";
    exit(1);
  }
  
  cout << "\n"<< FGREDSTART <<"===== Alea Level Solver Backward =====" << endl;
	cout << "           MAP_WIDTH : " << MAP_WIDTH << endl;
	cout << "           MAP_HEIGHT: " << MAP_HEIGHT << endl;
	cout << "           #dice : " << terminals.size() << endl;
	cout << "========================================"<< FGRESET << endl;
	cout << endl;
}

void AleaGame::generateMapForExpectedForwardMovements(json json_dict, string type){
  last_action_performed = Action::null_action;
  for (auto& e : json_dict["terminals"].items()) {
    json terminal_j = e.value();
    terminals.insert(P2D((int)terminal_j["x"], (int)terminal_j["y"]));
  }

  for (auto& e : json_dict["dice"].items()) {
    json dice_j = e.value();
    int x = dice_j["x"];
    int y = dice_j["y"];
    Dice *dice;
    Cell c(x, y);
    switch ((int)dice_j["type"]){
      case 0: dice = new WhiteDice(c, dice_j["num"], dice_j["num"]); break;
      case 1: dice = new RedDice(c, dice_j["num"], dice_j["num"]); break;
      case 2: dice = new YellowDice(c, dice_j["num"], dice_j["num"]); break;
      case 3: dice = new GreenDice(c, dice_j["num"], dice_j["num"]); break;
    }
    dices.insert(pair<P2D, Dice *>(P2D(x, y), dice));
  }
  MAP_WIDTH = json_dict["columns"];
  MAP_HEIGHT = json_dict["rows"];
  TOTAL_MOVES = remaining_moves();
  
  cout << "\n" << FGREDSTART << "===== Alea Level Solver "<<type<<" Forward =====" << endl;
	cout << "                MAP_WIDTH : " << MAP_WIDTH << endl;
	cout << "                MAP_HEIGHT: " << MAP_HEIGHT << endl;
	cout << "                #dice : " << terminals.size() << endl;
  cout << "                #total_moves : " << TOTAL_MOVES << endl;
	cout << "================================================" << FGRESET << endl;
}

int AleaGame::HashFun::operator()(const AleaGame& game) const {
  int type_map[] = {17, 31, 47, 97};
  int the_hash = 0;
  for (const P2D& t : game.terminals) the_hash += P2D::HashFun()(t);
  for (const auto &pair : game.dices) {
      the_hash += P2D::HashFun()(pair.first) * type_map[pair.second->get_actual_type_int()] * pair.second->get_n_moves()+1;
      the_hash ^= (int) pow(type_map[pair.second->get_actual_type_int()], pair.second->get_n_moves()+1);
  }
  return the_hash;
}

bool AleaGame::operator==(const AleaGame& other) const {
  for (auto& elem: other.terminals) {
    if (!is_terminal(elem)) return false;
  }
  for (auto elem : other.dices) {
    if (!has_dice(elem.first)) return false;
    if (!(*(this->dices.find(elem.first)->second) == elem.second)) return false;
  }
  return true;
}

AleaGame& AleaGame::operator=(const AleaGame& game){
  this->dices.clear();

  this->last_action_performed = game.last_action_performed;
  for (const auto& elem: game.terminals) {
    this->terminals.insert(P2D(elem));
  }
  for (auto const& elem : game.dices) {
    Dice *dice;
    Cell c(elem.second->get_position().get_x(), elem.second->get_position().get_y());
    switch (elem.second->get_actual_type_int()){
      case 0: dice = new WhiteDice(c, elem.second->get_n_moves(), elem.second->get_initial_moves()); break;
      case 1: dice = new RedDice(c, elem.second->get_n_moves(), elem.second->get_initial_moves()); break;
      case 2: dice = new YellowDice(c, elem.second->get_n_moves(), elem.second->get_initial_moves()); break;
      case 3: dice = new GreenDice(c, elem.second->get_n_moves(), elem.second->get_initial_moves()); break;
    }
    this->dices.insert(pair<P2D, Dice *>(P2D(elem.first), dice));
  }
  return *this;
}

/**
  PRIVATE method that allows to print the map on console
  @param pair a pair containing a bool parameter and the game instance we want to print.
              The bool one, if true, specifies that we want to print the map with the number 
              of initial moves assigned to each dice.
  @return a string which will be printed on console
*/
string print_aleagame_to_string (pair<bool, AleaGame> pair) {
  string s = string(3*MAP_WIDTH, ' ') + " \n";
  for (int i = 0; i < MAP_HEIGHT; ++i) {
    for (int j = 0; j < MAP_WIDTH; ++j) {
      P2D pos = P2D(j, i);
      string d = pair.second.dices.find(pos) == pair.second.dices.end() ? BGGRAY : (string) (pair.second.dices[pos]->print_dice_to_string(pair.first));
      s += pair.second.terminals.find(pos) == pair.second.terminals.end() ? " " + d + " " :  "[" + d + "]";
    }
    s += "\n" + string(3*MAP_WIDTH, ' ') + " \n";
  }
  return s;
}

ostream& operator<<(ostream& out, pair<bool, AleaGame> pair) {
  return out << (string) print_aleagame_to_string(pair);
}

/**
  PUBLIC method that allows to print the map on console colorful/less 
  @param color if true, prints the map coloful
  @param print_init_moves_number if true, prints, for each dice, its initial number of moves
                                 instead of the current number of moves
*/
void AleaGame::print(const bool& color, bool print_init_moves_number) {
  if (color) {
    cout << make_pair(print_init_moves_number, *this) << endl; //calls the << operator
    return;
  }
  string s = "";
  for (int i = 0; i < MAP_HEIGHT; i++) {
    for (int j = 0; j < MAP_WIDTH; j++) {
      P2D pos = P2D(j, i);
      string d = "    ";
      if (dices.find(pos) != dices.end()) {
        if(dices[pos]->get_actual_type().compare("WhiteDice") == 0) d = "W";
        else if(dices[pos]->get_actual_type().compare("RedDice") == 0) d = "R";
        else if(dices[pos]->get_actual_type().compare("YellowDice") == 0) d = "Y";
        else if(dices[pos]->get_actual_type().compare("GreenDice") == 0) d = "G";
        if(!print_init_moves_number)
          d += "(" + to_string(dices[pos]->get_n_moves()) + ")";
        else
          d += "(" + to_string(dices[pos]->get_initial_moves()) + ")";
      } 
      s += terminals.find(pos) == terminals.end() ? "." + d + "." :  "[" + d + "]";
    }
    s += "\n";
  }
  cout << s << endl;
}

string AleaGame::read_json(string filename) {
	string line, json_text;
	ifstream file_lvl(filename);
	if (file_lvl.is_open()) {
		while(!file_lvl.eof()) {
			getline(file_lvl, line);
			json_text += line;
		}
		file_lvl.close();
	}
	else {
		cout << "alea_game.cpp:read_json: ERROR: Unable to open file '" << filename << "'." << endl;
		exit(1);
	}
	return json_text;
}

int AleaGame::remaining_moves() const {
  int tot = 0;
  for (auto const& pair: dices) {
    tot += pair.second->get_n_moves();
  }
  return tot;
}

/**
  this analyzes, for each dice, the possible moves which could be done Backward
  @return a vector of legal action formed by:
         <from_position, to_position, move_weight, move_type, head_position>
         Note that head_position is necessary because the move done forward will be started by
         another dice (the head_position dice!)
*/
vector<Action> AleaGame::possible_moves_backward() {
  vector<Action> moves;
  for (auto const& pair: dices) {
    Dice *dice = pair.second;
    if(dice->get_n_moves() > 0){
      if(dice->get_actual_type().compare("GreenDice") == 0)
        green_dice_possible_moves_backward(dice, moves);
      else if(dice->get_actual_type().compare("WhiteDice") == 0)
        white_dice_possible_moves_backward(dice, moves);
      else if(dice->get_actual_type().compare("RedDice") == 0)
        red_dice_possible_moves_backward(dice, moves);
      else if(dice->get_actual_type().compare("YellowDice") == 0)
        yellow_dice_possible_moves_backward(dice, moves);
    }
  }
  return moves;
}

/**
  this is reached if the current dice analyzed is YELLOW; the legal backward actions are 
  added to @moves vector.

  For every direction(up, down, left, right) the action is simulated(doesn't really modify current
  dice position neither number of moves available). If the response is that the action could be done, 
  then is added to moves vector. 

  Note that if the last move the dice did was (eg. left) the opposite move (right, in this case) is
  not considered legal. This because we're looking for the most difficult moves sequence (backward)
  and if this was allowed, the dice could just move forward and backward until has moves available.
  (quite banal!)
  @param dice the considered dice
  @param moves vector of actions passed by reference 
*/  
void AleaGame::yellow_dice_possible_moves_backward(Dice *dice, vector<Action> &moves){
  int x = dice->get_position().get_x(), y = dice->get_position().get_y();
  vector<Cell> cells;
  if(x>0) cells.push_back(Cell(x-1, y));
  if(x<MAP_WIDTH-1) cells.push_back(Cell(x+1, y));
  if(y>0) cells.push_back(Cell(x, y-1));
  if(y<MAP_HEIGHT-1) cells.push_back(Cell(x, y+1));
  for(Cell c : cells){
    pair<bool, int> res = NO_MOVE;
    if(c.get_x() == x-1 && last_action_performed.dir.x > 0){
      res = dice->reverse_move("left", dices, __func__, true, PUSHED_MOVE);
      if(res.first)
        moves.push_back(Action(P2D(x, y), P2D::LEFT, PUSHED_MOVE_BACKWARD_WEIGHT, PUSHED_MOVE, P2D(x-(res.second+1), y)));
      else{
        res = dice->reverse_move("left", dices, __func__, true); 
        if(res.first){
          if(res.second == 1) 
            moves.push_back(Action(P2D(x, y), P2D::LEFT, SIMPLE_MOVE_BACKWARD_WEIGHT, SIMPLE_MOVE, P2D(x, y)+P2D::LEFT)); 
          else
            moves.push_back(Action(P2D(x, y), P2D(-res.second, 0), JUMPING_MOVE_BACKWARD_WEIGHT, JUMP_MOVE, P2D(x-res.second, y)));  
        }
      }
    }
    if(c.get_x() == x+1 && last_action_performed.dir.x < 0){
      res = dice->reverse_move("right", dices, __func__, true, PUSHED_MOVE);
      if(res.first){
        moves.push_back(Action(P2D(x, y), P2D::RIGHT, PUSHED_MOVE_BACKWARD_WEIGHT, PUSHED_MOVE, P2D(x+(res.second+1), y)));
      }
      else{
        res = dice->reverse_move("right", dices, __func__, true);
        if(res.first){
          if(res.second == 1) 
            moves.push_back(Action(P2D(x, y), P2D::RIGHT, SIMPLE_MOVE_BACKWARD_WEIGHT, SIMPLE_MOVE, P2D(x, y)+P2D::RIGHT)); 
          else
            moves.push_back(Action(P2D(x, y), P2D(res.second, 0), JUMPING_MOVE_BACKWARD_WEIGHT, JUMP_MOVE, P2D(x+res.second, y))); 
        }    
      } 
    }
    if(c.get_y() == y-1  && last_action_performed.dir.y > 0){
      res = dice->reverse_move("up", dices, __func__, true, PUSHED_MOVE);
      if(res.first)
        moves.push_back(Action(P2D(x, y), P2D::UP, PUSHED_MOVE_BACKWARD_WEIGHT, PUSHED_MOVE, P2D(x, y-(res.second+1))));
      else{
         res = dice->reverse_move("up", dices, __func__, true);
        if(res.first){
          if(res.second == 1) 
            moves.push_back(Action(P2D(x, y), P2D::UP, SIMPLE_MOVE_BACKWARD_WEIGHT, SIMPLE_MOVE, P2D(x, y)+P2D::UP)); 
          else
            moves.push_back(Action(P2D(x, y), P2D(0, -res.second), JUMPING_MOVE_BACKWARD_WEIGHT, JUMP_MOVE, P2D(x, y-res.second))); 
        } 
      }
    }
    if(c.get_y() == y+1  && last_action_performed.dir.y < 0){
      res = dice->reverse_move("down", dices, __func__, true, PUSHED_MOVE);
      if(res.first)
        moves.push_back(Action(P2D(x, y), P2D::DOWN, PUSHED_MOVE_BACKWARD_WEIGHT, PUSHED_MOVE, P2D(x, (y+res.second+1))));
      else{
        res = dice->reverse_move("down", dices, __func__, true);
        if(res.first){
          if(res.second == 1) 
            moves.push_back(Action(P2D(x, y), P2D::DOWN, SIMPLE_MOVE_BACKWARD_WEIGHT, SIMPLE_MOVE, P2D(x, y)+P2D::DOWN)); 
          else
            moves.push_back(Action(P2D(x, y), P2D(0, res.second), JUMPING_MOVE_BACKWARD_WEIGHT, JUMP_MOVE, P2D(x, y+res.second)));
        }    
      }
    }
  }
}

/**
  this is reached if the current dice analyzed is RED; the legal backward actions are 
  added to @moves vector.

  For every direction(up, down, left, right) the action is simulated(doesn't really modify current
  dice position neither number of moves available). If the response is that the action could be done, 
  then is added to moves vector. 

  Note that if the last move the dice did was (eg. left) the opposite move (right, in this case) is
  not considered legal. This because we're looking for the most difficult moves sequence (backward)
  and if this was allowed, the dice could just move forward and backward until has moves available.
  (quite banal!)
  @param dice the considered dice
  @param moves vector of actions passed by reference 
*/  
void AleaGame::red_dice_possible_moves_backward(Dice *dice, vector<Action> &moves){
  int x = dice->get_position().get_x(), y = dice->get_position().get_y();
  vector<Cell> cells;
  if(x>0) cells.push_back(Cell(x-1, y));
  if(x<MAP_WIDTH-1) cells.push_back(Cell(x+1, y));
  if(y>0) cells.push_back(Cell(x, y-1));
  if(y<MAP_HEIGHT-1) cells.push_back(Cell(x, y+1));
  for(Cell c : cells){
    pair<bool, int> res = NO_MOVE;
    if(c.get_x() == x-1  && last_action_performed.dir != P2D::RIGHT){
      res = dice->reverse_move("left", dices, __func__, true);
      if(res.first) moves.push_back(Action(P2D(x, y), P2D::LEFT, SIMPLE_MOVE_BACKWARD_WEIGHT, SIMPLE_MOVE, P2D(x, y)+P2D::LEFT));      
    }
    if(c.get_x() == x+1 && last_action_performed.dir != P2D::LEFT){
      res = dice->reverse_move("right", dices, __func__, true);
      if(res.first) moves.push_back(Action(P2D(x, y), P2D::RIGHT, SIMPLE_MOVE_BACKWARD_WEIGHT, SIMPLE_MOVE, P2D(x, y)+P2D::RIGHT));      
    }
    if(c.get_y() == y-1 && last_action_performed.dir != P2D::DOWN){
      res = dice->reverse_move("up", dices, __func__, true);
      if(res.first) moves.push_back(Action(P2D(x, y), P2D::UP, SIMPLE_MOVE_BACKWARD_WEIGHT, SIMPLE_MOVE, P2D(x, y)+P2D::UP));      
    }
    if(c.get_y() == y+1 && last_action_performed.dir != P2D::UP){
      res = dice->reverse_move("down", dices, __func__, true);
      if(res.first) moves.push_back(Action(P2D(x, y), P2D::DOWN, SIMPLE_MOVE_BACKWARD_WEIGHT, SIMPLE_MOVE, P2D(x, y)+P2D::DOWN));      
    }
  }
}

/**
  this is reached if the current dice analyzed is WHITE; the legal backward actions are 
  added to @moves vector.

  For every direction(up, down, left, right) the action is simulated(doesn't really modify current
  dice position neither number of moves available). If the response is that the action could be done, 
  then is added to moves vector. 

  Note that if the last move the dice did was (eg. left) the opposite move (right, in this case) is
  not considered legal. This because we're looking for the most difficult moves sequence (backward)
  and if this was allowed, the dice could just move forward and backward until has moves available.
  (quite banal!)
  @param dice the considered dice
  @param moves vector of actions passed by reference 
*/  
void AleaGame::white_dice_possible_moves_backward(Dice *dice, vector<Action> &moves){
  int x = dice->get_position().get_x(), y = dice->get_position().get_y();
  vector<Cell> cells;
  if(x>0) cells.push_back(Cell(x-1, y));
  if(x<MAP_WIDTH-1) cells.push_back(Cell(x+1, y));
  if(y>0) cells.push_back(Cell(x, y-1));
  if(y<MAP_HEIGHT-1) cells.push_back(Cell(x, y+1));
  for(Cell c : cells){
    pair<bool, int> res = NO_MOVE;
    if(c.get_x() == x-1 && last_action_performed.dir != P2D::RIGHT){
      res = dice->reverse_move("left", dices, __func__, true);
      if(res.first){
        if(dices.find(P2D::cellToP2D(c)) == dices.end())
          moves.push_back(Action(P2D(x, y), P2D::LEFT, SIMPLE_MOVE_BACKWARD_WEIGHT, SIMPLE_MOVE, P2D(x, y)+P2D::LEFT));
        else
          moves.push_back(Action(P2D(x, y), P2D::LEFT, PUSHED_MOVE_BACKWARD_WEIGHT, PUSHED_MOVE, P2D(x-res.second, y)));       
      }
    }
    if(c.get_x() == x+1 && last_action_performed.dir != P2D::LEFT){
      res = dice->reverse_move("right", dices, __func__, true);
      if(res.first){
        if(dices.find(P2D::cellToP2D(c)) == dices.end())
          moves.push_back(Action(P2D(x, y), P2D::RIGHT, SIMPLE_MOVE_BACKWARD_WEIGHT, SIMPLE_MOVE, P2D(x, y)+P2D::RIGHT));
        else
          moves.push_back(Action(P2D(x, y), P2D::RIGHT, PUSHED_MOVE_BACKWARD_WEIGHT, PUSHED_MOVE, P2D(x+res.second, y)));           
      }
    }
    if(c.get_y() == y-1 && last_action_performed.dir != P2D::DOWN){
      res = dice->reverse_move("up", dices, __func__, true);
      if(res.first){
        if(dices.find(P2D::cellToP2D(c)) == dices.end())
          moves.push_back(Action(P2D(x, y), P2D::UP, SIMPLE_MOVE_BACKWARD_WEIGHT, SIMPLE_MOVE, P2D(x, y)+P2D::UP));
        else
          moves.push_back(Action(P2D(x, y), P2D::UP, PUSHED_MOVE_BACKWARD_WEIGHT, PUSHED_MOVE, P2D(x, y-res.second)));         
      }
    }
    if(c.get_y() == y+1 && last_action_performed.dir != P2D::UP){
      res = dice->reverse_move("down", dices, __func__, true);
      if(res.first){
        if(dices.find(P2D::cellToP2D(c)) == dices.end())
          moves.push_back(Action(P2D(x, y), P2D::DOWN, SIMPLE_MOVE_BACKWARD_WEIGHT, SIMPLE_MOVE, P2D(x, y)+P2D::DOWN));
        else
          moves.push_back(Action(P2D(x, y), P2D::DOWN, PUSHED_MOVE_BACKWARD_WEIGHT, PUSHED_MOVE, P2D(x, y+res.second)));       
      }
    }
  }
}

void AleaGame::green_dice_possible_moves_backward(Dice *dice, vector<Action> &moves){
  if(dice->get_n_moves() > 0){
    //the dice could move by itself or be pushed by another dice
    green_dice_possible_moves_nMoves_gt_zero_backward(dice, moves);
    green_dice_possible_moves_being_pushed_backward(dice, moves);  
  }else
    green_dice_possible_moves_being_pushed_backward(dice, moves);  
}

/**
  this is reached if the current dice analyzed is GREEN with available move(>0); the legal backward 
  actions are added to @moves vector.

  For every direction(up, down, left, right) the action is simulated(doesn't really modify current
  dice position neither number of moves available). If the response is that the action could be done, 
  then is added to moves vector. 

  Note that if the last move the dice did was (eg. left) the opposite move (right, in this case) is
  not considered legal. This because we're looking for the most difficult moves sequence (backward)
  and if this was allowed, the dice could just move forward and backward until has moves available.
  (quite banal!)
  @param dice the considered dice
  @param moves vector of actions passed by reference 
*/  
void AleaGame::green_dice_possible_moves_nMoves_gt_zero_backward(Dice *dice, vector<Action> &moves){
  int x = dice->get_position().get_x(), y = dice->get_position().get_y();
  vector<Cell> cells;
  if(x>0) cells.push_back(Cell(x-1, y));
  if(x<MAP_WIDTH-1) cells.push_back(Cell(x+1, y));
  if(y>0) cells.push_back(Cell(x, y-1));
  if(y<MAP_HEIGHT-1) cells.push_back(Cell(x, y+1));
  for(Cell c : cells){
    pair<bool, int> res = NO_MOVE;
    if((c.get_x() == x-1 || x == 0) && last_action_performed.dir != P2D::LEFT){ // left one occupied/boundary, then could move right
      if(dices.find(P2D::cellToP2D(c)) != dices.end()){ //busy cell or boundary cell which acts like a shore
        res = dice->reverse_move("right", dices, __func__, true, SIMPLE_MOVE);
        if(res.first){
          int i = 1;
          while(i <= res.second){
            moves.push_back(Action(P2D(x, y), P2D(i, 0), SIMPLE_MOVE_BACKWARD_WEIGHT*i, SIMPLE_MOVE, P2D(x+i, y)));
            i++;
          }
        }
      }else{
        res = dice->reverse_move("left", dices, __func__, true, SIMPLE_MOVE);
        if(res.first)
          moves.push_back(Action(P2D(x, y), P2D(-res.second, 0), SIMPLE_MOVE_BACKWARD_WEIGHT*res.second, SIMPLE_MOVE, P2D(x-res.second, y)));
      }
    }
    if((c.get_x() == x+1 || x == MAP_WIDTH-1) && last_action_performed.dir != P2D::RIGHT){ //right one occupied/boundary, then could move left 
      if(dices.find(P2D::cellToP2D(c)) != dices.end()){ //busy cell or boundary cell which acts like a shore
        res = dice->reverse_move("left", dices, __func__, true, SIMPLE_MOVE);
        if(res.first){
          int i = 1;
          while(i <= res.second){
            moves.push_back(Action(P2D(x, y), P2D((-1*i), 0), SIMPLE_MOVE_BACKWARD_WEIGHT*i, SIMPLE_MOVE, P2D(x-i, y)));
            i++;
          }
        }
      }else{
        res = dice->reverse_move("right", dices, __func__, true, SIMPLE_MOVE);
        if(res.first)
          moves.push_back(Action(P2D(x, y), P2D(res.second, 0), SIMPLE_MOVE_BACKWARD_WEIGHT*res.second, SIMPLE_MOVE, P2D(x+res.second, y)));
      }
    }
    if((c.get_y() == y+1 || y == MAP_HEIGHT-1) && last_action_performed.dir != P2D::DOWN){ //down one occupied/boundary, then could move up 
      if(dices.find(P2D::cellToP2D(c)) != dices.end()){ //busy cell or boundary cell which acts like a shore
        res = dice->reverse_move("up", dices, __func__, true, SIMPLE_MOVE);
        if(res.first){
          int i = 1;
          while(i <= res.second){
            moves.push_back(Action(P2D(x, y), P2D(0, (-1*i)), SIMPLE_MOVE_BACKWARD_WEIGHT*i, SIMPLE_MOVE, P2D(x, y-i)));
            i++;
          }
        }
      }else{
        res = dice->reverse_move("down", dices, __func__, true, SIMPLE_MOVE);
        if(res.first)
          moves.push_back(Action(P2D(x, y), P2D(0, res.second), SIMPLE_MOVE_BACKWARD_WEIGHT*res.second, SIMPLE_MOVE, P2D(x, y+res.second)));
      }
    }
    if((c.get_y() == y-1 || y == 0) && last_action_performed.dir != P2D::UP){ //up one occupied, then could move down 
      if(dices.find(P2D::cellToP2D(c)) != dices.end()){ //busy cell or boundary cell which acts like a shore
        res = dice->reverse_move("down", dices, __func__, true, SIMPLE_MOVE);
        if(res.first){
          int i = 1;
          while(i <= res.second){
            moves.push_back(Action(P2D(x, y), P2D(0, i), SIMPLE_MOVE_BACKWARD_WEIGHT*i, SIMPLE_MOVE, P2D(x, y+i)));
            i++;
          }
        }
      }else{
        res = dice->reverse_move("up", dices, __func__, true, SIMPLE_MOVE);
        if(res.first)
          moves.push_back(Action(P2D(x, y), P2D(0, -res.second), SIMPLE_MOVE_BACKWARD_WEIGHT*res.second, SIMPLE_MOVE, P2D(x, y-res.second)));
      }
    }
  }
}

/**
  this is reached if the current dice analyzed is GREEN without available move(=0); the legal backward 
  actions are added to @moves vector.

  For every direction(up, down, left, right) the action is simulated(doesn't really modify current
  dice position neither number of moves available). If the response is that the action could be done, 
  then is added to moves vector. 

  Note that if the last move the dice did was (eg. left) the opposite move (right, in this case) is
  not considered legal. This because we're looking for the most difficult moves sequence (backward)
  and if this was allowed, the dice could just move forward and backward until has moves available.
  (quite banal!)
  @param dice the considered dice
  @param moves vector of actions passed by reference 
*/  
void AleaGame::green_dice_possible_moves_being_pushed_backward(Dice *dice, vector<Action> &moves){
  int x = dice->get_position().get_x(), y = dice->get_position().get_y();

  if(x>0 && last_action_performed.dir != P2D::RIGHT){ //check if can have been pushed from left
    pair<bool, int> res = dices.at(P2D(x,y))->reverse_move("left", dices, __func__, true, PUSHED_MOVE);
    if(res.first)
      moves.push_back(Action(P2D(x, y), P2D::LEFT, PUSHED_MOVE_BACKWARD_WEIGHT*res.second, PUSHED_MOVE, P2D(x-(res.second+1), y)));
  }
  if(x+2<MAP_WIDTH && last_action_performed.dir != P2D::LEFT){ //check if can have been pushed from right
    pair<bool, int> res = dices.at(P2D(x,y))->reverse_move("right", dices, __func__, true, PUSHED_MOVE);
    if(res.first)
      moves.push_back(Action(P2D(x, y), P2D::RIGHT, PUSHED_MOVE_BACKWARD_WEIGHT*res.second, PUSHED_MOVE, P2D(x+(res.second+1), y))); 
  }
  if(y>0 && last_action_performed.dir != P2D::DOWN){ //check if can have been pushed from up
    pair<bool, int> res = dices.at(P2D(x,y))->reverse_move("up", dices, __func__, true, PUSHED_MOVE);
    if(res.first)
      moves.push_back(Action(P2D(x, y), P2D::UP, PUSHED_MOVE_BACKWARD_WEIGHT*res.second, PUSHED_MOVE, P2D(x, y-(res.second+1))));
  }
  if(y+2<MAP_HEIGHT && last_action_performed.dir != P2D::UP){ //check if can have been pushed from down
    pair<bool, int> res = dices.at(P2D(x,y))->reverse_move("down", dices, __func__, true, PUSHED_MOVE);
    if(res.first)
      moves.push_back(Action(P2D(x, y), P2D::DOWN, PUSHED_MOVE_BACKWARD_WEIGHT*res.second, PUSHED_MOVE, P2D(x, y+(res.second+1))));
  }
}

/**
  this analyzes, for each dice, the possible moves which could be done Forward
  @param excluding_heuristic_possible_moves it's a pair which gives the number of times the heuristic
                                          has been activated over the total number of moves found
  @return a vector of legal action formed by:
         <from_position, to_position, move_weight, move_type>
*/
vector<Action> AleaGame::possible_moves_forward(vector<pair<int, int>> &excluding_heuristic_possible_moves_activation) {
  vector<Action> moves;
  for (auto const& pair: dices) {
    Dice *dice = pair.second;
    if(dice->get_n_moves() > 0){
      if(dice->get_actual_type().compare("WhiteDice") == 0)
        white_dice_possible_moves_forward(dice, moves, excluding_heuristic_possible_moves_activation[0]);
      else if(dice->get_actual_type().compare("RedDice") == 0)
        red_dice_possible_moves_forward(dice, moves, excluding_heuristic_possible_moves_activation[1]);
      else if(dice->get_actual_type().compare("YellowDice") == 0)
        yellow_dice_possible_moves_forward(dice, moves, excluding_heuristic_possible_moves_activation[2]);
      else if(dice->get_actual_type().compare("GreenDice") == 0)
        green_dice_possible_moves_forward(dice, moves, excluding_heuristic_possible_moves_activation[3]);
    }
  }
  return moves;
}

/**
  this is reached if the current dice analyzed is WHITE; the legal forward actions 
  are added to @moves vector.

  For every direction(up, down, left, right) the action is simulated(doesn't really modify current
  dice position neither number of moves available). If the response is that the action could be done, 
  then is added to moves vector. 

  Note that a heuristic excludes the moves which brings the dice too far (nMoves-1)*1.5 
  from closer terminal. Basically if the dice cannot reach the closer terminal anymore, the
  game would fail, so we exclude that kind of moves.
  @param dice the considered dice
  @param moves vector of actions passed by reference 
  @param white_heuristic_stats pair<#times heuristic activates, #total times>
*/  
void AleaGame::white_dice_possible_moves_forward(Dice *dice, vector<Action> &moves, pair<int, int> &white_heuristic_stats){
  int x = dice->get_position().get_x(), y = dice->get_position().get_y();
  double distance_from_closer_terminal_after_move = 0.00;
  vector<Cell> cells;
  if(x>0) cells.push_back(Cell(x-1, y));
  if(x<MAP_WIDTH-1) cells.push_back(Cell(x+1, y));
  if(y>0) cells.push_back(Cell(x, y-1));
  if(y<MAP_HEIGHT-1) cells.push_back(Cell(x, y+1));
  for(Cell c : cells){
    pair<bool, int> res = NO_MOVE;
    if(c.get_x() == x-1){
      res = dice->move("left", dices, __func__, true);
      if(res.first){
        distance_from_closer_terminal_after_move = calculate_distance_from_closer_terminal(P2D(x-1, y));
        if(distance_from_closer_terminal_after_move > dice->get_n_moves() && !check_dice_could_be_pushed(dice))
          white_heuristic_stats.first++; //heuristic activates
        else{
          if(dices.find(P2D::cellToP2D(c)) == dices.end())
            moves.push_back(Action(P2D(x, y), P2D::LEFT, SIMPLE_MOVE_FORWARD_WEIGHT, distance_from_closer_terminal_after_move, SIMPLE_MOVE));
          else
            moves.push_back(Action(P2D(x, y), P2D::LEFT, PUSHED_MOVE_FORWARD_WEIGHT, distance_from_closer_terminal_after_move, PUSHED_MOVE));       
        }
        white_heuristic_stats.second++;
      } 
    }
    if(c.get_x() == x+1){
      res = dice->move("right", dices, __func__, true);
      if(res.first){
        distance_from_closer_terminal_after_move = calculate_distance_from_closer_terminal(P2D(x+1, y));
        if(distance_from_closer_terminal_after_move > dice->get_n_moves() && !check_dice_could_be_pushed(dice))
          white_heuristic_stats.first++; //heuristic activates
        else{
          if(dices.find(P2D::cellToP2D(c)) == dices.end())
            moves.push_back(Action(P2D(x, y), P2D::RIGHT, SIMPLE_MOVE_FORWARD_WEIGHT, distance_from_closer_terminal_after_move, SIMPLE_MOVE));
          else
            moves.push_back(Action(P2D(x, y), P2D::RIGHT, PUSHED_MOVE_FORWARD_WEIGHT, distance_from_closer_terminal_after_move, PUSHED_MOVE));           
        }
        white_heuristic_stats.second++;
      }
    }
    if(c.get_y() == y-1){
      res = dice->move("up", dices, __func__, true);
      if(res.first){
        distance_from_closer_terminal_after_move = calculate_distance_from_closer_terminal(P2D(x, y-1));
        if(distance_from_closer_terminal_after_move > dice->get_n_moves() && !check_dice_could_be_pushed(dice))
          white_heuristic_stats.first++; //heuristic activates
        else{
          if(dices.find(P2D::cellToP2D(c)) == dices.end())
            moves.push_back(Action(P2D(x, y), P2D::UP, SIMPLE_MOVE_FORWARD_WEIGHT, distance_from_closer_terminal_after_move, SIMPLE_MOVE));
          else
            moves.push_back(Action(P2D(x, y), P2D::UP, PUSHED_MOVE_FORWARD_WEIGHT, distance_from_closer_terminal_after_move, PUSHED_MOVE));
        }
        white_heuristic_stats.second++;      
      }
    }
    if(c.get_y() == y+1){
      res = dice->move("down", dices, __func__, true);
      if(res.first){
        distance_from_closer_terminal_after_move = calculate_distance_from_closer_terminal(P2D(x, y+1));
        if(distance_from_closer_terminal_after_move > dice->get_n_moves() && !check_dice_could_be_pushed(dice))
          white_heuristic_stats.first++; //heuristic activates
        else{
          if(dices.find(P2D::cellToP2D(c)) == dices.end())
            moves.push_back(Action(P2D(x, y), P2D::DOWN, SIMPLE_MOVE_BACKWARD_WEIGHT, distance_from_closer_terminal_after_move, SIMPLE_MOVE));
          else
            moves.push_back(Action(P2D(x, y), P2D::DOWN, PUSHED_MOVE_BACKWARD_WEIGHT, distance_from_closer_terminal_after_move, PUSHED_MOVE)); 
        }
        white_heuristic_stats.second++;
      }
    }
  }
}

/**
  this is reached if the current dice analyzed is RED; the legal forward actions 
  are added to @moves vector.

  For every direction(up, down, left, right) the action is simulated(doesn't really modify current
  dice position neither number of moves available). If the response is that the action could be done, 
  then is added to moves vector. 

  Note that a heuristic excludes the moves which brings the dice too far (nMoves-1)
  from closer terminal. Basically if the dice cannot reach the closer terminal anymore, the
  game would fail, so we exclude that kind of moves.
  @param dice the considered dice
  @param moves vector of actions passed by reference 
  @param red_heuristic_stats pair<#times heuristic activates, #total times>
*/  
void AleaGame::red_dice_possible_moves_forward(Dice *dice, vector<Action> &moves, pair<int, int> &red_heuristic_stats){
  int x = dice->get_position().get_x(), y = dice->get_position().get_y();
  double distance_from_closer_terminal_after_move = 0.00;
  vector<Cell> cells;
  if(x>0) cells.push_back(Cell(x-1, y));
  if(x<MAP_WIDTH-1) cells.push_back(Cell(x+1, y));
  if(y>0) cells.push_back(Cell(x, y-1));
  if(y<MAP_HEIGHT-1) cells.push_back(Cell(x, y+1));
  for(Cell c : cells){
    pair<bool, int> res = NO_MOVE;
    if(c.get_x() == x-1){
      res = dice->move("left", dices, __func__, true);
      if(res.first){
        distance_from_closer_terminal_after_move = calculate_distance_from_closer_terminal(P2D(x-1, y));
        if(distance_from_closer_terminal_after_move <= RED_DICE_EXCLUDE_MOVE_FORWARD_HEURISTICS(dice->get_n_moves())){
          if(dices.find(P2D::cellToP2D(c)) == dices.end())
            moves.push_back(Action(P2D(x, y), P2D::LEFT, SIMPLE_MOVE_FORWARD_WEIGHT, distance_from_closer_terminal_after_move, SIMPLE_MOVE));      
          else
            moves.push_back(Action(P2D(x, y), P2D::LEFT, PUSHED_MOVE_FORWARD_WEIGHT, distance_from_closer_terminal_after_move, PUSHED_MOVE));      
        }else
          red_heuristic_stats.first++; //heuristic activates
        red_heuristic_stats.second++;
      } 
    }
    if(c.get_x() == x+1){
      res = dice->move("right", dices, __func__, true);
      if(res.first){
        distance_from_closer_terminal_after_move = calculate_distance_from_closer_terminal(P2D(x+1, y));
        if(distance_from_closer_terminal_after_move <= RED_DICE_EXCLUDE_MOVE_FORWARD_HEURISTICS(dice->get_n_moves())){
          if(dices.find(P2D::cellToP2D(c)) == dices.end())
            moves.push_back(Action(P2D(x, y), P2D::RIGHT, SIMPLE_MOVE_FORWARD_WEIGHT, distance_from_closer_terminal_after_move, SIMPLE_MOVE));      
          else
            moves.push_back(Action(P2D(x, y), P2D::RIGHT, PUSHED_MOVE_FORWARD_WEIGHT, distance_from_closer_terminal_after_move, PUSHED_MOVE));       
        }else
          red_heuristic_stats.first++; //heuristic activates
        red_heuristic_stats.second++;
      } 
    }
    if(c.get_y() == y-1){
      res = dice->move("up", dices, __func__, true);
      if(res.first){
        distance_from_closer_terminal_after_move = calculate_distance_from_closer_terminal(P2D(x, y-1));
        if(distance_from_closer_terminal_after_move <= RED_DICE_EXCLUDE_MOVE_FORWARD_HEURISTICS(dice->get_n_moves())){
          if(dices.find(P2D::cellToP2D(c)) == dices.end())
            moves.push_back(Action(P2D(x, y), P2D::UP, SIMPLE_MOVE_FORWARD_WEIGHT, distance_from_closer_terminal_after_move, SIMPLE_MOVE));      
          else
            moves.push_back(Action(P2D(x, y), P2D::UP, PUSHED_MOVE_FORWARD_WEIGHT, distance_from_closer_terminal_after_move, PUSHED_MOVE));      
        }else
          red_heuristic_stats.first++; //heuristic activates
        red_heuristic_stats.second++;
      }
    }
    if(c.get_y() == y+1){
      res = dice->move("down", dices, __func__, true);
      if(res.first){
        distance_from_closer_terminal_after_move = calculate_distance_from_closer_terminal(P2D(x, y+1));
        if(distance_from_closer_terminal_after_move <= RED_DICE_EXCLUDE_MOVE_FORWARD_HEURISTICS(dice->get_n_moves())){
          if(dices.find(P2D::cellToP2D(c)) == dices.end())
            moves.push_back(Action(P2D(x, y), P2D::DOWN, SIMPLE_MOVE_FORWARD_WEIGHT, distance_from_closer_terminal_after_move, SIMPLE_MOVE)); 
          else
            moves.push_back(Action(P2D(x, y), P2D::DOWN, PUSHED_MOVE_FORWARD_WEIGHT, distance_from_closer_terminal_after_move, PUSHED_MOVE)); 
        }else
          red_heuristic_stats.first++; //heuristic activates
        red_heuristic_stats.second++;
      }      
    }
  }
}


/**
  this is reached if the current dice analyzed is YELLOW; the legal forward actions 
  are added to @moves vector.

  For every direction(up, down, left, right) the action is simulated(doesn't really modify current
  dice position neither number of moves available). If the response is that the action could be done, 
  then is added to moves vector. 

  Note that a heuristic excludes the moves which brings the dice too far nMoves*2
  from closer terminal. Basically if the dice cannot reach the closer terminal anymore, the
  game would fail, so we exclude that kind of moves.
  @param dice the considered dice
  @param moves vector of actions passed by reference 
  @param yellow_heuristic_stats pair<#times heuristic activates, #total times>
*/  
void AleaGame::yellow_dice_possible_moves_forward(Dice *dice, vector<Action> &moves, pair<int, int> &yellow_heuristic_stats){
  int x = dice->get_position().get_x(), y = dice->get_position().get_y();
  double distance_from_closer_terminal_after_move = 0.00;
  vector<Cell> cells;
  if(x>0) cells.push_back(Cell(x-1, y));
  if(x<MAP_WIDTH-1) cells.push_back(Cell(x+1, y));
  if(y>0) cells.push_back(Cell(x, y-1));
  if(y<MAP_HEIGHT-1) cells.push_back(Cell(x, y+1));
  for(Cell c : cells){
    pair<bool, int> res = NO_MOVE;
    if(c.get_x() == x-1){
      res = dice->move("left", dices, __func__, true);
      if(res.first){
        if(res.second == 1){
          distance_from_closer_terminal_after_move = calculate_distance_from_closer_terminal(P2D(x-1, y));
          if(distance_from_closer_terminal_after_move <= YELLOW_DICE_EXCLUDE_MOVE_FORWARD_HEURISTICS(dice->get_n_moves()))
            moves.push_back(Action(P2D(x, y), P2D::LEFT, SIMPLE_MOVE_FORWARD_WEIGHT, distance_from_closer_terminal_after_move, SIMPLE_MOVE)); 
          else
            yellow_heuristic_stats.first++; //heuristic activates
          yellow_heuristic_stats.second++;
        } 
        else{
          distance_from_closer_terminal_after_move = calculate_distance_from_closer_terminal(P2D(x-2, y));
          if(distance_from_closer_terminal_after_move <= YELLOW_DICE_EXCLUDE_MOVE_FORWARD_HEURISTICS(dice->get_n_moves()))
            moves.push_back(Action(P2D(x, y), P2D(-2, 0), JUMPING_MOVE_FORWARD_WEIGHT, distance_from_closer_terminal_after_move, JUMP_MOVE)); 
          else
            yellow_heuristic_stats.first++; //heuristic activates
          yellow_heuristic_stats.second++;
        }
        
      }      
    }
    if(c.get_x() == x+1){
      res = dice->move("right", dices, __func__, true);
      if(res.first){
        if(res.second == 1){
          distance_from_closer_terminal_after_move = calculate_distance_from_closer_terminal(P2D(x+1, y));
          if(distance_from_closer_terminal_after_move <= YELLOW_DICE_EXCLUDE_MOVE_FORWARD_HEURISTICS(dice->get_n_moves()))
            moves.push_back(Action(P2D(x, y), P2D::RIGHT, SIMPLE_MOVE_FORWARD_WEIGHT, distance_from_closer_terminal_after_move, SIMPLE_MOVE)); 
          else
            yellow_heuristic_stats.first++; //heuristic activates
          yellow_heuristic_stats.second++;
        }
        else{ 
          distance_from_closer_terminal_after_move = calculate_distance_from_closer_terminal(P2D(x+2, y));
          if(distance_from_closer_terminal_after_move <= YELLOW_DICE_EXCLUDE_MOVE_FORWARD_HEURISTICS(dice->get_n_moves()))
            moves.push_back(Action(P2D(x, y), P2D(2, 0), JUMPING_MOVE_FORWARD_WEIGHT, distance_from_closer_terminal_after_move, JUMP_MOVE)); 
          else
            yellow_heuristic_stats.first++; //heuristic activates
          yellow_heuristic_stats.second++;
        }
      }      
    }
    if(c.get_y() == y-1){
      res = dice->move("up", dices, __func__, true);
      if(res.first){
        if(res.second == 1){
          distance_from_closer_terminal_after_move = calculate_distance_from_closer_terminal(P2D(x-1, y));
          if(distance_from_closer_terminal_after_move <= YELLOW_DICE_EXCLUDE_MOVE_FORWARD_HEURISTICS(dice->get_n_moves()))
            moves.push_back(Action(P2D(x, y), P2D::UP, SIMPLE_MOVE_FORWARD_WEIGHT, distance_from_closer_terminal_after_move, SIMPLE_MOVE)); 
          else
            yellow_heuristic_stats.first++; //heuristic activates
          yellow_heuristic_stats.second++;
        }else{
          distance_from_closer_terminal_after_move = calculate_distance_from_closer_terminal(P2D(x-2, y));
          if(distance_from_closer_terminal_after_move <= YELLOW_DICE_EXCLUDE_MOVE_FORWARD_HEURISTICS(dice->get_n_moves()))
            moves.push_back(Action(P2D(x, y), P2D(0, -2), JUMPING_MOVE_FORWARD_WEIGHT, distance_from_closer_terminal_after_move, JUMP_MOVE)); 
          else
            yellow_heuristic_stats.first++; //heuristic activates
          yellow_heuristic_stats.second++;
        }
      }      
    }
    if(c.get_y() == y+1){
      res = dice->move("down", dices, __func__, true);
      if(res.first){
        if(res.second == 1){
          distance_from_closer_terminal_after_move = calculate_distance_from_closer_terminal(P2D(x, y+1));
          if(distance_from_closer_terminal_after_move <= YELLOW_DICE_EXCLUDE_MOVE_FORWARD_HEURISTICS(dice->get_n_moves()))
            moves.push_back(Action(P2D(x, y), P2D::DOWN, SIMPLE_MOVE_FORWARD_WEIGHT, distance_from_closer_terminal_after_move, SIMPLE_MOVE)); 
          else
            yellow_heuristic_stats.first++; //heuristic activates
          yellow_heuristic_stats.second++;
        }else{
          distance_from_closer_terminal_after_move = calculate_distance_from_closer_terminal(P2D(x, y+2));
          if(distance_from_closer_terminal_after_move <= YELLOW_DICE_EXCLUDE_MOVE_FORWARD_HEURISTICS(dice->get_n_moves()))
            moves.push_back(Action(P2D(x, y), P2D(0, 2), JUMPING_MOVE_FORWARD_WEIGHT, distance_from_closer_terminal_after_move, JUMP_MOVE)); 
          else
            yellow_heuristic_stats.first++; //heuristic activates
          yellow_heuristic_stats.second++;
        }
      }      
    }
  }
}

/**
  this is reached if the current dice analyzed is GREEN; the legal forward actions 
  are added to @moves vector.

  For every direction(up, down, left, right) the action is simulated(doesn't really modify current
  dice position neither number of moves available). If the response is that the action could be done, 
  then is added to moves vector. 

  Note that a heuristic excludes the moves which brings the dice too far (nMoves-1)*1.5
  from closer terminal. Basically if the dice cannot reach the closer terminal anymore, the
  game would fail, so we exclude that kind of moves.
  @param dice the considered dice
  @param moves vector of actions passed by reference 
  @param green_heuristic_stats pair<#times heuristic activates, #total times>
*/  
void AleaGame::green_dice_possible_moves_forward(Dice *dice, vector<Action> &moves, pair<int, int> &green_heuristic_stats){
  int x = dice->get_position().get_x(), y = dice->get_position().get_y();
  double distance_from_closer_terminal_after_move = 0.00;
  vector<Cell> cells;
  if(x>0) cells.push_back(Cell(x-1, y));
  if(x<MAP_WIDTH-1) cells.push_back(Cell(x+1, y));
  if(y>0) cells.push_back(Cell(x, y-1));
  if(y<MAP_HEIGHT-1) cells.push_back(Cell(x, y+1));
  for(Cell c : cells){
    pair<bool, int> res = NO_MOVE;
    if(c.get_x() == x-1){
      res = dice->move("left", dices, __func__, true);
      if(res.first){
        distance_from_closer_terminal_after_move = calculate_distance_from_closer_terminal(P2D(x-res.second, y));
        if(distance_from_closer_terminal_after_move > dice->get_n_moves() && !check_dice_could_be_pushed(dice))
          green_heuristic_stats.first++; //heuristic activates
        else
          moves.push_back(Action(P2D(x, y), P2D::LEFT, (SIMPLE_MOVE_FORWARD_WEIGHT*res.second), distance_from_closer_terminal_after_move, SIMPLE_MOVE));       
        green_heuristic_stats.second++;
      }
    }
    if(c.get_x() == x+1){
      res = dice->move("right", dices, __func__, true);
      if(res.first){
        distance_from_closer_terminal_after_move = calculate_distance_from_closer_terminal(P2D(x+res.second, y));
        if(distance_from_closer_terminal_after_move > dice->get_n_moves() && !check_dice_could_be_pushed(dice))
          green_heuristic_stats.first++; //heuristic activates
        else
          moves.push_back(Action(P2D(x, y), P2D::RIGHT, (SIMPLE_MOVE_FORWARD_WEIGHT*res.second), distance_from_closer_terminal_after_move, SIMPLE_MOVE));       
        green_heuristic_stats.second++;
      }
    }
    if(c.get_y() == y-1){
      res = dice->move("up", dices, __func__, true);
      if(res.first){
        distance_from_closer_terminal_after_move = calculate_distance_from_closer_terminal(P2D(x, y-res.second));
        if(distance_from_closer_terminal_after_move > dice->get_n_moves() && !check_dice_could_be_pushed(dice))
          green_heuristic_stats.first++; //heuristic activates
        else
          moves.push_back(Action(P2D(x, y), P2D::UP, (SIMPLE_MOVE_FORWARD_WEIGHT*res.second), distance_from_closer_terminal_after_move, SIMPLE_MOVE));              
        green_heuristic_stats.second++;
      }
    }
    if(c.get_y() == y+1){
      res = dice->move("down", dices, __func__, true);
      if(res.first){
        distance_from_closer_terminal_after_move = calculate_distance_from_closer_terminal(P2D(x, y+res.second));
        if(distance_from_closer_terminal_after_move > dice->get_n_moves() && !check_dice_could_be_pushed(dice))
          green_heuristic_stats.first++; //heuristic activates
        else
          moves.push_back(Action(P2D(x, y), P2D::DOWN, (SIMPLE_MOVE_FORWARD_WEIGHT*res.second), distance_from_closer_terminal_after_move, SIMPLE_MOVE));             
        green_heuristic_stats.second++;
      }
    }
  }
}


bool AleaGame::check_dice_could_be_pushed(Dice *dice){
  P2D dice_position(dice->get_position().get_x(), dice->get_position().get_y());
  for(pair<P2D, Dice *> pair : dices)
    if(pair.first != dice_position)
      if(pair.second->get_actual_type().compare("RedDice") == 0 || pair.second->get_actual_type().compare("WhiteDice") == 0)
        if((pair.second->get_n_moves()+dice->get_n_moves())>(calculate_distance_from_closer_terminal(dice_position)+dice_position.manatthan(pair.first)))
          return true;
          
  return false;
}

bool AleaGame::move(const Action& action, bool is_moving_backward) {
  return move(action.from, action.dir, action.movement_type, is_moving_backward);
}

/**
  this method manages the move of the dice in position @pos
  @param pos position of the dice to be moved
  @param dir direction of move
  @param movement_type simple, jumping, pushed move
  @param is_moving_backward if the move is backward (true), or forward (false)
  @return true, if the move has been successful
*/  
bool AleaGame::move(const P2D pos, const P2D dir, const int movement_type, bool is_moving_backward) {
  if(dices.find(pos) != dices.end()){
    Dice *dice = dices[pos];
    if(is_moving_backward){
      if(dir.x<0)
        return dice->reverse_move("left", dices, __func__, false, movement_type).first;
      else if(dir.x>0)
        return dice->reverse_move("right", dices, __func__, false, movement_type).first;
      else if(dir.y>0)
        return dice->reverse_move("down", dices, __func__, false, movement_type).first;
      else if(dir.y<0)
        return dice->reverse_move("up", dices, __func__, false, movement_type).first;
    }else{
      if(dir.x<0)
        return dice->move("left", dices, __func__, false, movement_type).first;
      else if(dir.x>0)
        return dice->move("right", dices, __func__, false, movement_type).first;
      else if(dir.y>0)
        return dice->move("down", dices, __func__, false, movement_type).first;
      else if(dir.y<0)
        return dice->move("up", dices, __func__, false, movement_type).first;
    }
  }
  return false;
}

/**
  This method searchs for all the banal configuration which the user could find at the start to 
  solve the level. This is a wrapper method cuz the process is recursevely, the wrapper 
  thinks for the first dice, the core thinks for the rest of the dices.  
  Note that we're thinking forward, so we're looking for the easier solutions the user could
  find. 
  A banal configuration is a sequence of moves which brings a dice(or even more than a dice, reason why
  this is a recursive process) from its position straight(without having any interaction with other dices) to a terminal,
  so basically the manhattan distance between it and a terminal is equal to its number of available
  moves.
  When more than a dice have manhattan distance from a terminal equal to them number of available moves
  a conflict born, the terminal is disputed(eg. 2 dices could reach the same terminal straightly, 
  so we'll have two banal config: the first one assigns the first dice to the terminal without moving 
  the second dice, the second one vice versa).
  Note that even if the manhattan distance theoretically allows a dice to reach a terminal, this could
  not be possible (eg. man_distance=2, n_moves=2, but there's an obstacle between them (another dice), 
  so the dice should have at least the number of moves needed to bypass the obstacle and reach the 
  terminal).
  @return a vector containing all the banal solutions found. Each element(pair) in the vector
          is formed by the instance of AleaGame on which are applied the actions(moves) contained
          in the relative vector to get the banal configuration.
*/  
vector<pair<AleaGame, vector<Action>>> AleaGame::find_banal_starts_forward_search_wrapper(){
  vector<pair<AleaGame, vector<Action>>> banal_games;
  for(pair<P2D, Dice*> pair : this->dices){
    for(P2D terminal : this->terminals){
      if(pair.first.manatthan(terminal) == pair.second->get_n_moves() && pair.first!=terminal){
        if(terminal_is_disputed(terminal, this->dices)){
          vector<std::pair<P2D, Dice *>> disputer_dices_result = disputer_dices(terminal, this->dices);
          if(!disputed_is_assigned(terminal, disputer_dices_result)){
            for(std::pair<P2D, Dice*> d : disputer_dices_result){
              std::pair<AleaGame, vector<Action>> res = make_pair(*this, vector<Action>());
              if(find_banal_start_calculate_route(res.second, d, d.second->get_n_moves(), terminal, res.first.dices)){
                for(Action action : res.second)
                  res.first.move(action, false);  
                auto banal_start = find_banal_starts_forward_search(res); //calling the recursive search to find other dice which can be moved banally
                if(!banal_start_already_found(banal_start, banal_games))
                  banal_games.push_back(banal_start);                
              }
            }
          }
        }else{ //terminal is not disputed
          std::pair<AleaGame, vector<Action>> res = make_pair(*this, vector<Action>());
          if(find_banal_start_calculate_route(res.second, pair, pair.second->get_n_moves(), terminal, res.first.dices)){
            for(Action action : res.second)
              res.first.move(action, false);
            auto banal_start = find_banal_starts_forward_search(res); //calling the recursive search to find other dice which can be moved banally
            if(!banal_start_already_found(banal_start, banal_games))
              banal_games.push_back(banal_start);
          }
        }
      }
    }
  }   
  return banal_games;
}

/**
  This method searchs for all the banal configuration which the user could find at the start to 
  solve the level. This is the recursive core which thinks for the dices not considered by the wrapper.  
  Note that we're thinking forward, so we're looking for the easier solutions the user could
  find. 
  A banal configuration is a sequence of moves which brings a dice(or even more than a dice, reason why
  this is a recursive process) from its position straight(without having any interaction with other dices) to a terminal,
  so basically the manhattan distance between it and a terminal is equal to its number of available
  moves.
  When more than a dice have manhattan distance from a terminal equal to them number of available moves
  a conflict born, the terminal is disputed(eg. 2 dices could reach the same terminal straightly, 
  so we'll have two banal config: the first one assigns the first dice to the terminal without moving 
  the second dice, the second one vice versa).
  Note that even if the manhattan distance theoretically allows a dice to reach a terminal, this could
  not be possible (eg. man_distance=2, n_moves=2, but there's an obstacle between them (another dice), 
  so the dice should have at least the number of moves needed to bypass the obstacle and reach the 
  terminal).
  @param previous_game_actions a pair containing the starting configuration and the moves found by 
                            the wrapper(for the first dice analyzed). This will be the starting point 
                            for this core method on which the following moves will be pushed back
  @return a vector containing all the banal solutions found. Each element(pair) in the vector
          is formed by the instance of AleaGame on which are applied the actions(moves) contained
          in the relative vector to get the banal configuration.
*/  
pair<AleaGame, vector<Action>> AleaGame::find_banal_starts_forward_search(pair<AleaGame, vector<Action>> previous_game_actions){
  pair<AleaGame, vector<Action>> moves = previous_game_actions;
  for(pair<P2D, Dice*> pair : previous_game_actions.first.dices){
    for(P2D terminal : previous_game_actions.first.terminals){ 
      if(pair.first.manatthan(terminal) == pair.second->get_n_moves() && pair.first!=terminal){
        if(terminal_is_disputed(terminal, previous_game_actions.first.dices)){
          vector<std::pair<P2D, Dice *>> disputer_dices_result = disputer_dices(terminal, moves.first.dices);
          if(!disputed_is_assigned(terminal, disputer_dices_result)){
            for(std::pair<P2D, Dice*> d : disputer_dices_result){
              vector<Action> actions;
              if(find_banal_start_calculate_route(actions, d, d.second->get_n_moves(), terminal, moves.first.dices)){                
                for(Action action : actions){
                  if(moves.first.dices.find(action.from) != moves.first.dices.end()){
                    moves.first.move(action, false);
                    moves.second.push_back(action);
                  }
                }
                moves = find_banal_starts_forward_search(make_pair(moves.first, moves.second));
              }
            }
          }
        }else{
          vector<Action> actions;
          if(find_banal_start_calculate_route(actions, pair, pair.second->get_n_moves(), terminal, moves.first.dices)){
            for(Action action : actions){
              if(moves.first.dices.find(action.from) != moves.first.dices.end()){
                moves.first.move(action, false);
                moves.second.push_back(action);
              } 
            }
          }
        }
      }
    }
  }
  return moves;
}

/**
  This methods executes the moves specified to reach the banal configuration previously found
  @param banal_configuration a pair containing the starting configuration and the moves found for the 
                            considered banal cofiguration
  @param difficulty banal configuration difficulty (will be obtained doing moves specified
                    by @banal_configuration.second)
  @param counter i-th banal configuration
  @param banal_search_number total number of banal configuration found
  @return true if the banal configuration found is already a solution (no A* search needed), false otherwise
*/  
bool AleaGame::setting_up_banal_configuration(pair<AleaGame, vector<Action>> banal_configuration, double *difficulty, int counter, int banal_search_number){
  *this = banal_configuration.first;
  cout<<"\nBanal Starting Configuration Found: ("<<counter<<"/"<<banal_search_number<<")\n";
  for(Action move : banal_configuration.second){
    *difficulty += move.weight;
    cout<<move<<endl;
  }
  if(this->is_valid_ending_configuration_forward_search())
    return true;
  return false;
}

/**
  This methods is useful because detecs the transpositions: same arrival configuration with different 
  moves sequence.
  If a banal configuration is a transposition of another one, then is not considered anymore.
  @param banal_config a pair containing the starting configuration and the moves found for the 
                      considered banal cofiguration
  @param banal_config_vector a vector containing all the banal configuration found so far
  @return true if the banal configuration already belongs to the @banal_config_vector
          (the considered @banal_config is a transposition of another banal configuration)
*/  
bool AleaGame::banal_start_already_found(pair<AleaGame, vector<Action>> banal_config, vector<pair<AleaGame, vector<Action>>> banal_config_vector){
  AleaGame simulation_game = banal_config.first;
  for(Action act : banal_config.second)
    simulation_game.move(act, false);

  for(pair<AleaGame, vector<Action>> banal_start_found : banal_config_vector){
    AleaGame tmp_game = banal_start_found.first;
    for(Action act : banal_start_found.second)
      tmp_game.move(act, false);

    if(tmp_game == simulation_game)
      return true;
  }
  return false;
}

/**
  This methods detects if a terminal is disputed by more than one dice
  @param terminal_position terminal position in the map
  @param dices hash table containing all the dices and their position in the map
  @return true if more than two dices could reach the same terminal(manhattan distance only considering)
*/  
bool AleaGame::terminal_is_disputed(P2D terminal_position, unordered_map<P2D, Dice *, P2D::HashFun> dices){
  int counter = 0;
  for(pair<P2D, Dice*> pair : dices){
    if(pair.first.manatthan(terminal_position) == pair.second->get_n_moves() && pair.first!=terminal_position)
      counter++;
  }
  if(counter>1) 
    return true;
  return false;
}

/**
  This methods returns the dices which are in conflict for the same terminal
  @param terminal_position terminal position in the map
  @param dices hash table containing all the dices and their position in the map
  @return a vector containing all the dices in conflict for the same terminal
*/  
vector<pair<P2D, Dice *>> AleaGame::disputer_dices(P2D terminal_position, unordered_map<P2D, Dice *, P2D::HashFun> dices){
  vector<pair<P2D, Dice *>> res;
  for(pair<P2D, Dice*> pair : dices){
    if(pair.first.manatthan(terminal_position) == pair.second->get_n_moves() && pair.first!=terminal_position)
      res.push_back(pair);
  }
  return res;
}

//if a terminal is disputed but as already a dice on it, the dispution doesnt sussist
bool AleaGame::disputed_is_assigned(P2D terminal, vector<std::pair<P2D, Dice *>> disputer_dices){
  bool res=false;
  for(pair<P2D, Dice*> pair : disputer_dices){
    if(pair.first==terminal) res = true;
    break;
  }
  return res;
}

//tells me if the dice (which has manhattan distance from terminal = 0) can move up to the terminal in practical (imagine if there is an obstacles in between and the dice has not
//enough moves to avoid the obstacle and reach the terminal)
bool AleaGame::find_banal_start_calculate_route(vector<Action> &moves, pair<P2D, Dice*> dice, int dice_moves, P2D terminal_position, unordered_map<P2D, Dice *, P2D::HashFun> dices){
  // if(dices.find(dice.first) == dices.end())
  //   return false;
  
  if(dice_moves==0){
    if(dice.first.x == terminal_position.x && dice.first.y == terminal_position.y)
      return true;
    else
      return false;
  }  
  if(dice.first.x < terminal_position.x){//moving RIGHT
    if(dice.second->get_actual_type().compare("GreenDice") == 0){
      int i = 1;
      if(dice_moves-(i-1) > 0 && (dices.find(dice.first+P2D(i, 0)) == dices.end() && dice.first.x+i < MAP_WIDTH)){
        while(dice_moves-(i-1) > 0 && (dices.find(dice.first+P2D(i, 0)) == dices.end() && dice.first.x+i < MAP_WIDTH))
          i++;
        moves.push_back(Action(dice.first, P2D::RIGHT, SIMPLE_MOVE_FORWARD_WEIGHT, calculate_distance_from_closer_terminal(dice.first+P2D(i-1, 0)), SIMPLE_MOVE));
        dice.first=dice.first+P2D(i-1, 0);
        return find_banal_start_calculate_route(moves, dice, dice_moves-(i-1), terminal_position, dices);
      }else
        return false;
    }else{
      if(dices.find(dice.first+P2D::RIGHT) == dices.end()){
        moves.push_back(Action(dice.first, P2D::RIGHT, SIMPLE_MOVE_FORWARD_WEIGHT, calculate_distance_from_closer_terminal(dice.first+P2D::RIGHT), SIMPLE_MOVE));
        dice.first=dice.first+P2D::RIGHT;
        return find_banal_start_calculate_route(moves, dice, dice_moves-1, terminal_position, dices);
      }else{
        if(dices.find(dice.first+P2D::UP) == dices.end() && (dice.first+P2D::UP).y >= 0){ 
          moves.push_back(Action(dice.first, P2D::UP, SIMPLE_MOVE_FORWARD_WEIGHT, calculate_distance_from_closer_terminal(dice.first+P2D::UP), SIMPLE_MOVE));
          dice.first=dice.first+P2D::UP;
          return find_banal_start_calculate_route(moves, dice, dice_moves-1, terminal_position, dices);
        }else if(dices.find(dice.first+P2D::DOWN) == dices.end() && (dice.first+P2D::DOWN).y < MAP_HEIGHT){
          moves.push_back(Action(dice.first, P2D::DOWN, SIMPLE_MOVE_FORWARD_WEIGHT, calculate_distance_from_closer_terminal(dice.first+P2D::DOWN), SIMPLE_MOVE));
          dice.first=dice.first+P2D::DOWN;
          return find_banal_start_calculate_route(moves, dice, dice_moves-1, terminal_position, dices);
        }else
          return false;
      }
    }
  }
  else if(dice.first.x > terminal_position.x){//moving LEFT
    if(dice.second->get_actual_type().compare("GreenDice") == 0){
      int i = 1;
      if(dice_moves-(i-1) > 0 && (dices.find(dice.first+P2D(-i, 0)) == dices.end() && dice.first.x-i >= 0)){ //if it can move at least by one
        while(dice_moves-(i-1) > 0 && (dices.find(dice.first+P2D(-i, 0)) == dices.end() && dice.first.x-i >= 0))
          i++;
        moves.push_back(Action(dice.first, P2D::LEFT, SIMPLE_MOVE_FORWARD_WEIGHT, calculate_distance_from_closer_terminal(dice.first+P2D(-(i-1), 0)), SIMPLE_MOVE)); 
        dice.first=dice.first+P2D(-(i-1), 0);
        return find_banal_start_calculate_route(moves, dice, dice_moves-(i-1), terminal_position, dices);
      }else
        return false;
    }else{
      if(dices.find(dice.first+P2D::LEFT) == dices.end()){
        moves.push_back(Action(dice.first, P2D::LEFT, SIMPLE_MOVE_FORWARD_WEIGHT, calculate_distance_from_closer_terminal(dice.first+P2D::LEFT), SIMPLE_MOVE)); 
        dice.first=dice.first+P2D::LEFT;
        return find_banal_start_calculate_route(moves, dice, dice_moves-1, terminal_position, dices);
      }else{
        if(dices.find(dice.first+P2D::UP) == dices.end() && (dice.first+P2D::UP).y >= 0){ 
          moves.push_back(Action(dice.first, P2D::UP, SIMPLE_MOVE_FORWARD_WEIGHT, calculate_distance_from_closer_terminal(dice.first+P2D::UP),SIMPLE_MOVE)); 
          dice.first=dice.first+P2D::UP;
          return find_banal_start_calculate_route(moves, dice, dice_moves-1, terminal_position, dices);
        }else if(dices.find(dice.first+P2D::DOWN) == dices.end() && (dice.first+P2D::DOWN).y < MAP_HEIGHT){
          moves.push_back(Action(dice.first, P2D::DOWN, SIMPLE_MOVE_FORWARD_WEIGHT, calculate_distance_from_closer_terminal(dice.first+P2D::DOWN), SIMPLE_MOVE));
          dice.first=dice.first+P2D::DOWN;
          return find_banal_start_calculate_route(moves, dice, dice_moves-1, terminal_position, dices);
        }else
          return false;
      }
    }
  }
  else if(dice.first.y > terminal_position.y){//moving up
    if(dice.second->get_actual_type().compare("GreenDice") == 0){
      int i = 1;
      if(dice_moves-(i-1) > 0 && (dices.find(dice.first+P2D(0, -i)) == dices.end() && dice.first.y-i >= 0)){
        while(dice_moves-(i-1) > 0 && (dices.find(dice.first+P2D(0, -i)) == dices.end() && dice.first.y-i >= 0))
          i++;
        moves.push_back(Action(dice.first, P2D::UP, SIMPLE_MOVE_FORWARD_WEIGHT, calculate_distance_from_closer_terminal(dice.first+P2D(0, -(i-1))), SIMPLE_MOVE)); 
        dice.first=dice.first+P2D(0, -(i-1));
        return find_banal_start_calculate_route(moves, dice, dice_moves-(i-1), terminal_position, dices);
      }else
        return false;
    }else{
      if(dices.find(dice.first+P2D::UP) == dices.end()){
        moves.push_back(Action(dice.first, P2D::UP, SIMPLE_MOVE_FORWARD_WEIGHT, calculate_distance_from_closer_terminal(dice.first+P2D::UP), SIMPLE_MOVE)); 
        dice.first=dice.first+P2D::UP;
        return find_banal_start_calculate_route(moves, dice, dice_moves-1, terminal_position, dices);
      }else{
        if(dices.find(dice.first+P2D::LEFT) == dices.end() && (dice.first+P2D::LEFT).x >= 0){ 
          moves.push_back(Action(dice.first, P2D::LEFT, SIMPLE_MOVE_FORWARD_WEIGHT, calculate_distance_from_closer_terminal(dice.first+P2D::LEFT), SIMPLE_MOVE)); 
          dice.first=dice.first+P2D::LEFT;
          return find_banal_start_calculate_route(moves, dice, dice_moves-1, terminal_position, dices);
        }else if(dices.find(dice.first+P2D::RIGHT) == dices.end() && (dice.first+P2D::RIGHT).x < MAP_WIDTH){
          moves.push_back(Action(dice.first, P2D::RIGHT, SIMPLE_MOVE_FORWARD_WEIGHT, calculate_distance_from_closer_terminal(dice.first+P2D::RIGHT), SIMPLE_MOVE));
          dice.first=dice.first+P2D::RIGHT;
          return find_banal_start_calculate_route(moves, dice, dice_moves-1, terminal_position, dices);
        }else
          return false;
      }
    }
  }
  else if(dice.first.y < terminal_position.y){//moving down
    if(dice.second->get_actual_type().compare("GreenDice") == 0){
      int i = 1;
      if(dice_moves-(i-1) > 0 && (dices.find(dice.first+P2D(0, i)) == dices.end() && dice.first.y+i < MAP_HEIGHT)){
        while(dice_moves-(i-1) > 0 && (dices.find(dice.first+P2D(0, i)) == dices.end() && dice.first.y+i < MAP_HEIGHT))
          i++;
        moves.push_back(Action(dice.first, P2D::DOWN, SIMPLE_MOVE_FORWARD_WEIGHT, calculate_distance_from_closer_terminal(dice.first+P2D(0, i-1)), SIMPLE_MOVE));
        dice.first=dice.first+P2D(0, i-1);
        return find_banal_start_calculate_route(moves, dice, dice_moves-(i-1), terminal_position, dices);
      }else
        return false;
    }else{
      if(dices.find(dice.first+P2D::DOWN) == dices.end()){
        moves.push_back(Action(dice.first, P2D::DOWN, SIMPLE_MOVE_FORWARD_WEIGHT, calculate_distance_from_closer_terminal(dice.first+P2D::DOWN), SIMPLE_MOVE)); 
        dice.first=dice.first+P2D::DOWN;
        return find_banal_start_calculate_route(moves, dice, dice_moves-1, terminal_position, dices);
      }else{
        if(dices.find(dice.first+P2D::LEFT) == dices.end() && (dice.first+P2D::LEFT).x >= 0){ 
          moves.push_back(Action(dice.first, P2D::LEFT, SIMPLE_MOVE_FORWARD_WEIGHT, calculate_distance_from_closer_terminal(dice.first+P2D::LEFT), SIMPLE_MOVE)); 
          dice.first=dice.first+P2D::LEFT;
          return find_banal_start_calculate_route(moves, dice, dice_moves-1, terminal_position, dices);
        }else if(dices.find(dice.first+P2D::RIGHT) == dices.end() && (dice.first+P2D::RIGHT).x < MAP_WIDTH){
          moves.push_back(Action(dice.first, P2D::RIGHT, SIMPLE_MOVE_FORWARD_WEIGHT, calculate_distance_from_closer_terminal(dice.first+P2D::RIGHT), SIMPLE_MOVE));
          dice.first=dice.first+P2D::RIGHT;
          return find_banal_start_calculate_route(moves, dice, dice_moves-1, terminal_position, dices);
        }else
          return false;
      }
    }
  }
  
  return false;
}

int AleaGame::calculate_distance_from_closer_terminal(P2D dice_position){
  int distance = numeric_limits<int>::max();
  for(auto terminal : terminals)
    distance = MIN(distance, dice_position.manatthan(P2D(terminal.x, terminal.y)));
  return distance;
}

bool AleaGame::is_valid_starting_configuration_backward_search() {
  for(auto pair: dices) {
    if (pair.second->get_n_moves() > 0)
      return false;
  }
  return true;
}

bool AleaGame::is_valid_ending_configuration_backward_search() {
  for(auto const& dice: dices) {
    if (!is_terminal(dice.first) || dice.second->get_n_moves() <= 0) return false;
  }
  return true;
}

bool AleaGame::is_valid_ending_configuration_forward_search() {
  for(auto pair: dices) {
    if (pair.second->get_n_moves() > 0 || !is_terminal(pair.first))
      return false;
  }
  return true;
}

bool AleaGame::is_terminal(const P2D& pos) const {
  return terminals.find(pos) != terminals.end();
}

bool AleaGame::has_dice(const P2D& pos) const {
    return dices.find(pos) != dices.end();
}

Action AleaGame::revert_action(Action backward_action){
  return Action(backward_action.head, P2D(backward_action.dir.x*-1, backward_action.dir.y*-1), backward_action.weight, backward_action.movement_type);
}

void AleaGame::show_map(){
  cout << "\n";
  for(auto d : dices){
    cout << d.second->get_actual_type() << ": (" << d.second->get_position().get_x() << ", " << d.second->get_position().get_y() << ")\n";
  }
  cout << "\n";
}

void AleaGame::show_moves(vector<Action> moves){
  for(auto m : moves)
    cout << "\nfrom: " << m.from << " | dir: " << m.dir << "\n";
}