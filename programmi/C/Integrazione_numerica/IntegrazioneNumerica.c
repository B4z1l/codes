/*l'obbiettivo è quello di prendere una funzione f(x) e trovare l'antiderivata calcolata in un intervallo*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>


double f(double);
double letdoub(char *);
int sgn(double);
double der(double);

int main (void ){



FILE *output = fopen("output.dat", "w");

double a, b, dt, t, S, s, I, I1, epslon = 0.00001;/*a,b sono gli estremi dell'intervalo su cui integrare.*/

//a = letdoub("Inserisci l'estremo inferiore dell'intervallo di integrazione");
//b = letdoub("Inserisci l'estremo superiore dell'intervallo di integrazione");
//dt = letdoub("Inserisci dx incremento sull'intervallo[a,b]");
a = -10;
b = 10;
dt = 0.00001;


if(a > b){
    printf("a > b");
    exit(EXIT_FAILURE);
}

//fprintf(output, "# a = %lf, b = %lf, dt = %lf\n", a, b, dt);
//fprintf(output, "#x f(x) F(x)\n");


/*oltre il calcolo effettivo dell'antiderivata si vuole graficare la funzione integrale salvando tutti i passi di integrazione*/

for(t = a; t <= b; t += dt){ //calcolo lo sfasamento di F rispetto l'asse y = 0;

 S += f(t) * dt;
  s += f(t-dt) * dt;

 I1  = (S + s)/2.;

if(fabs(der(t)) > epslon){
} else if(fabs(der(t)) < epslon){
  break;
} else if( (der(t) > epslon) && (t = b) ){
  I1 = 0;
 break;
}

}

printf("%lf \n", I1);
S = 0; s = 0;

for(t = a; t < b; t += dt){
  
  S += f(t)  * dt;
  s += f(t-dt) * dt;

 I  = (S + s)/2.-I1;

  fprintf(output, " %lf %lf %lf\n", t, f(t), I);

}

/*Questo è il metodo generale per il suo calcolo tramite rettangoli inferiori di base dt e altezza f(t) che è : a, a+dt, a+2dt etc..*/
/*si vuole cercare l'antiderivata però!!!*/


system("gnuplot Integrale.gp");

fclose(output);
return 0;
}




/*funzione reale di variabile reale da integrare*/

double f(double x){
double y;

y = exp(-x * sin(x)) ;

return y;
}

double der(double x){
  double dx = 0.01;
  double df = (f(x+dx) - f(x))/dx;
  return df; 
}





double letdoub(char *print) {
    double input;

    printf("%s\n", print);
    fflush(stdout);
    scanf("%lg", &input);

    return input;
}


int sgn(double y){
  int l;
  if(y>=0){
  l = 1;
  } else if(y<0){
    l = -1;
  } else if(y == 0){
    l = 0;
  }
  return l;
}
