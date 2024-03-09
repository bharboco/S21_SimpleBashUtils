#include "parsing.h"
int main(int argc, char *argv[]) {
  opt options = {0};
  parser(argc, argv, &options);
  if (options.f)
    options.e = 0, options.c = 0, options.o = 0, options.s = 0, options.h = 0;

  if (options.v) {
    options.f = 0;
  }

  if (options.l && options.c) options.n = 0;

  if (options.l) {
    options.v = 0, options.o = 0, options.f = 0, options.h = 0, options.n = 0;
  }

  if (options.c) options.o = 0, options.n = 0;

  if (options.v && options.l) options.o = 0;

  while (optind < argc) {
    execution_file(argc, argv, &options);
    optind++;
  }
  return 0;
}