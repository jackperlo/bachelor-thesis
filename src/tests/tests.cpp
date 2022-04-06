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

TEST(oneWhiteDice, moveSx0Moves){
  list<Dice *> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      WhiteDice *wd = new WhiteDice(c, 0);
      dices.push_back(wd);
      list<Dice *>::iterator it = dices.begin();
      EXPECT_FALSE((*it)->move("sx", dices, __func__));
      dices.clear();
    }
  }
}

TEST(twoWhiteDices_PushingEachOther0Moves, moveSx){
  list<Dice *> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      WhiteDice *wd1 = new WhiteDice(c1, 0);
      WhiteDice *wd2 = new WhiteDice(c2, 1);
      dices.push_back(wd2);
      dices.push_back(wd1); 
      //dices = [wd2, wd1];
      // wd2 pushes to the left wd1:
      // map: |    | wd1 | wd2 |    |    |
      list<Dice *>::iterator it = dices.begin(); //get wd2
      EXPECT_TRUE((*it)->move("sx", dices, __func__));
      ASSERT_EQ((*it)->getPosition().getX(), i);
      advance(it, 1);
      ASSERT_EQ((*it)->getPosition().getX(), i-1);
      dices.clear();
    }
  }
}

TEST(oneWhiteDice, moveSx){
  list<Dice *> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      WhiteDice *wd = new WhiteDice(c, 1);
      dices.push_back(wd);
      list<Dice *>::iterator it = dices.begin();
      EXPECT_TRUE((*it)->move("sx", dices, __func__));
      dices.clear();
    }
  }
}

TEST(twoWhiteDices_PushingEachOther, moveSx){
  list<Dice *> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      WhiteDice *wd1 = new WhiteDice(c1, 1);
      WhiteDice *wd2 = new WhiteDice(c2, 1);
      dices.push_back(wd2);
      dices.push_back(wd1); 
      //dices = [wd2, wd1];
      // wd2 pushes to the left wd1:
      // map: |    | wd1 | wd2 |    |    |
      list<Dice *>::iterator it = dices.begin(); //get wd2
      EXPECT_TRUE((*it)->move("sx", dices, __func__));
      ASSERT_EQ((*it)->getPosition().getX(), i);
      advance(it, 1);
      ASSERT_EQ((*it)->getPosition().getX(), i-1);
      dices.clear();
    }
  }
}

TEST(oneWhiteDice, moveDx0Moves){
  list<Dice *> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      WhiteDice *wd = new WhiteDice(c, 0);
      dices.push_back(wd);
      list<Dice *>::iterator it = dices.begin();
      EXPECT_FALSE((*it)->move("dx", dices, __func__));
      dices.clear();
    }
  }
}

TEST(twoWhiteDices_PushingEachOther0Moves, moveDx){
  list<Dice *> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      WhiteDice *wd1 = new WhiteDice(c1, 1);
      WhiteDice *wd2 = new WhiteDice(c2, 0);
      dices.push_back(wd1);
      dices.push_back(wd2);
      list<Dice *>::iterator it = dices.begin();
      EXPECT_TRUE((*it)->move("dx", dices, __func__));
      ASSERT_EQ((*it)->getPosition().getX(), i+1);
      advance(it, 1);
      ASSERT_EQ((*it)->getPosition().getX(), i+2);
      dices.clear();
    }
  }
}

TEST(oneWhiteDice, moveDx){
  list<Dice *> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      WhiteDice *wd = new WhiteDice(c, 1);
      dices.push_back(wd);
      list<Dice *>::iterator it = dices.begin();
      EXPECT_TRUE((*it)->move("dx", dices, __func__));
      dices.clear();
    }
  }
}

TEST(twoWhiteDices_PushingEachOther, moveDx){
  list<Dice *> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      WhiteDice *wd1 = new WhiteDice(c1, 1);
      WhiteDice *wd2 = new WhiteDice(c2, 1);
      dices.push_back(wd1);
      dices.push_back(wd2);
      list<Dice *>::iterator it = dices.begin();
      EXPECT_TRUE((*it)->move("dx", dices, __func__));
      ASSERT_EQ((*it)->getPosition().getX(), i+1);
      advance(it, 1);
      ASSERT_EQ((*it)->getPosition().getX(), i+2);
      dices.clear();
    }
  }
}

