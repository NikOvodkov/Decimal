#include "../s21_decimal.h"

void s21_set_scale(s21_decimal *value,
                   int new_scale) {  // set the power of 10, will not change the
                                     // value 1.0 -> 1.00
  if (0 <= new_scale && new_scale <= 28) {
    int old_scale = s21_get_scale(*value);
    int diff = new_scale - old_scale;

    if (diff > 0) {
      for (int i = 0; i < diff; ++i) {
        s21_mul_10(value);
      }
    } else if (diff < 0) {
      for (int i = 0; i < -diff; ++i) {
        s21_div_10(value);
      }
    }

    value->bits[3] &= ~(0xFF << 16);
    value->bits[3] |= (new_scale & 0xFF) << 16;
  }
}

int s21_get_scale(s21_decimal value) {  // returns the power of 10
  int scale = (value.bits[3] >> 16) & 0xFF;
  return scale;
}