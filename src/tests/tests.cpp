// Copyright 2009 Google Inc. All Rights Reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#include "gtest/gtest.h"

#include "../lib/common.h"
#include "../lib/white_dice.h"
#include "../lib/red_dice.h"
#include "../lib/yellow_dice.h"
#include "../lib/green_dice.h"
#include "../lib/cell.h"
#include "../lib/p2d.h"
#include <assert.h>

TEST(oneWhiteDice, move_left0Moves){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      WhiteDice wd(c, 0, 0, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c.get_x(), c.get_y()), &wd));
      EXPECT_FALSE(dices.at(P2D(i, j))->move("LEFT", dices, __func__, 0).first);
      dices.clear();
    }
  }
}

TEST(twoWhiteDices_PushingEachOther0Moves, move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i+2);
      c2.setY(j);
      WhiteDice wd1(c1, 0, 0, P2D::neutral_p2d);
      WhiteDice wd2(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &wd2));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &wd1));
      EXPECT_TRUE(dices.at(P2D(i+2, j))->move("LEFT", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      dices.clear();
    }
  }
}

TEST(oneWhiteDice, move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      WhiteDice wd(c, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c.get_x(), c.get_y()), &wd));
      EXPECT_TRUE(dices.at(P2D(i, j))->move("LEFT", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i-1, j))->get_position().get_x(), i-1);
      dices.clear();
    }
  }
}

TEST(twoWhiteDices_PushingEachOther, move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i+2);
      c2.setY(j);
      WhiteDice wd1(c1, 1, 1, P2D::neutral_p2d);
      WhiteDice wd2(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &wd2));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &wd1));
      EXPECT_TRUE(dices.at(P2D(i+2, j))->move("LEFT", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      dices.clear();
    }
  }
}

TEST(oneWhiteDice, move_right0Moves){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      WhiteDice wd(c, 0, 0, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c.get_x(), c.get_y()), &wd));
      EXPECT_FALSE(dices.at(P2D(i, j))->move("RIGHT", dices, __func__, 0).first);
      dices.clear();
    }
  }
}

TEST(twoWhiteDices_PushingEachOther0Moves, move_right){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      WhiteDice wd1(c1, 1, 1, P2D::neutral_p2d);
      WhiteDice wd2(c2, 0, 0, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &wd2));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &wd1));
      EXPECT_TRUE(dices.at(P2D(i, j))->move("RIGHT", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i+2, j))->get_position().get_x(), i+2);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      dices.clear();
    }
  }
}

TEST(oneWhiteDice, move_right){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c.setX(i);
      c.setY(j);
      WhiteDice wd(c, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c.get_x(), c.get_y()), &wd));
      EXPECT_TRUE(dices.at(P2D(i, j))->move("RIGHT", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      dices.clear();
    }
  }
}

TEST(twoWhiteDices_PushingEachOther, move_right){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      WhiteDice wd1(c1, 1, 1, P2D::neutral_p2d);
      WhiteDice wd2(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &wd2));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &wd1));
      EXPECT_TRUE(dices.at(P2D(i, j))->move("RIGHT", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i+2, j))->get_position().get_x(), i+2);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      dices.clear();
    }
  }
}

TEST(oneWhiteDice0Moves, move_up){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 1; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      WhiteDice wd(c, 0, 0, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c.get_x(), c.get_y()), &wd));
      EXPECT_FALSE(dices.at(P2D(i, j))->move("up", dices, __func__, 0).first);
      dices.clear();
    }
  }
}

TEST(twoWhiteDices_PushingEachOther0Moves, move_up){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j+2);
      WhiteDice wd1(c1, 0, 0, P2D::neutral_p2d);
      WhiteDice wd2(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &wd2));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &wd1));
      EXPECT_TRUE(dices.at(P2D(i, j+2))->move("up", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      dices.clear();
    }
  }
}

TEST(oneWhiteDice, move_up){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 1; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      WhiteDice wd(c, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c.get_x(), c.get_y()), &wd));
      EXPECT_TRUE(dices.at(P2D(i, j))->move("up", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j-1))->get_position().get_y(), j-1);
      dices.clear();
    }
  }
}

TEST(twoWhiteDices_PushingEachOther, move_up){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j+2);
      WhiteDice wd1(c1, 1, 1, P2D::neutral_p2d);
      WhiteDice wd2(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &wd2));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &wd1));
      EXPECT_TRUE(dices.at(P2D(i, j+2))->move("up", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      dices.clear();
    }
  }
}

TEST(oneWhiteDice0Moves, move_down){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      WhiteDice wd(c, 0, 0, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c.get_x(), c.get_y()), &wd));
      EXPECT_FALSE(dices.at(P2D(i, j))->move("down", dices, __func__, 0).first);
      dices.clear();
    }
  }
}

TEST(twoWhiteDices_PushingEachOther0Moves, move_down){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      WhiteDice wd1(c1, 1, 1, P2D::neutral_p2d);
      WhiteDice wd2(c2, 0, 0, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &wd2));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &wd1));
      EXPECT_TRUE(dices.at(P2D(i, j))->move("down", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_position().get_y(), j+2);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      dices.clear();
    }
  }
}

TEST(oneWhiteDice, move_down){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      WhiteDice wd(c, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c.get_x(), c.get_y()), &wd));
      EXPECT_TRUE(dices.at(P2D(i, j))->move("down", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      dices.clear();
    }
  }
}

TEST(twoWhiteDices_PushingEachOther, move_down){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      WhiteDice wd1(c1, 1, 1, P2D::neutral_p2d);
      WhiteDice wd2(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &wd2));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &wd1));
      EXPECT_TRUE(dices.at(P2D(i, j))->move("down", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_position().get_y(), j+2);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      dices.clear();
    }
  }
}

TEST(oneRedDice, move_left0Moves){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      RedDice rd(c, 0, 0, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c.get_x(), c.get_y()), &rd));
      EXPECT_FALSE(dices.at(P2D(i, j))->move("LEFT", dices, __func__, 0).first);
      dices.clear();
    }
  }
}

TEST(twoRedDices_PushingEachOther0Moves, move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      RedDice rd1(c1, 0, 0, P2D::neutral_p2d);
      RedDice rd2(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &rd2));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &rd1));
      EXPECT_FALSE(dices.at(P2D(i+1, j))->move("LEFT", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      dices.clear();
    }
  }
}

TEST(oneRedDice, move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      RedDice rd(c, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c.get_x(), c.get_y()), &rd));
      EXPECT_TRUE(dices.at(P2D(i, j))->move("LEFT", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i-1, j))->get_position().get_x(), i-1);
      dices.clear();
    }
  }
}

TEST(twoRedDices_PushingEachOther, move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      RedDice rd1(c1, 1, 1, P2D::neutral_p2d);
      RedDice rd2(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &rd2));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &rd1));
      EXPECT_FALSE(dices.at(P2D(i+1, j))->move("LEFT", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingRedDice, move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      RedDice rd(c1, 1, 1, P2D::neutral_p2d);
      WhiteDice wd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &rd));
      EXPECT_FALSE(dices.at(P2D(i+1, j))->move("LEFT", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      dices.clear();
    }
  }
}

TEST(RedDicePushingWhiteDice, move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i+2);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      RedDice rd(c1, 1, 1, P2D::neutral_p2d);
      WhiteDice wd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &rd));
      EXPECT_TRUE(dices.at(P2D(i+2, j))->move("LEFT", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_n_moves(), 0);
      dices.clear();
    }
  }
}

TEST(RedDicePushingWhiteDice0Moves, move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i+2);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      RedDice rd(c1, 1, 1, P2D::neutral_p2d);
      WhiteDice wd(c2, 0, 0, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &rd));
      EXPECT_TRUE(dices.at(P2D(i+2, j))->move("LEFT", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      dices.clear();
    }
  }
}

TEST(oneRedDice, move_right0Moves){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      RedDice rd(c, 0, 0, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c.get_x(), c.get_y()), &rd));
      EXPECT_FALSE(dices.at(P2D(i, j))->move("RIGHT", dices, __func__, 0).first);
      dices.clear();
    }
  }
}

TEST(oneRedDice, move_right){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c.setX(i);
      c.setY(j);
      RedDice rd(c, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c.get_x(), c.get_y()), &rd));
      EXPECT_TRUE(dices.at(P2D(i, j))->move("RIGHT", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      dices.clear();
    }
  }
}

TEST(twoRedDices_PushingEachOther, move_right){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      RedDice rd1(c1, 1, 1, P2D::neutral_p2d);
      RedDice rd2(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &rd2));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &rd1));
      EXPECT_FALSE(dices.at(P2D(i, j))->move("RIGHT", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingRedDice, move_right){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j);
      RedDice rd(c1, 1, 1, P2D::neutral_p2d);
      WhiteDice wd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &rd));
      EXPECT_FALSE(dices.at(P2D(i, j))->move("RIGHT", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      dices.clear();
    }
  }
}

TEST(RedDicePushingWhiteDice, move_right){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      RedDice rd(c1, 1, 1, P2D::neutral_p2d);
      WhiteDice wd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &rd));
      EXPECT_TRUE(dices.at(P2D(i, j))->move("RIGHT", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i+2, j))->get_position().get_x(), i+2);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      dices.clear();
    }
  }
}

