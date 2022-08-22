#ifndef GREEN_DICE_H
#define GREEN_DICE_H

#include "common.h"
#include "dice.h"
#include "cell.h"

class GreenDice : public Dice{
  public:
    ~GreenDice();
    GreenDice(Cell position, int nMoves, int initial_moves);
    GreenDice();
    string print_dice_to_string (bool print_with_initial_moves) override;
    GreenDice(const GreenDice &gd1); //copying constructor, invoked in situation as: GreenDice gd1 = gd2.
    string get_actual_type() override;
    int get_actual_type_int() override;
    pair<bool, int> reverse_move(string direction, unordered_map<P2D, Dice *, P2D::HashFun> &dices, char const * caller_name, bool is_a_simulation, int movement_type = SIMPLE_MOVE) override;

  protected:
    pair<bool, int> move_left(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool is_a_simulation, int movement_type) override;
    pair<bool, int> move_right(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool is_a_simulation, int movement_type) override;
    pair<bool, int> move_up(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool is_a_simulation, int movement_type) override;
    pair<bool, int> move_down(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool is_a_simulation, int movement_type) override;
    pair<bool, int> reverse_move_left(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool is_a_simulationn, int movement_type = SIMPLE_MOVE) override;
    pair<bool, int> reverse_move_right(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool is_a_simulationn, int movement_type = SIMPLE_MOVE) override;
    pair<bool, int> reverse_move_up(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool is_a_simulationn, int movement_type = SIMPLE_MOVE) override;
    pair<bool, int> reverse_move_down(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool is_a_simulationn, int movement_type = SIMPLE_MOVE) override;
};

#endif