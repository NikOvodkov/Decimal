#include "../s21_decimal.h"

// Stub implementation of s21_truncate
int s21_truncate(s21_decimal * value) {

    int result = 0;

    if(!value){
        result = 1;
    }else{
        int sig = s21_get_sign(*value);
        int power = s21_get_scale(*value);
        if(power > 0){
            for(int i = 0; i < power; i++){
                s21_div_10(value);
            }
        }

        s21_set_sign(value,sig);
    }

    return result;
}
