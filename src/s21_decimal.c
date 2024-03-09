#include "s21_decimal.h"
// COMPARE:
int s21_is_equal(s21_decimal a, s21_decimal b) {  // ==
  int res = 1;
  s21_normalization(&a, &b);
  for (int i = 95; i >= 0; i--) {
    if (s21_get_bit(a, i) != s21_get_bit(b, i)) {
      res = 0;
      break;
    }
  }
  if (s21_get_sign(a) != s21_get_sign(b)) res = 0;
  return res;
}

int s21_is_not_equal(s21_decimal a, s21_decimal b) {  // !=
  return s21_is_equal(a, b) ? 0 : 1;
}

int s21_is_greater(s21_decimal a, s21_decimal b) {  // >
  int res = 1, match = 0, flag = 0;
  s21_normalization(&a, &b);
  if (s21_get_sign(a) == 1 && s21_get_sign(b) == 1) flag = 1;
  for (int i = 95; i >= 0; i--) {
    if (s21_get_bit(a, i) != s21_get_bit(b, i)) {
      if (s21_get_bit(a, i) < s21_get_bit(b, i) && !flag) {
        res = 0;
      }
      if (s21_get_bit(a, i) > s21_get_bit(b, i) && flag) {
        res = 0;
      }
      match = 1;
      break;
    }
  }
  if (match == 0) {
    res = 0;
  }
  // ifovka
  if (s21_get_sign(a) == 1 && s21_get_sign(b) == 0) res = 0;
  if (s21_get_sign(a) == 0 && s21_get_sign(b) == 1) res = 1;
  return res;
}

int s21_is_less(s21_decimal a, s21_decimal b) {  // <
  int res = 0, match = 0;
  s21_normalization(&a, &b);
  res = s21_is_greater(a, b) ? 0 : 1;
  for (int i = 95; i >= 0; i--) {
    if (s21_get_bit(a, i) != s21_get_bit(b, i)) {
      match = 1;
      break;
    }
  }
  if (match == 0) {
    res = 0;
  }
  return res;
}

int s21_is_greater_or_equal(s21_decimal a, s21_decimal b) {  // >=
  int res = 0;
  if (s21_is_greater(a, b) || s21_is_equal(a, b)) res = 1;
  return res;
}

int s21_is_less_or_equal(s21_decimal a, s21_decimal b) {  // <=
  int res = 0;
  if (s21_is_less(a, b) || s21_is_equal(a, b)) res = 1;
  return res;
}
// CONVERT:
int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int res = 0;
  s21_zerovka(dst);
  if (src < 0) {
    s21_set_sign(dst, 1);
    src *= -1;
  }
  if (src > S21_INT32_MAX || src < -S21_INT32_MAX)
    res = 1;
  else {
    dst->bits[0] = src;
  }
  return res;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int res = 0;
  if (src.bits[1] || src.bits[2])
    res = 1;
  else
    *dst = src.bits[0];
  if (s21_get_sign(src)) *dst *= -1;
  return res;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int result = 0;
  if (isnan(src) || isinf(src)) {
    result = 1;
  }
  if (dst && !result) {
    s21_zerovka(dst);
    int sign = 0;
    if (src < 0) {
      sign = 1;
      src *= -1;
    }
    int new = (int)src, exp = 0;
    while (src - ((float)new / (int)(pow(10, exp))) != 0) {
      exp++;
      new = src *(int)(pow(10, exp));
    }
    s21_from_int_to_decimal(new, dst);

    if (sign) s21_set_sign(dst, 1);

    s21_set_scale(dst, exp);
  } else
    result = 1;
  return result;
}

int s21_from_decimal_to_float(s21_decimal src,
                              float *dst) {  // deSHImal to flotka
  *dst = 0;
  double temp = 0;
  for (int i = 0; i < 96; i++) {
    temp += s21_get_bit(src, i) * pow(2, i);
  }
  temp = temp * pow(10, -s21_get_scale(src));
  if (s21_get_sign(src)) {
    temp *= -1;
  }
  *dst = (float)temp;
  return 0;
}
// TOOLS:

void s21_zerovka(s21_decimal *dec) { memset(dec, 0, sizeof(s21_decimal)); }

int s21_get_bit(s21_decimal dec, int index) {
  int position = index % 32;
  int num_i = index / 32;
  int mask = 1u << position;
  return (dec.bits[num_i] & mask) >> position;
}

