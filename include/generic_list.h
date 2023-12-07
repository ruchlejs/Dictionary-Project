#ifndef _GENERIC_LIST_H
#define _GENERIC_LIST_H
////////////////////////
#include "genericcommon.h"

/////////////////////////
// Macro pour definir les noms des fonctions et des types

// Definition de nom du type des listes, sous la forme list_type_t
#define listtype(type) makeid(makeid(list_,type),_t)
// Idem pour les maillons
#define linktype(type) makeid(makeid(link_,type),_t)

// Definition du nom des fonctions, sous la forme list_func ou link_func
// func sera add_first, _del_first, etc...
#define listfunction(type,func) makeid(makeid(list_,type),func)
#define linkfunction(type,func) makeid(makeid(link_,type),func)

////////////////////////
// Definition des structures des listes par la macro makelisttype
// D'abord les maillons, avec
// un champ data pour l'objet contenu dans la liste : un double, une structure, un tableau, un pointeur....
// un champ next pour le pointeur sur le suivant
// Le nom de la structure est link_type_t
//
// Puis la structure de liste avec un pointeur sur le premier maillon data
// la taille
// et les pointeurs de fonctions pour gérer les éléments
#define makelisttype(type) \
  /* Le maillon */ \
  typedef struct makeid(link_,type) { \
    type data;\
    struct makeid(link_,type)* next; \
  }  * makeid(makeid(link_,type),_t);  \
  \
  /* La liste */\
  typedef struct makeid(list_,type) { \
    makeid(makeid(link_,type),_t) data;\
    unsigned int size;\
    void (*fprint_data)(type,FILE*);\
    type (*delete_data)(type);\
    int (*equal_data)(type*,type*);\
  }  * makeid(makeid(list_,type),_t);

/////////////////////////////////
// Definition des fonctions de base sur les listes
// Creation d'une liste
// data est NULL, size est 0.
#define makelistnew(type) \
  listtype(type) listfunction(type,_new)(\
          void (*fprint_data)(type,FILE*),\
          type (*delete_data)(type),\
          int (*equal_data)(type*,type*)) {\
     listtype(type) p = malloc(sizeof(*p));\
     if(p) {\
       p->size=0;\
       p->data=NULL;\
       p->fprint_data=fprint_data;\
       p->delete_data=delete_data;\
       p->equal_data=equal_data;\
     }\
     return p;\
   }

// Liste vide et link vide?
#define makelistisempty(type) \
  \
  int linkfunction(type,_isempty)(linktype(type) l) {\
     return l==NULL;\
   }\
  int listfunction(type,_isempty)(listtype(type) l) {\
     return l==NULL || l->size==0 || l->data==NULL;\
   }
// Le premier maillon de la liste
#define makelistfirst(type) \
  linktype(type)  listfunction(type,_first)(listtype(type) l) {\
     return l->data;\
   }
// Le maillon suivant d'un link et non d'un list
#define makelistnext(type) \
  linktype(type)  listfunction(type,_next)(linktype(type) l) {\
     return l->next;\
   }

// Ajout en tete
// Ici, on définit à la fois list_type_add_first et link_type_add_first
// Car link_type_add_first est la fonction classique qui sera réutilisée
// plusieurs fois.
#define makelistaddfirst(type) \
  linktype(type) linkfunction(type,_add_first)(type* val, linktype(type) l) { \
    linktype(type) p;\
    p = calloc(1,sizeof(*p));\
    if (p==NULL) return l;\
    p->data=*val;\
    p->next=l;\
    return p;\
  }\
  listtype(type) listfunction(type,_add_first)(type* val, listtype(type) l) { \
    linktype(type) p = linkfunction(type,_add_first)(val,l->data);\
    if (p!=l->data) {\
      l->data=p;\
      (l->size)++;\
    } \
    return l;\
  }

// Ajout en queue
#define makelistaddlast(type) \
  listtype(type) listfunction(type,_add_last)(type* val, listtype(type) l) { \
    /* A Completer */\
    linktype(type) p=l->data;\
    if(listfunction(type,_isempty)(l)){\
      l->data=linkfunction(type,_add_first)(val,NULL);\
      l->size++;\
      return l;\
    }\
    while(!linkfunction(type,_isempty)(p->next)){\
      p=p->next;\
    }\
    p->next=linkfunction(type,_add_first)(val,NULL);\
    l->size++;\
    return l;\
  }

