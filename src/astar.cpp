#include "astar.h"
#include <string>
#include <iomanip>
#include <fstream>

AStarNode::AStarNode(AleaGame game) : game(game) { }
AStarNode::AStarNode(AleaGame game, Action action) : game(game), action(action) { }
AStarNode::AStarNode(AleaGame game, double g) : game(game), g(g) { }
AStarNode::AStarNode(AleaGame game, double g, double h) : game(game), g(g), h(h) { f = g + h; }
AStarNode::AStarNode(AleaGame game, Action action, AStarNode* parent) : game(game), action(action), parent(parent) { }
AStarNode::AStarNode(AleaGame game, Action action, AStarNode* parent, double g, double h) : game(game), action(action), parent(parent), g(g), h(h) { 
  f = g + h;
}

bool AStarNode::operator==(const AStarNode& other) const {
  return this->game == other.game;
}

bool AStarNode::operator<(const AStarNode& other) const {
  return f < other.f;
}

bool AStarNode::CompareFunBackward::operator() (AStarNode* n1, AStarNode* n2) {
  return n1->f < n2->f; //ordering priority queue as a max-heap
}

bool AStarNode::CompareFunForward::operator() (AStarNode* n1, AStarNode* n2) {
  return n1->f > n2->f; //ordering priority queue as a min-heap
}

size_t AStarNode::HashFun::operator()(AStarNode* const&n) const{
  return AleaGame::HashFun()(n->game);
}

bool AStarNode::CompareFunSolutionsForward:: operator() (pair<vector<Action>, double> solution1, pair<vector<Action>, double> solution2){
  return solution1.second > solution2.second; //ordering priority queue as a min-heap
}

pair<string, vector<Action>> AStarNode::astar_backward_search(AleaGame game, int limit) {
  pair<string, vector<Action>> res;
  priority_queue<AStarNode*, vector<AStarNode*>, AStarNode::CompareFunBackward> open;
  unordered_set<AStarNode*, AStarNode::HashFun> open_set;
  unordered_set<AleaGame, AleaGame::HashFun> closed;
  AStarNode* start_node = new AStarNode(game, 0);
  open.push(start_node);
  open_set.insert(start_node);
  int evaluated_moves = 0;
  int skipped_moves = 0;
  int branched_nodes = 0;
  while (open.size() > 0) {
    ++branched_nodes;
    AStarNode* current_node = open.top();
    open.pop();
    open_set.erase(current_node);
    closed.insert(current_node->game);
    if (current_node->game.is_valid_starting_configuration_backward_search()) {
      current_node->game.print(true);
      res.first = printLevel(current_node->game, current_node->f);
      while (current_node->parent != NULL) {
        res.second.push_back(AleaGame::revert_action(current_node->action));
        current_node = current_node->parent;
      }      
      break;
    }
    vector<Action> actions = current_node->game.possible_moves_backward();
    for (Action action : actions) {
      AleaGame new_game = AleaGame(current_node->game);
      if(!new_game.move(action, true)){
        cout<<"\nastar.cpp:astar_backward_search: Error while moving from: "<<action.from<<", dir: "<<action.dir<<", type:"<<action.movementType<<", head:"<<action.head<<"\nExiting.\n"; 
        exit(1);
      }
      new_game.last_action_performed = action;
      if (closed.find(new_game) != closed.end()) {
        ++skipped_moves;
        continue;
      }
      ++evaluated_moves;
      AStarNode* neighbor = new AStarNode(new_game, action, current_node, current_node->f, action.weight); //(double)value
      if (open_set.find(neighbor) == open_set.end()) {
        open.push(neighbor);
        open_set.insert(neighbor);
      }
    }
    if (branched_nodes > limit){
      cout << "\n\nBRANCHED_NODES LIMIT REACHED. EXIT\n\n";
      break;
    }
  }
  cout << "Evaluated:" << evaluated_moves << endl;
  cout << "Skipped:"<< skipped_moves << endl;
  cout << "Branched:"<< branched_nodes << endl;
  return res;
}

//BANAL: means the terminal-dice distance is equal to nMoves and the terminal is not disputed between 2 or more dices
pair<bool, pair<AleaGame, vector<Action>>> AStarNode::find_banal_start_forward_search(AleaGame original_start){
  pair<bool, pair<AleaGame, vector<Action>>> res;
  res.first = false;
  res.second.first = original_start;
  for(pair<P2D, Dice*> pair : original_start.dices){
    vector<Action> dice_moves;
    Dice *dice = pair.second;
    P2D dice_position = pair.first;
    for(P2D terminal : original_start.terminals){
      if(dice_position.manatthan(terminal) == dice->getNMoves() && !terminal_is_disputed(terminal, original_start.dices)){
        if(find_banal_start_calculate_route(dice_moves, dice_position, dice->getNMoves(), terminal, res.second.first.dices)){
          for(Action action : dice_moves){
            res.second.first.move(action, false);
            res.second.second.push_back(action);
          }
          res.first = true;
          continue;
        }
      } 
    }
  }
  return res;
}

