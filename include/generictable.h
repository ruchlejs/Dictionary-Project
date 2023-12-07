#ifndef _GENERIC_TABLE_H
#define _GENERIC_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef catid
#undef catid
#endif
#define catid(a,b) a##b

#ifdef makeid
#undef makeid
#endif
#define makeid(a,b) catid(a,b)
#define catid(a,b) a##b
#define makeid(a,b) catid(a,b)

// Definition de nom du type des tables, sous la forme table_type_t
#define tabletype(type) makeid(makeid(table_,type),_t)

// Definition du nom des fonctions, sous la forme table_type_func
// func sera _new, _del_first, etc...
#define tablefunction(type,func) makeid(makeid(table_,type),func)


////////////////////////
// Definition des structures des tables par la macro maketabletype
// Le nom de la structure est table_type_t
// Elle comporte les champs
//    - data : un tableau de donnees alloue dynamiquement,
//    - max_size : la taille max du tableau
//    - actual_size : la taille actuelle du tableau
//    - fprint_data : fonction d'affichage d'un element
//    - delete_data : fonction de liberation memoire d'un element, pour les pointeurs
//    - equal_data : fonction testant l'egalite de 2 elements

#define maketabletype(type) typedef struct { \
    type* data;\
    unsigned int max_size;\
    unsigned int actual_size;\
    void (*fprint_data)(type*,FILE*);\
    type* (*delete_data)(type*);\
    int (*equal_data)(type*,type*);\
  }  * tabletype(type);

/////////////////////////////////
// Definition des fonctions de base sur les tables
// Creation d'un table de n elements vide
// Allocation du tableau de n elements, taille actuelle nulle.
#define maketablenew(type) \
  tabletype(type) tablefunction(type,_new)(unsigned int n,\
      void (*fprint_data)(type*,FILE*),\
      type* (*delete_data)(type*),\
      int (*equal_data)(type*,type*)) {\
    tabletype(type) table=NULL;\
    if ( (table=malloc(sizeof(*table))) ==NULL) return NULL;\
    if (n<=0) n=1;\
    if ( (table->data=calloc(n,sizeof(*(table->data)))) ==NULL) {free(table); return NULL;}\
    table->max_size=n;\
    table->actual_size=0;\
    table->fprint_data=fprint_data;\
    table->delete_data=delete_data;\
    table->equal_data=equal_data;\
    return table;\
  }

// Liberation de la table
#define maketabledelete(type) \
  tabletype(type) tablefunction(type,_delete)(tabletype(type) table) {int i; \
    if (table==NULL) return NULL;\
    if (table->delete_data)\
      for(i=0;i<table->actual_size; i++)\
        table->delete_data(table->data+i);\
    free(table->data);\
    free(table);\
    return NULL;\
  }

// Ajout d'un element
// Ajoute un element en derniere place.
// precondition : tableau existant
#define maketableappend(type) \
  tabletype(type) tablefunction(type,_append)(type e, tabletype(type) table)  {\
    table->data=realloc(table->data,sizeof(type)*(table->max_size+1));\
    table->data[table->max_size]=e;\
    table->max_size+=1;\
    table->actual_size+=1;\
    return table;\
  }

// insertion d'un element
// Ajoute un element a la place i.
// preconditions : tableau existant  et i>=0 et i<=actual_size
#define maketableinsertat(type) \
  tabletype(type) tablefunction(type,_insert_at)(type e, int i, tabletype(type) table)  {\
    if((i<0) || (i>table->actual_size)){\
      printf("Indice d'insertion incorrect\n");\
      return table;\
    } \
    table->data=realloc(table->data,sizeof(type)*(table->max_size+1));\
    table->max_size+=1;\
      int k;\
      for(k=table->max_size-2;k>=i;k--){\
        table->data[k+1]=table->data[k];\
      }\
      table->data[i]=e;\
      table->actual_size+=1;\
      return table;\
  }\

// Supprime la case i du tableau
#define maketableremoveat(type) \
  tabletype(type) tablefunction(type,_remove_at)(int i, tabletype(type) table) {\
    /* A Completer */\
    if((i<0) || (i>table->actual_size)){\
      printf("Indice d'insertion incorrect\n");\
      return table;\
    } \
    int k;\
    for(k=i;k<table->actual_size-1;k++){\
      table->data[k]=table->data[k+1];\
    }\
    table->data=realloc(table->data,sizeof(type)*(table->max_size-1));\
    table->actual_size-=1;\
    table->max_size+=1;\
    return table;\
  }

// Affichage du tableau sur le flux fp
#define maketablefprint(type) \
  void tablefunction(type,_fprintf)(tabletype(type) table,FILE* fp) {\
    /* A Completer */\
    int i;\
    for(i=0;i<table->actual_size;i++){\
      table->fprint_data(table->data+i,fp);\
    }\
  }\

#define maketableprint(type) \
  void tablefunction(type,_printf)( tabletype(type) table) {\
    /* A Completer */\
    int i;\
    for(i=0;i<table->actual_size;i++){\
      table->fprint_data(table->data+i,stderr);\
    }\
    fprintf(stderr,"\n");\
  }\

////////////////////////////////
// Macro regroupant toutes les definitions de fonctions pour la creation de toutes
// les fonctions sur les tables. A utiliser dans table_type.c.
// Pratique de regrouper toutes les fonctions dans une seule commande
#define maketablefunction(type) \
  maketablenew(type)\
  maketableappend(type)\
  maketabledelete(type)\
  maketablefprint(type)\
  maketableprint(type)\
  maketableinsertat(type)\
  maketableremoveat(type)\


// Idem pour les prototypes de fonctions
// Macro regroupant toutes les declarations de fonctions
#define maketableproto(type)\
  tabletype(type) tablefunction(type,_new)(unsigned int n,\
      void (*fprint_data)(type*,FILE*),\
      type* (*delete_data)(type*),\
      int (*equal_data)(type*,type*));\
  tabletype(type) tablefunction(type,_delete)(tabletype(type) table);\
  tabletype(type) tablefunction(type,_append)(type e, tabletype(type) table)  ;\
  void tablefunction(type,_printf)(tabletype(type) table);\
  void tablefunction(type,_fprintf)( tabletype(type) table,FILE*);\
  tabletype(type) tablefunction(type,_remove_last)(int n,tabletype(type) table);\
  tabletype(type) tablefunction(type,_insert_at)(type e, int i, tabletype(type) table)  ;\
  tabletype(type) tablefunction(type,_remove_at)(int i, tabletype(type) table);

#endif
