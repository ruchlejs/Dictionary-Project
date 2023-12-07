#ifndef _LECTURE_ARGUMENTS_H
#define _LECTURE_ARGUMENTS_H
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


void help_printer();

void error_printer(char* error);

int read(int argc, char * argv[],FILE ** ft, FILE **fd );

#endif
