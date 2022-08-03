/**
  This contains the A* Backward algorithm and the RBFS Forward algorithm
  @file search_algorithms.h search_algorithms.cpp
  @authors Mirko Polato, Giacomo Perlo
*/
#include "search_algorithms.h"
#include <string>
#include <iomanip>
#include <fstream>

Node::Node(AleaGame game) : game(game) { }
Node::Node(AleaGame game, Action action) : game(game), action(action) { }
Node::Node(AleaGame game, double g) : game(game), g(g) { }
Node::Node(AleaGame game, double g, double h) : game(game), g(g), h(h) { f = g + h; }
Node::Node(AleaGame game, Action action, shared_ptr<Node> parent) : game(game), action(action), parent(parent) { }
Node::Node(AleaGame game, Action action, shared_ptr<Node> parent, double g, double h, double distance_from_closer_terminal_weight) : game(game), action(action), parent(parent), g(g), h(h), distance_from_closer_terminal_weight(distance_from_closer_terminal_weight) { 
  f = g + h;
}

bool Node::operator==(const Node& other) const {
  return this->game == other.game;
}

Node& Node::operator=(shared_ptr<Node> node){
  this->game = node->game;
  this->action = node->action;
  this->parent = node->parent;
  this->g = node->g;
  this->h = node->h;
  this->f = node->f;
  return *this;
}

bool Node::operator<(const Node& other) const {
  return f < other.f;
}

ostream& operator<<(ostream& out, shared_ptr<Node> node) {
  out << "(" << node->f << ")";
  return out;
}

bool Node::CompareFunBackward::operator() (shared_ptr<Node> n1, shared_ptr<Node> n2) {
  return n1->f < n2->f; //ordering priority queue as a max-heap
}

bool Node::CompareFunForward::operator() (shared_ptr<Node> n1, shared_ptr<Node> n2) {
  return n1->f+n1->distance_from_closer_terminal_weight > n2->f+n2->distance_from_closer_terminal_weight; //ordering priority queue as a min-heap
}

size_t Node::HashFun::operator()(shared_ptr<Node> const&n) const{
  return AleaGame::HashFun()(n->game);
}

