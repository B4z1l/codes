#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include<string.h>
#define Pi 3.1415

int main(void){
  double t, p, x, y, z, r = 3;
 FILE* out = fopen("klein.dat", "w");
  /*ora calcoliamo i punti della bottiglia di klein sotto parametrizzazione a figura 8*/

//valori in input

//calcolo dei punti della superficie della parametrizzazione a figura 8 della bottiglia di klein
for(p = - Pi; p < Pi; p += 0.02 ){

  for(t = 0; t < 2 * Pi; t += 0.02){

    x = (r + cos(t/2) * sin(p) - sin(t/2) * sin(2 * p)) * cos(t);
    y = (r + cos(t/2) * sin(p) - sin(t/2) * sin(2 * p)) * sin(t);
    z = sin(t/2) * sin(p) + cos(t/2) * sin(2 * p) ;
    
  fprintf(out, "%lf %lf %lf %lf %lf\n",x, y, z, t, p);
   }

}

fclose(out);

return 0;
}

