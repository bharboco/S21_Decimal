#include <check.h>

#include "s21_decimal.h"

START_TEST(s21_is_lesster_defolt_value) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  int res = s21_is_less(value_1, value_2);
  ck_assert_int_eq(res, 0);

  s21_decimal value_3 = {{1, 0, 0, 0}};
  s21_decimal value_4 = {{0, 0, 0, 0}};
  res = s21_is_less(value_3, value_4);
  ck_assert_int_eq(res, 0);

  s21_decimal value_5 = {{0, 0, 0, 0}};
  s21_decimal value_6 = {{1, 0, 0, 0}};
  res = s21_is_less(value_5, value_6);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_is_lesster_scale_value) {
  s21_decimal value_1 = {
      {2147483647, 0, 0, 0b00000000000000110000000000000000}};  // scale 3
  s21_decimal value_2 = {
      {2147483647, 0, 0, 0b00000000000000000000000000000000}};  // scale 0
  int res = s21_is_less(value_1, value_2);
  ck_assert_int_eq(res, 1);

  s21_decimal value_3 = {
      {325423523, 0, 0, 0b00000000000000000000000000000000}};  // scale 0
  s21_decimal value_4 = {
      {325423523, 0, 0, 0b00000000000000110000000000000000}};  // scale 3
  res = s21_is_less(value_3, value_4);
  ck_assert_int_eq(res, 0);

  s21_decimal value_5 = {
      {2147483647, 0, 2147483647, 0b00000000000000000000000000000000}};
  s21_decimal value_6 = {
      {2147483647, 0, 2147483647, 0b00000000000000110000000000000000}};
  res = s21_is_less(value_5, value_6);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_is_lesster_negative_value_for_scale_and_normal) {
  s21_decimal value_1 = {
      {2147483647, 0, 0, 0b10000000000000110000000000000000}};  // scale 3
  s21_decimal value_2 = {
      {2147483647, 0, 0,
       0b10000000000000000000000000000000}};  // negativ value scale 0
  int res = s21_is_less(value_1, value_2);
  ck_assert_int_eq(res, 0);

  s21_decimal value_3 = {
      {325423523, 0, 0, 0b00000000000000000000000000000000}};  // scale 0
  s21_decimal value_4 = {
      {325423523, 0, 0,
       0b10000000000000110000000000000000}};  // negativ value scale 3
  res = s21_is_less(value_3, value_4);
  ck_assert_int_eq(res, 0);

  s21_decimal value_5 = {
      {2147483647, 0, 2147483647,
       0b10000000000001000000000000000000}};  // negativ value scale 4
  s21_decimal value_6 = {
      {2147483647, 0, 2147483647,
       0b10000000000000110000000000000000}};  // negativ value scale 3
  res = s21_is_less(value_5, value_6);
  ck_assert_int_eq(res, 0);

  s21_decimal value_7 = {
      {2147483647, 0, 2147483647,
       0b10000000000000110000000000000000}};  // negativ value scale 4
  s21_decimal value_8 = {
      {2147483647, 0, 2147483647,
       0b10000000000001000000000000000000}};  // negativ value scale 3
  res = s21_is_less(value_7, value_8);
  ck_assert_int_eq(res, 1);

  s21_decimal value_9 = {
      {2147483649, 0, 2147483647,
       0b10000000000000000000000000000000}};  // negativ value
  s21_decimal value_10 = {
      {2147483647, 0, 2147483647,
       0b10000000000000000000000000000000}};  // negativ value
  res = s21_is_less(value_9, value_10);
  ck_assert_int_eq(res, 1);

  s21_decimal value_11 = {
      {2147483647, 0, 2147483647,
       0b10000000000000000000000000000000}};  // negativ value
  s21_decimal value_12 = {
      {2147483649, 0, 2147483647,
       0b10000000000000000000000000000000}};  // negativ value
  res = s21_is_less(value_11, value_12);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_is_lesster_or_equal_normal_value) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  int res = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(res, 1);

  s21_decimal value_3 = {{1, 0, 0, 0}};
  s21_decimal value_4 = {{0, 0, 0, 0}};
  res = s21_is_less_or_equal(value_3, value_4);
  ck_assert_int_eq(res, 0);

  s21_decimal value_5 = {{0, 0, 0, 0}};
  s21_decimal value_6 = {{1, 0, 0, 0}};
  res = s21_is_less_or_equal(value_5, value_6);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_is_lesster_or_equal_scale_value) {
  s21_decimal value_1 = {
      {2147483647, 0, 0, 0b00000000000000110000000000000000}};  // scale 3
  s21_decimal value_2 = {
      {2147483647, 0, 0, 0b00000000000000000000000000000000}};  // scale 0
  int res = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(res, 1);

  s21_decimal value_3 = {
      {325423523, 0, 0, 0b00000000000000000000000000000000}};  // scale 0
  s21_decimal value_4 = {
      {325423523, 0, 0, 0b00000000000000110000000000000000}};  // scale 3
  res = s21_is_less_or_equal(value_3, value_4);
  ck_assert_int_eq(res, 0);

  s21_decimal value_5 = {
      {2147483647, 0, 2147483647, 0b00000000000000110000000000000000}};
  s21_decimal value_6 = {
      {2147483647, 0, 2147483647, 0b00000000000000110000000000000000}};
  res = s21_is_less_or_equal(value_5, value_6);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_is_lesster_or_equal_negative_value_for_scale_and_normal) {
  s21_decimal value_1 = {
      {2147483647, 0, 0, 0b10000000000000110000000000000000}};  // scale 3
  s21_decimal value_2 = {
      {2147483647, 0, 0,
       0b10000000000000000000000000000000}};  // negativ value scale 0
  int res = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(res, 0);

  s21_decimal value_3 = {
      {325423523, 0, 0, 0b00000000000000000000000000000000}};  // scale 0
  s21_decimal value_4 = {
      {325423523, 0, 0,
       0b10000000000000110000000000000000}};  // negativ value scale 3
  res = s21_is_less_or_equal(value_3, value_4);
  ck_assert_int_eq(res, 0);

  s21_decimal value_5 = {
      {2147483647, 0, 2147483647,
       0b10000000000001000000000000000000}};  // negativ value scale 4
  s21_decimal value_6 = {
      {2147483647, 0, 2147483647,
       0b10000000000000110000000000000000}};  // negativ value scale 3
  res = s21_is_less_or_equal(value_5, value_6);
  ck_assert_int_eq(res, 0);

  s21_decimal value_7 = {
      {2147483647, 0, 2147483647,
       0b10000000000000110000000000000000}};  // negativ value scale 4
  s21_decimal value_8 = {
      {2147483647, 0, 2147483647,
       0b10000000000001000000000000000000}};  // negativ value scale 3
  res = s21_is_less_or_equal(value_7, value_8);
  ck_assert_int_eq(res, 1);

  s21_decimal value_9 = {
      {2147483649, 0, 2147483647,
       0b10000000000000000000000000000000}};  // negativ value
  s21_decimal value_10 = {
      {2147483647, 0, 2147483647,
       0b10000000000000000000000000000000}};  // negativ value
  res = s21_is_less_or_equal(value_9, value_10);
  ck_assert_int_eq(res, 1);

  s21_decimal value_11 = {
      {2147483647, 0, 2147483647,
       0b10000000000000110000000000000000}};  // negativ value
  s21_decimal value_12 = {
      {2147483647, 0, 2147483647,
       0b10000000000000110000000000000000}};  // negativ value
  res = s21_is_less_or_equal(value_11, value_12);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_is_greater_normal_value) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  int res = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(res, 0);

  s21_decimal value_3 = {{1, 0, 0, 0}};
  s21_decimal value_4 = {{0, 0, 0, 0}};
  res = s21_is_greater(value_3, value_4);
  ck_assert_int_eq(res, 1);

  s21_decimal value_5 = {{0, 0, 0, 0}};
  s21_decimal value_6 = {{1, 0, 0, 0}};
  res = s21_is_greater(value_5, value_6);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_is_greater_scale_value) {
  s21_decimal value_1 = {
      {2147483647, 0, 0, 0b00000000000000110000000000000000}};  // scale 3
  s21_decimal value_2 = {
      {2147483647, 0, 0, 0b00000000000000000000000000000000}};  // scale 0
  int res = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(res, 0);

  s21_decimal value_3 = {
      {325423523, 0, 0, 0b00000000000000000000000000000000}};  // scale 0
  s21_decimal value_4 = {
      {325423523, 0, 0, 0b00000000000000110000000000000000}};  // scale 3
  res = s21_is_greater(value_3, value_4);
  ck_assert_int_eq(res, 1);

  s21_decimal value_5 = {
      {2147483647, 0, 2147483647, 0b00000000000000000000000000000000}};
  s21_decimal value_6 = {
      {2147483647, 0, 2147483647, 0b00000000000000110000000000000000}};
  res = s21_is_greater(value_5, value_6);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_is_greater_negative_value_for_scale_and_normal) {
  s21_decimal value_1 = {
      {2147483647, 0, 0, 0b10000000000000110000000000000000}};  // scale 3
  s21_decimal value_2 = {
      {2147483647, 0, 0,
       0b10000000000000000000000000000000}};  // negativ value scale 0
  int res = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(res, 1);

  s21_decimal value_3 = {
      {325423523, 0, 0, 0b00000000000000000000000000000000}};  // scale 0
  s21_decimal value_4 = {
      {325423523, 0, 0,
       0b10000000000000110000000000000000}};  // negativ value scale 3
  res = s21_is_greater(value_3, value_4);
  ck_assert_int_eq(res, 1);

  s21_decimal value_5 = {
      {2147483647, 0, 2147483647,
       0b10000000000001000000000000000000}};  // negativ value scale 4
  s21_decimal value_6 = {
      {2147483647, 0, 2147483647,
       0b10000000000000110000000000000000}};  // negativ value scale 3
  res = s21_is_greater(value_5, value_6);
  ck_assert_int_eq(res, 1);

  s21_decimal value_7 = {
      {2147483647, 0, 2147483647,
       0b10000000000000110000000000000000}};  // negativ value scale 4
  s21_decimal value_8 = {
      {2147483647, 0, 2147483647,
       0b10000000000001000000000000000000}};  // negativ value scale 3
  res = s21_is_greater(value_7, value_8);
  ck_assert_int_eq(res, 0);

  s21_decimal value_9 = {
      {2147483649, 0, 2147483647,
       0b10000000000000000000000000000000}};  // negativ value
  s21_decimal value_10 = {
      {2147483647, 0, 2147483647,
       0b10000000000000000000000000000000}};  // negativ value
  res = s21_is_greater(value_9, value_10);
  ck_assert_int_eq(res, 0);

  s21_decimal value_11 = {
      {2147483647, 0, 2147483647,
       0b10000000000000000000000000000000}};  // negativ value
  s21_decimal value_12 = {
      {2147483649, 0, 2147483647,
       0b10000000000000000000000000000000}};  // negativ value
  res = s21_is_greater(value_11, value_12);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_is_greater_or_equal_normal_value) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  int res = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(res, 1);

  s21_decimal value_3 = {{1, 0, 0, 0}};
  s21_decimal value_4 = {{0, 0, 0, 0}};
  res = s21_is_greater_or_equal(value_3, value_4);
  ck_assert_int_eq(res, 1);

  s21_decimal value_5 = {{0, 0, 0, 0}};
  s21_decimal value_6 = {{1, 0, 0, 0}};
  res = s21_is_greater_or_equal(value_5, value_6);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_is_greater_or_equal_scale_value) {
  s21_decimal value_1 = {
      {2147483647, 0, 0, 0b00000000000000110000000000000000}};  // scale 3
  s21_decimal value_2 = {
      {2147483647, 0, 0, 0b00000000000000000000000000000000}};  // scale 0
  int res = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(res, 0);

  s21_decimal value_3 = {
      {325423523, 0, 0, 0b00000000000000000000000000000000}};  // scale 0
  s21_decimal value_4 = {
      {325423523, 0, 0, 0b00000000000000110000000000000000}};  // scale 3
  res = s21_is_greater_or_equal(value_3, value_4);
  ck_assert_int_eq(res, 1);

  s21_decimal value_5 = {
      {2147483647, 0, 2147483647, 0b00000000000000110000000000000000}};
  s21_decimal value_6 = {
      {2147483647, 0, 2147483647, 0b00000000000000110000000000000000}};
  res = s21_is_greater_or_equal(value_5, value_6);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_is_greater_or_equal_negative_value_for_scale_and_normal) {
  s21_decimal value_1 = {
      {2147483647, 0, 0, 0b10000000000000110000000000000000}};  // scale 3
  s21_decimal value_2 = {
      {2147483647, 0, 0,
       0b10000000000000000000000000000000}};  // negativ value scale 0
  int res = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(res, 1);

  s21_decimal value_3 = {
      {325423523, 0, 0, 0b00000000000000000000000000000000}};  // scale 0
  s21_decimal value_4 = {
      {325423523, 0, 0,
       0b10000000000000110000000000000000}};  // negativ value scale 3
  res = s21_is_greater_or_equal(value_3, value_4);
  ck_assert_int_eq(res, 1);

  s21_decimal value_5 = {
      {2147483647, 0, 2147483647,
       0b10000000000001000000000000000000}};  // negativ value scale 4
  s21_decimal value_6 = {
      {2147483647, 0, 2147483647,
       0b10000000000000110000000000000000}};  // negativ value scale 3
  res = s21_is_greater_or_equal(value_5, value_6);
  ck_assert_int_eq(res, 1);

  s21_decimal value_7 = {
      {2147483647, 0, 2147483647,
       0b10000000000000110000000000000000}};  // negativ value scale 6
  s21_decimal value_8 = {
      {2147483647, 0, 2147483647,
       0b10000000000001000000000000000000}};  // negativ value scale 4
  res = s21_is_greater_or_equal(value_7, value_8);
  ck_assert_int_eq(res, 0);

  s21_decimal value_9 = {
      {2147483649, 0, 2147483647,
       0b10000000000000000000000000000000}};  // negativ value
  s21_decimal value_10 = {
      {2147483647, 0, 2147483647,
       0b10000000000000000000000000000000}};  // negativ value
  res = s21_is_greater_or_equal(value_9, value_10);
  ck_assert_int_eq(res, 0);

  s21_decimal value_11 = {
      {2147483647, 0, 2147483647,
       0b10000000000000110000000000000000}};  // negativ value
  s21_decimal value_12 = {
      {2147483647, 0, 2147483647,
       0b10000000000000110000000000000000}};  // negativ value
  res = s21_is_greater_or_equal(value_11, value_12);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_is_equal_normal) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  int res = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(res, 1);

  s21_decimal value_3 = {{1, 0, 0, 0}};
  s21_decimal value_4 = {{0, 0, 0, 0}};
  res = s21_is_equal(value_3, value_4);
  ck_assert_int_eq(res, 0);

  s21_decimal value_5 = {{0, 0, 0, 0b10000000000000110000000000000000}};
  s21_decimal value_6 = {{0, 0, 0, 0b10000000000000110000000000000000}};
  res = s21_is_equal(value_5, value_6);
  ck_assert_int_eq(res, 1);

  s21_decimal value_7 = {
      {2147483647, 0, 0, 0b00000000000000110000000000000000}};
  s21_decimal value_8 = {
      {2147483647, 0, 0, 0b00000000000000110000000000000000}};
  res = s21_is_equal(value_7, value_8);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_is_not_equal_normal) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  int res = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(res, 0);

  s21_decimal value_3 = {{1, 0, 0, 0}};
  s21_decimal value_4 = {{0, 0, 0, 0}};
  res = s21_is_not_equal(value_3, value_4);
  ck_assert_int_eq(res, 1);

  s21_decimal value_5 = {{0, 0, 0, 0b10000000000000110000000000000000}};
  s21_decimal value_6 = {{0, 0, 0, 0b10000000000000110000000000000000}};
  res = s21_is_not_equal(value_5, value_6);
  ck_assert_int_eq(res, 0);

  s21_decimal value_7 = {
      {2147483647, 0, 0, 0b00000000000000110000000000000000}};
  s21_decimal value_8 = {
      {2147483647, 0, 0, 0b00000000000000110000000000000000}};
  res = s21_is_not_equal(value_7, value_8);
  ck_assert_int_eq(res, 0);
}
END_TEST

