#include <check.h>
#include "../s21_decimal.h"

// 1. Базовые тесты Scale Up
START_TEST(test_s21_scale_up_initial_scale_zero) {
    s21_decimal value = {{1, 0, 0, 0}};
    ck_assert_int_eq(0, s21_get_scale(value));
}
END_TEST

START_TEST(test_s21_scale_up_returns_success) {
    s21_decimal value = {{1, 0, 0, 0}};
    ck_assert_int_eq(0, s21_scale_up(&value, 1));
}
END_TEST

START_TEST(test_s21_scale_up_sets_correct_scale) {
    s21_decimal value = {{1, 0, 0, 0}};
    s21_scale_up(&value, 1);
    ck_assert_int_eq(1, s21_get_scale(value));
}
END_TEST

START_TEST(test_s21_scale_up_multiplies_value_correctly) {
    s21_decimal value = {{1, 0, 0, 0}};
    s21_scale_up(&value, 1);
    ck_assert_int_eq(10, value.bits[0]);
}
END_TEST

// 2. Базовые тесты Scale Down
START_TEST(test_s21_scale_down_initial_scale_one) {
    s21_decimal value = {{10, 0, 0, 0}};
    s21_set_scale(&value, 1);
    ck_assert_int_eq(1, s21_get_scale(value));
}
END_TEST

START_TEST(test_s21_scale_down_returns_success) {
    s21_decimal value = {{10, 0, 0, 0}};
    s21_set_scale(&value, 1);
    ck_assert_int_eq(0, s21_scale_down(&value, 1));
}
END_TEST

START_TEST(test_s21_scale_down_sets_zero_scale) {
    s21_decimal value = {{10, 0, 0, 0}};
    s21_set_scale(&value, 1);
    s21_scale_down(&value, 1);
    ck_assert_int_eq(0, s21_get_scale(value));
}
END_TEST

START_TEST(test_s21_scale_down_divides_value_correctly) {
    s21_decimal value = {{10, 0, 0, 0}};
    s21_set_scale(&value, 1);
    s21_scale_down(&value, 1);
    ck_assert_int_eq(1, value.bits[0]);
}
END_TEST

// 3. Тесты граничных случаев Scale Up
START_TEST(test_s21_scale_up_negative_power_error) {
    s21_decimal value = {{1, 0, 0, 0}};
    ck_assert_int_eq(1, s21_scale_up(&value, -1));
}
END_TEST

START_TEST(test_s21_scale_up_too_large_power_error) {
    s21_decimal value = {{1, 0, 0, 0}};
    ck_assert_int_eq(1, s21_scale_up(&value, 29));
}
END_TEST

START_TEST(test_s21_scale_up_scale_overflow_error) {
    s21_decimal value = {{1, 0, 0, 0}};
    s21_set_scale(&value, 28);
    ck_assert_int_eq(1, s21_scale_up(&value, 1));
}
END_TEST

// 4. Тесты граничных случаев Scale Down
START_TEST(test_s21_scale_down_negative_power_error) {
    s21_decimal value = {{1, 0, 0, 0}};
    ck_assert_int_eq(1, s21_scale_down(&value, -1));
}
END_TEST

START_TEST(test_s21_scale_down_scale_underflow_error) {
    s21_decimal value = {{1, 0, 0, 0}};
    ck_assert_int_eq(1, s21_scale_down(&value, 1));
}
END_TEST

