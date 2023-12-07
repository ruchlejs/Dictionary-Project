#include "../include/lecture_arguments.h"

/// @brief Affiche dans le terminal l'aide
void help_printer()
{
  printf("--------------\n");
  printf("AIDE : \n");
  printf("--------------\n");
  printf("Arguments nécessaires :\n");
  printf("Premier argument : nom du texte que l'on veut vérifier\n");
  printf("Deuxième argument : nom du fichier contenant le dictionnaire\n");
  printf("--------------\n");
}

/// @brief Affiche l'erreur dans le termianl
/// @param error erreur à afficher, non null
void error_printer(char *error)
{
  printf("--------------\n");
  printf("Une erreur a été commise : %s\n", error);
  printf("--------------\n");
  printf("\n");
  help_printer();
}

/// @brief Test les arguments passés en entré et ouvre les fichiers
/// @param argc saisi par l'utilisateur
/// @param argv saisi par l'utilisateur
/// @param ft texte à vérifier
/// @param fd dictionnaire
/// @return exit_failure si erreur, exit_succes sinon
int read(int argc, char *argv[], FILE **ft, FILE **fd)
{

  if (argc == 1)
  {
    char erreur[50] = "Pas d'arguments";
    error_printer(erreur);
    return EXIT_FAILURE;
  }
  else
  {
    if (strcmp(argv[1], "help") == 0 || strcmp(argv[1], "aide") == 0 || strcmp(argv[1], "h") == 0 || strcmp(argv[1], "-help") == 0 || strcmp(argv[1], "-aide") == 0 || strcmp(argv[1], "-h") == 0)
    {
      help_printer();
      return EXIT_FAILURE;
    }
    else
    {
      if (argc < 3 || argc > 3)
      {
        char erreur[50] = "Nombre d'arguments invalide";
        error_printer(erreur);
        return EXIT_FAILURE;
      }
      else
      {

        // Ouverture des fichiers
        *ft = fopen(argv[1], "r");
        *fd = fopen(argv[2], "r"); // verifier le mode
        if (*ft == NULL || *fd == NULL)
        {
          printf("ouverture du texte ou du dictionnaire impossible\n");
          return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
      }
    }
  }
}
