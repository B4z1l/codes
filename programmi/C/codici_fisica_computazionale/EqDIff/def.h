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


//ENERGIE-----------------------------------------------------------

/*potenziale*/
double potenziale(double w2, double x, int sistema, double l){
  double a;

   switch (sistema) {
   case 1:
    a =  w2 * x * x;
   break;
   case 2:
    a =  w2 * l * l * (1. - cos(x));
   break;
   default:
     exit(EXIT_FAILURE);
  }

    return a;
}

/*meccanica*/
double energia(double w2, ps posvel, int sistema, double l) {
    double E;
    E =  posvel.v * posvel.v +  potenziale(w2, posvel.x, sistema, l);
    return E;
}

//ALGORITMI---------------------------------------------------------------------------------------------

/*EULERO*/
ps eulero(double dt, double w2, double beta, ps posvelo, double f0, double wf, int sistema) { 
     ps posveln;
    
    posveln.v = posvelo.v + oscillatoreforzato(w2, posvelo.x, beta, posvelo.v, f0, wf, posvelo.t, sistema) * dt;
    posveln.x = posvelo.x + posvelo.v * dt;
    posveln.t = posvelo.t + dt;

    return posveln;

}

/*EULERO-CROMER*/
ps eulero_cromer(double dt, double w2, double beta, ps posvelo, double f0, double wf, int sistema) { 
   ps posveln;
    
    posveln.v = posvelo.v + oscillatoreforzato(w2, posvelo.x, beta, posvelo.v, f0, wf, posvelo.t, sistema) * dt;
    posveln.x = posvelo.x + posveln.v * dt;
    posveln.t = posvelo.t + dt;
    return posveln;
}


/*VERLET AUTOSUFFICIENTE*/
ps verlet_autosufficiente(double dt, double w2, double beta, ps posvelo, double f0, double wf, int sistema) {
    ps posveln;
    
    posveln.x = posvelo.x + posvelo.v * dt + 0.5 * oscillatoreforzato(w2, posvelo.x, beta, posvelo.v, f0, wf, posvelo.t, sistema) * dt * dt;
    posveln.v = posvelo.v + (oscillatoreforzato(w2, posvelo.x, beta, posvelo.v, f0, wf, posvelo.t, sistema) + oscillatoreforzato(w2, posveln.x, beta, posvelo.v, f0, wf, posvelo.t, sistema)) * 0.5 * dt;
    posveln.t = posvelo.t + dt;
    return posveln;

}
 
