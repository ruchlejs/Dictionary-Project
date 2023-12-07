#include "../include/trie_prefixe.h"

/// @brief Test si le trie est vide
/// @param tree 
/// @return 1 si vide, 0 sinon
int isemptytrie(trie_t tree)
{
  if (tree == NULL)
    return 1;
  return 0;
}

/// @brief alloue un trie pour l'alphabet 
/// @return un trie
trie_t newtrie_t()
{
  trie_t tree = malloc(sizeof(*tree));
  tree->sons = calloc(27, sizeof(*(tree->sons)));
  if (tree->sons[0] == NULL)
    return tree;
  return tree;
}

/// @brief Fonction de hashage du trie
/// @param c char à placer
/// @return l'indice dans le tableau
int fonction_hash(char c)
{
  if (compare_char(c, '\0') == 0)
    return 26;
   if (compare_char(c, '"') == 0)
    return 0;
  return (c - 97) % 26;
}

/// @brief Ajoute un mystring dans le trie, chaine de caractère non accentuée
/// @param tree trie de sauvegarde
/// @param mot Mystring à ajouter
/// @return trie
trie_t add_mystring_trie(trie_t tree, mystring mot)
{
  int i;
  trie_t pointeur = tree;
  for (i = 0; i <= strlen(mot); i++)
  {
    int h = fonction_hash(mot[i]);
    if (isemptytrie(pointeur->sons[h]) == 1)
    {
      pointeur->sons[h] = newtrie_t();
      pointeur = pointeur->sons[h];
    }
    else
    {
      pointeur = pointeur->sons[h];
    }
  }
  return tree;
}

/// @brief Test la présence du mot
/// @param mot mystring à chercher
/// @param tree trie de sauvegarde
/// @return 0 si présence, -1 sinon
int recherche_mystring_trie(mystring mot, trie_t tree)
{
  if (isemptytrie(tree) == 1 || mot == NULL)
    return -1;
  trie_t pointeur = tree;
  int i;
  for (i = 0; i <= strlen(mot); i++)
  {
    int h = fonction_hash(mot[i]);
    if (isemptytrie(pointeur->sons[h]) == 1)
      return -1;
    else
    {
      if (h == 26)
        return 0;
      else{
        pointeur = pointeur->sons[h];
      }
    }
  }
  return -1;
}

/// @brief Libère la mémoire allouée pour construire le trie
/// @param tree trie à libérer
void free_trie(trie_t tree)
{
  if (isemptytrie(tree) == 1)
    return;
  int i;
  for (i = 0; i < 27; i++)
  {
    free_trie(tree->sons[i]);
  }
  free(tree->sons);
  free(tree);
}
