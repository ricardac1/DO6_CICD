#ifndef S21_CAT_H
#define S21_CAT_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct FLAG {
  int b;
  int n;
  int e;
  int s;
  int t;
  int v;
} flag;

int readFile(char *argv[], flag *FLAG);
int ReadFlag(int argc, char *argv[], flag *FLAG);

#endif