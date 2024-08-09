#include "../../gui/cli/tetris_UI.h"
#include "defines.h"
#include "fsm.h"
#include "objects.h"
#include "tetris.h"

void CreateField(Field *field) {
  field->height = FIELD_HEIGHT;
  field->width = FIELD_WIDTH;

  field->block = (BlockType **)calloc(FIELD_HEIGHT, sizeof(BlockType *));
  for (int i = 0; i < field->height; ++i)
    field->block[i] = (BlockType *)calloc(FIELD_WIDTH, sizeof(BlockType));

  for (int i = 0; i < field->height; ++i)
    for (int j = 0; j < field->width; ++j) {
      if (j <= 2)
        field->block[i][j] = LEFT_BORDER;
      else if (j >= FIELD_WIDTH - 3)
        field->block[i][j] = RIGHT_BORDER;
      else if (i <= 4)
        field->block[i][j] = UPPER_BORDER;
      else if (i >= FIELD_HEIGHT - 4)
        field->block[i][j] = DOWN_BORDER;
    }
}

void FreeField(Field *field) {
  for (int i = 0; i < field->height; ++i) free(field->block[i]);
  free(field->block);
}

int CheckFullLines(GameInfo *Game) {
  int full_lines = 0;
  for (int i = 0; i <= 20; ++i) {
    int columns = 0;
    for (int j = 0; j <= 10; ++j) {
      if (Game->field.block[i + 5][j + 3] == 0) break;
      ++columns;
    }
    if (columns >= 10) {
      ClearLine(Game, i);
      ++full_lines;
    }
  }
  return full_lines;
}

void ClearLine(GameInfo *Game, int line_number) {
  for (int i = line_number; i > 0; --i)
    for (int j = 0; j < FIELD_WIDTH - 6; ++j)
      if (i == 0)
        Game->field.block[i + 5][j + 3] = 0;
      else
        Game->field.block[i + 5][j + 3] = Game->field.block[i + 5 - 1][j + 3];
}