void s21_set_bit(s21_decimal *dec, int index, int bit) {  // install bit
  int position = index % 32;
  int num_i = index / 32;
  int mask = 1u << position;
  if (bit == 1)
    dec->bits[num_i] |= mask;
  else
    dec->bits[num_i] &= (~mask);
}

int s21_get_sign(s21_decimal dec) { return s21_get_bit(dec, 127); }

void s21_set_sign(s21_decimal *dst, int n) { s21_set_bit(dst, 127, n); }

int s21_get_scale(s21_decimal dst) {  // scalekovka
  return (dst.bits[3] & SCALE) >> 16;
}

int s21_set_scale(s21_decimal *dst, int exp) {
  dst->bits[3] &= MINUS;  // cleangovka
  return dst->bits[3] |= exp << 16;
}

void s21_shift_left(s21_decimal *dec, int shift) {
  for (int i = 0; i < shift; i++) {
    s21_simple_shift_l(dec);
  }
}

void s21_simple_shift_l(s21_decimal *dec) {
  int end_zero_mantiss = s21_get_bit(*dec, 32 - 1);  // биткует конец bits[0]
  int end_first_mantiss = s21_get_bit(*dec, 64 - 1);  // биткует конец bits[1]
  for (int i = 0; i < 3; ++i) {
    dec->bits[i] <<= 1;  // сдвиг каждой мантиски на 1
  }
  s21_set_bit(dec, 32, end_zero_mantiss);  // сеткует в начало bits[1]
  s21_set_bit(dec, 64, end_first_mantiss);  // сеткует в начало bits[2]
}

void s21_mul_tenovka(s21_decimal *value) {
  s21_decimal ten = {{10, 0, 0, 0}};
  s21_decimal resa = {{0, 0, 0, 0}};
  s21_mul(*value, ten, &resa);
  *value = resa;
  int scale = s21_get_scale(*value) + 1;
  s21_set_scale(value, scale);
}

void s21_div_tenovka(s21_decimal *dec) {
  s21_decimal tmp = {{10, 0, 0, 0}};
  s21_div(*dec, tmp, dec);
  int scale = s21_get_scale(*dec) - 1;
  s21_set_scale(dec, scale);
}

void s21_normalization(s21_decimal *value_1, s21_decimal *value_2) {
  int scale_1 = s21_get_scale(*value_1), scale_2 = s21_get_scale(*value_2);
  while (scale_1 != scale_2) {
    int delta = s21_abs(scale_1 - scale_2);
    if (scale_1 < scale_2) {
      if ((delta + scale_1) < 29) {
        s21_mul_tenovka(value_1);
        scale_1 = s21_get_scale(*value_1);
      } else {
        s21_div_tenovka(value_1);
        scale_1 = s21_get_scale(*value_1);
      }
    } else if (scale_1 > scale_2) {
      if ((scale_2 + delta) < 29) {
        s21_mul_tenovka(value_2);
        scale_2 = s21_get_scale(*value_2);
      } else {
        s21_div_tenovka(value_2);
        scale_2 = s21_get_scale(*value_2);
      }
    }
  }
  return;
}

int s21_abs(int x) {
  if (x < 0) x = x * -1;
  return x;
}
//  ARITHMETIC:
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int res = 0, zs = s21_get_sign(value_1), vs = s21_get_sign(value_2);
  if (value_1.bits[0] > 4294967294) res = 1;
  if (value_2.bits[0] > 4294967294) res = 1;
  if (res == 1 && (zs || vs)) res = 2;
  s21_zerovka(result);
  s21_normalization(&value_1, &value_2);
  if (zs != vs) {  // subovka
    if (zs == 0 && vs == 1) {
      s21_set_sign(&value_2, 0);
      s21_sub(value_1, value_2, result);
      if (s21_is_less(value_1, value_2)) s21_set_sign(result, 1);
    }
    if (zs == 1 && vs == 0) {
      s21_set_sign(&value_1, 0);
      s21_sub(value_1, value_2, result);
      if (s21_is_greater(value_1, value_2)) s21_set_sign(result, 1);
    }
  } else if (zs && vs) {  // addovka
    simple_add(value_1, value_2, result);
    s21_set_sign(result, 1);
  } else if (!zs && !vs) {  // simple addovka
    simple_add(value_1, value_2, result);
  }
  int exp_norm = s21_get_scale(value_1);
  s21_set_scale(result, exp_norm);
  return res;
}