/*ROUNGE-KUTTA 2*/
ps rounge_kutta2(double dt, double w2, double beta, ps posvelo, double f0, double wf, int sistema){
  ps posveln;
  ps agg;

  agg.x = posvelo.v * dt;
  agg.v = oscillatoreforzato(w2, posvelo.x, beta, posvelo.v, f0, wf, posvelo.t, sistema) * dt;
  

  posveln.x = posvelo.x + ( posvelo.v + 0.5 * agg.v) * dt;
  posveln.v =  posvelo.v + oscillatoreforzato(w2, posvelo.x + 0.5 * agg.x, beta, posvelo.v + 0.5 * agg.v, f0, wf, posvelo.t, sistema) * dt;
  posveln.t = posvelo.t + dt;

  return posveln;
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



// SEQUENZA DI SCELTE PER GLI ALGORITMI_________________________________________________________

int scelta(int algoritmo, int at, FILE *o){
    int h, l = 0;
  switch (algoritmo) {
  case 0:
    fprintf(o,"hai scelto Eulero\n");
    break;
  case 1:
    fprintf(o,"hai scelto Eulero-Cromer\n");
    break;
  case 2:
    fprintf(o,"hai scelto Verlet autosufficiente\n");
    break;
  case 3:
    fprintf(o,"Hai scelto Rounge-Kutta\n");
 
    if (at == 0){/*per mettere come default rk2 basta cambiare h in h = 1 anziché 2*/
      h = 2;
      goto ah;
    }

    printf("di che ordine?\n");
    printf("1 secondo ordine, 2 quarto ordine\n");
    scanf("%i", &h); 

     ah:
    switch (h) {
    case 1:
      fprintf(o,"hai scelto Rounge-kutta di secondo ordine\n\n");
      l = 3;
      break;
    case 2:
      fprintf(o,"hai scelto Rounge-Kutta di quarto ordine \n\n");
      l = 4;
      break;
    default:
      l = 1;
      break;
    }
    break;
  default:
    printf("Errore, algoritmo %i non pervenuto o ancora non implementato, riprova\n", algoritmo);
    fflush(stdin);
    l = 1;
    break;
  }

return l;

}





// ALGORITMO EFFETTIVO PER L'INTEGRAZIONE---------------------------------------------------------------------------------------------------------------------------------------------



void algoritmi(int algoritmo, double dt, double w2, double beta, long int N, ps posvel, double E0, FILE *fp, double f0, double wf, int sistema, int c, double l ) {

    int i;
    double E;
      
            switch (algoritmo){
              case 0:       /*EULERO*/
                  for (i = 0; i < N; i++) {

                       posvel = eulero(dt, w2, beta, posvel, f0, wf,  sistema);
                        E = energia(w2, posvel, sistema, l);

                  fprintf(fp, " %lf %lf %lf %lf\n", posvel.t, posvel.x, posvel.v, (E-E0)/E0);
                  }
                break;
              case 1:    /*EULERO-CROMER*/ 
                  for (i = 0; i < N; i++) {

                       posvel = eulero_cromer(dt, w2, beta, posvel, f0, wf, sistema);
                        E = energia(w2, posvel, sistema, l);

                  fprintf(fp, " %g %g %g %g \n", posvel.t, posvel.x, posvel.v, (E-E0)/E0);
                  } 
                break;
              case 2:       /*VERLET AUTOSUFFICIENTE*/  
                  for (i = 0; i < N; i++){
                       posvel = verlet_autosufficiente(dt, w2, beta, posvel, f0, wf, sistema);
                      
                        E = energia(w2, posvel, sistema, l);
                  fprintf(fp, " %g %g %g %g \n", posvel.t, posvel.x, posvel.v, (E-E0)/E0);
                  }
                break;
              case 3: 

                switch(c) {
                  case 3:
                               /*rounge-kutta 2*/ 
                    for (i = 0; i < N; i++){
                       posvel = rounge_kutta2(dt, w2, beta, posvel, f0, wf, sistema);
                      
                        E = energia(w2, posvel, sistema, l);
                    fprintf(fp, " %g %g %g %g \n", posvel.t, posvel.x, posvel.v, (E-E0)/E0);
                    }
                    break;
                  case 4:     
                              /*rounge-kutta 4*/
                    for (i = 0; i < N; i++){
                       posvel = rounge_kutta4(dt, w2, beta, posvel, f0, wf, sistema);
                       
                        E = energia(w2, posvel, sistema, l);
                    fprintf(fp, " %g %g %g %g \n", posvel.t, posvel.x, posvel.v, (E-E0)/E0);
                    }
                    break;

                  default:
                    printf("cosa e' successo?1");
                    break;
                  }
            }
            fclose(fp);

}



//FUNZIONI PER LA LETTURA DATI DA STDIN_____________________________________

int letint(char *print) {
    int input;

    printf("%s\n", print);
    fflush(stdout);
    scanf("%i", &input);

    return input;
}

double letdoub(char *print) {
    double input;

    printf("%s\n", print);
    fflush(stdout);
    scanf("%lg", &input);

    return input;
}





/*analisi degli errori nei vari metodi: dE vs dt*/

double enersimp(double x, double v, double w2){
  return w2 * x * x + v*v;
}


void errori(){
 double dt, w2, beta,  wf, tmax, f0, dtmax, t, E, E0, dE,l ;
 int  sistema;
 ps posvel;

FILE *err = fopen("plotting/data/err.dat", "w");


f0 = wf = beta = l =  0 ;
dtmax = 1e-4;
w2 = 1;
tmax = 100;

sistema = 1;

posvel.x = 0.;
posvel.v = 1.;

E0 = energia(w2, posvel, sistema, l);

for(dt = 0.1; dt > dtmax; dt /= 1.2){

posvel.x = 0.;
posvel.v = 1.;

   for(t = 0; t < tmax; t += dt){
     posvel = verlet_autosufficiente(dt, w2, beta, posvel, f0, wf, sistema); //cambiando il nome della funzione si può valutare l'ordine dell'algoritmo scelto (sono tutte uguali le funzioni degli algoritmi)
    }

 E = enersimp(posvel.x, posvel.v, w2);

 dE = fabs((E-E0)/E0);
  fprintf(err, "%lf %.20lf\n", dt, dE);
}

fclose(err);
}








void poincare(){

FILE *fp = fopen("plotting/data/fasi.dat", "w");
FILE *poin = fopen("plotting/data/poincare.dat", "w");

if(fp == NULL || poin == NULL){
  fprintf(stderr, "Errore: file fasi.dat o poincare.dat non pervenuti.");
  exit(EXIT_FAILURE);
}
double  dt, w2, beta,  f0, wf, T,tmax,  t, alfa;
  int  sistema;
  ps posvel;


 wf = 0.666666666666666;
 posvel.v = 0.;
 posvel.x =  1.5707963267948966 ;
 beta = 0.5;
 w2 = 1.;
 T = 9.42477796076938;
 dt = 0.00942477796076938;
 sistema = 2;
 f0 = 1.15;






for (tmax = T; tmax <= T * 100; tmax += T) {

  posvel.t = 0;

          for(t = 0; t < tmax; t += dt){    

           posvel = rounge_kutta4(dt, w2, beta, posvel, f0, wf, sistema);

            alfa = mod(posvel.x + PI, 2 * PI) - PI;

            if(tmax > T * 99){
               fprintf(fp, "%lf %lf \n", alfa , posvel.v);
            }

          }

       fprintf(poin, " %lf %lf \n", alfa, posvel.v); 
      
}


fclose(fp);
fclose(poin);

}



/*calcolo dei bacini di attrazione*/

void attrazione(){
 ps posvel;
 double x, v, dt, w2, beta,  f0, wf, tmax;
 int  sistema;


 wf = 2./3.;
 beta = 0.5;
 w2 = 1.;
 dt = 0.01;
 sistema = 2;
 f0 = 1.50; 
 tmax = 93.;

   FILE *fp;
   fp  = fopen("plotting/data/attrazione.dat", "w");


  for (x = -PI; x < PI; x += PI/50) {
/*faccio variare angolo e velocità angolare valutando lo stato finale */
		for (v = -PI; v < PI ; v += PI/50) {

              posvel.x = x;
              posvel.v = v;
              posvel.t = 0;

			while(posvel.t < tmax) {

				posvel = rounge_kutta4(dt, w2, beta, posvel, f0, wf, sistema);
       
			}


         //  if(posvel.v >= 0) {    /*decommentare se non si vogliono sfumature nel grafico dei bacini*/
           //      posvel.v = 1;
          // } else if (posvel.v < 0) {
          //       posvel.v = 0;
           //}


			fprintf(fp, "%lf %lf %lf\n", x, v, posvel.v);

		}

	}

	fclose(fp);
}




/*Algoritmo per la biforcazione*/

void biforcazione(){
 double dt, w2, beta,  wf, tmax, f2, df, f;
 int  sistema;
 ps posvel;


 double k;
 

FILE *bif = fopen("plotting/data/biforcazione.dat", "w");
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

 
 

   for(f = 0.9; f <= f2; f += df){
    posvel.x = 1.57079632679489655800 ;
    posvel.v = k * PI/10.;
 
      
        for(posvel.t = 0; posvel.t < tmax * 100; ){

       
        posvel = rounge_kutta4(dt, w2, beta, posvel, f, wf,  sistema);
        
        }

      fprintf(bif, "%lf %lf %lf \n", f, posvel.v, posvel.x);
    }
 
 }

   fclose(bif);
  
}






            /*PROBLEMA DEI TRE CORPI E PROBLEMA DI KEPLERO*/

