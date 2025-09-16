#include "../s21_decimal.h"

#include "math.h"

int s21_is_set_bit(int number, int index) {
    return !!(number & (1U << index));
}

int s21_decimal_is_set_bit(s21_decimal decimal, int index) {
    return s21_is_set_bit(decimal.bits[index / 32], index % 32);
}

// Stub implementation of s21_from_decimal_to_float
int s21_from_decimal_to_float(s21_decimal src, float *dst) {
    int code = 0;
    
    if(dst == NULL){
        
        code = 1;
    }else if (s21_check_zero(src)){
        //Вдруг число равно нулю
        int sign = s21_get_sign(src);
        if (sign == 1) {
            *dst = -0.0;
        } else {
            *dst = 0.0;
        }
        printf("%d ",src.bits[0]);
    }else{
        *dst = 0.0;

        double tmp = 0.0;

        int sig = s21_get_sign(src);
        int power = s21_get_scale(src);

        for(int i = 0; i < 96; i++){
            if (s21_decimal_is_set_bit(src, i) != 0) {
                tmp += pow(2.0, i);
                
            }
        }

        tmp /= pow(10,power);

        if(sig){
            tmp *= -1.0;
        }

        *dst = (float)tmp;
    }
    
    return code;
}
