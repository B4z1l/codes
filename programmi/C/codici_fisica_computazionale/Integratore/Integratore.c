#include <time.h>
#include "def.h"


ps iposvel(double x0, double v0, double t0);
ps eulero(double dt, double w2, double beta, ps posvel, double f0, double wf, int sistema, double alf);
ps eulero_cromer(double dt, double w2, double beta, ps posvel, double f0, double wf, int sistema, double alf);
ps verlet_autosufficiente(double dt, double w2, double beta, ps posvel, double f0, double wf,  int sistema, double alf);
ps rounge_kutta2(double dt, double w2, double beta, ps posvelo, double f0, double wf, int sistema, double alf);
ps rounge_kutta4(double dt, double w2, double beta, ps posvelo, double f0, double wf,  int sistema, double alf);


double energia(double w2, ps posvel, int sistema, double l);
double enersimp(double x, double v, double w2);
double oscillatoreforzato(double w2, double x, double beta, double v, double f0, double wf, double dt, int sistema, double alf);
double potenziale(double w2, double x, int sistema, double l);
int scelta(int algoritmo, int at, FILE *o);
void algoritmi(int algoritmo, double dt, double w2, double beta, long int N, ps posvel, double E0, FILE *fp, double f0, double wf, int sistema, int c, double l, double alf);
void poincare();
void attrazione();
void keplero();
void biforcazione();
int letint(char *print);
double letdoub(char *print);
void errori();
void traiettorie(double dt0);

/*inizia qui l'algoritmo*/