TEST(RedDicePushingWhiteDice0Moves, move_right){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      RedDice rd(c1, 1, 1, P2D::neutral_p2d);
      WhiteDice wd(c2, 0, 0, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &rd));
      EXPECT_TRUE(dices.at(P2D(i, j))->move("RIGHT", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i+2, j))->get_position().get_x(), i+2);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      dices.clear();
    }
  }
}

TEST(oneRedDice, move_up0Moves){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      RedDice rd(c, 0, 0, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c.get_x(), c.get_y()), &rd));
      EXPECT_FALSE(dices.at(P2D(i, j))->move("down", dices, __func__, 0).first);
      dices.clear();
    }
  }
}

TEST(oneRedDice, move_up){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 1; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      RedDice rd(c, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c.get_x(), c.get_y()), &rd));
      EXPECT_TRUE(dices.at(P2D(i, j))->move("up", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j-1))->get_position().get_y(), j-1);
      dices.clear();
      dices.clear();
    }
  }
}

TEST(twoRedDices_PushingEachOther, move_up){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      RedDice rd1(c1, 1, 1, P2D::neutral_p2d);
      RedDice rd2(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &rd2));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &rd1));
      EXPECT_FALSE(dices.at(P2D(i, j+1))->move("up", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingRedDice, move_up){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      RedDice rd(c1, 1, 1, P2D::neutral_p2d);
      WhiteDice wd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &rd));
      EXPECT_FALSE(dices.at(P2D(i, j+1))->move("up", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      dices.clear();
    }
  }
}

TEST(RedDicePushingWhiteDice, move_up){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j+2);
      RedDice rd(c2, 1, 1, P2D::neutral_p2d);
      WhiteDice wd(c1, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &wd));
      EXPECT_TRUE(dices.at(P2D(i, j+2))->move("up", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      dices.clear();
    }
  }
}

TEST(RedDicePushingWhiteDice0Moves, move_up){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j+2);
      RedDice rd(c2, 1, 1, P2D::neutral_p2d);
      WhiteDice wd(c1, 0, 0, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &wd));
      EXPECT_TRUE(dices.at(P2D(i, j+2))->move("up", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      dices.clear();
    }
  }
}

TEST(oneRedDice, move_down0Moves){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      RedDice rd(c, 0, 0, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c.get_x(), c.get_y()), &rd));
      EXPECT_FALSE(dices.at(P2D(i, j))->move("down", dices, __func__, 0).first);
      dices.clear();
    }
  }
}

TEST(oneRedDice, move_down){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      RedDice rd(c, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c.get_x(), c.get_y()), &rd));
      EXPECT_TRUE(dices.at(P2D(i, j))->move("down", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      dices.clear();
    }
  }
}

TEST(twoRedDices_PushingEachOther, move_down){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      RedDice rd1(c1, 1, 1, P2D::neutral_p2d);
      RedDice rd2(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &rd2));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &rd1));
      EXPECT_FALSE(dices.at(P2D(i, j))->move("down", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingRedDice, move_down){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j);
      RedDice rd(c1, 1, 1, P2D::neutral_p2d);
      WhiteDice wd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &rd));
      EXPECT_FALSE(dices.at(P2D(i, j))->move("down", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      dices.clear();
    }
  }
}

TEST(RedDicePushingWhiteDice, move_down){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      RedDice rd(c1, 1, 1, P2D::neutral_p2d);
      WhiteDice wd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &rd));
      EXPECT_TRUE(dices.at(P2D(i, j))->move("down", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_position().get_y(), j+2);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_n_moves(), 0);
      dices.clear();
    }
  }
}

TEST(RedDicePushingWhiteDice0Moves, move_down){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      RedDice rd(c1, 1, 1, P2D::neutral_p2d);
      WhiteDice wd(c2, 0, 0, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &rd));
      EXPECT_TRUE(dices.at(P2D(i, j))->move("down", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_position().get_y(), j+2);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      dices.clear();
    }
  }
}

TEST(oneYellowDice, move_left0Moves){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      YellowDice yd(c, 0, 0, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c.get_x(), c.get_y()), &yd));
      EXPECT_FALSE(dices.at(P2D(i, j))->move("LEFT", dices, __func__, 0).first);
      dices.clear();
    }
  }
}

TEST(oneYellowDice, move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      YellowDice yd(c, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c.get_x(), c.get_y()), &yd));
      EXPECT_TRUE(dices.at(P2D(i, j))->move("LEFT", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i-1, j))->get_position().get_x(), i-1);
      dices.clear();
    }
  }
}

TEST(twoYellowDices_JumpingEachOther, move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i+2);
      c2.setY(j);
      YellowDice yd1(c1, 1, 1, P2D::neutral_p2d);
      YellowDice yd2(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &yd2));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &yd1));
      EXPECT_TRUE(dices.at(P2D(i+2, j))->move("LEFT", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingYellowDice, move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i+2);
      c2.setY(j);
      YellowDice yd(c1, 1, 1, P2D::neutral_p2d);
      WhiteDice wd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &yd));
      EXPECT_TRUE(dices.at(P2D(i+2, j))->move("LEFT", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingWhiteDice, move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i+2);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      YellowDice yd(c1, 1, 1, P2D::neutral_p2d);
      WhiteDice wd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &yd));
      EXPECT_TRUE(dices.at(P2D(i+2, j))->move("LEFT", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      dices.clear();
    }
  }
}

TEST(RedDicePushingYellowDice, move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i+2);
      c2.setY(j);
      YellowDice yd(c1, 1, 1, P2D::neutral_p2d);
      RedDice rd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &yd));
      EXPECT_TRUE(dices.at(P2D(i+2, j))->move("LEFT", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingRedDice, move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i+2);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      YellowDice yd(c1, 1, 1, P2D::neutral_p2d);
      RedDice rd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &yd));
      EXPECT_TRUE(dices.at(P2D(i+2, j))->move("LEFT", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      dices.clear();
    }
  }
}

TEST(oneYellowDice, move_right0Moves){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      YellowDice yd(c, 0, 0, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c.get_x(), c.get_y()), &yd));
      EXPECT_FALSE(dices.at(P2D(i, j))->move("RIGHT", dices, __func__, 0).first);
      dices.clear();
    }
  }
}

TEST(oneYellowDice, move_right){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c.setX(i);
      c.setY(j);
      YellowDice yd(c, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c.get_x(), c.get_y()), &yd));
      EXPECT_TRUE(dices.at(P2D(i, j))->move("RIGHT", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      dices.clear();
    }
  }
}

TEST(twoYellowDices_JumpingEachOther, move_right){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      YellowDice yd1(c1, 1, 1, P2D::neutral_p2d);
      YellowDice yd2(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &yd2));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &yd1));
      EXPECT_TRUE(dices.at(P2D(i, j))->move("RIGHT", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      ASSERT_EQ(dices.at(P2D(i+2, j))->get_position().get_x(), i+2);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingYellowDice, move_right){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j);
      YellowDice yd(c1, 1, 1, P2D::neutral_p2d);
      WhiteDice wd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &yd));
      EXPECT_TRUE(dices.at(P2D(i, j))->move("RIGHT", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      ASSERT_EQ(dices.at(P2D(i+2, j))->get_position().get_x(), i+2);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingWhiteDice, move_right){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      YellowDice yd(c1, 1, 1, P2D::neutral_p2d);
      WhiteDice wd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &yd));
      EXPECT_TRUE(dices.at(P2D(i, j))->move("RIGHT", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      ASSERT_EQ(dices.at(P2D(i+2, j))->get_position().get_x(), i+2);
      dices.clear();
    }
  }
}

TEST(RedDicePushingYellowDice, move_right){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j);
      YellowDice yd(c1, 1, 1, P2D::neutral_p2d);
      RedDice rd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &yd));
      EXPECT_TRUE(dices.at(P2D(i, j))->move("RIGHT", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      ASSERT_EQ(dices.at(P2D(i+2, j))->get_position().get_x(), i+2);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingRedDice, move_right){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      YellowDice yd(c1, 1, 1, P2D::neutral_p2d);
      RedDice rd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &yd));
      EXPECT_TRUE(dices.at(P2D(i, j))->move("RIGHT", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      ASSERT_EQ(dices.at(P2D(i+2, j))->get_position().get_x(), i+2);
      dices.clear();
    }
  }
}

TEST(oneYellowDice, move_down0Moves){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      YellowDice yd(c, 0, 0, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c.get_x(), c.get_y()), &yd));
      EXPECT_FALSE(dices.at(P2D(i, j))->move("down", dices, __func__, 0).first);
      dices.clear();
    }
  }
}

TEST(oneYellowDice, move_down){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      YellowDice yd(c, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c.get_x(), c.get_y()), &yd));
      EXPECT_TRUE(dices.at(P2D(i, j))->move("down", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      dices.clear();
    }
  }
}

