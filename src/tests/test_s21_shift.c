#include <check.h>
#include "../s21_decimal.h"

// 1. Тесты s21_shift_left
START_TEST(test_s21_shift_left_basic_success) {
    s21_decimal value = {{1, 0, 0, 0}};
    ck_assert_int_eq(0, s21_shift_left(&value, 1));
}
END_TEST

START_TEST(test_s21_shift_left_basic_result) {
    s21_decimal value = {{1, 0, 0, 0}};
    s21_shift_left(&value, 1);
    ck_assert_int_eq(2, value.bits[0]);
}
END_TEST

START_TEST(test_s21_shift_left_carry_success) {
    s21_decimal value = {{0x80000000, 0, 0, 0}};
    ck_assert_int_eq(0, s21_shift_left(&value, 1));
}
END_TEST

START_TEST(test_s21_shift_left_carry_bits0) {
    s21_decimal value = {{0x80000000, 0, 0, 0}};
    s21_shift_left(&value, 1);
    ck_assert_int_eq(0, value.bits[0]);
}
END_TEST

START_TEST(test_s21_shift_left_carry_bits1) {
    s21_decimal value = {{0x80000000, 0, 0, 0}};
    s21_shift_left(&value, 1);
    ck_assert_int_eq(1, value.bits[1]);
}
END_TEST

START_TEST(test_s21_shift_left_overflow_error) {
    s21_decimal value = {{0, 0x80000000, 0, 0}};
    ck_assert_int_eq(1, s21_shift_left(&value, 1));
}
END_TEST

START_TEST(test_s21_shift_left_max_shift_success) {
    s21_decimal value = {{1, 0, 0, 0}};
    ck_assert_int_eq(0, s21_shift_left(&value, 32));
}
END_TEST

START_TEST(test_s21_shift_left_max_shift_bits0) {
    s21_decimal value = {{1, 0, 0, 0}};
    s21_shift_left(&value, 32);
    ck_assert_int_eq(0, value.bits[0]);
}
END_TEST

START_TEST(test_s21_shift_left_max_shift_bits1) {
    s21_decimal value = {{1, 0, 0, 0}};
    s21_shift_left(&value, 32);
    ck_assert_int_eq(1, value.bits[1]);
}
END_TEST

START_TEST(test_s21_shift_left_invalid_shift_negative) {
    s21_decimal value = {{1, 0, 0, 0}};
    ck_assert_int_eq(1, s21_shift_left(&value, -1));
}
END_TEST

START_TEST(test_s21_shift_left_invalid_shift_zero) {
    s21_decimal value = {{1, 0, 0, 0}};
    ck_assert_int_eq(1, s21_shift_left(&value, 0));
}
END_TEST

START_TEST(test_s21_shift_left_invalid_shift_too_large) {
    s21_decimal value = {{1, 0, 0, 0}};
    ck_assert_int_eq(1, s21_shift_left(&value, 33));
}
END_TEST

// 2. Тесты s21_shift_right
START_TEST(test_s21_shift_right_basic_success) {
    s21_decimal value = {{2, 0, 0, 0}};
    ck_assert_int_eq(0, s21_shift_right(&value, 1));
}
END_TEST

START_TEST(test_s21_shift_right_basic_result) {
    s21_decimal value = {{2, 0, 0, 0}};
    s21_shift_right(&value, 1);
    ck_assert_int_eq(1, value.bits[0]);
}
END_TEST

START_TEST(test_s21_shift_right_carry_success) {
    s21_decimal value = {{0, 1, 0, 0}};
    ck_assert_int_eq(0, s21_shift_right(&value, 1));
}
END_TEST

START_TEST(test_s21_shift_right_carry_bits0) {
    s21_decimal value = {{0, 1, 0, 0}};
    s21_shift_right(&value, 1);
    ck_assert_int_eq(0x80000000, value.bits[0]);
}
END_TEST

START_TEST(test_s21_shift_right_carry_bits1) {
    s21_decimal value = {{0, 1, 0, 0}};
    s21_shift_right(&value, 1);
    ck_assert_int_eq(0, value.bits[1]);
}
END_TEST

START_TEST(test_s21_shift_right_underflow_error) {
    s21_decimal value = {{1, 0, 0, 0}};
    ck_assert_int_eq(1, s21_shift_right(&value, 1));
}
END_TEST

START_TEST(test_s21_shift_right_max_shift_success) {
    s21_decimal value = {{0, 1, 0, 0}};
    ck_assert_int_eq(0, s21_shift_right(&value, 32));
}
END_TEST

START_TEST(test_s21_shift_right_max_shift_bits0) {
    s21_decimal value = {{0, 1, 0, 0}};
    s21_shift_right(&value, 32);
    ck_assert_int_eq(1, value.bits[0]);
}
END_TEST

START_TEST(test_s21_shift_right_max_shift_bits1) {
    s21_decimal value = {{0, 1, 0, 0}};
    s21_shift_right(&value, 32);
    ck_assert_int_eq(0, value.bits[1]);
}
END_TEST

START_TEST(test_s21_shift_right_invalid_shift_negative) {
    s21_decimal value = {{1, 0, 0, 0}};
    ck_assert_int_eq(1, s21_shift_right(&value, -1));
}
END_TEST

