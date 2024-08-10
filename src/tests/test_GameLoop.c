#include "test_main.h"

START_TEST(GameLoop_1) {
  GameInfo Game;
  GameLoop(&Game);
}
END_TEST

Suite* test_GameLoop(void) {
  Suite* s = suite_create("GameLoop");
  TCase* tc = tcase_create("GameLoop_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, GameLoop_1);
  return s;
}