/*aggiornamento raggi*/

rg raggi(pxi pox, int d, built X, built Y, built Z){
rg rgn;
if(d==1){
rgn.r1 = sqrt(pox.x1 * pox.x1 + Y.ps1.x * Y.ps1.x + Z.ps1.x * Z.ps1.x);
rgn.r2 = sqrt(pox.x2 * pox.x2 + Y.ps2.x * Y.ps2.x + Z.ps2.x * Z.ps2.x);
rgn.r  = sqrt((pox.x2 - pox.x1) * (pox.x2 - pox.x1) + (Y.ps2.x-Y.ps1.x) * (Y.ps2.x-Y.ps1.x) + (Z.ps2.x-Z.ps1.x) * (Z.ps2.x-Z.ps1.x));
}
else if(d==2){
rgn.r1 = sqrt(X.ps1.x * X.ps1.x + pox.x1 * pox.x1 + Z.ps1.x * Z.ps1.x);
rgn.r2 = sqrt(X.ps2.x * X.ps2.x + pox.x2 * pox.x2 + Z.ps2.x * Z.ps2.x);
rgn.r  = sqrt((X.ps2.x - X.ps1.x) * (X.ps2.x - X.ps1.x) + (pox.x2 - pox.x1) * (pox.x2 - pox.x1) + (Z.ps2.x-Z.ps1.x) * (Z.ps2.x-Z.ps1.x));
}
else if(d==3){
rgn.r1 = sqrt(X.ps1.x * X.ps1.x+ Y.ps1.x * Y.ps1.x + pox.x1 * pox.x1);
rgn.r2 = sqrt(X.ps2.x * X.ps2.x + Y.ps2.x * Y.ps2.x + pox.x2 * pox.x2);
rgn.r  = sqrt((X.ps2.x - X.ps1.x) * (X.ps2.x-X.ps1.x) + (Y.ps2.x-Y.ps1.x) * (Y.ps2.x-Y.ps1.x) + (pox.x2 - pox.x1) * (pox.x2 - pox.x1));
} else if( d == 4){
  
rgn.r1 = sqrt(X.ps1.x * X.ps1.x + Y.ps1.x * Y.ps1.x + Z.ps1.x * Z.ps1.x);
rgn.r2 = sqrt(X.ps2.x * X.ps2.x + Y.ps2.x * Y.ps2.x + Z.ps2.x * Z.ps2.x);
rgn.r = sqrt((X.ps2.x - X.ps1.x) * (X.ps2.x-X.ps1.x) + (Y.ps2.x-Y.ps1.x) * (Y.ps2.x-Y.ps1.x) + (Z.ps2.x-Z.ps1.x) * (Z.ps2.x-Z.ps1.x));

}
else {
  printf("Che è successo? 1");
  exit(EXIT_FAILURE);
}
  return rgn;
}

