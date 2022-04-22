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
    AleaGame(json json_dict, bool isBackward);
    AleaGame(const char *filename, bool isBackward);
    AleaGame(string filename, bool isBackward);
    AleaGame(const AleaGame& game);
    operator string ();
		friend ostream& operator<<(ostream& out, AleaGame game);
    bool operator==(const AleaGame& other) const;
    string read_json(string filename);
    void print(const bool& color=false);
    vector<Action> possible_moves();
    void green_dice_possible_moves(Dice *dice, vector<Action> &moves);
    void green_dice_possible_moves_nMoves_gt_zero(Dice *dice, vector<Action> &moves);
    void green_dice_possible_moves_being_pushed(Dice *dice, vector<Action> &moves);
    void white_dice_possible_moves(Dice *dice, vector<Action> &moves);
    void red_dice_possible_moves(Dice *dice, vector<Action> &moves);
    void yellow_dice_possible_moves(Dice *dice, vector<Action> &moves);
    int remaining_moves() const;
    bool move(const Action& action, bool isMovingBackward);
		bool move(const P2D pos, const P2D dir, const int isPushed, bool isMovingBackward);
    bool is_valid_starting_configuration();
    static Action revert_action(Action backward_action);
    //int heuristic_evaluation();
    void show_map();
    static void show_moves(vector<Action> moves);

    struct HashFun {
			size_t operator()(const AleaGame& game) const;
		};

  private:
    void generateMapForBackwardMovements(json json_dict);
    void generateMapForForwardMovements(json json_dict);
    bool is_terminal(const P2D& pos) const;
    bool is_valid_ending_configuration();
    bool has_dice(const P2D& pos) const;
};

#endif