#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "RW.h"


pos av1d(pos point);
pos av(pos point);
int rb();
double d2(pos point);

int main(void){


//RANDOM WALK 1D
FILE *input = fopen("input_random/input_randwalk.txt", "r");
FILE *out = fopen("plotting/data/out1d.dat", "w");
FILE *xt = fopen("plotting/data/xt.dat", "w");


if(input == NULL || out == NULL){
    fprintf(stderr, "ERRORE: percorso file o file input o output non trovato!");
    exit(EXIT_FAILURE);
}

int bin, passi, sim;
fscanf(input, "%d %d %d", &passi, &sim, &bin);



/*per ragioni di precisione e casualita' uso il tempo corrente come seed*/
srand(time(NULL));
  int x = 0;
int *arr = calloc(passi, sizeof(int));
  if (arr == NULL){
    fprintf(stderr, "Errore: calloc non riuscita\n"); //e' veramente improbabile che finisca la memoria al giorno d'oggi:)
    exit(2);
  }


int *hist = calloc(bin, sizeof(int));
  if (hist == NULL){
    fprintf(stderr, "Errore: calloc non riuscita\n");
    exit(2);
  }

//1- verifica di x(t) ~ t

int s, t;
//s e' il numero di simulazione t invece il tempo della simulazione
for (s = 0; s < sim; s++){
    x = 0;
    for (t=0; t < passi; t++) {
        
        fprintf(out, "S %d T %d X %d\n", s, t, x);
        arr[t] += x * x;
        x += (rb() ? 1 : -1);
    }

  }

 for (t=0; t<passi; t++){
    fprintf(xt, "%d %lf\n", t, ((double)arr[t])/(double)sim );
  }



//RANDOM WALK 2D
 FILE* out2d = fopen("plotting/data/out2d.dat", "w");
  FILE* xt2d = fopen("plotting/data/xt2d.dat", "w");
  FILE* px2d = fopen("plotting/data/px2d.dat", "w");
  pos posiz;
  double ds;
  pos nposiz;

  for (t=0; t<passi; t++){/*azzero l'array precedente per riutilizzarlo*/
    arr[t] = 0;
  }

double (*hist2d)[bin] = calloc(bin, sizeof(double[bin])); /*in questo caso è interessante vedere la distribuzione delle posizioni finali*/

for (s =0; s < sim; s++){ /*simulo una camminata aleatoria a due gradi di libertà sim volte*/
    posiz.x = 0;
    posiz.y = 0;
    for (t=0; t < passi; t++) {
        fprintf(out2d, "S %d T %d X %d Y %d\n", s, t, posiz.x, posiz.y); 

        ds = d2(posiz);
        arr[t] += ds;
        posiz = av(posiz);
    }
    nposiz.x = ((double) (posiz.x + passi) / (2.0 * passi) )*bin;
    nposiz.y = ((double) (posiz.y + passi) / (2.0 * passi) )*bin;

    hist2d[nposiz.x][nposiz.y]++;
  }
  
    fprintf(xt2d, "%lf %lf\n", (double)t, ((double)arr[t])/(double)sim);
  for (t=0; t<passi; t++){/*verifica di x(t) ~ t in 2D*/
  }
  
  int j;
  double nind[2];
  for (t=0; t<bin; t++){/*riempio i bin nelle due dimensioni per ottenere la distribuzione*/
    nind[0] = ((2.0*passi)/bin)*t - passi;
    for (j=0; j<bin; j++){
       nind[1] = ((2.0*passi)/bin)*j - passi;
       
       fprintf(px2d, "%lf %lf %lf\n", nind[0], nind[1], hist2d[t][j]/sim);
    }
  }









fclose(input);
fclose(out);
fclose(xt);
fclose(out2d);
fclose(xt2d);
fclose(px2d);

free(hist);
free(arr);
free(hist2d);

}

