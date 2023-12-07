#include <stdio.h>
#include <stdlib.h>
#include "../include/generic_vect.h"
#include "../include/double.h"

makevecttype(double)
makevectproto(double)
makevectfunction(double)

int main(){
  vect_double_t v;
  v=vect_double_new(40,double_fprintf,NULL,double_equal);
  if (v==NULL) {
    printf("Erreru allocation\n");
    exit(EXIT_FAILURE);
  }
  int i;
  for (i=0; i<10; i++) {
    v->data[i]=random() %100;
    v->actual_size++;
  }
  vect_double_printf(v);
  v=vect_double_append(1,v);
  vect_double_printf(v);

  v=vect_double_insert(25,3,v);
  vect_double_printf(v);

  double a=25;
  printf("2 existe dans la table: %d \n",vect_double_find(&a,v));
  double b=25;
  printf("2 existe dans la table: %d \n",vect_double_lookup(&b,v,double_equal));
  v= vect_double_delete(v);
  return 0;
}
