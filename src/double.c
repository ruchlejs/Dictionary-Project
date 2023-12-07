#include "../include/double.h"


/// @brief Ecrit un double dans un fichier
/// @param val double à écrire
/// @param fp fichier à ouvrir en mode écriture
void double_fprintf(double val, FILE *fp) { fprintf(fp, "%lf ", val); }

/// @brief Ecrit un double dans le termnal
/// @param val double à écrire
void double_printf(double val) { double_fprintf(val, stdout); }

/// @brief Teste l'égualité entre deux doubles
/// @param pv1 double
/// @param pv2 double
/// @return 0 si égalité, 1 sinon
int double_equal(double *pv1, double *pv2) { return *pv1 == *pv2; }

/// @brief génère un double aléatoire modulo 100
/// @param p double
void double_random(double *p) { *p = random() % 100; }

/// @brief clone un double qui ne doit pas être NULL
/// @param val double
/// @return l'adresse du nouveau double
double *double_new(double *val)
{
  double *p = malloc(sizeof(*p));
  *p = *val;
  return p;
}

/// @brief Libère la mémoire d'un double
/// @param val 
/// @return 0
double delete_data(double val) { return 0; }
