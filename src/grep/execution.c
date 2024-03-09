#include "parsing.h"

void execution_file(int argc, char *argv[], opt *options) {
  regex_t RE;    // R - regular, E - expression
  regmatch_t S;  // S - start. Пример: "The is cool" grep: "is"
  // rm_so - отлавливает начало и конец совпадения побайтово(начальное смещение
  // следующего совпадения) "i" rm_eo - указываеь на смещение конца совпадения,
  // которое является первым символом после совпавшего текста " " между s и c
  int match = 0, match_counter = 0, str_count = 0, empty_string = 0,
      files_counter, one_counter = 0, match_counter_v = 0;
  int i = strlen(options->template);
  int prev = options->string[i - 1];

  if (options->e) {
    files_counter = (argc - 1) -
                    (options->flags_counter_e + (options->flags_counter_e + 1));
  } else
    files_counter = argc - options->flags_counter - 2;

  FILE *f = fopen(argv[optind], "r");
  if (f != NULL) {
    if (options->i) {  // i flag
      int flag_i = REG_EXTENDED | REG_ICASE;
      // REG_ICASE - игнорирует верхний и нижний регистры
      regcomp(&RE, options->template, flag_i);
      // regcomp - компилирует аргументы из template в регулярные
      // выражения с помощью REG_EXTENDED и сохраняем в структуру RE
      /* REG_EXTENDED приводит к типу регулярных выражений
      пример: [0-9] без REG_EXTENDED скобка ноль минус девять скобка
      с REG_EXTENDED поиск цифр от 0 до 9 hh */
    } else
      regcomp(&RE, options->template, REG_EXTENDED);
    while (fgets(options->string, BUF, f) != NULL) {  // or EOF
      // match - совпадение, т.е. счетчик совпадений
      match = regexec(&RE, options->string, 1, &S, 0);  // сравнивает строки
      // если есть совпадение, то regexec возвращает 0
      str_count++;
      if (!match) {
        match_counter++;
        if (!match && !options->e && !options->i && !options->v &&
            !options->c && !options->l && !options->n && !options->h &&
            !options->s && !options->f && !options->o) {
          if (files_counter > 1) {
            printf("%s:%s", argv[optind], options->string);
          } else
            printf("%s", options->string);
        }
      }

      //___________________________________________________________________
      if (!match && options->i) {  // i flag
        if (files_counter > 1 && !options->e && !options->h && !options->n &&
            !options->o && !options->l && !options->c && !options->v)
          printf("%s:%s", argv[optind], options->string);
        else if (!options->e && !options->n && !options->o && !options->f &&
                 !options->l && !options->c && !options->v)
          printf("%s", options->string);
      }
      //___________________________________________________________________
      if (!match && options->h)  // h flag
      {
        if (!options->o && !options->n && !options->c && !options->v &&
            !options->i)
          printf("%s", options->string);
      }
      //___________________________________________________________________
      if (!match && options->e)  // e flag
      {
        if (files_counter >= 1 && !options->f && !options->h && !options->c)
          printf("%s:%s", argv[optind], options->string);
        else if (!options->f && !options->c)
          printf("%s", options->string);
      }
      //___________________________________________________________________
      if (!match && options->f) {  // f flag
        if (files_counter > 1 && !options->h && !options->n && !options->v)
          printf("%s:%s", argv[optind], options->string);
        else if (!options->h && !options->n && !options->v)
          printf("%s", options->string);
      }
      //___________________________________________________________________
      if (options->v) {  // v flag
        match = !match;
        match_counter_v++;
        if (!match && files_counter > 1 && !options->h && !options->c)
          printf("%s:%s", argv[optind], options->string);
        else if (!match && !options->c && !options->n)
          printf("%s", options->string);
      }
      //___________________________________________________________________
      if (options->n && !match) {  // n flag
        if ((files_counter > 1 && !options->h && !options->f) ||
            (files_counter >= 1 && options->f && !options->h))
          printf("%s:%d:%s", argv[optind], str_count, options->string);
        else
          printf("%d:%s", str_count, options->string);
      }
      //___________________________________________________________________
      if (!match && options->o && !options->l && !options->c) {  // o flag
        char *pointer = options->string;
        while ((regexec(&RE, pointer, 1, &S, 0) == 0)) {
          printf("%.*s\n", (int)(S.rm_eo - S.rm_so), pointer + S.rm_so);
          pointer += S.rm_eo;
        }
      }
      //___________________________________________________________________
      if (!match && options->s && !options->f && !options->e) {  // s flag
        if (files_counter > 1 && !options->h)
          printf("%s:%s", argv[optind], options->string);
        else
          printf("%s", options->string);
      }

      if (prev == '\n' &&
          options->string[i] == '\n') {  // удаление пустых строк
        if (empty_string) continue;
        empty_string = 1;
      } else
        empty_string = 0;

      if (!match && options->c && options->l && one_counter == 0) {
        if (!match && !options->h) {
          printf("%s:1\n", argv[optind]);
          one_counter++;
        } else {
          printf("%s:0\n", argv[optind]);
          one_counter++;
        }
      }
      if (!match && options->l && match_counter == 1)  // l flag
        printf("%s\n", argv[optind]);
    }  // end while
       //___________________________________________________________________
    if (options->c && !options->l && !options->v) {  // c flag
      if (files_counter >= 1 && !options->h && options->n)
        printf("%s:%d\n", argv[optind], match_counter);
      else if (files_counter > 1 && !options->h && !options->n)
        printf("%s:%d\n", argv[optind], match_counter);
      else
        printf("%d\n", match_counter);
    }
    if (options->c && !options->l && options->v) {  // cv flag
      if (files_counter > 1 && !options->h)
        printf("%s:%d\n", argv[optind], match_counter_v);
      else
        printf("%d\n", match_counter_v - match_counter);
    }

    //___________________________________________________________________
    // ставит каретки между файлами, когда files_counter > 1
    if (!match && files_counter > 1 && !options->h && !options->l &&
        !options->n && !options->c && !options->v && !options->f) {
      if ((options->string[i - 1] != '\0' && !options->o))
        printf("\n");
      else if (options->string[i - 1] == '\n')
        options->string[i - 1] = '\0';
    }

    regfree(&RE);
  } else {
    if (!options->s) {  // s flag
      fprintf(stderr, "grep: %s: No such file or directory\n", argv[optind]);
      exit(1);
    }
  }
  fclose(f);
}

void f_flag(opt *options) {
  FILE *f = fopen(optarg, "r");
  if (f != NULL) {
    while (fgets(options->string, BUF, f) != NULL) {
      if (options->string[strlen(options->string) - 1] == '\n' &&
          strlen(options->string) - 1 != '\0') {
        options->string[strlen(options->string) - 1] = '\0';
      }
      strcat(options->template, options->string);
      strcat(options->template, "|");
    }
  } else {
    fprintf(stderr, "grep: %s: No such file or directory\n", optarg);
    exit(1);
  }
  fclose(f);
}