#include <check.h>
#include "../s21_decimal.h"

// 1. Тесты s21_get_bit
START_TEST(test_s21_get_bit_0) {
    s21_decimal value = {{1, 0, 0, 0}};
    ck_assert_int_eq(1, s21_get_bit(value, 0));
}
END_TEST

START_TEST(test_s21_get_bit_1) {
    s21_decimal value = {{1, 0, 0, 0}};
    ck_assert_int_eq(0, s21_get_bit(value, 1));
}
END_TEST

START_TEST(test_s21_get_bit_31) {
    s21_decimal value = {{1, 0, 0, 0}};
    ck_assert_int_eq(0, s21_get_bit(value, 31));
}
END_TEST

START_TEST(test_s21_get_bit_first_bit) {
    s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
    ck_assert_int_eq(1, s21_get_bit(value, 0));
}
END_TEST

START_TEST(test_s21_get_bit_last_bit_first_word) {
    s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
    ck_assert_int_eq(1, s21_get_bit(value, 31));
}
END_TEST

START_TEST(test_s21_get_bit_first_bit_second_word) {
    s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
    ck_assert_int_eq(1, s21_get_bit(value, 32));
}
END_TEST

START_TEST(test_s21_get_bit_last_bit_overall) {
    s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
    ck_assert_int_eq(1, s21_get_bit(value, 127));
}
END_TEST

START_TEST(test_s21_get_bit_out_of_bounds_negative) {
    s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
    ck_assert_int_eq(0, s21_get_bit(value, -1));
}
END_TEST

START_TEST(test_s21_get_bit_out_of_bounds_too_large) {
    s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
    ck_assert_int_eq(0, s21_get_bit(value, 128));
}
END_TEST

// 2. Тесты s21_set_bit
START_TEST(test_s21_set_bit_0_to_1) {
    s21_decimal value = {{0}};
    s21_set_bit(&value, 0, 1);
    ck_assert_int_eq(1, s21_get_bit(value, 0));
}
END_TEST

START_TEST(test_s21_set_bit_31_to_1) {
    s21_decimal value = {{0}};
    s21_set_bit(&value, 31, 1);
    ck_assert_int_eq(1, s21_get_bit(value, 31));
}
END_TEST

START_TEST(test_s21_set_bit_0_to_0) {
    s21_decimal value = {{0}};
    s21_set_bit(&value, 0, 1);
    s21_set_bit(&value, 0, 0);
    ck_assert_int_eq(0, s21_get_bit(value, 0));
}
END_TEST

START_TEST(test_s21_set_bit_out_of_bounds_negative) {
    s21_decimal value = {{0}};
    s21_set_bit(&value, -1, 1);
    // Должно отработать без падения
    ck_assert_int_eq(1, 1); // Просто проверяем что не упало
}
END_TEST

START_TEST(test_s21_set_bit_out_of_bounds_too_large) {
    s21_decimal value = {{0}};
    s21_set_bit(&value, 128, 1);
    // Должно отработать без падения
    ck_assert_int_eq(1, 1); // Просто проверяем что не упало
}
END_TEST

// 3. Тесты циклов (нужно разделить)
START_TEST(test_s21_set_bit_all_bits_0) {
    s21_decimal value = {{0}};
    s21_set_bit(&value, 0, 1);
    ck_assert_int_eq(1, s21_get_bit(value, 0));
}
END_TEST

START_TEST(test_s21_set_bit_all_bits_15) {
    s21_decimal value = {{0}};
    s21_set_bit(&value, 15, 1);
    ck_assert_int_eq(1, s21_get_bit(value, 15));
}
END_TEST

START_TEST(test_s21_set_bit_all_bits_31) {
    s21_decimal value = {{0}};
    s21_set_bit(&value, 31, 1);
    ck_assert_int_eq(1, s21_get_bit(value, 31));
}
END_TEST

START_TEST(test_s21_clear_bit_all_bits_0) {
    s21_decimal value = {{0xFFFFFFFF, 0, 0, 0}};
    s21_set_bit(&value, 0, 0);
    ck_assert_int_eq(0, s21_get_bit(value, 0));
}
END_TEST

START_TEST(test_s21_clear_bit_all_bits_15) {
    s21_decimal value = {{0xFFFFFFFF, 0, 0, 0}};
    s21_set_bit(&value, 15, 0);
    ck_assert_int_eq(0, s21_get_bit(value, 15));
}
END_TEST

START_TEST(test_s21_clear_bit_all_bits_31) {
    s21_decimal value = {{0xFFFFFFFF, 0, 0, 0}};
    s21_set_bit(&value, 31, 0);
    ck_assert_int_eq(0, s21_get_bit(value, 31));
}
END_TEST

Suite* s21_bit_suite(void) {
    Suite* s = suite_create("s21_bit");
    TCase* tc = tcase_create("core");
    
    // s21_get_bit tests
    tcase_add_test(tc, test_s21_get_bit_0);
    tcase_add_test(tc, test_s21_get_bit_1);
    tcase_add_test(tc, test_s21_get_bit_31);
    tcase_add_test(tc, test_s21_get_bit_first_bit);
    tcase_add_test(tc, test_s21_get_bit_last_bit_first_word);
    tcase_add_test(tc, test_s21_get_bit_first_bit_second_word);
    tcase_add_test(tc, test_s21_get_bit_last_bit_overall);
    tcase_add_test(tc, test_s21_get_bit_out_of_bounds_negative);
    tcase_add_test(tc, test_s21_get_bit_out_of_bounds_too_large);
    
    // s21_set_bit tests
    tcase_add_test(tc, test_s21_set_bit_0_to_1);
    tcase_add_test(tc, test_s21_set_bit_31_to_1);
    tcase_add_test(tc, test_s21_set_bit_0_to_0);
    tcase_add_test(tc, test_s21_set_bit_out_of_bounds_negative);
    tcase_add_test(tc, test_s21_set_bit_out_of_bounds_too_large);
    
    // Тесты циклов (выборочные проверки вместо полных циклов)
    tcase_add_test(tc, test_s21_set_bit_all_bits_0);
    tcase_add_test(tc, test_s21_set_bit_all_bits_15);
    tcase_add_test(tc, test_s21_set_bit_all_bits_31);
    tcase_add_test(tc, test_s21_clear_bit_all_bits_0);
    tcase_add_test(tc, test_s21_clear_bit_all_bits_15);
    tcase_add_test(tc, test_s21_clear_bit_all_bits_31);
    
    suite_add_tcase(s, tc);
    return s;
}