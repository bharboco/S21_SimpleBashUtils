#include "parsing.h"

void parser(int argc, char *argv[], opt *options) {
  int c;
  while ((c = getopt_long(argc, argv, "e:ivclnhsf:o", NULL, 0)) != -1) {
    switch (c) {
      case 'f':
        options->f = 1, options->flags_counter++;
        f_flag(options);
        break;
      case 'e':
        options->e = 1, options->flags_counter_e++;
        options->flags_counter++;
        strcat(options->template, optarg);
        strcat(options->template, "|");
        break;
      case 'l':
        options->l = 1, options->flags_counter++;
        break;
      case 'c':
        options->c = 1, options->flags_counter++;
        break;
      case 'o':
        options->o = 1, options->flags_counter++;
        break;
      case 'i':
        options->i = 1, options->flags_counter++;
        break;
      case 'v':
        options->v = 1, options->flags_counter++;
        break;
      case 's':
        options->s = 1, options->flags_counter++;
        break;
      case 'n':
        options->n = 1, options->flags_counter++;
        break;
      case 'h':
        options->h = 1, options->flags_counter++;
        break;
      default:
        fprintf(stderr,
                "usage: grep [-ivclnhso] [-e pattern] [-f file] [pattern] "
                "[file ...]");
        exit(1);
    }
  }
  if (!options->e && !options->f) {
    if (argc > optind) {
      strcat(options->template, argv[optind]);
    }
    optind++;
  }
  if (options->e || options->f) {
    options->template[strlen(options->template) - 1] = '\0';
  }
}