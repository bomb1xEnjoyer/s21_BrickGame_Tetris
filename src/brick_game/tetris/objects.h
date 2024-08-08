#ifndef OBJECTS_H
#define OBJECTS_H

#include "tetris.h"

typedef struct {
  int height;
  int width;
  BlockType **block;
  BlockType type;
} Field;

typedef struct {
  int x;
  int y;
  int size;
  int large;
  BlockType **block;
  BlockType type;
} Figure;

typedef struct {
  int left_collision;
  int right_collision;
  int upper_collision;
  int down_collision;
  int spawn_collision;
  int rotation_collision;
  int x_collision;
  int y_collision;
} Collision;

typedef struct {
  bool play;
  bool pause;
  Field field;
  Figure figure;
  Figure next_figure;
  int x_pos;
  int y_pos;
  int level;
  int score;
  int highscore;
  int speed;
  int move_count;
  int score_level;
  FILE *file;
  FiniteStateMachine state;
} GameInfo;

#endif /* OBJECTS_H */