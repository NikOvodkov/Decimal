#include "../s21_decimal.h"

// Stub implementation of s21_from_int_to_decimal
int s21_from_int_to_decimal(int src, s21_decimal *dst) {

    //TODO must ininit zero decimal!!
    int return_code = 0;
    if (! dst){
        return_code = 1;
    }else{
        int sign = 0;
        if(src < 0){
            sign = 1;
            
        }
        src = ( sign == 1) ?  -src : src;

        dst->bits[0] = src;

        s21_set_sign(dst,sign);
    }


    return return_code;
}
