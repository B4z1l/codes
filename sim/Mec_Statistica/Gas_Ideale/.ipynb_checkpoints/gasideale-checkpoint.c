#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>


// definisco il limite quadrato di coordinate che pe laricelle possono raggiungere
#define edge 10
#define eps 0.1
// definisco il numero di particelle per chiarezza 
#define N 2


//Lo scopo di questo codice è di integrare un insieme di particelle che si ignorano a vicenda (gas ideale)  e che sbattono su un muro. 
//lo spazio disponibile è un quadrato bidimensionale di lunghezza "edge"


//prima di fare tutto mi serve salvare le coordinate e le velocità delle particelle, uso un'array di struct per risolvere
//


struct var{
	double pos[2];
	double vel[2];
};



double acc(double x){
	double a = -x*x;
	return a;
}


//Funzione per generare numeri casuali tra 0 e 1 gia pronta

double casuale(){
	double cass = (double) rand()/ (double)RAND_MAX;
	return cass;
}

//utilizzo eulero semplice per aggiornare le coordinate


struct var eulero(struct var old, double dt){
	struct var new;

	//a volte si bugga e va fuori dal muro quindi controllo e correggo qua:
	//il controllo lo faccio prima per evitare che le velocita creino problemi perché si invertono!

	for(int i = 0; i < N; i++){
		if(old.pos[i]>edge){
			old.pos[i] = edge;

		}else if(old.pos[i]<-edge){

			old.pos[i] = -edge;
		}
	}

	//qua verifico che la particella non sia al bordo del quadrato
	if(fabs(edge - old.pos[0])<eps || old.pos[0] < -edge){
		old.vel[0] = -old.vel[0]; // la particella sbatte sul muro e ritorna indietro 
	}
	if(fabs(edge - old.pos[1])<eps || old.pos[1] < -edge){
		old.vel[1] = -old.vel[1];
	}


   new.vel[0] = old.vel[0]; //per ora non ci sono accelerazioni (gas perfetto in spazio come ti pare)
   new.vel[1] = old.vel[1];
   
   new.pos[0] = old.pos[0] + new.vel[0]*dt + 0.5*acc(old.pos[0])*dt*dt;
   new.pos[1] = old.pos[1] + new.vel[1]*dt + 0.5*acc(old.pos[1])*dt*dt;

  return new;
} //tanto più è piccolo dt più è precisa la collision detection


//creo una funzione che vada ad inizializzare la posizione e la velocità di ogni particella:
//
 

struct var inizializzazione(struct var old){
	 
	 //per inizializzare il tutto uso valori randomici per le posizioni (nel range definito obv) e imposto le velocità uniformi er semplicità 
         
	old.pos[0] = 10. * casuale();
        old.pos[1] = 10. * casuale();
	old.vel[0] = 5. * casuale();
	old.vel[1] = 5. * casuale();

 return old;	
 }





int main(void){
	srand(time(NULL)); // questo inizializza i numeri casuali
//la prima cosa che si vuole fare è sicuramente inizializzare un array di struct creato per poi aggiornarlo e stampare i dati raccolti
struct var syst[N];

for(int i = 0; i < N; i++){
syst[i] = inizializzazione(syst[i]);
printf("%lf %lf %lf %lf\n", syst[i].pos[0], syst[i].pos[1], syst[i].vel[0], syst[i].vel[1]); 
}

double t, dt = 0.01, tmax = 400.; 
//apro un file per la scrittura della posizione di almeno una particella;
 
FILE* ps = fopen("out.txt", "w");


//LOG 20/08/2025 corretto tutto, si compila e funziona, si possono aggiungere un numero qualsiasi di particelle ma va  cambiata l'inizializzazione delle particelle con random posizioni e velocità (in modo da avere una energia interna prestabilita però) e tale da stampare su file diversi i valori delle particelle.
//LOG 28/08/2025 aggiunta la possibilità di stamapare due particelle con accelerazione, ho corretto il controllo delle pareti dopo che ho vistoche le particelle la superavano lo stesso

while(t<tmax){
        for(int i = 0; i < N; i++){
	syst[i] = eulero(syst[i], dt);
	}

	for(int i = 0; i< N; i++){
		fprintf(ps," %lf %lf %lf\n", t, syst[i].pos[0], syst[i].pos[1]);
	}
t += dt;

}

fclose(ps);
	return 0;
}



