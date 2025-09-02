#include <time.h>
#include "def.h"


void attrazione();
struct in;
int main(void){

    clock_t q; 
  q = clock();

  
//inizializzo la ini

in ini;

 ini.wf = 2.4;
 ini.beta = 0.7;
 ini.w2 = 3.;
 ini.dt = 0.01;
 ini.f0 = -1.35; 
 ini.tmax = 0;
 double Tmax = ini.tmax + 10., Dt=1.;

 


while(ini.tmax<=Tmax){

 attrazione(ini);

FILE*att = fopen("out/plot/att.gp", "w"); //genero il file att.gp per la generazione delle immagini il tempo è segnato in millisecondi
  fprintf(att, "set terminal png size 900,800\n");
  fprintf(att, "set title \"Bacini di attrazione ad f0 = 1.35, tmax = %0.0lf ms\"\n", ini.tmax*1000);

  fprintf(att, "set output \"/home/bazil/Documents/codes/bac_attr_sim/out/plot/img/att_t%0.0lf.png\"\n", ini.tmax*1000);
  fprintf(att, "set xlabel \"α\"\n");
  fprintf(att, "set ylabel \"dα/dt\"\n");
  fprintf(att, "set grid \n");
  fprintf(att, "unset key\n");
  fprintf(att,"set palette defined (-1.5 \"black\", 1.5 \"red\")\n");
  fprintf(att, "plot \"/home/bazil/Documents/codes/bac_attr_sim/out/plot/data.txt\" u 1:2:3 w d palette z\n");
  fprintf(att, "reset\n");
fclose(att);

system("gnuplot /home/bazil/Documents/codes/bac_attr_sim/out/plot/att.gp"); // creo l'immagine

ini.tmax += Dt;

}


q = clock() - q;
  double time_taken = ((double)q)/CLOCKS_PER_SEC; 

FILE* log = fopen("out/log/out.log", "w");
fprintf(log, "Finito! Sono passati %lf min", time_taken/60);
fclose(log);

    return 0;
}