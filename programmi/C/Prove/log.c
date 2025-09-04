#include<stdio.h>
#include<stdlib.h>
#include<complex.h>

int main(void){

double complex z1 = 2.0 + 2.0 * I, z2;

z2 = conj(z1);


printf("%lf + (%lf)", creal(z2), cimag(z2));


    return 0;

}