
#include "s21_decimal.h"

// Bits 0 to 15, the lower word, are unused and must be zero.
// Bits 16 to 23 must contain an exponent between 0 and 28, which indicates the power of 10 to divide the integer number.
// Bits 24 to 30 are unused and must be zero.
// Bit 31 contains the sign; 0 meaning positive, and 1 meaning negative.


// typedef struct 
// {
//     int bits[4];
// } s21_decimal;

int count_digits(float num, int* exp){
    num = num < 0 ? -num : num;
    int count = 0;
    int count2 = 0;
    while(num >= 1){
        num /= 10;
        count++;
    }
    while(num < 0.1){
        num *= 10;
        count2++;
    }
    *exp = count2;
    return count;
}


int s21_from_int_to_decimal(int src, s21_decimal *dst){
    int exp;
    int num = count_digits(src, &exp);
    if(src < 0){
        dst->bits[3] = 0;
        printf("%d\n", num);
        dst->bits[3] = (1 << 31) | (num << 16);
        src = -src;
    }
    else{
        // dodelat
        dst->bits[3] = 0;
    }
    dst->bits[0] = src;
    dst->bits[1] = 0;
    dst->bits[2] = 0;
    return 0;
}

// int s21_from_float_to_decimal(float src, s21_decimal *dst){
//    
//     return 0;
// }


int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result){

return 0;
}

int s21_print_decimal(s21_decimal src){
    printf("%c%d%d%d\n", src.bits[3] >> 31 == -1 ? '-' : ' ', src.bits[0], src.bits[1], src.bits[2]);
    return 0;
}

int main() {
    s21_decimal d1, d2, res;
    s21_from_int_to_decimal(-123456789, &d1);
    s21_from_int_to_decimal(987654321, &d2);
    s21_add(d1, d2, &res);

    for(int i=sizeof(d1.bits[3])*8-1; i>=0; --i){
        printf("%d", (d1.bits[3] >> i)&1);
    }

    // s21_print_decimal(d1);
    // s21_print_decimal(d2);
    // s21_print_decimal(res);
    return 0;
}

////////

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result){
    int exp_1 = (value_1.bits[0] >> 16) & 0x7F;
    int exp_2 = (value_2.bits[0] >> 16) & 0x7F;
    int exp = exp_1 > exp_2 ? exp_1 : exp_2;
    int sign_1 = value_1.bits[0] >> 31;
    int sign_2 = value_2.bits[0] >> 31;
    int sign = sign_1 == sign_2 ? sign_1 : 0;
    int num_1 = value_1.bits[0] & 0xFFFF;
    int num_2 = value_2.bits[0] & 0xFFFF;
    int num = num_1 - num_2;
    if(num < 0){
        num += 10000;
        exp--;
    }
    result->bits[0] = (sign << 31) | (exp << 16) | num;
    num_1 = value_1.bits[1] & 0xFFFF;
    num_2 = value_2.bits[1] & 0xFFFF;
    num += num_1 - num_2;
    if(num < 0){
        num += 10000;
        exp--;
    }
    result->bits[1] = (exp << 16) | num;
    num_1 = value_1.bits[2] & 0xFFFF;
    num_2 = value_2.bits[2] & 0xFFFF;
    num += num_1 - num_2;
    if(num < 0){
        num += 10000;
        exp--;
    }
    result->bits[2] = (exp << 16) | num;
    num_1 = value_1.bits[3] & 0xFFFF;
    num_2 = value_2.bits[3] & 0xFFFF;
    num += num_1 - num_2;
    if(num < 0){
        num += 10000;
        exp--;
    }
    result->bits[3] = (exp << 16) | num;
    return 0;
}
