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
      cout<<"Configuration Found (user start): "<<endl;
      current_node->game.print(true, true);
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

priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, AStarNode::CompareFunSolutionsForward> AStarNode::astar_forward_wrapper(AleaGame original_game, int limit) {
  priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, AStarNode::CompareFunSolutionsForward> res;
  priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, AStarNode::CompareFunSolutionsForward> tmp;
  double difficulty = 0.00;
  
  vector<pair<bool, pair<AleaGame, vector<Action>>>> banal_search_results = original_game.find_banal_starts_forward_search_wrapper();
  int i=1;
  for(pair<bool, pair<AleaGame, vector<Action>>> banal_search : banal_search_results){
    if(banal_search.first){
      AleaGame new_game = original_game;
      if(new_game.setting_up_banal_configuration(banal_search.second, &difficulty, i, banal_search_results.size()))
        res.push(make_pair(banal_search.second.second, difficulty));
      
      tmp = astar_forward_search(new_game, limit, &difficulty, banal_search.first, banal_search);
      res = merge_priority_queues(res, tmp);
      if(res.size() > 0)
        return res;
      i++;
    }
  }
  if(res.size() == 0){
    tmp = astar_forward_search(original_game, limit, &difficulty);
    res = merge_priority_queues(res, tmp);
  }

  return res;
}

priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, AStarNode::CompareFunSolutionsForward> AStarNode::astar_forward_search(AleaGame game, int limit, double *difficulty, bool banal_solution_found, pair<bool, pair<AleaGame, vector<Action>>> banal_search){
  priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, AStarNode::CompareFunSolutionsForward> res;
  priority_queue<AStarNode*, vector<AStarNode*>, AStarNode::CompareFunForward> open;
  unordered_set<AStarNode*, AStarNode::HashFun> open_set;
  unordered_set<AleaGame, AleaGame::HashFun> closed;
  int evaluated_moves = 0;
  int skipped_moves = 0;
  int branched_nodes = 0;
  
  AStarNode* start_node = new AStarNode(game, *difficulty, 0.00);
  open.push(start_node);
  open_set.insert(start_node);
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
    if (branched_nodes > limit){
      cout << "BRANCHED_NODES LIMIT REACHED. EXIT\n\n";
      break;
    }
    if(branched_nodes % 2000 == 0)
      cout << "Branched:" << branched_nodes << endl;
  }
  cout << "Evaluated:" << evaluated_moves << endl;
  cout << "Skipped:"<< skipped_moves << endl;
  cout << "Branched:"<< branched_nodes << endl<<endl;

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

priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, AStarNode::CompareFunSolutionsForward> AStarNode::merge_priority_queues(priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, AStarNode::CompareFunSolutionsForward> source1, priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, AStarNode::CompareFunSolutionsForward> source2){
  while (!source2.empty()){
    source1.push(source2.top());
    source2.pop();
  }
  return source1;
}