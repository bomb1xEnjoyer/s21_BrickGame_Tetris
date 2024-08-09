#include "brick_game/tetris/tetris.h"
#include "gui/cli/tetris_UI.h"

int main() {
  INITSCR;
  GameInfo Game;
  GameLoop(&Game);
  endwin();
  return 0;
}