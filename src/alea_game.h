#ifndef ALEA_GAME_H
#define ALEA_GAME_H

#include "lib/common.h"
#include "./lib/white_dice.h"
#include "./lib/red_dice.h"
#include "./lib/yellow_dice.h"
#include "./lib/green_dice.h"
#include "./lib/p2d.h"

class AleaGame{
  public:
    unordered_set<P2D, P2D::HashFun> terminals;
    unordered_map<P2D, Dice*, P2D::HashFun> dices;
    Action last_action_performed;

    AleaGame();
    AleaGame(json json_dict, bool isBackward, string type);
    AleaGame(string filename, bool isBackward, string type = "");
    AleaGame(const AleaGame& game);

    operator string ();
		friend ostream& operator<<(ostream& out, AleaGame game);
    bool operator==(const AleaGame& other) const;
    AleaGame& operator=(const AleaGame&);
    string read_json(string filename);

    void print(const bool& color=false);
    void show_map();
    static void show_moves(vector<Action> moves);

    vector<Action> possible_moves_backward();
    void green_dice_possible_moves_backward(Dice *dice, vector<Action> &moves);
    void green_dice_possible_moves_nMoves_gt_zero_backward(Dice *dice, vector<Action> &moves);
    void green_dice_possible_moves_being_pushed_backward(Dice *dice, vector<Action> &moves);
    void white_dice_possible_moves_backward(Dice *dice, vector<Action> &moves);
    void red_dice_possible_moves_backward(Dice *dice, vector<Action> &moves);
    void yellow_dice_possible_moves_backward(Dice *dice, vector<Action> &moves);
    
    vector<Action> possible_moves_forward();
    void green_dice_possible_moves_forward(Dice *dice, vector<Action> &moves);
    void white_dice_possible_moves_forward(Dice *dice, vector<Action> &moves);
    void red_dice_possible_moves_forward(Dice *dice, vector<Action> &moves);
    void yellow_dice_possible_moves_forward(Dice *dice, vector<Action> &moves);

    bool move(const Action& action, bool isMovingBackward);
		bool move(const P2D pos, const P2D dir, const int isPushed, bool isMovingBackward);
    
    int remaining_moves() const;
    bool is_valid_starting_configuration_backward_search();
    bool is_valid_ending_configuration_forward_search();
    pair<bool, pair<AleaGame, vector<Action>>> find_banal_start_forward_search();

    static Action revert_action(Action backward_action);

    struct HashFun {
			size_t operator()(const AleaGame& game) const;
		};

  private:
    void generateMapForBackwardMovements(json json_dict);
    void generateMapForExpectedForwardMovements(json json_dict, string type);
    bool is_terminal(const P2D& pos) const;
    bool is_valid_ending_configuration_backward_search();
    bool has_dice(const P2D& pos) const;
    double calculate_distance_from_closer_terminal(P2D dice_position);
    static bool find_banal_start_calculate_route(vector<Action> &moves, P2D dice_position, int dice_moves, P2D terminal_position, unordered_map<P2D, Dice *, P2D::HashFun> dices);
    static bool terminal_is_disputed(P2D terminal_position, unordered_map<P2D, Dice *, P2D::HashFun> dices);
};

#endif