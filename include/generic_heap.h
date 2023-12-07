#ifndef _GENERIC_heap_H
#define _GENERIC_heap_H
////////////////////////
#include "genericcommon.h"

////////////////////////
#include "generic_vect.h"

/////////////////////////
// Macro pour definir les noms des fonctions et des types

// Definition de nom du type des heaps, sous la forme heap_type_t
#define heaptype(type) makeid(makeid(heap_,type),_t)

// Definition du nom des fonctions, sous la forme heap_func
// func sera _new, _del_first, etc...
#define heapfunction(type,func) makeid(makeid(heap_,type),func)

// Pour retrouver facilemetn les indices des peres et fils
#define HEAP_FATHER(i) ( ((i)-1)/2)
#define HEAP_LEFTSON(i) ( 2*(i)+1)
#define HEAP_RIGHTSON(i) ( 2*((i)+1))

////////////////////////
// Definition des structures des heaps par la macro makeheaptype
// Le nom de la structure est heap_type_t
// et est un vect_type_t

#define makeheaptype(type) typedef vecttype(type) heaptype(type);

/////////////////////////////////
// Definition des fonctions de base sur les heaps
// Creation d'un heap de n elements vide
// Allocation du tableau de n elements, taille actuelle nulle.
#define makeheapnew(type) \
  heaptype(type) heapfunction(type,_new)(unsigned int n, \
        void (*fprint_data)(type,FILE*),\
        type (*delete_data)(type),\
        int (*equal_data)(type*,type*)) {\
  heaptype(type) heap= vectfunction(type,_new)(n, fprint_data, delete_data, equal_data);\
  return heap;\
  }

// Ajout d'un element
// Augmente la taille du tableau si necessaire
#define makeheapadd(type) \
  int heapfunction(type,_add)(type e, heaptype(type) tas)  {\
    /* A Completer */\
    if(tas->actual_size==tas->max_size){\
      tas->max_size*=2;\
      tas->data=realloc(tas->data,sizeof(type)*(tas->max_size));\
      if(tas->data==NULL)\
        return 0;\
    }\
    tas->data[tas->actual_size]=e;\
    tas->actual_size++;\
    int i=tas->actual_size-1;\
    int j;\
    type f;\
    while(i>0){\
      j=HEAP_FATHER(i);\
      if(tas->equal_data(&tas->data[j],&tas->data[i])<0){\
        f=tas->data[j];\
        tas->data[j]=tas->data[i];\
        tas->data[i]=f;\
      }\
      i=j;\
    }\
    return 1;\
    }

#define makeheapempty(type) \
  int heapfunction(type,_is_empty)(heaptype(type) tas) {\
    /* A Completer */\
    if(tas->actual_size==0)\
      return 1;\
    return 0;\
  }


// Affichage
#define makeheapfprint(type) \
  void heapfunction(type,_fprintf)(heaptype(type) tas,FILE* fp) {\
    /* A Completer */\
    int i;\
    for(i=0;i<tas->actual_size;i++){\
      tas->fprint_data(tas->data[i],fp);\
    }\
    fprintf(fp, "\n");\
  }

#define makeheapprint(type) \
  void heapfunction(type,_printf)( heaptype(type) table) {\
    /* A Completer */\
    heapfunction(type,_fprintf)(table,stdout);\
  }


// Liberation de la table
#define makeheapdelete(type) \
  heaptype(type) heapfunction(type,_delete)(heaptype(type) tas) { \
    return vectfunction(type,_delete)(tas);\
  }

#define makeheapgetmax(type) \
  type heapfunction(type,_get_extrema)(heaptype(type) tas) {\
    /* A Completer */\
    return tas->data[0];\
  }
//ATTENTION, ne supprime pas l'extrema
#define makeheapdelmax(type) \
  static int heapfunction(type,_largest_son)(heaptype(type) tas, int indice) {\
    /* A Completer */\
    if(tas->equal_data(&tas->data[HEAP_RIGHTSON(indice)],&tas->data[HEAP_LEFTSON(indice)])>0)\
      return HEAP_RIGHTSON(indice);\
    else\
      return HEAP_LEFTSON(indice);\
  }\
  \
  int heapfunction(type,_delete_extrema)(heaptype(type)  tas) { \
    /* A Completer */\
    type t;\
    /*t=tas->data[0];\\
    tas->delete_data(tas->data[0]);\*/\
    tas->data[0]=tas->data[tas->actual_size-1];\
    tas->actual_size-=1;\
    int i,j;\
    i=0;\
    while(HEAP_LEFTSON(i)<tas->actual_size){\
      j=heapfunction(type,_largest_son)(tas,i);\
      if(tas->equal_data(&tas->data[j],&tas->data[i])>0){\
        t=tas->data[j];\
        tas->data[j]=tas->data[i];\
        tas->data[i]=t;\
        i=j;\
      }\
      else\
        return 1;\
    }\
    return 1;\
  }

#define makeheapverif(type) \
  int heapfunction(type,_verification)(heaptype(type) tas) {\
    int i;\
    for (i=0; i< tas->actual_size/2; i++) {\
    if (tas->equal_data(tas->data+i,tas->data+HEAP_LEFTSON(i))<0) return i;\
      if (HEAP_RIGHTSON(i)<tas->actual_size && tas->equal_data(tas->data+i,tas->data+HEAP_RIGHTSON(i))<0) return i;\
    }\
    return -1;\
  }

////////////////////////////////
// Macro regroupant toutes les definitions de fonctions pour la creation de toutes
// les fonctions sur les heapes. A utiliser dans heap_type.c.
#define makeheapfunction(type) \
makeheapnew(type)\
makeheapadd(type)\
makeheapdelete(type)\
makeheapdelmax(type)\
makeheapgetmax(type)\
makeheapverif(type)\
makeheapfprint(type)\
makeheapprint(type)\
makeheapempty(type)\

// Macro regroupant toutes les declarations de fonctions
// A utiliser dans heap_type.h
#define makeheapproto(type) \
heaptype(type) heapfunction(type,_new)(unsigned int n, \
      void (*fprintf_data)(type,FILE*),\
      type (*delete_data)(type),\
      int (*equal_data)(type*,type*));\
int heapfunction(type,_add)(type e, heaptype(type) table)  ;\
void heapfunction(type,_printf)(heaptype(type) table);\
void heapfunction(type,_fprintf)( heaptype(type) table,FILE*);\
heaptype(type) heapfunction(type,_delete)(heaptype(type) table);\
int heapfunction(type,_verification)(heaptype(type) tas);\
int heapfunction(type,_delete_extrema)(heaptype(type)  tas);\
type heapfunction(type,_get_extrema)(heaptype(type) tas);\
int heapfunction(type,_is_empty)(heaptype(type) tas);\

#endif
