/**
 * @file defines.h
 * @brief Hedear file with defines
 */
#ifndef DEFINES_H
#define DEFINES_H

#include "tetris.h"

#define FIELD_HEIGHT 30
#define FIELD_WIDTH 16

#define FIELD_POS_X 0
#define FIELD_POS_Y 0

#define START_POS_X 0
#define START_POS_Y 0

#define INITSCR                                                                \
  srand(time(NULL));                                                           \
  initscr();                                                                   \
  keypad(stdscr, true);                                                        \
  noecho();                                                                    \
  curs_set(0);

#define rand_figure rand() % 7 + 1

#define GAME_INIT(GameInfo)                                                    \
  GameInfo->play = true;                                                       \
  GameInfo->pause = false;                                                     \
  CreateFigure(&GameInfo->next_figure, rand_figure);                           \
  CreateField(&GameInfo->field);                                               \
  GameInfo->x_pos = FIELD_POS_X;                                               \
  GameInfo->y_pos = FIELD_POS_Y;                                               \
  GameInfo->level = 1;                                                         \
  GameInfo->score = 0;                                                         \
  GameInfo->highscore = 0;                                                     \
  GameInfo->speed = GameInfo->level * 2;                                       \
  GameInfo->move_count = 40;                                                   \
  GameInfo->score_level = 600;                                                 \
  GameInfo->state = START;

#define FREE_MEMORY(GameInfo)                                                  \
  FreeField(&GameInfo->field);                                                 \
  FreeFigure(&GameInfo->figure);                                               \
  FreeFigure(&GameInfo->next_figure);

#define ROTATION_START(GameInfo) Rotate(GameInfo);

#define SPAWNER(GameInfo)                                                      \
  GameInfo->figure = GameInfo->next_figure;                                    \
  GameInfo->figure.x = START_POS_X + 8 - GameInfo->figure.large;               \
  GameInfo->figure.y = START_POS_Y;                                            \
  CreateFigure(&GameInfo->next_figure, rand_figure);                           \
  if (GameInfo->next_figure.type == GameInfo->figure.type)                     \
    CreateFigure(&GameInfo->next_figure, rand_figure);                         \
  for (int i = 0; i < rand() % 4; ++i)                                         \
    ROTATION_START(GameInfo);

#define COLLISION_INIT(collision)                                              \
  collision.left_collision = 0;                                                \
  collision.right_collision = 0;                                               \
  collision.upper_collision = 0;                                               \
  collision.down_collision = 0;                                                \
  collision.inner_collision = 0;                                               \
  collision.spawn_collision = 0;                                               \
  collision.rotation_collision = 0;                                            \
  collision.x_collision = 0;                                                   \
  collision.y_collision = 0;

#define INIT_FIGURE_I(figure)                                                  \
  figure->block[2][3] = type;                                                  \
  figure->block[3][3] = type;                                                  \
  figure->block[4][3] = type;                                                  \
  figure->block[5][3] = type;

#define INIT_FIGURE_J(figure)                                                  \
  figure->block[1][2] = type;                                                  \
  figure->block[2][2] = type;                                                  \
  figure->block[3][2] = type;                                                  \
  figure->block[3][1] = type;

#define INIT_FIGURE_L(figure)                                                  \
  figure->block[1][2] = type;                                                  \
  figure->block[2][2] = type;                                                  \
  figure->block[3][2] = type;                                                  \
  figure->block[3][3] = type;

#define INIT_FIGURE_O(figure)                                                  \
  figure->block[1][1] = type;                                                  \
  figure->block[1][2] = type;                                                  \
  figure->block[2][1] = type;                                                  \
  figure->block[2][2] = type;

#define INIT_FIGURE_S(figure)                                                  \
  figure->block[1][2] = type;                                                  \
  figure->block[2][2] = type;                                                  \
  figure->block[2][3] = type;                                                  \
  figure->block[3][3] = type;

#define INIT_FIGURE_T(figure)                                                  \
  figure->block[1][2] = type;                                                  \
  figure->block[2][1] = type;                                                  \
  figure->block[2][2] = type;                                                  \
  figure->block[2][3] = type;

#define INIT_FIGURE_Z(figure)                                                  \
  figure->block[1][2] = type;                                                  \
  figure->block[2][2] = type;                                                  \
  figure->block[2][1] = type;                                                  \
  figure->block[3][1] = type;

#endif /* DEFINES_H */