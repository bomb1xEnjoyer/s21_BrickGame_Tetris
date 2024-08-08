#include "tetris_UI.h"

void ShowGUI(GameInfo *Game) {
  start_color();
  COLOR_INIT;
  ShowFigure(Game);
  ShowNextFigure(Game);
  ShowGame(Game);
  ShowInfo(Game);
  if (Game->pause) Pause();
}

void StartScreen() {
  mvprintw(3, 7, "+-+-+-+-+-+-+ +-+-+ +-+-+-+-+-+-+-+-+");
  mvprintw(4, 7, "|T|E|T|R|I|S| |b|y| |d|i|c|k|o|n|n|o|");
  mvprintw(5, 7, "+-+-+-+-+-+-+ +-+-+ +-+-+-+-+-+-+-+-+");
  mvprintw(8, 2, "+-+-+-+-+-+ +-+-+-+ +-+-+-+ +-+-+ +-+-+-+-+-+-+");
  mvprintw(9, 2, "|P|r|e|s|s| |a|n|y| |k|e|y| |t|o| |s|t|a|r|t|!|");
  mvprintw(10, 2, "+-+-+-+-+-+ +-+-+-+ +-+-+-+ +-+-+ +-+-+-+-+-+-+");
  mvprintw(11, 13, "________________________");
  mvaddch(12, 18, ACS_LARROW);
  mvprintw(12, 19, " - move left");
  mvaddch(13, 18, ACS_RARROW);
  mvprintw(13, 19, " - move right");
  mvaddch(14, 18, ACS_UARROW);
  mvprintw(14, 19, " - rotate");
  mvaddch(15, 18, ACS_DARROW);
  mvprintw(15, 19, " - move down");
  mvprintw(16, 14, "SPACE - place figure");
  mvprintw(17, 18, "P - pause");
  mvprintw(18, 18, "Q - quit");
}

void Pause() {
  attron(COLOR_PAIR(PAUSE));
  mvprintw(9, 10, "         ");
  mvprintw(10, 10, "  PAUSE  ");
  mvprintw(11, 10, "         ");
  attroff(COLOR_PAIR(PAUSE));
}

void PrintInfo(GameInfo *Game) {
  attron(COLOR_PAIR(255));
  mvprintw(2, 30, "Highscore: %d", Game->highscore);
  mvprintw(4, 30, "Score: %d", Game->score);
  mvprintw(6, 30, "Level: %d", Game->level);
  attroff(COLOR_PAIR(255));
}

void PrintGameOver(GameInfo *Game) {
  attron(COLOR_PAIR(255));
  mvprintw(8, 2, "+-+-+-+-+ +-+-+-+-+-+");
  mvprintw(9, 2, "|G|a|m|e| |o|v|e|r|!|");
  mvprintw(10, 2, "+-+-+-+-+ +-+-+-+-+-+");
  mvprintw(12, 2, "+-+-+-+-+ +-+-+-+-+-+ +-+-+-+-+-+");
  mvprintw(13, 2, "|Y|o|u|r| |s|c|o|r|e|    %d", Game->score);
  mvprintw(14, 2, "+-+-+-+-+ +-+-+-+-+-+ +-+-+-+-+-+");
  attroff(COLOR_PAIR(255));
}

void PrintFigure(GameInfo *Game) {
  int k = 0;
  attron(COLOR_PAIR(Game->figure.type));
  for (int i = 0; i < Game->figure.size; ++i) {
    for (int j = 0; j < Game->figure.size; ++j) {
      if (Game->figure.block[i][j] == Game->figure.type) {
        mvaddch(i + Game->figure.y - SHIFT_Y + 1,
                j + Game->figure.x * 2 + k - SHIFT_X, '[');
        mvaddch(i + Game->figure.y - SHIFT_Y + 1,
                j + Game->figure.x * 2 + k + 1 - SHIFT_X, ']');
      }
      ++k;
    }
    k = 0;
  }
  attroff(COLOR_PAIR(Game->figure.type));
}

void PrintNextFigure(GameInfo *Game) {
  int k = 0;
  int shift = (Game->next_figure.size - Game->next_figure.large) / 2;
  mvprintw(10, 30, "Next figure: ");
  attron(COLOR_PAIR(Game->next_figure.type));
  for (int i = 0; i <= Game->next_figure.large; i++) {
    for (int j = 0; j <= Game->next_figure.large; j++) {
      if (Game->next_figure.block[i + shift][j + shift] ==
          Game->next_figure.type) {
        mvaddch(i + NEXT_POX_Y, j + NEXT_POS_X + k, '[');
        mvaddch(i + NEXT_POX_Y, j + NEXT_POS_X + k + 1, ']');
      }
      k++;
    }
    k = 0;
  }
  attroff(COLOR_PAIR(Game->next_figure.type));
}

void PrintField(GameInfo *Game) {
  int k = 0;
  chtype left, right;

  for (int i = 0; i < WINDOW_HEIGHT; ++i)
    for (int j = 0; j < WINDOW_WIDTH; ++j) {
      if (Game->field.block[i + SHIFT_X][j + SHIFT_Y] == 0) {
        left = ' ';
        right = ' ';
      } else if (Game->field.block[i + SHIFT_X][j + SHIFT_Y] == LEFT_BORDER) {
        left = ' ';
        right = ACS_VLINE;
      } else if (Game->field.block[i + SHIFT_X][j + SHIFT_Y] == RIGHT_BORDER) {
        left = ACS_VLINE;
        right = ' ';
      } else if (Game->field.block[i + SHIFT_X][j + SHIFT_Y] == UPPER_BORDER ||
                 Game->field.block[i + SHIFT_X][j + SHIFT_Y] == DOWN_BORDER) {
        left = ACS_HLINE;
        right = ACS_HLINE;
      } else {
        left = '[';
        right = ']';
      }
      if (i == 0 && j == 0) {
        left = ' ';
        right = ACS_ULCORNER;
      }
      if (i == WINDOW_HEIGHT - 1 && j == 0) {
        left = ' ';
        right = ACS_LLCORNER;
      }
      if (i == 0 && j == WINDOW_WIDTH - 1) {
        left = ACS_URCORNER;
        right = ' ';
      }
      if (i == WINDOW_HEIGHT - 1 && j == WINDOW_WIDTH - 1) {
        left = ACS_LRCORNER;
        right = ' ';
      }
      if (Game->field.block[i + SHIFT_Y][j + SHIFT_X] != 0) {
        attron(COLOR_PAIR(Game->field.block[i + SHIFT_Y][j + SHIFT_X]));
        mvaddch(i + Game->y_pos + 1, j + Game->x_pos * 2 + SHIFT_X + k, left);
        mvaddch(i + Game->y_pos + 1, j + Game->x_pos * 2 + SHIFT_X + k + 1,
                right);
        attroff(COLOR_PAIR(Game->field.block[i + SHIFT_Y][j + SHIFT_X]));
      }
      ++k;
    }
    k = 0;
}