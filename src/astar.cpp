/**
  This contains the A* Backward algorithm and the A* Forward algorithm
  @file astar.h astar.cpp
  @authors Polato Mirko, Giacomo Perlo
*/
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

/**
  This algorithm is deep search based and explores the tree developing from the root node(= @game):
  for each node it checks if it's a valid starting configuration(user pov), if so returns;
  otherwise it computes the possible moves backward and, for each one, it creates a child node
  making that move.

  The nodes are stored in a priority queue ordered as a Max-Heap, comparing them on their f(n) value.
  Note that, f(n) = g(n) + h(n), where:
    - g(n) = sum, from root_node up to this_node, of the interactions occured between dices which moved
            (see common.h which contains the movement weights)
    - f(n) = next move weight (from the "possible moves backwards" bundle)

  Being a backward search, when a valid starting configuration is found, the moves to do are reverted
  so that can be used to show (forward: starting config->ending config) how A* got the solution
  @param game AleaGame instance based on ending configuration specified in its .json file
  @param limit maximum number of branched nodes astar can explore.
  @return returns the .json file which contains the starting configuration(user pov), and the vector of moves to
          astar used to get from ending config->starting config (reversed).
*/
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

/**
  This is a wrapper for the A* forward algorithm which obtains the banal starting configurations 
  (these are derivied by sequences of "banal" moves: dices which has manhattan distance from 
  a terminal equal to the number of their available moves).

  Once obtained all the banal configurations possible, it calls the A* forward algorithm starting 
  from each one of them. After that, if no solution has been found (starting from banal
  configurations) it calls A* forward starting from @original_game.
  Note that it's looking for the easier solutions, so if it find one (or more) solution starting 
  from a banal configuration then it will be way easier than a solution starting from @original_game; 
  so it can consider to avoid A* forward starting from @original_game in this case, saving time and 
  resources.

  Since more than a solution can be found, every time A* forward is called and returns one (or more) 
  solutions, the old priorty queue (which contains the solutions found so far) must be merged with 
  the one returned by A* (containing the new solution(s)).
  @param original_game AleaGame instance based on starting configuration specified in its .json file 
          previously found by A* backward search
  @param limit maximum number of branched nodes astar can explore.
  @return a priority queue containing pairs (each pair corresponds to a solution found) composed by:
          a vector of moves (to get from starting config->ending config(=solution)) 
          and the difficulty calculated for that solution
*/
priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, AStarNode::CompareFunSolutionsForward> AStarNode::astar_forward_search(AleaGame original_game, int limit) {
  priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, AStarNode::CompareFunSolutionsForward> res;
  priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, AStarNode::CompareFunSolutionsForward> tmp;
  double difficulty = 0.00;
  
  vector<pair<AleaGame, vector<Action>>> banal_search_results = original_game.find_banal_starts_forward_search_wrapper();
  int i=1;
  for(pair<AleaGame, vector<Action>> banal_search : banal_search_results){
    AleaGame new_game = original_game;
    if(new_game.setting_up_banal_configuration(banal_search, &difficulty, i, banal_search_results.size()))
      res.push(make_pair(banal_search.second, difficulty));
    
    tmp = astar_forward(new_game, limit, &difficulty, banal_search);
    if(tmp.size() > 0) res = merge_priority_queues(res, tmp);
    if(res.size() > 0) return res;
    
    i++;
  }
  if(res.size() == 0){
    tmp = astar_forward(original_game, limit, &difficulty);
    res = merge_priority_queues(res, tmp);
  }

  return res;
}

/**
  This algorithm is deep search based and explores the tree developing from the root node(= @game):
  for each node it checks if it's a valid ending configuration(user pov), if so returns;
  otherwise it computes the possible moves forward and, for each one, it creates a child node
  making that move.

  The nodes are stored in a priority queue ordered as a Min-Heap, comparing them on their f(n) value.
  Note that, f(n) = g(n) + h(n), where:
    - g(n) = sum, from root_node up to this_node, of the interactions occured between dices which moved
            (see common.h which contains the movement weights)
    - f(n) = next move weight (from the "possible moves backwards" bundle)

  If the node considered is a valid ending configuration it mixes in a proper way the banal moves 
  computed before (if presents) and the moves computed by A* forward to reach the ending configuration
  @param game AleaGame instance prepared and passed by the wrapper (astar_forward_search)
  @param limit maximum number of branched nodes astar can explore.
  @param difficulty number which rapresents level difficulty. Initialized (=0) by the wrapper 
  @param banal_search banal configurations found by the wrapper: 
                      starting configuration and list of moves detected, for each
  @return a priority queue containing pairs (each pair corresponds to a solution found) composed by:
          a vector of moves (to get from starting config->ending config(=solution)) 
          and the difficulty calculated for that solution
*/
priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, AStarNode::CompareFunSolutionsForward> AStarNode::astar_forward(AleaGame game, int limit, double *difficulty, pair<AleaGame, vector<Action>> banal_search){
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
    if (current_node->game.is_valid_ending_configuration_forward_search()){
      pair<vector<Action>, double> solution;
      while (current_node->parent != NULL) {
        solution.first.push_back(current_node->action);
        solution.second += current_node->f;
        current_node = current_node->parent;
      }
      reverse(solution.first.begin(), solution.first.end());
      int offset = 0;
      for(Action move : banal_search.second){
        solution.first.insert(solution.first.begin()+offset, move);
        solution.second += move.weight;
        offset++;
      }
      cout<<"\nAStar Forward: New Solution Found!\n";
      res.push(solution);
      continue;
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


/**
  Prints the configuration found by A* backwards in a .json file in generated_levels folder.
  This file are the starting level from which a user could start to play.
  @param map_configuration AleaGame instance prepared and passed by A* backwards
  @param difficulty number which rapresents level difficulty. Initialized (=0) by the wrapper 
  @return a string containing the path to reach the level just generated (so that can be used
          by level_solver.cpp to do forward search)
*/
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

/**
  Returns a priority queue which is the mix of the two passed as parameter
  @param source1 priority queue containing pairs of moves and related difficulty(for each one)
  @param source2 priority queue containing pairs of moves and related difficulty(for each one)
  @return a priority queue which is the mix of @source1 and @sourc2, 
          containing pairs of moves and related difficulty(for each one)
*/
priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, AStarNode::CompareFunSolutionsForward> AStarNode::merge_priority_queues(priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, AStarNode::CompareFunSolutionsForward> source1, priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, AStarNode::CompareFunSolutionsForward> source2){
  while (!source2.empty()){
    source1.push(source2.top());
    source2.pop();
  }
  return source1;
}