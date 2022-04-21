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
		double g = 0;
		double h = 0;
		double f = 0;

		AStarNode(AleaGame game);
		AStarNode(AleaGame game, Action action);
		AStarNode(AleaGame game, double g);
		AStarNode(AleaGame game, Action action, AStarNode* parent);
		AStarNode(AleaGame game, Action action, AStarNode* parent, double g, double h);

		bool operator==(const AStarNode& other) const;
		bool operator<(const AStarNode& other) const;

		struct CompareFun {
			bool operator() (AStarNode* n1, AStarNode* n2);
		};

		struct HashFun {
			size_t operator()(AStarNode* const&n) const;
		}; 
};

pair<string, vector<Action>> astar_backward_search(AleaGame game, int limit=numeric_limits<int>::max());
string printLevel(AleaGame map_configuration, double difficulty);
//vector<vector<Action>> astar_search_all(AleaGame game, int limit=numeric_limits<int>::max());

#endif