#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include<string.h>
#define Pi 3.1415


int main(void){
  double t, p, x, y, z;
 FILE* out = fopen("Mobius.dat", "w");
  /*ora calcoliamo i punti del toro*/

//valori in input

//calcolo dei punti della superficie del nastro di Mobius
for(t = 0.; t < 2. * Pi; t += 0.01 ){

 for(p = -1.; p < 1; p += 0.01){

x = 2 * cos(t) + p * cos(t) * cos(t/2.);
y = 2 * sin(t) + p * sin(t) * sin(t/2.);
z = p * sin(t/2.);


  fprintf(out, "%lf %lf %lf %lf %lf\n",x, y, z, t, p);
 }

}

fclose(out);

return 0;
}