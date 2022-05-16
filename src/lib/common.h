#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <unordered_set>
#include <queue>
#include <stack>
#include "json.hpp"

#define BGGRAY "\x1b[48;2;50;50;50m \x1b[0m"
#define BGWHT(n) "\x1b[48;2;255;255;255m\x1b[38;2;0;0;0m" + to_string(n) + "\x1b[0m\x1b[0m"
#define BGRED(n) "\x1b[48;2;255;0;0m\x1b[38;2;0;0;0m" + to_string(n) + "\x1b[0m\x1b[0m"
#define BGYEL(n) "\x1b[48;2;255;255;0m\x1b[38;2;0;0;0m" + to_string(n) + "\x1b[0m\x1b[0m"
#define BGGRE(n) "\x1b[48;2;0;255;0m\x1b[38;2;0;0;0m" + to_string(n) + "\x1b[0m\x1b[0m"
#define MAX(a, b) a > b ? a : b
#define MIN(a, b) a < b ? a : b

#define SIMPLE_MOVE_BACKWARD 0.01
#define JUMPING_MOVE_BACKWARD 1.00
#define PUSHED_MOVE_BACKWARD 1.00

#define SIMPLE_MOVE_FORWARD 0.01
#define JUMPING_MOVE_FORWARD 1.00
#define PUSHED_MOVE_FORWARD 1.00

#define WHITE_DICE_EXCLUDE_MOVE_FORWARD_HEURISTICS(nMoves) ((nMoves-1)*2)+1
#define RED_DICE_EXCLUDE_MOVE_FORWARD_HEURISTICS(nMoves) nMoves-1

#define BRANCHED_NODES_LIMIT 50000

#define NO_MOVE {false, 0}
#define MOVE_BY_1 {true, 1}
#define JUMP_BY_1 {true, 2}

using namespace std;

using json = nlohmann::json;

extern int TOTAL_MOVES;
extern int MAP_WIDTH;
extern int MAP_HEIGHT;

#endif