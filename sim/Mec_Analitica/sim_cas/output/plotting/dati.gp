#Script for gnuplot

set terminal png size 1270, 720
set title "Traiettoria pendolo smorzato"
set output "C:Immagini/pendolo/traipendcaos.png"
set xlabel "t"
set ylabel "x(t)"
set grid
plot "data/dati.dat" u 1:2 w l 
reset 

set terminal png size 1270, 720
set title "Velocità pendolo smorzato"
set output "C:Immagini/pendolo/velpendcaos.png"
set xlabel "t"
set ylabel "v(t)"
set grid
plot "data/dati.dat" u 1:3 w l 
reset 



set terminal png size 1270, 720
set title "Energia"
set output "C:Immagini/pendolo/enerpendcaos.png"
set xlabel "t"
set ylabel "e"
set grid
plot "data/dati.dat" u 1:4 w l 
reset 