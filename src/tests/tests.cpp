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

TEST(oneWhiteDice, moveSx0Moves){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      WhiteDice wd(c, 0);
      dices.insert(pair<P2D, Dice *>(P2D(c.getX(), c.getY()), &wd));
      EXPECT_FALSE(dices.at(P2D::cellToP2D(c))->move("sx", dices, __func__, 0));
      dices.clear();
    }
  }
}

TEST(twoWhiteDices_PushingEachOther0Moves, moveSx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i+2);
      c2.setY(j);
      WhiteDice wd1(c1, 0);
      WhiteDice wd2(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &wd2));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &wd1));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c2))->move("sx", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i);
      dices.clear();
    }
  }
}

TEST(oneWhiteDice, moveSx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      WhiteDice wd(c, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c.getX(), c.getY()), &wd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c))->move("sx", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c))->getPosition().getX(), i-1);
      dices.clear();
    }
  }
}

TEST(twoWhiteDices_PushingEachOther, moveSx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i+2);
      c2.setY(j);
      WhiteDice wd1(c1, 1);
      WhiteDice wd2(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &wd2));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &wd1));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c2))->move("sx", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i);
      dices.clear();
    }
  }
}

TEST(oneWhiteDice, moveDx0Moves){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      WhiteDice wd(c, 0);
      dices.insert(pair<P2D, Dice *>(P2D(c.getX(), c.getY()), &wd));
      EXPECT_FALSE(dices.at(P2D::cellToP2D(c))->move("dx", dices, __func__, 0));
      dices.clear();
    }
  }
}

TEST(twoWhiteDices_PushingEachOther0Moves, moveDx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      WhiteDice wd1(c1, 1);
      WhiteDice wd2(c2, 0);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &wd2));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &wd1));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c1))->move("dx", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i+1);
      dices.clear();
    }
  }
}

TEST(oneWhiteDice, moveDx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      WhiteDice wd(c, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c.getX(), c.getY()), &wd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c))->move("dx", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c))->getPosition().getX(), i+1);
      dices.clear();
    }
  }
}

TEST(twoWhiteDices_PushingEachOther, moveDx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      WhiteDice wd1(c1, 1);
      WhiteDice wd2(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &wd2));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &wd1));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c1))->move("dx", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i+1);
      dices.clear();
    }
  }
}

TEST(oneWhiteDice0Moves, moveUp){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 1; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      WhiteDice wd(c, 0);
      dices.insert(pair<P2D, Dice *>(P2D(c.getX(), c.getY()), &wd));
      EXPECT_FALSE(dices.at(P2D::cellToP2D(c))->move("up", dices, __func__, 0));
      dices.clear();
    }
  }
}

TEST(twoWhiteDices_PushingEachOther0Moves, moveUp){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j+2);
      WhiteDice wd1(c1, 0);
      WhiteDice wd2(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &wd2));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &wd1));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c2))->move("up", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j);
      dices.clear();
    }
  }
}

TEST(oneWhiteDice, moveUp){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 1; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      WhiteDice wd(c, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c.getX(), c.getY()), &wd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c))->move("up", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c))->getPosition().getY(), j-1);
      dices.clear();
    }
  }
}

TEST(twoWhiteDices_PushingEachOther, moveUp){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j+2);
      WhiteDice wd1(c1, 1);
      WhiteDice wd2(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &wd2));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &wd1));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c2))->move("up", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j);
      dices.clear();
    }
  }
}

TEST(oneWhiteDice0Moves, moveDown){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      WhiteDice wd(c, 0);
      dices.insert(pair<P2D, Dice *>(P2D(c.getX(), c.getY()), &wd));
      EXPECT_FALSE(dices.at(P2D::cellToP2D(c))->move("down", dices, __func__, 0));
      dices.clear();
    }
  }
}

TEST(twoWhiteDices_PushingEachOther0Moves, moveDown){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      WhiteDice wd1(c1, 1);
      WhiteDice wd2(c2, 0);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &wd2));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &wd1));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c1))->move("down", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j+1);
      dices.clear();
    }
  }
}

TEST(oneWhiteDice, moveDown){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      WhiteDice wd(c, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c.getX(), c.getY()), &wd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c))->move("down", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c))->getPosition().getY(), j+1);
      dices.clear();
    }
  }
}

TEST(twoWhiteDices_PushingEachOther, moveDown){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      WhiteDice wd1(c1, 1);
      WhiteDice wd2(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &wd2));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &wd1));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c1))->move("down", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j+1);
      dices.clear();
    }
  }
}

TEST(oneRedDice, moveSx0Moves){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      RedDice rd(c, 0);
      dices.insert(pair<P2D, Dice *>(P2D(c.getX(), c.getY()), &rd));
      EXPECT_FALSE(dices.at(P2D::cellToP2D(c))->move("sx", dices, __func__, 0));
      dices.clear();
    }
  }
}

TEST(twoRedDices_PushingEachOther0Moves, moveSx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      RedDice rd1(c1, 0);
      RedDice rd2(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &rd2));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &rd1));
      EXPECT_FALSE(dices.at(P2D::cellToP2D(c2))->move("sx", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i);
      dices.clear();
    }
  }
}

TEST(oneRedDice, moveSx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      RedDice rd(c, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c.getX(), c.getY()), &rd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c))->move("sx", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c))->getPosition().getX(), i-1);
      dices.clear();
    }
  }
}

TEST(twoRedDices_PushingEachOther, moveSx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      RedDice rd1(c1, 1);
      RedDice rd2(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &rd2));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &rd1));
      EXPECT_FALSE(dices.at(P2D::cellToP2D(c2))->move("sx", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingRedDice, moveSx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      RedDice rd(c1, 1);
      WhiteDice wd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &rd));
      EXPECT_FALSE(dices.at(P2D::cellToP2D(c2))->move("sx", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i);
      dices.clear();
    }
  }
}

TEST(RedDicePushingWhiteDice, moveSx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i+2);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      RedDice rd(c1, 1);
      WhiteDice wd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &rd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c1))->move("sx", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i+1);
      dices.clear();
    }
  }
}

TEST(RedDicePushingWhiteDice0Moves, moveSx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i+2);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      RedDice rd(c1, 1);
      WhiteDice wd(c2, 0);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &rd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c1))->move("sx", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i+1);
      dices.clear();
    }
  }
}

