#include "alea_game.h"

AleaGame::AleaGame(const char *filename) : AleaGame(json::parse(read_json(filename))) { }

AleaGame::AleaGame(string filename) : AleaGame(json::parse(read_json(filename))) { }

AleaGame::AleaGame(json json_dict) {
  int cols = json_dict["columns"];
  int max_row = 0;

  for (auto& e : json_dict["terminals"].items()) {
    terminals.insert(P2D((int)e.value() % cols + 1, (int)e.value() / cols + 1));
    max_row = MAX((int)e.value() / cols + 1, max_row);
  }

  for (auto& e : json_dict["dice"].items()) {
    json dice_j = e.value();
    int pos = dice_j["pos"];
    int y = pos / cols, x = pos % cols;
    max_row = MAX(y + 1, max_row);
    Dice *dice;
    Cell c(x, y);
    switch ((int)dice_j["type"]){
      case 0: dice = new WhiteDice(c, dice_j["num"]); break;
      case 1: dice = new RedDice(c, dice_j["num"]); break;
      case 2: dice = new YellowDice(c, dice_j["num"]); break;
      case 3: dice = new GreenDice(c, dice_j["num"]); break;
    }
    dices.insert(pair<P2D, Dice *>(P2D(x + 1, y + 1), dice));
  }
  width = cols + 2;
  height = max_row + 2;
  total_moves = remaining_moves();

  if(!is_valid_ending_configuration()){
    cout << "\n\nPlease insert a valid Final Configuration of the Map.\nMismatches between Dices and Terminals positions.\n\n\n";
    exit(1);
  }
  cout << "===== Alea Level Solver =====" << endl;
	cout << "        width : " << width << endl;
	cout << "        height: " << height << endl;
	cout << "        #dice : " << terminals.size() << endl;
	cout << "=============================" << endl;
	cout << endl;
}

AleaGame::operator string () {
  string s = string(3*width, ' ') + " \n";
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      P2D pos = P2D(j, i);
      string d = dices.find(pos) == dices.end() ? BGGRAY : (string) *(dices[pos]);
      s += terminals.find(pos) == terminals.end() ? " " + d + " " :  "[" + d + "]";
    }
    s += "\n" + string(3*MAP_WIDTH, ' ') + " \n";
  }
  return s;
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
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
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
    P2D pos = pair.first;
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

void AleaGame::yellow_dice_possible_moves(Dice *dice, vector<Action> moves){
  int x = dice->getPosition().getX(), y = dice->getPosition().getY();
  vector<Cell> cells;
  if(x>0) cells.push_back(Cell(x-1, y));
  if(x<width-1) cells.push_back(Cell(x+1, y));
  if(y>0) cells.push_back(Cell(x, y-1));
  if(y<height-1) cells.push_back(Cell(x, y+1));
  for(Cell c : cells){
    pair<bool, int> res = NO_MOVE;
    if(c.getX() == x-1){
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
    if(c.getX() == x+1){
      res = dice->reverseMove("dx", dices, __func__, 1);
      if(res.first){
        if(res.second == 1) 
          moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::DX, SIMPLE_MOVE, 0, P2D::cellToP2D(Cell(x, y))+P2D::DX)); 
        else if(res.second == 2 && dices.find(P2D::cellToP2D(Cell(x+2, y))) == dices.end())
          moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::cellToP2D(Cell(0, 2)), JUMPING_MOVE, 2, P2D::cellToP2D(Cell(x+2, y)))); 
        else
          moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::DX, PUSHED_MOVE, 1, P2D::cellToP2D(Cell(x+(res.second+1), y))));
      }      
    }
    if(c.getY() == y-1){
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
    if(c.getY() == y+1){
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

void AleaGame::red_dice_possible_moves(Dice *dice, vector<Action> moves){
  int x = dice->getPosition().getX(), y = dice->getPosition().getY();
  vector<Cell> cells;
  if(x>0) cells.push_back(Cell(x-1, y));
  if(x<width-1) cells.push_back(Cell(x+1, y));
  if(y>0) cells.push_back(Cell(x, y-1));
  if(y<height-1) cells.push_back(Cell(x, y+1));
  for(Cell c : cells){
    pair<bool, int> res = NO_MOVE;
    if(c.getX() == x-1){
      res = dice->reverseMove("sx", dices, __func__, 1);
      if(res.first) moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::SX, SIMPLE_MOVE, 0, P2D::cellToP2D(Cell(x, y))+P2D::SX));      
    }
    if(c.getX() == x+1){
      res = dice->reverseMove("dx", dices, __func__, 1);
      if(res.first) moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::DX, SIMPLE_MOVE, 0, P2D::cellToP2D(Cell(x, y))+P2D::DX));      
    }
    if(c.getY() == y-1){
      res = dice->reverseMove("up", dices, __func__, 1);
      if(res.first) moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::UP, SIMPLE_MOVE, 0, P2D::cellToP2D(Cell(x, y))+P2D::UP));      
    }
    if(c.getY() == y+1){
      res = dice->reverseMove("down", dices, __func__, 1);
      if(res.first) moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::DOWN, SIMPLE_MOVE, 0, P2D::cellToP2D(Cell(x, y))+P2D::DOWN));      
    }
  }
}

