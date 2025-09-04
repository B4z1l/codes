set terminal png size 1000, 700
set title "Traiettoria problema dei tre corpi"
set output "immagini/Keplero/traikeplero.png"
set xlabel "x"
set ylabel "y"
set grid
plot "data/keplero.dat" u 2:3 w l title "Primo corpo", "data/keplero.dat" u 5:6 w l title "secondo corpo"
reset 
