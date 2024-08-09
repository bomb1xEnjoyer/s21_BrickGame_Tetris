#ifndef TETRIS_H
#define TETRIS_H

#include <math.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../../gui/cli/tetris_UI.h"
#include "defines.h"
#include "fsm.h"
#include "objects.h"

/*------ Frontend ------*/
void ShowGUI(GameInfo *Game);
void StartScreen();
void Pause();
void PrintInfo(GameInfo *Game);
void PrintGameOver(GameInfo *Game);
void PrintFigure(GameInfo *Game);
void PrintNextFigure(GameInfo *Game);
void PrintField(GameInfo *Game);

/*------ Backend ------*/
void GameLoop(GameInfo *Game);
void GameOver(GameInfo *Game);
void StateMachine(GameInfo *Game);
/*--- Control ---*/
void MoveFigure(GameInfo *Game, Keys key);
void RotateFigure(GameInfo *Game);
void DropDown(GameInfo *Game);
void Rotate(GameInfo *Game);
int MoveDown(GameInfo *Game);
void MoveLeft(GameInfo *Game);
void MoveRight(GameInfo *Game);
Collision IsColliding(GameInfo *Game);
void AttachingFigure(GameInfo *Game);
void LevelCounter(GameInfo *Game, int filled_lines);
void MoveDowmCycle(GameInfo *Game);
/*--- Field ---*/
void CreateField(Field *field);
void FreeField(Field *field);
int CheckFullLines(GameInfo *Game);
void ClearLine(GameInfo *Game, int line_number);
/*--- Figure ---*/
void CreateFigure(Figure *figure, BlockType type);
void TakeCollide(Figure *figure);
void FreeFigure(Figure *figure);

#endif /* TETRIS_H */