#include "astar.h"

AStarNode::AStarNode(AleaGame game) : game(game) { }
AStarNode::AStarNode(AleaGame game, Action action) : game(game), action(action) { }
AStarNode::AStarNode(AleaGame game, Action action, AStarNode* parent) : game(game), action(action), parent(parent) { }
AStarNode::AStarNode(AleaGame game, Action action, AStarNode* parent, int g, int h) : game(game), action(action), parent(parent), g(g), h(h) { 
  f = g + h;
}

bool AStarNode::operator==(const AStarNode& other) const {
  return this->game == other.game;
}

bool AStarNode::operator<(const AStarNode& other) const {
  return f < other.f;
}

bool AStarNode::CompareFun::operator() (const AStarNode* n1, const AStarNode* n2) {
  return n1->f > n2->f;
}

size_t AStarNode::HashFun::operator()(const AStarNode* n) const {
  return AleaGame::HashFun()(n->game);
}

vector<Action> astar_backward_search(AleaGame game, int limit) {
  priority_queue<AStarNode*, vector<AStarNode*>, AStarNode::CompareFun> open;
  unordered_set<AStarNode*, AStarNode::HashFun> open_set;
  unordered_set<AleaGame, AleaGame::HashFun> closed;
  AStarNode* start_node = new AStarNode(game);
  open.push(start_node);
  open_set.insert(start_node);
  vector<Action> solution;
  int evaluated_moves = 0;
  int dead_positions = 0;
  int skipped_moves = 0;
  int branched_nodes = 0;
  while (open.size() > 0) {
    ++branched_nodes;
    AStarNode* current_node = open.top();
    open.pop();
    open_set.erase(current_node);
    closed.insert(current_node->game);
    if (current_node->game.is_valid_starting_configuration()) {
      while (current_node->parent != NULL) {
        solution.push_back(AleaGame::revert_action(current_node->action));
        current_node = current_node->parent;
      }
      break;
    }
    vector<Action> actions = current_node->game.possible_moves();
    for (Action action : actions) {
      AleaGame new_game = AleaGame(current_node->game);
      new_game.move(action);
      if (closed.find(new_game) != closed.end()) {
        ++skipped_moves;
        continue;
      }
      int value = new_game.heuristic_evaluation();
      ++evaluated_moves;
      if (value < 0) {
        ++dead_positions;
        continue;
      }
      AStarNode* neighbor = new AStarNode(new_game, action, current_node, 0, value);
      if (open_set.find(neighbor) == open_set.end()) {
        open.push(neighbor);
        open_set.insert(neighbor);
      }
    }
    if (branched_nodes > limit) break;
  }
  // cout << "Evaluated:" << evaluated_moves << endl;
  // cout << "Dead:"<< dead_positions << endl;
  // cout << "Skipped:"<< skipped_moves << endl;
  // cout << "Branched:"<< branched_nodes << endl;
  return solution;
}

/*
vector<vector<Action>> astar_search_all(AleaGame game, int limit) {
  priority_queue<AStarNode*, vector<AStarNode*>, AStarNode::CompareFun> open;
  unordered_set<AStarNode*, AStarNode::HashFun> open_set;
  unordered_set<AleaGame, AleaGame::HashFun> closed;
  AStarNode* start_node = new AStarNode(game);
  open.push(start_node);
  open_set.insert(start_node);
  vector<vector<Action>> solutions;
  int evaluated_moves = 0;
  int dead_positions = 0;
  int skipped_moves = 0;
  int branched_nodes = 0;
  while (open.size() > 0) {
    ++branched_nodes;
    AStarNode* current_node = open.top();
    open.pop();
    open_set.erase(current_node);
    closed.insert(current_node->game);
    if (current_node->game.win()) {
      vector<Action> solution;
      while (current_node->parent != NULL) {
        solution.push_back(current_node->action);
        current_node = current_node->parent;
      }
      reverse(solution.begin(), solution.end());
      solutions.push_back(solution);
      continue;
    }
    vector<Action> actions = current_node->game.possible_moves();
    for (Action action : actions) {
      AleaGame new_game = AleaGame(current_node->game);
      new_game.move(action);
      if (closed.find(new_game) != closed.end()) {
        ++skipped_moves;
        continue;
      }
      int value = new_game.heuristic_evaluation();
      ++evaluated_moves;
      if (value < 0) {
        ++dead_positions;
        continue;
      }
      AStarNode* neighbor = new AStarNode(new_game, action, current_node, 0, value);
      if (open_set.find(neighbor) == open_set.end()) {
        open.push(neighbor);
        open_set.insert(neighbor);
      }
    }
    if (branched_nodes > limit) break;
  }
  return solutions;
}*/