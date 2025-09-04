#Script for gnuplot

set terminal png size 1080, 920
set title "Sezioni di Poincare"
set output "C:Immagini/poincare/poincare.png"
set xlabel "α"
set ylabel "dα/dt"
set grid
plot "C:/Users/Nicola/Desktop/Programmi/C/codici_fisica_computazionale/Integratore/output/plotting/data/poincare.dat" u 1:2 pt 7 ps 0.6 notitle #, "C:/Users/Nicola/Desktop/Programmi/C/codici_fisica_computazionale/Integratore/output/plotting/data/fasi.dat" u 1:2 pt 1 ps 0.6 notitle 
reset 
