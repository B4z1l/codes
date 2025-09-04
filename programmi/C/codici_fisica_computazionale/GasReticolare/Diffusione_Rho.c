#include "GR.h"
#include <string.h>


int main(void){
 FILE *input = fopen("input_gas/input.txt", "r");
 

//DIFFUSIONE RHO

int N, i, L;
double ro, dro = 0.2, tmax, sim;

fscanf(input, "%d %lf %lf\n", &L, &sim, &tmax);
fclose(input);

srand(time(NULL));

char *gnuplot[204] = {
        "set terminal png size 800,600 enhanced",
        "set title 'Coefficiente di diffusione nel tempo, per diversi valori di densita'",
        "set xlabel 't'",
        "set ylabel 'A(t)'",
        "set grid",
        "set output 'img/Arho.png'",
        "end"
    };

   FILE *gnu = popen("gnuplot -persist", "w");

    i=0;
    char *c;

   c = gnuplot[i];
    do {
        fprintf(gnu, "%s\n", c);
        i++;
        c = gnuplot[i];
    } while (strcmp(c,"end") != 0);
    fprintf(gnu, "plot ");
    for (ro = dro; ro < 1; ro += dro){
        fprintf(gnu, "'-' title ' r =%.2lf', ", ro);
    }
    fprintf(gnu, "\n");


int **matrix = imatrix(L);
    pos *tpos, *abs_pos;
    double *diff;
    for (ro = dro; ro < 1; ro += dro){
        N = L*L*ro;
        tpos = mycalloc(N, sizeof(pos));
        abs_pos = mycalloc(N, sizeof(pos));
        diff = A(matrix, tpos, abs_pos, L, N, ro, sim, tmax);
        for (i=0; i<tmax; i++){
            fprintf(gnu, "%d %lf\n", i, diff[i]);
        }
        fprintf(gnu, "e\n");
        free(diff);
        free(tpos);
        free(abs_pos);
    }

    pclose(gnu);
    for (i=0; i<L; i++){
        free(matrix[i]);
    }
    free(matrix);
    return 0;

}
