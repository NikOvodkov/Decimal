#include "../s21_decimal.h"

void s21_set_sign(
    s21_decimal *value,
    int sign) {  // parameter sign is 0 for positive, 1 for negative
  if (sign == 0) {
    value->bits[3] &= ~(1u << 31);
  } else {
    value->bits[3] |= (1u << 31);
  }
}

int s21_get_sign(
    s21_decimal value) {  // returns 0 for positive value, 1 for negative
  return (value.bits[3] >> 31) & 1;
}