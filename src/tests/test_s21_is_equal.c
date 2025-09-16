#include <check.h>

#include "../s21_decimal.h"

START_TEST(test_s21_is_equal_basic) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};

  val1.bits[0] = 1;
  val2.bits[0] = 1;
  ck_assert_int_eq(1, s21_is_equal(val1, val2));  // 1 == 1

  val1.bits[3] = 0x80000000;
  val2.bits[3] = 0x80000000;
  ck_assert_int_eq(1, s21_is_equal(val1,
                                   val2));  // -1 == -1

  val1.bits[0] = 1;
  val2.bits[0] = 2;
  ck_assert_int_eq(0, s21_is_equal(val1, val2));  // -1 != -2

  val1.bits[3] = 0x00000000;
  val2.bits[3] = 0x00000000;
  ck_assert_int_eq(0, s21_is_equal(val1, val2));  // 1 != 2

  val1.bits[0] = 1;
  val1.bits[3] = 0x00000000;
  val2.bits[0] = 1;
  val2.bits[3] = 0x80000000;
  ck_assert_int_eq(0, s21_is_equal(val1,
                                   val2));  // 1 != -1
}
END_TEST

START_TEST(test_s21_is_equal_basic_high_values) {
  s21_decimal max = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal min = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  ck_assert_int_eq(1, s21_is_equal(max, max));  // max == max
  ck_assert_int_eq(1, s21_is_equal(min, min));  // min == min
  ck_assert_int_eq(0, s21_is_equal(min, max));  // min != max
}

START_TEST(test_s21_is_equal_zeros) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};

  ck_assert_int_eq(1, s21_is_equal(val1, val2));  // +0 == +0

  val1.bits[3] = 0x80000000;
  val2.bits[3] = 0x80000000;
  ck_assert_int_eq(1, s21_is_equal(val1, val2));  // -0 == -0

  val1.bits[3] = 0x80000000;
  val2.bits[3] = 0x00000000;
  ck_assert_int_eq(1, s21_is_equal(val1, val2));  // -0 == +0

  val1.bits[3] = 0x00010000;
  val2.bits[3] = 0x00040000;
  ck_assert_int_eq(1, s21_is_equal(val1,
                                   val2));  // +0.0 == +0.00

  val1.bits[3] = 0x80010000;
  val2.bits[3] = 0x00040000;
  ck_assert_int_eq(1, s21_is_equal(val1,
                                   val2));  // -0.0 == +0.00
}

START_TEST(test_s21_is_equal_scale) {
  s21_decimal val1 = {{0, 0, 0, 0x00010000}};  // scale = 1, +
  s21_decimal val2 = {{0, 0, 0, 0x00020000}};  // scale = 2, +

  val1.bits[0] = 10;                              // 1.0
  val2.bits[0] = 100;                             // 1.00
  ck_assert_int_eq(1, s21_is_equal(val1, val2));  // 1.0 == 1.00

  val1.bits[0] = 10;                              // 1.0
  val2.bits[0] = 200;                             // 2.00
  ck_assert_int_eq(0, s21_is_equal(val1, val2));  // 1.0 != 2.00

  val1.bits[3] = 0x80010000;                      // scale = 1, -
  val2.bits[3] = 0x80020000;                      // scale = 2, -
  val1.bits[0] = 10;                              // -1.0
  val2.bits[0] = 100;                             // -1.00
  ck_assert_int_eq(1, s21_is_equal(val1, val2));  // -1.0 == -1.00

  val1.bits[0] = 10;                              // -1.0
  val2.bits[0] = 200;                             // -2.00
  ck_assert_int_eq(0, s21_is_equal(val1, val2));  // -1.0 != -2.00

  val1.bits[3] = 0x00010000;                      // scale = 1, +
  val2.bits[3] = 0x80020000;                      // scale = 2, -
  val1.bits[0] = 10;                              // 1.0
  val2.bits[0] = 100;                             // -1.00
  ck_assert_int_eq(0, s21_is_equal(val1, val2));  // 1.0 != -1.00

  val1.bits[0] = 1;
  val1.bits[3] = 0x001B0000;  // scale = 28, знак "+"
  val2.bits[0] = 10;
  val2.bits[3] = 0x001C0000;                      // scale = 27, +
  ck_assert_int_eq(1, s21_is_equal(val1, val2));  // 1e-28 == 10e-27

  val2.bits[0] = 20;
  val2.bits[3] = 0x001B0000;                      // scale = 27, +
  ck_assert_int_eq(0, s21_is_equal(val1, val2));  // 1e-28 != 2e-27

  val1.bits[0] = 1;
  val1.bits[3] = 0x801C0000;  // scale = 28, -
  val2.bits[0] = 10;
  val2.bits[3] = 0x801B0000;                      // scale = 27, -
  ck_assert_int_eq(1, s21_is_equal(val1, val2));  // -1e-28 == -10e-27

  val2.bits[0] = 20;
  val2.bits[3] = 0x801B0000;                      // scale = 27, -
  ck_assert_int_eq(0, s21_is_equal(val1, val2));  // -1e-28 != -2e-27
}

Suite* s21_is_equal_suite(void) {
  Suite* s = suite_create("s21_is_equal");
  TCase* tc = tcase_create("core");
  tcase_add_test(tc, test_s21_is_equal_basic);
  tcase_add_test(tc, test_s21_is_equal_basic_high_values);
  tcase_add_test(tc, test_s21_is_equal_zeros);
  tcase_add_test(tc, test_s21_is_equal_scale);
  suite_add_tcase(s, tc);
  return s;
}