TEST(oneWhiteDice0Moves, moveUp){
  list<Dice *> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      WhiteDice *wd = new WhiteDice(c, 0);
      dices.push_back(wd);
      list<Dice *>::iterator it = dices.begin();
      EXPECT_FALSE((*it)->move("up", dices, __func__));
      dices.clear();
    }
  }
}

TEST(twoWhiteDices_PushingEachOther0Moves, moveUp){
  list<Dice *> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      WhiteDice *wd1 = new WhiteDice(c1, 0);
      WhiteDice *wd2 = new WhiteDice(c2, 1);
      dices.push_back(wd2);
      dices.push_back(wd1);
      list<Dice *>::iterator it = dices.begin();
      EXPECT_TRUE((*it)->move("up", dices, __func__));
      ASSERT_EQ((*it)->getPosition().getY(), j);
      advance(it, 1);
      ASSERT_EQ((*it)->getPosition().getY(), j-1);
      dices.clear();
    }
  }
}

TEST(oneWhiteDice, moveUp){
  list<Dice *> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      WhiteDice *wd = new WhiteDice(c, 1);
      dices.push_back(wd);
      list<Dice *>::iterator it = dices.begin();
      EXPECT_TRUE((*it)->move("up", dices, __func__));
      dices.clear();
    }
  }
}

TEST(twoWhiteDices_PushingEachOther, moveUp){
  list<Dice *> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      WhiteDice *wd1 = new WhiteDice(c1, 1);
      WhiteDice *wd2 = new WhiteDice(c2, 1);
      dices.push_back(wd2);
      dices.push_back(wd1);
      list<Dice *>::iterator it = dices.begin();
      EXPECT_TRUE((*it)->move("up", dices, __func__));
      ASSERT_EQ((*it)->getPosition().getY(), j);
      advance(it, 1);
      ASSERT_EQ((*it)->getPosition().getY(), j-1);
      dices.clear();
    }
  }
}

TEST(oneWhiteDice0Moves, moveDown){
  list<Dice *> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      WhiteDice *wd = new WhiteDice(c, 0);
      dices.push_back(wd);
      list<Dice *>::iterator it = dices.begin();
      EXPECT_FALSE((*it)->move("down", dices, __func__));
      dices.clear();
    }
  }
}

TEST(twoWhiteDices_PushingEachOther0Moves, moveDown){
  list<Dice *> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      WhiteDice *wd1 = new WhiteDice(c1, 1);
      WhiteDice *wd2 = new WhiteDice(c2, 0);
      dices.push_back(wd1);
      dices.push_back(wd2);
      list<Dice *>::iterator it = dices.begin();
      EXPECT_TRUE((*it)->move("down", dices, __func__));
      ASSERT_EQ((*it)->getPosition().getY(), j+1);
      advance(it, 1);
      ASSERT_EQ((*it)->getPosition().getY(), j+2);
      dices.clear();
    }
  }
}

TEST(oneWhiteDice, moveDown){
  list<Dice *> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      WhiteDice *wd = new WhiteDice(c, 1);
      dices.push_back(wd);
      list<Dice *>::iterator it = dices.begin();
      EXPECT_TRUE((*it)->move("down", dices, __func__));
      dices.clear();
    }
  }
}

TEST(twoWhiteDices_PushingEachOther, moveDown){
  list<Dice *> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      WhiteDice *wd1 = new WhiteDice(c1, 1);
      WhiteDice *wd2 = new WhiteDice(c2, 1);
      dices.push_back(wd1);
      dices.push_back(wd2);
      list<Dice *>::iterator it = dices.begin();
      EXPECT_TRUE((*it)->move("down", dices, __func__));
      ASSERT_EQ((*it)->getPosition().getY(), j+1);
      advance(it, 1);
      ASSERT_EQ((*it)->getPosition().getY(), j+2);
      dices.clear();
    }
  }
}

