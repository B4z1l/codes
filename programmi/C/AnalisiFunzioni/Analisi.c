#include "funzioni.h"





int sgn(double);
double incr(double, double);
double radice(double x, double n);
double fact(double x);
double f(double x);

int main(void){

// ANALISI DI FUNZIONI REALI DI VARIABILE REALE

FILE *out = fopen("log/Output.log", "w");
FILE *plt = fopen("data/plt.dat", "w");

//iniziamo col cercare i punti di discontinuità per f:
//oltre l'uso proprio dei punti di discontinuità indotti si può fare
// un' unlteriore verifica per la continuità tramite la derivabilità. Quindi effettuiamo il rapporto incrementale
//sulla funzione in modo da vedere dove cambia rapidamente:
//si applica il criterio di derivabilità in cui la derivata esiste se esistono uguali limite destro e sinistro di ogni punto e 
//coincidono




double /*eps = 0.001,*/ j, h, hmax = 20, eps1 = 3100000;
double interv = 10.;    
double ddx  = .00001;
int contr = 0;


for(j = - interv; j < interv; j += ddx) {

  if((fabs(f(j+ddx)-f(j-ddx)) > eps1) && (((f(j+ddx) > 0) && (f(j-ddx) < 0)) || ((f(j+ddx) < 0) && (f(j-ddx) > 0)))){ 
   fprintf(out, "La funzione ha un punto di non definizione del dominio in %lf +- %lf\n", j, ddx);
  j += ddx;
  contr++;
  }


}
if(contr != 0){
  fprintf(out, "Dunque la funzione ha %i asintoti verticali\n", contr);
} else if (contr == 0){
  fprintf(out, "La funzione non ha asintoti verticali quindi R vale come dominio\n\n");
}





//************************************************************************************************************************


  
 




for(j = -interv; j < interv; j +=ddx){
  h = f(j);

  if(h>hmax){
    h = hmax;
  }else if(h <-hmax){
    h = -hmax;
  }

fprintf(plt, "%lf %lf\n", j, h);
}


//fclose(deri);
fclose(out);

system("gnuplot f(x).gp");
//system("gnuplot f'(x).gp");
    return 0;
}

