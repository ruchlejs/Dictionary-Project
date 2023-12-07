#include "../include/generic_queue.h"
#include "../include/double.h"
// #include "queue_double.h"

// pour compiler gcc double.c test_double_queue.c -o exe

makelisttype(double)
makelistproto(double)
makelistfunction(double)

makequeuetype(double)
makequeueproto(double)
makequeuefunction(double)


int main(){
  queue_double_t q1=queue_double_new(double_fprintf,delete_data,double_equal);
  double v;

  for (v=10; v<=50; v+=10){
    q1=queue_double_enqueue(&v,q1);
  }
  queue_double_printf(q1);
  queue_double_dequeue(q1);
  fprintf(stdout, "\n" );
  queue_double_printf(q1);
  fprintf(stdout, "\n" );
  q1=queue_double_delete(q1);
  queue_double_printf(q1);
  fprintf(stdout, "\n" );
  free(q1);

  return 0;
}