TEST(oneRedDice, moveDx0Moves){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      RedDice rd(c, 0);
      dices.insert(pair<P2D, Dice *>(P2D(c.getX(), c.getY()), &rd));
      EXPECT_FALSE(dices.at(P2D::cellToP2D(c))->move("dx", dices, __func__, 0));
      dices.clear();
    }
  }
}

TEST(oneRedDice, moveDx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c.setX(i);
      c.setY(j);
      RedDice rd(c, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c.getX(), c.getY()), &rd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c))->move("dx", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c))->getPosition().getX(), i+1);
      dices.clear();
    }
  }
}

TEST(twoRedDices_PushingEachOther, moveDx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      RedDice rd1(c1, 1);
      RedDice rd2(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &rd2));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &rd1));
      EXPECT_FALSE(dices.at(P2D::cellToP2D(c1))->move("dx", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingRedDice, moveDx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j);
      RedDice rd(c1, 1);
      WhiteDice wd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &rd));
      EXPECT_FALSE(dices.at(P2D::cellToP2D(c2))->move("dx", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i+1);
      dices.clear();
    }
  }
}

TEST(RedDicePushingWhiteDice, moveDx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      RedDice rd(c1, 1);
      WhiteDice wd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &rd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c1))->move("dx", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i+1);
      dices.clear();
    }
  }
}

TEST(RedDicePushingWhiteDice0Moves, moveDx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      RedDice rd(c1, 1);
      WhiteDice wd(c2, 0);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &rd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c1))->move("dx", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i+1);
      dices.clear();
    }
  }
}

TEST(oneRedDice, moveUp0Moves){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      RedDice rd(c, 0);
      dices.insert(pair<P2D, Dice *>(P2D(c.getX(), c.getY()), &rd));
      EXPECT_FALSE(dices.at(P2D::cellToP2D(c))->move("down", dices, __func__, 0));
      dices.clear();
    }
  }
}

TEST(oneRedDice, moveUp){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 1; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      RedDice rd(c, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c.getX(), c.getY()), &rd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c))->move("up", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c))->getPosition().getY(), j-1);
      dices.clear();
      dices.clear();
    }
  }
}

TEST(twoRedDices_PushingEachOther, moveUp){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      RedDice rd1(c1, 1);
      RedDice rd2(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &rd2));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &rd1));
      EXPECT_FALSE(dices.at(P2D::cellToP2D(c2))->move("up", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingRedDice, moveUp){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      RedDice rd(c1, 1);
      WhiteDice wd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &rd));
      EXPECT_FALSE(dices.at(P2D::cellToP2D(c2))->move("up", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j);
      dices.clear();
    }
  }
}

TEST(RedDicePushingWhiteDice, moveUp){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j+2);
      RedDice rd(c2, 1);
      WhiteDice wd(c1, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &wd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c2))->move("up", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j);
      dices.clear();
    }
  }
}

TEST(RedDicePushingWhiteDice0Moves, moveUp){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j+2);
      RedDice rd(c2, 1);
      WhiteDice wd(c1, 0);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &wd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c2))->move("up", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j);
      dices.clear();
    }
  }
}

TEST(oneRedDice, moveDown0Moves){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      RedDice rd(c, 0);
      dices.insert(pair<P2D, Dice *>(P2D(c.getX(), c.getY()), &rd));
      EXPECT_FALSE(dices.at(P2D::cellToP2D(c))->move("down", dices, __func__, 0));
      dices.clear();
    }
  }
}

TEST(oneRedDice, moveDown){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      RedDice rd(c, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c.getX(), c.getY()), &rd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c))->move("down", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c))->getPosition().getY(), j+1);
      dices.clear();
    }
  }
}

TEST(twoRedDices_PushingEachOther, moveDown){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      RedDice rd1(c1, 1);
      RedDice rd2(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &rd2));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &rd1));
      EXPECT_FALSE(dices.at(P2D::cellToP2D(c1))->move("down", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingRedDice, moveDown){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j);
      RedDice rd(c1, 1);
      WhiteDice wd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &rd));
      EXPECT_FALSE(dices.at(P2D::cellToP2D(c2))->move("down", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j+1);
      dices.clear();
    }
  }
}

TEST(RedDicePushingWhiteDice, moveDown){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      RedDice rd(c1, 1);
      WhiteDice wd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &rd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c1))->move("down", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j+1);
      dices.clear();
    }
  }
}

TEST(RedDicePushingWhiteDice0Moves, moveDown){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      RedDice rd(c1, 1);
      WhiteDice wd(c2, 0);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &rd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c1))->move("down", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j+1);
      dices.clear();
    }
  }
}

TEST(oneYellowDice, moveSx0Moves){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      YellowDice yd(c, 0);
      dices.insert(pair<P2D, Dice *>(P2D(c.getX(), c.getY()), &yd));
      EXPECT_FALSE(dices.at(P2D::cellToP2D(c))->move("sx", dices, __func__, 0));
      dices.clear();
    }
  }
}

TEST(oneYellowDice, moveSx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      YellowDice yd(c, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c.getX(), c.getY()), &yd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c))->move("sx", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c))->getPosition().getX(), i-1);
      dices.clear();
    }
  }
}

TEST(twoYellowDices_PushingEachOther, moveSx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i+2);
      c2.setY(j);
      YellowDice yd1(c1, 1);
      YellowDice yd2(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &yd2));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &yd1));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c2))->move("sx", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i+1);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingYellowDice, moveSx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i+2);
      c2.setY(j);
      YellowDice yd(c1, 1);
      WhiteDice wd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &yd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c2))->move("sx", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingWhiteDice, moveSx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i+2);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      YellowDice yd(c1, 1);
      WhiteDice wd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &yd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c1))->move("sx", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i);
      dices.clear();
    }
  }
}

TEST(RedDicePushingYellowDice, moveSx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i+2);
      c2.setY(j);
      YellowDice yd(c1, 1);
      RedDice rd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &yd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c2))->move("sx", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingRedDice, moveSx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i+2);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      YellowDice yd(c1, 1);
      RedDice rd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &yd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c1))->move("sx", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i);
      dices.clear();
    }
  }
}

