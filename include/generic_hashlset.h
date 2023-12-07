#ifndef _GENERIC_hashlset_H
#define _GENERIC_hashlset_H

#include "genericcommon.h"

#include "generic_list.h"

#include "mystring.h"

/////////////////////////
// Macro pour definir les noms des fonctions et des types
// Definition de nom du type des hashlsetes, sous la forme hashlset_type_t
#define hashlsettype(type) makeid(makeid(hashlset_,type),_t)

// Definition du nom des fonctions, sous la forme hashlset_func
// func sera add_first, _del_first, etc...
#define hashlsetfunction(type,func) makeid(makeid(hashlset_,type),func)

////////////////////////
// Definition des structures des hashlsets par la macro maketypehashlset
// Le nom de la structure est hashlset_type_t

#define makehashlsettype(type) \
    /* Besoin des définitions sur les list_t et link_t */\
  makelisttype(type);\
  makelistproto(type);\
  makelistfunction(type);\
    /* Definition du type hashlset_t */\
  typedef struct makeid(hashlset_,type) { \
      /* Le tableau de pointeurs vers maillons */\
    linktype(type)* data;\
      /* La fonction de hachage pour cet ensemble */\
    unsigned int (*hachage)(type ); \
      /* Taille du tableau */\
    unsigned int size;\
      /* Nombre d'elements de l'ensemble */\
    unsigned int total_number;\
      /* Les fonctions classques */\
    type (*delete_key)(type);\
    int (*compare_key)(type* e1, type* e2);\
    void (*print_key)(type, FILE*);\
  }  * makeid(makeid(hashlset_,type),_t);

/////////////////////////////////
// Definition des fonctions de base sur les hashlsetes
// Creation d'une hashlsete
#define makehashlsetnew(type) \
  hashlsettype(type) hashlsetfunction(type,_new)(unsigned int n, \
      unsigned int (*fhachage)(type ), void (*print_key)(type, FILE*),\
          type (*delete_key)(type),\
          int (*compare_key)(type* e1, type* e2)) {\
    hashlsettype(type) table=malloc(sizeof(*table));\
      /* A COmpleter */\
      /* Allocation de la structure et du tableau de listes */\
      /* Mise a jour des champs */\
      table->size=n;\
      table->data=calloc(n,sizeof(linktype(type)));\
      table->total_number=0;\
      table->delete_key=delete_key;\
      table->compare_key=compare_key;\
      table->hachage=fhachage;\
      table->print_key=print_key;\
    return table;\
  }

  // Ajout d'un element
#define makehashlsetadd(type) \
  int hashlsetfunction(type,_put)(type key, hashlsettype(type) table){\
    /* A completer */\
    /* Calcul du hascode et de l'indice modulo taille */\
      if(table->total_number==table->size){\
      linktype(type)* data = calloc(table->size*2,sizeof(linktype(type)));\
      int i;\
      for(i=0;i<table->size;i++){\
        linktype(type) p;\
        p=table->data[i];\
        while(!linkfunction(type,_isempty)(p)){\
            int h= table->hachage(p->data);\
            int slot=h%(table->size*2);\
            data[slot]=linkfunction(type,_add_first)(&p->data, data[slot]);\
          p=p->next;\
        }\
      }\
      for(i=0;i<table->size;i++){\
        linktype(type) p;\
        p=table->data[i];\
        while(!linkfunction(type,_isempty)(p)) p=linkfunction(type,_del_first)(p,NULL);\
      }\
      free(table->data);\
      table->data=data;\
      table->size=table->size*2;\
    }\
    int h= table->hachage(key);\
    int slot=h%table->size;\
    linktype(type) p;\
    for (p=table->data[slot]; !linkfunction(type,_isempty)(p);p=p->next){\
      if(p->data==key) return 1;\
    }\
    table->data[slot]=linkfunction(type,_add_first)(&key, table->data[slot]);\
    table->total_number++;\
    if(table->data[slot]->data==key) return 2;\
    else return 0;\
  }

  // Suppression d'un élément
#define makehashlsetremovekey(type) \
  int hashlsetfunction(type,_remove_key)(type key, hashlsettype(type) table)  {\
    /* A Completer */\
    int h= table->hachage(key);\
    int slot=h%table->size;\
    linktype(type) p;\
    if(table->compare_key(&key,&table->data[slot]->data)==0){\
      table->data[slot]=linkfunction(type,_del_first)(table->data[slot],table->delete_key);\
      return 1; \
    }\
    for (p=table->data[slot]; !linkfunction(type,_isempty)(p);p=p->next){\
      if(table->compare_key(&key,&p->next->data)==0){\
        linktype(type) c;\
        c= p->next;\
        p->next=c->next;\
        if(table->delete_key!=NULL) table->delete_key(c->data);\
        free(c);\
        return 1;\
      }\
      return 0;\
  }\
  return 0;\
  }

  // Affichage
#define makehashlsetfprintf(type) \
  void hashlsetfunction(type,_fprintf)(hashlsettype(type) table,FILE* fp) {\
    /* A Completer */\
    int i;\
    for(i=0;i<table->size;i++){\
      fprintf(fp, "Slot %d:",i);\
      linktype(type) p;\
      p=table->data[i];\
      while(!linkfunction(type,_isempty)(p)){\
          table->print_key(p->data,fp);\
        p=p->next;\
      }\
      fprintf(fp, "\n");\
    }\
    fprintf(fp, "\n");\
  }

// Liberation de la table
#define makehashlsetdelete(type) \
  hashlsettype(type) hashlsetfunction(type,_delete)(hashlsettype(type) table) {\
    /* A Completer */\
    int i;\
    for(i=0;i<table->size;i++){\
      while(!linkfunction(type,_isempty)(table->data[i])){\
        table->data[i]=linkfunction(type,_del_first)(table->data[i],table->delete_key);\
      }\
    }\
    free(table->data);\
    return table;\
  }

  // Recherche et présence d'un element
#define makehashlsetfindkey(type) \
  int hashlsetfunction(type,_find_key)(type key, hashlsettype(type) table)  {\
      /* A Completer */\
      int h= table->hachage(key);\
      int slot=h%table->size;\
      linktype(type) p;\
      for (p=table->data[slot]; !linkfunction(type,_isempty)(p);p=p->next){\
        if(table->compare_key(&p->data,&key)==0) return 1;\
      }\
    return -1;\
  }

////////////////////////////////
// Macro regroupant toutes les definitions de fonctions pour la creation de toutes
// les fonctions sur les hashlsetes. A utiliser dans hashlset_type.c.
#define makehashlsetfunction(type) \
makehashlsetnew(type)\
makehashlsetdelete(type)\
makehashlsetfprintf(type)\
 makehashlsetadd(type)\
 makehashlsetremovekey(type)\
makehashlsetfindkey(type)\


// Macro regroupant toutes les declarations de fonctions
// A utiliser dans hashlset_type.h
#define makehashlsetproto(type) \
hashlsettype(type) hashlsetfunction(type,_new)(unsigned int n, \
    unsigned int (*fhachage)(type ), void (*print_key)(type, FILE*),\
        type (*delete_key)(type),\
        int (*compare_key)(type* e1, type* e2)) ;\
hashlsettype(type) hashlsetfunction(type,_delete)(hashlsettype(type) table);\
void hashlsetfunction(type,_fprintf)(hashlsettype(type) table,FILE*) ;\
int hashlsetfunction(type,_put)(type e, hashlsettype(type) table);\
int hashlsetfunction(type,_remove_key)(type e, hashlsettype(type) table);\
int hashlsetfunction(type,_find_key)(type key, hashlsettype(type) table);\

#endif