// CONVERTOVKA:
START_TEST(s21_from_int_to_decimal_test) {
  // MAXOVKA
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal res = {{2147483647, 0, 0, 0}};
  int numbovka_1 = 2147483647;
  s21_from_int_to_decimal(numbovka_1, &value_1);
  ck_assert_int_eq(value_1.bits[0], res.bits[0]);
  ck_assert_int_eq(value_1.bits[1], res.bits[1]);
  ck_assert_int_eq(value_1.bits[2], res.bits[2]);
  ck_assert_int_eq(value_1.bits[3], res.bits[3]);
  // MINOVKA
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal res2 = {{2147483647, 0, 0, 0b10000000000000000000000000000000}};
  int numbovka_2 = -2147483647;
  s21_from_int_to_decimal(numbovka_2, &value_2);
  ck_assert_int_eq(value_2.bits[0], res2.bits[0]);
  ck_assert_int_eq(value_2.bits[1], res2.bits[1]);
  ck_assert_int_eq(value_2.bits[2], res2.bits[2]);
  ck_assert_int_eq(value_2.bits[3], res2.bits[3]);
  // NORMALOVKA
  s21_decimal value_3 = {{0, 0, 0, 0}};
  s21_decimal res3 = {{21, 0, 0, 0}};
  int numbovka_3 = 21;
  s21_from_int_to_decimal(numbovka_3, &value_3);
  ck_assert_int_eq(value_3.bits[0], res3.bits[0]);
  ck_assert_int_eq(value_3.bits[1], res3.bits[1]);
  ck_assert_int_eq(value_3.bits[2], res3.bits[2]);
  ck_assert_int_eq(value_3.bits[3], res3.bits[3]);
}
END_TEST

