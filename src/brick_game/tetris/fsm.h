#ifndef FSM_H
#define FSM_H

#include "tetris.h"

typedef enum {
  I = 1,
  J = 2,
  L = 3,
  O = 4,
  S = 5,
  Z = 6,
  T = 7,

  LEFT_BORDER = 8,
  RIGHT_BORDER = 9,
  UPPER_BORDER = 10,
  DOWN_BORDER = 11,

  LEFT_COLLISION = 12,
  RIGHT_COLLISION = 13,
  UPPER_COLLISION = 14,
  DOWN_COLLISION = 15,
} BlockType;

typedef enum {
  LEFT = KEY_LEFT,
  RIGHT = KEY_RIGHT,
  UP = KEY_UP,
  DOWN = KEY_DOWN,
  SPACE = ' ',
  PAUSE = 'p',
  EXIT = 'q',
} Keys;

typedef enum {
  START = 0,
  SPAWN = 1,
  MOVING = 2,
  SHIFTING = 3,
  ATTACHING = 4,
  PAUSE = 5,
  GAME_OVER = 6,
} FiniteStateMachine;

#endif /* FSM_H */