#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(void){
FILE* out = fopen("outML.dat", "w");

int n, i;
double  r = 3.0, y1, y0;

n = 100;
y0 = 0.2;
for(i=0; i < n; i++){

y1 = r*y0*(1 - y0);

fprintf(out, "%d %lf \n", i, y1);

y0 = y1;
}





fclose(out);

    return 0;

}