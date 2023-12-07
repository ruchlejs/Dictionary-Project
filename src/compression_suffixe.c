#include "../include/compression_suffixe.h"
#include "../include/generic_hashlset.h"
#include "../include/generic_vect.h"

/*
    Les fonctions utilsants les hashlset on du être commenté car elle crée des multiples définitions lors de la compilation.
    A CORRIGER
*/


// makehashlsettype(mystring)
// makehashlsetfunction(mystring)
// makehashlsetproto(mystring)

// makevecttype(mystring)
// makevectproto(mystring)
// makevectfunction(mystring)


tree_t compression(tree_t arbre){
    // Structure de donnée regroupant les suffixes déjà rencontré. On a choisit de le faire sous forme d'ensemble pour avoir une recherche rapide.
    //devrait être en dehors de la fonction mais ne peut pas être défini en dehors. A CORRIGER.

    //hashlset_mystring_t suffixe_rencontre = hashlset_mystring_new(10, fhashchage, mystring_fprintf, mystring_delete, mystring_equal);
    
    
    tree_t arbre_compresse;

    //  1) Elle compresse les fils ou les fils et le frere ainé selon la structure lexicographique
    if( !isemptytree(arbre->son) ){
        arbre_compresse = compression(arbre->son);
    }
    if( !isemptytree(arbre->brother) ){
        arbre_compresse = compression(arbre->brother);
    }

    /*  2) Elle cherche dans une structure de données des suffixes déjà rencontrés (à définir par vous même) 
    si un sous-arbre commencant avec la même lettre et les mêmes fils a déjà été rencontré, 
    c'est à dire si le suffixe formé par le noeud en cours de compression et ses fils sont un suffixe déjà rencontré.*/
    int present = 1;
    char suffixe[50];
    int i = 0;

    tree_t temp = arbre;
    for(i = 0; !isemptytree(temp->son);i++){
        suffixe[i] = arbre->value;
        temp = temp->son;
    }

    // if(hashvset_tree_t_find_key(suffixe,suffixe_rencontre) == -1){
    //     present = 0;
    // }

    /*  3)Si ce sous-arbre existe déjà, elle détruit le noeud (mais pas les fils) en cours de compression
        et retourne le sous-arbre déjà rencontré,*/
    if(present){
        free(arbre);
        
        return arbre;
    }
    else{
        /*  4)Sinon, elle rajoute ce noeud à la structure de données des suffixes déjà rencontrés
            et retourne le noeud compressé.*/

        // hashvset_tree_t_put(suffixe,suffixe_rencontre);

        return arbre;
    }   
}
