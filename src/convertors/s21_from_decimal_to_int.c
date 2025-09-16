#include "../s21_decimal.h"


int s21_from_decimal_to_int(s21_decimal src, int *dst) {
    ///
    int result_code = 0;

    if(!dst){
        result_code = 1;
    }else{
        *dst = 0;
        s21_decimal truncate = src;
        s21_truncate(&truncate);

        if(truncate.bits[1] != 0 || truncate.bits[2] != 0){
            result_code = 1;
        }else{

            *dst = truncate.bits[0];
            if(s21_get_sign(src)) *dst = -*dst;
        }
    }

    return result_code;
}
