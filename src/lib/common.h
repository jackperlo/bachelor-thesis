#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <random>
#include <bits/stdc++.h>
#include <typeinfo>
#include <string>
#include <assert.h>
#include "json.hpp"

#define BGGRAY "\x1b[48;2;50;50;50m \x1b[0m"
#define BGWHT(n) "\x1b[48;2;255;255;255m\x1b[38;2;0;0;0m" + to_string(n) + "\x1b[0m\x1b[0m"
#define BGRED(n) "\x1b[48;2;255;0;0m\x1b[38;2;0;0;0m" + to_string(n) + "\x1b[0m\x1b[0m"
#define BGYEL(n) "\x1b[48;2;255;255;0m\x1b[38;2;0;0;0m" + to_string(n) + "\x1b[0m\x1b[0m"
#define BGGRE(n) "\x1b[48;2;0;255;0m\x1b[38;2;0;0;0m" + to_string(n) + "\x1b[0m\x1b[0m"
#define MAX(a, b) a > b ? a : b
#define MIN(a, b) a < b ? a : b

#define SIMPLE_MOVE 0.01
#define JUMPING_MOVE 1
#define PUSHED_MOVE 1

#define NO_MOVE {false, 0}
#define MOVE_BY_1 {true, 1}
#define JUMP_BY_1 {true, 2}

using namespace std;

using json = nlohmann::json;

extern int TOTAL_MOVES;
extern int MAP_WIDTH;
extern int MAP_HEIGHT;

#endif