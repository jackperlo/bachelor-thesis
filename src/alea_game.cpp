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

AleaGame::AleaGame(const char *filename, bool isBackward) : AleaGame(json::parse(read_json(filename)), isBackward) { }

AleaGame::AleaGame(string filename, bool isBackward) : AleaGame(json::parse(read_json(filename)), isBackward) { }

AleaGame::AleaGame(const AleaGame& game) {
  last_action_performed = game.last_action_performed;
  for (const auto& elem: game.terminals) {
    terminals.insert(P2D(elem));
  }
  for (auto const& elem : game.dices) {
    Dice *dice;
    Cell c(elem.second->getPosition().getX(), elem.second->getPosition().getY());
    switch (elem.second->getActualTypeInt()){
      case 0: dice = new WhiteDice(c, elem.second->getNMoves(), elem.second->getInitialMoves()); break;
      case 1: dice = new RedDice(c, elem.second->getNMoves(), elem.second->getInitialMoves()); break;
      case 2: dice = new YellowDice(c, elem.second->getNMoves(), elem.second->getInitialMoves()); break;
      case 3: dice = new GreenDice(c, elem.second->getNMoves(), elem.second->getInitialMoves()); break;
    }
    dices.insert(pair<P2D, Dice *>(P2D(elem.first), dice));
  }
}

AleaGame::AleaGame(json json_dict, bool isBackward) {
  if(isBackward)
    generateMapForBackwardMovements(json_dict);
  else
    generateMapForForwardMovements(json_dict);
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

  if(!is_valid_ending_configuration()){
    cout << "\n\nPlease insert a valid Final Configuration of the Map.\nMismatches between Dices and Terminals positions.\n\n\n";
    exit(1);
  }
  
  cout << "\n===== Alea Level Solver Backward =====" << endl;
	cout << "           MAP_WIDTH : " << MAP_WIDTH << endl;
	cout << "           MAP_HEIGHT: " << MAP_HEIGHT << endl;
	cout << "           #dice : " << terminals.size() << endl;
	cout << "========================================" << endl;
	cout << endl;
}

void AleaGame::generateMapForForwardMovements(json json_dict){
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
  
  cout << "\n===== Alea Level Solver Forward =====" << endl;
	cout << "            MAP_WIDTH : " << MAP_WIDTH << endl;
	cout << "            MAP_HEIGHT: " << MAP_HEIGHT << endl;
	cout << "            #dice : " << terminals.size() << endl;
	cout << "=======================================" << endl;
	cout << endl;
}

AleaGame::operator string () {
  string s = string(3*MAP_WIDTH, ' ') + " \n";
  for (int i = 0; i < MAP_HEIGHT; ++i) {
    for (int j = 0; j < MAP_WIDTH; ++j) {
      P2D pos = P2D(j, i);
      string d = dices.find(pos) == dices.end() ? BGGRAY : (string) *(dices[pos]);
      s += terminals.find(pos) == terminals.end() ? " " + d + " " :  "[" + d + "]";
    }
    s += "\n" + string(3*MAP_WIDTH, ' ') + " \n";
  }
  return s;
}

size_t AleaGame::HashFun::operator()(const AleaGame& game) const {
    int type_map[] = {17, 31, 47, 97};
    size_t the_hash = 0;
    for (const P2D& t : game.terminals) the_hash += P2D::HashFun()(t);
    for (const auto &pair : game.dices) {
        the_hash += P2D::HashFun()(pair.first) * type_map[pair.second->getActualTypeInt()] * pair.second->getNMoves()+1;
        the_hash ^= (int) pow(type_map[pair.second->getActualTypeInt()], pair.second->getNMoves()+1);
    }
    return the_hash;
}

bool AleaGame::operator==(const AleaGame& other) const {
  for (const auto& elem: other.terminals) {
    if (!is_terminal(elem)) return false;
  }
  for (auto const& elem : other.dices) {
    if (!has_dice(elem.first)) return false;
    if (dices.find(elem.first)->second != elem.second) return false;
  }
  return true;
}

ostream& operator<<(ostream& out, AleaGame game) {
  return out << (string) game;
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
		cout << "ERROR: Unable to open file '" << filename << "'." << endl;
		exit(1);
	}
	return json_text;
}

