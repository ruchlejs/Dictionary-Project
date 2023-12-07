#ifndef _ARBRE_LEXICO_H
#define _ARBRE_LEXICO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/mystring.h"

typedef
struct _node {
  char value;
  struct _node *son, * brother; } *  tree_t;

tree_t newtree_t(char value);

int isemptytree(tree_t tree);


tree_t add_mystring_arbre(mystring mot, tree_t tree);

int recherche_mystring(mystring mot, tree_t tree);

void free_tree(tree_t tree);

#endif
