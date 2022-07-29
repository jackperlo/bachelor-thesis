/**
  This contains the A* Backward algorithm and the A* Forward algorithm
  @file astar.h astar.cpp
  @authors Mirko Polato, Giacomo Perlo
*/
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
    Action action = Action::null_action; 
    shared_ptr<AStarNode> parent = NULL;
    double g = 0.00;
    double h = 0.00;
    double distance_from_closer_terminal_weight = 0.00;
    double f = 0.00;

    AStarNode(AleaGame game);
    AStarNode(AleaGame game, Action action);
    AStarNode(AleaGame game, double g);
    AStarNode(AleaGame game, double g, double h);
    AStarNode(AleaGame game, Action action, shared_ptr<AStarNode> parent);
    AStarNode(AleaGame game, Action action, shared_ptr<AStarNode> parent, double g, double h, double distance_from_closer_terminal_weight = 0.00);

    bool operator==(const AStarNode& other) const;
    AStarNode& operator=(shared_ptr<AStarNode>);
    bool operator<(const AStarNode& other) const;
    friend ostream& operator<<(ostream& out, shared_ptr<AStarNode> node);

    struct CompareFunBackward {
      bool operator() (shared_ptr<AStarNode> n1, shared_ptr<AStarNode> n2);
    };

    struct CompareFunForward {
      bool operator() (shared_ptr<AStarNode> n1, shared_ptr<AStarNode> n2);
    };

    struct HashFun {
      size_t operator()(shared_ptr<AStarNode> const&n) const;
    }; 

    struct CompareFunSolutionsForward{
      bool operator() (pair<vector<Action>, double> solution1, pair<vector<Action>, double> solution2);
    };

    static pair<string, vector<Action>> astar_backward_search(AleaGame game, int limit=numeric_limits<int>::max());
    static priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, AStarNode::CompareFunSolutionsForward> astar_forward_search(AleaGame original_game, double upper_bound, int limit=numeric_limits<int>::max());   
    static string printLevel(AleaGame map_configuration, double difficulty);

  private:
    void backtrace(shared_ptr<AStarNode> parent_node, int &sequentially_skipped_nodes, int &depth, int &siblings_number, priority_queue<shared_ptr<AStarNode>, vector<shared_ptr<AStarNode>>, AStarNode::CompareFunForward> &open, unordered_set<shared_ptr<AStarNode>, AStarNode::HashFun> &open_set, int &evaluated_moves, vector<pair<int, int>> &excluding_heuristic_possible_moves_activation);
    static int get_siblings(shared_ptr<AStarNode> current_node, priority_queue<shared_ptr<AStarNode>, vector<shared_ptr<AStarNode>>, AStarNode::CompareFunForward> &open, unordered_set<shared_ptr<AStarNode>, AStarNode::HashFun> &open_set, int &evaluated_moves, /*int depth,*/ vector<pair<int, int>> &excluding_heuristic_possible_moves_activation);
    static priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, AStarNode::CompareFunSolutionsForward> astar_forward(AleaGame game, int limit, double *difficulty, double upper_bound, pair<AleaGame, vector<Action>> banal_search = make_pair(AleaGame(), vector<Action>()));
    static priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, AStarNode::CompareFunSolutionsForward> merge_priority_queues(priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, AStarNode::CompareFunSolutionsForward> source1, priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, AStarNode::CompareFunSolutionsForward> source2);
};


#endif