#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846
#define g 9.81 /*m/s^2*/
#define G 6.57430E-20 /*km^3 x kg^-1 x s^-2*/



struct spaziofasi {
    double x;
    double v;
    double t;
}; 
typedef struct spaziofasi ps;



double oscillatoreforzato(double w2, double x, double beta, double v, double f0, double wf, double t, int sistema) {
double e;
   switch (sistema) {
    case 1:
     e = -w2 * x - beta * v + f0 * cos(wf * t);
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

ps rounge_kutta4(double dt, double w2, double beta, ps posvelo, double f0, double wf, int sistema){
 ps posveln;
 
 double x1 = posvelo.v * dt;
 double v1 = oscillatoreforzato(w2, posvelo.x, beta, posvelo.v, f0, wf, posvelo.t , sistema) * dt;

 double x2 = (posvelo.v +  v1/2.0) * dt;
 double v2 = oscillatoreforzato(w2, posvelo.x +  x1/2.0, beta, posvelo.v +  v1/2.0,f0, wf, posvelo.t + dt /2.0, sistema) * dt;

 double x3 = (posvelo.v + v2/2.0) * dt;
 double v3 = oscillatoreforzato(w2, posvelo.x + x2/2.0, beta, posvelo.v + v2/2.0,f0, wf, posvelo.t + dt/2.0, sistema) * dt;

 double x4 = (posvelo.v + v3) * dt;
 double v4 = oscillatoreforzato(w2, posvelo.x + x3, beta, posvelo.v + v3, f0, wf, posvelo.t + dt , sistema) * dt;

  posveln.x = posvelo.x + (x1 + 2*x2 + 2*x3 + x4)/6.0;
  posveln.v = posvelo.v + (v1 + 2*v2 + 2*v3 + v4)/6.0;
  posveln.t = posvelo.t + dt;

  return posveln;

}

typedef struct init{
  double wf;
  double beta;
  double w2;
  double dt;
  double f0;
  double tmax;
} in;

/*calcolo dei bacini di attrazione*/

void attrazione(in ini){
 ps posvel;
 double x, v;
 int sistema = 2;
 double var = 500.;

   FILE *fp;
   fp  = fopen("out/plot/data.txt", "w");

  for (x = -PI; x < PI; x += PI/var) {

		for (v = -PI; v < PI ; v += PI/var) {
              posvel.x = x;
              posvel.v = v;
              posvel.t = 0;
			while(posvel.t < ini.tmax) {
				posvel = rounge_kutta4(ini.dt, ini.w2, ini.beta, posvel, ini.f0, ini.wf, sistema);
			}

      if(posvel.v >= 0) {    
        posvel.v = 1;
      } else if (posvel.v < 0) {
        posvel.v = 0;
    
	    }

			fprintf(fp, "%lf %lf %lf\n", x, v, posvel.v);
		}
  }
	  fclose(fp);
}