TEST(oneYellowDice, moveDx0Moves){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      YellowDice yd(c, 0);
      dices.insert(pair<P2D, Dice *>(P2D(c.getX(), c.getY()), &yd));
      EXPECT_FALSE(dices.at(P2D::cellToP2D(c))->move("dx", dices, __func__, 0));
      dices.clear();
    }
  }
}

TEST(oneYellowDice, moveDx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c.setX(i);
      c.setY(j);
      YellowDice yd(c, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c.getX(), c.getY()), &yd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c))->move("dx", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c))->getPosition().getX(), i+1);
      dices.clear();
    }
  }
}

TEST(twoYellowDices_PushingEachOther, moveDx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      YellowDice yd1(c1, 1);
      YellowDice yd2(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &yd2));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &yd1));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c1))->move("dx", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i+2);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingYellowDice, moveDx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j);
      YellowDice yd(c1, 1);
      WhiteDice wd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &yd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c2))->move("dx", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i+2);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingWhiteDice, moveDx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      YellowDice yd(c1, 1);
      WhiteDice wd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &yd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c1))->move("dx", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i+2);
      dices.clear();
    }
  }
}

TEST(RedDicePushingYellowDice, moveDx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j);
      YellowDice yd(c1, 1);
      RedDice rd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &yd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c2))->move("dx", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i+2);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingRedDice, moveDx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      YellowDice yd(c1, 1);
      RedDice rd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &yd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c1))->move("dx", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i+2);
      dices.clear();
    }
  }
}

TEST(oneYellowDice, moveDown0Moves){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      YellowDice yd(c, 0);
      dices.insert(pair<P2D, Dice *>(P2D(c.getX(), c.getY()), &yd));
      EXPECT_FALSE(dices.at(P2D::cellToP2D(c))->move("down", dices, __func__, 0));
      dices.clear();
    }
  }
}

TEST(oneYellowDice, moveDown){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      YellowDice yd(c, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c.getX(), c.getY()), &yd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c))->move("down", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c))->getPosition().getY(), j+1);
      dices.clear();
    }
  }
}

TEST(twoYellowDices_PushingEachOther, moveDown){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      YellowDice yd1(c1, 1);
      YellowDice yd2(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &yd2));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &yd1));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c1))->move("down", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j+2);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingYellowDice, moveDown){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j);
      YellowDice yd(c1, 1);
      WhiteDice wd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &yd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c2))->move("down", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j+2);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingWhiteDice, moveDown){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      YellowDice yd(c1, 1);
      WhiteDice wd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &yd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c1))->move("down", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j+2);
      dices.clear();
    }
  }
}

TEST(RedDicePushingYellowDice, moveDown){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j);
      YellowDice yd(c1, 1);
      RedDice rd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &yd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c2))->move("down", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j+2);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingRedDice, moveDown){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      YellowDice yd(c1, 1);
      RedDice rd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &yd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c1))->move("down", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j+2);
      dices.clear();
    }
  }
}

TEST(oneYellowDice, moveUp0Moves){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      YellowDice yd(c, 0);
      dices.insert(pair<P2D, Dice *>(P2D(c.getX(), c.getY()), &yd));
      EXPECT_FALSE(dices.at(P2D::cellToP2D(c))->move("up", dices, __func__, 0));
      dices.clear();
    }
  }
}

TEST(oneYellowDice, moveUp){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 1; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      YellowDice yd(c, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c.getX(), c.getY()), &yd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c))->move("up", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c))->getPosition().getY(), j-1);
      dices.clear();
    }
  }
}

TEST(twoYellowDices_PushingEachOther, moveUp){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      YellowDice yd1(c1, 1);
      YellowDice yd2(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &yd2));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &yd1));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c2))->move("up", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j-1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingYellowDice, moveUp){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 1; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      YellowDice yd(c1, 1);
      WhiteDice wd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &yd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c2))->move("up", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j-1);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingWhiteDice, moveUp){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j+2);
      YellowDice yd(c2, 1);
      WhiteDice wd(c1, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &yd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &wd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c2))->move("up", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j+1);
      dices.clear();
    }
  }
}

TEST(RedDicePushingYellowDice, moveUp){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      YellowDice yd(c1, 1);
      RedDice rd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &yd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c2))->move("up", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j-1);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingRedDice, moveUp){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j+2);
      YellowDice yd(c2, 1);
      RedDice rd(c1, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &yd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &rd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c2))->move("up", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j+1);
      dices.clear();
    }
  }
}

TEST(oneGreenDice, moveSx0Moves){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      GreenDice gd(c, 0);
      dices.insert(pair<P2D, Dice *>(P2D(c.getX(), c.getY()), &gd));
      EXPECT_FALSE(dices.at(P2D::cellToP2D(c))->move("sx", dices, __func__, 0));
      dices.clear();
    }
  }
}

TEST(oneGreenDice, moveSx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 3; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      GreenDice gd(c, 3);
      dices.insert(pair<P2D, Dice *>(P2D(c.getX(), c.getY()), &gd));
      int nMoves = dices.at(P2D::cellToP2D(c))->getNMoves();
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c))->move("sx", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c))->getPosition().getX(), i-nMoves);
      dices.clear();
    }
  }
}

TEST(twoGreenDices_PushingEachOther, moveSx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+2);
      c2.setY(j);
      GreenDice gd1(c1, 3);
      GreenDice gd2(c2, 3);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &gd2));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd1));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c2))->move("sx", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingGreenDice, moveSx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 2; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      GreenDice gd(c1, 2);
      WhiteDice wd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c2))->move("sx", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i-2);
      dices.clear();
    }
  }
}

TEST(GreenDicePushingWhiteDice, moveSx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j);
      GreenDice gd(c1, 1);
      WhiteDice wd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd));
      EXPECT_FALSE(dices.at(P2D::cellToP2D(c1))->move("sx", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i+1);
      dices.clear();
    }
  }
}

TEST(RedDicePushingGreenDice, moveSx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 2; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      GreenDice gd(c1, 2);  
      RedDice rd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c2))->move("sx", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i-2);
      dices.clear();
    }
  }
}

TEST(GreenDicePushingRedDice, moveSx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j);
      GreenDice gd(c1, 1);
      RedDice rd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &rd));
      EXPECT_FALSE(dices.at(P2D::cellToP2D(c1))->move("sx", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i);
      dices.clear();
    }
  }
}