TEST(oneRedDice, moveSx0Moves){
  list<Dice *> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      RedDice *rd = new RedDice(c, 0);
      dices.push_back(rd);
      list<Dice *>::iterator it = dices.begin();
      EXPECT_FALSE((*it)->move("sx", dices, __func__));
      dices.clear();
    }
  }
}

TEST(twoRedDices_PushingEachOther0Moves, moveSx){
  list<Dice *> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      RedDice *rd1 = new RedDice(c1, 0);
      RedDice *rd2 = new RedDice(c2, 1);
      dices.push_back(rd2);
      dices.push_back(rd1); 
      list<Dice *>::iterator it = dices.begin();
      EXPECT_FALSE((*it)->move("sx", dices, __func__));
      ASSERT_EQ((*it)->getPosition().getX(), i+1);
      advance(it, 1);
      ASSERT_EQ((*it)->getPosition().getX(), i);
      dices.clear();
    }
  }
}

TEST(oneRedDice, moveSx){
  list<Dice *> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      RedDice *rd = new RedDice(c, 1);
      dices.push_back(rd);
      list<Dice *>::iterator it = dices.begin();
      EXPECT_TRUE((*it)->move("sx", dices, __func__));
      dices.clear();
    }
  }
}

TEST(twoRedDices_PushingEachOther, moveSx){
  list<Dice *> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      RedDice *rd1 = new RedDice(c1, 1);
      RedDice *rd2 = new RedDice(c2, 1);
      dices.push_back(rd2);
      dices.push_back(rd1); 
      list<Dice *>::iterator it = dices.begin();
      EXPECT_FALSE((*it)->move("sx", dices, __func__));
      ASSERT_EQ((*it)->getPosition().getX(), i+1);
      advance(it, 1);
      ASSERT_EQ((*it)->getPosition().getX(), i);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingRedDice, moveSx){
  list<Dice *> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      RedDice *rd = new RedDice(c1, 1);
      WhiteDice *wd = new WhiteDice(c2, 1);
      dices.push_back(wd);
      dices.push_back(rd); 
      list<Dice *>::iterator it = dices.begin();
      EXPECT_FALSE((*it)->move("sx", dices, __func__));
      ASSERT_EQ((*it)->getPosition().getX(), i+1);
      advance(it, 1);
      ASSERT_EQ((*it)->getPosition().getX(), i);
      dices.clear();
    }
  }
}

TEST(RedDicePushingWhiteDice, moveSx){
  list<Dice *> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j);
      RedDice *rd = new RedDice(c1, 1);
      WhiteDice *wd = new WhiteDice(c2, 1);
      dices.push_back(rd); 
      dices.push_back(wd);
      list<Dice *>::iterator it = dices.begin();
      EXPECT_TRUE((*it)->move("sx", dices, __func__));
      ASSERT_EQ((*it)->getPosition().getX(), i);
      advance(it, 1);
      ASSERT_EQ((*it)->getPosition().getX(), i-1);
      dices.clear();
    }
  }
}

TEST(RedDicePushingWhiteDice0Moves, moveSx){
  list<Dice *> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j);
      RedDice *rd = new RedDice(c1, 1);
      WhiteDice *wd = new WhiteDice(c2, 0);
      dices.push_back(rd); 
      dices.push_back(wd);
      list<Dice *>::iterator it = dices.begin();
      EXPECT_TRUE((*it)->move("sx", dices, __func__));
      ASSERT_EQ((*it)->getPosition().getX(), i);
      advance(it, 1);
      ASSERT_EQ((*it)->getPosition().getX(), i-1);
      dices.clear();
    }
  }
}

TEST(oneRedDice, moveDx0Moves){
  list<Dice *> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      RedDice *rd = new RedDice(c, 0);
      dices.push_back(rd);
      list<Dice *>::iterator it = dices.begin();
      EXPECT_FALSE((*it)->move("dx", dices, __func__));
      dices.clear();
    }
  }
}

