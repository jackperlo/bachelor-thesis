/**
  This contains the A* Backward algorithm and the RBFS Forward algorithm
  @file search_algorithms.h search_algorithms.cpp
  @authors Mirko Polato, Giacomo Perlo
*/
#include "search_algorithms.h"
#include <string>
#include <iomanip>
#include <fstream>
#include <thread>
#include <future>
#include <mutex>
#include <chrono>
#include <ctime>

mutex mtx;
int search_limit = numeric_limits<int>::max();
Node::~Node(){}
Node::Node(AleaGame game) : game(game) { }
Node::Node(AleaGame game, Action action) : game(game), action(action) { }
Node::Node(AleaGame game, double g) : game(game), g(g) { }
Node::Node(AleaGame game, double g, double h) : game(game), g(g), h(h) { f = g + h; }
Node::Node(AleaGame game, Action action, shared_ptr<Node> parent) : game(game), action(action), parent(parent) { }
Node::Node(AleaGame game, Action action, shared_ptr<Node> parent, double g, double h) : game(game), action(action), parent(parent), g(g), h(h) { 
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
  return n1->f > n2->f; //ordering priority queue as a min-heap
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
      shared_ptr<Node> neighbor(new Node(new_game, action, current_node, current_node->f, action.heuristic_value));
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
  search_limit = limit;
  vector<pair<AleaGame, vector<Action>>> banal_search_results = original_game.find_banal_starts_forward_search_wrapper();
  
  #ifdef DEBUG
    return start_multi_threading(original_game, banal_search_results, res, upper_bound);
  #else
    auto it = banal_search_results.begin();

    for(pair<AleaGame, vector<Action>> &banal_search : banal_search_results){
      if(banal_search.first.is_valid_ending_configuration_forward_search()){
        cout<<"\nBanal Starting Configuration Found. (Difficulty = "<<banal_search.first.heuristic_value<<")\n";
        if(banal_search.first.heuristic_value<upper_bound){
          res.push(make_pair(banal_search.second, banal_search.first.heuristic_value));
          cout<<"\n\t"<< FGGREENSTART <<"New BANAL Solution Found!\n"<< FGRESET;
          banal_search_results.erase(it);
        }
      }    
      it++;
    }
    if(res.size() > 0) return res; 
    else return start_multi_threading(original_game, banal_search_results, res, upper_bound);
  #endif
}

priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, Node::CompareFunSolutionsForward> Node::start_multi_threading(AleaGame original_game, vector<pair<AleaGame, vector<Action>>> banal_search_results, priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, Node::CompareFunSolutionsForward> res, double upper_bound){
  priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, Node::CompareFunSolutionsForward> tmp;
  vector<future<priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, Node::CompareFunSolutionsForward>>> futures;
  futures.reserve(banal_search_results.size());

  #ifndef DEBUG
    int i=1;

    cout<<"Banal Configurations Found: "<<banal_search_results.size()<<endl<<endl;
    cout<<"Loading..."<<endl<<endl;
    for(pair<AleaGame, vector<Action>> banal_search : banal_search_results){
      search_limit = BRANCHED_NODES_LIMIT;
      futures.push_back(async(launch::async, rbfs_forward, banal_search, upper_bound, i));
      i++;    
    }

    i=0;
    for (size_t i = 0; i < futures.size(); ++i){
      auto tmp = futures[i].get();
      if(tmp.size() > 0) res = merge_priority_queues(res, tmp);
    }
  #endif
      
  if(res.size() == 0){
    search_limit = numeric_limits<int>::max();
    cout<<"\nOriginal Starting Configuration Analysis:\n";
    tmp = rbfs_forward(make_pair(original_game, vector<Action>()), upper_bound);
    res = merge_priority_queues(res, tmp);
  }

  return res;
} 

