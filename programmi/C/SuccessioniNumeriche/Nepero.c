#include<stdio.h>
#include<stdlib.h>
#include<math.h>

 double fattoriale( double);

int main(void){/*calcoliamo in numero di Nepero dalla definizione*/

  double an = 0;


for(int n = 0; n < 20; n++){  /*l'algoritmo può calcolare con precisione assoluta fino alla quindicesima cifra decimale di e*/


an += 1. / fattoriale(n) ; 

}


printf(" e = %.15lf\n",(double) an);



    return 0;
}

 double fattoriale(double x){
 if(x == 0){
  return 1.;
 } else {
  return x * fattoriale(x-1.);
 }
}


