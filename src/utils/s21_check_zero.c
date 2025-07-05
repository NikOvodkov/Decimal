#include "../s21_decimal.h"

int s21_check_zero(
    s21_decimal value) {  // returns 1 if value is zero, 0 otherwise
  int i = 0;
  while (i < 3 && value.bits[i] == 0) {
    ++i;
  }
  return i == 3 ? 1 : 0;
}