int Node::get_siblings(shared_ptr<Node> current_node, priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, Node::CompareFunForward> &open, unordered_set<shared_ptr<Node>, Node::HashFun> &open_set, int &evaluated_moves, vector<pair<int, int>> &excluding_heuristic_possible_moves_activation){
  open_set.clear();
  while (!open.empty()) open.pop();

  #ifdef DEBUG
    cout<<"=====SIBLINGS=====\n";
  #endif

  int siblings_number = 0;
  for(pair<P2D, Dice*> pair : current_node->game.dices){
    if(pair.second->get_n_moves() > 0){
      for(P2D dir : {P2D::LEFT, P2D::RIGHT, P2D::DOWN, P2D::UP}){
        P2D from_pos = pair.first;
        AleaGame new_game = AleaGame(current_node->game);
        std::pair<bool, int> movement_result;

        int movement_type = SIMPLE_MOVE;
        if(new_game.dices.find(pair.first+dir) != new_game.dices.end()){
          if(pair.second->get_actual_type().compare("YellowDice") == 0) movement_type = JUMP_MOVE;
          else movement_type = PUSHED_MOVE;
        }
        movement_result = new_game.move(pair.first, dir, SIMPLE_MOVE, false);
        P2D new_dice_position = new_game.get_new_dice_position(pair.first, dir, movement_result.second);
        std::pair<P2D, Dice *> new_dice = make_pair(new_dice_position, pair.second);

        #ifdef DEBUG
          cout<<"Dice: "<<pair.first<<" | To: "<<dir<<" | Resulted in: "<<movement_result.first<<endl;
        #endif

        if(movement_result.first){
          Action action_result = new_game.move_forward_stats(excluding_heuristic_possible_moves_activation, from_pos, new_dice, dir, movement_result, movement_type);
          if(!(action_result == Action::null_action)){
            #ifdef DEBUG
              cout<<"\tStats: Don't cut"<<endl;
            #endif

            siblings_number++;
            shared_ptr<Node> neighbor(new Node(new_game, action_result, current_node, current_node->f, new_game.calculate_heuristic_value())); 
            if (open_set.find(neighbor) == open_set.end()) {
              open.push(neighbor);
              open_set.insert(neighbor);
            }
          }
          #ifdef DEBUG
            else cout<<"\tStats: Cut"<<endl;
          #endif
        }

        evaluated_moves++;
      }
    }
  }
  #ifdef DEBUG
    cout<<"=====END SIBLINGS=====\n";
  #endif
  return siblings_number;
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
priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, Node::CompareFunSolutionsForward> Node::rbfs_forward(pair<AleaGame, vector<Action>> banal_search, double upper_bound, int thread_name){
  priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, Node::CompareFunSolutionsForward> res;
  priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, Node::CompareFunForward> open;
  unordered_set<shared_ptr<Node>, Node::HashFun> open_set;
  unordered_set<int> closed;  
  unordered_set<int> siblings_closed;
  pair<AleaGame, double> best_solution_found;
  shared_ptr<Node> parent_node;
  int siblings_number = 1;
  int sequentially_skipped_nodes = 0;
  int evaluated_moves = 0;
  int skipped_moves = 0;
  int branched_nodes = 0;
  
  vector<pair<int, int>> excluding_heuristic_possible_moves_activation = {make_pair(0,0), make_pair(0,0), make_pair(0,0), make_pair(0,0)};
  best_solution_found.second = 0.00;
  chrono::time_point<chrono::system_clock> start, end;

  shared_ptr<Node> current_node;
  shared_ptr<Node> start_node(new Node(banal_search.first, banal_search.first.heuristic_value, 0.00));
  open.push(start_node);
  open_set.insert(start_node);
  
  #ifdef DEBUG
    int depth=0;
    cout<<"\nRoot DEPTH="<<depth<<"\n";
    int i=1;
  #endif
  /*unordered_set<P2D, P2D::HashFun> terminals;
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  terminals.insert(P2D(2, 1));
  terminals.insert(P2D(3, 3));
  WhiteDice wd1(Cell(2, 1), 0, 2);
  WhiteDice wd2(Cell(3, 2), 1, 1);
  dices.insert(pair<P2D, Dice *>(P2D(2, 1), &wd1));
  dices.insert(pair<P2D, Dice *>(P2D(3, 2), &wd2));
  AleaGame my_game(terminals, dices); */

  start = std::chrono::system_clock::now();
  while (open.size() > 0) {
    #ifdef DEBUG
      if(i!=1)
        cout<<"Node: "<<i<<" | NSiblings: "<<siblings_number<<" | Open.size(): "<<open.size()<<" | Current Depth: "<<depth<<endl;
    #endif

    current_node = open.top();
    open.pop();
    open_set.erase(current_node);

    #ifdef DEBUG
      i++;  
      cout << FGMAGENTASTART << "\nTHREAD " << thread_name << "~:" << FGRESET << endl;
      current_node->game.print(true, false);
      cout << "HashValue: " << AleaGame::HashFun()(current_node->game) << endl;
    #endif

    if(current_node->game.is_valid_ending_configuration_forward_search() && current_node->f <= upper_bound){
      pair<vector<Action>, double> solution;
      solution.second = current_node->f;
      while (current_node->parent != NULL) {
        solution.first.push_back(current_node->action);
        current_node = current_node->parent;
      }
      if(solution.first.size() > 0) cout<<"\n"<< FGMAGENTASTART << "THREAD " << thread_name << "~:" << FGRESET << FGGREENSTART <<"RBFS Forward: New Solution Found!\n"<< FGRESET;
      reverse(solution.first.begin(), solution.first.end());
      int offset = 0;
      for(Action move : banal_search.second){
        solution.first.insert(solution.first.begin()+offset, move);
        offset++;
      }
      
      res.push(solution);
      closed.insert(AleaGame::HashFun()(current_node->game));

      search_limit = BRANCHED_NODES_LIMIT; //to not waste too much time.. at least a solution has already been found
      continue;
    }

    if(siblings_closed.find(AleaGame::HashFun()(current_node->game)) != siblings_closed.end() || closed.find(AleaGame::HashFun()(current_node->game)) != closed.end() || current_node->f > upper_bound){
      skipped_moves++;
      sequentially_skipped_nodes++;

      #ifdef DEBUG
        cout<<FGREDSTART<<"^Skipped^\n"<<FGRESET;
        if(siblings_closed.find(AleaGame::HashFun()(current_node->game)) != siblings_closed.end())
          cout<<"\tsibling skipped: found in siblings_closed\n\tsequentially skipped siblings "<<sequentially_skipped_nodes<<endl;
        else if(closed.find(AleaGame::HashFun()(current_node->game)) != closed.end())
          cout<<"\tsibling skipped: found in closed\n\tsequentially skipped siblings "<<sequentially_skipped_nodes<<endl;
        else if(current_node->f >= upper_bound)
          cout<<"\tsibling skipped: "<<current_node->f<<">="<<upper_bound<<"\n\tsequentially skipped siblings "<<sequentially_skipped_nodes<<endl;
      #endif

      closed.insert(AleaGame::HashFun()(current_node->game));
      if(sequentially_skipped_nodes == siblings_number){ //backtracking internal nodes
        if(current_node->parent && current_node->parent != start_node){
          closed.insert(AleaGame::HashFun()(current_node->parent->game));
          siblings_closed.clear();
          
          parent_node = current_node->parent->parent;
          sequentially_skipped_nodes = 0;
          #ifdef DEBUG
            depth-=DEPTH_DECREASING_INDEX;
            cout << "BACKTRACKING FROM INTERNAL NODE, ALL SIBLINGS EXPLORED, NEW DEPTH="<<depth<<endl;
          #endif
          siblings_number = get_siblings(parent_node, open, open_set, evaluated_moves, excluding_heuristic_possible_moves_activation);
          #ifdef DEBUG 
            depth++;
            cout<<"NSiblings found:"<<siblings_number<<" at depth: "<<depth<<endl;
          #endif
        continue;
        }
      } 
      
    }
    skipped_moves--;

    sequentially_skipped_nodes = 0;
    branched_nodes++;
    siblings_closed.insert(AleaGame::HashFun()(current_node->game));
    siblings_number = get_siblings(current_node, open, open_set, evaluated_moves, excluding_heuristic_possible_moves_activation);
    #ifdef DEBUG
      depth++;
      cout<<"\tNSiblings found:"<<siblings_number<<" at DEPTH: "<<depth<<endl<<endl;
    #endif

    if(siblings_number==0){ //backtracking leaves
      if(current_node->parent){ 
        closed.insert(AleaGame::HashFun()(current_node->game));

        parent_node = current_node->parent;
        sequentially_skipped_nodes = 0;
        #ifdef DEBUG
          depth-=DEPTH_DECREASING_INDEX;
          cout << "BACKTRACKING FROM LEAF, NEW DEPTH="<<depth<<endl;
        #endif
        siblings_number = get_siblings(parent_node, open, open_set, evaluated_moves, excluding_heuristic_possible_moves_activation);
        #ifdef DEBUG 
          depth++;
          cout<<"NSiblings found:"<<siblings_number<<" at depth: "<<depth<<endl;
        #endif
      }
    }

    if(sequentially_skipped_nodes == siblings_number){ //backtracking internal nodes
      if(current_node->parent && current_node->parent != start_node){
        closed.insert(AleaGame::HashFun()(current_node->parent->game));
        siblings_closed.clear();
        
        parent_node = current_node->parent->parent;
        sequentially_skipped_nodes = 0;
        
        #ifdef DEBUG
          depth-=DEPTH_DECREASING_INDEX;
          cout << "BACKTRACKING FROM INTERNAL NODE, ALL SIBLINGS EXPLORED, NEW DEPTH="<<depth<<endl;
        #endif
        siblings_number = get_siblings(parent_node, open, open_set, evaluated_moves, excluding_heuristic_possible_moves_activation);
        #ifdef DEBUG 
          depth++;
          cout<<"NSiblings found:"<<siblings_number<<" at depth: "<<depth<<endl;
        #endif
      }
    } 

    if(current_node->f > best_solution_found.second){
      best_solution_found.first = current_node->game;
      best_solution_found.second = current_node->f;        
    }
    if (branched_nodes > search_limit){
      cout << FGMAGENTASTART << "\nTHREAD " << thread_name << "~:" << FGRESET << FGREDSTART << "BRANCHED_NODES LIMIT REACHED. EXIT.\n" << FGRESET;
      break;
    }
    if(branched_nodes % 50000 == 0){
      cout << FGMAGENTASTART << "\nTHREAD " << thread_name << "~:" << FGRESET << "Branched:" << branched_nodes << endl;
      cout << FGMAGENTASTART << "\nTHREAD " << thread_name << "~:" << FGRESET << "Current Heuristic Treshold: "<<best_solution_found.second<<endl;
      //current_node->game.print(true, false);
    }
  }
  end = std::chrono::system_clock::now();
  chrono::duration<double> elapsed_seconds = end - start;

  if (branched_nodes <= search_limit && open.size() == 0)
    cout << FGMAGENTASTART << "\nTHREAD " << thread_name << "~:" << FGRESET << FGYELLOWSTART << "TREE TOTALLY EXPLORED. EXIT.\n" << FGRESET;

  cout << "\tTime Elapsed: " << elapsed_seconds.count() << " sec" << endl;
  cout << "\tEvaluated:" << evaluated_moves << endl;
  cout << "\tSkipped:"<< skipped_moves << endl;
  cout << "\tBranched:"<< branched_nodes << endl<<endl;

  cout << "\tWhite Cutting Heuristics [#triggered/#total]: (" << excluding_heuristic_possible_moves_activation[0].first << "/" << excluding_heuristic_possible_moves_activation[0].second << ") ";
  if(excluding_heuristic_possible_moves_activation[0].second != 0) cout << "-> " << ((double)excluding_heuristic_possible_moves_activation[0].first/(double)excluding_heuristic_possible_moves_activation[0].second)*100 << "%" << endl;
  else cout << " -> 0%" << endl;
  
  cout << "\tRed Cutting Heuristics [#triggered/#total]: (" << excluding_heuristic_possible_moves_activation[1].first << "/" << excluding_heuristic_possible_moves_activation[1].second << ") ";
  if(excluding_heuristic_possible_moves_activation[1].second != 0) cout << "-> " << ((double)excluding_heuristic_possible_moves_activation[1].first/(double)excluding_heuristic_possible_moves_activation[1].second)*100 << "%" << endl;
  else cout << " -> 0%" << endl;
  
  cout << "\tYellow Cutting Heuristics [#triggered/#total]: (" << excluding_heuristic_possible_moves_activation[2].first << "/" << excluding_heuristic_possible_moves_activation[2].second << ") ";
  if(excluding_heuristic_possible_moves_activation[2].second != 0) cout << "-> " << ((double)excluding_heuristic_possible_moves_activation[2].first/(double)excluding_heuristic_possible_moves_activation[2].second)*100 << "%" << endl;
  else cout << " -> 0%" << endl;
  
  cout << "\tGreen Cutting Heuristics [#triggered/#total]: (" << excluding_heuristic_possible_moves_activation[3].first << "/" << excluding_heuristic_possible_moves_activation[3].second << ") ";
  if(excluding_heuristic_possible_moves_activation[3].second != 0) cout << "-> " << ((double)excluding_heuristic_possible_moves_activation[3].first/(double)excluding_heuristic_possible_moves_activation[3].second)*100 << "%" << endl<<endl;
  else cout << " -> 0%" << endl;
  
  if(res.size() == 0){
    cout << FGMAGENTASTART << "\nTHREAD " << thread_name << "~:" << FGRESET << "Deeper solution found (value="<<best_solution_found.second<<"):\n";
    //best_solution_found.first.print(true, false);
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
  mtx.lock();
  while (!source2.empty()){
    source1.push(source2.top());
    source2.pop();
  }
  mtx.unlock();
  return source1;
}