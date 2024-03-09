CFLAGS = -c -Wall -Werror -Wextra -std=c11
LDFLAGS = -O2 -Wall -Werror -Wextra -std=c11
SOURCE = s21_*.c

all: clean s21_decimal.a test gcov_report

s21_decimal.a:
	gcc $(CFLAGS) $(SOURCE)
	ar rc s21_decimal.a s21_*.o
	ranlib s21_decimal.a

test: clean test.c s21_decimal.a
	gcc $(LDFLAGS) -o test test.c s21_decimal.a -lcheck
	./test

gcov_report: clean $(SOURCE)
	gcc --coverage $(SOURCE) test.c -o s21_test -lcheck
	./s21_test
	lcov -t "s21_test" -o s21_test.info -c -d .
	genhtml -o report s21_test.info
	open ./report/index.html
	rm -rf *.gcno *.gcda *.info s21_test

clang:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i *.c *.h
	rm -rf .clang-format

clang_review:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.c *.h
	rm -rf .clang-format

clean:
	rm -rf *.a *.o *.gcno *.gcda test *.info s21_test report
