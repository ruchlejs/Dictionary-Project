#ifndef _GENERIC_VECT_H
#define _GENERIC_VECT_H

#include "genericcommon.h"
////////////////////////


////////////////////////
// Generation de code pour des vecteurs redimensionnables

// API, avec type=double, complex, pcomplex, mystring, etc....

    /////////////////////////
// Macro pour definir les noms des fonctions et des types

// Definition de nom du type des vects, sous la forme vect_type_t
#define vecttype(type) makeid(makeid(vect_,type),_t)

// Definition du nom des fonctions, sous la forme vect_func
// func sera _new, _del_first, etc...
#define vectfunction(type,func) makeid(makeid(vect_,type),func)


////////////////////////
// Definition des structures des vects par la macro maketypevect
// Le nom de la structure est vect_type_t
// Elle comporte les champs
//    - data : un tableau de donnees alloue dynamiquement,
//    - max_size : la taille max du tableau
//    - actual_size : la taille actuelle du tableau

#define makevecttype(type) typedef struct makeid(vect_,type) { \
    type* data;\
    unsigned int max_size;\
    unsigned int actual_size;\
    void (*fprint_data)(type,FILE*);\
    type (*delete_data)(type);\
    int (*equal_data)(type*,type*);\
  }  * makeid(makeid(vect_,type),_t);


/////////////////////////////////
// Definition des fonctions de base sur les vects
// Creation d'un vect de n elements vide
// Allocation du tableau de n elements, taille actuelle nulle.
#define makevectnew(type) \
  vecttype(type) vectfunction(type,_new)(unsigned int n, \
        void (*fprint_data)(type,FILE*),\
        type (*delete_data)(type),\
        int (*equal_data)(type*,type*)) {\
      /* Définition d une variable de type vect_type_t et de nom table */\
    vecttype(type) table=NULL;\
    if ( (table=calloc(1,sizeof(*table))) ==NULL) return NULL;\
    if (n<=0) n=1;\
    if ( (table->data=calloc(n,sizeof(*(table->data)))) ==NULL) {free(table); return NULL;}\
    table->max_size=n;\
    table->actual_size=0;\
    table->fprint_data=fprint_data;\
    table->delete_data=delete_data;\
    table->equal_data=equal_data;\
    return table;\
  }

// Ajout d'un element en derniere place.
// Augmente la taille du tableau si necessaire
#define makevectappend(type) \
vecttype(type) vectfunction(type,_append)(type e, vecttype(type) table)  {\
    /* A Completer */\
    if(table->actual_size==table->max_size){\
      table->max_size*=2;\
      table->data=realloc(table->data,sizeof(type)*(table->max_size));\
    }\
    table->actual_size+=1;\
    table->data[table->actual_size-1]=e;\
    return table;\
  }

// insertion d'un element
// Augmente la taille allouée du tableau si necessaire
// Ajoute un element a la place i.
// preconditions : tableau existant  et i>=0 et i<=actual_size
#define makevectinsert(type) \
vecttype(type) vectfunction(type,_insert)(type e, int i, vecttype(type) table)  {\
    /* A Completer */\
    if((i<0) || (i>table->actual_size)){\
      printf("Indice d'insertion incorrect\n");\
      return table;\
    } \
    if(table->actual_size==table->max_size){\
      table->max_size*=2;\
      table->data=realloc(table->data,sizeof(type)*(table->max_size));\
      }\
      int k;\
      for(k=table->actual_size-1;k>=i;k--){\
        table->data[k+1]=table->data[k];\
        }\
    table->data[i]=e;\
    table->actual_size+=1;\
    return table;\
  }

// Supprime la case i du tableau; Diminue la taille allouée si necessaire
#define makevectremoveat(type) \
  vecttype(type) vectfunction(type,_remove_at)(int i, vecttype(type) table) {\
    /* A Completer */\
    int k;\
    for(k=i;k<table->actual_size-1;k++){\
      table->data[k]=table->data[k+1];\
    }\
    table->actual_size-=1;\
    if(table->actual_size<table->max_size/3){\
      table->max_size=table->actual_size;\
      table->data=realloc(table->data,sizeof(type)*(table->max_size-1));\
    }\
    return table;\
  }

// Affichage du tableau dans un flux
#define makevectfprint(type) \
  void vectfunction(type,_fprintf)(vecttype(type) table,FILE* fp) {\
    /* A Completer */\
    int i;\
  for(i=0;i<table->actual_size;i++){\
    table->fprint_data(table->data[i],fp);\
  }\
  fprintf(fp,"\n");\
  }

// Affichage du tableau sur la sortie standart
#define makevectprint(type) \
  void vectfunction(type,_printf)( vecttype(type) table) {\
    /* A Completer */\
    int i;\
  for(i=0;i<table->actual_size;i++){\
    table->fprint_data(table->data[i],stderr);\
  }\
  fprintf(stderr,"\n");\
  }

// Liberation de la table
#define makevectdelete(type) \
  vecttype(type) vectfunction(type,_delete)(vecttype(type) table) {int i; \
    /* A Completer */\
    if (table==NULL) return NULL;\
    if (table->delete_data)\
      for(i=0;i<table->actual_size; i++)\
        table->delete_data(table->data[i]);\
    free(table->data);\
    free(table);\
    return NULL;\
  }
//
// Recherche d'un element dans un vecteur
// Utilise la fonction equal_data si elle existe ou memcpy sinon
#define makevectfind(type)\
  int vectfunction(type,_find)(type* param, vecttype(type) table) { \
    /* A Completer */\
    int i;\
    for(i=0;i<table->actual_size;i++){\
      if(table->equal_data(param,table->data+i)==0){\
        return 0;\
      }\
    }\
    return -1;\
  }

// Recherche selon un critere  donné par le parametre compare dans un vecteur
#define makevectlookup(type)\
  int vectfunction(type,_lookup)(type* param, vecttype(type) table, int (*compare)(type*,type*)) {\
    /* A Completer */\
    int i;\
    for(i=0;i<table->actual_size;i++){\
      if(compare(param,table->data+i)==0){\
        return i;\
      }\
    }\
    return 0;\
  }



////////////////////////////////
// Macro regroupant toutes les definitions de fonctions pour la creation de toutes
// les fonctions sur les vecteurs. A utiliser dans vect_type.c.
#define makevectfunction(type) \
makevectnew(type)\
makevectprint(type)\
makevectappend(type)\
makevectinsert(type)\
makevectremoveat(type)\
makevectdelete(type)\
makevectfind(type)\
makevectfprint(type)\
makevectlookup(type)\


// Macro regroupant toutes les declarations de fonctions
// Pour déclarer toutes les fonctions
#define makevectproto(type) \
vecttype(type) vectfunction(type,_new)(unsigned int n, \
      void (*fprint_data)(type,FILE*),\
      type (*delete_data)(type),\
      int (*equal_data)(type*,type*)) ;\
vecttype(type) vectfunction(type,_append)(type e, vecttype(type) table)  ;\
void vectfunction(type,_printf)(vecttype(type) table);\
void vectfunction(type,_fprintf)( vecttype(type) table,FILE*);\
vecttype(type) vectfunction(type,_delete)(vecttype(type) table);\
int vectfunction(type,_find)(type* param, vecttype(type) l) ;\
int vectfunction(type,_lookup)(type* param, vecttype(type) l, int (*compare)(type*,type*)) ;\
vecttype(type) vectfunction(type,_insert)(type e, int i, vecttype(type) table)  ;\
vecttype(type) vectfunction(type,_remove_at)(int i, vecttype(type) table) ;\

#endif