TEST(twoYellowDices_JumpingEachOther, move_down){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      YellowDice yd1(c1, 1, 1, P2D::neutral_p2d);
      YellowDice yd2(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &yd2));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &yd1));
      EXPECT_TRUE(dices.at(P2D(i, j))->move("down", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_position().get_y(), j+2);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingYellowDice, move_down){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j);
      YellowDice yd(c1, 1, 1, P2D::neutral_p2d);
      WhiteDice wd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &yd));
      EXPECT_TRUE(dices.at(P2D(i, j))->move("down", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_position().get_y(), j+2);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingWhiteDice, move_down){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      YellowDice yd(c1, 1, 1, P2D::neutral_p2d);
      WhiteDice wd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &yd));
      EXPECT_TRUE(dices.at(P2D(i, j))->move("down", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_position().get_y(), j+2);
      dices.clear();
    }
  }
}

TEST(RedDicePushingYellowDice, move_down){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j);
      YellowDice yd(c1, 1, 1, P2D::neutral_p2d);
      RedDice rd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &yd));
      EXPECT_TRUE(dices.at(P2D(i, j))->move("down", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_position().get_y(), j+2);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingRedDice, move_down){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      YellowDice yd(c1, 1, 1, P2D::neutral_p2d);
      RedDice rd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &yd));
      EXPECT_TRUE(dices.at(P2D(i, j))->move("down", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_position().get_y(), j+2);
      dices.clear();
    }
  }
}

TEST(oneYellowDice, move_up0Moves){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      YellowDice yd(c, 0, 0, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c.get_x(), c.get_y()), &yd));
      EXPECT_FALSE(dices.at(P2D(i, j))->move("up", dices, __func__, 0).first);
      dices.clear();
    }
  }
}

TEST(oneYellowDice, move_up){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 1; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      YellowDice yd(c, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c.get_x(), c.get_y()), &yd));
      EXPECT_TRUE(dices.at(P2D(i, j))->move("up", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j-1))->get_position().get_y(), j-1);
      dices.clear();
    }
  }
}

TEST(twoYellowDices_JumpingEachOther, move_up){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 1; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      YellowDice yd1(c1, 1, 1, P2D::neutral_p2d);
      YellowDice yd2(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &yd2));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &yd1));
      EXPECT_TRUE(dices.at(P2D(i, j+1))->move("up", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j-1))->get_position().get_y(), j-1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingYellowDice, move_up){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 1; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      YellowDice yd(c1, 1, 1, P2D::neutral_p2d);
      WhiteDice wd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &yd));
      EXPECT_TRUE(dices.at(P2D(i, j+1))->move("up", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      ASSERT_EQ(dices.at(P2D(i, j-1))->get_position().get_y(), j-1);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingWhiteDice, move_up){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j+2);
      YellowDice yd(c2, 1, 1, P2D::neutral_p2d);
      WhiteDice wd(c1, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &yd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &wd));
      EXPECT_TRUE(dices.at(P2D(i, j+2))->move("up", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      dices.clear();
    }
  }
}

TEST(RedDicePushingYellowDice, move_up){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 1; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      YellowDice yd(c1, 1, 1, P2D::neutral_p2d);
      RedDice rd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &yd));
      EXPECT_TRUE(dices.at(P2D(i, j+1))->move("up", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      ASSERT_EQ(dices.at(P2D(i, j-1))->get_position().get_y(), j-1);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingRedDice, move_up){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j+2);
      YellowDice yd(c2, 1, 1, P2D::neutral_p2d);
      RedDice rd(c1, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &yd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &rd));
      EXPECT_TRUE(dices.at(P2D(i, j+2))->move("up", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      dices.clear();
    }
  }
}

TEST(oneGreenDice, move_left0Moves){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      GreenDice gd(c, 0, 0, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c.get_x(), c.get_y()), &gd));
      EXPECT_FALSE(dices.at(P2D(i, j))->move("LEFT", dices, __func__, 0).first);
      dices.clear();
    }
  }
}

TEST(oneGreenDice, move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 3; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      GreenDice gd(c, 3, 3, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c.get_x(), c.get_y()), &gd));
      int nMoves = dices.at(P2D(i, j))->get_n_moves();
      EXPECT_TRUE(dices.at(P2D(i, j))->move("LEFT", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i-nMoves, j))->get_position().get_x(), i-nMoves);
      dices.clear();
    }
  }
}

TEST(twoGreenDices_PushingEachOther, move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+2);
      c2.setY(j);
      GreenDice gd1(c1, 3, 3, P2D::neutral_p2d);
      GreenDice gd2(c2, 3, 3, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &gd2));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd1));
      EXPECT_TRUE(dices.at(P2D(i+2, j))->move("LEFT", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingGreenDice, move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 2; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      GreenDice gd(c1, 2, 2, P2D::neutral_p2d);
      WhiteDice wd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd));
      EXPECT_TRUE(dices.at(P2D(i+1, j))->move("LEFT", dices, __func__, false).first);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      ASSERT_EQ(dices.at(P2D(i-1, j))->get_position().get_x(), i-1);
      ASSERT_EQ(dices.at(P2D(i-1, j))->get_n_moves(), 2);
      dices.clear();
    }
  }
}

TEST(GreenDicePushingWhiteDice, move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j);
      GreenDice gd(c1, 1, 1, P2D::neutral_p2d);
      WhiteDice wd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd));
      EXPECT_FALSE(dices.at(P2D(i+1, j))->move("LEFT", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      dices.clear();
    }
  }
}

TEST(RedDicePushingGreenDice, move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 2; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      GreenDice gd(c1, 2, 2, P2D::neutral_p2d);  
      RedDice rd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd));
      EXPECT_TRUE(dices.at(P2D(i+1, j))->move("LEFT", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      ASSERT_EQ(dices.at(P2D(i-1, j))->get_position().get_x(), i-1);
      ASSERT_EQ(dices.at(P2D(i-1, j))->get_n_moves(), 2);
      dices.clear();
    }
  }
}

TEST(GreenDicePushingRedDice, move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j);
      GreenDice gd(c1, 1, 1, P2D::neutral_p2d);
      RedDice rd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &rd));
      EXPECT_FALSE(dices.at(P2D(i+1, j))->move("LEFT", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingGreenDice, move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      GreenDice gd(c1, 2, 2, P2D::neutral_p2d);
      YellowDice yd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &yd));
      EXPECT_TRUE(dices.at(P2D(i+1, j))->move("LEFT", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i-1, j))->get_position().get_x(), i-1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      dices.clear();
    }
  }
}

TEST(GreenDicePushingYellowDice, move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j);
      GreenDice gd(c1, 1, 1, P2D::neutral_p2d);
      YellowDice yd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &yd));
      EXPECT_FALSE(dices.at(P2D(i+1, j))->move("LEFT", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      dices.clear();
    }
  }
}

TEST(oneGreenDice, move_right0Moves){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      GreenDice gd(c, 0, 0, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c.get_x(), c.get_y()), &gd));
      EXPECT_FALSE(dices.at(P2D(i, j))->move("RIGHT", dices, __func__, 0).first);
      dices.clear();
    }
  }
}

TEST(oneGreenDice, move_right){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-3; i++){
      c.setX(i);
      c.setY(j);
      GreenDice gd(c, 3, 3, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c.get_x(), c.get_y()), &gd));
      int nMoves = dices.at(P2D(i, j))->get_n_moves();
      EXPECT_TRUE(dices.at(P2D(i, j))->move("RIGHT", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i+nMoves, j))->get_position().get_x(), i+nMoves);
      dices.clear();
    }
  }
}

TEST(twoGreenwDices_PushingEachOther, move_right){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+2);
      c2.setY(j);
      GreenDice gd1(c1, 3, 3, P2D::neutral_p2d);
      GreenDice gd2(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &gd2));
      EXPECT_TRUE(dices.at(P2D(i, j))->move("RIGHT", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      ASSERT_EQ(dices.at(P2D(i+2, j))->get_position().get_x(), i+2);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingGreenDice, move_right){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-3; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j);
      GreenDice gd(c1, 2, 2, P2D::neutral_p2d);
      WhiteDice wd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd));
      EXPECT_TRUE(dices.at(P2D(i, j))->move("RIGHT", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      ASSERT_EQ(dices.at(P2D(i+2, j))->get_position().get_x(), i+2);
      ASSERT_EQ(dices.at(P2D(i+2, j))->get_n_moves(), 2);
      dices.clear();
    }
  }
}

TEST(GreenDicePushingWhiteDice, move_right){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      GreenDice gd(c1, 1, 1, P2D::neutral_p2d);
      WhiteDice wd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &wd));
      EXPECT_FALSE(dices.at(P2D(i, j))->move("RIGHT", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      dices.clear();
    }
  }
}

TEST(RedDicePushingGreenDice, move_right){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-3 ; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      RedDice rd(c1, 1, 1, P2D::neutral_p2d);
      GreenDice gd(c2, 2, 2, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &gd));
      EXPECT_TRUE(dices.at(P2D(i, j))->move("RIGHT", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      ASSERT_EQ(dices.at(P2D(i+2, j))->get_position().get_x(), i+2);
      ASSERT_EQ(dices.at(P2D(i+2, j))->get_n_moves(), 2);
      dices.clear();
    }
  }
}

TEST(GreenDicePushingRedDice, move_right){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      GreenDice gd(c1, 1, 1, P2D::neutral_p2d);
      RedDice rd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &rd));
      EXPECT_FALSE(dices.at(P2D(i, j))->move("RIGHT", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingGreenDice, move_right){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      YellowDice yd(c1, 1, 1, P2D::neutral_p2d);
      GreenDice gd(c2, 2, 2, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &yd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &gd));
      EXPECT_TRUE(dices.at(P2D(i, j))->move("RIGHT", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i+2, j))->get_position().get_x(), i+2);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      dices.clear();
    }
  }
}

