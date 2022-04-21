#include "alea_game.h"
#include "astar.h"

int main(int argc, char *argv[]){ 
  AleaGame *backward_game = new AleaGame("./generated_levels/TrialLevel.json");
	backward_game->print(true);
  pair <string, vector<Action>> solution = astar_backward_search(*backward_game, 50000);
  
  if(solution.second.size() > 0 && solution.first.compare("") != 0){
    AleaGame *forward_game = new AleaGame(solution.first);
    forward_game->print(true);
    for (Action action : solution.second) {
      forward_game->move(action);
      forward_game->print(true);
    }
  }

  return 0;
}




