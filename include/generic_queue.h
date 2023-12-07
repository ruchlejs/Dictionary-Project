#ifndef _GENERIC_queue_H
#define _GENERIC_queue_H
////////////////////////
#include "genericcommon.h"
#include "generic_list.h"

/////
///// iL est necessaire d'avoir les list_t disponibles
///// donc le programme qui utilise les files doit faire
///// un makelisttype(type)
/////////////////////////

// Definition de nom du type des files, sous la forme queue_type_t
#define queuetype(type) makeid(makeid(queue_,type),_t)

// Definition du nom des fonctions, sous la forme queue_type_func ou link_type_func
// func sera add_first, _del_first, etc...
#define queuefunction(type,func) makeid(makeid(queue_,type),func)

////////////////////////
// Definition des structures des files par la macro makequeuetype
// C'est juste le typedef classique des files, avec
// un champ data pour la liste de maillons
// un champ size pour la taille
// et les pointeurs de fonctions utiles
// Le nom de la structure est queue_type_t
/// Une queue est une liste générique circulaire
/// Attention, la liste est circulaire, le champ data de lsit_type_t
/// doit pointer sur le dernier élément de la liste
#define makequeuetype(type) \
  typedef makeid(makeid(list_,type),_t) makeid(makeid(queue_,type),_t);

/////////////////////////////////
// Definition des fonctions de base sur les files
// Creation d'une file
#define makequeuenew(type) \
  queuetype(type) queuefunction(type,_new)(\
          void (*fprint_data)(type,FILE*),\
          type (*delete_data)(type),\
          int (*equal_data)(type*,type*)) {\
     /* A completer */\
     queuetype(type) q;\
     q=listfunction(type,_new)(fprint_data,delete_data,equal_data);\
     return q;\
   }

// file vide ?
#define makequeueisempty(type) \
  int queuefunction(type,_is_empty)(queuetype(type) l) {\
     return l==NULL || l->size==0 || l->data==NULL;\
   }

// Retourne Le premier maillon de la file, sachant que le dernier est donné par l->data
// C'est un maillon et pas une valeur
#define makequeuefirst(type) \
  linktype(type)  queuefunction(type,_first)(queuetype(type) l) {\
     return l->data->next;\
  }

 // Ajoute l'élément val en fin de la file et retourne la nouvelle queue
 // Allocation d'un maillon, ajoute ce maillon a la liste circulaire
 // dont le dernier maillon est pointé par l->data ....
 // Retourne la queue NON MODIFIEE en cas d'erreur
#define makefilenqueue(type) \
  queuetype(type) queuefunction(type,_enqueue)(type* val, queuetype(type) l) { \
    /* A completer */\
    if(!queuefunction(type,_is_empty)(l)){\
    linktype(type) link= linkfunction(type,_add_first)(val,l->data->next);\
    l->data->next=link;\
    l->data=link;\
    l->size++;\
  }\
  else{\
    linktype(type) link = linkfunction(type,_add_first)(val,NULL);\
    link->next=link;\
    l->data=link;\
    l->size++;\
  }\
    return l;\
  }

  // Supprime le maillon en tête de file et retourne l'element
  // Ne LIBERE PAS l'element, puisqu'il est retourné
  // PRECONDITION : queue non vide
#define makequeuedequeue(type)\
  type queuefunction(type,_dequeue)(queuetype(type) l) { \
    /* A completer */\
    assert(!queuefunction(type,_is_empty)(l));\
    linktype(type) link=l->data->next;\
    type res=link->data;\
    l->data->next=link->next; /*Peut être problème si nul*/\
    free(link);\
    l->size--;\
    return res;\
  }

// Libère toute la file et retourne une file vide
// Libère aussi les éléments
#define  makequeuedelete(type) \
  queuetype(type) queuefunction(type,_delete)(queuetype(type) l) { \
    /* A Completer */\
    while(l->data!=l->data->next){\
      type res= queuefunction(type,_dequeue)(l);\
      l->delete_data(res);\
    }\
    type res= queuefunction(type,_dequeue)(l);\
    l->delete_data(res);\
    return l;\
  }

// Affichage de la file
#define makequeuefprintf(type)\
  void queuefunction(type,_fprintf)(queuetype(type) l,FILE* fp) { \
    /* A Completer */\
    linktype(type) link;\
   if(!queuefunction(type,_is_empty)(l)){\
     link=l->data->next;\
     do{\
       l->fprint_data(link->data,fp);\
       link=link->next;\
     }while(link!=l->data->next);\
   }\
  }
// Affichage de la file a l'ecran : juste un appel a la fonction precedente
#define makequeueprintf(type) void queuefunction(type,_printf)(queuetype(type) l) { \
    queuefunction(type,_fprintf)(l,stdout);\
  }

// lobgueur de la file
#define makequeuelength(type)\
  unsigned int queuefunction(type,_length)(queuetype(type) l ) { \
    return l->size;\
  }



////////////////////////////////
// Macro regroupant toutes les definitions de fonctions pour la creation de toutes
// les fonctions sur les files. A utiliser dans queue_type.c.
#define makequeuefunction(type)\
makequeuenew(type)\
\
makequeuefirst(type)\
\
makequeueisempty(type)\
\
makefilenqueue(type)\
\
makequeuedequeue(type)\
\
makequeuedelete(type)\
\
makequeuefprintf(type)\
\
makequeueprintf(type)\
\
makequeuelength(type)\
\

// Macro regroupant toutes les declarations de fonctions
// A utiliser dans queue_type.h
#define makequeueproto(type)\
queuetype(type) queuefunction(type,_new)(void (*fprint_data)(type,FILE*),type (*delete_data)(type),int (*equal_data)(type*,type*)) ;\
linktype(type)  queuefunction(type,_first)(queuetype(type) l);\
int queuefunction(type,_is_empty)(queuetype(type) l) ;\
queuetype(type) queuefunction(type,_enqueue)(type* val, queuetype(type) l) ;\
type queuefunction(type,_dequeue)(queuetype(type) l);\
queuetype(type) queuefunction(type,_delete)(queuetype(type) l);\
void queuefunction(type,_fprintf)(queuetype(type) l,FILE* fp);\
void queuefunction(type,_printf)(queuetype(type) l);\
unsigned int queuefunction(type,_length)(queuetype(type) l ) ;\

#endif
