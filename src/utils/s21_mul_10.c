#include "../s21_decimal.h"

void s21_mul_10(s21_decimal *value) {
  s21_decimal tmp_for_mul_2 = {0}, tmp_for_mul_8 = {0}, result = {0};

  // x * 2
  int carry = 0;
  for (int i = 0; i < 3; ++i) {
    long long val = (long long)value->bits[i] * 2 + carry;
    tmp_for_mul_2.bits[i] = val & 0xFFFFFFFF;
    carry = val >> 32;
  }

  // x * 8
  carry = 0;
  for (int i = 0; i < 3; ++i) {
    long long val = (long long)value->bits[i] * 8 + carry;
    tmp_for_mul_8.bits[i] = val & 0xFFFFFFFF;
    carry = val >> 32;
  }

  // tmp1 + tmp2
  carry = 0;
  for (int i = 0; i < 3; ++i) {
    long long val =
        (long long)tmp_for_mul_2.bits[i] + tmp_for_mul_8.bits[i] + carry;
    result.bits[i] = val & 0xFFFFFFFF;
    carry = val >> 32;
  }

  result.bits[3] = value->bits[3];
  *value = result;
}