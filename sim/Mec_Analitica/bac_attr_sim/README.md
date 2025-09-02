Il software è intento nel ricreare le immagini dei bacini di attrazione.
ogni immagine viene computata con gnuplot per ora e viene salvata in out/plot/img

-viene creato il file data.dat in cui sono contenuti i dati della simulazione

-viene generata l'immagine da gnuplot e salvata tramite il file att.gp o tramite chiamate a sistema nella cartella /img

 -- viene genrato il file att.gp in cui vengono printate le linee di codice necessarie alla compilazione dell'immagine

-il programma ritorna e aumenta il tempo di simulazione di Dt facendo gli stessi passaggi fino a raggiungere il Tmax impostato 

-raggiunto Tmax il programma si arresta ed esce dalla computazione al salvataggio dell'ultima immagine

-il programma scrive per ultimo il tempo impiegato a calcolare il tutto