// Suppression en tete
// Idem que ajout en tete, link_type_del_first est la fonction classique qui sera réutilisée
// plusieurs fois.
// list_type_del_first est simplement un appel a cette fonction, avec mise a jour de size.
#define makelistdelfirst(type)\
  \
  linktype(type) linkfunction(type,_del_first)(linktype(type) l,type (*delete_data)(type)) { \
    /* A Completer */\
    linktype(type) p;\
    p = l->next;\
    if(delete_data!=NULL) delete_data(l->data);\
    free(l);\
    return p;\
  }\
  listtype(type) listfunction(type,_del_first)(listtype(type) l) { \
    /* A Completer */\
    if(!listfunction(type,_isempty)(l)){\
      linktype(type) p = linkfunction(type,_del_first)(l->data,l->delete_data);\
      if (p!=l->data) {\
        l->data=p;\
        (l->size)--;\
      }  \
    }\
    return l;\
  }

#define makelistdellast(type) \
  listtype(type) listfunction(type,_del_last)(listtype(type) l) { \
    /* A Completer */\
    if(listfunction(type,_isempty)(l)) return l;\
    linktype(type) p=l->data;\
    if(linkfunction(type,_isempty)(p->next)) return l=listfunction(type,_del_first)(l);\
    while(!linkfunction(type,_isempty)(p->next->next)){\
      p=p->next;\
    }\
    if(l->delete_data!=NULL) l->delete_data(p->next->data);\
    free(p->next);\
    p->next=NULL;\
    l->size--;\
    return l;\
  }

// Liberation de la liste
#define  makelistdelete(type) \
  listtype(type) listfunction(type,_delete)(listtype(type) l) { \
    /* A Completer */\
    while(!listfunction(type,_isempty)(l)){\
      l=listfunction(type,_del_first)(l);\
    }\
    return l;\
  }

// Affichage de la liste
// Affichage de la liste dans un fichier list_type_fprintf(FILE*,list_type_t *)
#define makelistfprintf(type)\
  void listfunction(type,_fprintf)(listtype(type) l,FILE* fp) { \
    /* A Completer */\
    linktype(type) p;\
    p=l->data;\
    while(!linkfunction(type,_isempty)(p)){\
      l->fprint_data(p->data,fp);\
      p=p->next;\
    }\
    fprintf(fp,"\n");\
  }
// Affichage de la liste a l'ecran : juste un appel a la fonction precedente
#define makelistprint(type) void listfunction(type,_printf)(listtype(type) l) { \
    listfunction(type,_fprintf)(l,stdout);\
  }

// longueur de la liste
#define makelistlength(type)\
  unsigned int listfunction(type,_length)(listtype(type) l ) { \
    return l->size;\
  }

// Recherche d'un element dans une liste avec la fonction equal de la liste
#define makelistfind(type)\
  linktype(type) listfunction(type,_find)(type* param, listtype(type) l ) { \
    linktype(type) p;\
    for (p=l->data; !linkfunction(type,_isempty)(p);p=p->next) {\
      if (l->equal_data ? l->equal_data(&p->data,param)!=0 : memcmp(param,&p->data,sizeof(type))==0)\
        return p;\
    }\
    return NULL;\
  }

// Recherche selon un critere dans une liste
#define makelistlookup(type)\
  linktype(type) listfunction(type,_lookup)( type* param,  listtype(type) l, int (*equal)(type*,type*)) { \
    /* A complete */\
    linktype(type) p;\
    for (p=l->data; !linkfunction(type,_isempty)(p);p=p->next) {\
      if (equal(&p->data,param)!=0 )\
        return p;\
    }\
    return NULL;\
  }

// Suppression selon le critere equal_data dans une liste. Si le critere n'est pas donne, alors on compare les valeurs
// avec memcmp de la liste.
#define makelistremove(type)\
  listtype(type) listfunction(type,_remove)(type* param, listtype(type) l) { \
    /* A Completer*/\
    return l;\
  }