int simple_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int res = 0, umovka = 0, z = 0, v = 0;  // umovka - бит в уме
                                          /* table add:
                                          0 + 0 = 0;
                                          0 + 1 = 1;
                                          1 + 0 = 1;
                                          1 + 1 = 1(umovka)0;
                                          */
  for (int i = 0; i < 96; i++) {
    z = s21_get_bit(value_1, i);
    v = s21_get_bit(value_2, i);
    if (i == 96 && (z == 1 || v == 1)) res = 1;  // слишком большая intovka
    if (res == 0) {
      if (z == 1 && v == 1 && umovka == 1) {
        s21_set_bit(result, i, 1);
        umovka = 1;
      } else if (z == 1 && v == 1 && umovka == 0) {
        s21_set_bit(result, i, 0);
        umovka = 1;
      } else if (z == 1 && v == 0 && umovka == 0) {
        s21_set_bit(result, i, 1);
        umovka = 0;
      } else if (z == 1 && v == 0 && umovka == 1) {
        s21_set_bit(result, i, 0);
        umovka = 1;
      } else if (z == 0 && v == 1 && umovka == 0) {
        s21_set_bit(result, i, 1);
        umovka = 0;
      } else if (z == 0 && v == 1 && umovka == 1) {
        s21_set_bit(result, i, 0);
        umovka = 1;
      } else if (z == 0 && v == 0 && umovka == 0) {
        s21_set_bit(result, i, 0);
        umovka = 0;
      } else if (z == 0 && v == 0 && umovka == 1) {
        s21_set_bit(result, i, 1);
        umovka = 0;
      }
      if (result->bits[3] == 1)
        res = 1;  // intovka дошла до ячейки со степенями и знаком
    }
  }
  return res;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int res = 0, zs = s21_get_sign(value_1), vs = s21_get_sign(value_2);
  if (value_1.bits[0] > 4294967294) res = 1;
  if (value_2.bits[0] > 4294967294) res = 1;
  if (res == 1 && (zs || vs)) res = 2;
  s21_zerovka(result);
  s21_normalization(&value_1, &value_2);
  if (zs != vs) {
    if (zs == 1 && vs == 0) {
      s21_set_sign(&value_1, 0);
      simple_add(value_1, value_2, result);
      s21_set_sign(result, 1);
    } else {
      s21_set_sign(&value_2, 0);
      simple_add(value_1, value_2, result);
    }
  } else if (zs == 1 && vs == 1) {
    if (s21_is_less(value_2, value_1)) {
      s21_set_sign(&value_2, 0);
      simple_sub(value_2, value_1, result);
      s21_set_sign(result, 0);
    } else {
      s21_set_sign(&value_2, 0);
      s21_set_sign(&value_1, 0);
      simple_sub(value_1, value_2, result);
      if (s21_is_equal(value_1, value_2)) {
        s21_set_sign(result, 0);
      } else {
        s21_set_sign(result, 1);
      }
    }
  } else if ((vs == 0 && zs == 0) && s21_is_greater(value_2, value_1)) {
    simple_sub(value_2, value_1, result);
  } else {
    simple_sub(value_1, value_2, result);
  }
  int exp_norm = s21_get_scale(value_1);
  s21_set_scale(result, exp_norm);
  if (result->bits[3] == 1) res = 1;
  return res;
}