TEST(GreenDicePushingYellowDice, move_right){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      GreenDice gd(c1, 1, 1, P2D::neutral_p2d);
      YellowDice yd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &yd));
      EXPECT_FALSE(dices.at(P2D(i, j))->move("RIGHT", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      dices.clear();
    }
  }
}

TEST(oneGreenDice, move_down0Moves){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      GreenDice gd(c, 0, 0, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c.get_x(), c.get_y()), &gd));
      EXPECT_FALSE(dices.at(P2D(i, j))->move("down", dices, __func__, 0).first);
      dices.clear();
    }
  }
}

TEST(oneGreenDice, move_down){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      GreenDice gd(c, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c.get_x(), c.get_y()), &gd));
      int nMoves = dices.at(P2D(i, j))->get_n_moves();
      EXPECT_TRUE(dices.at(P2D(i, j))->move("down", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j+nMoves))->get_position().get_y(), j+nMoves);
      dices.clear();
    }
  }
}

TEST(twoGreenDices_PushingEachOther, move_down){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-3; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+3);
      GreenDice gd1(c1, 3, 3, P2D::neutral_p2d);
      GreenDice gd2(c2, 3, 3, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &gd2));
      EXPECT_TRUE(dices.at(P2D(i, j))->move("down", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_position().get_y(), j+2);
      ASSERT_EQ(dices.at(P2D(i, j+3))->get_position().get_y(), j+3);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingGreenDice, move_down){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-3; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j);
      GreenDice gd(c1, 2, 2, P2D::neutral_p2d);
      WhiteDice wd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd));
      EXPECT_TRUE(dices.at(P2D(i, j))->move("down", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_position().get_y(), j+2);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_n_moves(), 2);
      dices.clear();
    }
  }
}

TEST(GreenDicePushingWhiteDice, move_down){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      GreenDice gd(c1, 1, 1, P2D::neutral_p2d);
      WhiteDice wd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &wd));
      EXPECT_FALSE(dices.at(P2D(i, j))->move("down", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      dices.clear();
    }
  }
}

TEST(RedDicePushingGreenDice, move_down){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-3; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j);
      GreenDice gd(c1, 2, 2, P2D::neutral_p2d);
      RedDice rd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &rd));
      EXPECT_TRUE(dices.at(P2D(i, j))->move("down", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_position().get_y(), j+2);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_n_moves(), 2);
      dices.clear();
    }
  }
}

TEST(GreenDicePushingRedDice, move_down){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      GreenDice gd(c1, 1, 1, P2D::neutral_p2d);
      RedDice rd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &rd));
      EXPECT_FALSE(dices.at(P2D(i, j))->move("down", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingGreenDice, move_down){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j);
      GreenDice gd(c1, 2, 2, P2D::neutral_p2d);
      YellowDice yd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &yd));
      EXPECT_TRUE(dices.at(P2D(i, j))->move("down", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_position().get_y(), j+2);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      dices.clear();
    }
  }
}

TEST(GreenDicePushingYellowDice, move_down){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      GreenDice gd(c1, 1, 1, P2D::neutral_p2d);
      YellowDice yd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &yd));
      EXPECT_FALSE(dices.at(P2D(i, j))->move("down", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      dices.clear();
    }
  }
}

TEST(oneGreenDice, move_up0Moves){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      GreenDice gd(c, 0, 0, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c.get_x(), c.get_y()), &gd));
      EXPECT_FALSE(dices.at(P2D(i, j))->move("up", dices, __func__, 0).first);
      dices.clear();
    }
  }
}

TEST(oneGreenDice, move_up){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 3; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      GreenDice gd(c, 3, 3, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c.get_x(), c.get_y()), &gd));
      int nMoves = dices.at(P2D(i, j))->get_n_moves();
      EXPECT_TRUE(dices.at(P2D(i, j))->move("up", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j-nMoves))->get_position().get_y(), j-nMoves);
      dices.clear();
    }
  }
}

TEST(twoGreenDices_PushingEachOther, move_up){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+3);
      GreenDice gd1(c1, 3, 3, P2D::neutral_p2d);
      GreenDice gd2(c2, 3, 3, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &gd2));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd1));
      EXPECT_TRUE(dices.at(P2D(i, j+3))->move("up", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingGreenDice, move_up){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 2; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      GreenDice gd(c1, 2, 2, P2D::neutral_p2d);
      WhiteDice wd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd));
      EXPECT_TRUE(dices.at(P2D(i, j+1))->move("up", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      ASSERT_EQ(dices.at(P2D(i, j-1))->get_position().get_y(), j-1);
      ASSERT_EQ(dices.at(P2D(i, j-1))->get_n_moves(), 2);
      dices.clear();
    }
  }
}

TEST(GreenDicePushingWhiteDice, move_up){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      GreenDice gd(c2, 1, 1, P2D::neutral_p2d);
      WhiteDice wd(c1, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &gd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &wd));
      EXPECT_FALSE(dices.at(P2D(i, j+1))->move("up", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      dices.clear();
    }
  }
}

TEST(RedDicePushingGreenDice, move_up){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 2; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      GreenDice gd(c1, 2, 2, P2D::neutral_p2d);
      RedDice rd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd));
      EXPECT_TRUE(dices.at(P2D(i, j+1))->move("up", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      ASSERT_EQ(dices.at(P2D(i, j-1))->get_position().get_y(), j-1);
      ASSERT_EQ(dices.at(P2D(i, j-1))->get_n_moves(), 2);
      dices.clear();
    }
  }
}

TEST(GreenDicePushingRedDice, move_up){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      GreenDice gd(c2, 1, 1, P2D::neutral_p2d);
      RedDice rd(c1, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &gd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &rd));
      EXPECT_FALSE(dices.at(P2D(i, j+1))->move("up", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingGreenDice, move_up){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 1; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      GreenDice gd(c1, 1, 1, P2D::neutral_p2d);
      YellowDice yd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &yd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd));
      EXPECT_TRUE(dices.at(P2D(i, j+1))->move("up", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j-1))->get_position().get_y(), j-1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      dices.clear();
    }
  }
}

TEST(GreenDicePushingYellowDice, move_up){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      GreenDice gd(c2, 1, 1, P2D::neutral_p2d);
      YellowDice yd(c1, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &gd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &yd));
      EXPECT_FALSE(dices.at(P2D(i, j+1))->move("up", dices, __func__, 0).first);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      dices.clear();
    }
  }
}

TEST(RedDicePushingWhiteDice, reverse_move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      WhiteDice wd(c1, 1, 1, P2D::neutral_p2d);
      RedDice rd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &rd));
      pair<bool, int> res = dices.at(P2D(i+1, j))->reverse_move("LEFT", dices, __func__, 0);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      dices.clear();
    }
  }
}

TEST(RedDicePushingWhiteDice, reverse_move_right){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j);
      WhiteDice wd(c1, 1, 1, P2D::neutral_p2d);
      RedDice rd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &rd));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("RIGHT", dices, __func__, 0);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      dices.clear();
    }
  }
}

TEST(RedDicePushingWhiteDice, reverse_move_up){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 1; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      WhiteDice wd(c1, 1, 1, P2D::neutral_p2d);
      RedDice rd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &rd));
      pair<bool, int> res = dices.at(P2D(i, j+1))->reverse_move("up", dices, __func__, 0);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      dices.clear();
    }
  }
}

TEST(RedDicePushingWhiteDice, reverse_move_down){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j);
      WhiteDice wd(c1, 1, 1, P2D::neutral_p2d);
      RedDice rd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &rd));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("down", dices, __func__, 0);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingRedDice, reverse_move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH-1; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j);
      WhiteDice wd(c1, 1, 1, P2D::neutral_p2d);
      RedDice rd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &rd));
      pair<bool, int> res = dices.at(P2D(i+1, j))->reverse_move("LEFT", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i-1, j))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i-1, j))->get_position().get_x(), i-1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingRedDice, reverse_move_right){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      WhiteDice wd(c1, 1, 1, P2D::neutral_p2d);
      RedDice rd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &rd));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("RIGHT", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i+2, j))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i+2, j))->get_position().get_x(), i+2);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingRedDice, reverse_move_up){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 1; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j);
      WhiteDice wd(c1, 1, 1, P2D::neutral_p2d);
      RedDice rd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &rd));
      pair<bool, int> res = dices.at(P2D(i, j+1))->reverse_move("up", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j-1))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i, j-1))->get_position().get_y(), j-1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingRedDice, reverse_move_down){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      WhiteDice wd(c1, 1, 1, P2D::neutral_p2d);
      RedDice rd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &rd));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("down", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_position().get_y(), j+2);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      dices.clear();
    }
  }
}

TEST(YellowDicePushingWhiteDice, reverse_move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c0, c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH-2; i++){
      c0.setX(i);
      c0.setY(j);
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i+2);
      c2.setY(j);
      WhiteDice wd0(c0, 1, 1, P2D::neutral_p2d);
      WhiteDice wd1(c1, 1, 1, P2D::neutral_p2d);
      YellowDice yd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c0.get_x(), c0.get_y()), &wd0));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &wd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &yd));
      pair<bool, int> res = dices.at(P2D(i+2, j))->reverse_move("LEFT", dices, __func__, false, PUSHED_MOVE);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i-1, j))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      ASSERT_EQ(dices.at(P2D(i-1, j))->get_position().get_x(), i-1);
      dices.clear();
    }
  }
}

