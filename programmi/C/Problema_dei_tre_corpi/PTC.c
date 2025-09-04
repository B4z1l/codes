#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define PI 3.14159265358979323846
#define gg 9.81 /*m/s^2*/
#define G 6.57430E-20 /*km^3 x kg^-1 x s^-2*/



struct energia {
  double E1;
  double E2;
  double E3;
}; 
typedef struct energia En;


struct pxi{
  double x1;
  double x2;
}; 
typedef struct pxi pxi;

struct sf{
  double x, v, e;
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
    sf ps3;
};
typedef struct built built;

struct raggi {
  double r12;
  double r23;
  double r13;
}; 
typedef struct raggi rg;

double mod(double a, double b){
    return fmod(fmod(a,b)+b, b);
}



double enel(double r1, double r2, double v, double a1, double a2);
void keplero();


int main(void){

   clock_t q; /*inizio del contatore del tempo*/
  q = clock();

 keplero();

q = clock() - q;
  double time_taken = ((double)q)/CLOCKS_PER_SEC; 

  printf("The program took %lf sec to finish", time_taken);

    return 0;
}













            /*PROBLEMA DEI TRE CORPI E PROBLEMA DI KEPLERO*/ /*il problema è trattato tramite la definizione generale ceh G * M = 1 per ogni corpo */

/*aggiornamento raggi*/

rg raggi( built X, built Y, built Z){
rg rgn;

  
rgn.r13 = sqrt((X.ps3.x - X.ps1.x) * (X.ps3.x-X.ps1.x) + (Y.ps3.x-Y.ps1.x) * (Y.ps3.x-Y.ps1.x) + (Z.ps3.x-Z.ps1.x) * (Z.ps3.x-Z.ps1.x));
rgn.r23 =sqrt((X.ps2.x - X.ps3.x) * (X.ps2.x-X.ps3.x) + (Y.ps2.x-Y.ps3.x) * (Y.ps2.x-Y.ps3.x) + (Z.ps2.x-Z.ps3.x) * (Z.ps2.x-Z.ps3.x));
rgn.r12 = sqrt((X.ps2.x - X.ps1.x) * (X.ps2.x-X.ps1.x) + (Y.ps2.x-Y.ps1.x) * (Y.ps2.x-Y.ps1.x) + (Z.ps2.x-Z.ps1.x) * (Z.ps2.x-Z.ps1.x));

  return rgn;
}



/*inizializzazione posizione e velocità dei due punti con massa*/
 double acc(double h1, double h2, double h3, int b, rg raggi){
   
 double a, r13, r12, r23;
 // costanti
double k12 = 1., k13 = 1., k23 = 1.;

 r13 = raggi.r13;
 r12 = raggi.r12;
 r23 = raggi.r23;


switch (b)
{
case 1:
 a =  k12*(h2-h1)/(r12*r12*r12)+k13*(h3-h1)/(r13*r13*r13);   

  break;

case 2 :
 a = -k12*(h2-h1)/(r12*r12*r12)+k23*(h3-h2)/(r23*r23*r23);   
break;
case 3:
 a = -k13*(h3-h1)/(r13*r13*r13)-k23*(h3-h2)/(r23*r23*r23);
break;

default:
  break;
}

// calcolo dell'energia
 

  

return a;
}

