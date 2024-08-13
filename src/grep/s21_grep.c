#include "s21_grep.h"

int main(int argc, char *argv[]) {
  flag FLAG = {0};

  readFlag(argc, argv, &FLAG);

  output(argc, argv, &FLAG);
  return 0;
}

void readFlag(int argc, char *argv[], flag *FLAG) {
  int currentFlag = 0;
  int options_index;
  struct option longOpt[] = {
      {0, 0, 0, 0},
  };
  while ((currentFlag = getopt_long(argc, argv, "e:ivclnhsf:o", longOpt,
                                    &options_index)) != -1) {
    switch (currentFlag) {
      case 'e':
        FLAG->e = 1;
        pattern(optarg, FLAG);
        break;
      case 'i':
        FLAG->i = REG_ICASE;
        break;
      case 'v':
        FLAG->v = 1;
        break;
      case 'c':
        FLAG->c = 1;
        break;
      case 'l':
        FLAG->l = 1;
        break;
      case 'n':
        FLAG->n = 1;
        break;
      case 'h':
        FLAG->h = 1;
        break;
      case 's':
        FLAG->s = 1;
        break;
      case 'f':
        FLAG->f = 1;
        patternFlagF(optarg, FLAG);
        break;
      case 'o':
        FLAG->o = 1;
        break;

      default:
        if (FLAG->s != 1) {
          fprintf(stderr, "ERROR CASE\n");
        }
        exit(1);
    }
  }
  if (FLAG->lenPattern == 0) {
    pattern(argv[optind], FLAG);
    optind++;
  }
  if (argc - optind == 1) {
    FLAG->h = 1;
  }
}

int readFile(char *path, regex_t *reg, flag *FLAG) {
  FILE *file = fopen(path, "r");
  if (file == NULL) {
    if (FLAG->s == 0)
      fprintf(stderr, "grep: %s: No such file or directory\n", path);
    return 1;
  }

  char *line = NULL;
  size_t memlen = 0;
  int lineNumber = 1;
  int matchCount = 0;

  int read = getline(&line, &memlen, file);
  while (read != -1) {
    int result = regexec(reg, line, 0, NULL, 0);
    if ((result == 0 && FLAG->v == 0) || (result != 0 && FLAG->v == 1)) {
      if (FLAG->c == 0 && FLAG->l == 0) {
        if (FLAG->o == 1 && FLAG->v == 0) {
          printFlagO(line, path, lineNumber, FLAG, reg);
        } else {
          chFlag(path, lineNumber, FLAG);
          outputLine(line, read);
        }
      }

      matchCount++;
    }
    read = getline(&line, &memlen, file);
    lineNumber++;
  }
  if (FLAG->c == 1 && FLAG->l == 1 && matchCount > 0) matchCount = 1;
  if (FLAG->c == 1) {
    if (FLAG->h == 0) printf("%s:", path);
    printf("%d\n", matchCount);
  }
  if (FLAG->l == 1 && matchCount > 0) printf("%s\n", path);
  free(line);
  fclose(file);
  return 0;
}

void outputLine(char *line, int N) {
  for (int i = 0; i < N; i++) {
    putchar(line[i]);
  }
  if (line[N - 1] != '\n') putchar('\n');
}

// вывод всех файлов
void output(int argc, char **argv, flag *FLAG) {
  regex_t reg;
  int err = regcomp(&reg, FLAG->pattern, REG_EXTENDED | FLAG->i);

  if (err) {
    if (FLAG->s == 0) {
      fprintf(stderr, "<<<ERROR REGCOMP>>>\n");
    }
  }

  for (int i = optind; i < argc; i++) {
    readFile(argv[i], &reg, FLAG);
  }
  regfree(&reg);
}

void pattern(char *pattern, flag *FLAG) {
  if (FLAG->lenPattern != 0) {
    strcat(FLAG->pattern + FLAG->lenPattern, "|");
    FLAG->lenPattern++;
  }

  FLAG->lenPattern +=
      sprintf(FLAG->pattern + FLAG->lenPattern, "(%s)", pattern);
}

void patternFlagF(char *filepath, flag *FLAG) {
  FILE *file = fopen(filepath, "r");
  if (file == NULL) {
    if (FLAG->s == 0) {
      fprintf(stderr, "<<<ERROR READ FILE>>>\n");
    }
    exit(1);
  }

  char *line = NULL;
  size_t memlen = 0;

  int read = getline(&line, &memlen, file);
  if (read != -1) {
    while (read != -1) {
      if (line[read - 1] == '\n') line[read - 1] = '\0';
      pattern(line, FLAG);
      read = getline(&line, &memlen, file);
    }
  } else {
    if (FLAG->s == 0) fprintf(stderr, "<<<ERROR>>>\n");
  }

  free(line);
  fclose(file);
}

void printFlagO(char *line, char *path, int lineNumber, flag *FLAG,
                regex_t *reg) {
  regmatch_t match;

  int off = 0;
  while (1) {
    int result = regexec(reg, line + off, 1, &match, 0);
    if (result != 0) {
      break;
    }
    chFlag(path, lineNumber, FLAG);
    for (int i = match.rm_so; i < match.rm_eo; i++) {
      putchar(line[off + i]);
    }

    putchar('\n');

    off += match.rm_eo;
  }
}

void chFlag(char *path, int lineNumber, flag *FLAG) {
  if (FLAG->h == 0) printf("%s:", path);
  if (FLAG->n) printf("%d:", lineNumber);
}