TEST(YellowDicePushingWhiteDice0Moves, reverse_move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c0, c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH-2; i++){
      c0.setX(i);
      c0.setY(j);
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i+2);
      c2.setY(j);
      WhiteDice wd0(c0, 0, 1, P2D::neutral_p2d);
      WhiteDice wd1(c1, 1, 1, P2D::neutral_p2d);
      YellowDice yd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c0.get_x(), c0.get_y()), &wd0));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &wd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &yd));
      pair<bool, int> res = dices.at(P2D(i+2, j))->reverse_move("LEFT", dices, __func__, false, PUSHED_MOVE);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i+2, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      ASSERT_EQ(dices.at(P2D(i+2, j))->get_position().get_x(), i+2);
      dices.clear();
    }
  }
}

TEST(YellowDicePushingWhiteDice, reverse_move_right){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c0, c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-3; i++){
      c0.setX(i+2);
      c0.setY(j);
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j);
      WhiteDice wd0(c0, 1, 1, P2D::neutral_p2d);
      WhiteDice wd1(c1, 1, 1, P2D::neutral_p2d);
      YellowDice yd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c0.get_x(), c0.get_y()), &wd0));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &wd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &yd));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("RIGHT", dices, __func__, false, PUSHED_MOVE);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i+2, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i+3, j))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      ASSERT_EQ(dices.at(P2D(i+2, j))->get_position().get_x(), i+2);
      ASSERT_EQ(dices.at(P2D(i+3, j))->get_position().get_x(), i+3);
      dices.clear();
    }
  }
}

TEST(YellowDicePushingWhiteDice, reverse_move_up){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c0, c1, c2;
  for (int j = 1; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c0.setX(i);
      c0.setY(j);
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j+2);
      WhiteDice wd0(c0, 1, 1, P2D::neutral_p2d);
      WhiteDice wd1(c1, 1, 1, P2D::neutral_p2d);
      YellowDice yd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c0.get_x(), c0.get_y()), &wd0));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &wd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &yd));
      pair<bool, int> res = dices.at(P2D(i, j+2))->reverse_move("up", dices, __func__, false, PUSHED_MOVE);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j-1))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      ASSERT_EQ(dices.at(P2D(i, j-1))->get_position().get_y(), j-1);
      dices.clear();
    }
  }
}

TEST(YellowDicePushingWhiteDice, reverse_move_down){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c0, c1, c2;
  for (int j = 0; j < MAP_HEIGHT-3; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c0.setX(i);
      c0.setY(j+2);
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j);
      WhiteDice wd0(c0, 1, 1, P2D::neutral_p2d);
      WhiteDice wd1(c1, 1, 1, P2D::neutral_p2d);
      YellowDice yd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c0.get_x(), c0.get_y()), &wd0));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &wd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &yd));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("down", dices, __func__, false, PUSHED_MOVE);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j+3))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_position().get_y(), j+2);
      ASSERT_EQ(dices.at(P2D(i, j+3))->get_position().get_y(), j+3);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingWhiteDice, reverse_move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      WhiteDice wd(c1, 1, 1, P2D::neutral_p2d);
      YellowDice yd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &yd));
      pair<bool, int> res = dices.at(P2D(i+1, j))->reverse_move("LEFT", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D(i-1, j))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i-1, j))->get_position().get_x(), i-1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingWhiteDice, reverse_move_right){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j);
      WhiteDice wd(c1, 1, 1, P2D::neutral_p2d);
      YellowDice yd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &yd));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("RIGHT", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D(i+2, j))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i+2, j))->get_position().get_x(), i+2);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingWhiteDice, reverse_move_up){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 1; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      WhiteDice wd(c1, 1, 1, P2D::neutral_p2d);
      YellowDice yd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &yd));
      pair<bool, int> res = dices.at(P2D(i, j+1))->reverse_move("up", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D(i, j-1))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j-1))->get_position().get_y(), j-1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingWhiteDice, reverse_move_down){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j);
      WhiteDice wd(c1, 1, 1, P2D::neutral_p2d);
      YellowDice yd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &yd));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("down", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_position().get_y(), j+2);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingGreenDice, reverse_move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH-1; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j);
      WhiteDice wd(c1, 1, 1, P2D::neutral_p2d);
      GreenDice gd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &gd));
      pair<bool, int> res = dices.at(P2D(i+1, j))->reverse_move("LEFT", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingGreenDice, reverse_move_right){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      WhiteDice wd(c1, 1, 1, P2D::neutral_p2d);
      GreenDice gd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &gd));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("RIGHT", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingGreenDice, reverse_move_up){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 1; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j);
      WhiteDice wd(c1, 1, 1, P2D::neutral_p2d);
      GreenDice gd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &gd));
      pair<bool, int> res = dices.at(P2D(i, j+1))->reverse_move("up", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingGreenDice, reverse_move_down){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+2);
      c2.setX(i);
      c2.setY(j+1);
      WhiteDice wd(c1, 1, 1, P2D::neutral_p2d);
      GreenDice gd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &gd));
      pair<bool, int> res = dices.at(P2D(i, j+2))->reverse_move("up", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_position().get_y(), j+2);
      dices.clear();
    }
  }
}

TEST(YellowDicePushingRedDice, reverse_move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c0, c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH-2; i++){
      c0.setX(i);
      c0.setY(j);
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i+2);
      c2.setY(j);
      RedDice rd(c0, 1, 1, P2D::neutral_p2d);
      WhiteDice wd(c1, 1, 1, P2D::neutral_p2d);
      YellowDice yd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c0.get_x(), c0.get_y()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &yd));
      pair<bool, int> res = dices.at(P2D(i+2, j))->reverse_move("LEFT", dices, __func__, false, PUSHED_MOVE);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i-1, j))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      ASSERT_EQ(dices.at(P2D(i-1, j))->get_position().get_x(), i-1);
      dices.clear();
    }
  }
}

TEST(YellowDicePushingRedDice, reverse_move_right){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c0, c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-3; i++){
      c0.setX(i+2);
      c0.setY(j);
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j);
      RedDice rd(c0, 1, 1, P2D::neutral_p2d);
      WhiteDice wd(c1, 1, 1, P2D::neutral_p2d);
      YellowDice yd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c0.get_x(), c0.get_y()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &yd));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("RIGHT", dices, __func__, false, PUSHED_MOVE);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i+2, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i+3, j))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      ASSERT_EQ(dices.at(P2D(i+2, j))->get_position().get_x(), i+2);
      ASSERT_EQ(dices.at(P2D(i+3, j))->get_position().get_x(), i+3);
      dices.clear();
    }
  }
}

TEST(YellowDicePushingRedDice, reverse_move_up){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c0, c1, c2;
  for (int j = 1; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c0.setX(i);
      c0.setY(j);
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j+2);
      RedDice rd(c0, 1, 1, P2D::neutral_p2d);
      WhiteDice wd(c1, 1, 1, P2D::neutral_p2d);
      YellowDice yd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c0.get_x(), c0.get_y()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &yd));
      pair<bool, int> res = dices.at(P2D(i, j+2))->reverse_move("up", dices, __func__, false, PUSHED_MOVE);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j-1))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      ASSERT_EQ(dices.at(P2D(i, j-1))->get_position().get_y(), j-1);
      dices.clear();
    }
  }
}

TEST(YellowDicePushingRedDice, reverse_move_down){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c0, c1, c2;
  for (int j = 0; j < MAP_HEIGHT-3; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c0.setX(i);
      c0.setY(j+2);
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j);
      RedDice rd(c0, 1, 1, P2D::neutral_p2d);
      WhiteDice wd(c1, 1, 1, P2D::neutral_p2d);
      YellowDice yd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c0.get_x(), c0.get_y()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &yd));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("down", dices, __func__, false, PUSHED_MOVE);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j+3))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_position().get_y(), j+2);
      ASSERT_EQ(dices.at(P2D(i, j+3))->get_position().get_y(), j+3);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingRedDice, reverse_move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      RedDice rd(c1, 1, 1, P2D::neutral_p2d);
      YellowDice yd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &yd));
      pair<bool, int> res = dices.at(P2D(i+1, j))->reverse_move("LEFT", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D(i-1, j))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i-1, j))->get_position().get_x(), i-1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingRedDice, reverse_move_right){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j);
      RedDice rd(c1, 1, 1, P2D::neutral_p2d);
      YellowDice yd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &yd));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("RIGHT", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D(i+2, j))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i+2, j))->get_position().get_x(), i+2);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingRedDice, reverse_move_up){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 1; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      RedDice rd(c1, 1, 1, P2D::neutral_p2d);
      YellowDice yd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &yd));
      pair<bool, int> res = dices.at(P2D(i, j+1))->reverse_move("up", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D(i, j-1))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j-1))->get_position().get_y(), j-1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingRedDice, reverse_move_down){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j);
      RedDice rd(c1, 1, 1, P2D::neutral_p2d);
      YellowDice yd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &yd));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("down", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_position().get_y(), j+2);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      dices.clear();
    }
  }
}

