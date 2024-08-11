#include "../../gui/cli/tetris_UI.h"
#include "defines.h"
#include "fsm.h"
#include "objects.h"
#include "tetris.h"

/**
 * @brief Figure moving function
 */
void MoveFigure(GameInfo *Game, Keys key) {
  switch (key) {
  case UP:
    if (!Game->pause) {
      RotateFigure(Game);
      Game->move_count--;
    }
    break;
  case DOWN:
    if (!Game->pause) {
      MoveDown(Game);
      Game->move_count -= 2;
    }
    break;
  case LEFT:
    if (!Game->pause) {
      MoveLeft(Game);
      Game->move_count--;
    }
    break;
  case RIGHT:
    if (!Game->pause) {
      MoveRight(Game);
      Game->move_count--;
    }
    break;
  case SPACE:
    if (!Game->pause) {
      DropDown(Game);
      Game->move_count--;
    }
    break;
  case PAUSE_KEY:
    if (!Game->pause)
      Game->pause = true;
    else
      Game->pause = false;
    break;
  case EXIT:
    Game->state = GAME_OVER;
    break;
  default:
    break;
  }
}

/**
 * @brief Figure rotating function
 */
void RotateFigure(GameInfo *Game) {
  Collision coll = IsColliding(Game);
  if (coll.rotation_collision > 2) {
    ;
  } else {
    Figure rotated_figure;
    CreateFigure(&rotated_figure, Game->figure.type);

    for (int i = 0; i < Game->figure.size; i++)
      for (int j = 0; j < Game->figure.size; j++)
        rotated_figure.block[i][Game->figure.size - j - 1] =
            Game->figure.block[j][i];

    TakeCollide(&rotated_figure);

    for (int i = 0; i < Game->figure.size; i++)
      for (int j = 0; j < Game->figure.size; j++)
        Game->figure.block[i][j] = rotated_figure.block[i][j];

    FreeFigure(&rotated_figure);

    while (true) {
      coll = IsColliding(Game);
      if (coll.inner_collision) {
        if (coll.left_collision && !coll.right_collision)
          Game->figure.x++;
        else if (!coll.left_collision && coll.right_collision)
          Game->figure.x--;
        else if (coll.down_collision)
          Game->figure.y--;
      } else
        break;
    }
  }
}

/**
 * @brief Drop down figure function
 */
void DropDown(GameInfo *Game) {
  int can_move_down = 1;
  while (can_move_down)
    can_move_down = MoveDown(Game);
}

/**
 * @brief Simple rotate
 */
void Rotate(GameInfo *Game) {
  Figure rotated_figure;
  CreateFigure(&rotated_figure, Game->next_figure.type);

  for (int i = 0; i < Game->next_figure.size; i++)
    for (int j = 0; j < Game->next_figure.size; j++)
      rotated_figure.block[i][Game->next_figure.size - 1 - j] =
          Game->next_figure.block[i][j];

  TakeCollide(&rotated_figure);

  for (int i = 0; i < Game->next_figure.size; i++)
    for (int j = 0; j < Game->next_figure.size; j++)
      Game->next_figure.block[i][j] = rotated_figure.block[i][j];

  FreeFigure(&rotated_figure);
}

/**
 * @brief Moving figure to the down function
 */
int MoveDown(GameInfo *Game) {
  int move = 1;
  Collision coll = IsColliding(Game);
  if (coll.down_collision == 0)
    Game->figure.y += 1;
  else {
    move = 0;
    Game->state = ATTACHING;
  }
  return move;
}

/**
 * @brief Moving figure to the left function
 */
void MoveLeft(GameInfo *Game) {
  Collision coll = IsColliding(Game);
  if (coll.left_collision == 0) {
    Game->figure.x -= 1;
    coll = IsColliding(Game);
    if (coll.inner_collision)
      Game->figure.x += 1;
  }
}

/**
 * @brief Moving figure to the right function
 */
void MoveRight(GameInfo *Game) {
  Collision coll = IsColliding(Game);
  if (coll.right_collision == 0) {
    Game->figure.x += 1;
    coll = IsColliding(Game);
    if (coll.inner_collision)
      Game->figure.x += 1;
  }
}

