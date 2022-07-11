/**
  Generates a starting level config using A* Backward. Tries to resolve the level using A* forward
  @file level_solver.cpp
  @author Giacomo Perlo
*/
#include "alea_game.h"
#include "astar.h"

pair<string, vector<Action>> start_backward_analysis(char *ending_config_file_name);
void get_solution_number_and_related_difficulty(string starting_config_file_name);
void print_expected_forward_solution(pair<string, vector<Action>> solution);
void playGamePrinter(AleaGame game, vector<Action> actions);

//controls operation of the program
int main(int argc, char *argv[]){ 
  pair<string, vector<Action>> solution;
  if(argc != 2){
    cout<<"\nlevel_solver.cpp:main: please insert level file name.\n\n"; 
    exit(1);
  }
  
  solution = start_backward_analysis(argv[1]);
  
  if(solution.first.compare("") != 0){
    get_solution_number_and_related_difficulty(solution.first);
    print_expected_forward_solution(solution);  
  }else
    cout << "\nlevel_solver:main: level_generated file has not been created. astar_backward_search failed.\n";  

  return 0;
}

/**
  Returns a possible starting configuration(user pov) using A* backward and the moves done to get there
  @param ending_config_file_name .json file name which contains the ending configuration(user pov) from which A* starts 
  @return starting configuration file name, moves (A* used on the contrary) to get from starting config->ending config
*/
pair<string, vector<Action>> start_backward_analysis(char *ending_config_file_name){
  string level_name = "./custom_level_config/";
  level_name.append(ending_config_file_name);
  AleaGame *backward_game = new AleaGame(level_name, true);
  cout<<"Starting Configuration (user end)"<<endl;
	backward_game->print(true);
  return AStarNode::astar_backward_search(*backward_game, BRANCHED_NODES_LIMIT);
}

/**
  Prints the number of solution found using A* forward(starting config->ending config, user pov) and show the moves of the easiest one(first position, being a priority queue)
  @param starting_config_file_name .json file name which contains the starting configuration(user pov) which A* backwards computed
*/
void get_solution_number_and_related_difficulty(string starting_config_file_name){
  cout<<starting_config_file_name<<endl;
  AleaGame *starting_config_analyzed_game = new AleaGame(starting_config_file_name, false, "ANALYZED");
  
  //list of the solutions (seen as list of moves to reach solution), and solution difficulty
  priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, AStarNode::CompareFunSolutionsForward> solutions_queue = AStarNode::astar_forward_search(*starting_config_analyzed_game, BRANCHED_NODES_LIMIT);
  
  cout<<"\n# Solutions Found: "<<solutions_queue.size();
  if(solutions_queue.size()>0){
    cout<<"\nEasiest Solution Difficulty: "<<solutions_queue.top().second<<"\n";
    playGamePrinter(*starting_config_analyzed_game, solutions_queue.top().first);
  }
  cout<<"\n";
}

/**
  Prints the solution A* backwards computed (reversing the moves order)
  @param solution .json file name which contains the starting config computed(user pov) and the vector of moves to get from starting config->ending config
*/
void print_expected_forward_solution(pair<string, vector<Action>> solution){
  if(solution.second.size() > 0 && solution.first.compare("") != 0){
    AleaGame forward_game(solution.first, false, "EXPECTED"); 
    playGamePrinter(forward_game, solution.second);
  }
}

/**
  Prints the game board specifying the move done
  @param game instance of the game based on the .json file which contains its configuration 
  @param actions vector of moves to do to get from starting config->ending config
*/
void playGamePrinter(AleaGame game, vector<Action> actions){
  game.print(true);
  for (Action action : actions) {
    cout<<"moving from: "<<action.from<<" | dir: "<<action.dir<<" | weight: "<<action.weight<<" | moveType: "<<action.movement_type<<"\n\n"; 
    if(!game.move(action, false)){
      cout<<"\nlevel_solver.cpp:playGamePrinter: Error while moving from: "<<action.from<<" | dir: "<<action.dir<<"Exiting.\n"; 
      exit(1);
    }
    game.print(true);
  }
}



