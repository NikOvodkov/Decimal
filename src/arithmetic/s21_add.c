#include "../s21_decimal.h"


/*
    TODO 
    Знаю, что объявление этой функции должно быть вынесено в отдельный заголовочный файл хелперов.
    Но пока такого файла у меня нет :( 
    Жду Гошу.
*/

int normalize(s21_decimal * v1, s21_decimal * v2){
    int s1 = s21_get_scale(*v1);
    int s2 = s21_get_scale(*v2);

    if (s1 == s2) return 0;

    int dif = (s1 < s2) ? s2 - s1 : s1 - s2;

    s21_decimal * smaller = (s1 < s2) ? v1 : v2;
    s21_decimal * bigger = (s1 < s2) ? v2 : v1;

    for (int i = 0; i < dif; i++){
        s21_mul_10(smaller);
    }
    
    s21_set_scale(smaller,s21_get_scale(*bigger));
    return 0;
}

int s21_add_core(s21_decimal v1, s21_decimal v2, s21_decimal * res){

    normalize(&v1,&v2);
    uint64_t r = 0;
    for(int i = 0; i < 3; i++){
        uint64_t s = (int64_t)v1.bits[i] + v2.bits[i] + r;
        res->bits[i] = (int)(s & 0xFFFFFFFF);
        r = s >> 32;
    }
    return 0;
}

// Stub implementation of s21_add
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {

    int code = 0;

    if(result == NULL){
        code = 1;
       
    }else{

        int sig1 = s21_get_sign(value_1);
        int sig2 = s21_get_sign(value_2);
        
        if(sig1 == sig2){
            //оба числа одного знака
            s21_add_core(value_1,value_2,result);
            s21_set_sign(result,sig1);
        }else if (sig1 == 0 && sig2 == 1)
        {
            //второе число отрицательное
            //TODO нужна функция вычитания
        }else if (sig1 == 1 && sig2 == 0)
        {
            //первое число отрицательное
            //TODO нужна функция вычитания
        }

        

    }
    

    return code;
}

