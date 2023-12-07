#ifndef _TRIE_PREFIXE_H
#define _TRIE_PREFIXE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/mystring.h"

typedef
    struct _node {
      struct _node **sons; } *  trie_t;

int isemptytrie(trie_t tree);


trie_t newtrie_t();

int fonction_hash(char c);

trie_t add_mystring_trie(trie_t tree,mystring mot);

int recherche_mystring_trie(mystring mot, trie_t tree);

void free_trie(trie_t tree);

#endif
