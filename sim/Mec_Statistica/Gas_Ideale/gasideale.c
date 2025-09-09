#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<stdbool.h>
#include<unistd.h>
#include <omp.h>

// definisco il limite massimo della scatola
#define edge 10.
#define eps 0.01 // questo serve per i controlli al bordo
// definisco il numero di particelle e la dimensione della simulazione
#define N 1000  //lo stack è piccolo quindi non eccedere le 20000
#define dim 3
#define k 1000.0
//Lo scopo di questo codice è di integrare un insieme di particelle che si ignorano a vicenda (gas ideale)  e che sbattono su un muro. 



//prima di fare tutto mi serve salvare le coordinate e le velocità delle particelle, uso un'array di struct di array per risolvere



struct var{
	double pos[dim];
	double vel[dim];
};


//funzione accelerazione dello spazio di simulazione
//questa funzione deve essere modificata prima o poi per comprendere l'accelerazione dovuta alle singole particelle (che generano da sole potenziali!)

double acc(double x, double v, double t, int h){
	double a;
	if(h == 2){
	a = 0;
	} else if (h == 0){
		a = 0;
	} else {
		a = 0;
	}

	return a;
}


//Funzione per generare numeri casuali tra 0 e 1 gia pronta

double casuale(){
	double cass = (double) rand()/ (double)RAND_MAX;
	return cass;
}

//genero -1 o +1 casualmente

double nepos(bool flag){
	double sig;
    if(flag){
	double n = (double) rand()/ (double) RAND_MAX;
	if(n > 0.5){
		sig = 1.;
	} else {
		sig = -1.;
	}
	}else {
		sig = 1;
	}

	return sig;

}


// array globali per RK4
double k1_v[N][dim], k1_x[N][dim];
double k2_v[N][dim], k2_x[N][dim];
double k3_v[N][dim], k3_x[N][dim];
double k4_v[N][dim], k4_x[N][dim];


double total_acc(double pos, double vel, int i, double t) {
	double a = acc(pos, vel, t, i); // tua funzione di accelerazione

	if(pos > edge){
		a += -k*(pos - edge);
	}else if(pos < -edge){
		a += -k*(pos + edge);
	}

	return a;
}



// integrazione RK4 con OpenMP

void integ(struct var old[N], struct var new[N], double dt, double t) {
	#pragma omp parallel for
	for(int p = 0; p < N; p++){
		for(int i = 0; i < dim; i++){
			k1_v[p][i] = total_acc(old[p].pos[i], old[p].vel[i], i, t) * dt;
			k1_x[p][i] = old[p].vel[i] * dt;
		}
	}

	#pragma omp parallel for
	for(int p = 0; p < N; p++){
		for(int i = 0; i < dim; i++){
			k2_v[p][i] = total_acc(old[p].pos[i] + 0.5*k1_x[p][i], old[p].vel[i] + 0.5*k1_v[p][i], i, t + 0.5*dt) * dt;
			k2_x[p][i] = (old[p].vel[i] + 0.5*k1_v[p][i]) * dt;
		}
	}

	#pragma omp parallel for
	for(int p = 0; p < N; p++){
		for(int i = 0; i < dim; i++){
			k3_v[p][i] = total_acc(old[p].pos[i] + 0.5*k2_x[p][i], old[p].vel[i] + 0.5*k2_v[p][i], i, t + 0.5*dt) * dt;
			k3_x[p][i] = (old[p].vel[i] + 0.5*k2_v[p][i]) * dt;
		}
	}

	#pragma omp parallel for
	for(int p = 0; p < N; p++){
		for(int i = 0; i < dim; i++){
			k4_v[p][i] = total_acc(old[p].pos[i] + k3_x[p][i], old[p].vel[i] + k3_v[p][i], i, t + dt) * dt;
		    k4_x[p][i] = (old[p].vel[i] + k3_v[p][i]) * dt;
		}
	}

	// aggiornamento finale
	#pragma omp parallel for
	for(int p = 0; p < N; p++){
		for(int i = 0; i < dim; i++){
			new[p].vel[i] = old[p].vel[i] + (k1_v[p][i] + 2*k2_v[p][i] + 2*k3_v[p][i] + k4_v[p][i])/6.0;
			new[p].pos[i] = old[p].pos[i] + (k1_x[p][i] + 2*k2_x[p][i] + 2*k3_x[p][i] + k4_x[p][i])/6.0;
		}
	}
}




