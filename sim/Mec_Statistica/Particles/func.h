#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>



// input da codice e ricompilato per ora, si creano solo le porzioni che simulano il movimento
// vettore delle velocità e delle posizioni per ogni paricella e del movimento casuale aggiunto
//
//

//GENERO NUMERI CASUALI PER SIMULARE UN MOTO BROWNIANO INDIPENDENTE PER OGNI PARTICELLA
//



int rad(){
float rad = drand48();
int add;

 if(rad > 0.5){
    	add = 1;
 }else if(rad < 0.5){
	add = -1;
 }

return add;

}



//Formo il vettore di coordinate del sistema 

//typedef struct pos{
//	int x;
//	int y;
//} pos;
//
// l'obiettivo ora è simulare N particelle anziché 1 e graficare la traiettoria 
