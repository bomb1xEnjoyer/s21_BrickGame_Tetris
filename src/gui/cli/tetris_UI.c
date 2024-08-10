#include "tetris_UI.h"

/**
 * @brief Display graphical user interface
 */
void ShowGUI(GameInfo *Game) {
  start_color();
  COLOR_INIT;
  PrintFigure(Game);
  PrintNextFigure(Game);
  PrintField(Game);
  PrintInfo(Game);
  if (Game->pause) Pause();
}

/**
 * @brief Display start screen
 */
void StartScreen() {
  mvprintw(3, 7, "+-+-+-+-+-+-+ +-+-+ +-+-+-+-+-+-+-+-+");
  mvprintw(4, 7, "|T|E|T|R|I|S| |b|y| |d|i|c|k|o|n|n|o|");
  mvprintw(5, 7, "+-+-+-+-+-+-+ +-+-+ +-+-+-+-+-+-+-+-+");
  mvprintw(8, 2, "+-+-+-+-+-+ +-+-+-+ +-+-+-+ +-+-+ +-+-+-+-+-+-+");
  mvprintw(9, 2, "|P|r|e|s|s| |a|n|y| |k|e|y| |t|o| |s|t|a|r|t|!|");
  mvprintw(10, 2, "+-+-+-+-+-+ +-+-+-+ +-+-+-+ +-+-+ +-+-+-+-+-+-+");
  mvprintw(13, 14, "Rotate figures with up arrow");
  mvprintw(14, 14, "Move figures with other arrows");
  mvprintw(15, 14, "Drop down figures with SPACE");
  mvprintw(16, 14, "Set pause with P");
  mvprintw(17, 14, "Close game with Q");
}

/**
 * @brief Display pause
 */
void Pause() {
  attron(COLOR_PAIR(PAUSE));
  mvprintw(9, 10, "         ");
  mvprintw(10, 10, "  PAUSE  ");
  mvprintw(11, 10, "         ");
  attroff(COLOR_PAIR(PAUSE));
}

/**
 * @brief Display info panel
 */
void PrintInfo(GameInfo *Game) {
  attron(COLOR_PAIR(255));
  mvprintw(2, 30, "Highscore: %d", Game->highscore);
  mvprintw(4, 30, "Score: %d", Game->score);
  mvprintw(6, 30, "Level: %d", Game->level);
  attroff(COLOR_PAIR(255));
}

/**
 * @brief Display game over screen
 */
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

/**
 * @brief Display figure on field
 */
void PrintFigure(GameInfo *Game) {
  int k = 0;
  attron(COLOR_PAIR(Game->figure.type));
  for (int i = 0; i < Game->figure.size; i++) {
    for (int j = 0; j < Game->figure.size; j++) {
      if (Game->figure.block[i][j] == Game->figure.type) {
        mvaddch(i + Game->figure.y - SHIFT_Y + 1,
                j + Game->figure.x * 2 + k - SHIFT_X, '[');
        mvaddch(i + Game->figure.y - SHIFT_Y + 1,
                j + Game->figure.x * 2 + k + 1 - SHIFT_X, ']');
      }
      k++;
    }
    k = 0;
  }
  attroff(COLOR_PAIR(Game->figure.type));
}

/**
 * @brief Display next figure in the info pannel
 */
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

/**
 * @brief Display field
 */
void PrintField(GameInfo *Game) {
  int k = 0;
  chtype left, right;

  for (int i = 0; i < WINDOW_HEIGHT; ++i) {
    for (int j = 0; j < WINDOW_WIDTH; ++j) {
      if (Game->field.block[i + SHIFT_Y][j + SHIFT_X] == 0) {
        left = ' ';
        right = ' ';
      } else if (Game->field.block[i + SHIFT_Y][j + SHIFT_X] == LEFT_BORDER) {
        left = ' ';
        right = ACS_VLINE;
      } else if (Game->field.block[i + SHIFT_Y][j + SHIFT_X] == RIGHT_BORDER) {
        left = ACS_VLINE;
        right = ' ';
      } else if (Game->field.block[i + SHIFT_Y][j + SHIFT_X] == UPPER_BORDER ||
                 Game->field.block[i + SHIFT_Y][j + SHIFT_X] == DOWN_BORDER) {
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
      k++;
    }
    k = 0;
  }
}