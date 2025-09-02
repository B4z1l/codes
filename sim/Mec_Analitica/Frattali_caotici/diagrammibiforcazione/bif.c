#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846
#define g 9.81 /*m/s^2*/
#define G 6.57430E-20 /*km^3 x kg^-1 x s^-2*/



//STRUCT ###################################################################################################
struct spaziofasi {
    double x;
    double v;
    double t;
}; 
typedef struct spaziofasi ps;

struct pxi{
  double x1;
  double x2;
}; 
typedef struct pxi pxi;

struct sf{
  double x, v;
};
typedef struct sf sf;


sf ips(double x0, double v0){
  sf isf;
  isf.x = x0;
  isf.v = v0;
  return isf;
}


struct built {
    sf ps1;
    sf ps2;
};
typedef struct built built;

struct raggi {
  double r1;
  double r2;
  double r;
}; 
typedef struct raggi rg;

double mod(double a, double b){
    return fmod(fmod(a,b)+b, b);
}

ps iposvel(double x0, double v0, double t0) {

    ps posvel;

    posvel.x = x0;
    posvel.v = v0;
    posvel.t = t0;

    return posvel;
}



//OSCILLATORE #####################################################################################################
 

double oscillatoreforzato(double w2, double x, double beta, double v, double f0, double wf, double t, int sistema, double alf) {
double e;
   switch (sistema) {
    case 1:
     e = -w2 * x - beta * v + f0 * cos(wf * t) - alf * x * x * x; 
    break;
    case 2:
    e = -w2 * sin(x) - beta * v + f0 * cos(wf * t);
    break;
    default:
      exit(EXIT_FAILURE);
    break;
    }

return e;
    
}

/*ROUNGE-KUTTA 4*/ 

ps rounge_kutta4(double dt, double w2, double beta, ps posvelo, double f0, double wf, int sistema, double alf){
 ps posveln;
 
 double x1 = posvelo.v * dt;
 double v1 = oscillatoreforzato(w2, posvelo.x, beta, posvelo.v, f0, wf, posvelo.t , sistema, alf) * dt;

 double x2 = (posvelo.v +  v1/2.0) * dt;
 double v2 = oscillatoreforzato(w2, posvelo.x +  x1/2.0, beta, posvelo.v +  v1/2.0,f0, wf, posvelo.t + dt /2.0, sistema, alf) * dt;

 double x3 = (posvelo.v + v2/2.0) * dt;
 double v3 = oscillatoreforzato(w2, posvelo.x + x2/2.0, beta, posvelo.v + v2/2.0,f0, wf, posvelo.t + dt/2.0, sistema, alf) * dt;

 double x4 = (posvelo.v + v3) * dt;
 double v4 = oscillatoreforzato(w2, posvelo.x + x3, beta, posvelo.v + v3, f0, wf, posvelo.t + dt , sistema, alf) * dt;

  posveln.x = posvelo.x + (x1 + 2*x2 + 2*x3 + x4)/6.0;
  posveln.v = posvelo.v + (v1 + 2*v2 + 2*v3 + v4)/6.0;
  posveln.t = posvelo.t + dt;

  return posveln;

}






/*Algoritmo per la biforcazione*/

void biforcazione(){
 double dt, w2, beta,  wf, tmax, f2, df, f;
 int  sistema;
 ps posvel;


 double k;
 

FILE *bif = fopen("output/plotting/data/biforcazione.dat", "w");
if(bif == NULL){
  printf("biforcazioni.dat non trovato!");
  exit(EXIT_FAILURE);
}

for (k = 0.; k <= 10.; k+=1.) {



 wf = 2./3.;
 beta = 0.5;
 w2 = 1.;
 f2 = 1.5;
 df = 0.0001;
 sistema = 2;
 tmax = 9.42477796076937934799; 
 dt = 0.09424777960769378793;

 double alf = 0.;
 

   for(f = 0.9; f <= f2; f += df){
    posvel.x = 1.57079632679489655800 ;
    posvel.v = k * PI/10.;
 
      
        for(posvel.t = 0; posvel.t < tmax *10; ){

       
        posvel = rounge_kutta4(dt, w2, beta, posvel, f, wf,  sistema, alf);
        
        }

      fprintf(bif, "%lf %lf %lf \n", f, posvel.v, posvel.x);
    }
 
 }

   fclose(bif);
  
}



//AVVIO IL PROGRAMMA



int main(void){
    biforcazione();
    return 0;

}