TEST(oneRedDice, moveDx){
  list<Dice *> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      RedDice *rd = new RedDice(c, 1);
      dices.push_back(rd);
      list<Dice *>::iterator it = dices.begin();
      EXPECT_TRUE((*it)->move("dx", dices, __func__));
      dices.clear();
    }
  }
}

TEST(twoRedDices_PushingEachOther, moveDx){
  list<Dice *> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      RedDice *rd1 = new RedDice(c1, 1);
      RedDice *rd2 = new RedDice(c2, 1);
      dices.push_back(rd1);
      dices.push_back(rd2);
      list<Dice *>::iterator it = dices.begin();
      EXPECT_FALSE((*it)->move("dx", dices, __func__));
      ASSERT_EQ((*it)->getPosition().getX(), i);
      advance(it, 1);
      ASSERT_EQ((*it)->getPosition().getX(), i+1);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingRedDice, moveDx){
  list<Dice *> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i+1);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j);
      RedDice *rd = new RedDice(c1, 1);
      WhiteDice *wd = new WhiteDice(c2, 1);
      dices.push_back(wd);
      dices.push_back(rd); 
      list<Dice *>::iterator it = dices.begin();
      EXPECT_FALSE((*it)->move("dx", dices, __func__));
      ASSERT_EQ((*it)->getPosition().getX(), i);
      advance(it, 1);
      ASSERT_EQ((*it)->getPosition().getX(), i+1);
      dices.clear();
    }
  }
}

TEST(RedDicePushingWhiteDice, moveDx){
  list<Dice *> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      RedDice *rd = new RedDice(c1, 1);
      WhiteDice *wd = new WhiteDice(c2, 1);
      dices.push_back(rd); 
      dices.push_back(wd);
      list<Dice *>::iterator it = dices.begin();
      EXPECT_TRUE((*it)->move("dx", dices, __func__));
      ASSERT_EQ((*it)->getPosition().getX(), i+1);
      advance(it, 1);
      ASSERT_EQ((*it)->getPosition().getX(), i+2);
      dices.clear();
    }
  }
}

TEST(RedDicePushingWhiteDice0Moves, moveDx){
  list<Dice *> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      RedDice *rd = new RedDice(c1, 1);
      WhiteDice *wd = new WhiteDice(c2, 0);
      dices.push_back(rd); 
      dices.push_back(wd);
      list<Dice *>::iterator it = dices.begin();
      EXPECT_TRUE((*it)->move("dx", dices, __func__));
      ASSERT_EQ((*it)->getPosition().getX(), i+1);
      advance(it, 1);
      ASSERT_EQ((*it)->getPosition().getX(), i+2);
      dices.clear();
    }
  }
}

TEST(oneRedDice, moveUp0Moves){
  list<Dice *> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      RedDice *rd = new RedDice(c, 0);
      dices.push_back(rd);
      list<Dice *>::iterator it = dices.begin();
      EXPECT_FALSE((*it)->move("up", dices, __func__));
      dices.clear();
    }
  }
}

TEST(oneRedDice, moveUp){
  list<Dice *> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      RedDice *rd = new RedDice(c, 1);
      dices.push_back(rd);
      list<Dice *>::iterator it = dices.begin();
      EXPECT_TRUE((*it)->move("up", dices, __func__));
      dices.clear();
    }
  }
}

TEST(twoRedDices_PushingEachOther, moveUp){
  list<Dice *> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      RedDice *rd1 = new RedDice(c1, 1);
      RedDice *rd2 = new RedDice(c2, 1);
      dices.push_back(rd2);
      dices.push_back(rd1); 
      list<Dice *>::iterator it = dices.begin();
      EXPECT_FALSE((*it)->move("up", dices, __func__));
      ASSERT_EQ((*it)->getPosition().getY(), j+1);
      advance(it, 1);
      ASSERT_EQ((*it)->getPosition().getY(), j);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingRedDice, moveUp){
  list<Dice *> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      RedDice *rd = new RedDice(c1, 1);
      WhiteDice *wd = new WhiteDice(c2, 1);
      dices.push_back(wd);
      dices.push_back(rd); 
      list<Dice *>::iterator it = dices.begin();
      EXPECT_FALSE((*it)->move("up", dices, __func__));
      ASSERT_EQ((*it)->getPosition().getY(), j+1);
      advance(it, 1);
      ASSERT_EQ((*it)->getPosition().getY(), j);
      dices.clear();
    }
  }
}