TEST(YellowDicePushingGreenDice, moveSx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      GreenDice gd(c1, 2);
      YellowDice yd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &yd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c2))->move("sx", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i-1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i);
      dices.clear();
    }
  }
}

TEST(GreenDicePushingYellowDice, moveSx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j);
      GreenDice gd(c1, 1);
      YellowDice yd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &yd));
      EXPECT_FALSE(dices.at(P2D::cellToP2D(c1))->move("sx", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i);
      dices.clear();
    }
  }
}

TEST(oneGreenDice, moveDx0Moves){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      GreenDice gd(c, 0);
      dices.insert(pair<P2D, Dice *>(P2D(c.getX(), c.getY()), &gd));
      EXPECT_FALSE(dices.at(P2D::cellToP2D(c))->move("dx", dices, __func__, 0));
      dices.clear();
    }
  }
}

TEST(oneGreenDice, moveDx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      GreenDice gd(c, 3);
      dices.insert(pair<P2D, Dice *>(P2D(c.getX(), c.getY()), &gd));
      int nMoves = dices.at(P2D::cellToP2D(c))->getNMoves();
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c))->move("dx", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c))->getPosition().getX(), i+nMoves);
      dices.clear();
    }
  }
}

TEST(twoGreenwDices_PushingEachOther, moveDx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+2);
      c2.setY(j);
      GreenDice gd1(c1, 3);
      GreenDice gd2(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &gd2));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c1))->move("dx", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+2);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingGreenDice, moveDx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-3; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j);
      GreenDice gd(c1, 2);
      WhiteDice wd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c2))->move("dx", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i+3);
      dices.clear();
    }
  }
}

TEST(GreenDicePushingWhiteDice, moveDx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      GreenDice gd(c1, 1);
      WhiteDice wd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &wd));
      EXPECT_FALSE(dices.at(P2D::cellToP2D(c1))->move("dx", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+1);
      dices.clear();
    }
  }
}

TEST(RedDicePushingGreenDice, moveDx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-3 ; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      RedDice rd(c1, 1);
      GreenDice gd(c2, 2);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &gd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c1))->move("dx", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+3);
      dices.clear();
    }
  }
}

TEST(GreenDicePushingRedDice, moveDx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      GreenDice gd(c1, 1);
      RedDice rd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &rd));
      EXPECT_FALSE(dices.at(P2D::cellToP2D(c1))->move("dx", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+1);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingGreenDice, moveDx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      YellowDice yd(c1, 1);
      GreenDice gd(c2, 2);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &yd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &gd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c1))->move("dx", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i+2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+1);
      dices.clear();
    }
  }
}

TEST(GreenDicePushingYellowDice, moveDx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      GreenDice gd(c1, 1);
      YellowDice yd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &yd));
      EXPECT_FALSE(dices.at(P2D::cellToP2D(c1))->move("dx", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+1);
      dices.clear();
    }
  }
}

TEST(oneGreenDice, moveDown0Moves){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      GreenDice gd(c, 0);
      dices.insert(pair<P2D, Dice *>(P2D(c.getX(), c.getY()), &gd));
      EXPECT_FALSE(dices.at(P2D::cellToP2D(c))->move("down", dices, __func__, 0));
      dices.clear();
    }
  }
}

TEST(oneGreenDice, moveDown){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      GreenDice gd(c, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c.getX(), c.getY()), &gd));
      int nMoves = dices.at(P2D::cellToP2D(c))->getNMoves();
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c))->move("down", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c))->getPosition().getY(), j+nMoves);
      dices.clear();
    }
  }
}

TEST(twoGreenDices_PushingEachOther, moveDown){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-3; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+3);
      GreenDice gd1(c1, 3);
      GreenDice gd2(c2, 3);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &gd2));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c1))->move("down", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j+2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+3);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingGreenDice, moveDown){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-3; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j);
      GreenDice gd(c1, 2);
      WhiteDice wd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c2))->move("down", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j+3);
      dices.clear();
    }
  }
}

TEST(GreenDicePushingWhiteDice, moveDown){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      GreenDice gd(c1, 1);
      WhiteDice wd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &wd));
      EXPECT_FALSE(dices.at(P2D::cellToP2D(c1))->move("down", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+1);
      dices.clear();
    }
  }
}

TEST(RedDicePushingGreenDice, moveDown){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-3; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j);
      GreenDice gd(c1, 2);
      RedDice rd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &rd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c2))->move("down", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j+3);
      dices.clear();
    }
  }
}

TEST(GreenDicePushingRedDice, moveDown){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      GreenDice gd(c1, 1);
      RedDice rd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &rd));
      EXPECT_FALSE(dices.at(P2D::cellToP2D(c1))->move("down", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+1);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingGreenDice, moveDown){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j);
      GreenDice gd(c1, 2);
      YellowDice yd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &yd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c2))->move("down", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j+1);
      dices.clear();
    }
  }
}

TEST(GreenDicePushingYellowDice, moveDown){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      GreenDice gd(c1, 1);
      YellowDice yd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &yd));
      EXPECT_FALSE(dices.at(P2D::cellToP2D(c1))->move("down", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+1);
      dices.clear();
    }
  }
}

TEST(oneGreenDice, moveUp0Moves){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      GreenDice gd(c, 0);
      dices.insert(pair<P2D, Dice *>(P2D(c.getX(), c.getY()), &gd));
      EXPECT_FALSE(dices.at(P2D::cellToP2D(c))->move("up", dices, __func__, 0));
      dices.clear();
    }
  }
}

TEST(oneGreenDice, moveUp){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c;
  for (int j = 3; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      GreenDice gd(c, 3);
      dices.insert(pair<P2D, Dice *>(P2D(c.getX(), c.getY()), &gd));
      int nMoves = dices.at(P2D::cellToP2D(c))->getNMoves();
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c))->move("up", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c))->getPosition().getY(), j-nMoves);
      dices.clear();
    }
  }
}

TEST(twoGreenDices_PushingEachOther, moveUp){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+3);
      GreenDice gd1(c1, 3);
      GreenDice gd2(c2, 3);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &gd2));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd1));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c2))->move("up", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingGreenDice, moveUp){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 2; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      GreenDice gd(c1, 2);
      WhiteDice wd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c2))->move("up", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j-2);
      dices.clear();
    }
  }
}