void AleaGame::print(const bool& color) {
  if (color) {
    cout << *this << endl;
    return;
  }
  string s = "";
  for (int i = 0; i < MAP_HEIGHT; i++) {
    for (int j = 0; j < MAP_WIDTH; j++) {
      P2D pos = P2D(j, i);
      string d = "    ";
      if (dices.find(pos) != dices.end()) {
        if(dices[pos]->getActualType().compare("WhiteDice") == 0) d = "W";
        else if(dices[pos]->getActualType().compare("RedDice") == 0) d = "R";
        else if(dices[pos]->getActualType().compare("YellowDice") == 0) d = "Y";
        else if(dices[pos]->getActualType().compare("GreenDice") == 0) d = "G";
        d += "(" + to_string(dices[pos]->getNMoves()) + ")";
      } 
      s += terminals.find(pos) == terminals.end() ? "." + d + "." :  "[" + d + "]";
    }
    s += "\n";
  }
  cout << s << endl;
}

int AleaGame::remaining_moves() const {
  int tot = 0;
  for (auto const& pair: dices) {
    tot += pair.second->getNMoves();
  }
  return tot;
}

vector<Action> AleaGame::possible_moves() {
  vector<Action> moves;
  for (auto const& pair: dices) {
    Dice *dice = pair.second;
    if(dice->getNMoves() > 0){
      if(dice->getActualType().compare("GreenDice") == 0)
        green_dice_possible_moves(dice, moves);
      else if(dice->getActualType().compare("WhiteDice") == 0)
        white_dice_possible_moves(dice, moves);
      else if(dice->getActualType().compare("RedDice") == 0)
        red_dice_possible_moves(dice, moves);
      else if(dice->getActualType().compare("YellowDice") == 0)
        yellow_dice_possible_moves(dice, moves);
    }
  }
  return moves;
}

void AleaGame::yellow_dice_possible_moves(Dice *dice, vector<Action> &moves){
  int x = dice->getPosition().getX(), y = dice->getPosition().getY();
  vector<Cell> cells;
  if(x>0) cells.push_back(Cell(x-1, y));
  if(x<MAP_WIDTH-1) cells.push_back(Cell(x+1, y));
  if(y>0) cells.push_back(Cell(x, y-1));
  if(y<MAP_HEIGHT-1) cells.push_back(Cell(x, y+1));
  for(Cell c : cells){
    pair<bool, int> res = NO_MOVE;
    if(c.getX() == x-1 && last_action_performed.dir != P2D::DX && last_action_performed.dir != P2D::JUMPING_DX){
      res = dice->reverseMove("sx", dices, __func__, 1);
      if(res.first){
        if(res.second == 1) 
          moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::SX, SIMPLE_MOVE, 0, P2D::cellToP2D(Cell(x, y))+P2D::SX)); 
        else if(res.second == 2 && dices.find(P2D::cellToP2D(Cell(x-2, y))) == dices.end())
          moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::cellToP2D(Cell(-2, 0)), JUMPING_MOVE, 2, P2D::cellToP2D(Cell(x-2, y)))); 
        else
          moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::SX, PUSHED_MOVE, 1, P2D::cellToP2D(Cell(x-(res.second+1), y))));
      }      
    }
    if(c.getX() == x+1 && last_action_performed.dir != P2D::SX && last_action_performed.dir != P2D::JUMPING_SX){
      res = dice->reverseMove("dx", dices, __func__, 1);
      if(res.first){
        if(res.second == 1) 
          moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::DX, SIMPLE_MOVE, 0, P2D::cellToP2D(Cell(x, y))+P2D::DX)); 
        else if(res.second == 2 && dices.find(P2D::cellToP2D(Cell(x+2, y))) == dices.end())
          moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::cellToP2D(Cell(2, 0)), JUMPING_MOVE, 2, P2D::cellToP2D(Cell(x+2, y)))); 
        else
          moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::DX, PUSHED_MOVE, 1, P2D::cellToP2D(Cell(x+(res.second+1), y))));
      }      
    }
    if(c.getY() == y-1  && last_action_performed.dir != P2D::DOWN  && last_action_performed.dir != P2D::JUMPING_DOWN){
      res = dice->reverseMove("up", dices, __func__, 1);
      if(res.first){
        if(res.second == 1) 
          moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::UP, SIMPLE_MOVE, 0, P2D::cellToP2D(Cell(x, y))+P2D::UP)); 
        else if(res.second == 2 && dices.find(P2D::cellToP2D(Cell(x, y-2))) == dices.end())
          moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::cellToP2D(Cell(0, -2)), JUMPING_MOVE, 2, P2D::cellToP2D(Cell(x, y-2)))); 
        else
          moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::UP, PUSHED_MOVE, 1, P2D::cellToP2D(Cell(x, y-(res.second+1)))));
      }      
    }
    if(c.getY() == y+1  && last_action_performed.dir != P2D::UP && last_action_performed.dir != P2D::JUMPING_UP){
      res = dice->reverseMove("down", dices, __func__, 1);
      if(res.first){
        if(res.second == 1) 
          moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::DOWN, SIMPLE_MOVE, 0, P2D::cellToP2D(Cell(x, y))+P2D::DOWN)); 
        else if(res.second == 2 && dices.find(P2D::cellToP2D(Cell(x, y+2))) == dices.end())
          moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::cellToP2D(Cell(0, 2)), JUMPING_MOVE, 2, P2D::cellToP2D(Cell(x, y+2)))); 
        else
          moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::DOWN, PUSHED_MOVE, 1, P2D::cellToP2D(Cell(x, y+(res.second+1)))));
      }      
    }
  }
}