bool AStarNode::terminal_is_disputed(P2D terminal_position, unordered_map<P2D, Dice *, P2D::HashFun> dices){
  int counter = 0;
  for(pair<P2D, Dice*> pair : dices){
    if(pair.first.manatthan(terminal_position) == pair.second->getNMoves())
      counter++;
  }
  if(counter>1) 
    return true;
  return false;
}

bool AStarNode::find_banal_start_calculate_route(vector<Action> &moves, P2D dice_position, int dice_moves, P2D terminal_position, unordered_map<P2D, Dice *, P2D::HashFun> dices){
  if(dice_moves==0){
    if(dice_position.x == terminal_position.x && dice_position.y == terminal_position.y)
      return true;
    else
      return false;
  }  
  
  if(dice_position.x < terminal_position.x){//moving dx
    if(dices.find(dice_position) != dices.end() && dices.at(dice_position)->getActualType().compare("GreenDice") == 0){
      int i = 1;
      while(dice_moves-(i-1) > 0 && (dices.find(dice_position+P2D(i, 0)) == dices.end() && dice_position.x+i < MAP_WIDTH))
        i++;
      moves.push_back(Action(dice_position, P2D::DX, SIMPLE_MOVE_FORWARD+(dice_position+P2D(i-1, 0)).manatthan(terminal_position)/100, 0));
      return find_banal_start_calculate_route(moves, dice_position+P2D(i-1, 0), dice_moves-(i-1), terminal_position, dices);
    }else{
      if(dices.find(dice_position+P2D::DX) == dices.end()){
        moves.push_back(Action(dice_position, P2D::DX, SIMPLE_MOVE_FORWARD+(dice_position+P2D::DX).manatthan(terminal_position)/100, 0));
        return find_banal_start_calculate_route(moves, dice_position+P2D::DX, dice_moves-1, terminal_position, dices);
      }else{
        if(dices.find(dice_position+P2D::UP) == dices.end() && (dice_position+P2D::UP).y >= 0){ 
          moves.push_back(Action(dice_position, P2D::UP, SIMPLE_MOVE_FORWARD+(dice_position+P2D::UP).manatthan(terminal_position)/100, 0));
          return find_banal_start_calculate_route(moves, dice_position+P2D::UP, dice_moves-1, terminal_position, dices);
        }else if(dices.find(dice_position+P2D::DOWN) == dices.end() && (dice_position+P2D::DOWN).y < MAP_HEIGHT){
          moves.push_back(Action(dice_position, P2D::DOWN, SIMPLE_MOVE_FORWARD+(dice_position+P2D::DOWN).manatthan(terminal_position)/100, 0));
          return find_banal_start_calculate_route(moves, dice_position+P2D::DOWN, dice_moves-1, terminal_position, dices);
        }else
          return false;
      }
    }
  }
  else if(dice_position.x > terminal_position.x){//moving sx
    if(dices.find(dice_position) != dices.end() && dices.at(dice_position)->getActualType().compare("GreenDice") == 0){
      int i = 1;
      while(dice_moves-(i-1) > 0 && (dices.find(dice_position+P2D(-i, 0)) == dices.end() && dice_position.x-i >= 0))
        i++;
      moves.push_back(Action(dice_position, P2D::SX, SIMPLE_MOVE_FORWARD+(dice_position+P2D(-(i-1), 0)).manatthan(terminal_position)/100, 0));
      return find_banal_start_calculate_route(moves, dice_position+P2D(-(i-1), 0), dice_moves-(i-1), terminal_position, dices);
    }else{
      if(dices.find(dice_position+P2D::SX) == dices.end()){
        moves.push_back(Action(dice_position, P2D::SX, SIMPLE_MOVE_FORWARD+(dice_position+P2D::SX).manatthan(terminal_position)/100, 0));
        return find_banal_start_calculate_route(moves, dice_position+P2D::SX, dice_moves-1, terminal_position, dices);
      }else{
        if(dices.find(dice_position+P2D::UP) == dices.end() && (dice_position+P2D::UP).y >= 0){ 
          moves.push_back(Action(dice_position, P2D::UP, SIMPLE_MOVE_FORWARD+(dice_position+P2D::UP).manatthan(terminal_position)/100, 0));
          return find_banal_start_calculate_route(moves, dice_position+P2D::UP, dice_moves-1, terminal_position, dices);
        }else if(dices.find(dice_position+P2D::DOWN) == dices.end() && (dice_position+P2D::DOWN).y < MAP_HEIGHT){
          moves.push_back(Action(dice_position, P2D::DOWN, SIMPLE_MOVE_FORWARD+(dice_position+P2D::DOWN).manatthan(terminal_position)/100, 0));
          return find_banal_start_calculate_route(moves, dice_position+P2D::DOWN, dice_moves-1, terminal_position, dices);
        }else
          return false;
      }
    }
  }
  else if(dice_position.y > terminal_position.y){//moving up
    if(dices.find(dice_position) != dices.end() && dices.at(dice_position)->getActualType().compare("GreenDice") == 0){
      int i = 1;
      while(dice_moves-(i-1) > 0 && (dices.find(dice_position+P2D(0, -i)) == dices.end() && dice_position.y-i >= 0))
        i++;
      moves.push_back(Action(dice_position, P2D::UP, SIMPLE_MOVE_FORWARD+(dice_position+P2D(0, -(i-1))).manatthan(terminal_position)/100, 0));
      return find_banal_start_calculate_route(moves, dice_position+P2D(0, -(i-1)), dice_moves-(i-1), terminal_position, dices);
    }else{
      if(dices.find(dice_position+P2D::UP) == dices.end()){
        moves.push_back(Action(dice_position, P2D::UP, SIMPLE_MOVE_FORWARD+(dice_position+P2D::UP).manatthan(terminal_position)/100, 0));
        return find_banal_start_calculate_route(moves, dice_position+P2D::UP, dice_moves-1, terminal_position, dices);
      }else{
        if(dices.find(dice_position+P2D::SX) == dices.end() && (dice_position+P2D::SX).x >= 0){ 
          moves.push_back(Action(dice_position, P2D::SX, SIMPLE_MOVE_FORWARD+(dice_position+P2D::SX).manatthan(terminal_position)/100, 0));
          return find_banal_start_calculate_route(moves, dice_position+P2D::SX, dice_moves-1, terminal_position, dices);
        }else if(dices.find(dice_position+P2D::DX) == dices.end() && (dice_position+P2D::DX).x < MAP_WIDTH){
          moves.push_back(Action(dice_position, P2D::DX, SIMPLE_MOVE_FORWARD+(dice_position+P2D::DX).manatthan(terminal_position)/100, 0));
          return find_banal_start_calculate_route(moves, dice_position+P2D::DX, dice_moves-1, terminal_position, dices);
        }else
          return false;
      }
    }
  }
  else if(dice_position.y < terminal_position.y){//moving down
    if(dices.find(dice_position) != dices.end() && dices.at(dice_position)->getActualType().compare("GreenDice") == 0){
      int i = 1;
      while(dice_moves-(i-1) > 0 && (dices.find(dice_position+P2D(0, i)) == dices.end() && dice_position.y+i < MAP_HEIGHT))
        i++;
      moves.push_back(Action(dice_position, P2D::DOWN, SIMPLE_MOVE_FORWARD+(dice_position+P2D(0, i-1)).manatthan(terminal_position)/100, 0));
      return find_banal_start_calculate_route(moves, dice_position+P2D(0, i-1), dice_moves-(i-1), terminal_position, dices);
    }else{
      if(dices.find(dice_position+P2D::DOWN) == dices.end()){
        moves.push_back(Action(dice_position, P2D::DOWN, SIMPLE_MOVE_FORWARD+(dice_position+P2D::DOWN).manatthan(terminal_position)/100, 0));
        return find_banal_start_calculate_route(moves, dice_position+P2D::DOWN, dice_moves-1, terminal_position, dices);
      }else{
        if(dices.find(dice_position+P2D::SX) == dices.end() && (dice_position+P2D::SX).x >= 0){ 
          moves.push_back(Action(dice_position, P2D::SX, SIMPLE_MOVE_FORWARD+(dice_position+P2D::SX).manatthan(terminal_position)/100, 0));
          return find_banal_start_calculate_route(moves, dice_position+P2D::SX, dice_moves-1, terminal_position, dices);
        }else if(dices.find(dice_position+P2D::DX) == dices.end() && (dice_position+P2D::DX).x < MAP_WIDTH){
          moves.push_back(Action(dice_position, P2D::DX, SIMPLE_MOVE_FORWARD+(dice_position+P2D::DX).manatthan(terminal_position)/100, 0));
          return find_banal_start_calculate_route(moves, dice_position+P2D::DX, dice_moves-1, terminal_position, dices);
        }else
          return false;
      }
    }
  }
  
  return false;
}

priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, AStarNode::CompareFunSolutionsForward> AStarNode::astar_forward_search(AleaGame game, int limit) {
  priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, AStarNode::CompareFunSolutionsForward> res;
  priority_queue<AStarNode*, vector<AStarNode*>, AStarNode::CompareFunForward> open;
  unordered_set<AStarNode*, AStarNode::HashFun> open_set;
  unordered_set<AleaGame, AleaGame::HashFun> closed;
  double difficulty = 0.00;
  bool banal_solution_found = false;
  pair<bool, pair<AleaGame, vector<Action>>> banal_search = find_banal_start_forward_search(game);
  if(banal_search.first){
    game = banal_search.second.first;
    cout<<"Banal Starting Configuration Found.\n";
    for(Action move : banal_search.second.second){
      difficulty += move.weight;
      cout<<move<<endl;
    }
    if(game.is_valid_ending_configuration_forward_search())
      res.push(make_pair(banal_search.second.second, difficulty));
  }
  banal_solution_found = banal_search.first;
  AStarNode* start_node = new AStarNode(game, difficulty, 0.00);
  open.push(start_node);
  open_set.insert(start_node);
  int evaluated_moves = 0;
  int skipped_moves = 0;
  int branched_nodes = 0;
  while (open.size() > 0) {
    ++branched_nodes;
    AStarNode* current_node = open.top();
    open.pop();
    open_set.erase(current_node);
    closed.insert(current_node->game);
    if(banal_solution_found) banal_solution_found = false;
    else{
      if (current_node->game.is_valid_ending_configuration_forward_search()){
        pair<vector<Action>, double> solution;
        while (current_node->parent != NULL) {
          solution.first.push_back(current_node->action);
          solution.second += current_node->f;
          current_node = current_node->parent;
        }
        reverse(solution.first.begin(), solution.first.end());
        if(banal_search.first){
          int offset = 0;
          for(Action move : banal_search.second.second){
            solution.first.insert(solution.first.begin()+offset, move);
            solution.second += move.weight;
            offset++;
          }
        }
        cout<<"\nAStar Forward: New Solution Found!\n";
        res.push(solution);
        continue;
      }
    }
    vector<Action> actions = current_node->game.possible_moves_forward();
    for (Action action : actions) {
      //cout<<action<<endl;
      AleaGame new_game = AleaGame(current_node->game);
      if(!new_game.move(action, false)){
        cout<<"\nastar.cpp:astar_forward_search: Error while moving from: "<<action.from<<", dir: "<<action.dir<<", type:"<<action.movementType<<", head:"<<action.head<<"\nExiting.\n"; 
        exit(1);
      }
      if (closed.find(new_game) != closed.end()) {
        ++skipped_moves;
        continue;
      }
      ++evaluated_moves;
      AStarNode* neighbor = new AStarNode(new_game, action, current_node, current_node->f, action.weight); 
      if (open_set.find(neighbor) == open_set.end()) {
        open.push(neighbor);
        open_set.insert(neighbor);
      }
    }
    //current_node->game.show_map();
    //char ch;
    //cin>>ch;
    if (branched_nodes > limit){
      cout << "\n\nBRANCHED_NODES LIMIT REACHED. EXIT\n\n";
      break;
    }
    //if(branched_nodes % 500)
      //cout << branched_nodes;
  }
  /*cout << "Evaluated:" << evaluated_moves << endl;
  cout << "Dead:"<< dead_positions << endl;
  cout << "Skipped:"<< skipped_moves << endl;
  cout << "Branched:"<< branched_nodes << endl;*/
  return res;
}