/**
 * @brief Find collisions function
 */
Collision IsColliding(GameInfo *Game) {
  Collision result;
  COLLISION_INIT(result);
  for (int i = 0; i < Game->figure.size; ++i) {
    for (int j = 0; j < Game->figure.size; ++j) {
      if (Game->figure.block[i][j] == LEFT_COLLISION &&
          (Game->field.block[Game->figure.y + i][Game->figure.x + j] != 0 &&
           Game->field.block[Game->figure.y + i][Game->figure.x + j] !=
               UPPER_BORDER)) {
        result.left_collision += 1;
        result.x_collision = j;
        result.y_collision = i;
      }
      if (Game->figure.block[i][j] == RIGHT_COLLISION &&
          (Game->field.block[Game->figure.y + i][Game->figure.x + j] != 0 &&
           Game->field.block[Game->figure.y + i][Game->figure.x + j] !=
               UPPER_BORDER)) {
        result.right_collision += 1;
        result.x_collision = j;
        result.y_collision = i;
      }
      if (Game->figure.block[i][j] == UPPER_COLLISION &&
          (Game->field.block[Game->figure.y + i][Game->figure.x + j] != 0 &&
           Game->field.block[Game->figure.y + i][Game->figure.x + j] !=
               UPPER_BORDER)) {
        result.upper_collision += 1;
        result.x_collision = j;
        result.y_collision = i;
      }
      if (Game->figure.block[i][j] == DOWN_COLLISION &&
          (Game->field.block[Game->figure.y + i][Game->figure.x + j] != 0 &&
           Game->field.block[Game->figure.y + i][Game->figure.x + j] !=
               UPPER_BORDER)) {
        result.down_collision += 1;
        result.x_collision = j;
        result.y_collision = i;
      }
      if (Game->figure.block[i][j] == Game->figure.type &&
          (Game->field.block[Game->figure.y + i][Game->figure.x + j] != 0 &&
           Game->field.block[Game->figure.y + i][Game->figure.x + j] !=
               UPPER_BORDER)) {
        result.inner_collision += 1;
        result.x_collision = j;
        result.y_collision = i;
      }
      if (Game->figure.block[i][j] == Game->figure.type &&
          (Game->field.block[Game->figure.y + i][Game->figure.x + j] ==
           UPPER_BORDER)) {
        result.upper_collision += 1;
        result.x_collision = j;
        result.y_collision = i;
      }
    }
  }
  return result;
}

/**
 * @brief Attaching figure function
 */
void AttachingFigure(GameInfo *Game) {
  Collision coll = IsColliding(Game);
  int filled_lines = 0;
  if (coll.upper_collision)
    Game->state = GAME_OVER;
  else {
    for (int i = 0; i < Game->figure.size; ++i)
      for (int j = 0; j < Game->figure.size; ++j)
        if (Game->figure.block[i][j] == Game->figure.type &&
            Game->field.block[Game->figure.y + i][Game->figure.x + j] !=
                UPPER_BORDER)
          Game->field.block[Game->figure.y + i][Game->figure.x + j] =
              Game->figure.type;
    filled_lines = CheckFullLines(Game);
    LevelCounter(Game, filled_lines);
    Game->state = SPAWN;
    Game->move_count = 40;
  }
}

/**
 * @brief Level counting function
 */
void LevelCounter(GameInfo *Game, int filled_lines) {
  Game->score += 100 * (pow(2, filled_lines) - 1);
  if (Game->highscore <= Game->score)
    Game->highscore = Game->score;
  if (Game->level < 10)
    Game->level = Game->score / Game->score_level + 1;
  else
    Game->level = 10;
  Game->speed = Game->level * 2;
}

/**
 * @brief Moving figure to the down without pressing key function
 */
void MoveDowmCycle(GameInfo *Game) {
  Game->move_count -= Game->speed;
  if (Game->move_count <= 0) {
    Game->state = SHIFTING;
    Game->move_count = 40;
  }
}