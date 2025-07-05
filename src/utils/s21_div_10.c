#include "../s21_decimal.h"

void s21_div_10(s21_decimal *value) {
  s21_decimal result = {0};
  unsigned long long remainder = 0;

  for (int i = 2; i >= 0; --i) {
    unsigned long long current =
        (remainder << 32) | (unsigned long long)value->bits[i];
    result.bits[i] = current / 10;
    remainder = current % 10;
  }

  result.bits[3] = value->bits[3];
  *value = result;
}