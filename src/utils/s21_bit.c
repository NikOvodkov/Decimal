#include "../s21_decimal.h"

int s21_get_bit(s21_decimal value, int bit_pos) {
    int result = 0;
    if (bit_pos >= 0 && bit_pos <= 127) {
        int word_index = bit_pos / 32;
        int bit_index = bit_pos % 32;
        result = (value.bits[word_index] >> bit_index) & 1;
    }
    return result;
}

void s21_set_bit(s21_decimal *value, int bit_pos, int bit_value) {
    if (bit_pos >= 0 && bit_pos <= 127) {
        int word_index = bit_pos / 32;
        int bit_index = bit_pos % 32;
        
        if (bit_value) {
            value->bits[word_index] |= (1 << bit_index);
        } else {
            value->bits[word_index] &= ~(1 << bit_index);
        }
    }
}