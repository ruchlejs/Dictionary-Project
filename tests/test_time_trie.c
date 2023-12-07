#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generic_heap.h"
#include "generic_sort_vect.h"
#include "mystring.h"

makevecttype(mystring)
makevectproto(mystring)
makevectfunction(mystring)

makeheaptype(mystring)
makeheapfunction(mystring)
makeheapproto(mystring)

makesortvectproto(mystring)
makesortvectfunction(mystring)

int compar(void* a, void*b) { return *(int*)a-*(int*)b;}


int main() { clock_t avant, apres;
  double temps1,temps2,temps3;
  int k, total_number=10000000;

    /* Ouverture d'un fichier contenant les temps de calcul */
  FILE* fp =fopen("tempstri.dat","w");

    /* k est le nombre d’elements a trier */
  for (k=1; k<=total_number; k+=k) {

     /* génération des mots aléatoires et copie dans le deuxieme tableau */
     vect_mystring_t table1 =vect_mystring_new(k,mystring_fprintf,mystring_delete,mystring_equal);
     vect_mystring_t table2 =vect_mystring_new(k,mystring_fprintf,mystring_delete,mystring_equal);
     vect_mystring_t table3 =vect_mystring_new(k,mystring_fprintf,mystring_delete,mystring_equal);

     int i;
     for(i=0;i<k;i++){
       mystring s=calloc(6,sizeof(char));
       int k= random()%5;
       if(k==6) sprintf(s,"%c%c%c%c%c%c", rand() % 20 + 'a',rand() % 20 + 'a',rand() % 20 + 'a',rand() % 20 + 'a',rand() % 20 + 'a',rand() % 20 + 'a'); // ou +'a' pour les minuscules
       else if (k==1) sprintf(s,"%c%c%c%c%c", rand() % 20 + 'a',rand() % 20 + 'a',rand() % 20 + 'a',rand() % 20 + 'a',rand() % 20 + 'a'); // ou +'a' pour les minuscules
       else if (k==2) sprintf(s,"%c%c%c%c", rand() % 20 + 'a',rand() % 20 + 'a',rand() % 20 + 'a',rand() % 20 + 'a'); // ou +'a' pour les minuscules
       else if (k==3) sprintf(s,"%c%c%c", rand() % 20 + 'a',rand() % 20 + 'a',rand() % 20 + 'a'); // ou +'a' pour les minuscules
       else if (k==4) sprintf(s,"%c%c", rand() % 20 + 'a',rand() % 20+ 'a'); // ou +'a' pour les minuscules
       else if (k==5) sprintf(s,"%c", rand() % 20 + 'a'); // ou +'a' pour les minuscules
       mystring s2= strdup(s);
       mystring s3= strdup(s);
       vect_mystring_append (s,table1);
       vect_mystring_append (s2,table2);
       vect_mystring_append (s3,table3);
     }

             /* Tri par quick sort , version de la bibliotheque C */
   avant=clock();      vect_mystring_qsort(table1);  apres=clock();
       /* Le temps de qsort est donne par apres-avant/CLOCKS_PER_SEC. */
    temps1=((double)apres - avant)/CLOCKS_PER_SEC;

       /* Tri par ma fonction heap_sort*/

    avant = clock();     heap_mystring_t tas=vect_mystring_heapsort(table2);       apres = clock();
    temps2=((double)apres - avant)/CLOCKS_PER_SEC;

    /* Tri par quick sort , version de la bibliotheque C */
   avant=clock();      vect_mystring_mergesort(table3);    apres=clock();
   /* Le temps de qsort est donne par apres-avant/CLOCKS_PER_SEC. */
   temps3=((double)apres - avant)/CLOCKS_PER_SEC;
      /* Affichage des temps des 2 tris dans le fichier */
    if (fp) {
      fprintf(fp,"%d\t%lf\t%lf\t%lf\n", k, temps1, temps2,temps3);


    }
    table1=vect_mystring_delete(table1);
    table2=vect_mystring_delete(table2);
    table3=vect_mystring_delete(table3);
    free(tas->data);
    free(tas);
    free(table1);
    free(table2);
    free(table3);
  }


  /* Affichage des 2 courbes contenues dans le fichier tempstri.dat avec le logiciel gnuplot */
 if (fp) {
   fclose(fp);
   system("gnuplot -p -e \"set logscale x; f(x) = a * x * log(x); fit f(x) 'tempstri.dat' u 1:2 via a;"
                "plot 'tempstri.dat' u 1:2 with line lt 4 title 'quickSort';"
                "g(x) = b * x * log(x);fit g(x) 'tempstri.dat' u 1:3 via b;"
                "replot 'tempstri.dat' u 1:3 with line lt 2 title 'MonTriHeap';"
                "h(x) = c * x * log(x);fit h(x) 'tempstri.dat' u 1:4 via c;"
                "replot 'tempstri.dat' u 1:4 with line lt 1 title 'MonTriFusion'; quit\"");


 }
 return 1;
}