/*posizioni per i raggi*/
pxi pox(double p1, double p2){
  pxi pox;
 pox.x1 = p1;
 pox.x2 = p2;
 return pox;
}

/*inizializzazione posizione e velocità dei due punti con massa*/
 double acc(double h1, double h2, int b, rg raggi){
  
 double a, r, r1, r2;
 double mu1 = 0.00517;
 double mu2 = 0.00517;
 double Gamma = 4 * PI * PI; //1.3E11 per il sistema solare
 r = raggi.r;
 r1 = raggi.r1;
 r2 = raggi.r2;


  if (b==0){
    a = mu2 * Gamma * (h2 - h1)/(r*r*r) - (Gamma * h1)/(r1*r1*r1);     // 
  } else if(b==1) {
    a = - mu1 * Gamma * (h2 - h1)/(r*r*r)- (Gamma * h2)/(r2*r2*r2);    // 
  } else {
  printf("che e' successo? 2");
    exit(EXIT_FAILURE);
  }
return a;
}

/*costruisco rk2 per keplero*/
built rounge_kutta4k(sf posveloa, sf posvelob, double dt,int f, int d, built X, built Y, built Z) {
  
 built pv;
 sf pv1;
 sf pv2;
 pxi h;
 rg R;
 int b, p;

 if(f==0){
    b = 0;
    p = 1;
 } else {
    b = 1;
    p = 0;
 }

 /*assieme alle posizioni aggiorno i raggi di consecutivo in modo da minimizzare gli errori*/
h = pox(posveloa.x , posvelob.x);
R = raggi(h, d, X, Y, Z);

 double x10 = posveloa.v * dt;
 double x11 = posvelob.v * dt;

 double v10 = acc(posveloa.x, posvelob.x, b, R) * dt;
 double v11 = acc(posveloa.x, posvelob.x , p, R) * dt;

 double x20 = (posveloa.v + 0.5 * v10) * dt;
 double x21 = (posvelob.v + 0.5 * v11) * dt;

 double v20 = acc(posveloa.x + 0.5 * x10, posvelob.x + 0.5 * x11 , b, R) * dt;
 double v21 = acc(posveloa.x + 0.5 * x10, posvelob.x + 0.5 * x11 , p, R) * dt;

 double x30 = (posveloa.v + 0.5 * v20) * dt;
 double x31 = (posvelob.v + 0.5 * v21) * dt;

 double v30 = acc(posveloa.x + 0.5 * x20, posvelob.x + 0.5 * x21, b, R) * dt;
 double v31 = acc(posveloa.x + 0.5 * x20, posvelob.x + 0.5 * x21, p, R) * dt; 

 double x40 = (posveloa.v + v30) * dt;
 double x41 = (posvelob.v + v31) * dt;

 double v40 = acc(posveloa.x + x30, posvelob.x + x31, b, R) * dt;
 double v41 = acc(posveloa.x + x30, posvelob.x + x31, p, R) * dt;


  pv1.x = posveloa.x + (x10 + 2.*x20 + 2.*x30 + x40)/6.0;
  pv1.v = posveloa.v + (v10 + 2.*v20 + 2.*v30 + v40)/6.0;


  pv2.x = posvelob.x + (x11 + 2.*x21 + 2.*x31 + x41)/6.0;
  pv2.v = posvelob.v + (v11 + 2.*v21 + 2.*v31 + v41)/6.0;
  


  pv.ps2 = pv2;
  pv.ps1 = pv1;
  return pv;
  
}


