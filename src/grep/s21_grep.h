#ifndef S21_GRAP_H
#define S21_GRAP_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct FLAG {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  char pattern[1024];
  int lenPattern;
} flag;

void readFlag(int argc, char *argv[], flag *FLAG);
int readFile(char *path, regex_t *reg, flag *FLAG);
void outputLine(char *line, int N);
void output(int argc, char **argv, flag *FLAG);
void pattern(char *pattern, flag *FLAG);
void patternFlagF(char *filepath, flag *FLAG);
void printFlagO(char *line, char *path, int lineNumber, flag *FLAG,
                regex_t *reg);
void chFlag(char *path, int lineNumber, flag *FLAG);
#endif