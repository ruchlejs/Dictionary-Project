#include "../include/arbre_lexico.h"

/// @brief Permet de génerer un arbre lexicographique à partir d'un premier caractère
/// @param value caractère à enregistrer
/// @return pointeur sur l'arbre
tree_t newtree_t(char value)
{
  tree_t tree = malloc(sizeof(struct _node));
  tree->value = value;
  tree->son = NULL;
  tree->brother = NULL;
  return tree;
}

/// @brief  Test si le noeud est vide
/// @param tree 
/// @return 1 si vide, 0 sinon
int isemptytree(tree_t tree)
{
  if (tree == NULL)
    return 1;
  return 0;
}


/// @brief AJoute un mystring à l'arbre
/// @param mot mystring à ajouter
/// @param tree arbre de sauvegarde
/// @return l'abre complété
tree_t add_mystring_arbre(mystring mot, tree_t tree)
{
  if (isemptytree(tree) == 1)
    tree = newtree_t(mot[0]);
  if (compare_char(mot[0], tree->value) == 0)
  {
    if (compare_char(mot[1], '\0') == 0)
    {
      tree->son = newtree_t('\0');
      return tree;
    }
    else
      tree->son = add_mystring_arbre(mot + 1, tree->son);
  }
  else
    tree->brother = add_mystring_arbre(mot, tree->brother);
  return tree;
}

/// @brief Test la présence d'un mystring dans l'arbre
/// @param mot mystring à tester
/// @param tree arbre de sauvegarde
/// @return 0 si présence, -1 sinon
int recherche_mystring(mystring mot, tree_t tree)
{
  if (isemptytree(tree) == 1 && mot == NULL)
    return -1;
  tree_t pointeur = tree;
  int i;
  for (i = 0; i <= strlen(mot); i++)
  {
    while (isemptytree(pointeur) == 0)
    {
      if (compare_char(mot[i], pointeur->value) == 0)
      {
        if (compare_char(mot[i], '\0') == 0)
          return 0;
        else
          pointeur = pointeur->son;
        break;
      }
      else
        pointeur = pointeur->brother;
    }
  }
  return -1;
}

/// @brief Libère l'abre de sauvegarde
/// @param tree arbre de sauvegarde
void free_tree(tree_t tree)
{
  if (isemptytree(tree) == 1)
    return;
  free_tree(tree->son);
  free_tree(tree->brother);
  free(tree);
}
