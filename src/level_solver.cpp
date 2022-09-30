/**
  Generates a starting level config using A* Backward. Tries to resolve the level using A* Variant forward
  @file level_solver.cpp
  @author Giacomo Perlo
*/
#include "alea_game.h"
#include "search_algorithms.h"
#include <string>

void print_menu();
pair<string, vector<Action>> start_backward_analysis(string ending_config_file_name);
pair<string, vector<Action>> start_backward_auto_level_generation();
void start_forward_analysis(string starting_config_file_name, bool calculate_x_y);
void print_expected_forward_solution(pair<string, vector<Action>> solution);
void playGamePrinter(AleaGame game, vector<Action> actions);

//controls operation of the program
int main(){ 

  int choice = -1;
  pair<string, vector<Action>> res;
  string level_name = "";
  string level_path = "";

  cout<<FGCYANSTART<<"\nWelcome to Alea Game Level Generator & Solver.\n\n"<<FGRESET;
  #ifdef DEBUG
  cout<<FGCYANSTART<<"\nDEBUG MODE\n"<<FGRESET;
  #endif
  do{
    print_menu();

    choice = -1;
    cin.clear();
    cin >> choice;
    switch(choice){
      case 0:
        cout<<"\nByee! x\n\n"; 
        exit(0);
      case 1:
        level_name = "";
        cout<<"\n./backward_levels/";
        cin.clear();
        cin >> level_name;
        res = start_backward_analysis(level_name);
        if(res.first.compare("") != 0)
          cout<<endl<<res.first<<endl;
        print_expected_forward_solution(res);  
        break;
      case 2:
        level_path = "./forward_levels/";
        level_name = "";
        cout<<"\n./forward_levels/";
        cin.clear();
        cin >> level_name;
        level_path.append(level_name);
        start_forward_analysis(level_path, true);
        break;
      case 3:
        level_name = "";
        cout<<"\n./backward_levels/";
        cin.clear();
        cin >> level_name;
        res = start_backward_analysis(level_name);
        if(res.first.compare("") != 0){
          cout<<endl<<res.first<<endl;
          start_forward_analysis(res.first, false);
          print_expected_forward_solution(res);  
        }
        break;
      case 4:
        res = start_backward_auto_level_generation();
        if(res.first.compare("") != 0){
          cout<<endl<<res.first<<endl;
          start_forward_analysis(res.first, false);
          print_expected_forward_solution(res);  
        }
        break;
      default:
        cout<<endl<<"Selection not valid. Try Again."<<endl;
        break;
    }
  }while(choice != 0);

  return 0;
}

void print_menu(){
  cout<<FGCYANSTART<<"==============================Menu================================="<<endl;
  cout<<"|| Manually Submitted Levels\t\t\t\t\t ||"<<endl;
  cout<<"||\t1. GENERATE a Level from an Ending Configuration\t ||"<<endl;
  cout<<"||\t2. SOLVE a Level from a Starting Configuration\t\t ||"<<endl;
  cout<<"||\t3. GENERATE & SOLVE a Level from an Ending Configuration ||"<<endl;
  cout<<"|| Auto Generated Levels    \t\t\t\t\t ||"<<endl;
  cout<<"||\t4. AUTO GENERATE & SOLVE a Level\t\t\t ||"<<endl;
  cout<<"|| 0. Exit\t\t\t\t\t\t\t ||"<<endl;
  cout<<"=================================================================="<<endl;
  cout<<"Make your choice: "<<FGRESET;
}

/**
  Returns a possible starting configuration(user pov) using A* backward and the moves done to get there
  @param ending_config_file_name .json file name which contains the ending configuration(user pov) from which A* starts 
  @return starting configuration file name, moves (A* used on the contrary) to get from starting config->ending config
*/
pair<string, vector<Action>> start_backward_analysis(string ending_config_file_name){
  string level_name = "./backward_levels/";
  level_name.append(ending_config_file_name);
  AleaGame backward_game(level_name, true);
  cout<<"Starting Configuration (user end)"<<endl;
	backward_game.print(true);
  return Node::astar_backward_search(backward_game, BRANCHED_NODES_LIMIT);
}

pair<string, vector<Action>> start_backward_auto_level_generation(){
  AleaGame auto_backward_game(true);
  cout<<"Starting Configuration (user end)"<<endl;
  auto_backward_game.print(true);
  return Node::astar_backward_search(auto_backward_game, BRANCHED_NODES_LIMIT);
}

/**
  Prints the number of solution found using A* Variant forward(starting config->ending config, user pov) and show the moves of the easiest one(first position, being a priority queue)
  @param starting_config_file_name .json file name which contains the starting configuration(user pov) which A* backwards computed
*/
void start_forward_analysis(string starting_config_file_name, bool calculate_x_y){
  AleaGame starting_config_analyzed_game(starting_config_file_name, false, "ANALYZED", calculate_x_y);
  starting_config_analyzed_game.print(true, true);
  
  //list of the solutions (seen as list of moves to reach solution), and solution difficulty
  priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, Node::CompareFunSolutionsForward> solutions_queue = Node::a_star_variant_forward_search(starting_config_analyzed_game/*, BRANCHED_NODES_LIMIT*/);
  if(solutions_queue.size()>0) cout<<FGGREENSTART<<"\n=================SOLUTION=====================\n"<<FGRESET;
  cout<<"Number of Solutions Found: "<<solutions_queue.size();
  if(solutions_queue.size()>0){
    cout<<"\nEasiest Solution Difficulty: "<<solutions_queue.top().second<<"\n";
    playGamePrinter(starting_config_analyzed_game, solutions_queue.top().first);
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
    cout<<"moving from: "<<action.from<<" | dir: "<<action.dir<<" | heuristic value: "<<action.heuristic_value<<" | moveType: "<<action.movement_type<<"\n\n"; 
    if(!game.move(action, false)){
      cout<<"\nlevel_solver.cpp:playGamePrinter: Error while moving from: "<<action.from<<" | dir: "<<action.dir<<"Exiting.\n"; 
      exit(1);
    }
    game.print(true);
  }
}