TEST(GreenDicePushingWhiteDice, moveUp){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      GreenDice gd(c2, 1);
      WhiteDice wd(c1, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &gd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &wd));
      EXPECT_FALSE(dices.at(P2D::cellToP2D(c2))->move("up", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j);
      dices.clear();
    }
  }
}

TEST(RedDicePushingGreenDice, moveUp){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 2; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      GreenDice gd(c1, 2);
      RedDice rd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c2))->move("up", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j-2);
      dices.clear();
    }
  }
}

TEST(GreenDicePushingRedDice, moveUp){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      GreenDice gd(c2, 1);
      RedDice rd(c1, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &gd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &rd));
      EXPECT_FALSE(dices.at(P2D::cellToP2D(c2))->move("up", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingGreenDice, moveUp){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      GreenDice gd(c1, 1);
      YellowDice yd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &yd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd));
      EXPECT_TRUE(dices.at(P2D::cellToP2D(c2))->move("up", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j-1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j);
      dices.clear();
    }
  }
}

TEST(GreenDicePushingYellowDice, moveUp){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      GreenDice gd(c2, 1);
      YellowDice yd(c1, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &gd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &yd));
      EXPECT_FALSE(dices.at(P2D::cellToP2D(c2))->move("up", dices, __func__, 0));
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j);
      dices.clear();
    }
  }
}

TEST(RedDicePushingWhiteDice, reverseMoveSx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      WhiteDice wd(c1, 1);
      RedDice rd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &rd));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c2))->reverseMove("sx", dices, __func__, 0);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i);
      dices.clear();
    }
  }
}

TEST(RedDicePushingWhiteDice, reverseMoveDx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j);
      WhiteDice wd(c1, 1);
      RedDice rd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &rd));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c2))->reverseMove("dx", dices, __func__, 0);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i+1);
      dices.clear();
    }
  }
}

TEST(RedDicePushingWhiteDice, reverseMoveUp){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 1; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      WhiteDice wd(c1, 1);
      RedDice rd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &rd));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c2))->reverseMove("up", dices, __func__, 0);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j);
      dices.clear();
    }
  }
}

TEST(RedDicePushingWhiteDice, reverseMoveDown){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j);
      WhiteDice wd(c1, 1);
      RedDice rd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &rd));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c2))->reverseMove("down", dices, __func__, 0);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j+1);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingRedDice, reverseMoveSx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH-1; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j);
      WhiteDice wd(c1, 1);
      RedDice rd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &rd));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("sx", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i-1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingRedDice, reverseMoveDx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      WhiteDice wd(c1, 1);
      RedDice rd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &rd));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("dx", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i+1);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingRedDice, reverseMoveUp){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 1; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j);
      WhiteDice wd(c1, 1);
      RedDice rd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &rd));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("up", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j-1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingRedDice, reverseMoveDown){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      WhiteDice wd(c1, 1);
      RedDice rd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &rd));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("down", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j+1);
      dices.clear();
    }
  }
}

TEST(YellowDicePushingWhiteDice, reverseMoveSx){
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
      WhiteDice wd0(c0, 1);
      WhiteDice wd1(c1, 1);
      YellowDice yd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c0.getX(), c0.getY()), &wd0));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &wd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &yd));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c2))->reverseMove("sx", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 3);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c0))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c0))->getPosition().getX(), i-1);
      dices.clear();
    }
  }
}

TEST(YellowDicePushingWhiteDice, reverseMoveDx){
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
      WhiteDice wd0(c0, 1);
      WhiteDice wd1(c1, 1);
      YellowDice yd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c0.getX(), c0.getY()), &wd0));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &wd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &yd));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c2))->reverseMove("dx", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 3);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c0))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i+2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c0))->getPosition().getX(), i+3);
      dices.clear();
    }
  }
}

TEST(YellowDicePushingWhiteDice, reverseMoveUp){
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
      WhiteDice wd0(c0, 1);
      WhiteDice wd1(c1, 1);
      YellowDice yd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c0.getX(), c0.getY()), &wd0));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &wd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &yd));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c2))->reverseMove("up", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 3);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c0))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c0))->getPosition().getY(), j-1);
      dices.clear();
    }
  }
}

TEST(YellowDicePushingWhiteDice, reverseMoveDown){
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
      WhiteDice wd0(c0, 1);
      WhiteDice wd1(c1, 1);
      YellowDice yd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c0.getX(), c0.getY()), &wd0));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &wd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &yd));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c2))->reverseMove("down", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 3);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c0))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j+2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c0))->getPosition().getY(), j+3);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingWhiteDice, reverseMoveSx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      WhiteDice wd(c1, 1);
      YellowDice yd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &yd));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c2))->reverseMove("sx", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i-1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingWhiteDice, reverseMoveDx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j);
      WhiteDice wd(c1, 1);
      YellowDice yd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &yd));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c2))->reverseMove("dx", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i+1);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingWhiteDice, reverseMoveUp){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 1; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      WhiteDice wd(c1, 1);
      YellowDice yd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &yd));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c2))->reverseMove("up", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j-1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingWhiteDice, reverseMoveDown){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j);
      WhiteDice wd(c1, 1);
      YellowDice yd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &yd));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c2))->reverseMove("down", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j+1);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingGreenDice, reverseMoveSx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH-1; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j);
      WhiteDice wd(c1, 1);
      GreenDice gd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &gd));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("sx", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i+1);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingGreenDice, reverseMoveDx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      WhiteDice wd(c1, 1);
      GreenDice gd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &gd));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("dx", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingGreenDice, reverseMoveUp){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 1; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j);
      WhiteDice wd(c1, 1);
      GreenDice gd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &gd));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("up", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j+1);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingGreenDice, reverseMoveDown){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+2);
      c2.setX(i);
      c2.setY(j+1);
      WhiteDice wd(c1, 1);
      GreenDice gd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &gd));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("up", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j+2);
      dices.clear();
    }
  }
}

TEST(YellowDicePushingRedDice, reverseMoveSx){
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
      RedDice rd(c0, 1);
      WhiteDice wd(c1, 1);
      YellowDice yd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c0.getX(), c0.getY()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &yd));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c2))->reverseMove("sx", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 3);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c0))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c0))->getPosition().getX(), i-1);
      dices.clear();
    }
  }
}

