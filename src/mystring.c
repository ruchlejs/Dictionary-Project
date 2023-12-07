#include "../include/mystring.h"

/// @brief Ecrit un mystring dans un fichier qui ne doit pas être NULL
/// @param v mystring
/// @param fp fichier d'écriture, en mode écriture
void mystring_fprintf(mystring v, FILE *fp) { fprintf(fp, "%s ", v); }
mystring mystring_delete(mystring p)
{
  free(p);
  return p;
}

/// @brief Teste l'égalité entre deux mystring
/// @param v1 
/// @param v2 
/// @return voir strcasecmp
int mystring_equal(mystring *v1, mystring *v2) { return strcasecmp(*v1, *v2); }

/// @brief Copie un mystring
/// @param val mystring à copier
/// @return pointeur sur la chaine copiée
void *mystring_new(mystring val) { return strdup(val); }

/// @brief Génere une clé de hachage
/// @param key mystring
/// @return clé de hachage
unsigned int fhashchage(mystring key)
{
  unsigned int hash = 5381;
  int c;

  while ((c = *key++))
    hash = ((hash << 5) + hash) + c; // hash * 33 + c

  return hash;
}

/// @brief supprimme toutes les majuscules d'un mot
/// @param m mystring à modifier
void mystring_downcase(mystring m)
{
  int i;
  for (i = 0; i < strlen(m); i++)
  {
    if (m[i] >= 65 && m[i] <= 90)
      m[i] += 32;
    i++;
  }
}

/// @brief compare deux caractères
/// @param a 
/// @param b 
/// @return 0 si a=b, 1 si a>b, -1 sinon 
int compare_char(char a, char b)
{
  if (a == b)
    return 0;
  if (tolower(a) == tolower(b))
    return 0;
  if (a > b)
    return 1;
  return -1;
}