TEST(RedDicePushingWhiteDice, moveUp){
  list<Dice *> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      RedDice *rd = new RedDice(c2, 1);
      WhiteDice *wd = new WhiteDice(c1, 1);
      dices.push_back(rd); 
      dices.push_back(wd);
      list<Dice *>::iterator it = dices.begin();
      EXPECT_TRUE((*it)->move("up", dices, __func__));
      ASSERT_EQ((*it)->getPosition().getY(), j);
      advance(it, 1);
      ASSERT_EQ((*it)->getPosition().getY(), j-1);
      dices.clear();
    }
  }
}

TEST(RedDicePushingWhiteDice0Moves, moveUp){
  list<Dice *> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      RedDice *rd = new RedDice(c2, 1);
      WhiteDice *wd = new WhiteDice(c1, 0);
      dices.push_back(rd); 
      dices.push_back(wd);
      list<Dice *>::iterator it = dices.begin();
      EXPECT_TRUE((*it)->move("up", dices, __func__));
      ASSERT_EQ((*it)->getPosition().getY(), j);
      advance(it, 1);
      ASSERT_EQ((*it)->getPosition().getY(), j-1);
      dices.clear();
    }
  }
}

TEST(oneRedDice, moveDown0Moves){
  list<Dice *> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      RedDice *rd = new RedDice(c, 0);
      dices.push_back(rd);
      list<Dice *>::iterator it = dices.begin();
      EXPECT_FALSE((*it)->move("down", dices, __func__));
      dices.clear();
    }
  }
}

TEST(oneRedDice, moveDown){
  list<Dice *> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      RedDice *rd = new RedDice(c, 1);
      dices.push_back(rd);
      list<Dice *>::iterator it = dices.begin();
      EXPECT_TRUE((*it)->move("down", dices, __func__));
      dices.clear();
    }
  }
}

TEST(twoRedDices_PushingEachOther, moveDown){
  list<Dice *> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      RedDice *rd1 = new RedDice(c1, 1);
      RedDice *rd2 = new RedDice(c2, 1);
      dices.push_back(rd1);
      dices.push_back(rd2);
      list<Dice *>::iterator it = dices.begin(); //get rd1
      EXPECT_FALSE((*it)->move("down", dices, __func__));
      ASSERT_EQ((*it)->getPosition().getY(), j);
      advance(it, 1);
      ASSERT_EQ((*it)->getPosition().getY(), j+1);
      dices.clear();
    }
  }
}

TEST(WhiteDicePushingRedDice, moveDown){
  list<Dice *> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j+1);
      c2.setX(i);
      c2.setY(j);
      RedDice *rd = new RedDice(c1, 1);
      WhiteDice *wd = new WhiteDice(c2, 1);
      dices.push_back(wd);
      dices.push_back(rd); 
      list<Dice *>::iterator it = dices.begin();
      EXPECT_FALSE((*it)->move("down", dices, __func__));
      ASSERT_EQ((*it)->getPosition().getY(), j);
      advance(it, 1);
      ASSERT_EQ((*it)->getPosition().getY(), j+1);
      dices.clear();
    }
  }
}

TEST(RedDicePushingWhiteDice, moveDown){
  list<Dice *> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      RedDice *rd = new RedDice(c1, 1);
      WhiteDice *wd = new WhiteDice(c2, 1);
      dices.push_back(rd); 
      dices.push_back(wd);
      list<Dice *>::iterator it = dices.begin();
      EXPECT_TRUE((*it)->move("down", dices, __func__));
      ASSERT_EQ((*it)->getPosition().getY(), j+1);
      advance(it, 1);
      ASSERT_EQ((*it)->getPosition().getY(), j+2);
      dices.clear();
    }
  }
}

