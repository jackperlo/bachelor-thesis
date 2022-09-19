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
    double heuristic_value = 0.00;

    ~AleaGame();
    AleaGame();
    AleaGame(unordered_set<P2D, P2D::HashFun> terminals, unordered_map<P2D, Dice*, P2D::HashFun> dices);
    AleaGame(json json_dict, bool is_backward, string type, bool calculate_x_y = false);
    AleaGame(string filename, bool is_backward, string type = "", bool calculate_x_y = false);
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

    double calculate_heuristic_value();
    Action move_forward_stats(vector<pair<int, int>> &excluding_heuristic_possible_moves_activation, P2D from_pos, pair<P2D, Dice *> dice, P2D dir, pair<bool, int> move_results, int movement_type);
    Action green_dice_move_forward_stats(P2D from_pos, pair<P2D, Dice *> dice, P2D dir, pair<bool, int> move_results, pair<int, int> &green_heuristic_stats);
    Action white_dice_move_forward_stats(P2D from_pos, pair<P2D, Dice *>dice, P2D dir, pair<int, int> &white_heuristic_stats, int movement_type);
    Action red_dice_move_forward_stats(P2D from_pos, pair<P2D, Dice *> dice, P2D dir, pair<int, int> &red_heuristic_stats, int movement_type);
    Action yellow_dice_move_forward_stats(P2D from_pos, pair<P2D, Dice *> ice, P2D dir, pair<bool, int> move_results, pair<int, int> &yellow_heuristic_stats);
    P2D get_new_dice_position(P2D old_position, P2D dir, int n_cells);

    bool move(const Action& action, bool is_moving_backward);
		pair<bool, int> move(const P2D pos, const P2D dir, const int movement_type, bool is_moving_backward);
    
    int remaining_moves() const;
    bool is_valid_starting_configuration_backward_search();
    bool is_valid_ending_configuration_forward_search();
    vector<pair<AleaGame, vector<Action>>> find_banal_starts_forward_search_wrapper();
    bool banal_start_already_found(pair<AleaGame, vector<Action>> banal_config, vector<pair<AleaGame, vector<Action>>> banal_config_vector);

    static Action revert_action(Action backward_action);

    struct HashFun {
			size_t operator()(const AleaGame& game) const;
		};

  private:
    void generate_map_for_backward_movements(json json_dict);
    void generate_map_for_expected_forward_movements_given_x_y(json json_dict, string type);
    void generate_map_for_expected_forward_movements(json json_dict);
    
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
    
    bool check_dice_could_be_pushed(P2D dice_position, int dice_moves);
};

#endif