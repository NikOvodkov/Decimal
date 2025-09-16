#include "../s21_decimal.h"

// float src, s21_decimal *dst
int s21_from_float_to_decimal(float src, s21_decimal *dst) {
    int code = 0;

    if(!dst){
        code = 1;
    }else{
        //Если всё хорошо (что бывает далеко не всегда!)
        s21_decimal result = {{0,0,0,0}};
        char str_ver[256];
        sprintf(str_ver,"%.7f",src);
        int power = 0;
        int flag = 0;
        int i = 0;
        while (str_ver[i] != '\0')
        {
            if(flag){
                power++;
            }

            if(str_ver[i] == '.'){
                flag = 1;
            }

            if(str_ver[i] >= '0' && str_ver[i] <= '9'){
                s21_decimal tmp = {{0,0,0,0}};
                tmp.bits[0] = str_ver[i] - '0';
                
                s21_mul_10(&result);
                s21_add(tmp,result,&result);
            }

            i++;
        }
        
        for(int i = 0; i < power; i++){
            
            s21_div_10(&result);
            s21_set_scale(&result,2);
        }

        *dst = result;
    }

    return code;
}
