#ifndef _GENERIC_hashvset_H
#define _GENERIC_hashvset_H

////////////////////////
#include "genericcommon.h"

#include "mystring.h"

typedef enum { EMPTY, FREE, OCCUPED} hash_state_t;
/////////////////////////
// Macros pour definir les noms des fonctions et des types

// Definition de nom du type des hashvset, sous la forme hashvset_type_t
#define hashvsettype(type) makeid(makeid(hashvset_,type),_t)
#define cellhashvsettype(type) makeid(makeid(cellhashvset_,type),_t)

// Definition du nom des fonctions, sous la forme hashvset_func
#define hashvsetfunction(type,func) makeid(makeid(hashvset_,type),func)

#define sondage(i) ((i)*(i))

////////////////////////
// Definition des structures des hashvsets par la macro maketypehashvset
// Le nom de la structure est hashvset_type_t
// Une case du tableau comporte une clé, un etat d'occupation et eventuellement le hashcode.
#define makehashvsettype(type) \
  typedef struct {\
    type key;\
    hash_state_t busy;\
    /* Le champ hashcode n'est utile que pour optimiser le redimensionnement*/ \
    unsigned int hashcode;\
  }  cellhashvsettype(type);\
  typedef struct makeid(_hashvset,type) { \
    cellhashvsettype(type)* data;\
    unsigned int (*hachage)(type ); \
    unsigned int size;\
    unsigned int total_number;\
    type (*delete_key)(type);\
    int (*compare_key)(type* e1, type* e2);\
    void (*print_key)(type, FILE*);\
  }  * hashvsettype(type) ;

/////////////////////////////////
// Definition des fonctions de base sur les hashvsetes
// Creation d'une hashvsete
#define makehashvsetnew(type) \
  hashvsettype(type) hashvsetfunction(type,_new)(unsigned int n,\
      unsigned int (*fhachage)(type), void (*print_key)(type, FILE*),\
          type (*delete_key)(type),\
          int (*compare_key)(type* e1, type* e2)) {\
    /* A Completer */\
    hashvsettype(type) table=malloc(sizeof(*table));\
    table->size=n;\
    table->data=calloc(n,sizeof(cellhashvsettype(type)));\
    int i;\
    for(i=0;i<table->size;i++){\
      table->data[i].busy=EMPTY;\
    }\
    table->total_number=0;\
    table->delete_key=delete_key;\
    table->compare_key=compare_key;\
    table->hachage=fhachage;\
    table->print_key=print_key;\
    return table;\
  }

  /* POur le redimensionnement */
/*  #define makehashvsetnewlength(type) \
    static int hashvsetfunction(type,_new_length)(int sens, hashvsettype(type) table)  {\
      return 1;\
    }*/

// Recherhce d'un element; Retourne l'indice de l'element trouvé ou -1
#define makehashvsetfindkey(type) \
  int hashvsetfunction(type,_find_key)(type k, hashvsettype(type) t)  {\
    int i,j;\
    unsigned int slot = t->hachage(k) % t->size;\
    /* Version avec suppression possible*/\
    for( i=0; i<t->size && t->data[j=(slot+sondage(i))%t->size].busy!=EMPTY; i++) { \
      if( (t->data[j].busy !=FREE) && (t->compare_key(&t->data[j].key, &k)==0)) { \
        return j;\
      }\
    }\
    return -1;\
  }

