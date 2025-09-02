//Lo scopo di questo codice è correggere in un loop il nome dei file png per i bacini di attrazione
//una volta utilizzato vado a correggere il codice sorgente delle immagini così non si usa più questo codice

//TASKS


//-il codice printa una stringa (comando bash)
//-il comando è mov file1.png file%d1.png
//--Ovviamente bisogna figurarsi come immettere un ciclo che possa printare il comando al sistema aggiornando il valore %d
//fatto questo si avvia il programma e si risolve per tutte le 200 immagini


//-l'idea è quella di aggiornare una stringa nota e passarla a system
//--RIVEDERE TEORIA DEI CHAR



#include<stdio.h>
#include<stdlib.h>

int main(void){

int n = 5, i;



//-viene creato un file su cui viene per ogni ciclo printata una stringa
//--la stringa viene aggiornata ad ogni ciclo con il valore corretto
//-la stringa viene letta dal file e viene copiata sulla variabile str
//-la stringa str viene mandata a system in modo ricorsivo 
//-il comando viene eseguito dal sistema




for(i = 0; i<n; i++){
FILE* st = fopen("str.txt", "w+");
    
    char str[40];
    double l = i;
   fprintf(st, "mv att_t%0.0lf.png att_t00%0.0lf.png\n", l*100, l*100);
   printf("fatto %d\n", i);
   fgets(str, 40, st);
   
   printf("%s\n", &str);


    system(str);
    
    fclose(st);
}



    return 0;
}



