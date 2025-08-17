#include <check.h>
#include "../s21_decimal.h"

START_TEST(test_s21_scale_up_basic) {
    s21_decimal value = {{1, 0, 0, 0}}; // 1 with scale 0
    
    ck_assert_int_eq(0, s21_get_scale(value));
    
    ck_assert_int_eq(0, s21_scale_up(&value, 1));
    ck_assert_int_eq(1, s21_get_scale(value));
    // After scale_up, value should be multiplied by 10
    ck_assert_int_eq(10, value.bits[0]);
}
END_TEST

START_TEST(test_s21_scale_down_basic) {
    s21_decimal value = {{10, 0, 0, 0}};
    s21_set_scale(&value, 1); // 1.0
    
    ck_assert_int_eq(0, s21_scale_down(&value, 1));
    ck_assert_int_eq(0, s21_get_scale(value));
    // After scale_down, value should be divided by 10
    ck_assert_int_eq(1, value.bits[0]);
}
END_TEST

START_TEST(test_s21_scale_up_edge_cases) {
    s21_decimal value = {{1, 0, 0, 0}};
    
    // Test invalid power
    ck_assert_int_eq(1, s21_scale_up(&value, -1));
    ck_assert_int_eq(1, s21_scale_up(&value, 29)); // exceeds max scale
    
    // Test scale overflow
    s21_set_scale(&value, 28);
    ck_assert_int_eq(1, s21_scale_up(&value, 1));
}
END_TEST

START_TEST(test_s21_scale_down_edge_cases) {
    s21_decimal value = {{1, 0, 0, 0}};
    
    // Test invalid power
    ck_assert_int_eq(1, s21_scale_down(&value, -1));
    
    // Test scale underflow
    ck_assert_int_eq(1, s21_scale_down(&value, 1)); // scale would be negative
}
END_TEST

Suite* s21_scale_suite(void) {
    Suite* s = suite_create("s21_scale");
    TCase* tc = tcase_create("core");
    
    tcase_add_test(tc, test_s21_scale_up_basic);
    tcase_add_test(tc, test_s21_scale_down_basic);
    tcase_add_test(tc, test_s21_scale_up_edge_cases);
    tcase_add_test(tc, test_s21_scale_down_edge_cases);
    
    suite_add_tcase(s, tc);
    return s;
}