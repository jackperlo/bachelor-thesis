/**
  This contains the A* Backward algorithm and the RBFS Forward algorithm
  @file search_algorithms.h search_algorithms.cpp
  @authors Mirko Polato, Giacomo Perlo
*/
#ifndef SEARCH_ALGORITHMS_H
#define SEARCH_ALGORITHMS_H

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

class Node{
  public:
    AleaGame game;
    Action action = Action::null_action; 
    shared_ptr<Node> parent = NULL;
    double g = 0.00;
    double h = 0.00;
    double f = 0.00;

    ~Node();
    Node(AleaGame game);
    Node(AleaGame game, Action action);
    Node(AleaGame game, double g);
    Node(AleaGame game, double g, double h);
    Node(AleaGame game, Action action, shared_ptr<Node> parent);
    Node(AleaGame game, Action action, shared_ptr<Node> parent, double g, double h);

    bool operator==(const Node& other) const;
    Node& operator=(shared_ptr<Node>);
    bool operator<(const Node& other) const;
    friend ostream& operator<<(ostream& out, shared_ptr<Node> node);

    struct CompareFunBackward {
      bool operator() (shared_ptr<Node> n1, shared_ptr<Node> n2);
    };

    struct CompareFunForward {
      bool operator() (shared_ptr<Node> n1, shared_ptr<Node> n2);
    };

    struct HashFun {
      size_t operator()(shared_ptr<Node> const&n) const;
    }; 

    struct CompareFunSolutionsForward{
      bool operator() (pair<vector<Action>, double> solution1, pair<vector<Action>, double> solution2);
    };

    static pair<string, vector<Action>> astar_backward_search(AleaGame game, int limit=numeric_limits<int>::max());    
    static priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, Node::CompareFunSolutionsForward> a_star_variant_forward_search(AleaGame original_game, double upper_bound=numeric_limits<int>::max(), int limit=numeric_limits<int>::max());   
    static string printLevel(AleaGame map_configuration, double difficulty);

  private:
    static priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, Node::CompareFunSolutionsForward> start_multi_threading(AleaGame original_game, vector<pair<AleaGame, vector<Action>>> banal_search_results, priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, Node::CompareFunSolutionsForward> res, double upper_bound);
    static int a_star_variant_get_siblings(shared_ptr<Node> current_node, priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, Node::CompareFunForward> &open, unordered_set<shared_ptr<Node>, Node::HashFun> &open_set, int &evaluated_moves, vector<pair<int, int>> &excluding_heuristic_possible_moves_activation);
    static priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, Node::CompareFunSolutionsForward> a_star_variant_forward(pair<AleaGame, vector<Action>> banal_search, double upper_bound, int thread_name=0);
    static priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, Node::CompareFunSolutionsForward> merge_priority_queues(priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, Node::CompareFunSolutionsForward> source1, priority_queue<pair<vector<Action>, double>, vector<pair<vector<Action>, double>>, Node::CompareFunSolutionsForward> source2);
};


#endif