void keplero() {


double x01, y01, z01, vx01, vy01, vz01, x02, y02, z02, vx02, vy02, vz02, r, tmax = 128, dt = 0.001, t = 0, r1, r2, v2;;
int f, d;

/*l'algoritmo funziona aggiornando i vettori posizione e velocità, ogni vettore va valutato separatamente prima di integrare.*/
/*posizione corpo 1*/
x01 = 32;  //1.496E11 /*terra*/
y01 = 0.;
z01 = 0.;

/* posizione corpo 2*/
x02 = 30.21;  //2.307E11  /*marte*/
y02 = 0.;
z02 = 0.;

/*velocità corpo 1*/
vx01 = 0;
vy01 = -1.2; 
vz01 = 0.01;

/*velocità corpo 2*/
vx02 = 0;
vy02 = -0.9;
vz02 = -0.01;


built X;
built Y;
built Z;

/*inizializzazione variabili*/
X.ps1 = ips(x01, vx01);
Y.ps1 = ips(y01, vy01);
Z.ps1 = ips(z01, vz01);

X.ps2 = ips(x02, vx02);
Y.ps2 = ips(y02, vy02);
Z.ps2 = ips(z02, vz02);





FILE *j = fopen("plotting/data/keplero.dat","w");


f = 0; 

while(t < tmax) {

r1 = sqrt(X.ps1.x * X.ps1.x + Y.ps1.x * Y.ps1.x + Z.ps1.x * Z.ps1.x);
r2 = sqrt(X.ps2.x * X.ps2.x + Y.ps2.x * Y.ps2.x + Z.ps2.x * Z.ps2.x);
r = sqrt((X.ps2.x - X.ps1.x) * (X.ps2.x-X.ps1.x) + (Y.ps2.x-Y.ps1.x) * (Y.ps2.x-Y.ps1.x) + (Z.ps2.x-Z.ps1.x) * (Z.ps2.x-Z.ps1.x));

//decommenta d = 4 e decommenta gli altri per non interpolare i raggi sui valori di RK4 e commenta anche in RK4 h e R
//d = 4


d = 1;
X = rounge_kutta4k(X.ps1, X.ps2,  dt, f, d,  X,  Y,  Z);
d = 2;
Y = rounge_kutta4k(Y.ps1, Y.ps2,  dt, f, d,  X,  Y,  Z);
d = 3;
Z = rounge_kutta4k(Z.ps1, Z.ps2,  dt, f, d,  X,  Y,  Z);


v2 = sqrt(X.ps2.v * X.ps2.v + Y.ps2.v * Y.ps2.v);
t += dt;

fprintf(j, " %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf \n", t ,X.ps1.x, Y.ps1.x, Z.ps1.x, X.ps2.x, Y.ps2.x, Z.ps2.x, r, r2 - r1, r1, r2, X.ps1.v, X.ps2.v, Y.ps1.v, Y.ps2.v, v2 );

 }

fclose(j);

}








