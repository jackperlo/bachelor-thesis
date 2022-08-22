/**
  This class contains the work logic of AleaGame 
  @file astar.h astar.cpp
  @authors Mirko Polato, Giacomo Perlo
*/
#ifndef ALEA_GAME_H
#define ALEA_GAME_H

#include "lib/common.h"
#include "./lib/white_dice.h"
#include "./lib/red_dice.h"
#include "./lib/yellow_dice.h"
#include "./lib/green_dice.h"
#include "./lib/p2d.h"

using namespace std;

class AleaGame{
  public:
    unordered_set<P2D, P2D::HashFun> terminals;
    unordered_map<P2D, Dice*, P2D::HashFun> dices;
    Action last_action_performed;
    double difficulty = 0.00;

    ~AleaGame();
    AleaGame();
    AleaGame(json json_dict, bool is_backward, string type);
    AleaGame(string filename, bool is_backward, string type = "");
    AleaGame(const AleaGame& game);

		friend ostream& operator<<(ostream& out, pair<bool, AleaGame> pair);
    bool operator==(const AleaGame& other) const;
    AleaGame& operator=(const AleaGame&);
    string read_json(string filename);

    void print(const bool& color=false, bool print_init_moves_number = false);
    void show_map();
    static void show_moves(vector<Action> moves);

    vector<Action> possible_moves_backward();
    void green_dice_possible_moves_backward(Dice *dice, vector<Action> &moves);
    void green_dice_possible_moves_nMoves_gt_zero_backward(Dice *dice, vector<Action> &moves);
    void green_dice_possible_moves_being_pushed_backward(Dice *dice, vector<Action> &moves);
    void white_dice_possible_moves_backward(Dice *dice, vector<Action> &moves);
    void red_dice_possible_moves_backward(Dice *dice, vector<Action> &moves);
    void yellow_dice_possible_moves_backward(Dice *dice, vector<Action> &moves);
    
    vector<Action> possible_moves_forward(vector<pair<int, int>> &excluding_heuristic_possible_moves_activation);
    void green_dice_possible_moves_forward(Dice *dice, vector<Action> &moves, pair<int, int> &green_heuristic_stats);
    void white_dice_possible_moves_forward(Dice *dice, vector<Action> &moves, pair<int, int> &white_heuristic_stats);
    void red_dice_possible_moves_forward(Dice *dice, vector<Action> &moves, pair<int, int> &red_heuristic_stats);
    void yellow_dice_possible_moves_forward(Dice *dice, vector<Action> &moves, pair<int, int> &yellow_heuristic_stats);

    bool move(const Action& action, bool is_moving_backward);
		bool move(const P2D pos, const P2D dir, const int isPushed, bool is_moving_backward);
    
    int remaining_moves() const;
    bool is_valid_starting_configuration_backward_search();
    bool is_valid_ending_configuration_forward_search();
    vector<pair<AleaGame, vector<Action>>> find_banal_starts_forward_search_wrapper();
    bool banal_start_already_found(pair<AleaGame, vector<Action>> banal_config, vector<pair<AleaGame, vector<Action>>> banal_config_vector);

    static Action revert_action(Action backward_action);

    struct HashFun {
			int operator()(const AleaGame& game) const;
		};

  private:
    void generateMapForBackwardMovements(json json_dict);
    void generateMapForExpectedForwardMovements(json json_dict, string type);
    static string print_aleagame_to_string (pair<bool, AleaGame> pair);
    bool is_terminal(const P2D& pos) const;
    bool is_valid_ending_configuration_backward_search();
    bool has_dice(const P2D& pos) const;
    int calculate_distance_from_closer_terminal(P2D dice_position);
    bool find_banal_start_calculate_route(vector<Action> &moves, pair<P2D, Dice*> dice, int dice_moves, P2D terminal_position, unordered_map<P2D, Dice *, P2D::HashFun> dices);
    static bool terminal_is_disputed(P2D terminal_position, unordered_map<P2D, Dice *, P2D::HashFun> dices);
    static vector<pair<P2D, Dice *>> disputer_dices(P2D terminal_position, unordered_map<P2D, Dice *, P2D::HashFun> dices);
    static bool disputed_is_assigned(P2D terminal, vector<std::pair<P2D, Dice *>> disputer_dices);
    pair<AleaGame, vector<Action>> find_banal_starts_forward_search(pair<AleaGame, vector<Action>> previous_game_actions);
    bool check_dice_could_be_pushed(Dice *dice);
};

#endif