#ifndef _PARSING_H_
#define _PARSING_H_
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF 15000

typedef struct options {
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
  int flags_counter;
  int flags_counter_e;
  char string_o_flag[BUF];
  char template[BUF];  // строка шаблонов
  char string[BUF];  // строка, которую будем сравнивать RE с string
  char file_name[BUF];  // строка имен файлов
} opt;

enum option_codes {
  CLEAR = 0,
  SET = 1,
  HELP = 2,
};

void parser(int argc, char *argv[], opt *options);
void execution_file(int argc, char *argv[], opt *options);
void f_flag(opt *options);
int file_counter(char *argv[], opt *options);

#endif  // _PARSING_H_