START_TEST(test_s21_shift_right_invalid_shift_zero) {
    s21_decimal value = {{1, 0, 0, 0}};
    ck_assert_int_eq(1, s21_shift_right(&value, 0));
}
END_TEST

START_TEST(test_s21_shift_right_invalid_shift_too_large) {
    s21_decimal value = {{1, 0, 0, 0}};
    ck_assert_int_eq(1, s21_shift_right(&value, 33));
}
END_TEST

// 3. Комплексные тесты (требуют подготовки данных)
START_TEST(test_s21_shift_left_then_right_identity_success) {
    s21_decimal original = {{0x12345678, 0x9ABCDEF0, 0, 0}};
    s21_decimal value = original;
    ck_assert_int_eq(0, s21_shift_left(&value, 7));
    ck_assert_int_eq(0, s21_shift_right(&value, 7));
}
END_TEST

START_TEST(test_s21_shift_left_then_right_bits0) {
    s21_decimal original = {{0x12345678, 0x9ABCDEF0, 0, 0}};
    s21_decimal value = original;
    s21_shift_left(&value, 7);
    s21_shift_right(&value, 7);
    ck_assert_int_eq(original.bits[0], value.bits[0]);
}
END_TEST

START_TEST(test_s21_shift_left_then_right_bits1) {
    s21_decimal original = {{0x12345678, 0x9ABCDEF0, 0, 0}};
    s21_decimal value = original;
    s21_shift_left(&value, 7);
    s21_shift_right(&value, 7);
    ck_assert_int_eq(original.bits[1], value.bits[1]);
}
END_TEST

START_TEST(test_s21_shift_left_then_right_bits2) {
    s21_decimal original = {{0x12345678, 0x9ABCDEF0, 0, 0}};
    s21_decimal value = original;
    s21_shift_left(&value, 7);
    s21_shift_right(&value, 7);
    ck_assert_int_eq(original.bits[2], value.bits[2]);
}
END_TEST

START_TEST(test_s21_shift_preserves_scale) {
    s21_decimal value = {{1, 0, 0, 0x80010000}};
    int original_scale = s21_get_scale(value);
    s21_shift_left(&value, 3);
    ck_assert_int_eq(original_scale, s21_get_scale(value));
}
END_TEST

START_TEST(test_s21_shift_preserves_sign) {
    s21_decimal value = {{1, 0, 0, 0x80010000}};
    int original_sign = s21_get_sign(value);
    s21_shift_left(&value, 3);
    ck_assert_int_eq(original_sign, s21_get_sign(value));
}
END_TEST

Suite* s21_shift_suite(void) {
    Suite* s = suite_create("s21_shift");
    TCase* tc = tcase_create("core");
    
    // s21_shift_left tests
    tcase_add_test(tc, test_s21_shift_left_basic_success);
    tcase_add_test(tc, test_s21_shift_left_basic_result);
    tcase_add_test(tc, test_s21_shift_left_carry_success);
    tcase_add_test(tc, test_s21_shift_left_carry_bits0);
    tcase_add_test(tc, test_s21_shift_left_carry_bits1);
    tcase_add_test(tc, test_s21_shift_left_overflow_error);
    tcase_add_test(tc, test_s21_shift_left_max_shift_success);
    tcase_add_test(tc, test_s21_shift_left_max_shift_bits0);
    tcase_add_test(tc, test_s21_shift_left_max_shift_bits1);
    tcase_add_test(tc, test_s21_shift_left_invalid_shift_negative);
    tcase_add_test(tc, test_s21_shift_left_invalid_shift_zero);
    tcase_add_test(tc, test_s21_shift_left_invalid_shift_too_large);
    
    // s21_shift_right tests
    tcase_add_test(tc, test_s21_shift_right_basic_success);
    tcase_add_test(tc, test_s21_shift_right_basic_result);
    tcase_add_test(tc, test_s21_shift_right_carry_success);
    tcase_add_test(tc, test_s21_shift_right_carry_bits0);
    tcase_add_test(tc, test_s21_shift_right_carry_bits1);
    tcase_add_test(tc, test_s21_shift_right_underflow_error);
    tcase_add_test(tc, test_s21_shift_right_max_shift_success);
    tcase_add_test(tc, test_s21_shift_right_max_shift_bits0);
    tcase_add_test(tc, test_s21_shift_right_max_shift_bits1);
    tcase_add_test(tc, test_s21_shift_right_invalid_shift_negative);
    tcase_add_test(tc, test_s21_shift_right_invalid_shift_zero);
    tcase_add_test(tc, test_s21_shift_right_invalid_shift_too_large);
    
    // Комплексные тесты
    tcase_add_test(tc, test_s21_shift_left_then_right_identity_success);
    tcase_add_test(tc, test_s21_shift_left_then_right_bits0);
    tcase_add_test(tc, test_s21_shift_left_then_right_bits1);
    tcase_add_test(tc, test_s21_shift_left_then_right_bits2);
    tcase_add_test(tc, test_s21_shift_preserves_scale);
    tcase_add_test(tc, test_s21_shift_preserves_sign);
    
    suite_add_tcase(s, tc);
    return s;
}