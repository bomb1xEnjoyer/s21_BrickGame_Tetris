#include "tetris_UI.h"

void ShowGUI(GameInfo* Game) {
  start_color();
  COLOR_INIT;
  ShowFigure(Game);
  ShowNextFigure(Game);
  ShowGame(Game);
  ShowInfo(Game);
  if (Game->pause) Pause();
}

void StartScreen() {
  mvprintw(3, 3, "BrickGame")
}