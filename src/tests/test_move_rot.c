#include "test_main.h"

START_TEST(move_rot_1) {
  GameInfo Game;
  CreateFigure(&Game.figure, 1);
  CreateField(&Game.field);
  Game.figure.x = START_POS_X + 8 - Game.figure.large;
  Game.figure.y = START_POS_Y;
  MoveFigure(&Game, UP);
  MoveFigure(&Game, 0);
  FreeFigure(&Game.figure);
  FreeField(&Game.field);
}
END_TEST

START_TEST(move_rot_2) {
  GameInfo Game;
  CreateFigure(&Game.figure, 1);
  CreateField(&Game.field);
  Game.figure.x = START_POS_X + 8 - Game.figure.large;
  Game.figure.y = START_POS_Y;
  MoveFigure(&Game, DOWN);
  FreeFigure(&Game.figure);
  FreeField(&Game.field);
}
END_TEST

START_TEST(move_rot_3) {
  GameInfo Game;
  CreateFigure(&Game.figure, 1);
  CreateField(&Game.field);
  Game.figure.x = START_POS_X + 8 - Game.figure.large;
  Game.figure.y = START_POS_Y;
  for (int i = 0; i < 6; i++) MoveFigure(&Game, LEFT);
  MoveFigure(&Game, UP);
  FreeFigure(&Game.figure);
  FreeField(&Game.field);
}
END_TEST

START_TEST(move_rot_4) {
  GameInfo Game;
  CreateFigure(&Game.figure, 1);
  CreateField(&Game.field);
  Game.figure.x = START_POS_X + 8 - Game.figure.large;
  Game.figure.y = START_POS_Y;
  for (int i = 0; i < 6; i++) MoveFigure(&Game, RIGHT);
  MoveFigure(&Game, UP);
  FreeFigure(&Game.figure);
  FreeField(&Game.field);
}
END_TEST

START_TEST(move_rot_5) {
  GameInfo Game;
  CreateFigure(&Game.figure, 1);
  CreateFigure(&Game.next_figure, 2);
  CreateField(&Game.field);
  Rotate(&Game);
  Game.figure.x = START_POS_X + 8 - Game.figure.large;
  Game.figure.y = START_POS_Y;
  MoveFigure(&Game, SPACE);
  FreeFigure(&Game.figure);
  FreeFigure(&Game.next_figure);
  FreeField(&Game.field);
}
END_TEST

START_TEST(move_rot_6) {
  GameInfo Game;
  CreateFigure(&Game.figure, 1);
  CreateField(&Game.field);
  Game.figure.x = START_POS_X + 8 - Game.figure.large;
  Game.figure.y = START_POS_Y;
  MoveFigure(&Game, PAUSE_KEY);
  Pause();
  MoveFigure(&Game, PAUSE_KEY);
  MoveFigure(&Game, EXIT);
  FreeFigure(&Game.figure);
  FreeField(&Game.field);
}
END_TEST

START_TEST(move_rot_7) {
  GameInfo Game;
  CreateFigure(&Game.figure, 1);
  CreateField(&Game.field);
  Game.figure.x = START_POS_X + 8 - Game.figure.large;
  Game.figure.y = START_POS_Y;
  MoveDowmCycle(&Game);
  MoveDowmCycle(&Game);
  MoveDowmCycle(&Game);
  FreeFigure(&Game.figure);
  FreeField(&Game.field);
}
END_TEST

START_TEST(move_rot_8) {
  GameInfo Game;
  CreateFigure(&Game.figure, 1);
  CreateField(&Game.field);
  Game.figure.x = START_POS_X + 8 - Game.figure.large;
  Game.figure.y = START_POS_Y + 10;
  AttachingFigure(&Game);
  FreeFigure(&Game.figure);
  FreeField(&Game.field);
}
END_TEST

START_TEST(move_rot_9) {
  GameInfo Game;
  CreateFigure(&Game.figure, 1);
  CreateField(&Game.field);
  Game.figure.x = START_POS_X + 8 - Game.figure.large;
  Game.figure.y = START_POS_Y;
  AttachingFigure(&Game);
  FreeFigure(&Game.figure);
  FreeField(&Game.field);
}
END_TEST

START_TEST(move_rot_10) {
  GameInfo Game;
  CreateField(&Game.field);
  ClearLine(&Game, 10);
  FreeField(&Game.field);
}
END_TEST

Suite* test_move_rot(void) {
  Suite* s = suite_create("move_rot");
  TCase* tc = tcase_create("move_rot_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, move_rot_1);
  tcase_add_test(tc, move_rot_2);
  tcase_add_test(tc, move_rot_3);
  tcase_add_test(tc, move_rot_4);
  tcase_add_test(tc, move_rot_5);
  tcase_add_test(tc, move_rot_6);
  tcase_add_test(tc, move_rot_7);
  tcase_add_test(tc, move_rot_8);
  tcase_add_test(tc, move_rot_9);
  tcase_add_test(tc, move_rot_10);
  // tcase_add_test(tc, move_rot_11);
  return s;
}