// 5. Тесты семантических ошибок
START_TEST(test_s21_scale_up_value_overflow_error) {
    s21_decimal value = {{0x19999999, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
    s21_set_scale(&value, 0);
    ck_assert_int_eq(1, s21_scale_up(&value, 1));
}
END_TEST

START_TEST(test_s21_scale_down_precision_loss_error) {
    s21_decimal value = {{15, 0, 0, 0}};
    s21_set_scale(&value, 1);
    ck_assert_int_eq(1, s21_scale_down(&value, 1));
}
END_TEST

// 6. Тесты безопасности данных
START_TEST(test_s21_scale_after_error_value_unchanged) {
    s21_decimal original = {{123, 0, 0, 0}};
    s21_decimal value = original;
    s21_set_scale(&value, 1);
    s21_scale_down(&value, 2);
    ck_assert_int_eq(original.bits[0], value.bits[0]);
}
END_TEST

START_TEST(test_s21_scale_after_error_bits1_unchanged) {
    s21_decimal original = {{123, 0, 0, 0}};
    s21_decimal value = original;
    s21_set_scale(&value, 1);
    s21_scale_down(&value, 2);
    ck_assert_int_eq(original.bits[1], value.bits[1]);
}
END_TEST

START_TEST(test_s21_scale_after_error_bits2_unchanged) {
    s21_decimal original = {{123, 0, 0, 0}};
    s21_decimal value = original;
    s21_set_scale(&value, 1);
    s21_scale_down(&value, 2);
    ck_assert_int_eq(original.bits[2], value.bits[2]);
}
END_TEST

START_TEST(test_s21_scale_after_error_scale_unchanged) {
    s21_decimal original = {{123, 0, 0, 0}};
    s21_decimal value = original;
    s21_set_scale(&value, 1);
    s21_scale_down(&value, 2);
    ck_assert_int_eq(1, s21_get_scale(value));
}
END_TEST

// 7. Дополнительные тесты
START_TEST(test_s21_scale_down_zero_success) {
    s21_decimal value = {{0, 0, 0, 0}};
    s21_set_scale(&value, 2);
    ck_assert_int_eq(0, s21_scale_down(&value, 1));
}
END_TEST

START_TEST(test_s21_scale_down_zero_final_scale) {
    s21_decimal value = {{0, 0, 0, 0}};
    s21_set_scale(&value, 2);
    s21_scale_down(&value, 1);
    ck_assert_int_eq(1, s21_get_scale(value));
}
END_TEST

START_TEST(test_s21_scale_down_zero_value_unchanged) {
    s21_decimal value = {{0, 0, 0, 0}};
    s21_set_scale(&value, 2);
    s21_scale_down(&value, 1);
    ck_assert_int_eq(0, value.bits[0]);
}
END_TEST

START_TEST(test_s21_scale_multiple_up_success) {
    s21_decimal value = {{1, 0, 0, 0}};
    ck_assert_int_eq(0, s21_scale_up(&value, 2));
}
END_TEST

START_TEST(test_s21_scale_multiple_up_final_scale) {
    s21_decimal value = {{1, 0, 0, 0}};
    s21_scale_up(&value, 2);
    ck_assert_int_eq(2, s21_get_scale(value));
}
END_TEST

START_TEST(test_s21_scale_multiple_up_final_value) {
    s21_decimal value = {{1, 0, 0, 0}};
    s21_scale_up(&value, 2);
    ck_assert_int_eq(100, value.bits[0]);
}
END_TEST

START_TEST(test_s21_scale_multiple_down_success) {
    s21_decimal value = {{100, 0, 0, 0}};
    s21_set_scale(&value, 2);
    ck_assert_int_eq(0, s21_scale_down(&value, 1));
}
END_TEST

START_TEST(test_s21_scale_multiple_down_final_scale) {
    s21_decimal value = {{100, 0, 0, 0}};
    s21_set_scale(&value, 2);
    s21_scale_down(&value, 1);
    ck_assert_int_eq(1, s21_get_scale(value));
}
END_TEST

START_TEST(test_s21_scale_multiple_down_final_value) {
    s21_decimal value = {{100, 0, 0, 0}};
    s21_set_scale(&value, 2);
    s21_scale_down(&value, 1);
    ck_assert_int_eq(10, value.bits[0]);
}
END_TEST

Suite* s21_scale_suite(void) {
    Suite* s = suite_create("s21_scale");
    TCase* tc = tcase_create("core");
    
    // Scale Up базовые
    tcase_add_test(tc, test_s21_scale_up_initial_scale_zero);
    tcase_add_test(tc, test_s21_scale_up_returns_success);
    tcase_add_test(tc, test_s21_scale_up_sets_correct_scale);
    tcase_add_test(tc, test_s21_scale_up_multiplies_value_correctly);
    
    // Scale Down базовые
    tcase_add_test(tc, test_s21_scale_down_initial_scale_one);
    tcase_add_test(tc, test_s21_scale_down_returns_success);
    tcase_add_test(tc, test_s21_scale_down_sets_zero_scale);
    tcase_add_test(tc, test_s21_scale_down_divides_value_correctly);
    
    // Граничные случаи
    tcase_add_test(tc, test_s21_scale_up_negative_power_error);
    tcase_add_test(tc, test_s21_scale_up_too_large_power_error);
    tcase_add_test(tc, test_s21_scale_up_scale_overflow_error);
    tcase_add_test(tc, test_s21_scale_down_negative_power_error);
    tcase_add_test(tc, test_s21_scale_down_scale_underflow_error);
    
    // Семантические ошибки
    tcase_add_test(tc, test_s21_scale_up_value_overflow_error);
    tcase_add_test(tc, test_s21_scale_down_precision_loss_error);
    
    // Безопасность данных
    tcase_add_test(tc, test_s21_scale_after_error_value_unchanged);
    tcase_add_test(tc, test_s21_scale_after_error_bits1_unchanged);
    tcase_add_test(tc, test_s21_scale_after_error_bits2_unchanged);
    tcase_add_test(tc, test_s21_scale_after_error_scale_unchanged);
    
    // Дополнительные тесты
    tcase_add_test(tc, test_s21_scale_down_zero_success);
    tcase_add_test(tc, test_s21_scale_down_zero_final_scale);
    tcase_add_test(tc, test_s21_scale_down_zero_value_unchanged);
    tcase_add_test(tc, test_s21_scale_multiple_up_success);
    tcase_add_test(tc, test_s21_scale_multiple_up_final_scale);
    tcase_add_test(tc, test_s21_scale_multiple_up_final_value);
    tcase_add_test(tc, test_s21_scale_multiple_down_success);
    tcase_add_test(tc, test_s21_scale_multiple_down_final_scale);
    tcase_add_test(tc, test_s21_scale_multiple_down_final_value);
    
    suite_add_tcase(s, tc);
    return s;
}