#ifndef ASTAR_H
#define ASTAR_H

#include "./lib/p2d.h"
#include "./lib/common.h"
#include "alea_game.h"
#include "./lib/white_dice.h"
#include "./lib/red_dice.h"
#include "./lib/yellow_dice.h"
#include "./lib/green_dice.h"
#include "./lib/green_dice.h"
#include "./lib/dice.h"

using namespace std;

class AStarNode {
  public:
    AleaGame game;
    Action action = Action(P2D(-1, -1), P2D(0, 0)); //null action
    AStarNode* parent = NULL;
    double g = 0.00;
    double h = 0.00;
    double f = 0.00;

    AStarNode(AleaGame game);
    AStarNode(AleaGame game, Action action);
    AStarNode(AleaGame game, double g);
    AStarNode(AleaGame game, double g, double h);
    AStarNode(AleaGame game, Action action, AStarNode* parent);
    AStarNode(AleaGame game, Action action, AStarNode* parent, double g, double h);

    bool operator==(const AStarNode& other) const;
    bool operator<(const AStarNode& other) const;

    struct CompareFunBackward {
      bool operator() (AStarNode* n1, AStarNode* n2);
    };

    struct CompareFunForward {
      bool operator() (AStarNode* n1, AStarNode* n2);
    };

    struct HashFun {
      size_t operator()(AStarNode* const&n) const;
    }; 

    struct CompareFunSolutionsForward{
      bool operator() (pair<vector<Action>, double> solution1, pair<vector<Action>, double> solution2);
    };

    static pair<string, vector<Action>> astar_backward_search(AleaGame game, int limit=numeric_limits<int>::max());
    static string printLevel(AleaGame map_configuration, double difficulty);
    static priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, AStarNode::CompareFunSolutionsForward> astar_forward_search(AleaGame game, int limit=numeric_limits<int>::max());   
    static pair<bool, pair<AleaGame, vector<Action>>> find_banal_start_forward_search(AleaGame original_start);
    
  private:
    static bool find_banal_start_calculate_route(vector<Action> &moves, P2D dice_position, int dice_moves, P2D terminal_position, unordered_map<P2D, Dice *, P2D::HashFun> dices);
    static bool terminal_is_disputed(P2D terminal_position, unordered_map<P2D, Dice *, P2D::HashFun> dices);
};


#endif