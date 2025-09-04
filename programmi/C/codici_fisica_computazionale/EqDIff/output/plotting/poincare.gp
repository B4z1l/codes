#Script for gnuplot

set terminal png size 1920, 1080
set title "Sezioni di Poincare"
set output "C:Immagini/poincare/poincare.png"
set xlabel "α"
set ylabel "dα/dt"
set grid
plot "data/fasi.dat" u 1:2 w d notitle, "data/poincare.dat" u 1:2 pt 7 ps 0.6 notitle 
reset 