TEST(RedDicePushingGreenDice, reverse_move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH-1; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j);
      RedDice rd(c1, 1, 1, P2D::neutral_p2d);
      GreenDice gd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &gd));
      pair<bool, int> res = dices.at(P2D(i+1, j))->reverse_move("LEFT", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      dices.clear();
    }
  }
}

TEST(RedDicePushingGreenDice, reverse_move_right){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      RedDice rd(c1, 1, 1, P2D::neutral_p2d);
      GreenDice gd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &gd));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("RIGHT", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      dices.clear();
    }
  }
}

TEST(RedDicePushingGreenDice, reverse_move_up){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 1; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j);
      RedDice rd(c1, 1, 1, P2D::neutral_p2d);
      GreenDice gd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &gd));
      pair<bool, int> res = dices.at(P2D(i, j+1))->reverse_move("up", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      dices.clear();
    }
  }
}

TEST(RedDicePushingGreenDice, reverse_move_down){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+2);
      c2.setX(i);
      c2.setY(j+1);
      RedDice rd(c1, 1, 1, P2D::neutral_p2d);
      GreenDice gd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &gd));
      pair<bool, int> res = dices.at(P2D(i, j+2))->reverse_move("up", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_position().get_y(), j+2);
      dices.clear();
    }
  }
}

TEST(YellowDicePushingGreenDice, reverse_move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c0, c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH-2; i++){
      c0.setX(i);
      c0.setY(j);
      c1.setX(i+2);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      WhiteDice wd(c0, 1, 1, P2D::neutral_p2d);
      YellowDice rd(c1, 1, 1, P2D::neutral_p2d);
      GreenDice gd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c0.get_x(), c0.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &gd));
      pair<bool, int> res = dices.at(P2D(i+2, j))->reverse_move("LEFT", dices, __func__, false, PUSHED_MOVE);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i+2, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      ASSERT_EQ(dices.at(P2D(i+2, j))->get_position().get_x(), i+2);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      dices.clear();
    }
  }
}

TEST(YellowDicePushingGreenDice, reverse_move_right){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c0, c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-3; i++){
      c0.setX(i+2);
      c0.setY(j);
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      WhiteDice wd(c0, 1, 1, P2D::neutral_p2d);
      YellowDice rd(c1, 1, 1, P2D::neutral_p2d);
      GreenDice gd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c0.get_x(), c0.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &gd));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("RIGHT", dices, __func__, false, PUSHED_MOVE);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D(i+2, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      ASSERT_EQ(dices.at(P2D(i+2, j))->get_position().get_x(), i+2);
      dices.clear();
    }
  }
}

TEST(YellowDicePushingGreenDice, reverse_move_up){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c0, c1, c2;
  for (int j = 1; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c0.setX(i);
      c0.setY(j);
      c1.setX(i);
      c1.setY(j+2);
      c2.setX(i);
      c2.setY(j+1);
      WhiteDice wd(c0, 1, 1, P2D::neutral_p2d);
      YellowDice rd(c1, 1, 1, P2D::neutral_p2d);
      GreenDice gd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c0.get_x(), c0.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &gd));
      pair<bool, int> res = dices.at(P2D(i, j+2))->reverse_move("up", dices, __func__, false, PUSHED_MOVE);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_position().get_y(), j+2);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      dices.clear();
    }
  }
}

TEST(YellowDicePushingGreenDice, reverse_move_down){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c0, c1, c2;
  for (int j = 0; j < MAP_HEIGHT-3; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c0.setX(i);
      c0.setY(j+2);
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      WhiteDice wd(c0, 1, 1, P2D::neutral_p2d);
      YellowDice rd(c1, 1, 1, P2D::neutral_p2d);
      GreenDice gd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c0.get_x(), c0.get_y()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &gd));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("down", dices, __func__, false, PUSHED_MOVE);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_position().get_y(), j+2);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingGreenDice, reverse_move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      GreenDice gd(c1, 1, 1, P2D::neutral_p2d);
      YellowDice yd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &yd));
      pair<bool, int> res = dices.at(P2D(i+1, j))->reverse_move("LEFT", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D(i-1, j))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i-1, j))->get_position().get_x(), i-1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingGreenDice, reverse_move_right){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j);
      GreenDice gd(c1, 1, 1, P2D::neutral_p2d);
      YellowDice yd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &yd));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("RIGHT", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D(i+2, j))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i+2, j))->get_position().get_x(), i+2);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingGreenDice, reverse_move_up){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 1; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      GreenDice gd(c1, 1, 1, P2D::neutral_p2d);
      YellowDice yd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &yd));
      pair<bool, int> res = dices.at(P2D(i, j+1))->reverse_move("up", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D(i, j-1))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j-1))->get_position().get_y(), j-1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingGreenDice, reverse_move_down){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j);
      GreenDice gd(c1, 1, 1, P2D::neutral_p2d);
      YellowDice yd(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &yd));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("down", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_position().get_y(), j+2);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingTwoDices, reverse_move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2, c3;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-3; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i+2);
      c2.setY(j);
      c3.setX(i+3);
      c3.setY(j);
      GreenDice gd1(c1, 1, 1, P2D::neutral_p2d);
      GreenDice gd2(c2, 1, 1, P2D::neutral_p2d);
      YellowDice yd(c3, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &gd2));
      dices.insert(pair<P2D, Dice *>(P2D(c3.get_x(), c3.get_y()), &yd));
      pair<bool, int> res = dices.at(P2D(i+3, j))->reverse_move("LEFT", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 3);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i+2, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      ASSERT_EQ(dices.at(P2D(i+2, j))->get_position().get_x(), i+2);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingTwoDices, reverse_move_right){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2, c3;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-3; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i+2);
      c2.setY(j);
      c3.setX(i);
      c3.setY(j);
      GreenDice gd1(c1, 1, 1, P2D::neutral_p2d);
      GreenDice gd2(c2, 1, 1, P2D::neutral_p2d);
      YellowDice yd(c3, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &gd2));
      dices.insert(pair<P2D, Dice *>(P2D(c3.get_x(), c3.get_y()), &yd));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("RIGHT", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 3);
      ASSERT_EQ(dices.at(P2D(i+3, j))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i+2, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i+3, j))->get_position().get_x(), i+3);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      ASSERT_EQ(dices.at(P2D(i+2, j))->get_position().get_x(), i+2);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingTwoDices, reverse_move_up){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2, c3;
  for (int j = 0; j < MAP_HEIGHT-3; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j+2);
      c3.setX(i);
      c3.setY(j+3);
      GreenDice gd1(c1, 1, 1, P2D::neutral_p2d);
      GreenDice gd2(c2, 1, 1, P2D::neutral_p2d);
      YellowDice yd(c3, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &gd2));
      dices.insert(pair<P2D, Dice *>(P2D(c3.get_x(), c3.get_y()), &yd));
      pair<bool, int> res = dices.at(P2D(i, j+3))->reverse_move("UP", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 3);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_position().get_y(), j+2);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingTwoDices, reverse_move_down){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2, c3;
  for (int j = 0; j < MAP_HEIGHT-3; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j+2);
      c3.setX(i);
      c3.setY(j);
      GreenDice gd1(c1, 1, 1, P2D::neutral_p2d);
      GreenDice gd2(c2, 1, 1, P2D::neutral_p2d);
      YellowDice yd(c3, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &gd2));
      dices.insert(pair<P2D, Dice *>(P2D(c3.get_x(), c3.get_y()), &yd));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("DOWN", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 3);
      ASSERT_EQ(dices.at(P2D(i, j+3))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j+3))->get_position().get_y(), j+3);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_position().get_y(), j+2);
      dices.clear();
    }
  }
}

TEST(GreenDicePushingGreenDice, reverse_move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      GreenDice gd1(c1, 1, 1, P2D::neutral_p2d);
      GreenDice gd2(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &gd2));
      pair<bool, int> res = dices.at(P2D(i+1, j))->reverse_move("LEFT", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      dices.clear();
    }
  }
}

TEST(GreenDicePushingGreenDice, reverse_move_right){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      GreenDice gd1(c1, 1, 1, P2D::neutral_p2d);
      GreenDice gd2(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &gd2));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("RIGHT", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      dices.clear();
    }
  }
}

TEST(GreenDicePushingGreenDice, reverse_move_up){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 1; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      GreenDice gd1(c1, 1, 1, P2D::neutral_p2d);
      GreenDice gd2(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &gd2));
      pair<bool, int> res = dices.at(P2D(i, j+1))->reverse_move("up", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      dices.clear();
    }
  }
}

TEST(GreenDicePushingGreenDice, reverse_move_down){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      GreenDice gd1(c1, 1, 1, P2D::neutral_p2d);
      GreenDice gd2(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &gd2));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("down", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      dices.clear();
    }
  }
}

TEST(RedDicePushingRedDice, reverse_move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      RedDice rd1(c1, 1, 1, P2D::neutral_p2d);
      RedDice rd2(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &rd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &rd2));
      pair<bool, int> res = dices.at(P2D(i+1, j))->reverse_move("LEFT", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      dices.clear();
    }
  }
}