void AleaGame::white_dice_possible_moves(Dice *dice, vector<Action> moves){
  int x = dice->getPosition().getX(), y = dice->getPosition().getY();
  vector<Cell> cells;
  if(x>0) cells.push_back(Cell(x-1, y));
  if(x<width-1) cells.push_back(Cell(x+1, y));
  if(y>0) cells.push_back(Cell(x, y-1));
  if(y<height-1) cells.push_back(Cell(x, y+1));
  for(Cell c : cells){
    pair<bool, int> res = NO_MOVE;
    if(c.getX() == x-1){
      res = dice->reverseMove("sx", dices, __func__, 1);
      if(res.first){
        if(dices.find(P2D::cellToP2D(c)) == dices.end())
          moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::SX, SIMPLE_MOVE, 0, P2D::cellToP2D(Cell(x, y))+P2D::SX));
        else
          moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::SX, PUSHED_MOVE, 1, P2D::cellToP2D(Cell(x-(res.second+1), y))));       
      }
    }
    if(c.getX() == x+1){
      res = dice->reverseMove("dx", dices, __func__, 1);
      if(res.first){
        if(dices.find(P2D::cellToP2D(c)) == dices.end())
          moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::DX, SIMPLE_MOVE, 0, P2D::cellToP2D(Cell(x, y))+P2D::DX));
        else
          moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::DX, PUSHED_MOVE, 1, P2D::cellToP2D(Cell(x+(res.second+1), y))));           
      }
    }
    if(c.getY() == y-1){
      res = dice->reverseMove("up", dices, __func__, 1);
      if(res.first){
        if(dices.find(P2D::cellToP2D(c)) == dices.end())
          moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::UP, SIMPLE_MOVE, 0, P2D::cellToP2D(Cell(x, y))+P2D::UP));
        else
          moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::UP, PUSHED_MOVE, 1, P2D::cellToP2D(Cell(x, y-(res.second+1)))));         
      }
    }
    if(c.getY() == y+1){
      res = dice->reverseMove("down", dices, __func__, 1);
      if(res.first){
        if(dices.find(P2D::cellToP2D(c)) == dices.end())
          moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::DOWN, SIMPLE_MOVE, 0, P2D::cellToP2D(Cell(x, y))+P2D::DOWN));
        else
          moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::DOWN, PUSHED_MOVE, 1, P2D::cellToP2D(Cell(x, y+(res.second+1)))));       
      }
    }
  }
}

void AleaGame::green_dice_possible_moves(Dice *dice, vector<Action> moves){
  if(dice->getNMoves() > 0){
    green_dice_possible_moves_nMoves_gt_zero(dice, moves);
    green_dice_possible_moves_being_pushed(dice, moves);  
  }else
    green_dice_possible_moves_being_pushed(dice, moves);  
}