TEST(YellowDicePushingRedDice, reverseMoveDx){
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
      RedDice rd(c0, 1);
      WhiteDice wd(c1, 1);
      YellowDice yd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c0.getX(), c0.getY()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &yd));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c2))->reverseMove("dx", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 3);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c0))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i+2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c0))->getPosition().getX(), i+3);
      dices.clear();
    }
  }
}

TEST(YellowDicePushingRedDice, reverseMoveUp){
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
      RedDice rd(c0, 1);
      WhiteDice wd(c1, 1);
      YellowDice yd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c0.getX(), c0.getY()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &yd));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c2))->reverseMove("up", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 3);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c0))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c0))->getPosition().getY(), j-1);
      dices.clear();
    }
  }
}

TEST(YellowDicePushingRedDice, reverseMoveDown){
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
      RedDice rd(c0, 1);
      WhiteDice wd(c1, 1);
      YellowDice yd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c0.getX(), c0.getY()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &yd));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c2))->reverseMove("down", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 3);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c0))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j+2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c0))->getPosition().getY(), j+3);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingRedDice, reverseMoveSx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      RedDice rd(c1, 1);
      YellowDice yd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &yd));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c2))->reverseMove("sx", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i-1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingRedDice, reverseMoveDx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j);
      RedDice rd(c1, 1);
      YellowDice yd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &yd));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c2))->reverseMove("dx", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i+1);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingRedDice, reverseMoveUp){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 1; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      RedDice rd(c1, 1);
      YellowDice yd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &yd));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c2))->reverseMove("up", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j-1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingRedDice, reverseMoveDown){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j);
      RedDice rd(c1, 1);
      YellowDice yd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &yd));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c2))->reverseMove("down", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j+1);
      dices.clear();
    }
  }
}

TEST(RedDicePushingGreenDice, reverseMoveSx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH-1; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j);
      RedDice rd(c1, 1);
      GreenDice gd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &gd));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("sx", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i+1);
      dices.clear();
    }
  }
}

TEST(RedDicePushingGreenDice, reverseMoveDx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      RedDice rd(c1, 1);
      GreenDice gd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &gd));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("dx", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i);
      dices.clear();
    }
  }
}

TEST(RedDicePushingGreenDice, reverseMoveUp){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 1; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j);
      RedDice rd(c1, 1);
      GreenDice gd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &gd));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("up", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j+1);
      dices.clear();
    }
  }
}

TEST(RedDicePushingGreenDice, reverseMoveDown){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+2);
      c2.setX(i);
      c2.setY(j+1);
      RedDice rd(c1, 1);
      GreenDice gd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &gd));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("up", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j+2);
      dices.clear();
    }
  }
}

TEST(YellowDicePushingGreenDice, reverseMoveSx){
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
      WhiteDice wd(c0, 1);
      YellowDice rd(c1, 1);
      GreenDice gd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c0.getX(), c0.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &gd));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("sx", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c0))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i+2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c0))->getPosition().getX(), i);
      dices.clear();
    }
  }
}

TEST(YellowDicePushingGreenDice, reverseMoveDx){
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
      WhiteDice wd(c0, 1);
      YellowDice rd(c1, 1);
      GreenDice gd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c0.getX(), c0.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &gd));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("dx", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c0))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c0))->getPosition().getX(), i+2);
      dices.clear();
    }
  }
}

TEST(YellowDicePushingGreenDice, reverseMoveUp){
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
      WhiteDice wd(c0, 1);
      YellowDice rd(c1, 1);
      GreenDice gd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c0.getX(), c0.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &gd));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("up", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c0))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j+2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c0))->getPosition().getY(), j);
      dices.clear();
    }
  }
}

TEST(YellowDicePushingGreenDice, reverseMoveDown){
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
      WhiteDice wd(c0, 1);
      YellowDice rd(c1, 1);
      GreenDice gd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c0.getX(), c0.getY()), &wd));
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &rd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &gd));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("down", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c0))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c0))->getPosition().getY(), j+2);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingGreenDice, reverseMoveSx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      GreenDice gd(c1, 1);
      YellowDice yd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &yd));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c2))->reverseMove("sx", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i-1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingGreenDice, reverseMoveDx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j);
      GreenDice gd(c1, 1);
      YellowDice yd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &yd));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c2))->reverseMove("dx", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i+1);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingGreenDice, reverseMoveUp){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 1; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      GreenDice gd(c1, 1);
      YellowDice yd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &yd));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c2))->reverseMove("up", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j-1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingGreenDice, reverseMoveDown){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j);
      GreenDice gd(c1, 1);
      YellowDice yd(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &yd));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c2))->reverseMove("down", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j+1);
      dices.clear();
    }
  }
}

TEST(GreenDicePushingGreenDice, reverseMoveSx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      GreenDice gd1(c1, 1);
      GreenDice gd2(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &gd2));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c2))->reverseMove("sx", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i);
      dices.clear();
    }
  }
}

TEST(GreenDicePushingGreenDice, reverseMoveDx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      GreenDice gd1(c1, 1);
      GreenDice gd2(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &gd2));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("dx", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i);
      dices.clear();
    }
  }
}

TEST(GreenDicePushingGreenDice, reverseMoveUp){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 1; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      GreenDice gd1(c1, 1);
      GreenDice gd2(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &gd2));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c2))->reverseMove("up", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j);
      dices.clear();
    }
  }
}

TEST(GreenDicePushingGreenDice, reverseMoveDown){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      GreenDice gd1(c1, 1);
      GreenDice gd2(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &gd2));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("down", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j);
      dices.clear();
    }
  }
}

TEST(RedDicePushingRedDice, reverseMoveSx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      RedDice rd1(c1, 1);
      RedDice rd2(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &rd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &rd2));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c2))->reverseMove("sx", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i);
      dices.clear();
    }
  }
}

TEST(RedDicePushingRedDice, reverseMoveDx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      RedDice rd1(c1, 1);
      RedDice rd2(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &rd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &rd2));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("dx", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i);
      dices.clear();
    }
  }
}

TEST(RedDicePushingRedDice, reverseMoveUp){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 1; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      RedDice rd1(c1, 1);
      RedDice rd2(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &rd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &rd2));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c2))->reverseMove("up", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j);
      dices.clear();
    }
  }
}