int main(void) {


    double x0, v0, dt, w2, T, E0, l, beta, t, f0, wf, alf;
    long int N;
    int algoritmo, sistema, forz, c, at;
    ps posvel;
 
 FILE *o = fopen("output/log/output.log", "w");
 if(o == NULL){
    printf("Attenzione output.log non pervenuto");
    exit(EXIT_FAILURE);
  }

  
  inizio:    
     /*commentare riga 47 se si vuole solo automatico e decommentare riga 48, altrimenti il contrario*/
    //at = letint("Inserisci 0 per prendere i dati da file, 1 per inserire manualmente i dati."); 
    at = 0;
    
  switch (at) {
   case 0:
    printf("hai scelto input da file\n");
    forz = 0;
    goto autoin;
   break;

   case 1:
    printf("Hai scelto input manuale\n");
   break;

   default:
    printf("La tua scelta non rientra nelle opzioni, ritenta\n");
    fflush(stdin);
    goto inizio;
   break;
  }

  sistema = letint("inserisci 1 per integrare un oscillatore, 2 per un pendolo, 3 per l'analisi degli errori ,\n 4  per le sezioni di Poincare, 5 per i bacini di attrazione, 6  per le biforcazioni, 7  per il problema di keplero, 8 per le traiettorie, 0 per uscire");

  autoin:



 

  if(at == 0) {
  FILE *z = fopen("output/input/input.txt", "r");

   if(z == NULL){
    fprintf(stderr, "Attenzione input non presente si crei il file input.dat inserire i dati come indicato nella relazione\n");
    exit(EXIT_FAILURE);
   } else {
    fscanf(z, "%d %d %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", &sistema, &algoritmo, &beta, &f0, &wf, &x0, &v0, &t, &dt, &l, &w2, &alf);
    fclose(z);
   }
  }


if ((sistema == 1 && at == 0) || (sistema == 2 && at == 0) || sistema == 3 || sistema == 0|| sistema == 4 || sistema == 5 || sistema == 6|| sistema == 7 || sistema == 8) {
   goto salto;
} else if (sistema == 1 || sistema == 2) {
   forza:
    if(at == 1){
       forz = letint("Inserisci 1 per classico, 2 per lo smorzato, 3 per forzato, 4 per caotico");
     }
} else {
    printf("non vale, scegli bene!\n");
    fflush(stdin); 
    goto inizio;
}
    
 //*********************************************************************************************************
  if (forz == 1) {
      beta = 0.0;
  } else if (forz == 2) {
      beta = letdoub("inserisci il valore di beta\n");
  } else if (forz == 3){
    beta = 0.0;
      f0 = letdoub("inserisci il valore del forzante\n");
      wf = letdoub("inserisci il valore della sua frequenza\n");
  } else if (forz == 4) {
    beta = letdoub("inserisci il valore della resistenza\n");
      f0 = letdoub("inserisci il valore del forzante\n");
      wf = letdoub("inserisci il valore della frequenza del forzante\n");
  } else {
    printf("Hai sbagliato, reinserisci!");
    fflush(stdin);
    goto forza;
  }

 //*********************************************************************************************************


salto:


  printf("\n Iniziamo i calcoli...\n");
 
   clock_t q; /*inizio del contatore del tempo*/
  q = clock();

  //000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000

                              /*codice di integrazione dell'oscillatore*/


  if (sistema == 1 ) {        ///////////////////////////////////////////////////////

     fprintf(o, "Hai scelto di integrare un oscillatore\n");

      initosc: 

      if(at == 1){
      algoritmo = letint("inserisci 0 per eulero, 1 per eulero-cromer, 2 per verlet autosufficiente, 3 per Rounge-Kutta");
      }

      c = scelta(algoritmo, at, o);

         if ( c==1 ){
          goto initosc;
         } else if(c == 2) {
           fprintf(o,"non vi sono altri metodi, scegli tra quelli presenti!\n");
           fflush(stdin);
          goto initosc;
         }

        /*qui è per valutare la conservazione dell'energia con i vari metodi a diversi dt*/
        FILE *fp = fopen("/home/bazil/Documents/codes/Programmi/C/codici_fisica_computazionale/Integratore/output/plotting/data/dati.dat", "w");
        if(fp == NULL){
        printf("Errore: impossibile aprire plotting/data/dati.dat\n");
         exit(EXIT_FAILURE);
        }
      if(at == 0){
        goto go1;
      }
        


        v0 = letdoub("Scegli la velocita' iniziale v0");
        x0 = letdoub("Scegli la posizione iniziale x0");
        w2 = letdoub("Scegli la pulsazione quadra w2");
    
      tempo1:

         t = letdoub("Scegli l'intevallo di tempo su cui integrare t");
        dt = letdoub("Scegli il passo di integrazione dt");
        
        go1:
         N = (long int)(t/dt);

           if (N>= 100000000 || N < 0) {
               printf("Numero passi troppo grande, per evitare problemi reinserisci t e dt:\n");
               goto tempo1; 
            }

      fprintf(o,"dt = %lf, t = %lf\n", dt, t);
      fprintf(o,"w2 = %lf, x0 = %lf, v0 = %lf\n",w2, x0, v0);
      fprintf(o,"Numero di passi da integrare N = %li \n", N); 
               /*inizializzo le variabili*/
      l = 1;
      posvel = iposvel(x0, v0, 0);  
      E0 = energia(w2, posvel, sistema, l);
      fprintf(o,"A t = 0 l'energia vale %lf \n", E0);
               /*facciamo i calcoli ora*/
      algoritmi(algoritmo, dt, w2, beta, N, posvel, E0, fp, f0, wf, sistema, c, l, alf);
      

  } else if (sistema == 2) {     //////////////////////////////////////////////////////////////

                              /*codice di integrazione per il pendolo*/
  sistema = 2;
  fprintf(o,"hai scelto di integrare un pendolo\n");


  initpen:

  if(at == 1){
  algoritmo = letint("inserisci 0 per eulero, 1 per eulero-cromer, 2  per verlet autosufficiente, 3 per Rounge-Kutta ");
  }
               /*inserire controllo algoritmi*/
      c = scelta(algoritmo, at, o);
        
           if ( c==1 ){
          goto initpen;
         } else if(c == 2) {
           fprintf(o,"non vi sono altri metodi, scegli tra quelli presenti!\n");
           fflush(stdin);
          goto initosc;
         }


if(at == 0){
  goto go2;
}

/*qui è per valutare la conservazione dell'energia con i vari metodi a diversi dt*/

     
           /*scelgo i valori iniziali*/
    l = letdoub("Inserire la lunghezza del pendolo"); /*in metri*/
    x0 = letdoub("inserire angolo iniziale "); /*in radianti*/
    v0 = letdoub("inserire velocita' angolare iniziale");
    
   tempo2: 

     t = letdoub("Scegli l'intevallo di tempo su cui integrare t");
    dt = letdoub("Scegli il passo di integrazione dt");

   go2:

     N = (long int)(t/dt+0.5);
      if (N >= 1000000000 || N < 0) {
            printf("Numero passi troppo grande, per evitare problemi reinserisci T e dt:\n");
            goto tempo2; 
      }
     T = 2 * PI * sqrt(l/g);
    w2 = g/l;

      fprintf(o, "Il periodo teorico calcolato e' T=%lf", T);
      fprintf(o,"\n Il numero di punti da integrare e' N = %li \n", N);

   /*inizializzo le variabili*/
    posvel = iposvel(x0, v0, 0);  
      fprintf(o,"theta(0) = %lf, omega(0) = %lf\n", posvel.x, posvel.v);
    E0 = energia(w2, posvel, sistema, l);
      fprintf(o,"A t = 0 l'energia vale %lf \n", E0);
      /*inizio algoritmi di calcolo per il pendolo*/
       FILE *fp = fopen("plotting/data/dati.dat", "w");
      algoritmi(algoritmo, dt, w2, beta, N, posvel, E0, fp, f0, wf, sistema, c, l, alf);
      printf("qua");
///////////////////////////////////////////////////////////////////////////////////////////
  } else if (sistema == 3) {
    fprintf(o,"hai scelto l'analisi degli errori\n");
   errori();

  } else if (sistema == 4) {
    fprintf(o,"hai scelto di generare le sezioni di Poincare'\n");
   poincare();

  } else if (sistema == 5) { 
     fprintf(o,"hai scelto di generare i bacini di attrazione... buona fortuna...\n");
   attrazione();
  
  } else if (sistema == 6) { 
     fprintf(o,"hai scelto le biforcazioni\n");
   biforcazione();

  } else if (sistema == 7) {
    fprintf(o,"hai deciso di integrare il problema di Keplero\n");
   keplero();

  } else if (sistema == 8) {
    fprintf(o, "hai deciso di calcolare le traiettorie a diverso forzante");
    dt = 0.001;
    traiettorie(dt);
  } else if (sistema == 0) {
   fprintf(o,"Arrivederci allora...\n");
      exit(EXIT_SUCCESS);

  } else {
  printf("Scegli bene cosa vuoi fare!\n");
  fflush(stdin);

     goto inizio; /*torno all'inizio delle scelte*/
  } 


fprintf(o,"Fatto!");
q = clock() - q;
  double time_taken = ((double)q)/CLOCKS_PER_SEC; 

fprintf(o,"\n the program took %lf seconds to finish", time_taken);
fclose(o);
return 0;

}





