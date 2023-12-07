#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/generic_queue.h"
#include "../include/mystring.h"

#define TAILLE_MAX 100000

int main(){

    FILE *ft = fopen("textes/sans_accents/test.txt", "r");
    FILE *fd = fopen("dictionnaire/dico1.txt", "r"); //verifier le mode
    if (ft == NULL || fd == NULL){
        printf("ouverture du texte ou du dictionnaire impossible\n");
        return 1;
    }


// Lecture du fichier
    char str[TAILLE_MAX];
    char* mot;
    mystring s;

    while(fgets (str, TAILLE_MAX, ft)!= NULL){
        mot = strtok(str, " \n.,:-;!?()'");
        while (mot!= NULL) {

            if(mot[0] != '"'){
              s=strdup(mot);
            mystring_fprintf(s,stderr); // C'est ici qu'il faut remplir la structure avec ou tester son existence dans le dictionnaire.
            printf("\n");
            mystring_delete(s); // la suppression peut se faire lors de la libération de la structure.
          }
            mot = strtok(NULL, " \n.,:;!?()'-");
        }
    }

// Lecture du dictionnaire
    char mot_dct[50];
    while(fgets (mot_dct, 50, fd)!= NULL){
        s=strndup(mot_dct,(strlen(mot_dct)-1)*sizeof(char));
        mystring_fprintf(s,stderr);
        printf("\n");
        mystring_delete(s); // la suppression aura lieu lors de la libération de la structure.
    }

    fclose(fd);
    fclose(ft);
    return 0;
}
