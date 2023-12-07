#include "generic_stack.h"
#include "../include/double.h"


// pour compiler gcc double.c test_double_stack.c -o exe

makelisttype(double)
makelistproto(double)
makelistfunction(double)

makestacktype(double)
makestackproto(double)
makestackfunction(double)


int main(){
  stack_double_t q1=stack_double_new(double_fprintf,delete_data,double_equal);
  stack_double_printf(q1);
  double v;

  for (v=10; v<=50; v+=10){
    q1=stack_double_push(&v,q1);
  }
  
  stack_double_printf(q1);
  stack_double_pop(q1);
  stack_double_pop(q1);
  fprintf(stdout, "\n" );
  stack_double_printf(q1);
  fprintf(stdout, "\n" );
  q1=stack_double_delete(q1);
  stack_double_printf(q1);
  fprintf(stdout, "\n" );
  free(q1);

  return 0;
}
