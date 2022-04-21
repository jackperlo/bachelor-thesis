#include "astar.h"
#include <string>

AStarNode::AStarNode(AleaGame game) : game(game) { }
AStarNode::AStarNode(AleaGame game, Action action) : game(game), action(action) { }
AStarNode::AStarNode(AleaGame game, double g) : game(game), g(g) { }
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

bool AStarNode::CompareFun::operator() (AStarNode* n1, AStarNode* n2) {
  return n1->f > n2->f;
}

size_t AStarNode::HashFun::operator()(AStarNode* const&n) const{
  return AleaGame::HashFun()(n->game);
}

pair<string, vector<Action>> astar_backward_search(AleaGame game, int limit) {
  pair<string, vector<Action>> res;
  priority_queue<AStarNode*, vector<AStarNode*>, AStarNode::CompareFun> open;
  unordered_set<AStarNode*, AStarNode::HashFun> open_set;
  unordered_set<AleaGame, AleaGame::HashFun> closed;
  AStarNode* start_node = new AStarNode(game, 0);
  open.push(start_node);
  open_set.insert(start_node);
  int evaluated_moves = 0;
  int dead_positions = 0;
  int skipped_moves = 0;
  int branched_nodes = 0;
  while (open.size() > 0) {
    ++branched_nodes;
    AStarNode* current_node = open.top();
    open.pop();
    open_set.erase(current_node);
    closed.insert(current_node->game);
    if (current_node->game.is_valid_starting_configuration()) {
      current_node->game.print(true);
      res.first = printLevel(current_node->game, current_node->f);
      while (current_node->parent != NULL) {
        res.second.push_back(AleaGame::revert_action(current_node->action));
        current_node = current_node->parent;
      }      
      break;
    }
    vector<Action> actions = current_node->game.possible_moves();
    //AleaGame::show_moves(actions);
    for (Action action : actions) {
      AleaGame new_game = AleaGame(current_node->game);
      if(!new_game.move(action, true)){
        cout<<"\nError while moving from: "<<action.from<<" | dir: "<<action.dir<<"Exiting.\n"; 
        exit(1);
      }
      if (closed.find(new_game) != closed.end()) {
        ++skipped_moves;
        continue;
      }
      int value = new_game.heuristic_evaluation();
      ++evaluated_moves;
      if (value < 0) {
        ++dead_positions;
        continue;
      }
      AStarNode* neighbor = new AStarNode(new_game, action, current_node, -1*action.weight, value);
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
  //cout << "Evaluated:" << evaluated_moves << endl;
  //cout << "Dead:"<< dead_positions << endl;
  //cout << "Skipped:"<< skipped_moves << endl;
  //cout << "Branched:"<< branched_nodes << endl;
  return res;
}

string printLevel(AleaGame map_configuration, double difficulty){
  json level, dice, terminal;
  level["columns"] = MAP_WIDTH;
  level["rows"] = MAP_HEIGHT;

  for(auto t : map_configuration.terminals){
    terminal["x"] = t.x;
    terminal["y"] = t.y;
    level["terminals"].push_back(terminal);
  }
  for(auto d : map_configuration.dices){
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

/*
vector<vector<Action>> astar_search_all(AleaGame game, int limit) {
  priority_queue<AStarNode*, vector<AStarNode*>, AStarNode::CompareFun> open;
  unordered_set<AStarNode*, AStarNode::HashFun> open_set;
  unordered_set<AleaGame, AleaGame::HashFun> closed;
  AStarNode* start_node = new AStarNode(game);
  open.push(start_node);
  open_set.insert(start_node);
  vector<vector<Action>> solutions;
  int evaluated_moves = 0;
  int dead_positions = 0;
  int skipped_moves = 0;
  int branched_nodes = 0;
  while (open.size() > 0) {
    ++branched_nodes;
    AStarNode* current_node = open.top();
    open.pop();
    open_set.erase(current_node);
    closed.insert(current_node->game);
    if (current_node->game.win()) {
      vector<Action> solution;
      while (current_node->parent != NULL) {
        solution.push_back(current_node->action);
        current_node = current_node->parent;
      }
      reverse(solution.begin(), solution.end());
      solutions.push_back(solution);
      continue;
    }
    vector<Action> actions = current_node->game.possible_moves();
    for (Action action : actions) {
      AleaGame new_game = AleaGame(current_node->game);
      new_game.move(action);
      if (closed.find(new_game) != closed.end()) {
        ++skipped_moves;
        continue;
      }
      int value = new_game.heuristic_evaluation();
      ++evaluated_moves;
      if (value < 0) {
        ++dead_positions;
        continue;
      }
      AStarNode* neighbor = new AStarNode(new_game, action, current_node, 0, value);
      if (open_set.find(neighbor) == open_set.end()) {
        open.push(neighbor);
        open_set.insert(neighbor);
      }
    }
    if (branched_nodes > limit) break;
  }
  return solutions;
}*/