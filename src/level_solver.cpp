#include "alea_game.h"
#include "astar.h"

pair<string, vector<Action>> start_backward_analysis(char *ending_config_file_name);
void get_solution_number_and_related_difficulty(string starting_config_file_name);
void print_expected_forward_solution(pair<string, vector<Action>> solution);
void playGamePrinter(AleaGame game, vector<Action> actions);

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

pair<string, vector<Action>> start_backward_analysis(char *ending_config_file_name){
  string level_name = "./custom_level_config/";
  level_name.append(ending_config_file_name);
  AleaGame *backward_game = new AleaGame(level_name, true);
	backward_game->print(true);
  return AStarNode::astar_backward_search(*backward_game, BRANCHED_NODES_LIMIT);
}

void get_solution_number_and_related_difficulty(string starting_config_file_name){
  cout<<starting_config_file_name<<endl;
  AleaGame *starting_config_analyzed_game = new AleaGame(starting_config_file_name, false, "ANALYZED");
  priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, AStarNode::CompareFunSolutionsForward> solutions_queue = AStarNode::astar_forward_search(*starting_config_analyzed_game, 500000);
  
  cout<<"\n# Solutions Found: "<<solutions_queue.size();
  if(solutions_queue.size()>0){
    cout<<"\nEasiest Solution Difficulty: "<<solutions_queue.top().second<<"\n";
    playGamePrinter(*starting_config_analyzed_game, solutions_queue.top().first);
  }
  cout<<"\n";
}

void print_expected_forward_solution(pair<string, vector<Action>> solution){
  if(solution.second.size() > 0 && solution.first.compare("") != 0){
    AleaGame forward_game(solution.first, false, "EXPECTED"); 
    playGamePrinter(forward_game, solution.second);
  }
}

void playGamePrinter(AleaGame game, vector<Action> actions){
  game.print(true);
  for (Action action : actions) {
    cout<<"moving from: "<<action.from<<" | dir: "<<action.dir<<" | weight: "<<action.weight<<" | moveType: "<<action.movementType<<"\n\n"; 
    if(!game.move(action, false)){
      cout<<"\nlevel_solver.cpp:playGamePrinter: Error while moving from: "<<action.from<<" | dir: "<<action.dir<<"Exiting.\n"; 
      exit(1);
    }
    game.print(true);
  }
}