TEST(RedDicePushingWhiteDice0Moves, moveDown){
  list<Dice *> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT-1; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      RedDice *rd = new RedDice(c1, 1);
      WhiteDice *wd = new WhiteDice(c2, 0);
      dices.push_back(rd); 
      dices.push_back(wd);
      list<Dice *>::iterator it = dices.begin();
      EXPECT_TRUE((*it)->move("down", dices, __func__));
      ASSERT_EQ((*it)->getPosition().getY(), j+1);
      advance(it, 1);
      ASSERT_EQ((*it)->getPosition().getY(), j+2);
      dices.clear();
    }
  }
}

TEST(oneYellowDice, moveSx0Moves){
  list<Dice *> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      YellowDice *rd = new YellowDice(c, 0);
      dices.push_back(rd);
      list<Dice *>::iterator it = dices.begin();
      EXPECT_FALSE((*it)->move("sx", dices, __func__));
      dices.clear();
    }
  }
}

TEST(oneYellowDice, moveSx){
  list<Dice *> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      YellowDice *rd = new YellowDice(c, 1);
      dices.push_back(rd);
      list<Dice *>::iterator it = dices.begin();
      EXPECT_TRUE((*it)->move("sx", dices, __func__));
      ASSERT_EQ((*it)->getPosition().getX(), i-1);
      dices.clear();
    }
  }
}

TEST(twoYellowDices_PushingEachOther, moveSx){
  list<Dice *> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      YellowDice *rd1 = new YellowDice(c1, 1);
      YellowDice *rd2 = new YellowDice(c2, 1);
      dices.push_back(rd2);
      dices.push_back(rd1); 
      list<Dice *>::iterator it = dices.begin();
      EXPECT_TRUE((*it)->move("sx", dices, __func__));
      ASSERT_EQ((*it)->getPosition().getX(), i-1);
      advance(it, 1);
      ASSERT_EQ((*it)->getPosition().getX(), i);
      dices.clear();
    }
  }
}

TEST(oneYellowDice, moveDx0Moves){
  list<Dice *> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      YellowDice *rd = new YellowDice(c, 0);
      dices.push_back(rd);
      list<Dice *>::iterator it = dices.begin();
      EXPECT_FALSE((*it)->move("dx", dices, __func__));
      dices.clear();
    }
  }
}

TEST(oneYellowDice, moveDx){
  list<Dice *> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      YellowDice *rd = new YellowDice(c, 1);
      dices.push_back(rd);
      list<Dice *>::iterator it = dices.begin();
      EXPECT_TRUE((*it)->move("dx", dices, __func__));
      ASSERT_EQ((*it)->getPosition().getX(), i+1);
      dices.clear();
    }
  }
}

TEST(twoYellowDices_PushingEachOther, moveDx){
  list<Dice *> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+1);
      c2.setY(j);
      YellowDice *rd1 = new YellowDice(c1, 1);
      YellowDice *rd2 = new YellowDice(c2, 1);
      dices.push_back(rd1);
      dices.push_back(rd2);
      list<Dice *>::iterator it = dices.begin();
      EXPECT_TRUE((*it)->move("dx", dices, __func__));
      ASSERT_EQ((*it)->getPosition().getX(), i+2);
      advance(it, 1);
      ASSERT_EQ((*it)->getPosition().getX(), i+1);
      dices.clear();
    }
  }
}

TEST(oneYellowDice, moveDown0Moves){
  list<Dice *> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      YellowDice *rd = new YellowDice(c, 0);
      dices.push_back(rd);
      list<Dice *>::iterator it = dices.begin();
      EXPECT_FALSE((*it)->move("down", dices, __func__));
      dices.clear();
    }
  }
}

TEST(oneYellowDice, moveDown){
  list<Dice *> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      YellowDice *rd = new YellowDice(c, 1);
      dices.push_back(rd);
      list<Dice *>::iterator it = dices.begin();
      EXPECT_TRUE((*it)->move("down", dices, __func__));
      ASSERT_EQ((*it)->getPosition().getY(), j+1);
      dices.clear();
    }
  }
}