// Visiteur simple : parcourt la liste et execute une fonction sur chaque maillon
// Version simple du visiteur suivant, presente pour des questions pedagogiques
// La fonction qui est executee prend l'adresse de la valeur contenue dans le maillon en premier argument
// et un deuxieme pointeur si besoin : elle execute une action (affichage ou autre).
// Pas de valeur de retour
#define makelistsimplevisit(type)\
  void listfunction(type,_simple_visit)(listtype(type) l, void (*action)(type,void*), void* param) { \
    linktype(type) p;\
    for (p=l->data; !linkfunction(type,_isempty)(p);p=p->next)\
       action(p->data,param);\
  }

// Visiteur complet : parcourt la liste
// Execute une fonction qui a une action sur la valeur contenue dans le maillon
// (exemple : compter le nombre de maillon ayant une valeur donnee)
// cette fonction prend l'adresse de la valeur contenue dans le maillon en premier argument, l'adresse d'un autre parametre si besoin
// Execute une fonction qui a une action sur le maillon lui-meme (exemple : liberer le maillon)
// cette fonction prend l'adresse du maillon en premier argument,  l'adresse d'un autre parametre si besoin
#define makelistvisit(type)\
  int listfunction(type,_visit)(listtype(type) l, \
        int (*exec_on_value)(type*,type*),\
        int (*exec_on_link)(linktype(type),type*),type* param ) { \
    linktype(type) p=l->data, pnext;\
    int ret=0; \
    while (!linkfunction(type,_isempty)(p)) {\
      pnext=p->next;\
      ret += exec_on_value ? (int)exec_on_value(&( p->data ), param ) : 0;\
      ret += exec_on_link  ? (int)exec_on_link(p,param) : 0;\
      p=pnext;\
    }\
    return ret;\
  }

////////////////////////////////
// Macro regroupant toutes les definitions de fonctions pour la creation de toutes
// les fonctions sur les listes. A utiliser dans list_type.c.
#define makelistfunction(type) \
makelistnew(type)\
 makelistnext(type)\
 makelistfirst(type)\
 makelistisempty(type)\
 makelistaddfirst(type)\
 makelistaddlast(type)\
makelistdelfirst(type)\
makelistdellast(type)\
 makelistdelete(type)\
makelistfprintf(type)\
 makelistprint(type)\
 makelistfind(type)\
 makelistlookup(type)\
 makelistlength(type)\


// Macro regroupant toutes les declarations de fonctions
// A utiliser dans list_type.h
#define makelistproto(type) \
listtype(type) listfunction(type,_new)(void (*fprint_data)(type,FILE*),type (*delete_data)(type),int (*equal_data)(type*,type*)) ;\
linktype(type)  listfunction(type,_first)(listtype(type) l);\
linktype(type)  listfunction(type,_next)(linktype(type) l);\
int listfunction(type,_isempty)(listtype(type) l) ;\
listtype(type) listfunction(type,_add_first)(type* val, listtype(type) l) ;\
listtype(type) listfunction(type,_add_last)(type* val, listtype(type) l) ;\
listtype(type) listfunction(type,_del_last)(listtype(type) l);\
listtype(type) listfunction(type,_del_first)(listtype(type) l);\
listtype(type) listfunction(type,_delete)(listtype(type) l);\
void listfunction(type,_fprintf)(listtype(type) l,FILE* fp);\
void listfunction(type,_printf)(listtype(type) l);\
int listfunction(type,_visit)(listtype(type) l, int (*exec_on_value)(type*,type*), int (*exec_on_link)(linktype(type),type*),type* param);\
linktype(type) listfunction(type,_lookup)(type* param, listtype(type) l, int (*equal)(type*,type*));\
void listfunction(type,_simple_visit)(listtype(type) l, void (*action)(type,void*), void* param);\
linktype(type) listfunction(type,_find)(type* param, listtype(type) l );\
listtype(type) listfunction(type,_remove)(type* param, listtype(type) l);\
unsigned int listfunction(type,_length)(listtype(type) l ) ;\

#endif
