#include<stdio.h>
#include<math.h>
#include<stdlib.h>


int main(void){

FILE* in = fopen("out.dat", "r");

if(in == NULL){
	printf("File out.dat non trovato o impossibile accedervi");
	exit(1);
}
int i, N = 1000000;
int j = 0, k = 0, ji = 0, ki = 0;
float meanx, meany;

for(i = 0; i < N; i++){
	fscanf(in, "%d %d\n", &ji, &ki);
 j += ji;
 k += ki;
} 

 meanx = j/N;

 meany = k/N;

 printf("x = %f y = %f\n", cos(meanx), sin(meany));
   return 0;

}