void AleaGame::red_dice_possible_moves(Dice *dice, vector<Action> &moves){
  int x = dice->getPosition().getX(), y = dice->getPosition().getY();
  vector<Cell> cells;
  if(x>0) cells.push_back(Cell(x-1, y));
  if(x<MAP_WIDTH-1) cells.push_back(Cell(x+1, y));
  if(y>0) cells.push_back(Cell(x, y-1));
  if(y<MAP_HEIGHT-1) cells.push_back(Cell(x, y+1));
  for(Cell c : cells){
    pair<bool, int> res = NO_MOVE;
    if(c.getX() == x-1  && last_action_performed.dir != P2D::DX){
      res = dice->reverseMove("sx", dices, __func__, 1);
      if(res.first) moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::SX, SIMPLE_MOVE, 0, P2D::cellToP2D(Cell(x, y))+P2D::SX));      
    }
    if(c.getX() == x+1 && last_action_performed.dir != P2D::SX){
      res = dice->reverseMove("dx", dices, __func__, 1);
      if(res.first) moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::DX, SIMPLE_MOVE, 0, P2D::cellToP2D(Cell(x, y))+P2D::DX));      
    }
    if(c.getY() == y-1 && last_action_performed.dir != P2D::DOWN){
      res = dice->reverseMove("up", dices, __func__, 1);
      if(res.first) moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::UP, SIMPLE_MOVE, 0, P2D::cellToP2D(Cell(x, y))+P2D::UP));      
    }
    if(c.getY() == y+1 && last_action_performed.dir != P2D::UP){
      res = dice->reverseMove("down", dices, __func__, 1);
      if(res.first) moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::DOWN, SIMPLE_MOVE, 0, P2D::cellToP2D(Cell(x, y))+P2D::DOWN));      
    }
  }
}