string AStarNode::printLevel(AleaGame map_configuration, double difficulty){
  json level, dice, terminal;
  level["columns"] = MAP_WIDTH;
  level["rows"] = MAP_HEIGHT;

  if(map_configuration.terminals.size() == 0 || map_configuration.dices.size() == 0){
    cout << "\n\nError while generating level. #terminals or #dices equals to zero.\n\n\n";
    exit(1);
  }

  for(P2D t : map_configuration.terminals){
    terminal["x"] = t.x;
    terminal["y"] = t.y;
    level["terminals"].push_back(terminal);
  }

  for(pair<P2D, Dice *> d : map_configuration.dices){
    dice["num"] = d.second->getInitialMoves();
    dice["type"] = d.second->getActualTypeInt(); 
    dice["x"] = d.second->getPosition().getX();
    dice["y"] = d.second->getPosition().getY();
    level["dice"].push_back(dice);
  }
  level["difficulty"] = difficulty;
  char to_print[30];
  sprintf(to_print, "%4.2f", difficulty);
  ofstream o("generated_levels/level_" + string(to_print) + "_" + to_string(time(nullptr)) + ".json");
	o << setw(4) << level << endl;
  return "generated_levels/level_" + string(to_print) + "_" + to_string(time(nullptr)) + ".json";
}
