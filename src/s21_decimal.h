#ifndef S21_DECIMAL_
#define S21_DECIMAL_

#include <math.h>
#include <stdio.h>
#include <string.h>

// MASKS:
#define MINUS 0x80000000  // 10000000 00000000 00000000 00000000
#define SCALE 0x00ff0000  // 00000000 11111111 00000000 00000001

#define S21_INT32_MAX 2147483647

typedef struct {
  unsigned int bits[4];
} s21_decimal;

/* decimal struct
  x0000000 000zzzzz 00000000 00000000   bits[2] bits[1] bits[0]
 |_______________bits[3]_____________| |________mantissa_______|
 x - биты для знака
 zzzzz - биты для scale,  т.е. 10^scale */

/* СДВИГИ:
00001010 << 2 == 00101000 сдвиг влево
10001010 << 2 == 00101000
00001010 >> 2 == 00000010 сдвиг вправо */

/* ПОБИТОВЫЕ ОПЕРАЦИИ:
~00001010 == 11110101 NOT (все 0 заменяет на 1, все 1 заменяет на 0)
00001010 & 11100011 == 00000010 AND (1 если две единицы на одном разряде,
остальное 0)
00001010 | 11100011 == 11101011 OR (0 если два нуля, если хоть один
единица, то 1)
00001010 ^ 11100011 == 11111001 XOR исключающее (если одинаковые
- 0, если разные - 1) */

// TOOLS:
void s21_zerovka(s21_decimal *dec);
int s21_get_bit(s21_decimal dec, int index);
int s21_get_sign(s21_decimal dec);
void s21_set_bit(s21_decimal *dec, int index, int bit);
void s21_set_sign(s21_decimal *dst, int n);
int s21_get_scale(s21_decimal dst);
int s21_set_scale(s21_decimal *dst, int exp);
int simple_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void simple_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void s21_simple_shift_l(s21_decimal *dec);
void s21_shift_left(s21_decimal *dec, int shift);
void s21_normalization(s21_decimal *value_1, s21_decimal *value_2);
void s21_mul_tenovka(s21_decimal *value);
void s21_div_tenovka(s21_decimal *dec);
int s21_abs(int x);

// COMPARE:
int s21_is_less(s21_decimal a, s21_decimal b);              // <
int s21_is_less_or_equal(s21_decimal a, s21_decimal b);     // <=
int s21_is_greater(s21_decimal a, s21_decimal b);           // >
int s21_is_greater_or_equal(s21_decimal a, s21_decimal b);  // >=
int s21_is_equal(s21_decimal a, s21_decimal b);             // ==
int s21_is_not_equal(s21_decimal a, s21_decimal b);         // !=

// CONVERTING:
int s21_from_int_to_decimal(int src, s21_decimal *dst);      // int -> dec
int s21_from_float_to_decimal(float src, s21_decimal *dst);  // float -> dec
int s21_from_decimal_to_int(s21_decimal src, int *dst);      // dec -> int
int s21_from_decimal_to_float(s21_decimal src, float *dst);  // dec -> float

// ARITHMETICS:
int s21_add(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result);  // '+'
int s21_sub(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result);  // '-'
int s21_mul(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result);  // '*'
int s21_div(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result);  // '/'

// OTHER FUNCTION
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

#endif  // S21_DECIMAL_