TEST(twoYellowDices_PushingEachOther, moveDown){
  list<Dice *> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      YellowDice *rd1 = new YellowDice(c1, 1);
      YellowDice *rd2 = new YellowDice(c2, 1);
      dices.push_back(rd1);
      dices.push_back(rd2);
      list<Dice *>::iterator it = dices.begin(); 
      EXPECT_TRUE((*it)->move("down", dices, __func__));
      ASSERT_EQ((*it)->getPosition().getY(), j+2);
      advance(it, 1);
      ASSERT_EQ((*it)->getPosition().getY(), j+1);
      dices.clear();
    }
  }
}

TEST(oneYellowDice, moveUp0Moves){
  list<Dice *> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      YellowDice *rd = new YellowDice(c, 0);
      dices.push_back(rd);
      list<Dice *>::iterator it = dices.begin();
      EXPECT_FALSE((*it)->move("up", dices, __func__));
      dices.clear();
    }
  }
}

TEST(oneYellowDice, moveUp){
  list<Dice *> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      YellowDice *rd = new YellowDice(c, 1);
      dices.push_back(rd);
      list<Dice *>::iterator it = dices.begin();
      EXPECT_TRUE((*it)->move("up", dices, __func__));
      ASSERT_EQ((*it)->getPosition().getY(), j-1);
      dices.clear();
    }
  }
}

TEST(twoYellowDices_PushingEachOther, moveUp){
  list<Dice *> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+1);
      YellowDice *rd1 = new YellowDice(c1, 1);
      YellowDice *rd2 = new YellowDice(c2, 1);
      dices.push_back(rd2);
      dices.push_back(rd1); 
      list<Dice *>::iterator it = dices.begin();
      EXPECT_TRUE((*it)->move("up", dices, __func__));
      ASSERT_EQ((*it)->getPosition().getY(), j-1);
      advance(it, 1);
      ASSERT_EQ((*it)->getPosition().getY(), j);
      dices.clear();
    }
  }
}

TEST(oneGreenDice, moveSx0Moves){
  list<Dice *> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      GreenDice *rd = new GreenDice(c, 0);
      dices.push_back(rd);
      list<Dice *>::iterator it = dices.begin();
      EXPECT_FALSE((*it)->move("sx", dices, __func__));
      dices.clear();
    }
  }
}

TEST(oneGreenDice, moveSx){
  list<Dice *> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      GreenDice *rd = new GreenDice(c, 3);
      dices.push_back(rd);
      list<Dice *>::iterator it = dices.begin();
      int nMoves = (*it)->getNMoves();
      EXPECT_TRUE((*it)->move("sx", dices, __func__));
      ASSERT_EQ((*it)->getPosition().getX(), i-nMoves);
      dices.clear();
    }
  }
}

TEST(twoGreenDices_PushingEachOther, moveSx){
  list<Dice *> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+2);
      c2.setY(j);
      GreenDice *rd1 = new GreenDice(c1, 3);
      GreenDice *rd2 = new GreenDice(c2, 3);
      dices.push_back(rd2);
      dices.push_back(rd1); 
      list<Dice *>::iterator it = dices.begin();
      EXPECT_TRUE((*it)->move("sx", dices, __func__));
      ASSERT_EQ((*it)->getPosition().getX(), i+1);
      advance(it, 1);
      ASSERT_EQ((*it)->getPosition().getX(), i);
      dices.clear();
    }
  }
}

TEST(oneGreenDice, moveDx0Moves){
  list<Dice *> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      GreenDice *rd = new GreenDice(c, 0);
      dices.push_back(rd);
      list<Dice *>::iterator it = dices.begin();
      EXPECT_FALSE((*it)->move("dx", dices, __func__));
      dices.clear();
    }
  }
}

TEST(oneGreenDice, moveDx){
  list<Dice *> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      GreenDice *rd = new GreenDice(c, 3);
      dices.push_back(rd);
      list<Dice *>::iterator it = dices.begin();
      int nMoves = (*it)->getNMoves();
      EXPECT_TRUE((*it)->move("dx", dices, __func__));
      ASSERT_EQ((*it)->getPosition().getX(), i+nMoves);
      dices.clear();
    }
  }
}

