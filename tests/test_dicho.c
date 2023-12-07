#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/generic_queue.h"
#include "../include/mystring.h"
#define TAILLE_MAX 511

//https://pixees.fr/informatiquelycee/n_site/isn_dicho_algo.html


makelisttype(mystring)
makelistproto(mystring)
makelistfunction(mystring)

makequeuetype(mystring)
makequeueproto(mystring)
makequeuefunction(mystring)

/*

void mystring_fprintf(mystring v,FILE* fp) { fprintf(fp,"%s ",v); }
mystring mystring_delete(mystring p) {
  free(p);
  return NULL;
}
int mystring_equal(mystring* v1, mystring* v2){ return strcmp(*v1,*v2)==0;}
void* mystring_new(mystring val) {return strdup(val);}*/

//Mis en commentaire afin de controler que le make total ne fait pas derreur
/* int dichotomique(char* mot_txt, queue_mystring_t dct){

    if(mot_txt[0] >= 'A' && mot_txt[0]<='Z') return 0;

    int bas = 0; int haut =dct->size;
    //va voir test_double_queue, on utilise pas cette fontion comme ca
    char *mot_milieu = *(char**)queue_mystring_enqueue(dct, haut/2);


    while(strcasecmp(mot_txt,mot_milieu)!=0){
        if(strcasecmp(mot_txt,mot_milieu)>0){
            bas = (haut + bas)/2;
            mot_milieu = *(char**)queue_mystring_enqueue(dct, (haut + bas)/2);
        }
        else{
            haut = (haut+bas)/2;
            mot_milieu = *(char**)queue_mystring_enqueue(&dct, (haut + bas)/2);
        }
        if((haut-bas)<=1 && strcasecmp(mot_txt,mot_milieu) != 0){
            return 1;
        }

    }
    return 0;
}*/
const int BAR_LENGHT=30;
void update_bar(int pc){
    int i=0;
    int num_char = pc*BAR_LENGHT/100;
    printf("\r[");
    for(i=0;i<num_char;i++){
        printf("#");
    }
    for(i=0;i<BAR_LENGHT-num_char;i++){
        printf(" ");
    }
    printf("] %d%% done", pc);
    fflush(stdout);
}

int iteratif(char* mot_txt, queue_mystring_t dct){

    if(mot_txt[0] >= 'A' && mot_txt[0]<='Z') return 0;


    int k = 0;
    link_mystring_t p = queue_mystring_first(dct);

    while(strcasecmp(mot_txt,*(char**)p)>0 && k<dct->size){
        k++;
        p = p->next;
    }

    if(strcasecmp(*(char**)p,mot_txt) != 0){ return 1;}
    return 0;
}


int main(){


//début remplissage des tableaux
    //char mot_txt[TAILLE_MAX];

    //FILE *ft = fopen("textes/sans_accents/a_la_recherche_du_temps_perdu.txt", "r");
    FILE *ft = fopen("textes/sans_accents/test.txt", "r");

    FILE *fd = fopen("dictionnaire/dico1.txt", "r"); //verifier le mode
    if (ft == NULL || fd == NULL){
        printf("ouverture du texte ou du dictionnaire impossible\n");
        return 1;
    }

    char str[TAILLE_MAX];
    char* mot;
    mystring s;
    queue_mystring_t txt=queue_mystring_new(mystring_fprintf,mystring_delete,mystring_equal); //liste des mots du textes
    queue_mystring_t dct=queue_mystring_new(mystring_fprintf,mystring_delete,mystring_equal);//liste des mots du dictionnaires
    queue_mystring_t err=queue_mystring_new(mystring_fprintf,mystring_delete,mystring_equal);//liste des mots mal orthographiés


//remplissage du tableau de mots du texte
    while(fgets (str, TAILLE_MAX, ft)!= NULL){
        mot = strtok(str, " \n.,:-;!?()'");
        while (mot!= NULL) {
            s=strdup(mot);
            if(mot[0] != '"') txt= queue_mystring_enqueue(&s,txt);
            mot = strtok(NULL, " \n.,:;!?()'-");
        }
    }


//remplissage du tableau de mots du dictionnaire
    char mot_dct[TAILLE_MAX];
    while(fgets (mot_dct, TAILLE_MAX, fd)!= NULL){
        s=strndup(mot_dct,(strlen(mot_dct)-1)*sizeof(char));
        dct= queue_mystring_enqueue(&s,dct);
    }
//fin remplissage tableau

//correction orthographique dichotomique :
/*
    char* mot_txt; mystring s2; int txt_size =txt->size;
    int k = 0; link_mystring_t p = txt->data->next;
    printf("%d\n",txt_size);

    for(k=0; k<1000; k++){
    //while( k < txt->size){
    //while( k < txt_size ){
        if((dichotomique(*(char**)p, dct))){
            s2=strdup(*(char**)p);
            queue_mystring_enqueue(&s2, err);
        }
        k++;
        p = p->next;
        update_bar((k+1)/10);
    }
    printf("\n");




//affichage des erreurs du texte
    printf("nombre d'erreurs dans le texte: %d \n", err->size);
    queue_mystring_printf(err);
    printf("\n");*/

//correction orthographique itérative:

    mystring s2; int txt_size =txt->size;
    int k = 0; link_mystring_t p = txt->data->next;
    printf("%d\n",txt_size);

    //for(k=0; k<5000; k++){
    //while( k < txt->size){
    while( k < txt_size ){
        if((iteratif(*(char**)p, dct))){
            s2=strdup(*(char**)p);
            queue_mystring_enqueue(&s2, err);
        }
        k++;
        p = p->next;
        update_bar(100*(k)/txt_size);
    }
    printf("\n");




//affichage des erreurs du texte
    printf("nombre d'erreurs dans le texte: %d \n", err->size);
    queue_mystring_printf(err);
    printf("\n");




//destruction

    txt=queue_mystring_delete(txt);
    dct=queue_mystring_delete(dct);
    free(txt);
    free(dct);
    //err=queue_mystring_delete(err);
    //free(err);



    return 0;
}
