#include "../include/generic_hashvset.h"
#include "../include/mystring.h"
#include <string.h>



makehashvsettype(mystring)
makehashvsetfunction(mystring)
makehashvsetproto(mystring)


int main(){
  hashvset_mystring_t table =hashvset_mystring_new(5,fhashchage,mystring_fprintf,mystring_delete,mystring_equal);
  int i;
  for(i=0;i<26;i++){
    mystring s=calloc(6,sizeof(char));
    int k= random()%5;
    if(k==6) sprintf(s,"%c%c%c%c%c%c", rand() % 20 + 'a',rand() % 20 + 'a',rand() % 20 + 'a',rand() % 20 + 'a',rand() % 20 + 'a',rand() % 20 + 'a'); // ou +'a' pour les minuscules
    else if (k==1) sprintf(s,"%c%c%c%c%c", rand() % 20 + 'a',rand() % 20 + 'a',rand() % 20 + 'a',rand() % 20 + 'a',rand() % 20 + 'a'); // ou +'a' pour les minuscules
    else if (k==2) sprintf(s,"%c%c%c%c", rand() % 20 + 'a',rand() % 20 + 'a',rand() % 20 + 'a',rand() % 20 + 'a'); // ou +'a' pour les minuscules
    else if (k==3) sprintf(s,"%c%c%c", rand() % 20 + 'a',rand() % 20 + 'a',rand() % 20 + 'a'); // ou +'a' pour les minuscules
    else if (k==4) sprintf(s,"%c%c", rand() % 20 + 'a',rand() % 20+ 'a'); // ou +'a' pour les minuscules
    else if (k==5) sprintf(s,"%c", rand() % 20 + 'a'); // ou +'a' pour les minuscules

    if(hashvset_mystring_put(s,table)==0) mystring_delete(s);
  }
  hashvset_mystring_fprintf(table, stderr);
  hashvset_mystring_remove_key("cb",table);
  mystring s= strdup("cb");
  hashvset_mystring_put(s,table);
  printf("\n");
   hashvset_mystring_fprintf(table, stderr);
   mystring t= strdup("mmm");
   printf("mmm est présente %d\n",hashvset_mystring_find_key(t,table));
  table=hashvset_mystring_delete(table);

  free(table);

  return 1;
}
