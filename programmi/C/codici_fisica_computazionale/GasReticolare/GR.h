#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define Dim 2 

double INVRANDMAX=1/(RAND_MAX + 1.);

typedef struct pos {
    int x;
    int y;
} pos;



void* mycalloc(int N, int size);
double randrange(double a, double b);
int randbool(double p);
double mod(double x, double m);
int** imatrix(int L);
void popmatrix(int **matrix, double ro, int L, int N);
void poparray(int** matrix, pos* tpos, pos* abs_pos, int L);
void update(int **matrix, pos *tpos, pos *abs_pos, int L, int N);


double Dil(int** matrix, pos *tpos, pos *abs_pos, int L, int N, double ro, int NSIM, int tmax);



double mod(double a, double b){ 
    //qui si calcola a mod b
    return fmod(fmod(a, b) + b, b);
}


double randrange(double a, double b){
    return rand()*INVRANDMAX*(b-a)+a;
}

int randbool(double p){
    //genero numeri random tra 0 ed 1
    return rand()*INVRANDMAX < p;
}

void *mycalloc(int N, int size){
    void* ptr = calloc(N, size);
    if (ptr == NULL){
        fprintf(stderr, "Errore: calloc fallita!\n");
        exit(2);
    }
}



int** imatrix(int L){
    // Allocate a matrix of int
    int **matrix = mycalloc(L, sizeof(int *));
    int i;
    for (i=0; i<L; i++){
        matrix[i] = mycalloc(L, sizeof(int));
    }
    return matrix;
}








void popmatrix(int **matrix, double rho, int L, int N){
    //riempie la matrice con L*L*rho particelle di gas
    
    int n=0;
    int x, y;
    int i,j;
    
    for (i=0; i<L; i++)
        for (j=0; j<L; j++)
            matrix[i][j] = -1;
   
    if (rho < 0.5){
        while(n < N){
            x = randrange(0, L);
            y = randrange(0, L);
            if (matrix[y][x] == -1){
                matrix[y][x] = n++;
            }
        }
   
    } else {
        while(1){
            for (i=0; i<L; i++){
                for (j=0; j<L; j++){
                    if (randbool(rho) && matrix[i][j] == -1){
                        matrix[i][j] = n++;
                    }
                    if(n >= N){
                        return;
                    }
                }
            }
        }
    }
}

void poparray(int** matrix, pos* tpos, pos* abs_pos, int L){
    
    int i,j;
    int p;
    for (i=0; i<L; i++){
        for(j=0; j<L; j++){
            p = matrix[i][j];
            if (p != -1){
                tpos[p].x = j;
                tpos[p].y = i;
                abs_pos[p].x = 0;
                abs_pos[p].y = 0;
            }
        }
    }
}


void update(int** matrix, pos *tpos, pos *abs_pos, int L, int N){
    //la funzione aggiorna tutte le particelle nella matrice
    int i;
    pos delta_pos;
    pos new_pos;
    for (i=0; i<N; i++){
        delta_pos.x = 0; delta_pos.y = 0;
        if (randbool(0.5)){ // sposta in x
            delta_pos.x = randbool(0.5) ? -1 : 1;
        } else { // sposta in y
            delta_pos.y = randbool(0.5) ? -1 : 1;
        }
        new_pos.x = mod(tpos[i].x + delta_pos.x, L);
        new_pos.y = mod(tpos[i].y + delta_pos.y, L);

        if (matrix[new_pos.y][new_pos.x] == -1){
            matrix[new_pos.y][new_pos.x] = i;
            matrix[tpos[i].y][tpos[i].x] = -1;
            abs_pos[i].x += delta_pos.x;
            abs_pos[i].y += delta_pos.y;
            tpos[i] = new_pos;
        }
    }
}


double R2(pos *abs_pos, int N){
    // Calculate the average R^2 where R is the distance from the starting
    // Point of every particle.
    int i;
    double res = 0;
    for (i=0; i<N; i++){
        res += abs_pos[i].x*abs_pos[i].x + abs_pos[i].y*abs_pos[i].y;
    }
    return res/N;
}



double Dil(int** matrix, pos *tpos, pos *abs_pos, int L, int N, double rho, int NSIM, int tmax){
    /*qui si calcola il limite a tempo "infinito" di R^2/(2*D*t) calcolandone la media su diverse simulazioni*/
  
    int i,j;
    double avg = 0;
    for (i=0; i<NSIM; i++){
        popmatrix(matrix, rho, L, N);
        poparray(matrix, tpos, abs_pos, L);
        for(j=0; j<tmax; j++){
            update(matrix, tpos, abs_pos, L, N);
        }
        avg += R2(abs_pos, N);
    }
    return avg/(NSIM*2*Dim*tmax);
}

double* A(int** matrix, pos *tpos, pos *abs_pos, int L, int N, double ro, int NSIM, int tmax){
  
    int i,j;
    double *avg = mycalloc(tmax, sizeof(double));
    for (i=0; i<NSIM; i++){
        popmatrix(matrix, ro, L, N);
        poparray(matrix, tpos, abs_pos, L);
        for(j=0; j<tmax; j++){
            update(matrix, tpos, abs_pos, L, N);
            avg[j] += R2(abs_pos, N);
        }
    }
    for (i=0; i<tmax; i++){
        avg[i] = avg[i]/(NSIM*2*Dim*i);
    }
    return avg;
}