TEST(RedDicePushingRedDice, reverseMoveDown){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      RedDice rd1(c1, 1);
      RedDice rd2(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &rd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &rd2));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("down", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingWhiteDice, reverseMoveSx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      WhiteDice wd1(c1, 1);
      WhiteDice wd2(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &wd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &wd2));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c2))->reverseMove("sx", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i-1);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingWhiteDice, reverseMoveDx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      WhiteDice wd1(c1, 1);
      WhiteDice wd2(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &wd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &wd2));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("dx", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i+1);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingWhiteDice, reverseMoveUp){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 1; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      WhiteDice wd1(c1, 1);
      WhiteDice wd2(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &wd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &wd2));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c2))->reverseMove("up", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j-1);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingWhiteDice, reverseMoveDown){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      WhiteDice wd1(c1, 1);
      WhiteDice wd2(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &wd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &wd2));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("down", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j+1);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingYellowDice, reverseMoveSx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      YellowDice yd1(c1, 1);
      YellowDice yd2(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &yd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &yd2));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c2))->reverseMove("sx", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i-1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingYellowDice, reverseMoveDx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      YellowDice yd1(c1, 1);
      YellowDice yd2(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &yd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &yd2));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("dx", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i+2);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingYellowDice, reverseMoveUp){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 1; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      YellowDice yd1(c1, 1);
      YellowDice wd2(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &yd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &wd2));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c2))->reverseMove("up", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j-1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j);
      dices.clear();
    }
  }
}

TEST(YellowDiceJumpingYellowDice, reverseMoveDown){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      YellowDice yd1(c1, 1);
      YellowDice yd2(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &yd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &yd2));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("down", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j+2);
      dices.clear();
    }
  }
}

TEST(oneYellowDice, reverseMoveSx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      YellowDice yd1(c1, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &yd1));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("sx", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i-1);
      res = dices.at(P2D::cellToP2D(c1))->reverseMove("sx", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      dices.clear();
    }
  }
}

TEST(oneYellowDice, reverseMoveDx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      YellowDice yd1(c1, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &yd1));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("dx", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i+1);
      res = dices.at(P2D::cellToP2D(c1))->reverseMove("dx", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      dices.clear();
    }
  }
}

TEST(oneYellowDice, reverseMoveUp){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1;
  for (int j = 1; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      YellowDice yd1(c1, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &yd1));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("up", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j-1);
      res = dices.at(P2D::cellToP2D(c1))->reverseMove("up", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      dices.clear();
    }
  }
}

TEST(oneYellowDice, reverseMoveDown){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1;
  for (int j = 0; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      YellowDice yd1(c1, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &yd1));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("down", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j+1);
      res = dices.at(P2D::cellToP2D(c1))->reverseMove("down", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      dices.clear();
    }
  }
}

TEST(oneWhiteDice, reverseMoveSx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      WhiteDice wd1(c1, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &wd1));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("sx", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i-1);
      res = dices.at(P2D::cellToP2D(c1))->reverseMove("sx", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      dices.clear();
    }
  }
}

TEST(oneWhiteDice, reverseMoveDx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      WhiteDice wd1(c1, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &wd1));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("dx", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i+1);
      res = dices.at(P2D::cellToP2D(c1))->reverseMove("dx", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      dices.clear();
    }
  }
}

TEST(oneWhiteDice, reverseMoveUp){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1;
  for (int j = 1; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      WhiteDice wd1(c1, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &wd1));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("up", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j-1);
      res = dices.at(P2D::cellToP2D(c1))->reverseMove("up", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      dices.clear();
    }
  }
}

TEST(oneWhiteDice, reverseMoveDown){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1;
  for (int j = 0; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      WhiteDice wd1(c1, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &wd1));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("down", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j+1);
      res = dices.at(P2D::cellToP2D(c1))->reverseMove("down", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      dices.clear();
    }
  }
}

TEST(oneRedDice, reverseMoveSx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      RedDice rd1(c1, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &rd1));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("sx", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i-1);
      res = dices.at(P2D::cellToP2D(c1))->reverseMove("sx", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      dices.clear();
    }
  }
}

TEST(oneRedDice, reverseMoveDx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      RedDice rd1(c1, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &rd1));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("dx", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i+1);
      res = dices.at(P2D::cellToP2D(c1))->reverseMove("dx", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      dices.clear();
    }
  }
}

TEST(oneRedDice, reverseMoveUp){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1;
  for (int j = 1; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      RedDice rd1(c1, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &rd1));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("up", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j-1);
      res = dices.at(P2D::cellToP2D(c1))->reverseMove("up", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      dices.clear();
    }
  }
}

TEST(oneRedDice, reverseMoveDown){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1;
  for (int j = 0; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      RedDice rd1(c1, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &rd1));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("down", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j+1);
      res = dices.at(P2D::cellToP2D(c1))->reverseMove("down", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      dices.clear();
    }
  }
}

TEST(oneGreenDice, reverseMoveSx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 2; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      GreenDice gd1(c1, 2);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd1));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("sx", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i-2);
      res = dices.at(P2D::cellToP2D(c1))->reverseMove("sx", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      dices.clear();
    }
  }
}

TEST(oneGreenDice, reverseMoveDx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i);
      c1.setY(j);
      GreenDice gd1(c1, 2);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd1));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("dx", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i+2);
      res = dices.at(P2D::cellToP2D(c1))->reverseMove("dx", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      dices.clear();
    }
  }
}

TEST(oneGreenDice, reverseMoveUp){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1;
  for (int j = 2; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      GreenDice gd1(c1, 2);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd1));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("up", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j-2);
      res = dices.at(P2D::cellToP2D(c1))->reverseMove("up", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      dices.clear();
    }
  }
}

TEST(oneGreenDice, reverseMoveDown){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      GreenDice gd1(c1, 2);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd1));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("down", dices, __func__, false);
      EXPECT_TRUE(res.first);
      ASSERT_EQ(res.second, 2);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j+2);
      res = dices.at(P2D::cellToP2D(c1))->reverseMove("down", dices, __func__, false);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      dices.clear();
    }
  }
}

TEST(GreenDicePushingWhiteDice, reverseMoveSx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH-1; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j);
      GreenDice gd1(c1, 0);
      WhiteDice wd1(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &wd1));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("sx", dices, __func__, false, true);
      if(c1.getX() == MAP_WIDTH-1){
        EXPECT_TRUE(res.first);
        ASSERT_EQ(res.second, 1+c1.getX()-c2.getX());
        ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 0);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 0);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i-1);
      }else{
        EXPECT_FALSE(res.first);
        ASSERT_EQ(res.second, 0);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 0);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 1);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i+1);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i);
      }
      dices.clear();
    }
  }
}

