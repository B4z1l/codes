#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include<string.h>
#define Pi 3.1415


int main(void){
  double t, p, R, r, x, y, z;
 FILE* out = fopen("Toro.dat", "w");
  /*ora calcoliamo i punti del toro*/

//valori in input
r = 1;
R = 10;
t = 0;
p = 0;
//calcolo dei punti della superficie del toro 
for(t = 0.; t < 2. * Pi; t += 0.01 ){
//p = tan(t);
for(p = 0.; p < 2 * Pi; p += 0.01){

  x = (R + r * sin(p)) * cos(t);
  y = (R + r * sin(p)) * sin(t);
  z = r * cos(p);

  fprintf(out, "%lf %lf %lf %lf %lf\n",x, y, z, t, p);
 }

}

fclose(out);

return 0;
}