#include "generic_heap.h"
#include "generic_sort_vect.h"
#include "mystring.h"
#include <string.h>


makevecttype(mystring)
makevectproto(mystring)
makevectfunction(mystring)

makeheaptype(mystring)
makeheapfunction(mystring)
makeheapproto(mystring)

makesortvectproto(mystring)
makesortvectfunction(mystring)



int main(){

  vect_mystring_t table =vect_mystring_new(10,mystring_fprintf,mystring_delete,mystring_equal);
  int i;
  for(i=0;i<200;i++){
    mystring s=calloc(6,sizeof(char));
    int k= random()%5 + 1;
    if(k==6) sprintf(s,"%c%c%c%c%c%c", rand() % 20 + 'a',rand() % 20 + 'a',rand() % 20 + 'a',rand() % 20 + 'a',rand() % 20 + 'a',rand() % 20 + 'a'); // ou +'a' pour les minuscules
    else if (k==1) sprintf(s,"%c%c%c%c%c", rand() % 20 + 'a',rand() % 20 + 'a',rand() % 20 + 'a',rand() % 20 + 'a',rand() % 20 + 'a'); // ou +'a' pour les minuscules
    else if (k==2) sprintf(s,"%c%c%c%c", rand() % 20 + 'a',rand() % 20 + 'a',rand() % 20 + 'a',rand() % 20 + 'a'); // ou +'a' pour les minuscules
    else if (k==3) sprintf(s,"%c%c%c", rand() % 20 + 'a',rand() % 20 + 'a',rand() % 20 + 'a'); // ou +'a' pour les minuscules
    else if (k==4) sprintf(s,"%c%c", rand() % 20 + 'a',rand() % 20+ 'a'); // ou +'a' pour les minuscules
    else if (k==5) sprintf(s,"%c", rand() % 20 + 'a'); // ou +'a' pour les minuscules

    vect_mystring_append (s,table);
  }

  vect_mystring_fprintf(table, stdout);
  vect_mystring_mergesort(table) ;
  vect_mystring_fprintf(table, stdout);
  //printf("verif=%d\n",vect_mystring_verif_sort((vect_mystring_t)tas));
  table=vect_mystring_delete(table);
  free(table);

  return 1;
}
