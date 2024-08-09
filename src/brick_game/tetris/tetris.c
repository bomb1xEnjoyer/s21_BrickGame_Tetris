#include "tetris.h"

#include "../../gui/cli/tetris_UI.h"
#include "defines.h"
#include "fsm.h"
#include "objects.h"

void GameLoop(GameInfo *Game) {
  GAME_INIT(Game);
  Game->file = fopen("highscore.txt", "r+");
  if (Game->file) {
    fscanf(Game->file, "%d", &Game->highscore);
    fclose(Game->file);
  }
  while (Game->play) {
    clear();
    StateMachine(Game);
    refresh();
  }
  GameOver(Game);
  FREE_MEMORY(Game);
}

void GameOver(GameInfo *Game) {
  cbreak();
  clear();
  Game->file = fopen("highscore.txt", "w+");
  fprintf(Game->file, "%d", Game->highscore);
  fclose(Game->file);
  PrintGameOver(Game);
  getch();
}

void StateMachine(GameInfo *Game) {
  switch (Game->state) {
    case START:
      StartScreen();
      getch();
      Game->state = SPAWN;
      halfdelay(1);
      break;
    case SPAWN:
      SPAWNER(Game);
      Game->state = MOVING;
      while (IsColliding(Game).upper_collision > 0 && MoveDown(Game))
        ;
      break;
    case MOVING:
      ShowGUI(Game);
      MoveDowmCycle(Game);
      Keys key = getch();
      MoveFigure(Game, key);
      break;
    case SHIFTING:
      int can_shift = 1;
      if (!Game->pause) can_shift = MoveDown(Game);
      if (can_shift) Game->state = MOVING;
      break;
    case ATTACHING:
      AttachingFigure(Game);
      break;
    case GAME_OVER:
      Game->play = false;
      break;
    default:
      break;
  }
}