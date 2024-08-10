#include "../../gui/cli/tetris_UI.h"
#include "defines.h"
#include "fsm.h"
#include "objects.h"
#include "tetris.h"

/**
 * @brief Function for allocating memory for the figure
 */
void CreateFigure(Figure *figure, BlockType type) {
  if (type == I) {
    figure->size = 8;
    figure->large = 4;
  } else if (type == O) {
    figure->size = 4;
    figure->large = 2;
  } else if (type >= J && type <= T && type != O) {
    figure->size = 5;
    figure->large = 3;
  }

  figure->type = type;
  figure->x = 0;
  figure->y = 0;

  figure->block = (BlockType **)calloc(figure->size, sizeof(BlockType *));
  for (int i = 0; i < figure->size; ++i)
    figure->block[i] = (BlockType *)calloc(figure->size, sizeof(BlockType));

  if (type == I) {
    INIT_FIGURE_I(figure);
  } else if (type == J) {
    INIT_FIGURE_J(figure);
  } else if (type == L) {
    INIT_FIGURE_L(figure);
  } else if (type == O) {
    INIT_FIGURE_O(figure);
  } else if (type == S) {
    INIT_FIGURE_S(figure);
  } else if (type == T) {
    INIT_FIGURE_T(figure);
  } else if (type == Z) {
    INIT_FIGURE_Z(figure);
  }

  TakeCollide(figure);
}

/**
 * @brief Function for taking collisions
 */
void TakeCollide(Figure *figure) {
  for (int i = figure->size - 1; i >= 0; --i)
    for (int j = 0; j < figure->size; ++j)
      if (figure->block[i][j] == figure->type) {
        if (figure->block[i][j + 1] != figure->type)
          figure->block[i][j + 1] = RIGHT_COLLISION;
        if (figure->block[i][j - 1] != figure->type)
          figure->block[i][j - 1] = LEFT_COLLISION;
        if (figure->block[i + 1][j] != figure->type)
          figure->block[i + 1][j] = DOWN_COLLISION;
        if (figure->block[i - 1][j] != figure->type)
          figure->block[i - 1][j] = UPPER_COLLISION;
      }
}

/**
 * @brief Clear memory with figure data
 */
void FreeFigure(Figure *figure) {
  for (int i = 0; i < figure->size; ++i) free(figure->block[i]);
  free(figure->block);
}