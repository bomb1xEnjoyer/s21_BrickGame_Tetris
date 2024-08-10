#include "test_main.h"

START_TEST(createFigute_1) {
  printf("1");
  GameInfo Game;
  BlockType type = I;
  CreateFigure(&Game.figure, type);
  printf("1");
  FreeFigure(&Game.figure);
  printf("1\n");
}
END_TEST

START_TEST(createFigute_2) {
  printf("2");
  GameInfo Game;
  BlockType type = L;
  CreateFigure(&Game.figure, type);
  printf("2");
  FreeFigure(&Game.figure);
  printf("2\n");
}
END_TEST

START_TEST(createFigute_3) {
  printf("3");
  GameInfo Game;
  BlockType type = J;
  CreateFigure(&Game.figure, type);
  printf("3");
  FreeFigure(&Game.figure);
  printf("3\n");
}
END_TEST

START_TEST(createFigute_4) {
  printf("4");
  GameInfo Game;
  BlockType type = S;
  CreateFigure(&Game.figure, type);
  printf("4");
  FreeFigure(&Game.figure);
  printf("4\n");
}
END_TEST

START_TEST(createFigute_5) {
  printf("5");
  GameInfo Game;
  BlockType type = Z;
  CreateFigure(&Game.figure, type);
  printf("5");
  FreeFigure(&Game.figure);
  printf("5\n");
}
END_TEST

START_TEST(createFigute_6) {
  printf("6");
  GameInfo Game;
  BlockType type = T;
  CreateFigure(&Game.figure, type);
  printf("6");
  FreeFigure(&Game.figure);
  printf("6\n");
}
END_TEST

START_TEST(createFigute_7) {
  printf("7");
  GameInfo Game;
  BlockType type = O;
  CreateFigure(&Game.figure, type);
  printf("7");
  FreeFigure(&Game.figure);
  printf("7\n");
}
END_TEST

Suite* test_createFigure(void) {
  Suite* s = suite_create("createFigute");
  TCase* tc = tcase_create("createFigute_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, createFigute_1);
  tcase_add_test(tc, createFigute_2);
  tcase_add_test(tc, createFigute_3);
  tcase_add_test(tc, createFigute_4);
  tcase_add_test(tc, createFigute_5);
  tcase_add_test(tc, createFigute_6);
  tcase_add_test(tc, createFigute_7);
  return s;
}