struct var inizializzazione(struct var old){        //inizializzazione posizioni e velocita
	 bool flag1 = false;
     bool flag2 = true;

	for(int i = 0; i < dim; i++){

	    old.pos[i] =  edge * casuale() * nepos(flag1);
	    old.vel[i] = 50. * casuale() * nepos(flag2);

	}
 return old;	
 }




void densita(FILE *de, struct var sis[N], double t){      // calcolo la densità in ogni istante del sistema e scrivo su file

	double vol = (double) edge * edge * edge / 2.;


	int num = 0;

	for(int i = 0; i < N; i++){
		if(sis[i].pos[0] > 0.){
			num++;
		}
	}
	double den = (double) num / vol;
	fprintf(de, "%lf %lf\n", t, den);

return;

}





 //===================================> OBIETTIVI PRINCIPALI: calcolare la pressione su ogni faccia, calcolare la densità volumetrica di particelle nel tempo in volumetti definiti.





//----------------------------------------------------------------------------------------------------------/         MAIN

int main() {
	struct var new_syst[N];  // unico array per lo stato corrente delle particelle

	double t = 0.0, dt=0.001, tmax = 10.0;
	

	FILE* ps = fopen("out.dat", "w");
	FILE* de = fopen("dens.dat", "w");
	if(!ps || !de){
		printf("Errore apertura file!\n");
		return 1;
	}

	fprintf(ps, "t x y z\n");

	// inizializzazione particelle
	for(int i = 0; i < N; i++){
		new_syst[i] = inizializzazione(new_syst[i]);
	}

	// ciclo temporale
	while(t < tmax){
		// calcolo densità
		densita(de, new_syst, t);

		// integrazione RK4
		struct var old_syst[N];
		for(int i = 0; i < N; i++)
			old_syst[i] = new_syst[i];  // salva stato corrente temporaneamente

			integ(old_syst, new_syst, dt, t);

		// scrittura posizioni su file

		for(int i = 0; i < N; i++){
			fprintf(ps, "%lf %lf %lf %lf\n", t,
					new_syst[i].pos[0],
		   new_syst[i].pos[1],
		   new_syst[i].pos[2]);
		}


		t += dt;
	}

	fclose(ps);
	fclose(de);



	system("gnuplot graf.gp"); //faccio il grafico della densità nella directory corrente



	bool animazione3d = false; //decido se fare l'animazione (meglio false che se no occupa troppa ram se ci sono tante particelle)
	bool animazione = false; // riemepie un sacco la memoria

	if(animazione3d){
       system("~/Documents/codes/venv/bin/python3 ani3d.py");
	}else if(animazione){
		system("~/Documents/codes/venv/bin/python3  anima.py");
	}



	return 0;
}

//per decompilare il binario: objdump -D -M amd64 bianrio > file.asm


//LOG 20/08/2025 corretto tutto, si compila e funziona, si possono aggiungere un numero qualsiasi di particelle ma va  cambiata l'inizializzazione delle particelle con random posizioni e velocità (in modo da avere una energia interna prestabilita però) e tale da stampare su file diversi i valori delle particelle.
//LOG 28/08/2025 aggiunta la possibilità di stamapare due particelle con accelerazione, ho corretto il controllo delle pareti dopo che ho vistoche le particelle la superavano lo stesso
//LOG 04/09/2025 Agginta la terza dimensione e reso più generale la generazione di punti e velocità assieme ai calcoli per dimensioni più alte.
//LOG 06/09/2025 Aggiunto il calcolo della densità per un volume pari ad un mezzo del totale (x>0)
//LOG 07/09/2025 Ottimizzato l'integrazione implementando il multithread, inoltre è stato implementato un potenziale elastico alla parete per il rimbalzo e rk4 per l'integrazione.

