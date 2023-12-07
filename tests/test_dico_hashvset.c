#include "../include/generic_hashvset.h"
#include "../include/generic_vect.h"
#include "../include/mystring.h"
#include "../include/lecture_arguments.h"
#include <string.h>
#include <time.h>
#define TAILLE_MAX 100000

makehashvsettype(mystring)
makehashvsetfunction(mystring)
makehashvsetproto(mystring)

makevecttype(mystring)
makevectproto(mystring)
makevectfunction(mystring)

int main(int argc, char *argv[])
{

  FILE *ft = NULL;
  FILE *fd = NULL;

  // Ouverture des fichiers
  if (read(argc, argv, &ft, &fd) == EXIT_FAILURE)
    return EXIT_FAILURE;

  // Création du dictionnaire
  hashvset_mystring_t table = hashvset_mystring_new(10, fhashchage, mystring_fprintf, mystring_delete, mystring_equal);
  mystring s;
  char mot_dct[50];
  while (fgets(mot_dct, 50, fd) != NULL)
  {
    s = strndup(mot_dct, (strlen(mot_dct) - 1) * sizeof(char));
    hashvset_mystring_put(s, table);
  }

  // Création du tableau des mots inconnus au dictionnaire
  vect_mystring_t inconnus = vect_mystring_new(2, mystring_fprintf, mystring_delete, mystring_equal);

  // Identification des mots du texte source
  char str[TAILLE_MAX];
  char *mot;
  int presence;

  // Demarrage du timer
  clock_t debut, fin;
  double temps = 0;

  while (fgets(str, TAILLE_MAX, ft) != NULL)
  {
    mot = strtok(str, " \n.,:-;!?()'");
    while (mot != NULL)
    {

      if (mot[0] != '"')
      {

        // On supprime les caractères de fin de mot qui ne sont pas des lettres
        if (mot[strlen(mot) - 1] > 122 || mot[strlen(mot) - 1] < 97)
        {
          s = strndup(mot, strlen(mot) - 1);
        }
        else
        {
          s = strdup(mot);
        }
        // On ignore les mots ne commençant pas par une minuscule
        if (s[0] < 123 && s[0] > 96)
        {
          // Recherche de l'élément dans le dictionnaire
          debut = clock();
          presence = hashvset_mystring_find_key(s, table);
          fin = clock();
          temps += ((double)fin - debut) / CLOCKS_PER_SEC;
          // Ajout dans la liste des inconnus
          if (presence == -1)
          {
            if (vect_mystring_find(&s, inconnus) == -1)
              vect_mystring_append(s, inconnus);
            else
              mystring_delete(s);
          }
          else
            mystring_delete(s);
        }
        else
          mystring_delete(s);
      }
      mot = strtok(NULL, " \n.,:;!?()'-");
    }
  }
  // Affichage des mots inconnus
  // vect_mystring_fprintf(inconnus, stderr);
  printf("Il y a %d mots inconnus\n", inconnus->actual_size);

  // Affichage du temps
  printf("temps mis par le vérificateur=%lf\n", temps);

  // Libération des objets utilisés
  inconnus = vect_mystring_delete(inconnus);
  table = hashvset_mystring_delete(table);
  free(table);
  free(inconnus);
  fclose(fd);
  fclose(ft);
  return 0;
}
