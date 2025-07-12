#include "../s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = 0;
  if (s21_check_zero(value_1) && s21_check_zero(value_2)) {
    result = 1;
  } else if (s21_get_sign(value_1) == s21_get_sign(value_2)) {
    if (s21_get_scale(value_1) > s21_get_scale(value_2)) {
      s21_set_scale(&value_2, s21_get_scale(value_1));
    } else if (s21_get_scale(value_1) < s21_get_scale(value_2)) {
      s21_set_scale(&value_1, s21_get_scale(value_2));
    }
    int i = 0;
    while (i < 4 && value_1.bits[i] == value_2.bits[i]) {
      ++i;
    }
    if (i == 4) {
      result = 1;
    }
  }
  return result;
}
