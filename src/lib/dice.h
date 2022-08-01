#ifndef DICE_H
#define DICE_H

#include "common.h"
#include "cell.h"
#include "p2d.h"

class Dice{
  protected:
    Cell position;
    int nMoves;
    int initial_moves;
    pair<bool, int> virtual move_left(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool is_a_simulation, int movement_type = SIMPLE_MOVE) = 0; 
    pair<bool, int> virtual move_right(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool is_a_simulation, int movement_type = SIMPLE_MOVE) = 0;
    pair<bool, int> virtual move_up(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool is_a_simulation, int movement_type = SIMPLE_MOVE) = 0;
    pair<bool, int> virtual move_down(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool is_a_simulation, int movement_type = SIMPLE_MOVE) = 0;
    pair<bool, int> virtual reverse_move_left(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool is_a_simulationn, int movement_type = SIMPLE_MOVE) = 0;
    pair<bool, int> virtual reverse_move_right(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool is_a_simulationn, int movement_type = SIMPLE_MOVE) = 0;
    pair<bool, int> virtual reverse_move_up(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool is_a_simulationn, int movement_type = SIMPLE_MOVE) = 0;
    pair<bool, int> virtual reverse_move_down(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> &dices, bool is_a_simulationn, int movement_type = SIMPLE_MOVE) = 0;
    int check_arrival_cell_is_empty(int x, int y, unordered_map<P2D, Dice *, P2D::HashFun> dices); //returns -1 if it's Empty
    bool make_move(int x, int y, int nMovesDone, unordered_map<P2D, Dice *, P2D::HashFun> &dices);
    string string_to_lower(string input_string);

  public:
    Dice(Cell position, int nMoves, int initial_moves);
    Dice();
    string virtual print_dice_to_string (bool print_with_initial_moves) = 0;
    bool operator==(Dice *other_dice);
    void set_position(Cell position);
    Cell get_position() const;
    int get_n_moves();
    int get_initial_moves();
    void print_dice();
    pair<bool, int> move(string direction, unordered_map<P2D, Dice *, P2D::HashFun> &dices, char const * caller_name, bool is_a_simulation, int movement_type = SIMPLE_MOVE);
    pair<bool, int> virtual reverse_move(string direction, unordered_map<P2D, Dice *, P2D::HashFun> &dices, char const * caller_name, bool is_a_simulation, int movement_type = SIMPLE_MOVE) = 0;
    string virtual get_actual_type() = 0;
    int virtual get_actual_type_int() = 0;
};

#endif