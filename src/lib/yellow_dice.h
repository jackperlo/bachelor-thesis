#ifndef YELLOW_DICE_H
#define YELLOW_DICE_H

#include "common.h"
#include "dice.h"
#include "cell.h"

class YellowDice : public Dice{
  public:
    YellowDice(Cell position, int nMoves, int initial_moves);
    YellowDice();
    YellowDice(const YellowDice &yd1); //copying constructor, invoked in situation as: YellowDice yd1 = yd2.
    string print_dice_to_string (bool print_with_initial_moves) override;
    string get_actual_type() override;
    int get_actual_type_int() override;
    pair<bool, int> reverse_move(string direction, unordered_map<P2D, Dice *, P2D::HashFun> &dices, char const * caller_name, bool is_a_simulation, int movement_type = SIMPLE_MOVE) override;

  protected:
    pair<bool, int> call4reverse_move(string direction, unordered_map<P2D, Dice *, P2D::HashFun> &dices, char const * caller_name, bool is_a_simulation, int movement_type = SIMPLE_MOVE);
    pair<bool, int> move_left(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool is_a_simulation, int movement_type) override;
    pair<bool, int> move_right(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool is_a_simulation, int movement_type) override;
    pair<bool, int> move_up(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool is_a_simulation, int movement_type) override;
    pair<bool, int> move_down(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool is_a_simulation, int movement_type) override;
    pair<bool, int> reverse_move_left(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool is_a_simulation) override;
    pair<bool, int> reverse_move_right(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool is_a_simulation) override;
    pair<bool, int> reverse_move_up(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool is_a_simulation) override;
    pair<bool, int> reverse_move_down(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool is_a_simulation) override;
};

#endif