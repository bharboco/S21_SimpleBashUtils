#ifndef _EXECUTION_H_
#define _EXECUTION_H_
#include "parsing.h"

void execution_file(int argc, char *argv[], opt *options);
void f_flag(opt *options);
int file_counter(char *argv[], opt *options);

#endif  // _EXECUTION_H_