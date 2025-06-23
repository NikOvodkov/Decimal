#include <check.h>

#include "s21_string.h"

TCase *s21_add_suite(void);
TCase *s21_div_suite(void);
TCase *s21_floor_suite(void);
TCase *s21_from_decimal_to_float_suite(void);
TCase *s21_from_decimal_to_int_suite(void);
TCase *s21_from_float_to_decimal_suite(void);
TCase *s21_from_int_to_decimal_suite(void);
TCase *s21_is_equal_suite(void);
TCase *s21_is_greater_or_equal_suite(void);
TCase *s21_is_greater_suite(void);
TCase *s21_is_less_or_equal_suite(void);
TCase *s21_is_less_suite(void);
TCase *s21_is_not_equal_suite(void);
TCase *s21_mul_suite(void);
TCase *s21_negate_suite(void);
TCase *s21_round_suite(void);
TCase *s21_sub_suite(void);
TCase *s21_truncate_suite(void);

int main(void) {
  int number_failed;
  Suite *s = suite_create("s21_string");

  // Добавляем тестовые наборы

  suite_add_tcase(s, s21_add_suite());
  suite_add_tcase(s, s21_div_suite());
  suite_add_tcase(s, s21_floor_suite());
  suite_add_tcase(s, s21_from_decimal_to_float_suite());
  suite_add_tcase(s, s21_from_decimal_to_int_suite());
  suite_add_tcase(s, s21_from_float_to_decimal_suite());
  suite_add_tcase(s, s21_from_int_to_decimal_suite());
  suite_add_tcase(s, s21_is_equal_suite());
  suite_add_tcase(s, s21_is_greater_or_equal_suite());
  suite_add_tcase(s, s21_is_greater_suite());
  suite_add_tcase(s, s21_is_less_or_equal_suite());
  suite_add_tcase(s, s21_is_less_suite());
  suite_add_tcase(s, s21_is_not_equal_suite());
  suite_add_tcase(s, s21_mul_suite());
  suite_add_tcase(s, s21_negate_suite());
  suite_add_tcase(s, s21_round_suite());
  suite_add_tcase(s, s21_sub_suite());
  suite_add_tcase(s, s21_truncate_suite());


  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
