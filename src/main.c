#include "brick_game/tetris/tetris.h"
#include "gui/cli/tetris_UI.h"

/**
 * @brief Main function
 */
int main() {
  INITSCR;
  GameInfo Game;
  GameLoop(&Game);
  endwin();
  return 0;
}