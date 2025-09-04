#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "GR.h"

int main(void){
 FILE *input = fopen("input_gas/input.txt", "r");
 

//DIFFUSIONE LIMITE 

int N, i, L;
double ro, dro = 0.01, tmax, sim;

fscanf(input, "%d %lf %lf\n", &L, &sim, &tmax);
fclose(input);

srand(time(NULL));

 char *gnuplot[200] = {
        "f(x) = a*(1-x)**b + c*(1-x)**d",
        "fit f(x) 'data/diff_lim.dat' via a,b,c,d",
        "set terminal png size 1290,720 enhanced",
        "set title 'Coefficiente di diffusione in funzione della densita'",
        "set xlabel 'r'",
        "set ylabel 'D(r)'",
        "set grid",
        "set output 'img/Difflim.png'",
        "plot 'data/diff_lim.dat' title 'data' pt 7 ps 0.6, f(x) title 'fit'",
        "end"
    };

    FILE *gnu = popen("gnuplot -persist", "w");
    FILE *out = fopen("data/diff_lim.dat", "w");

   
    int **matrix = imatrix(L);
    pos *tpos, *abs_pos;
    double diff;
    for (ro = dro; ro < 1; ro += dro){ // calcolo la diffusione incrementando il tempo e la densità del reticolo
        N = L*L*ro;
        tpos = mycalloc(N, sizeof(pos));
        abs_pos = mycalloc(N, sizeof(pos));
        diff = Dil(matrix, tpos, abs_pos, L, N, ro, sim, tmax);
        fprintf(out, "%lf %lf\n", ro, diff);
        free(tpos);
        free(abs_pos);
    }

    fclose(out);
 // ora si mandano i comandi alla pipe per eseguire lo script per gnuplot in modo da stampare automaticamente l'immagine ed il fit
    i=0;
    char *c;
  
    c = gnuplot[i];
    do {
        fprintf(gnu, "%s\n", c);
        i++;
        c = gnuplot[i];
    } while (strcmp(c,"end") != 0);

    pclose(gnu);
    for (i=0; i<L; i++){
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}








