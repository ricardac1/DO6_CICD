CC = gcc
CFLAGS = -c -Wall -Werror -Wextra

all : s21_grep

s21_grep : s21_grep.o
	$(CC) s21_grep.o -o ./s21_grep
s21_grep.o : s21_grep.c
	$(CC) $(CFLAGS) s21_grep.c -o s21_grep.o

rebuild : clean
	make

clean :
	rm *.o s21_grep

format_style:
	cp ../../materials/linters/.clang-format .
	clang-format -i *.c *.h
	rm .clang-format




