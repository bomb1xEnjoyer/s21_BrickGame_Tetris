/**
 * @file tetris_UI.h
 * @brief User interface hedear file
 */
#ifndef TETRIS_UI_H
#define TETRIS_UI_H

#include "../../brick_game/tetris/tetris.h"

#define WINDOW_HEIGHT 23
#define WINDOW_WIDTH 12

#define SHIFT_X 2
#define SHIFT_Y 4

#define NEXT_POS_X 31
#define NEXT_POX_Y 12

#define COLOR_INIT                                                             \
  init_pair(I, 160, COLOR_BLACK);                                              \
  init_pair(J, 130, COLOR_BLACK);                                              \
  init_pair(L, 184, COLOR_BLACK);                                              \
  init_pair(O, 127, COLOR_BLACK);                                              \
  init_pair(S, 105, COLOR_BLACK);                                              \
  init_pair(T, 4, COLOR_BLACK);                                                \
  init_pair(Z, 176, COLOR_BLACK);                                              \
  init_pair(LEFT_BORDER, COLOR_WHITE, COLOR_BLACK);                            \
  init_pair(RIGHT_BORDER, COLOR_WHITE, COLOR_BLACK);                           \
  init_pair(UPPER_BORDER, COLOR_WHITE, COLOR_BLACK);                           \
  init_pair(DOWN_BORDER, COLOR_WHITE, COLOR_BLACK);                            \
  init_pair(PAUSE, COLOR_BLACK, COLOR_RED);                                    \
  init_pair(255, COLOR_WHITE, COLOR_BLACK);

#endif /* TETRIS_UI_H */