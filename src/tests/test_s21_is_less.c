#include <check.h>

#include "../s21_decimal.h"

START_TEST(test_s21_is_less_basic) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};

  val1.bits[0] = 1;
  val2.bits[0] = 2;
  ck_assert_int_eq(1, s21_is_less(val1, val2));  // 1 < 2

  val1.bits[0] = 2;
  val2.bits[0] = 1;
  ck_assert_int_eq(0, s21_is_less(val1, val2));  // 2 < 1

  val1.bits[0] = 1;
  val1.bits[3] = 0x80000000;
  val2.bits[0] = 2;
  val2.bits[3] = 0x00000000;
  ck_assert_int_eq(1, s21_is_less(val1, val2));  // -1 < 2

  val1.bits[0] = 2;
  val1.bits[3] = 0x80000000;
  val2.bits[0] = 1;
  val2.bits[3] = 0x80000000;
  ck_assert_int_eq(1, s21_is_less(val1, val2));  // -2 < -1

  val1.bits[0] = 1;
  val1.bits[3] = 0x80000000;
  val2.bits[0] = 1;
  val2.bits[3] = 0x80000000;
  ck_assert_int_eq(0, s21_is_less(val1, val2));  // -1 < -1
}
END_TEST

START_TEST(test_s21_is_less_high_values) {
  s21_decimal max = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal min = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  ck_assert_int_eq(0, s21_is_less(max, max));  // max == max → false
  ck_assert_int_eq(0, s21_is_less(min, min));  // min == min → false
  ck_assert_int_eq(1, s21_is_less(min, max));  // min < max

  s21_decimal near_max = {
      {0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};  // max - 1
  s21_decimal near_min = {
      {0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};  // min - 1
  ck_assert_int_eq(1, s21_is_less(near_max, max));        // near_max < max
  ck_assert_int_eq(0, s21_is_less(max, near_max));        // max < near_max
  ck_assert_int_eq(0, s21_is_less(near_min, min));        // near_min < min
  ck_assert_int_eq(1, s21_is_less(min, near_min));        // min < near_min

  s21_decimal val1 = {{0, 0, 1, 0x00010000}};
  s21_decimal val2 = {{0, 1, 0, 0x00010000}};
  s21_decimal val3 = {{1, 0, 0, 0x00010000}};

  ck_assert_int_eq(0, s21_is_less(val1, max));
  ck_assert_int_eq(0, s21_is_less(val2, max));
  ck_assert_int_eq(0, s21_is_less(val3, max));
}
END_TEST

START_TEST(test_s21_is_less_zeros) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};

  ck_assert_int_eq(0, s21_is_less(val1, val2));  // 0 < 0

  val1.bits[3] = 0x80000000;                     // -0
  val2.bits[3] = 0x80000000;                     // -0
  ck_assert_int_eq(0, s21_is_less(val1, val2));  // -0 < -0

  val1.bits[3] = 0x80000000;                     // -0
  val2.bits[3] = 0x00000000;                     // 0
  ck_assert_int_eq(0, s21_is_less(val1, val2));  // -0 < 0
  ck_assert_int_eq(0, s21_is_less(val2, val1));  // 0 < -0

  val1.bits[3] = 0x00010000;                     // scale 1, +0
  val2.bits[3] = 0x00020000;                     // scale 2, +0
  ck_assert_int_eq(0, s21_is_less(val1, val2));  // +0 < +0
  ck_assert_int_eq(0, s21_is_less(val2, val1));  // +0 < +0

  val1.bits[3] = 0x80010000;                     // scale 1, -0
  val2.bits[3] = 0x80020000;                     // scale 2, -0
  ck_assert_int_eq(0, s21_is_less(val1, val2));  // -0 < -0
  ck_assert_int_eq(0, s21_is_less(val2, val1));  // -0 < -0
}
END_TEST

START_TEST(test_s21_is_less_scale) {
  s21_decimal val1 = {{10, 0, 0, 0x00010000}};   // 1.0
  s21_decimal val2 = {{100, 0, 0, 0x00020000}};  // 1.00

  ck_assert_int_eq(0, s21_is_less(val1, val2));  // 1.0 == 1.00

  val2.bits[0] = 200;                            // 2.00
  ck_assert_int_eq(1, s21_is_less(val1, val2));  // 1.0 < 2.00

  val1.bits[0] = 10;
  val1.bits[3] = 0x80010000;  // -1.0
  val2.bits[0] = 100;
  val2.bits[3] = 0x80020000;                     // -1.00
  ck_assert_int_eq(0, s21_is_less(val1, val2));  // -1.0 == -1.00

  val2.bits[0] = 200;                            // -2.00
  ck_assert_int_eq(0, s21_is_less(val1, val2));  // -1.0 < -2.00

  val1.bits[0] = 200;  // -2.0
  val2.bits[0] = 100;  // -1.00
  val1.bits[3] = 0x80010000;
  val2.bits[3] = 0x80020000;
  ck_assert_int_eq(1, s21_is_less(val1, val2));  // -2.0 < -1.00

  val1.bits[0] = 1;
  val1.bits[3] = 0x001B0000;
  val2.bits[0] = 10;
  val2.bits[3] = 0x001c0000;
  ck_assert_int_eq(0, s21_is_less(val1, val2));  // 1e-27 == 10e-28

  val2.bits[0] = 20;                             // 2e-27
  ck_assert_int_eq(1, s21_is_less(val1, val2));  // 1e-28 < 2e-27

  val1.bits[3] = 0x801C0000;  // -1e-28
  val2.bits[3] = 0x801B0000;  // -10e-27
  val2.bits[0] = 10;
  ck_assert_int_eq(0, s21_is_less(val1, val2));  // -1e-28 == -10e-27

  val2.bits[0] = 20;                             // -2e-27
  ck_assert_int_eq(1, s21_is_less(val1, val2));  // -2e-27 < -1e-28
}
END_TEST

Suite* s21_is_less_suite(void) {
  Suite* s = suite_create("s21_is_less");
  TCase* tc = tcase_create("core");
  tcase_add_test(tc, test_s21_is_less_basic);
  tcase_add_test(tc, test_s21_is_less_high_values);
  tcase_add_test(tc, test_s21_is_less_zeros);
  tcase_add_test(tc, test_s21_is_less_scale);
  suite_add_tcase(s, tc);
  return s;
}