START_TEST(s21_from_int_to_decimal_returnovka) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  int numbovka_1 = 2147483647;
  ck_assert_int_eq(0, s21_from_int_to_decimal(numbovka_1, &value_1));
}
END_TEST

START_TEST(s21_from_decimal_to_int_test) {
  // MAXOVKA
  s21_decimal value_1 = {{2147483647, 0, 0, 0}};
  int res = 2147483647;
  int numbovka_1 = 0;
  s21_from_decimal_to_int(value_1, &numbovka_1);
  ck_assert_int_eq(res, numbovka_1);
  // MINOVKA
  s21_decimal value_2 = {
      {2147483647, 0, 0, 0b10000000000000000000000000000000}};
  int res2 = -2147483647;
  int numbovka_2 = 0;
  s21_from_decimal_to_int(value_2, &numbovka_2);
  ck_assert_int_eq(res2, numbovka_2);
  // NORMALOVKA
  s21_decimal value_3 = {{21, 0, 0, 0}};
  int res3 = 21;
  int numbovka_3 = 0;
  s21_from_decimal_to_int(value_3, &numbovka_3);
  ck_assert_int_eq(res3, numbovka_3);
}
END_TEST

START_TEST(s21_from_decimal_to_int_returnovka) {
  s21_decimal value_1 = {{2147483647, 0, 0, 0}};
  int numbovka_1 = 0;
  ck_assert_int_eq(0, s21_from_decimal_to_int(value_1, &numbovka_1));
}
END_TEST

