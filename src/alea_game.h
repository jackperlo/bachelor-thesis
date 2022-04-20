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
    AleaGame(json json_dict);
    AleaGame(const char *filename);
    AleaGame(string filename);
    operator string ();
		friend ostream& operator<<(ostream& out, AleaGame game);
    bool operator==(const AleaGame& other) const;
    string read_json(string filename);
    void print(const bool& color=false);
    vector<Action> possible_moves();
    void green_dice_possible_moves(Dice *dice, vector<Action> moves);
    void green_dice_possible_moves_nMoves_gt_zero(Dice *dice, vector<Action> moves);
    void green_dice_possible_moves_being_pushed(Dice *dice, vector<Action> moves);
    void white_dice_possible_moves(Dice *dice, vector<Action> moves);
    void red_dice_possible_moves(Dice *dice, vector<Action> moves);
    void yellow_dice_possible_moves(Dice *dice, vector<Action> moves);
    int remaining_moves() const;
    bool move(const Action& action);
		int move(const P2D pos, const P2D dir, const bool isPushed);
    bool is_valid_starting_configuration();
    static Action revert_action(Action backward_action);
    
    struct HashFun {
			size_t operator()(const AleaGame& game) const;
		};

  private:
    int width, height, total_moves;
    unordered_set<P2D, P2D::HashFun> terminals;
    unordered_map<P2D, Dice*, P2D::HashFun> dices;
    bool is_terminal(const P2D& pos) const;
    bool is_valid_ending_configuration();
    bool has_dice(const P2D& pos) const;
};

#endif