TEST(GreenDicePushingWhiteDice, reverseMoveDx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      GreenDice gd1(c1, 0);
      WhiteDice wd1(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &wd1));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("dx", dices, __func__, false, true);
      if(c1.getX() == 0){
        EXPECT_TRUE(res.first);
        ASSERT_EQ(res.second, 1+c2.getX()-c1.getX());
        ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 0);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 0);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i+1);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+2);
      }else{
        EXPECT_FALSE(res.first);
        ASSERT_EQ(res.second, 0);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 0);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 1);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+1);
      }
      dices.clear();
    }
  }
}

TEST(GreenDicePushingWhiteDice, reverseMoveUp){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 1; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j);
      GreenDice gd1(c1, 0);
      WhiteDice wd1(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &wd1));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("up", dices, __func__, false, true);
      if(c1.getY() == MAP_HEIGHT-1){
        EXPECT_TRUE(res.first);
        ASSERT_EQ(res.second, 1+c1.getY()-c2.getY());
        ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 0);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 0);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j-1);
      }else{
        EXPECT_FALSE(res.first);
        ASSERT_EQ(res.second, 0);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 0);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 1);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j+1);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j);
      }
      dices.clear();
    }
  }
}

TEST(GreenDicePushingWhiteDice, reverseMoveDown){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      GreenDice gd1(c1, 0);
      WhiteDice wd1(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &wd1));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("down", dices, __func__, false, true);
      if(c1.getY() == 0){
        EXPECT_TRUE(res.first);
        ASSERT_EQ(res.second, 1+c2.getY()-c1.getY());
        ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 0);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 0);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j+1);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+2);
      }else{
        EXPECT_FALSE(res.first);
        ASSERT_EQ(res.second, 0);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 0);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 1);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+1);
      }
      dices.clear();
    }
  }
}

TEST(GreenDicePushingRedDice, reverseMoveSx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH-1; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j);
      GreenDice gd1(c1, 0);
      RedDice rd1(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &rd1));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("sx", dices, __func__, false, true);
      if(c1.getX() == MAP_WIDTH-1){
        EXPECT_TRUE(res.first);
        ASSERT_EQ(res.second, 1+c1.getX()-c2.getX());
        ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 0);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 0);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i-1);
      }else{
        EXPECT_FALSE(res.first);
        ASSERT_EQ(res.second, 0);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 0);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 1);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i+1);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i);
      }
      dices.clear();
    }
  }
}

TEST(GreenDicePushingRedDice, reverseMoveDx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      GreenDice gd1(c1, 0);
      RedDice rd1(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &rd1));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("dx", dices, __func__, false, true);
      if(c1.getX() == 0){
        EXPECT_TRUE(res.first);
        ASSERT_EQ(res.second, 1+c2.getX()-c1.getX());
        ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 0);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 0);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i+1);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+2);
      }else{
        EXPECT_FALSE(res.first);
        ASSERT_EQ(res.second, 0);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 0);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 1);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+1);
      }
      dices.clear();
    }
  }
}

TEST(GreenDicePushingRedDice, reverseMoveUp){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 1; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j);
      GreenDice gd1(c1, 0);
      RedDice rd1(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &rd1));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("up", dices, __func__, false, true);
      if(c1.getY() == MAP_HEIGHT-1){
        EXPECT_TRUE(res.first);
        ASSERT_EQ(res.second, 1+c1.getY()-c2.getY());
        ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 0);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 0);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j-1);
      }else{
        EXPECT_FALSE(res.first);
        ASSERT_EQ(res.second, 0);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 0);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 1);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j+1);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j);
      }
      dices.clear();
    }
  }
}

TEST(GreenDicePushingRedDice, reverseMoveDown){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      GreenDice gd1(c1, 0);
      RedDice rd1(c2, 1);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &rd1));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("down", dices, __func__, false, true);
      if(c1.getY() == 0){
        EXPECT_TRUE(res.first);
        ASSERT_EQ(res.second, 1+c2.getY()-c1.getY());
        ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 0);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 0);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j+1);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+2);
      }else{
        EXPECT_FALSE(res.first);
        ASSERT_EQ(res.second, 0);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 0);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 1);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j);
        ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+1);
      }
      dices.clear();
    }
  }
}

TEST(GreenDicePushingWhiteDice0Moves, reverseMoveSx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 1; i < MAP_WIDTH-1; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j);
      GreenDice gd1(c1, 0);
      WhiteDice wd1(c2, 0);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &wd1));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("sx", dices, __func__, false, true);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i);
      dices.clear();
    }
  }
}

TEST(GreenDicePushingWhiteDice0Moves, reverseMoveDx){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-2; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      GreenDice gd1(c1, 0);
      WhiteDice wd1(c2, 0);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &wd1));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("dx", dices, __func__, false, true);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getX(), i);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getX(), i+1);
      dices.clear();
    }
  }
}

TEST(GreenDicePushingWhiteDice0Moves, reverseMoveUp){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 1; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j);
      GreenDice gd1(c1, 0);
      WhiteDice wd1(c2, 0);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &wd1));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("up", dices, __func__, false, true);
      EXPECT_FALSE(res.first);
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j+1);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j);
      dices.clear();
    }
  }
}

TEST(GreenDicePushingWhiteDice0Moves, reverseMoveDown){
  unordered_map<P2D, Dice*, P2D::HashFun> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-2; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      GreenDice gd1(c1, 0);
      WhiteDice wd1(c2, 0);
      dices.insert(pair<P2D, Dice *>(P2D(c1.getX(), c1.getY()), &gd1));
      dices.insert(pair<P2D, Dice *>(P2D(c2.getX(), c2.getY()), &wd1));
      pair<bool, int> res = dices.at(P2D::cellToP2D(c1))->reverseMove("down", dices, __func__, false, true);
      EXPECT_FALSE(res.first);  
      ASSERT_EQ(res.second, 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getNMoves(), 0);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c1))->getPosition().getY(), j);
      ASSERT_EQ(dices.at(P2D::cellToP2D(c2))->getPosition().getY(), j+1);
      dices.clear();
    }
  }
}

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}