#ifndef _DOUBLE_H
#define _DOUBLE_H
#include "genericcommon.h"


void double_fprintf(double val,FILE* fp);
void double_printf(double val);
  // Test l'egalite de 2 reels
int double_equal(double* pv1, double* pv2);
  // Génération d'un reel aléatoire
void double_random(double*p);
  // Clone d'un reel
double* double_new(double* val);

double delete_data(double val );

#endif
