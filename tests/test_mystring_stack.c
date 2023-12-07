#include "generic_stack.h"
#include "../include/mystring.h"


// pour compiler gcc double.c test_double_stack.c -o exe

makelisttype(mystring)
makelistproto(mystring)
makelistfunction(mystring)

makestacktype(mystring)
makestackproto(mystring)
makestackfunction(mystring)


int main(){

  stack_mystring_t l2=stack_mystring_new(mystring_fprintf,mystring_delete,mystring_equal);

  mystring s;
  printf("Ajout de chaine1,2,3,4 : ");
  s=strdup("chaine1"); l2=stack_mystring_push(&s,l2);
  s=strdup("chaine2"); l2=stack_mystring_push(&s,l2);
  s=strdup("chaine3"); l2=stack_mystring_push(&s,l2);
  s=strdup("chaine4"); l2=stack_mystring_push(&s,l2);

stack_mystring_printf(l2);
stack_mystring_pop(l2);
fprintf(stdout, "\n" );
stack_mystring_printf(l2);
fprintf(stdout, "\n" );
fprintf(stdout, "%s\n",stack_mystring_peek(l2) );
s=stack_mystring_peek(l2);
l2=stack_mystring_delete(l2);
// stack_double_printf(q1);
// fprintf(stdout, "\n" );
free(l2);

return 0;
}
