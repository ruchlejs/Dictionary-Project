#include "../include/generic_hashlset.h"
#include "../include/mystring.h"
#include <string.h>


makehashlsettype(mystring)
makehashlsetfunction(mystring)
makehashlsetproto(mystring)




int main(){
  hashlset_mystring_t table =hashlset_mystring_new(5,fhashchage,mystring_fprintf,mystring_delete,mystring_equal);
  int i;
  for(i=0;i<60;i++){
    mystring s=calloc(6,sizeof(char));
    int k= random()%6;
    if(k==6) sprintf(s,"%c%c%c%c%c%c", rand() % 26 + 'a',rand() % 26 + 'a',rand() % 26 + 'a',rand() % 26 + 'a',rand() % 26 + 'a',rand() % 26 + 'a'); // ou +'a' pour les minuscules
    else if (k==1) sprintf(s,"%c%c%c%c%c", rand() % 26 + 'a',rand() % 26 + 'a',rand() % 26 + 'a',rand() % 26 + 'a',rand() % 26 + 'a'); // ou +'a' pour les minuscules
    else if (k==2) sprintf(s,"%c%c%c%c", rand() % 26 + 'a',rand() % 26 + 'a',rand() % 26 + 'a',rand() % 26 + 'a'); // ou +'a' pour les minuscules
    else if (k==3) sprintf(s,"%c%c%c", rand() % 26 + 'a',rand() % 26 + 'a',rand() % 26 + 'a'); // ou +'a' pour les minuscules
    else if (k==4) sprintf(s,"%c%c", rand() % 26 + 'a',rand() % 26 + 'a'); // ou +'a' pour les minuscules
    else if (k==5) sprintf(s,"%c", rand() % 26 + 'a'); // ou +'a' pour les minuscules

    if(hashlset_mystring_put(s,table)==1) mystring_delete(s);
  }

  hashlset_mystring_fprintf(table, stderr);
  hashlset_mystring_remove_key("kw",table);
  mystring s= strdup("kw");
  hashlset_mystring_put(s,table);
  printf("\n");
   hashlset_mystring_fprintf(table, stderr);
  table=hashlset_mystring_delete(table);

  free(table);

  return 1;
}