/*costruisco rk2 per keplero*/
built rounge_kutta4k(sf posveloa, sf posvelob,sf posveloc, double dt, built X, built Y, built Z) {
  
 built pv;

 sf pv1;
 sf pv2;
 sf pv3;
 rg R;


R = raggi(X, Y, Z);

 double x10 = posveloa.v * dt;
 double x11 = posvelob.v * dt;
 double x12 = posveloc.v * dt;


 double v10 = acc(posveloa.x, posvelob.x,posveloc.x, 1, R) * dt;
 double v11 = acc(posveloa.x, posvelob.x, posveloc.x, 2, R) * dt;
 double v12 = acc(posveloa.x, posvelob.x, posveloc.x, 3, R) * dt; 

 double x20 = (posveloa.v + 0.5 * v10) * dt;
 double x21 = (posvelob.v + 0.5 * v11) * dt;
 double x22 = (posveloc.v + 0.5 * v12) * dt;

 double v20 = acc(posveloa.x + .5*x10, posvelob.x, posveloc.x, 1, R) * dt;
 double v21 = acc(posveloa.x, posvelob.x + 0.5 * x11 ,posveloc.x , 2, R) * dt;
 double v22 = acc(posveloa.x, posvelob.x, posveloc.x + 0.5*x12, 3, R) * dt;

 double x30 = (posveloa.v + 0.5 * v20) * dt;
 double x31 = (posvelob.v + 0.5 * v21) * dt;
 double x32 = (posveloc.v + 0.5 * v22) * dt;

 double v30 = acc(posveloa.x + 0.5*x20, posvelob.x, posveloc.x, 1, R) * dt;
 double v31 = acc(posveloa.x, posvelob.x + 0.5*x21, posveloc.x, 2, R) * dt; 
 double v32 = acc(posveloa.x, posvelob.x, posveloc.x + 0.5*x22, 3, R) * dt; 

 double x40 = (posveloa.v + v30) * dt;
 double x41 = (posvelob.v + v31) * dt;
 double x42 = (posveloc.v + v32) * dt;

 double v40 = acc(posveloa.x + x30, posvelob.x, posveloc.x, 1, R) * dt;
 double v41 = acc(posveloa.x , posvelob.x + x31,posveloc.x, 2, R) * dt;
 double v42 = acc(posveloa.x, posvelob.x, posveloc.x + x32, 3, R) * dt;

  pv1.x = posveloa.x + (x10 + 2.*x20 + 2.*x30 + x40)/6.0;
  pv1.v = posveloa.v + (v10 + 2.*v20 + 2.*v30 + v40)/6.0;
 

  pv2.x = posvelob.x + (x11 + 2.*x21 + 2.*x31 + x41)/6.0;
  pv2.v = posvelob.v + (v11 + 2.*v21 + 2.*v31 + v41)/6.0;
  
  pv3.x = posveloc.x + (x12 + 2.*x22 + 2.*x32 + x42)/6.0;
  pv3.v = posveloc.v + (v12 + 2.*v22 + 2.*v32 + v42)/6.0;

  pv.ps1 = pv1;
  pv.ps2 = pv2;
  pv.ps3 = pv3; 
  return pv;
  
  
}


void keplero() {


double x1, y1, z1, vx1, vy1, vz1, x2, y2, z2, vx2, vy2, vz2, x3, y3, z3, vx3, vy3, vz3, tmax = 700., dt = 0.01, t = 0.;
int g = 1;
/*posizione corpo 1*/
x1 = 20.;  
y1 = 0.;
z1 = 0.;

/* posizione corpo 2*/
x2 = -20.;  
y2 = 0.;
z2 = 0.;

/*posizione corpo 3*/
x3 = 0.;
y3 = 0.;
z3 = 0.;

/*velocità corpo 1*/
vx1 = 0.;
vy1 = -0.2; 
vz1 = 0.;

/*velocità corpo 2*/
vx2 = 0.;
vy2 = 0.2;
vz2 = -0.1;

/*velocità corpo 3*/
vx3 = 0.;
vy3 = 0;
vz3 = 0.1;


built X;
built Y;
built Z;

/*inizializzazione variabili*/
X.ps1 = ips(x1, vx1);
Y.ps1 = ips(y1, vy1);
Z.ps1 = ips(z1, vz1);

X.ps2 = ips(x2, vx2);
Y.ps2 = ips(y2, vy2);
Z.ps2 = ips(z2, vz2);

X.ps3 = ips(x3, vx3);
Y.ps3 = ips(y3, vy3);
Z.ps3 = ips(z3, vz3);


//calcolo del baricentro a t = 0

double xbar = (x1 + x2 + x3) / 3.;
double ybar = (y1 + y2 + y3) / 3.;
double zbar = (z1 + z2 + z3) / 3.;

FILE* log = fopen("output/output.log","w");
fprintf(log, "Centro di massa a t = 0 : (%lf X, %lf Y, %lf Z)\n", xbar, ybar, zbar);
fclose(log);



FILE *j = fopen("output/plotting/data/keplero.dat","w");



while(t < tmax) {

switch (g) {

case 1:
  g = 0;
  break;
case 0:
g = 1;
break;

default:
  break;
}




X = rounge_kutta4k(X.ps1, X.ps2, X.ps3, dt, X, Y, Z);

Y = rounge_kutta4k(Y.ps1, Y.ps2, Y.ps3, dt, X, Y, Z);

Z = rounge_kutta4k(Z.ps1, Z.ps2, Z.ps3, dt, X, Y, Z);



t += dt;

switch (g) {
case 1:
 fprintf(j, " %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf \n", t ,X.ps1.x, Y.ps1.x, Z.ps1.x, X.ps2.x, Y.ps2.x, Z.ps2.x, X.ps3.x, Y.ps3.x, Z.ps3.x);
  break;

default:
 break;
}


if(Y.ps1.x <= 0.0001 && Y.ps1.x >= -0.0001){
  printf("il periodo del primo corpo vale: T = %lf\n", t);
}



 }

fclose(j);

}

double enel(double r1, double r2, double v, double a1, double a2 ){

  double E = 0.5 * v * v + a1 * r1 + a2 * r2;

  return E;
}