// Ajout d'un element
#define makehashvsetput(type) \
  int hashvsetfunction(type,_put)(type key, hashvsettype(type) table)  {\
    /* A Completer */\
    int h= table->hachage(key);\
    int i=0;\
    while(i<table->size){\
      int slot=(h+sondage(i))%table->size;\
      if((table->data[slot].busy!=OCCUPED)){\
        table->data[slot].key=key;\
        table->data[slot].hashcode=h;\
        table->data[slot].busy=OCCUPED;\
        table->total_number++;\
      return 1;\
      }\
      else{\
        if(table->compare_key(&table->data[slot].key,&key)==0){return 0;}\
        else i++;\
      }\
    }\
      cellhashvsettype(type)* data=calloc(table->size*2, sizeof(cellhashvsettype(type)));\
      table->total_number=0;\
      for(i=0;i<table->size;i++){\
        if(table->data[i].busy==OCCUPED){\
          int h=table->data[i].hashcode;\
          int j=0;\
          while(j<table->size*2){\
            int slot=(h+sondage(j))%(table->size*2);\
            if((data[slot].busy!=OCCUPED)){\
              data[slot].key=table->data[i].key;\
              data[slot].hashcode=h;\
              data[slot].busy=OCCUPED;\
              table->total_number++;\
              break;}\
            else j++;\
          }\
        }\
      }\
      free(table->data);\
      table->data=data;\
      table->size=table->size*2;\
      hashvsetfunction(type,_put)(key,table);\
    return 1;\
    }

// Affichage
#define makehashvsetfprintf(type) \
  void hashvsetfunction(type,_fprintf)(hashvsettype(type) table,FILE*fp) {\
    /* A Completer */\
    int i;\
    for(i=0;i<table->size;i++){\
        fprintf(fp, "Slot %d:",i);\
        if(table->data[i].busy==OCCUPED){table->print_key(table->data[i].key,fp);}\
        fprintf(fp, "\n");\
    }\
  }\
  void hashvsetfunction(type,_printf)(hashvsettype(type) table) {\
    hashvsetfunction(type,_fprintf)(table,stdout);\
  }

// Suppression d'un element;
#define makehashvsetremovekey(type) \
  int hashvsetfunction(type,_remove_key)(type key, hashvsettype(type) table) {\
    /* A Completer */\
    int slot=hashvsetfunction(type,_find_key)(key,table);\
    if(slot!=-1){\
      table->delete_key(table->data[slot].key);\
      table->data[slot].busy=FREE;\
      return 1; \
    }\
    return 0;\
  }


// Liberation de la table
#define makehashvsetdelete(type) \
  hashvsettype(type) hashvsetfunction(type,_delete)(hashvsettype(type) table) {\
    /* A Completer */\
    int i;\
    for(i=0;i<table->size;i++){\
      if(table->data[i].busy==OCCUPED){ table->delete_key(table->data[i].key);}\
    }\
    free(table->data);\
    return table;\
  }

////////////////////////////////
// Macro regroupant toutes les definitions de fonctions pour la creation de toutes
// les fonctions sur les hashvsetes. A utiliser dans hashvset_type.c.
#define makehashvsetfunction(type) \
makehashvsetnew(type)\
makehashvsetdelete(type)\
makehashvsetfindkey(type)\
 makehashvsetput(type)\
makehashvsetfprintf(type)\
makehashvsetremovekey(type)\
/*makehashvsetnewlength(type)\*/

// Macro regroupant toutes les declarations de fonctions
// A utiliser dans hashvset_type.h
#define makehashvsetproto(type) \
hashvsettype(type) hashvsetfunction(type,_new)(unsigned int n, \
    unsigned int (*fhachage)(type ), void (*print_key)(type, FILE*),\
        type (*delete_key)(type),\
        int (*compare_key)(type* e1, type* e2)) ;\
hashvsettype(type) hashvsetfunction(type,_delete)(hashvsettype(type) table);\
void hashvsetfunction(type,_printf)(hashvsettype(type) table) ;\
void hashvsetfunction(type,_fprintf)(hashvsettype(type) table,FILE*) ;\
int hashvsetfunction(type,_put)(type e, hashvsettype(type) table);\
int hashvsetfunction(type,_remove_key)(type e, hashvsettype(type) table);\
int hashvsetfunction(type,_find_key)(type key, hashvsettype(type) table);\

#endif
