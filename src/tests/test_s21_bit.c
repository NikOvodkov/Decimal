#include <check.h>
#include "../s21_decimal.h"

START_TEST(test_s21_get_bit_basic) {
    s21_decimal value = {{0}};
    value.bits[0] = 1; // 00000001
    
    ck_assert_int_eq(1, s21_get_bit(value, 0)); // bit 0 should be 1
    ck_assert_int_eq(0, s21_get_bit(value, 1)); // bit 1 should be 0
    ck_assert_int_eq(0, s21_get_bit(value, 31)); // bit 31 should be 0
}
END_TEST

START_TEST(test_s21_set_bit_basic) {
    s21_decimal value = {{0}};
    
    s21_set_bit(&value, 0, 1);
    ck_assert_int_eq(1, s21_get_bit(value, 0));
    
    s21_set_bit(&value, 31, 1);
    ck_assert_int_eq(1, s21_get_bit(value, 31));
    
    s21_set_bit(&value, 0, 0);
    ck_assert_int_eq(0, s21_get_bit(value, 0));
}
END_TEST

START_TEST(test_s21_get_bit_edge_cases) {
    s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
    
    ck_assert_int_eq(1, s21_get_bit(value, 0));   // first bit
    ck_assert_int_eq(1, s21_get_bit(value, 31));  // last bit of first word
    ck_assert_int_eq(1, s21_get_bit(value, 32));  // first bit of second word
    ck_assert_int_eq(1, s21_get_bit(value, 127)); // last bit overall
    
    // Test out of bounds
    ck_assert_int_eq(0, s21_get_bit(value, -1));
    ck_assert_int_eq(0, s21_get_bit(value, 128));
}
END_TEST

START_TEST(test_s21_set_bit_edge_cases) {
    s21_decimal value = {{0}};
    
    // Test out of bounds - should not crash
    s21_set_bit(&value, -1, 1);
    s21_set_bit(&value, 128, 1);
    
    // Test setting all bits in first word
    for (int i = 0; i < 32; i++) {
        s21_set_bit(&value, i, 1);
        ck_assert_int_eq(1, s21_get_bit(value, i));
    }
    
    // Test clearing all bits
    for (int i = 0; i < 32; i++) {
        s21_set_bit(&value, i, 0);
        ck_assert_int_eq(0, s21_get_bit(value, i));
    }
}
END_TEST

Suite* s21_bit_suite(void) {
    Suite* s = suite_create("s21_bit");
    TCase* tc = tcase_create("core");
    
    tcase_add_test(tc, test_s21_get_bit_basic);
    tcase_add_test(tc, test_s21_set_bit_basic);
    tcase_add_test(tc, test_s21_get_bit_edge_cases);
    tcase_add_test(tc, test_s21_set_bit_edge_cases);
    
    suite_add_tcase(s, tc);
    return s;
}