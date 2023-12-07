#ifndef _MYSTRING_H
#define _MYSTRING_H
#include "genericcommon.h"
#include <ctype.h>

typedef char* mystring;

void mystring_fprintf(mystring v,FILE* fp);
mystring  mystring_delete(mystring p) ;
int mystring_equal(mystring* v1, mystring* v2);

// Allocation et copie d'une chaine à partir d'une autre
void* mystring_new(mystring val);

unsigned int fhashchage(mystring key);

void mystring_downcase(mystring m);


//retourne 1 si a>b, -1 si a<b, 0 si a=b;
int compare_char(char a, char b);

#endif
