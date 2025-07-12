#include "../s21_decimal.h"

int s21_is_less(s21_decimal value_1,
                s21_decimal value_2) {  // value_1 < value_2
  int result = 1;
  if (s21_check_zero(value_1) && s21_check_zero(value_2)) {
    result = 0;
  } else if (s21_is_equal(value_1, value_2)) {
    result = 0;
  } else if (s21_get_sign(value_1) != s21_get_sign(value_2)) {
    result = s21_get_sign(value_1) > s21_get_sign(value_2);
  } else if (s21_get_sign(value_1) == 1 && s21_get_sign(value_2) == 1) {
    s21_set_sign(&value_1, 0);
    s21_set_sign(&value_2, 0);
    result = s21_is_less(value_2, value_1);
    s21_set_sign(&value_1, 1);
    s21_set_sign(&value_2, 1);
  } else {
    if (s21_get_scale(value_1) > s21_get_scale(value_2)) {
      s21_set_scale(&value_2, s21_get_scale(value_1));
    } else if (s21_get_scale(value_1) < s21_get_scale(value_2)) {
      s21_set_scale(&value_1, s21_get_scale(value_2));
    }

    int i = 2;
    while (i >= 0 && value_1.bits[i] == value_2.bits[i]) {
      --i;
    }

    if (i >= 0) {
      result = value_1.bits[i] < value_2.bits[i];
    }
  }
  return result;
}