void traiettorie(double dt0){
 /*dati*/
double forze[] = {0.9, 1.07, 1.15, 1.47, 1.50};
double x0, v0, dt, beta, N, wf, w2, f, t0;
int sistema;
ps posvel;





sistema = 2;
x0 = PI * 0.5;
posvel.x = x0;
v0 = 0;
posvel.v = v0;
wf = 2./3;
beta = 0.5;
w2 = 1.0;
t0 = 100;
N = t0/dt0;
dt = dt0;
/*ora si prende rounge-kutta 4 e si esegue un ciclo di integrazione per ogni valore di f0*/
int j, i;
for(j = 0; j < (int)sizeof(forze); j++){/*ciclo di esecuzione del cambio di forzante*/
 

 if(j==0){
    FILE *fx1;
    fx1 = fopen("plotting/data/x1.dat", "w");
     f = forze[0];
    for (i = 1; i<=N; i++){
                      
                       posvel = rounge_kutta4(dt, w2, beta, posvel, f, wf, sistema);
                       
                    

                     fprintf(fx1, "%g %g \n", posvel.t, posvel.x);
                }
fclose(fx1);

 } else if (j == 1) {
  
 
sistema = 2;
x0 = PI * 0.5;
posvel.x = x0;
v0 = 0;
posvel.v = v0;
wf = 2./3;
beta = 0.5;
w2 = 1.0;
dt = dt0;
t0 = 100;
N = t0/dt;


posvel.t = 0;




     FILE*fx2;
     fx2 = fopen("plotting/data/x2.dat", "w");
     f = forze[1];
    for (i = 1; i<=N; i++){
                      
                       posvel = rounge_kutta4(dt, w2, beta, posvel, f, wf, sistema);
                     fprintf(fx2, "%g %g\n", posvel.t, posvel.x);
                }
fclose(fx2);

 }else if (j == 2) {

sistema = 2;
x0 = PI * 0.5;
posvel.x = x0;
v0 = 0;
posvel.v = v0;
wf = 2./3;
beta = 0.5;
w2 = 1.0;
dt = dt0;
t0 = 100;
N = t0/dt;

posvel.t = 0;


       FILE*fx3;
     fx3 = fopen("plotting/data/x3.dat", "w");
     f = forze[2];
    for (i = 1; i<=N; i++){
                  
                       posvel = rounge_kutta4(dt, w2, beta, posvel, f, wf, sistema);
                     fprintf(fx3, "%g %g\n", posvel.t, posvel.x);
                }
fclose(fx3);

 }else if (j == 3) {

sistema = 2;
x0 =PI * 0.5;
posvel.x = x0;
v0 = 0;
posvel.v = v0;
wf = 2./3;
beta = 0.5;
w2 = 1.0;
dt = dt0;
t0 = 100;
N = t0/dt;

posvel.t = 0;


     FILE*fx4;
     fx4 = fopen("plotting/data/x4.dat", "w");
     f = forze[3];
    for (i = 1; i<=N; i++){
                      
                       posvel = rounge_kutta4(dt, w2, beta, posvel, f, wf, sistema);
                     fprintf(fx4, "%g %g\n", posvel.t, posvel.x);
                }
fclose(fx4);

 }else if (j == 4) {
 
sistema = 2;
x0 = PI * 0.5;
posvel.x = x0;
v0 = 0;
posvel.v = v0;
wf = 2./3;
beta = 0.5;
w2 = 1.0;
dt =dt0;
t0 = 100;
N = t0/dt;

posvel.t = 0;


     FILE*fx5;
     fx5 = fopen("plotting/data/x5.dat", "w");
     f = forze[4];
    for (i = 1; i<=N; i++){
                     
                       posvel = rounge_kutta4(dt, w2, beta, posvel, f, wf, sistema);
                     fprintf(fx5, "%g %g\n", posvel.t, posvel.x);
                }
fclose(fx5);

 }

 
 
}

}