void AleaGame::white_dice_possible_moves(Dice *dice, vector<Action> &moves){
  int x = dice->getPosition().getX(), y = dice->getPosition().getY();
  vector<Cell> cells;
  if(x>0) cells.push_back(Cell(x-1, y));
  if(x<MAP_WIDTH-1) cells.push_back(Cell(x+1, y));
  if(y>0) cells.push_back(Cell(x, y-1));
  if(y<MAP_HEIGHT-1) cells.push_back(Cell(x, y+1));
  for(Cell c : cells){
    pair<bool, int> res = NO_MOVE;
    if(c.getX() == x-1 && last_action_performed.dir != P2D::DX){
      res = dice->reverseMove("sx", dices, __func__, true);
      if(res.first){
        if(dices.find(P2D::cellToP2D(c)) == dices.end())
          moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::SX, SIMPLE_MOVE, 0, P2D::cellToP2D(Cell(x, y))+P2D::SX));
        else
          moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::SX, PUSHED_MOVE, 1, P2D::cellToP2D(Cell(x-res.second, y))));       
      }
    }
    if(c.getX() == x+1 && last_action_performed.dir != P2D::SX){
      res = dice->reverseMove("dx", dices, __func__, 1);
      if(res.first){
        if(dices.find(P2D::cellToP2D(c)) == dices.end())
          moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::DX, SIMPLE_MOVE, 0, P2D::cellToP2D(Cell(x, y))+P2D::DX));
        else
          moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::DX, PUSHED_MOVE, 1, P2D::cellToP2D(Cell(x+res.second, y))));           
      }
    }
    if(c.getY() == y-1 && last_action_performed.dir != P2D::DOWN){
      res = dice->reverseMove("up", dices, __func__, 1);
      if(res.first){
        if(dices.find(P2D::cellToP2D(c)) == dices.end())
          moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::UP, SIMPLE_MOVE, 0, P2D::cellToP2D(Cell(x, y))+P2D::UP));
        else
          moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::UP, PUSHED_MOVE, 1, P2D::cellToP2D(Cell(x, y-res.second))));         
      }
    }
    if(c.getY() == y+1 && last_action_performed.dir != P2D::UP){
      res = dice->reverseMove("down", dices, __func__, 1);
      if(res.first){
        if(dices.find(P2D::cellToP2D(c)) == dices.end())
          moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::DOWN, SIMPLE_MOVE, 0, P2D::cellToP2D(Cell(x, y))+P2D::DOWN));
        else
          moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::DOWN, PUSHED_MOVE, 1, P2D::cellToP2D(Cell(x, y+res.second))));       
      }
    }
  }
}

void AleaGame::green_dice_possible_moves(Dice *dice, vector<Action> &moves){
  if(dice->getNMoves() > 0){
    green_dice_possible_moves_nMoves_gt_zero(dice, moves);
    green_dice_possible_moves_being_pushed(dice, moves);  
  }else
    green_dice_possible_moves_being_pushed(dice, moves);  
}

void AleaGame::green_dice_possible_moves_nMoves_gt_zero(Dice *dice, vector<Action> &moves){
  int x = dice->getPosition().getX(), y = dice->getPosition().getY();
  vector<Cell> cells;
  if(x>0) cells.push_back(Cell(x-1, y));
  if(x<MAP_WIDTH-1) cells.push_back(Cell(x+1, y));
  if(y>0) cells.push_back(Cell(x, y-1));
  if(y<MAP_HEIGHT-1) cells.push_back(Cell(x, y+1));
  for(Cell c : cells){
    if(dices.find(P2D::cellToP2D(c)) != dices.end() || x == 0 || y == 0 || x == MAP_WIDTH-1 || y == MAP_HEIGHT-1){ //busy cell or boundary cell
      pair<bool, int> res = NO_MOVE;
      if((c.getX() == x-1 || x == 0) && last_action_performed.dir != P2D::SX){ // left one occupied/boundary, then could move right
        res = dice->reverseMove("dx", dices, __func__, true, 0);
        if(res.first){
          int i = 1;
          while(i <= res.second){
            moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::cellToP2D(Cell(i, 0)), SIMPLE_MOVE*i, 0, P2D::cellToP2D(Cell(x+i, y))));
            i++;
          }
        }
      }
      if((c.getX() == x+1 || x == MAP_WIDTH-1) && last_action_performed.dir != P2D::DX){ //right one occupied/boundary, then could move left 
        res = dice->reverseMove("sx", dices, __func__, true, 0);
        if(res.first){
          int i = 1;
          while(i <= res.second){
            moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::cellToP2D(Cell((-1*i), 0)), SIMPLE_MOVE*i, 0, P2D::cellToP2D(Cell(x-i, y))));
            i++;
          }
        }
      }
      if((c.getY() == y+1 || y == MAP_HEIGHT-1) && last_action_performed.dir != P2D::DOWN){ //down one occupied/boundary, then could move up 
        res = dice->reverseMove("up", dices, __func__, true, 0);
        if(res.first){
          int i = 1;
          while(i <= res.second){
            moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::cellToP2D(Cell(0, (-1*i))), SIMPLE_MOVE*i, 0, P2D::cellToP2D(Cell(x, y-i))));
            i++;
          }
        }
      }
      if((c.getY() == y-1 || y == 0) && last_action_performed.dir != P2D::UP){ //up one occupied, then could move down 
        res = dice->reverseMove("down", dices, __func__, true, 0);
        if(res.first){
          int i = 1;
          while(i <= res.second){
            moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::cellToP2D(Cell(0, i)), SIMPLE_MOVE*i, 0, P2D::cellToP2D(Cell(x, y+i))));
            i++;
          }
        }
      }
    }
  }
}

