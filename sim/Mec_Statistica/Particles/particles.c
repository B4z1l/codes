#include "func.h" 


//il programma seguente è volto alla simulazione di un insieme di particelle rinchiuse all'interno di un contenitore di lato l.
//
//gli input sono svolti dal file input.dat nella cartella out.
//le istruzioni necessarie al funzionamento del sistema sono nel file README.txt
//
//
int main(void){ 

int seed = time(0);//inizializzo il generatore di sequenze casuali
srand48(seed);


//inizio a simulare una sola particella ferma per vedere che fa
//
//lo spazio di movimento è il piano 2d e la particella si muove casualmente in modo uniforme in tutte le direzioni
//


// inizializzo il file di output dati per salcare le posizioni per il plot
//
FILE* out = fopen("out.dat", "w");

int i,N = 1000000; //numero di passi da compiere


int x = 0, y = 0;

for(i = 0; i<N; i++){
x = x + rad();
y = y + rad();

fprintf(out, "%d %d\n", x ,y);

}

fclose(out);

 return 0;
}
 
 