void AleaGame::green_dice_possible_moves_nMoves_gt_zero(Dice *dice, vector<Action> moves){
  int x = dice->getPosition().getX(), y = dice->getPosition().getY();
  vector<Cell> cells;
  if(x>0) cells.push_back(Cell(x-1, y));
  if(x<width-1) cells.push_back(Cell(x+1, y));
  if(y>0) cells.push_back(Cell(x, y-1));
  if(y<height-1) cells.push_back(Cell(x, y+1));
  for(Cell c : cells){
    if(dices.find(P2D::cellToP2D(c)) != dices.end() || x == 0 || y == 0 || x == MAP_WIDTH-1 || y == MAP_HEIGHT-1){ //busy cell or boundary cell
      pair<bool, int> res = NO_MOVE;
      if(c.getX() == x-1 || x == 0){ // left one occupied/boundary, then could move right
        res = dice->reverseMove("dx", dices, __func__, 1);
        if(res.first){
          int i = 1;
          while(i <= res.second){
            moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::cellToP2D(Cell(i, 0)), SIMPLE_MOVE*i, 0, P2D::cellToP2D(Cell(x+i, y))));
            i++;
          }
        }
      }
      if(c.getX() == x+1 || x == MAP_WIDTH-1){ //right one occupied/boundary, then could move left 
        res = dice->reverseMove("sx", dices, __func__, 1);
        if(res.first){
          int i = 1;
          while(i <= res.second){
            moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::cellToP2D(Cell((-1*i), 0)), SIMPLE_MOVE*i, 0, P2D::cellToP2D(Cell(x-i, y))));
            i++;
          }
        }
      }
      if(c.getY() == y+1 || y == MAP_HEIGHT-1){ //down one occupied/boundary, then could move up 
        res = dice->reverseMove("up", dices, __func__, 1);
        if(res.first){
          int i = 1;
          while(i <= res.second){
            moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::cellToP2D(Cell(0, (-1*i))), SIMPLE_MOVE*i, 0, P2D::cellToP2D(Cell(x, y-i))));
            i++;
          }
        }
      }
      if(c.getY() == y-1 || y == 0){ //up one occupied, then could move down 
        res = dice->reverseMove("down", dices, __func__, 1);
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

void AleaGame::green_dice_possible_moves_being_pushed(Dice *dice, vector<Action> moves){
  int x = dice->getPosition().getX(), y = dice->getPosition().getY();
  for(P2D move: {P2D::UP, P2D::DX, P2D::DOWN, P2D::SX}){
    if(x>0){ //check if can have been pushed from left
      pair<bool, int> res = dices.at(P2D::cellToP2D(Cell(x,y)))->reverseMove("sx", dices, __func__, 1, true);
      if(res.first)
        moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::SX, PUSHED_MOVE*res.second, 1, P2D::cellToP2D(Cell(x-(res.second+1), y))));
    }
    if(x+1<width){ //check if can have been pushed from right
      pair<bool, int> res = dices.at(P2D::cellToP2D(Cell(x,y)))->reverseMove("dx", dices, __func__, 1, true);
      if(res.first)
        moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::DX, PUSHED_MOVE*res.second, 1, P2D::cellToP2D(Cell(x+(res.second+1), y)))); 
    }
    if(y>0){ //check if can have been pushed from up
      pair<bool, int> res = dices.at(P2D::cellToP2D(Cell(x,y)))->reverseMove("up", dices, __func__, 1);
      if(res.first)
        moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::UP, PUSHED_MOVE*res.second, 1, P2D::cellToP2D(Cell(x, y-(res.second+1)))));
    }
    if(y+1<height){ //check if can have been pushed from down
      pair<bool, int> res = dices.at(P2D::cellToP2D(Cell(x,y)))->reverseMove("down", dices, __func__, 1);
      if(res.first)
        moves.push_back(Action(P2D::cellToP2D(Cell(x, y)), P2D::DOWN, PUSHED_MOVE*res.second, 1, P2D::cellToP2D(Cell(x, y+(res.second+1)))));
    }
  }
}

bool AleaGame::move(const Action& action) {
  return move(action.from, action.dir, action.movementType);
}

int AleaGame::move(const P2D pos, const P2D dir, const bool isPushed) {
  Dice *dice = dices[pos];
  int from_x = dice->getPosition().getX();
  int from_y = dice->getPosition().getY();
  int to_x = dir.x;
  int to_y = dir.y;
  if(from_x > to_x && from_y == to_y)
    dice->reverseMove("sx", dices, __func__, false, isPushed);
  else if(from_x < to_x && from_y == to_y)
    dice->reverseMove("dx", dices, __func__, false, isPushed);
  else if(from_x == to_x && from_y < to_y)
    dice->reverseMove("down", dices, __func__, false, isPushed);
  else if(from_x == to_x && from_y > to_y)
    dice->reverseMove("up", dices, __func__, false, isPushed);
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