bool Node::CompareFunSolutionsForward:: operator() (pair<vector<Action>, double> solution1, pair<vector<Action>, double> solution2){
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
pair<string, vector<Action>> Node::astar_backward_search(AleaGame game, int limit) {
  pair<string, vector<Action>> res;
  priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, Node::CompareFunBackward> open;
  unordered_set<shared_ptr<Node>, Node::HashFun> open_set;
  unordered_set<AleaGame, AleaGame::HashFun> closed;
  shared_ptr<Node> start_node(new Node(game, 0));
  open.push(start_node);
  open_set.insert(start_node);
  int evaluated_moves = 0;
  int skipped_moves = 0;
  int branched_nodes = 0;
  while (open.size() > 0) {
    ++branched_nodes;
    shared_ptr<Node> current_node = open.top();
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
        cout<<"\nastar.cpp:astar_backward_search: Error while moving from: "<<action.from<<", dir: "<<action.dir<<", type:"<<action.movement_type<<", head:"<<action.head<<"\nExiting.\n"; 
        exit(1);
      }
      new_game.last_action_performed = action;
      if (closed.find(new_game) != closed.end()) {
        ++skipped_moves;
        continue;
      }
      ++evaluated_moves;
      shared_ptr<Node> neighbor(new Node(new_game, action, current_node, current_node->f, action.weight));
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
  This is a wrapper for the RBFS forward algorithm which obtains the banal starting configurations 
  (these are derivied by sequences of "banal" moves: dices which has manhattan distance from 
  a terminal equal to the number of their available moves).

  Once obtained all the banal configurations possible, it calls the RBFS forward algorithm starting 
  from each one of them. After that, if no solution has been found (starting from banal
  configurations) it calls RBFS forward starting from @original_game.
  Note that it's looking for the easier solutions, so if it find one (or more) solution starting 
  from a banal configuration then it will be way easier than a solution starting from @original_game; 
  so it can consider to avoid RBFS forward starting from @original_game in this case, saving time and 
  resources.

  Since more than a solution can be found, every time RBFS forward is called and returns one (or more) 
  solutions, the old priorty queue (which contains the solutions found so far) must be merged with 
  the one returned by A* (containing the new solution(s)).
  @param original_game AleaGame instance based on starting configuration specified in its .json file 
          previously found by A* backward search
  @param limit maximum number of branched nodes astar can explore.
  @return a priority queue containing pairs (each pair corresponds to a solution found) composed by:
          a vector of moves (to get from starting config->ending config(=solution)) 
          and the difficulty calculated for that solution
*/
priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, Node::CompareFunSolutionsForward> Node::rbfs_forward_search(AleaGame original_game, double upper_bound, int limit) {
  priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, Node::CompareFunSolutionsForward> res;
  priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, Node::CompareFunSolutionsForward> tmp;
  double difficulty = 0.00;
  
  vector<pair<AleaGame, vector<Action>>> banal_search_results = original_game.find_banal_starts_forward_search_wrapper();
  int i=1;
  for(pair<AleaGame, vector<Action>> banal_search : banal_search_results){
    AleaGame new_game = original_game;
    difficulty = 0.00;
    if(new_game.setting_up_banal_configuration(banal_search, &difficulty, i, banal_search_results.size()) && difficulty<upper_bound){
      res.push(make_pair(banal_search.second, difficulty));
      cout<<"\n\t"<< FGGREENSTART <<"New BANAL Solution Found!\n"<< FGRESET;
    }else{
      cout<<"Banal Starting Configuration Forward Analysis: (starting difficulty = "<<difficulty<<")\n";
      tmp = rbfs_forward(new_game, limit, &difficulty, upper_bound, banal_search);
      if(tmp.size() > 0) res = merge_priority_queues(res, tmp);
    }
    
    if(res.size() > 0) return res;
    
    i++;
  }
  if(res.size() == 0){
    difficulty=0.00;
    cout<<"\nOriginal Starting Configuration Analysis:\n";
    tmp = rbfs_forward(original_game, limit, &difficulty, upper_bound);
    res = merge_priority_queues(res, tmp);
  }
  
  return res;
}

int Node::get_siblings(shared_ptr<Node> current_node, priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, Node::CompareFunForward> &open, unordered_set<shared_ptr<Node>, Node::HashFun> &open_set, int &evaluated_moves, /*int depth,*/ vector<pair<int, int>> &excluding_heuristic_possible_moves_activation){
  open_set.clear();
  while (!open.empty()) open.pop();
  
  vector<Action> actions = current_node->game.possible_moves_forward(excluding_heuristic_possible_moves_activation);
  int siblings_number = actions.size();
  //cout<<"NSiblings found:"<<siblings_number<<" at depth: "<<depth<<endl;
  for (Action action : actions) {
    AleaGame new_game = AleaGame(current_node->game);
    if(!new_game.move(action, false)){
      cout<<"\nastar.cpp:astar_forward_search: Error while moving from: "<<action.from<<", dir: "<<action.dir<<", type:"<<action.movement_type<<", head:"<<action.head<<"\nExiting.\n"; 
      exit(1);
    }

    evaluated_moves++;
    
    shared_ptr<Node> neighbor(new Node(new_game, action, current_node, current_node->f, action.weight, action.distance_from_closer_terminal)); 
    if (open_set.find(neighbor) == open_set.end()) {
      open.push(neighbor);
      open_set.insert(neighbor);
    }
  }
  return siblings_number;
}

void Node::backtrace(shared_ptr<Node> parent_node, int &sequentially_skipped_nodes, int &depth, int &siblings_number, priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, Node::CompareFunForward> &open, unordered_set<shared_ptr<Node>, Node::HashFun> &open_set, int &evaluated_moves, vector<pair<int, int>> &excluding_heuristic_possible_moves_activation){
  sequentially_skipped_nodes = 0;
  depth-=DEPTH_DECREASING_INDEX;
  //cout << "BACKTRACKING, NEW DEEP="<<depth<<endl;
  //cancellare tutti i fratelli del current node..
  siblings_number = get_siblings(parent_node, open, open_set, evaluated_moves, /*depth+1,*/ excluding_heuristic_possible_moves_activation);
  depth++;
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
  computed before (if presents) and the moves computed by RBFS forward to reach the ending configuration
  @param game AleaGame instance prepared and passed by the wrapper (astar_forward_search)
  @param limit maximum number of branched nodes astar can explore.
  @param difficulty number which rapresents level difficulty. Initialized (=0) by the wrapper 
  @param banal_search banal configurations found by the wrapper: 
                      starting configuration and list of moves detected, for each
  @return a priority queue containing pairs (each pair corresponds to a solution found) composed by:
          a vector of moves (to get from starting config->ending config(=solution)) 
          and the difficulty calculated for that solution
*/
priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, Node::CompareFunSolutionsForward> Node::rbfs_forward(AleaGame game, int limit, double *difficulty, double upper_bound, pair<AleaGame, vector<Action>> banal_search){
  priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, Node::CompareFunSolutionsForward> res;
  priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, Node::CompareFunForward> open;
  unordered_set<shared_ptr<Node>, Node::HashFun> open_set;
  unordered_set<int> closed;  
  unordered_set<int> siblings_closed;
  pair<AleaGame, double> best_solution_found;
  shared_ptr<Node> parent_node;
  int depth=0;
  int siblings_number = 1;
  int sequentially_skipped_nodes = 0;
  int evaluated_moves = 0;
  int skipped_moves = 0;
  int branched_nodes = 0;
  vector<pair<int, int>> excluding_heuristic_possible_moves_activation = {make_pair(0,0), make_pair(0,0), make_pair(0,0), make_pair(0,0)};
  best_solution_found.second = 0.00;
  
  shared_ptr<Node> current_node;
  shared_ptr<Node> start_node(new Node(game, *difficulty, 0.00));
  open.push(start_node);
  open_set.insert(start_node);
  //cout<<"Root DEEP=0\n\n";
  while (open.size() > 0) {
    //cout<<"NSiblings: "<<siblings_number<<" | Open.size(): "<<open.size()<<" | Current Depth: "<<depth<<endl;
    current_node = open.top();
    open.pop();
    open_set.erase(current_node);

    if(siblings_number == 0 || siblings_closed.find(AleaGame::HashFun()(current_node->game)) != siblings_closed.end() || closed.find(AleaGame::HashFun()(current_node->game)) != closed.end() || current_node->f > upper_bound) {
      if(siblings_number != 0){
        skipped_moves++;
        sequentially_skipped_nodes++;
        /*if(siblings_closed.find(AleaGame::HashFun()(current_node->game)) != siblings_closed.end())
          cout<<"\tsibling skipped: found in siblings_closed\n\tsequentially skipped siblings"<<sequentially_skipped_nodes<<endl;
        else if(closed.find(AleaGame::HashFun()(current_node->game)) != closed.end())
          cout<<"\tsibling skipped: found in closed\n\tsequentially skipped siblings"<<sequentially_skipped_nodes<<endl;
        else if(current_node->f >= upper_bound)
          cout<<"\tsibling skipped: "<<current_node->f<<">="<<upper_bound<<"\n\tsequentially skipped siblings"<<sequentially_skipped_nodes<<endl;
        */
      }
      if(siblings_number == 0 || sequentially_skipped_nodes == siblings_number){//BACKTRACKING internal nodes and leafs
        if(current_node->parent){
          
          if(sequentially_skipped_nodes==siblings_number) 
            closed.insert(AleaGame::HashFun()(current_node->parent->game));
          siblings_closed.clear();
          
          if(current_node->parent->parent){ 
            parent_node = current_node->parent->parent;
            //cout<<"IF sibling 0->backtracking\n";
            current_node->backtrace(parent_node, sequentially_skipped_nodes, depth, siblings_number, open, open_set, evaluated_moves, excluding_heuristic_possible_moves_activation);
          }
          
        }
      } 
      closed.insert(AleaGame::HashFun()(current_node->game));
      continue;  
    }

    sequentially_skipped_nodes = 0;
    branched_nodes++;
    depth++;
    siblings_closed.insert(AleaGame::HashFun()(current_node->game));
    //cout<<"\n\tsibling found and added to sibling_closed, DEEP="<<depth-1<<endl;
    siblings_number = get_siblings(current_node, open, open_set, evaluated_moves, /*depth,*/ excluding_heuristic_possible_moves_activation);
      
    if (current_node->game.is_valid_ending_configuration_forward_search()){
      pair<vector<Action>, double> solution;
      while (current_node->parent != NULL) {
        solution.first.push_back(current_node->action);
        solution.second += current_node->f;
        current_node = current_node->parent;
      }
      if(solution.first.size() > 0) cout<< FGGREENSTART <<"\nAStar Forward: New Solution Found!\n"<< FGRESET;
      reverse(solution.first.begin(), solution.first.end());
      int offset = 0;
      for(Action move : banal_search.second){
        solution.first.insert(solution.first.begin()+offset, move);
        solution.second += move.weight;
        offset++;
      }
      
      res.push(solution);
      continue;
    }

    if(current_node->f > best_solution_found.second){
      best_solution_found.first = current_node->game;
      best_solution_found.second = current_node->f;
    }
      

    if(siblings_number==0){
      if(current_node->parent != start_node){ //backtracking to grandfather
        if(current_node->parent->parent){ 
          parent_node = current_node->parent->parent;
          //cout<<"Sibling 0->bracktracking\n";
          closed.insert(AleaGame::HashFun()(current_node->game));
          depth--;
          current_node->backtrace(parent_node, sequentially_skipped_nodes, depth, siblings_number, open, open_set, evaluated_moves, excluding_heuristic_possible_moves_activation);
        }
      }
    }

    if (branched_nodes > limit){
      cout << FGREDSTART << "BRANCHED_NODES LIMIT REACHED. EXIT.\n\n" << FGRESET;
      break;
    }
    if(branched_nodes % 10000 == 0){
      cout << "Branched:" << branched_nodes << endl;
      cout << "Interactions Threshold: "<<current_node->f<<endl;
    }
  }

  if (branched_nodes <= limit)
    cout << FGYELLOWSTART << "TREE TOTALLY EXPLORED. EXIT.\n\n" << FGRESET;

  cout << "Evaluated:" << evaluated_moves << endl;
  cout << "Skipped:"<< skipped_moves << endl;
  cout << "Branched:"<< branched_nodes << endl<<endl;
  
  cout << "White Heuristics [#triggered/#total]: (" << excluding_heuristic_possible_moves_activation[0].first << "/" << excluding_heuristic_possible_moves_activation[0].second << ") ";
  if(excluding_heuristic_possible_moves_activation[0].second != 0) cout << "-> " << ((double)excluding_heuristic_possible_moves_activation[0].first/(double)excluding_heuristic_possible_moves_activation[0].second)*100 << "%" << endl;
  else cout << " -> 0%" << endl;
  
  cout << "Red Heuristics [#triggered/#total]: (" << excluding_heuristic_possible_moves_activation[1].first << "/" << excluding_heuristic_possible_moves_activation[1].second << ") ";
  if(excluding_heuristic_possible_moves_activation[1].second != 0) cout << "-> " << ((double)excluding_heuristic_possible_moves_activation[1].first/(double)excluding_heuristic_possible_moves_activation[1].second)*100 << "%" << endl;
  else cout << " -> 0%" << endl;
  
  cout << "Yellow Heuristics [#triggered/#total]: (" << excluding_heuristic_possible_moves_activation[2].first << "/" << excluding_heuristic_possible_moves_activation[2].second << ") ";
  if(excluding_heuristic_possible_moves_activation[2].second != 0) cout << "-> " << ((double)excluding_heuristic_possible_moves_activation[2].first/(double)excluding_heuristic_possible_moves_activation[2].second)*100 << "%" << endl;
  else cout << " -> 0%" << endl;
  
  cout << "Green Heuristics [#triggered/#total]: (" << excluding_heuristic_possible_moves_activation[3].first << "/" << excluding_heuristic_possible_moves_activation[3].second << ") ";
  if(excluding_heuristic_possible_moves_activation[3].second != 0) cout << "-> " << ((double)excluding_heuristic_possible_moves_activation[3].first/(double)excluding_heuristic_possible_moves_activation[3].second)*100 << "%" << endl<<endl;
  else cout << " -> 0%" << endl;

  if(res.size() == 0){
    cout << "Deeper solution found (value="<<best_solution_found.second<<"):\n";
    best_solution_found.first.print(true, false);
    cout<<endl;
  }
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
string Node::printLevel(AleaGame map_configuration, double difficulty){
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
    terminal["pos"] = (t.y*MAP_WIDTH)+t.x;
    level["terminals"].push_back(terminal);
  }

  for(pair<P2D, Dice *> d : map_configuration.dices){
    dice["num"] = d.second->get_initial_moves();
    dice["type"] = d.second->get_actual_type_int(); 
    dice["x"] = d.second->get_position().get_x();
    dice["y"] = d.second->get_position().get_y();
    dice["pos"] = (d.second->get_position().get_y()*MAP_WIDTH)+d.second->get_position().get_x();
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
priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, Node::CompareFunSolutionsForward> Node::merge_priority_queues(priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, Node::CompareFunSolutionsForward> source1, priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, Node::CompareFunSolutionsForward> source2){
  while (!source2.empty()){
    source1.push(source2.top());
    source2.pop();
  }
  return source1;
}