void simple_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  /* table sub:
  0 - 0 = 0;
  0 - 1 = 1(zaem)1;
  1 - 0 = 1;
  1 - 1 = 0;
  */
  int z = 0, v = 0;
  for (int i = 0; i < 96; i++) {
    z = s21_get_bit(value_1, i);
    v = s21_get_bit(value_2, i);
    if (z == 0 && v == 1) {
      int n_e = 0;  // n_e - next element
      while (s21_get_bit(value_1, i + n_e) != 1) {
        s21_set_bit(&value_1, i + n_e, 1);
        n_e++;
      }
      if (s21_get_bit(value_1, i + n_e) == 1) {
        s21_set_bit(&value_1, i + n_e, 0);
      }
      s21_set_bit(result, i, 1);
    } else if (z == 1 && v == 0) {
      s21_set_bit(result, i, 1);
    } else if (z == 1 && v == 1) {
      s21_set_bit(result, i, 0);
    } else if (z == 0 && v == 0) {
      s21_set_bit(result, i, 0);
    }
  }
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  /* table mul:
  0 * 0 = 0;
  0 * 1 = 0;
  1 * 0 = 0;
  1 * 1 = 1;
  */
  int res = 0;
  s21_zerovka(result);
  int sign1 = s21_get_sign(value_1), sign2 = s21_get_sign(value_2);
  int exp = s21_get_scale(value_1) +
            s21_get_scale(value_2);  // при умножовке степени складываются
  for (int i = 0; i < 96; i++) {
    if (s21_get_bit(value_1, i) == 1) {
      simple_add(value_2, *result, result);  // Заменил s21_add на simple_add
    }
    s21_shift_left(&value_2, 1);  // делаем shiftovku влево == * 2
  }
  if (result->bits[0] >= 4294967294) res = 1;  // если intovka слишком большая
  s21_set_scale(result, exp);
  if (sign1 != sign2)
    s21_set_sign(result, 1);  // '-' * '+' = '-' || '+' * '-' = '-'
  if (sign1 == sign2) s21_set_sign(result, 0);          // '-' * '-' = '+'
  if (res == 1 && s21_get_sign(*result) == 1) res = 2;  // -4294967294
  return res;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int res = 0, i = 95, j = 95;
  if (value_2.bits[0] == 0 && value_2.bits[1] == 0 && value_2.bits[2] == 0)
    res = 3;
  int sign1 = s21_get_sign(value_1), sign2 = s21_get_sign(value_2);
  int exp = s21_get_scale(value_1) - s21_get_scale(value_2);
  s21_set_scale(&value_1, 0);
  s21_set_scale(&value_2, 0);
  s21_set_sign(&value_1, 0);
  s21_set_sign(&value_2, 0);
  s21_decimal copy = value_2;
  s21_zerovka(result);
  while (s21_get_bit(value_1, i) != 1) {
    i--;
  }
  while (s21_get_bit(value_2, j) != 1) {
    j--;
  }
  while (i >= j) {
    s21_shift_left(&value_2, i - j);
    if (s21_is_greater_or_equal(value_1, value_2)) {
      simple_sub(value_1, value_2, &value_1);
      s21_set_bit(result, i - j, 1);
    } else {
      s21_set_bit(result, i - j, 0);
    }
    value_2 = copy;
    i--;
  }
  s21_set_scale(result, exp);
  if (exp < 0) {
    s21_set_scale(result, 0);
    s21_decimal tmp = {{0}};
    exp = s21_abs(exp);
    int multiply = pow(10, exp);
    s21_from_int_to_decimal(multiply, &tmp);
    s21_mul(*result, tmp, result);
  }
  if (sign1 != sign2) s21_set_sign(result, 1);
  if (sign1 == sign2) s21_set_sign(result, 0);
  if (s21_get_bit(*result, 96) == 1) res = 1;
  if (res == 1 && s21_get_sign(*result) == 1) res = 2;
  return res;
}
// OTHER FUNCTION
int s21_negate(s21_decimal value, s21_decimal *result) {
  int res = 0;
  *result = value;
  if (s21_get_sign(value) == 0) {
    s21_set_sign(result, 1);
  } else {
    s21_set_sign(result, 0);
  }
  return res;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int res = 0;
  if (s21_get_scale(value) > 0) {
    do {
      s21_div_tenovka(&value);
    } while (s21_get_scale(value) > 0);
  }
  *result = value;
  return res;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  int res = 0;
  s21_zerovka(result);
  int scale = s21_get_scale(value), sign = s21_get_sign(value);
  if (result) {
    if (scale) s21_truncate(value, result);
    if (sign) {
      s21_decimal one = {{1, 0, 0, 0}};
      simple_add(*result, one, result);
    }
  } else {
    res = 1;
  }
  return res;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  s21_zerovka(result);
  int sign = s21_get_sign(value), res = 0;
  s21_decimal five = {{5, 0, 0, 0b00000000000000010000000000000000}},
              one = {{1, 0, 0, 0}};
  s21_decimal okryglenie = {{0, 0, 0, 0}}, tmp = {{0, 0, 0, 0}};
  s21_set_sign(&value, 0);
  if (result == NULL) {
    res = 1;
  } else {
    s21_truncate(value, &okryglenie);
    s21_sub(value, okryglenie, &tmp);
    s21_set_scale(&tmp, s21_get_scale(value));
    if (s21_is_greater_or_equal(tmp, five)) {
      s21_add(okryglenie, one, result);
      s21_set_scale(result, 0);
      s21_set_sign(result, sign);
    } else {
      *result = okryglenie;
      s21_set_scale(result, 0);
      s21_set_sign(result, sign);
    }
  }
  return res;
}
