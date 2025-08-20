#include "../s21_decimal.h"

void s21_set_scale(s21_decimal *value, int new_scale) {
    if (new_scale >= 0 && new_scale <= 28) {
        value->bits[3] &= ~(0xFF << 16);     // Очищаем поле масштаба
        value->bits[3] |= (new_scale << 16);  // Устанавливаем новый масштаб
    }
}

int s21_get_scale(s21_decimal value) {  // returns the power of 10
  int scale = (value.bits[3] >> 16) & 0xFF;
  return scale;
}

int s21_scale_up(s21_decimal *value, int power) {
    int result = 0;
    
    // Проверка входных параметров
    if (power < 0 || power > 28) {
        result = 1;
    }
    
    int current_scale = s21_get_scale(*value);
    int new_scale = current_scale + power;
    
    if (new_scale > 28) {
        result = 1;
    }
    
    // Умножаем мантиссу на 10^power с проверкой переполнения
    for (int i = 0; i < power && result == 0; i++) {
        if (s21_will_mul10_overflow(*value)) {
            result = 1;  // Переполнение!
        } else {
            s21_mul_10(value);
        }
    }
    
    // Устанавливаем новый масштаб только если не было ошибок
    if (result == 0) {
        s21_set_scale(value, new_scale);
    }
    
    return result;
}

int s21_scale_down(s21_decimal *value, int power) {
    int result = 0;
    
    // Проверка входных параметров
    if (power < 0) {
        result = 1;
    }
    
    int current_scale = s21_get_scale(*value);
    int new_scale = current_scale - power;
    
    if (new_scale < 0) {
        result = 1;
    }
    
    // Делим мантиссу на 10^power с проверкой потери точности
    for (int i = 0; i < power && result == 0; i++) {
        if (s21_will_div10_lose_precision(*value)) {
            result = 1;  // Потеря точности!
        } else {
            s21_div_10(value);
        }
    }
    
    // Устанавливаем новый масштаб только если не было ошибок
    if (result == 0) {
        s21_set_scale(value, new_scale);
    }
    
    return result;
}

// Вспомогательная функция для проверки переполнения при умножении на 10
int s21_will_mul10_overflow(s21_decimal value) {
    int result = 0; // По умолчанию - переполнения нет
    
    // Проверяем умножение на 2
    s21_decimal mul_2 = {{0}};
    uint64_t carry = 0;
    int overflow_detected = 0;
    
    for (int i = 0; i < 3 && !overflow_detected; i++) {
        uint64_t current_val = (uint64_t)value.bits[i];
        uint64_t multiplied = current_val * 2 + carry;
        
        if (multiplied > 0xFFFFFFFF) {
            overflow_detected = 1;
        } else {
            mul_2.bits[i] = multiplied & 0xFFFFFFFF;
            carry = multiplied >> 32;
        }
    }
    
    // Проверяем умножение на 8
    s21_decimal mul_8 = {{0}};
    carry = 0;
    
    for (int i = 0; i < 3 && !overflow_detected; i++) {
        uint64_t current_val = (uint64_t)value.bits[i];
        uint64_t multiplied = current_val * 8 + carry;
        
        if (multiplied > 0xFFFFFFFF) {
            overflow_detected = 1;
        } else {
            mul_8.bits[i] = multiplied & 0xFFFFFFFF;
            carry = multiplied >> 32;
        }
    }
    
    // Проверяем сложение (2 + 8 = 10)
    carry = 0;
    
    for (int i = 0; i < 3 && !overflow_detected; i++) {
        uint64_t sum = (uint64_t)mul_2.bits[i] + mul_8.bits[i] + carry;
        
        if (sum > 0xFFFFFFFF) {
            overflow_detected = 1;
        } else {
            carry = sum >> 32;
        }
    }
    
    // Если на любом этапе обнаружено переполнение
    if (overflow_detected || carry != 0) {
        result = 1;
    }
    
    return result;
}

// Вспомогательная функция для проверки потери точности при делении на 10  
int s21_will_div10_lose_precision(s21_decimal value) {
    int result = 0; // По умолчанию - потери точности нет
    uint64_t remainder = 0;
    int precision_lost = 0;
    
    // Проверяем деление каждого 32-битного блока
    for (int i = 2; i >= 0 && !precision_lost; i--) {
        uint64_t current_block = (remainder << 32) | (uint64_t)value.bits[i];
        uint64_t quotient = current_block / 10;
        remainder = current_block % 10;
        
        // Если это последний блок и есть остаток - потеря точности
        if (i == 0 && remainder != 0) {
            precision_lost = 1;
        }
    }
    
    if (precision_lost) {
        result = 1;
    }
    
    return result;
}