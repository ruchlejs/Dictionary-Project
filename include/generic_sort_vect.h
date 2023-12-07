#ifndef _GENERIC_SORT_VECT_H
#define _GENERIC_SORT_VECT_H

////////////////////////
#include "genericcommon.h"
#include "generic_vect.h"
#include "generic_heap.h"
////////////////////////

#define makevectverifsort(type)\
  int vectfunction(type,_verif_sort)(vecttype(type) tab) { \
    int i;\
    for (i=0; i<tab->actual_size-1; i++){ \
      if (tab->equal_data(tab->data+i,tab->data+i+1) >0) return 0; \
    }\
    return 1;\
  }

#define makevectheapsort(type)\
  heaptype(type) vectfunction(type,_heapsort)(vecttype(type) tab) { \
    /* A Completer */\
    heaptype(type) tas = heapfunction(type,_new)(tab->max_size,tab->fprint_data,tab->delete_data,tab->equal_data);\
    int i;\
    for(i=0;i<tab->actual_size;i++){\
      heapfunction(type,_add)(tab->data[i],tas);\
    }\
    type m;\
    int k= tas->actual_size;\
    while(tas->actual_size>0){\
      m=heap_mystring_get_extrema(tas);\
      heap_mystring_delete_extrema(tas);\
      tas->data[tas->actual_size]=m;\
  }\
  tas->actual_size=k;\
  return tas;\
}

#define makevectquicksort(type)\
  static int vectfunction(type,_part)(vecttype(type) tableau, int l, int h) {\
      /* A Completer */\
      int i = l-1;\
      int j;\
      for (j = l; j <= h- 1; j++){\
        if(tableau->equal_data(tableau->data+j,tableau->data+l) <=0){\
            i++;\
            type t;\
            t=tableau->data[i];\
            tableau->data[i]=tableau->data[j];\
            tableau->data[j]=t;\
        }\
      }\
      return l+rand()% (h+1-l);\
  }\
  void vectfunction(type,_quick_sort)(vecttype(type) tableau, int l, int h) { \
    /* A Completer */\
  if(l<h){\
    int p=vectfunction(type,_part)(tableau,l,h);\
    vectfunction(type,_quick_sort)(tableau,l,p-1);\
    vectfunction(type,_quick_sort)(tableau,p+1,h);\
   }\
  }\
  void vectfunction(type,_qsort)(vecttype(type) tableau) {\
    /* A COmpleter : fonction wrapper */\
    vectfunction(type,_quick_sort)(tableau,0,tableau->actual_size-1);\
  }

#define makevectmergesort(type)\
  static void vectfunction(type,_fusion)(vecttype(type) table, vecttype(type) res, int gauche, int droite) { \
    /* A completer */\
    int milieu =(gauche +droite)/2;\
    int i = gauche;\
    int j = milieu+1;\
    int k = 0;\
    while (i <= milieu && j <= droite) {\
          if (table->equal_data(table->data+i,table->data+j)<= 0) {\
              res->data[k] = table->data[i];\
              i++;\
          }\
          else {\
              res->data[k] = table->data[j];\
              j++;\
          }\
          k++;\
      }\
      while (i <= milieu) {\
          res->data[k] = table->data[i];\
          k++;\
          i++;\
      }\
      while (j <= droite) {\
          res->data[k] = table->data[j];\
          k++;\
          j++;\
      }\
    for (i = gauche; i <=droite; i++) {\
        table->data[i] = res->data[i - gauche];\
     }\
  }\
  static void vectfunction(type,_trifusion)(vecttype(type) table, vecttype(type) res, int gauche, int droite) { \
    /* A Completer */\
    if(gauche<droite){\
      int milieu = (gauche + droite)/2;\
      vectfunction(type,_trifusion)(table,res,gauche,milieu);\
      vectfunction(type,_trifusion)(table,res,milieu+1,droite);\
      vectfunction(type,_fusion)(table,res,gauche,droite);\
    }\
  }\
  void vectfunction(type,_mergesort)(vecttype(type) table) {\
    /* A completer : fonction wrapper */\
    vecttype(type) res =vectfunction(type,_new)(table->actual_size,mystring_fprintf,mystring_delete,mystring_equal);\
    vectfunction(type,_trifusion)(table,res,0,table->actual_size-1);\
    res=vect_mystring_delete(res);\
  }

////////////////////////////////
// Macro regroupant toutes les definitions de fonctions pour la creation d
#define makesortvectfunction(type) \
 makevectheapsort(type)\
 makevectverifsort(type)\
makevectquicksort(type)\
 makevectmergesort(type)\


// Macro regroupant toutes les declarations de fonctions
// A utiliser dans vect_type.h
#define makesortvectproto(type) \
void vectfunction(type,_qsort)(vecttype(type) tableau) ;\
void vectfunction(type,_mergesort)(vecttype(type) tableau) ;\
heaptype(type) vectfunction(type,_heapsort)(vecttype(type) tab);\
int vectfunction(type,_verif_sort)(vecttype(type) tab);\

#endif
