#include "alea_game.h"
#include "astar.h"

int main(int argc, char *argv[]){ 
  AleaGame *backward_game = new AleaGame("./generated_levels/CustomLevel.json", true);
	backward_game->print(true);
  pair <string, vector<Action>> solution = astar_backward_search(*backward_game, 50000);
  
  if(solution.second.size() > 0 && solution.first.compare("") != 0){
    AleaGame forward_game(solution.first, false);
    forward_game.print(true);
    for (Action action : solution.second) {
      cout<<"\nmoving from: "<<action.from<<" | dir: "<<action.dir<<"\n"; 
      if(!forward_game.move(action, false)){
        cout<<"\nlevel_solver.cpp: Error while moving from: "<<action.from<<" | dir: "<<action.dir<<"Exiting.\n"; 
        exit(1);
      }
      forward_game.print(true);
    }
  }

  return 0;
}




