#ifndef _GENERIC_stack_H
#define _GENERIC_stack_H

#include <stdio.h>
#include<assert.h>
#include <stdlib.h>
#include <string.h>
////////////////////////
#include "genericcommon.h"
////////////////////////
#include "generic_list.h"

/////////////////////////
// Macro pour definir les noms des fonctions et des types

// Definition de nom du type des stackes, sous la forme stack_type_t
#define stacktype(type) makeid(makeid(stack_,type),_t)


// Definition du nom des fonctions, sous la forme stack_func
// func sera add_first, _del_first, etc...
#define stackfunction(type,func) makeid(makeid(stack_,type),func)

////////////////////////
// Definition des structures des stack par la macro makestacktype
// Comme c'est une liste, il faut d'abord creer
// le type list_type_t avec makevecttype
// puis définir le type stack_type_t à partir de ce type
#define makestacktype(type) \
  typedef listtype(type) stacktype(type);\

/////////////////////////////////
// Definition des fonctions de base sur les stacks
// On réutilise les fonctions sur les listes list_type....
// Creation d'une stack
#define makestacknew(type) \
  stacktype(type) stackfunction(type,_new)(\
          void (*fprint_data)(type,FILE*),\
          type (*delete_data)(type),\
          int (*equal_data)(type*,type*)) {\
     return listfunction(type,_new)(fprint_data,delete_data,equal_data);\
   }

// stacke vide ?
#define makestackisempty(type) \
  int  stackfunction(type,_is_empty)(stacktype(type) l) {\
    /* A Completer */\
     return listfunction(type,_isempty)(l);\
   }

// Ajout en tete
#define makestackpush(type) \
  stacktype(type) stackfunction(type,_push)(type* val, stacktype(type) l) { \
    return  listfunction(type,_add_first)(val, l);\
  }

#define makestackpop(type)\
  type stackfunction(type,_pop)(stacktype(type) l) { type res;\
    /* A Completer */\
    assert(!stackfunction(type,_is_empty)(l));\
    res= l->data->data;\
    l=listfunction(type,_del_first)(l);\
      return res;\
  }

#define makestackpeek(type)\
  type stackfunction(type,_peek)(stacktype(type) l) { \
    /* A Completer */\
    assert(!stackfunction(type,_is_empty)(l));\
    return l->data->data;\
  }

// Liberation de la stacke
#define  makestackdelete(type) \
  stacktype(type) stackfunction(type,_delete)(stacktype(type) l) { \
    /* A Completer */\
    return listfunction(type,_delete)(l);\
  }

// Affichage de la stacke
// Utilise la fonction d'affichage des objets nommee type_fprint qui doit etre defini pour tous les objets
// y compris pour les types de base comme int, double, etc...
// Affichage de la stacke dans un fichier stack_type_fprintf(FILE*,stack_type_t *)
#define makestackfprintf(type)\
  void stackfunction(type,_fprintf)(stacktype(type) l,FILE* fp) { \
    /* A Completer */\
    listfunction(type,_fprintf)(l,fp);\
  }

// Affichage de la stacke a l'ecran : juste un appel a la fonction precedente
#define makestackprintf(type) void stackfunction(type,_printf)(stacktype(type) l) { \
  /* A Completer */\
  stackfunction(type,_fprintf)(l,stdout);\
  }

// longueur de la stacke
#define makestacklength(type)\
  unsigned int stackfunction(type,_length)(stacktype(type) l ) { \
    /* A Completer */\
    return listfunction(type,_length)(l);\
  }

////////////////////////////////
// Macro regroupant toutes les definitions de fonctions pour la creation de toutes
// les fonctions sur les stackes. A utiliser dans stack_type.c.
#define makestackfunction(type) \
makestacknew(type)\
makestackpeek(type)\
makestackisempty(type)\
makestackpush(type)\
makestackpop(type)\
makestackdelete(type)\
makestackfprintf(type)\
makestackprintf(type)\
makestacklength(type)\

// Macro regroupant toutes les declarations de fonctions
// A utiliser dans stack_type.h
#define makestackproto(type) \
stacktype(type) stackfunction(type,_new)(void (*fprint_data)(type,FILE*),type (*delete_data)(type),int (*equal_data)(type*,type*)) ;\
type  stackfunction(type,_peek)(stacktype(type) l);\
int stackfunction(type,_is_empty)(stacktype(type) l) ;\
stacktype(type) stackfunction(type,_push)(type* val, stacktype(type) l) ;\
type stackfunction(type,_pop)(stacktype(type) l);\
stacktype(type) stackfunction(type,_delete)(stacktype(type) l);\
void stackfunction(type,_fprintf)(stacktype(type) l,FILE* fp);\
void stackfunction(type,_printf)(stacktype(type) l);\
unsigned int stackfunction(type,_length)(stacktype(type) l ) ;\

#endif
