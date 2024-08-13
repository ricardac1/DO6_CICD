CC = gcc
CFLAGS = -c -Wall -Werror -Wextra

all : s21_cat

s21_cat : s21_cat.o
	$(CC) s21_cat.o -o ./s21_cat
s21_cat.o : s21_cat.c
	$(CC) $(CFLAGS) s21_cat.c -o s21_cat.o

rebuild : clean
	make

clean : 
	rm *.o s21_cat

format_style:
	cp ../../materials/linters/.clang-format .
	clang-format -i *.c *.h
	rm .clang-format