void AleaGame::green_dice_possible_moves_being_pushed(Dice *dice, vector<Action> &moves){
  int x = dice->getPosition().getX(), y = dice->getPosition().getY();

  if(x>0 && last_action_performed.dir != P2D::DX){ //check if can have been pushed from left
    pair<bool, int> res = dices.at(P2D(x,y))->reverseMove("sx", dices, __func__, true, 1);
    if(res.first)
      moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::SX, PUSHED_MOVE*res.second, 1, P2D::cellToP2D(Cell(x-res.second, y))));
  }
  if(x+1<MAP_WIDTH && last_action_performed.dir != P2D::SX){ //check if can have been pushed from right
    pair<bool, int> res = dices.at(P2D(x,y))->reverseMove("dx", dices, __func__, true, 1);
    if(res.first)
      moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::DX, PUSHED_MOVE*res.second, 1, P2D::cellToP2D(Cell(x+res.second, y)))); 
  }
  if(y>0 && last_action_performed.dir != P2D::DOWN){ //check if can have been pushed from up
    pair<bool, int> res = dices.at(P2D(x,y))->reverseMove("up", dices, __func__, true, 1);
    if(res.first)
      moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::UP, PUSHED_MOVE*res.second, 1, P2D::cellToP2D(Cell(x, y-res.second))));
  }
  if(y+1<MAP_HEIGHT && last_action_performed.dir != P2D::UP){ //check if can have been pushed from down
    pair<bool, int> res = dices.at(P2D(x,y))->reverseMove("down", dices, __func__, true, 1);
    if(res.first)
      moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::DOWN, PUSHED_MOVE*res.second, 1, P2D::cellToP2D(Cell(x, y+res.second))));
  }
}

bool AleaGame::move(const Action& action, bool isMovingBackward) {
  return move(action.from, action.dir, action.movementType, isMovingBackward);
}

bool AleaGame::move(const P2D pos, const P2D dir, const int movementType, bool isMovingBackward) {
  Dice *dice = dices[pos];
  if(isMovingBackward){
    if(dir.x<0)
      return dice->reverseMove("sx", dices, __func__, false, movementType).first;
    else if(dir.x>0)
      return dice->reverseMove("dx", dices, __func__, false, movementType).first;
    else if(dir.y>0)
      return dice->reverseMove("down", dices, __func__, false, movementType).first;
    else if(dir.y<0)
      return dice->reverseMove("up", dices, __func__, false, movementType).first;
  }else{
    if(dir.x<0)
      return dice->move("sx", dices, __func__, false);
    else if(dir.x>0)
      return dice->move("dx", dices, __func__, false);
    else if(dir.y>0)
      return dice->move("down", dices, __func__, false);
    else if(dir.y<0)
      return dice->move("up", dices, __func__, false);
  }
  return false;
}

bool AleaGame::is_valid_starting_configuration() {
  for(auto pair: dices) {
    if (pair.second->getNMoves() > 0)
      return false;
  }
  return true;
}

bool AleaGame::is_valid_ending_configuration() {
  for(auto const& dice: dices) {
    if (!is_terminal(dice.first)) return false;
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
  return Action(backward_action.head, P2D(backward_action.dir.x*-1, backward_action.dir.y*-1), backward_action.weight);
}

void AleaGame::show_map(){
  cout << "\n";
  for(auto d : dices){
    cout << d.second->getActualType() << ": (" << d.second->getPosition().getX() << ", " << d.second->getPosition().getY() << ")\n";
  }
  cout << "\n";
}

void AleaGame::show_moves(vector<Action> moves){
  for(auto m : moves)
    cout << "\nfrom: " << m.from << " | dir: " << m.dir << "\n";
}