START_TEST(s21_from_float_to_decimal_test) {
  // MAXOVKA
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal res = {{2147489, 0, 0, 0b00000000000000010000000000000000}};
  float numbovka_1 = 214748.9;
  s21_from_float_to_decimal(numbovka_1, &value_1);
  ck_assert_int_eq(value_1.bits[0], res.bits[0]);
  ck_assert_int_eq(value_1.bits[1], res.bits[1]);
  ck_assert_int_eq(value_1.bits[2], res.bits[2]);
  ck_assert_int_eq(value_1.bits[3], res.bits[3]);
  // MINOVKA
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal res2 = {
      {2147489, 0, 0, 0b10000000000000010000000000000000}};  // 1
  float numbovka_2 = -214748.9;
  s21_from_float_to_decimal(numbovka_2, &value_2);
  ck_assert_int_eq(value_2.bits[0], res2.bits[0]);
  ck_assert_int_eq(value_2.bits[1], res2.bits[1]);
  ck_assert_int_eq(value_2.bits[2], res2.bits[2]);
  ck_assert_int_eq(value_2.bits[3], res2.bits[3]);
  // NORMALOVKA
  s21_decimal value_3 = {{0, 0, 0, 0}};
  s21_decimal res3 = {{213453, 0, 0, 0b00000000000001000000000000000000}};  // 4
  float numbovka_3 = 21.3453;
  s21_from_float_to_decimal(numbovka_3, &value_3);
  ck_assert_int_eq(value_3.bits[0], res3.bits[0]);
  ck_assert_int_eq(value_3.bits[1], res3.bits[1]);
  ck_assert_int_eq(value_3.bits[2], res3.bits[2]);
  ck_assert_int_eq(value_3.bits[3], res3.bits[3]);
}
END_TEST

START_TEST(s21_from_float_to_decimal_returnovka) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  float numbovka_1 = 21474836.7;
  ck_assert_int_eq(0, s21_from_float_to_decimal(numbovka_1, &value_1));
}
END_TEST

START_TEST(s21_from_decimal_to_float_test) {
  // MAXOVKA
  s21_decimal value_1 = {{2147489, 0, 0, 0b00000000000000010000000000000000}};
  float res = 214748.9;
  float numbovka_1 = 0;
  s21_from_decimal_to_float(value_1, &numbovka_1);
  ck_assert_float_eq(res, numbovka_1);
  // MINOVKA
  s21_decimal value_2 = {
      {2147489, 0, 0, 0b10000000000000010000000000000000}};  // 1
  float res2 = -214748.9;
  float numbovka_2 = 0;
  s21_from_decimal_to_float(value_2, &numbovka_2);
  ck_assert_float_eq(res2, numbovka_2);
  // NORMALOVKA
  s21_decimal value_3 = {
      {213453, 0, 0, 0b00000000000001000000000000000000}};  // 4
  float res3 = 21.3453;
  float numbovka_3 = 0;
  s21_from_decimal_to_float(value_3, &numbovka_3);
  ck_assert_float_eq(res3, numbovka_3);
}
END_TEST