TEST(twoGreenwDices_PushingEachOther, moveDx){
  list<Dice *> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i+2);
      c2.setY(j);
      GreenDice *rd1 = new GreenDice(c1, 3);
      GreenDice *rd2 = new GreenDice(c2, 3);
      dices.push_back(rd1);
      dices.push_back(rd2);
      list<Dice *>::iterator it = dices.begin();
      EXPECT_TRUE((*it)->move("dx", dices, __func__));
      ASSERT_EQ((*it)->getPosition().getX(), i+1);
      advance(it, 1);
      ASSERT_EQ((*it)->getPosition().getX(), i+2);
      dices.clear();
    }
  }
}

TEST(oneGreenDice, moveDown0Moves){
  list<Dice *> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      GreenDice *rd = new GreenDice(c, 0);
      dices.push_back(rd);
      list<Dice *>::iterator it = dices.begin();
      EXPECT_FALSE((*it)->move("down", dices, __func__));
      dices.clear();
    }
  }
}

TEST(oneGreenDice, moveDown){
  list<Dice *> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      GreenDice *rd = new GreenDice(c, 1);
      dices.push_back(rd);
      list<Dice *>::iterator it = dices.begin();
      int nMoves = (*it)->getNMoves();
      EXPECT_TRUE((*it)->move("down", dices, __func__));
      ASSERT_EQ((*it)->getPosition().getY(), j+nMoves);
      dices.clear();
    }
  }
}

TEST(twoGreenDices_PushingEachOther, moveDown){
  list<Dice *> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+3);
      GreenDice *rd1 = new GreenDice(c1, 3);
      GreenDice *rd2 = new GreenDice(c2, 3);
      dices.push_back(rd1);
      dices.push_back(rd2);
      list<Dice *>::iterator it = dices.begin(); 
      EXPECT_TRUE((*it)->move("down", dices, __func__));
      ASSERT_EQ((*it)->getPosition().getY(), j+2);
      advance(it, 1);
      ASSERT_EQ((*it)->getPosition().getY(), j+3);
      dices.clear();
    }
  }
}

TEST(oneGreenDice, moveUp0Moves){
  list<Dice *> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      GreenDice *rd = new GreenDice(c, 0);
      dices.push_back(rd);
      list<Dice *>::iterator it = dices.begin();
      EXPECT_FALSE((*it)->move("up", dices, __func__));
      dices.clear();
    }
  }
}

TEST(oneGreenDice, moveUp){
  list<Dice *> dices;
  Cell c;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH; i++){
      c.setX(i);
      c.setY(j);
      GreenDice *rd = new GreenDice(c, 3);
      dices.push_back(rd);
      list<Dice *>::iterator it = dices.begin();
      int nMoves = (*it)->getNMoves();
      EXPECT_TRUE((*it)->move("up", dices, __func__));
      ASSERT_EQ((*it)->getPosition().getY(), j-nMoves);
      dices.clear();
    }
  }
}

TEST(twoGreenDices_PushingEachOther, moveUp){
  list<Dice *> dices;
  Cell c1, c2;
  for (int j = 0; j < MAP_HEIGHT; j++){
    for (int i = 0; i < MAP_WIDTH-1; i++){
      c1.setX(i);
      c1.setY(j);
      c2.setX(i);
      c2.setY(j+3);
      GreenDice *rd1 = new GreenDice(c1, 3);
      GreenDice *rd2 = new GreenDice(c2, 3);
      dices.push_back(rd2);
      dices.push_back(rd1); 
      list<Dice *>::iterator it = dices.begin();
      EXPECT_TRUE((*it)->move("up", dices, __func__));
      ASSERT_EQ((*it)->getPosition().getY(), j+1);
      advance(it, 1);
      ASSERT_EQ((*it)->getPosition().getY(), j);
      dices.clear();
    }
  }
}

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}