TEST(RedDicePushingRedDice, reverse_move_right){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      RedDice rd1(c1, 1, 1, P2D::neutral_p2d);
      RedDice rd2(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &rd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &rd2));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("RIGHT", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      dices.clear();
    }
  }
}

TEST(RedDicePushingRedDice, reverse_move_up){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 1; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      RedDice rd1(c1, 1, 1, P2D::neutral_p2d);
      RedDice rd2(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &rd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &rd2));
      pair<bool, int> res = dices.at(P2D(i, j+1))->reverse_move("up", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      dices.clear();
    }
  }
}

TEST(RedDicePushingRedDice, reverse_move_down){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      RedDice rd1(c1, 1, 1, P2D::neutral_p2d);
      RedDice rd2(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &rd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &rd2));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("down", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingWhiteDice, reverse_move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      WhiteDice wd1(c1, 1, 1, P2D::neutral_p2d);
      WhiteDice wd2(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &wd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &wd2));
      pair<bool, int> res = dices.at(P2D(i+1, j))->reverse_move("LEFT", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i-1, j))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      ASSERT_EQ(dices.at(P2D(i-1, j))->get_position().get_x(), i-1);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingWhiteDice, reverse_move_right){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      WhiteDice wd1(c1, 1, 1, P2D::neutral_p2d);
      WhiteDice wd2(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &wd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &wd2));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("RIGHT", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D(i+2, j))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i+2, j))->get_position().get_x(), i+2);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingWhiteDice, reverse_move_up){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 1; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      WhiteDice wd1(c1, 1, 1, P2D::neutral_p2d);
      WhiteDice wd2(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &wd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &wd2));
      pair<bool, int> res = dices.at(P2D(i, j+1))->reverse_move("up", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j-1))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      ASSERT_EQ(dices.at(P2D(i, j-1))->get_position().get_y(), j-1);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingWhiteDice, reverse_move_down){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      WhiteDice wd1(c1, 1, 1, P2D::neutral_p2d);
      WhiteDice wd2(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &wd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &wd2));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("down", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_position().get_y(), j+2);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingYellowDice, reverse_move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      YellowDice yd1(c1, 1, 1, P2D::neutral_p2d);
      YellowDice yd2(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &yd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &yd2));
      pair<bool, int> res = dices.at(P2D(i+1, j))->reverse_move("LEFT", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D(i-1, j))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i-1, j))->get_position().get_x(), i-1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingYellowDice, reverse_move_right){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      YellowDice yd1(c1, 1, 1, P2D::neutral_p2d);
      YellowDice yd2(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &yd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &yd2));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("RIGHT", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i+2, j))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      ASSERT_EQ(dices.at(P2D(i+2, j))->get_position().get_x(), i+2);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingYellowDice, reverse_move_up){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 1; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      YellowDice yd1(c1, 1, 1, P2D::neutral_p2d);
      YellowDice yd2(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &yd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &yd2));
      pair<bool, int> res = dices.at(P2D(i, j+1))->reverse_move("up", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D(i, j-1))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j-1))->get_position().get_y(), j-1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingYellowDice, reverse_move_down){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      YellowDice yd1(c1, 1, 1, P2D::neutral_p2d);
      YellowDice yd2(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &yd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &yd2));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("down", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_n_moves(), 1);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_position().get_y(), j+2);
      dices.clear();
    }
  }
}

TEST(oneYellowDice, reverse_move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      YellowDice yd1(c1, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &yd1));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("LEFT", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 1);
      ASSERT_EQ(dices.at(P2D(i-1, j))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i-1, j))->get_position().get_x(), i-1);
      res = dices.at(P2D(i-1, j))->reverse_move("LEFT", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      dices.clear();
    }
  }
}

TEST(oneYellowDice, reverse_move_right){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      YellowDice yd1(c1, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &yd1));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("RIGHT", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 1);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      res = dices.at(P2D(i+1, j))->reverse_move("RIGHT", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      dices.clear();
    }
  }
}

TEST(oneYellowDice, reverse_move_up){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1;
  for (int j = 1; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      YellowDice yd1(c1, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &yd1));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("up", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 1);
      ASSERT_EQ(dices.at(P2D(i, j-1))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i, j-1))->get_position().get_y(), j-1);
      res = dices.at(P2D(i, j-1))->reverse_move("up", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      dices.clear();
    }
  }
}

TEST(oneYellowDice, reverse_move_down){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1;
  for (int j = 0; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      YellowDice yd1(c1, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &yd1));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("down", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 1);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      res = dices.at(P2D(i, j+1))->reverse_move("down", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      dices.clear();
    }
  }
}

TEST(oneWhiteDice, reverse_move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      WhiteDice wd1(c1, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &wd1));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("LEFT", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 1);
      ASSERT_EQ(dices.at(P2D(i-1, j))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i-1, j))->get_position().get_x(), i-1);
      res = dices.at(P2D(i-1, j))->reverse_move("LEFT", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D(i-1, j))->get_n_moves(), 0);
      dices.clear();
    }
  }
}

TEST(oneWhiteDice, reverse_move_right){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      WhiteDice wd1(c1, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &wd1));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("RIGHT", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 1);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      res = dices.at(P2D(i+1, j))->reverse_move("RIGHT", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      dices.clear();
    }
  }
}

TEST(oneWhiteDice, reverse_move_up){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1;
  for (int j = 1; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      WhiteDice wd1(c1, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &wd1));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("up", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 1);
      ASSERT_EQ(dices.at(P2D(i, j-1))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i, j-1))->get_position().get_y(), j-1);
      res = dices.at(P2D(i, j-1))->reverse_move("up", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      dices.clear();
    }
  }
}

TEST(oneWhiteDice, reverse_move_down){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1;
  for (int j = 0; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      WhiteDice wd1(c1, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &wd1));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("down", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 1);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      res = dices.at(P2D(i, j+1))->reverse_move("down", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      dices.clear();
    }
  }
}

TEST(oneRedDice, reverse_move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      RedDice rd1(c1, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &rd1));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("LEFT", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 1);
      ASSERT_EQ(dices.at(P2D(i-1, j))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i-1, j))->get_position().get_x(), i-1);
      res = dices.at(P2D(i-1, j))->reverse_move("LEFT", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      dices.clear();
    }
  }
}

TEST(oneRedDice, reverse_move_right){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      RedDice rd1(c1, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &rd1));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("RIGHT", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 1);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      res = dices.at(P2D(i+1, j))->reverse_move("RIGHT", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      dices.clear();
    }
  }
}

TEST(oneRedDice, reverse_move_up){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1;
  for (int j = 1; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      RedDice rd1(c1, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &rd1));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("up", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 1);
      ASSERT_EQ(dices.at(P2D(i, j-1))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i, j-1))->get_position().get_y(), j-1);
      res = dices.at(P2D(i, j-1))->reverse_move("up", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      dices.clear();
    }
  }
}

TEST(oneRedDice, reverse_move_down){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1;
  for (int j = 0; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      RedDice rd1(c1, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &rd1));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("down", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 1);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      res = dices.at(P2D(i, j+1))->reverse_move("down", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      dices.clear();
    }
  }
}

TEST(oneGreenDice, reverse_move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 2; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      GreenDice gd1(c1, 2, 2, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd1));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("LEFT", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D(i-2, j))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i-2, j))->get_position().get_x(), i-2);
      res = dices.at(P2D(i-2, j))->reverse_move("LEFT", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      dices.clear();
    }
  }
}

TEST(oneGreenDice, reverse_move_right){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i);
      c1.setY(j);
      GreenDice gd1(c1, 2, 2, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd1));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("RIGHT", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D(i+2, j))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i+2, j))->get_position().get_x(), i+2);
      res = dices.at(P2D(i+2, j))->reverse_move("RIGHT", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      dices.clear();
    }
  }
}

TEST(oneGreenDice, reverse_move_up){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1;
  for (int j = 2; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      GreenDice gd1(c1, 2, 2, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd1));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("up", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D(i, j-2))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i, j-2))->get_position().get_y(), j-2);
      res = dices.at(P2D(i, j-2))->reverse_move("up", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      dices.clear();
    }
  }
}

TEST(oneGreenDice, reverse_move_down){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      GreenDice gd1(c1, 2, 2, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd1));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("down", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i, j+2))->get_position().get_y(), j+2);
      res = dices.at(P2D(i, j+2))->reverse_move("down", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      dices.clear();
    }
  }
}

TEST(GreenDicePushingWhiteDice, reverse_move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH-1; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j);
      GreenDice gd1(c1, 1, 1, P2D::neutral_p2d);
      WhiteDice wd1(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &wd1));
      pair<bool, int> res = dices.at(P2D(i+1, j))->reverse_move("LEFT", dices, __func__, false, PUSHED_MOVE);
      if(c2.get_x() > 0){
        EXPECT_TRUE(res.first);
        ASSERT_EQ(res.second, 1);
        ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
        ASSERT_EQ(dices.at(P2D(i-1, j))->get_n_moves(), 0);
        ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
        ASSERT_EQ(dices.at(P2D(i-1, j))->get_position().get_x(), i-1);
      }else{
        EXPECT_FALSE(res.first);
        ASSERT_EQ(res.second, 0);
        ASSERT_EQ(dices.at(P2D(i+1, j))->get_n_moves(), 1);
        ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
        ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
        ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      }
      dices.clear();
    }
  }
}

