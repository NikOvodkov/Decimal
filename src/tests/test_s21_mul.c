#include <check.h>
#include "../s21_decimal.h"

START_TEST(test_s21_mul_basic) {
    // TODO: implement test
    ck_assert_int_eq(1, 1);
} END_TEST

Suite* s21_mul_suite(void) {
    Suite* s = suite_create("s21_mul");
    TCase* tc = tcase_create("core");
    tcase_add_test(tc, test_s21_mul_basic);
    suite_add_tcase(s, tc);
    return s;
}
