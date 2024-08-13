#include "s21_cat.h"

int main(int argc, char *argv[]) {
  flag FLAG = {0};

  ReadFlag(argc, argv, &FLAG);

  if (FLAG.b == 1) {
    FLAG.n = 0;
  }

  while (optind < argc) {
    readFile(argv, &FLAG);
    optind++;
  }
  return 0;
}

int ReadFlag(int argc, char *argv[], flag *FLAG) {
  int currentFlag = 0;
  int ret = 0;
  struct option longOpt[] = {

      {"number-nonblank", 0, NULL, 'b'},
      {"number", 0, NULL, 'n'},
      {"squeeze", 0, NULL, 's'},
      {NULL, 0, NULL, 0}};

  while ((currentFlag = getopt_long(argc, argv, "bevEnstT", longOpt, NULL)) !=
         -1) {
    switch (currentFlag) {
      case 'b':
        FLAG->b = 1;
        break;
      case 'e':
        FLAG->e = 1;
        FLAG->v = 1;
        break;
      case 'v':
        FLAG->v = 1;
        break;
      case 'E':
        FLAG->e = 1;
        break;
      case 'n':
        FLAG->n = 1;
        break;
      case 's':
        FLAG->s = 1;
        break;
      case 't':
        FLAG->t = 1;
        FLAG->v = 1;
        break;
      case 'T':
        FLAG->t = 1;
        break;

      default:
        ret = -1;
        break;
    }
  }
  return ret;
}

int readFile(char *argv[], flag *FLAG) {
  int ret = 0;
  int str = 1;
  int emptyStr = 0;
  int lastSym = '\n';

  FILE *file;
  file = fopen(argv[optind], "r");
  if (file != NULL) {
    while (1) {
      int curc = fgetc(file);
      if (curc == EOF) {
        break;
      }

      if (FLAG->s == 1 && curc == '\n' && lastSym == '\n') {
        emptyStr++;
        if (emptyStr > 1) {
          continue;
        }
      } else {
        emptyStr = 0;
      }

      if (lastSym == '\n' && FLAG->n) {
        printf("%6d\t", str++);
      }

      if (lastSym == '\n' && FLAG->b == 1 && curc != '\n') {
        printf("%6d\t", str++);
      }

      if (FLAG->t == 1 && curc == '\t') {
        printf("^");
        curc = 'I';
      }

      if (FLAG->e == 1 && curc == '\n') {
        if (FLAG->b == 1 && curc == '\n' && lastSym == '\n') {
          printf("      \t");
        }

        printf("$");
      }

      if (FLAG->v == 1) {
        if (curc > 127 && curc < 160) printf("M-^");
        if ((curc < 32 && curc != '\n' && curc != '\t') || curc == 127)
          printf("^");
        if ((curc < 32 || (curc > 126 && curc < 160)) && curc != '\n' &&
            curc != '\t')
          curc = curc > 126 ? curc - 128 + 64 : curc + 64;
      }

      printf("%c", curc);
      lastSym = curc;
    }
    fclose(file);
  }

  else {
    ret = -1;
  }
  return ret;
}
