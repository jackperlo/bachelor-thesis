#ifndef ASTAR_H
#define ASTAR_H

#include "./lib/p2d.h"
#include "./lib/common.h"
#include "alea_game.h"

using namespace std;

class AStarNode {
	public:

		AleaGame game;
		Action action = Action(P2D(-1, -1), P2D(0, 0)); //null action
		AStarNode* parent = NULL;
		int g = 0;
		int h = 0;
		int f = 0;

		AStarNode(AleaGame game);
		AStarNode(AleaGame game, Action action);
		AStarNode(AleaGame game, Action action, AStarNode* parent);
		AStarNode(AleaGame game, Action action, AStarNode* parent, int g, int h);

		bool operator==(const AStarNode& other) const;
		bool operator<(const AStarNode& other) const;

		struct CompareFun {
			bool operator() (const AStarNode* n1, const AStarNode* n2);
		};

		struct HashFun {
			size_t operator()(const AStarNode* n) const;
		};
};

vector<Action> astar_backward_search(AleaGame game, int limit=numeric_limits<int>::max());
//vector<vector<Action>> astar_search_all(AleaGame game, int limit=numeric_limits<int>::max());

#endif