TEST(GreenDicePushingWhiteDice, reverse_move_right){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      GreenDice gd1(c1, 1, 1, P2D::neutral_p2d);
      WhiteDice wd1(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &wd1));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("RIGHT", dices, __func__, false, PUSHED_MOVE);
      if(c2.get_x() < MAP_WIDTH-1){
        EXPECT_TRUE(res.first);
        ASSERT_EQ(res.second, 1);
        ASSERT_EQ(dices.at(P2D(i+1, j))->get_n_moves(), 1);
        ASSERT_EQ(dices.at(P2D(i+2, j))->get_n_moves(), 0);
        ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
        ASSERT_EQ(dices.at(P2D(i+2, j))->get_position().get_x(), i+2);
      }else{
        EXPECT_FALSE(res.first);
        ASSERT_EQ(res.second, 0);
        ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
        ASSERT_EQ(dices.at(P2D(i+1, j))->get_n_moves(), 1);
        ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
        ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      }
      dices.clear();
    }
  }
}

TEST(GreenDicePushingWhiteDice, reverse_move_up){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 1; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j);
      GreenDice gd1(c1, 1, 1, P2D::neutral_p2d);
      WhiteDice wd1(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &wd1));
      pair<bool, int> res = dices.at(P2D(i, j+1))->reverse_move("up", dices, __func__, false, PUSHED_MOVE);
      if(c2.get_y() > 0){
        EXPECT_TRUE(res.first);
        ASSERT_EQ(res.second, 1);
        ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
        ASSERT_EQ(dices.at(P2D(i, j-1))->get_n_moves(), 0);
        ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
        ASSERT_EQ(dices.at(P2D(i, j-1))->get_position().get_y(), j-1);
      }else{
        EXPECT_FALSE(res.first);
        ASSERT_EQ(res.second, 0);
        ASSERT_EQ(dices.at(P2D(i, j+1))->get_n_moves(), 1);
        ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
        ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
        ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      }
      dices.clear();
    }
  }
}

TEST(GreenDicePushingWhiteDice, reverse_move_down){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      GreenDice gd1(c1, 1, 1, P2D::neutral_p2d);
      WhiteDice wd1(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &wd1));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("down", dices, __func__, false, PUSHED_MOVE);
      if(c2.get_y() < MAP_HEIGHT-1){
        EXPECT_TRUE(res.first);
        ASSERT_EQ(res.second, 1);
        ASSERT_EQ(dices.at(P2D(i, j+1))->get_n_moves(), 1);
        ASSERT_EQ(dices.at(P2D(i, j+2))->get_n_moves(), 0);
        ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
        ASSERT_EQ(dices.at(P2D(i, j+2))->get_position().get_y(), j+2);
      }else{
        EXPECT_FALSE(res.first);
        ASSERT_EQ(res.second, 0);
        ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
        ASSERT_EQ(dices.at(P2D(i, j+1))->get_n_moves(), 1);
        ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
        ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      }
      dices.clear();
    }
  }
}

TEST(GreenDicePushingRedDice, reverse_move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH-1; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j);
      GreenDice gd1(c1, 1, 1, P2D::neutral_p2d);
      RedDice rd1(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &rd1));
      pair<bool, int> res = dices.at(P2D(i+1, j))->reverse_move("LEFT", dices, __func__, false, PUSHED_MOVE);
      if(c2.get_x() > 0){
        EXPECT_TRUE(res.first);
        ASSERT_EQ(res.second, 1);
        ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
        ASSERT_EQ(dices.at(P2D(i-1, j))->get_n_moves(), 0);
        ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
        ASSERT_EQ(dices.at(P2D(i-1, j))->get_position().get_x(), i-1);
      }else{
        EXPECT_FALSE(res.first);
        ASSERT_EQ(res.second, 0);
        ASSERT_EQ(dices.at(P2D(i+1, j))->get_n_moves(), 1);
        ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
        ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
        ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      }
      dices.clear();
    }
  }
}

TEST(GreenDicePushingRedDice, reverse_move_right){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      GreenDice gd1(c1, 1, 1, P2D::neutral_p2d);
      RedDice rd1(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &rd1));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("RIGHT", dices, __func__, false, PUSHED_MOVE);
      if(c2.get_x() < MAP_WIDTH-1){
        EXPECT_TRUE(res.first);
        ASSERT_EQ(res.second, 1);
        ASSERT_EQ(dices.at(P2D(i+1, j))->get_n_moves(), 1);
        ASSERT_EQ(dices.at(P2D(i+2, j))->get_n_moves(), 0);
        ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
        ASSERT_EQ(dices.at(P2D(i+2, j))->get_position().get_x(), i+2);
      }else{
        EXPECT_FALSE(res.first);
        ASSERT_EQ(res.second, 0);
        ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
        ASSERT_EQ(dices.at(P2D(i+1, j))->get_n_moves(), 1);
        ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
        ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      }
      dices.clear();
    }
  }
}

TEST(GreenDicePushingRedDice, reverse_move_up){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 1; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j);
      GreenDice gd1(c1, 1, 1, P2D::neutral_p2d);
      RedDice rd1(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &rd1));
      pair<bool, int> res = dices.at(P2D(i, j+1))->reverse_move("up", dices, __func__, false, PUSHED_MOVE);
      if(c2.get_y() > 0){
        EXPECT_TRUE(res.first);
        ASSERT_EQ(res.second, 1);
        ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
        ASSERT_EQ(dices.at(P2D(i, j-1))->get_n_moves(), 0);
        ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
        ASSERT_EQ(dices.at(P2D(i, j-1))->get_position().get_y(), j-1);
      }else{
        EXPECT_FALSE(res.first);
        ASSERT_EQ(res.second, 0);
        ASSERT_EQ(dices.at(P2D(i, j+1))->get_n_moves(), 1);
        ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
        ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
        ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      }
      dices.clear();
    }
  }
}

TEST(GreenDicePushingRedDice, reverse_move_down){
   unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      GreenDice gd1(c1, 1, 1, P2D::neutral_p2d);
      RedDice rd1(c2, 1, 1, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &rd1));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("down", dices, __func__, false, PUSHED_MOVE);
      if(c2.get_y() < MAP_HEIGHT-1){
        EXPECT_TRUE(res.first);
        ASSERT_EQ(res.second, 1);
        ASSERT_EQ(dices.at(P2D(i, j+1))->get_n_moves(), 1);
        ASSERT_EQ(dices.at(P2D(i, j+2))->get_n_moves(), 0);
        ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
        ASSERT_EQ(dices.at(P2D(i, j+2))->get_position().get_y(), j+2);
      }else{
        EXPECT_FALSE(res.first);
        ASSERT_EQ(res.second, 0);
        ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 1);
        ASSERT_EQ(dices.at(P2D(i, j+1))->get_n_moves(), 1);
        ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
        ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      }
      dices.clear();
    }
  }
}

TEST(GreenDicePushingWhiteDice0Moves, reverse_move_left){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH-1; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j);
      GreenDice gd1(c1, 0, 0, P2D::neutral_p2d);
      WhiteDice wd1(c2, 0, 0, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &wd1));
      pair<bool, int> res = dices.at(P2D(i+1, j))->reverse_move("LEFT", dices, __func__, false, true);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      dices.clear();
    }
  }
}

TEST(GreenDicePushingWhiteDice0Moves, reverse_move_right){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      GreenDice gd1(c1, 0, 0, P2D::neutral_p2d);
      WhiteDice wd1(c2, 0, 0, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &wd1));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("RIGHT", dices, __func__, false, true);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_x(), i);
      ASSERT_EQ(dices.at(P2D(i+1, j))->get_position().get_x(), i+1);
      dices.clear();
    }
  }
}

TEST(GreenDicePushingWhiteDice0Moves, reverse_move_up){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 1; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j);
      GreenDice gd1(c1, 0, 0, P2D::neutral_p2d);
      WhiteDice wd1(c2, 0, 0, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &wd1));
      pair<bool, int> res = dices.at(P2D(i, j+1))->reverse_move("up", dices, __func__, false, true);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      dices.clear();
    }
  }
}

TEST(GreenDicePushingWhiteDice0Moves, reverse_move_down){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      GreenDice gd1(c1, 0, 0, P2D::neutral_p2d);
      WhiteDice wd1(c2, 0, 0, P2D::neutral_p2d);
      dices.insert(pair<P2D, Dice *>(P2D(c1.get_x(), c1.get_y()), &gd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.get_x(), c2.get_y()), &wd1));
      pair<bool, int> res = dices.at(P2D(i, j))->reverse_move("down", dices, __func__, false, true);
      EXPECT_FALSE(res.first);  
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D(i, j))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_n_moves(), 0);
      ASSERT_EQ(dices.at(P2D(i, j))->get_position().get_y(), j);
      ASSERT_EQ(dices.at(P2D(i, j+1))->get_position().get_y(), j+1);
      dices.clear();
    }
  }
}

int main(int argc, char **argv){
  MAP_WIDTH = 5;
  MAP_HEIGHT = 6;
  cout << "======== Alea Tester ========" << endl;
	cout << "        MAP_WIDTH : " << MAP_WIDTH << endl;
	cout << "        MAP_HEIGHT: " << MAP_HEIGHT << endl;
	cout << "=============================" << endl;
	cout << endl;
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}