START_TEST(s21_from_decimal_to_float_returnovka) {
  s21_decimal value_1 = {{213453, 0, 0, 0b00000000000001000000000000000000}};
  float numbovka_1 = 0;
  ck_assert_int_eq(0, s21_from_decimal_to_float(value_1, &numbovka_1));
}
END_TEST

START_TEST(s21_add_normaldi) {
  s21_decimal value_1 = {{2, 0, 0, 0}};
  s21_decimal value_2 = {{5, 0, 0, 0}};
  s21_decimal value_3 = {{0, 0, 0, 0}};
  s21_decimal reza = {{7, 0, 0, 0}};
  s21_add(value_1, value_2, &value_3);
  ck_assert_int_eq(value_3.bits[0], reza.bits[0]);
  ck_assert_int_eq(value_3.bits[1], reza.bits[1]);
  ck_assert_int_eq(value_3.bits[2], reza.bits[2]);
  ck_assert_int_eq(value_3.bits[3], reza.bits[3]);

  s21_decimal value_4 = {{2147483647, 0, 0, 0}};
  s21_decimal value_5 = {{2147483647, 0, 0, 0}};
  s21_decimal value_6 = {{0, 0, 0, 0}};
  s21_decimal reza1 = {{2147483647, 0, 0, 0}};
  s21_add(value_4, value_5, &value_6);
  ck_assert_int_eq(value_4.bits[0], reza1.bits[0]);
  ck_assert_int_eq(value_4.bits[1], reza1.bits[1]);
  ck_assert_int_eq(value_4.bits[2], reza1.bits[2]);
  ck_assert_int_eq(value_4.bits[3], reza1.bits[3]);
}
END_TEST

