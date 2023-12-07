#include "generic_heap.h"
#include "mystring.h"
#include <string.h>


makevecttype(mystring)
makevectproto(mystring)
makevectfunction(mystring)

makeheaptype(mystring)
makeheapfunction(mystring)
makeheapproto(mystring)

int main(){

  heap_mystring_t tas =heap_mystring_new(10,mystring_fprintf,mystring_delete,mystring_equal);
  int i;
  for(i=0;i<8;i++){
    mystring s=calloc(6,sizeof(char));
    int k= random()%5;
    if(k==6) sprintf(s,"%c%c%c%c%c%c", rand() % 20 + 'a',rand() % 20 + 'a',rand() % 20 + 'a',rand() % 20 + 'a',rand() % 20 + 'a',rand() % 20 + 'a'); // ou +'a' pour les minuscules
    else if (k==1) sprintf(s,"%c%c%c%c%c", rand() % 20 + 'a',rand() % 20 + 'a',rand() % 20 + 'a',rand() % 20 + 'a',rand() % 20 + 'a'); // ou +'a' pour les minuscules
    else if (k==2) sprintf(s,"%c%c%c%c", rand() % 20 + 'a',rand() % 20 + 'a',rand() % 20 + 'a',rand() % 20 + 'a'); // ou +'a' pour les minuscules
    else if (k==3) sprintf(s,"%c%c%c", rand() % 20 + 'a',rand() % 20 + 'a',rand() % 20 + 'a'); // ou +'a' pour les minuscules
    else if (k==4) sprintf(s,"%c%c", rand() % 20 + 'a',rand() % 20+ 'a'); // ou +'a' pour les minuscules
    else if (k==5) sprintf(s,"%c", rand() % 20 + 'a'); // ou +'a' pour les minuscules

    heap_mystring_add(s,tas);
  }
  heap_mystring_fprintf(tas, stderr);
  heap_mystring_delete_extrema(tas);
  heap_mystring_fprintf(tas, stderr);
  mystring s= strdup("aaa");
  heap_mystring_add(s,tas);
  heap_mystring_fprintf(tas, stderr);
  printf("verif=%d\n",heap_mystring_verification(tas));
  tas=heap_mystring_delete(tas);
  free(tas);

  return 1;
}