START_TEST(s21_add_nega) {
  s21_decimal value_1 = {{10000, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal value_2 = {{5000, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal value_3 = {{0, 0, 0, 0}};
  s21_decimal reza = {{5000, 0, 0, 0}};
  s21_add(value_1, value_2, &value_3);
  ck_assert_int_eq(value_3.bits[0], reza.bits[0]);
  ck_assert_int_eq(value_3.bits[1], reza.bits[1]);
  ck_assert_int_eq(value_3.bits[2], reza.bits[2]);
  ck_assert_int_eq(value_3.bits[3], reza.bits[3]);

  s21_decimal value_4 = {{5000, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal value_5 = {{10000, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal value_6 = {{0, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal reza1 = {{5000, 0, 0, 0b10000000000000000000000000000000}};
  s21_add(value_4, value_5, &value_6);
  ck_assert_int_eq(value_6.bits[0], reza1.bits[0]);
  ck_assert_int_eq(value_6.bits[1], reza1.bits[1]);
  ck_assert_int_eq(value_6.bits[2], reza1.bits[2]);
  ck_assert_int_eq(value_6.bits[3], reza1.bits[3]);
}
END_TEST

START_TEST(s21_add_nega1) {
  s21_decimal value_1 = {{10000, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal value_2 = {{5000, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal value_3 = {{0, 0, 0, 0}};
  s21_decimal reza = {{5000, 0, 0, 0b10000000000000000000000000000000}};
  s21_add(value_1, value_2, &value_3);
  ck_assert_int_eq(value_3.bits[0], reza.bits[0]);
  ck_assert_int_eq(value_3.bits[1], reza.bits[1]);
  ck_assert_int_eq(value_3.bits[2], reza.bits[2]);
  ck_assert_int_eq(value_3.bits[3], reza.bits[3]);

  s21_decimal value_4 = {{5000, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal value_5 = {{10000, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal value_6 = {{0, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal reza1 = {{5000, 0, 0, 0b00000000000000000000000000000000}};
  s21_add(value_4, value_5, &value_6);
  ck_assert_int_eq(value_6.bits[0], reza1.bits[0]);
  ck_assert_int_eq(value_6.bits[1], reza1.bits[1]);
  ck_assert_int_eq(value_6.bits[2], reza1.bits[2]);
  ck_assert_int_eq(value_6.bits[3], reza1.bits[3]);

  s21_decimal value_7 = {{5000, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal value_8 = {{10000, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal value_9 = {{0, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal reza2 = {{15000, 0, 0, 0b10000000000000000000000000000000}};
  s21_add(value_7, value_8, &value_9);
  ck_assert_int_eq(value_9.bits[0], reza2.bits[0]);
  ck_assert_int_eq(value_9.bits[1], reza2.bits[1]);
  ck_assert_int_eq(value_9.bits[2], reza2.bits[2]);
  ck_assert_int_eq(value_9.bits[3], reza2.bits[3]);
}
END_TEST

START_TEST(s21_add_normaldi_stepsoid) {
  s21_decimal value_1 = {{2, 0, 0, 0b00000000000001000000000000000000}};  // 4
  s21_decimal value_2 = {{5, 0, 0, 0b00000000000001010000000000000000}};
  s21_decimal value_3 = {{0, 0, 0, 0}};
  s21_decimal reza = {{25, 0, 0, 0b00000000000001010000000000000000}};
  s21_add(value_1, value_2, &value_3);
  ck_assert_int_eq(value_3.bits[0], reza.bits[0]);
  ck_assert_int_eq(value_3.bits[1], reza.bits[1]);
  ck_assert_int_eq(value_3.bits[2], reza.bits[2]);
  ck_assert_int_eq(value_3.bits[3], reza.bits[3]);
}
END_TEST

START_TEST(s21_sub_normaldi) {
  s21_decimal value_1 = {{10, 0, 0, 0}};
  s21_decimal value_2 = {{5, 0, 0, 0}};
  s21_decimal value_3 = {{0, 0, 0, 0}};
  s21_decimal reza = {{5, 0, 0, 0}};
  s21_sub(value_1, value_2, &value_3);
  ck_assert_int_eq(value_3.bits[0], reza.bits[0]);
  ck_assert_int_eq(value_3.bits[1], reza.bits[1]);
  ck_assert_int_eq(value_3.bits[2], reza.bits[2]);
  ck_assert_int_eq(value_3.bits[3], reza.bits[3]);

  s21_decimal value_4 = {{2147483647, 0, 0, 0}};
  s21_decimal value_5 = {{2147483647, 0, 0, 0}};
  s21_decimal value_6 = {{0, 0, 0, 0}};
  s21_decimal reza1 = {{0, 0, 0, 0}};
  s21_sub(value_4, value_5, &value_6);
  ck_assert_int_eq(value_6.bits[0], reza1.bits[0]);
  ck_assert_int_eq(value_6.bits[1], reza1.bits[1]);
  ck_assert_int_eq(value_6.bits[2], reza1.bits[2]);
  ck_assert_int_eq(value_6.bits[3], reza1.bits[3]);
}
END_TEST

START_TEST(s21_sub_nega) {
  s21_decimal value_1 = {{10000, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal value_2 = {{5000, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal value_3 = {{0, 0, 0, 0}};
  s21_decimal reza = {{15000, 0, 0, 0}};
  s21_sub(value_1, value_2, &value_3);
  ck_assert_int_eq(value_3.bits[0], reza.bits[0]);
  ck_assert_int_eq(value_3.bits[1], reza.bits[1]);
  ck_assert_int_eq(value_3.bits[2], reza.bits[2]);
  ck_assert_int_eq(value_3.bits[3], reza.bits[3]);

  s21_decimal value_4 = {{5000, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal value_5 = {{10000, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal value_6 = {{0, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal reza1 = {{15000, 0, 0, 0b00000000000000000000000000000000}};
  s21_sub(value_4, value_5, &value_6);
  ck_assert_int_eq(value_6.bits[0], reza1.bits[0]);
  ck_assert_int_eq(value_6.bits[1], reza1.bits[1]);
  ck_assert_int_eq(value_6.bits[2], reza1.bits[2]);
  ck_assert_int_eq(value_6.bits[3], reza1.bits[3]);
}
END_TEST

START_TEST(s21_sub_nega1) {
  s21_decimal value_1 = {{10000, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal value_2 = {{5000, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal value_3 = {{0, 0, 0, 0}};
  s21_decimal reza = {{15000, 0, 0, 0b10000000000000000000000000000000}};
  s21_sub(value_1, value_2, &value_3);
  ck_assert_int_eq(value_3.bits[0], reza.bits[0]);
  ck_assert_int_eq(value_3.bits[1], reza.bits[1]);
  ck_assert_int_eq(value_3.bits[2], reza.bits[2]);
  ck_assert_int_eq(value_3.bits[3], reza.bits[3]);

  s21_decimal value_4 = {{5000, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal value_5 = {{10000, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal value_6 = {{0, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal reza1 = {{15000, 0, 0, 0b10000000000000000000000000000000}};
  s21_sub(value_4, value_5, &value_6);
  ck_assert_int_eq(value_6.bits[0], reza1.bits[0]);
  ck_assert_int_eq(value_6.bits[1], reza1.bits[1]);
  ck_assert_int_eq(value_6.bits[2], reza1.bits[2]);
  ck_assert_int_eq(value_6.bits[3], reza1.bits[3]);

  s21_decimal value_7 = {{5000, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal value_8 = {{10000, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal value_9 = {{0, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal reza2 = {{5000, 0, 0, 0b00000000000000000000000000000000}};
  s21_sub(value_7, value_8, &value_9);
  ck_assert_int_eq(value_9.bits[0], reza2.bits[0]);
  ck_assert_int_eq(value_9.bits[1], reza2.bits[1]);
  ck_assert_int_eq(value_9.bits[2], reza2.bits[2]);
  ck_assert_int_eq(value_9.bits[3], reza2.bits[3]);

  s21_decimal value_10 = {{10000, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal value_11 = {{5000, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal value_12 = {{0, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal reza3 = {{5000, 0, 0, 0b10000000000000000000000000000000}};
  s21_sub(value_10, value_11, &value_12);
  ck_assert_int_eq(value_12.bits[0], reza3.bits[0]);
  ck_assert_int_eq(value_12.bits[1], reza3.bits[1]);
  ck_assert_int_eq(value_12.bits[2], reza3.bits[2]);
  ck_assert_int_eq(value_12.bits[3], reza3.bits[3]);

  s21_decimal value_13 = {{5000, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal value_14 = {{5000, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal value_15 = {{0, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal reza4 = {{0, 0, 0, 0b00000000000000000000000000000000}};
  s21_sub(value_13, value_14, &value_15);
  ck_assert_int_eq(value_15.bits[0], reza4.bits[0]);
  ck_assert_int_eq(value_15.bits[1], reza4.bits[1]);
  ck_assert_int_eq(value_15.bits[2], reza4.bits[2]);
  ck_assert_int_eq(value_15.bits[3], reza4.bits[3]);
}
END_TEST

START_TEST(s21_mul_normaldi) {
  s21_decimal value_1 = {{10, 0, 0, 0}};
  s21_decimal value_2 = {{5, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal value_3 = {{0, 0, 0, 0}};
  s21_decimal reza = {{50, 0, 0, 0b10000000000000000000000000000000}};
  s21_mul(value_1, value_2, &value_3);
  ck_assert_int_eq(value_3.bits[0], reza.bits[0]);
  ck_assert_int_eq(value_3.bits[1], reza.bits[1]);
  ck_assert_int_eq(value_3.bits[2], reza.bits[2]);
  ck_assert_int_eq(value_3.bits[3], reza.bits[3]);

  s21_decimal value_4 = {{16, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal value_5 = {{4, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal value_6 = {{0, 0, 0, 0}};
  s21_decimal reza1 = {{64, 0, 0, 0b00000000000000000000000000000000}};
  s21_mul(value_4, value_5, &value_6);
  ck_assert_int_eq(value_6.bits[0], reza1.bits[0]);
  ck_assert_int_eq(value_6.bits[1], reza1.bits[1]);
  ck_assert_int_eq(value_6.bits[2], reza1.bits[2]);
  ck_assert_int_eq(value_6.bits[3], reza1.bits[3]);
}
END_TEST

START_TEST(s21_div_normaldi) {
  s21_decimal value_1 = {{10, 0, 0, 0}};
  s21_decimal value_2 = {{5, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal value_3 = {{0, 0, 0, 0}};
  s21_decimal reza = {{2, 0, 0, 0b00000000000000000000000000000000}};
  s21_div(value_1, value_2, &value_3);
  ck_assert_int_eq(value_3.bits[0], reza.bits[0]);
  ck_assert_int_eq(value_3.bits[1], reza.bits[1]);
  ck_assert_int_eq(value_3.bits[2], reza.bits[2]);
  ck_assert_int_eq(value_3.bits[3], reza.bits[3]);

  s21_decimal value_4 = {{16, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal value_5 = {{4, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal value_6 = {{0, 0, 0, 0}};
  s21_decimal reza1 = {{4, 0, 0, 0b10000000000000000000000000000000}};
  s21_div(value_4, value_5, &value_6);
  ck_assert_int_eq(value_6.bits[0], reza1.bits[0]);
  ck_assert_int_eq(value_6.bits[1], reza1.bits[1]);
  ck_assert_int_eq(value_6.bits[2], reza1.bits[2]);
  ck_assert_int_eq(value_6.bits[3], reza1.bits[3]);

  s21_decimal value_7 = {{16, 0, 0, 0b00000000000000110000000000000000}};
  s21_decimal value_8 = {{4, 0, 0, 0b00000000000001010000000000000000}};
  s21_decimal value_9 = {{0, 0, 0, 0}};
  s21_decimal reza2 = {{400, 0, 0, 0}};
  s21_div(value_7, value_8, &value_9);
  ck_assert_int_eq(value_9.bits[0], reza2.bits[0]);
  ck_assert_int_eq(value_9.bits[1], reza2.bits[1]);
  ck_assert_int_eq(value_9.bits[2], reza2.bits[2]);
  ck_assert_int_eq(value_9.bits[3], reza2.bits[3]);
}
END_TEST

START_TEST(s21_negate_test) {
  s21_decimal value_1 = {{10, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal value_2 = {{0, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal reza = {{10, 0, 0, 0b00000000000000000000000000000000}};
  s21_negate(value_1, &value_2);
  ck_assert_int_eq(value_2.bits[0], reza.bits[0]);
  ck_assert_int_eq(value_2.bits[1], reza.bits[1]);
  ck_assert_int_eq(value_2.bits[2], reza.bits[2]);
  ck_assert_int_eq(value_2.bits[3], reza.bits[3]);

  s21_decimal value_3 = {{10, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal value_4 = {{0, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal reza2 = {{10, 0, 0, 0b10000000000000000000000000000000}};
  s21_negate(value_3, &value_4);
  ck_assert_int_eq(value_4.bits[0], reza2.bits[0]);
  ck_assert_int_eq(value_4.bits[1], reza2.bits[1]);
  ck_assert_int_eq(value_4.bits[2], reza2.bits[2]);
  ck_assert_int_eq(value_4.bits[3], reza2.bits[3]);
}
END_TEST

START_TEST(s21_truncate_test) {
  s21_decimal value_1 = {
      {10000, 0, 0, 0b00000000000001000000000000000000}};  // 4
  s21_decimal value_2 = {{0, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal reza = {{1, 0, 0, 0b00000000000000000000000000000000}};
  s21_truncate(value_1, &value_2);
  ck_assert_int_eq(value_2.bits[0], reza.bits[0]);
  ck_assert_int_eq(value_2.bits[1], reza.bits[1]);
  ck_assert_int_eq(value_2.bits[2], reza.bits[2]);
  ck_assert_int_eq(value_2.bits[3], reza.bits[3]);

  s21_decimal value_3 = {{1024, 0, 0, 0b10000000000000010000000000000000}};
  s21_decimal value_4 = {{0, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal reza2 = {{102, 0, 0, 0b10000000000000000000000000000000}};
  s21_truncate(value_3, &value_4);
  ck_assert_int_eq(value_4.bits[0], reza2.bits[0]);
  ck_assert_int_eq(value_4.bits[1], reza2.bits[1]);
  ck_assert_int_eq(value_4.bits[2], reza2.bits[2]);
  ck_assert_int_eq(value_4.bits[3], reza2.bits[3]);
}
END_TEST

START_TEST(s21_floor_test) {
  s21_decimal value_1 = {{155, 0, 0, 0b00000000000000100000000000000000}};  // 2
  s21_decimal value_2 = {{0, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal reza = {{1, 0, 0, 0b00000000000000000000000000000000}};
  s21_floor(value_1, &value_2);
  ck_assert_int_eq(value_2.bits[0], reza.bits[0]);
  ck_assert_int_eq(value_2.bits[1], reza.bits[1]);
  ck_assert_int_eq(value_2.bits[2], reza.bits[2]);
  ck_assert_int_eq(value_2.bits[3], reza.bits[3]);

  s21_decimal value_3 = {{1024, 0, 0, 0b00000000000000010000000000000000}};
  s21_decimal value_4 = {{0, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal reza2 = {{102, 0, 0, 0b00000000000000000000000000000000}};
  s21_floor(value_3, &value_4);
  ck_assert_int_eq(value_4.bits[0], reza2.bits[0]);
  ck_assert_int_eq(value_4.bits[1], reza2.bits[1]);
  ck_assert_int_eq(value_4.bits[2], reza2.bits[2]);
  ck_assert_int_eq(value_4.bits[3], reza2.bits[3]);
}
END_TEST

START_TEST(s21_round_test) {
  s21_decimal value_1 = {{160, 0, 0, 0b00000000000000010000000000000000}};  // 1
  s21_decimal value_2 = {{0, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal reza = {{16, 0, 0, 0b00000000000000000000000000000000}};
  s21_round(value_1, &value_2);
  ck_assert_int_eq(value_2.bits[0], reza.bits[0]);
  ck_assert_int_eq(value_2.bits[1], reza.bits[1]);
  ck_assert_int_eq(value_2.bits[2], reza.bits[2]);
  ck_assert_int_eq(value_2.bits[3], reza.bits[3]);

  s21_decimal value_3 = {{13, 0, 0, 0b00000000000000010000000000000000}};
  s21_decimal value_4 = {{0, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal reza2 = {{1, 0, 0, 0b00000000000000000000000000000000}};
  s21_round(value_3, &value_4);
  ck_assert_int_eq(value_4.bits[0], reza2.bits[0]);
  ck_assert_int_eq(value_4.bits[1], reza2.bits[1]);
  ck_assert_int_eq(value_4.bits[2], reza2.bits[2]);
  ck_assert_int_eq(value_4.bits[3], reza2.bits[3]);

  s21_decimal value_5 = {{15, 0, 0, 0b00000000000000010000000000000000}};
  s21_decimal value_6 = {{0, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal reza3 = {{2, 0, 0, 0b00000000000000000000000000000000}};
  s21_round(value_5, &value_6);
  ck_assert_int_eq(value_6.bits[0], reza3.bits[0]);
  ck_assert_int_eq(value_6.bits[1], reza3.bits[1]);
  ck_assert_int_eq(value_6.bits[2], reza3.bits[2]);
  ck_assert_int_eq(value_6.bits[3], reza3.bits[3]);
}
END_TEST

int main() {
  Suite *s1 = suite_create(
      "s21_decimal");  // создаем набор тестов s1 с названием  s21_decimal
  TCase *tc1_1 = tcase_create(
      "s21_decimal");  // создаем тестовый случай tc1_1 c названием s21_decimal
  SRunner *sr = srunner_create(
      s1);  // создаем отчет о запуске, связывая его с набором тестров
  int nf;
  suite_add_tcase(s1, tc1_1);  // добавляем тестовый случай к набору тестов

  tcase_add_test(
      tc1_1, s21_is_lesster_defolt_value);  // добавляем функцию в набор тестов
  tcase_add_test(tc1_1, s21_is_lesster_scale_value);
  tcase_add_test(tc1_1, s21_is_lesster_negative_value_for_scale_and_normal);

  tcase_add_test(tc1_1, s21_is_lesster_or_equal_normal_value);
  tcase_add_test(tc1_1, s21_is_lesster_or_equal_scale_value);
  tcase_add_test(tc1_1,
                 s21_is_lesster_or_equal_negative_value_for_scale_and_normal);

  tcase_add_test(tc1_1, s21_is_greater_normal_value);
  tcase_add_test(tc1_1, s21_is_greater_scale_value);
  tcase_add_test(tc1_1, s21_is_greater_negative_value_for_scale_and_normal);

  tcase_add_test(tc1_1, s21_is_greater_or_equal_normal_value);
  tcase_add_test(tc1_1, s21_is_greater_or_equal_scale_value);
  tcase_add_test(tc1_1,
                 s21_is_greater_or_equal_negative_value_for_scale_and_normal);

  tcase_add_test(tc1_1, s21_is_equal_normal);
  tcase_add_test(tc1_1, s21_is_not_equal_normal);
  // CONVERTOVKA:
  tcase_add_test(tc1_1, s21_from_int_to_decimal_test);
  tcase_add_test(tc1_1, s21_from_int_to_decimal_returnovka);
  tcase_add_test(tc1_1, s21_from_decimal_to_int_test);
  tcase_add_test(tc1_1, s21_from_decimal_to_int_returnovka);
  tcase_add_test(tc1_1, s21_from_float_to_decimal_test);
  tcase_add_test(tc1_1, s21_from_float_to_decimal_returnovka);
  tcase_add_test(tc1_1, s21_from_decimal_to_float_test);
  tcase_add_test(tc1_1, s21_from_decimal_to_float_returnovka);

  // ARITHMETICS:
  tcase_add_test(tc1_1, s21_add_normaldi);
  tcase_add_test(tc1_1, s21_add_nega);
  tcase_add_test(tc1_1, s21_add_nega1);
  tcase_add_test(tc1_1, s21_add_normaldi_stepsoid);

  tcase_add_test(tc1_1, s21_sub_normaldi);
  tcase_add_test(tc1_1, s21_sub_nega);
  tcase_add_test(tc1_1, s21_sub_nega1);

  tcase_add_test(tc1_1, s21_mul_normaldi);

  tcase_add_test(tc1_1, s21_div_normaldi);

  tcase_add_test(tc1_1, s21_negate_test);

  tcase_add_test(tc1_1, s21_truncate_test);

  tcase_add_test(tc1_1, s21_floor_test);

  tcase_add_test(tc1_1, s21_round_test);

  srunner_run_all(sr, CK_ENV);  //  запускает все тесты в наборе тестов с
                                //  использованием окружения CHECK.h
  nf = srunner_ntests_failed(
      sr);  // сохраянем колличество тестов, которые завершились
  srunner_free(sr);  // освобождаем память выделенную под структуру тестов

  return nf == 0 ? 0 : 1;
}
